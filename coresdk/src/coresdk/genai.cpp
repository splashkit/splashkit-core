//
//  genai.cpp
//  splashkit
//
//  Created by Sean Boettger on 20/12/25.
//

#include "genai_driver.h"
#include "genai.h"
#include "utility_functions.h"
#include "web_driver.h"
#include "terminal.h"
#include "core_driver.h"
#include "random.h"

#include <filesystem>
#include <sstream>

namespace splashkit_lib
{
    // forward declare private function -- until language_model_options can be exported
    language_model_options option_language_model(language_model model);

    static vector<conversation> objects;

    const language_model DEFAULT_LANGUAGE_MODEL = QWEN3_0_6B_INSTRUCT;
    const language_model DEFAULT_BASE_LANGUAGE_MODEL = QWEN3_0_6B_BASE;

    const int DEFAULT_MAX_TOKENS_BASE = 125; // base has a higher likelihood of running forever for no reason, better to limit it early
    const int DEFAULT_MAX_TOKENS_INSTRUCT = 4096;
    const int DEFAULT_MAX_TOKENS_THINKING = 4096;

    extern const std::array<language_model_options, 26> models; // defined at end of file

    /* terminal util functions in lieu of ncurses*/
    void terminal_erase_left(int count /* -1 for all */)
    {
        if (count == 0)
            return;

        if (count == -1)
            write("\r\033[K");
        else
            write("\033[" + std::to_string(count) + "D\033[K");
    }

    std::vector<int> terminal_stack;

    void terminal_push(const string &str)
    {
        write(str);
        terminal_stack.push_back(str.size());
    }

    void terminal_pop()
    {
        terminal_erase_left(terminal_stack.back());
        terminal_stack.pop_back();
    }

    bool download_with_progress_bar(string filename, string url)
    {
        auto callback = [](unsigned long expected_size, unsigned long current_size)
        {
            terminal_pop();

            if (expected_size == 0)
            {
                terminal_push("");
                return;
            }

            static int spinner_index = 0;

            const int progress_bar_length = 10;
            const string spinner = "|/-\\";

            int expected_mb = expected_size / (1024 * 1024);
            int current_mb = current_size / (1024 * 1024);

            // construct progress bar
            int progress_bar_filled = 0;
            if (expected_size > 0)
                progress_bar_filled = (int)(progress_bar_length * current_size/(double)expected_size);
            if (progress_bar_filled > progress_bar_length)
                progress_bar_filled = progress_bar_length;

            string progress_bar = string(progress_bar_filled, '=') + string(progress_bar_length-progress_bar_filled, ' ');
            if (progress_bar_filled <= progress_bar_length)
                progress_bar[progress_bar_filled] = spinner[(spinner_index++)/2 % spinner.size()];

            // write message
            terminal_push(progress_bar + "| (" + std::to_string(current_mb) + "mb / " + std::to_string(expected_mb) + "mb)");
        };

        terminal_push("");

        sk_http_response * resp = sk_http_get_file(filename, url, 443, callback);

        terminal_pop();

        return resp != nullptr && resp->code >= 200 && resp->code < 300;
    }

    bool ensure_exists_or_download(string path, string url, string message)
    {
        if (std::filesystem::exists(path))
            return true;

        terminal_push(message);

        bool result = download_with_progress_bar(path, url);

        terminal_pop();

        return result;
    }

    llamacpp::model __get_model(language_model_options options)
    {
        llamacpp::init();

        if (options.url != "" && !ensure_exists_or_download(options.path, options.url, " ::: Downloading Language Model: " + options.name + " |"))
        {
            CLOG(ERROR, "GenAI") << "Failed to download language model - see error above.";
            return {false};
        }

        return llamacpp::create_model(options.path);
    }

    string __generate_common(string prompt, language_model_options options, bool format_chat)
    {
        llamacpp::model model = __get_model(options);

        if (!model.valid) return "";

        std::string formatted = prompt;

        if (format_chat)
        {
            formatted = llamacpp::format_chat(model, {
                {
                    "user", prompt + options.prompt_append
                },
            }, true);
        }
        llamacpp::llama_tokens tokens = llamacpp::tokenize_string(model, formatted, true);

        llamacpp::context ctx = llamacpp::start_context(model, tokens, {
            options.temperature,
            options.top_p,
            options.top_k,
            options.min_p,
            options.presence_penalty,
            options.max_tokens,
            options.use_seed,
            (uint32_t)options.seed
        });

        std::string result = "";
        llamacpp::token_result token;

        while (!llamacpp::context_step(ctx, &token))
        {
            if (token.type == llamacpp::token_result::CONTENT)
                result += token.text;
        };

        llamacpp::delete_context(ctx);
        llamacpp::delete_model(model);

        return trim(result);
    }

    // Made private for now - due to string field

    /**
     * @brief Generates a reply to a textual prompt by a language model
     *
     * The language model will respond to the textual prompt in a chat style format. It will follow instructions and answer questions.
     * Instruct or Thinking models are recommended. Base models likely won't output sensible results.
     *
     * @param prompt  The prompt for the language model to reply to.
     * @param options The generation options - use the `option_` functions to create this, for instance `option_language_model`
     *
     * @returns The generated reply.
     *
     * @attribute suffix with_options
     */

    string generate_reply(string prompt, language_model_options options)
    {
        return __generate_common(prompt, options, true);
    }

    string generate_reply(string prompt)
    {
        return generate_reply(DEFAULT_LANGUAGE_MODEL, prompt);
    }    

    string generate_reply(language_model model, string prompt)
    {
        return generate_reply(prompt, option_language_model(model));
    }    

    /**
     * @brief Generates text that continues from a prompt
     *
     * The language model will continue predicting text based on patterns in the prompt - it will not directly follow instructions or answer questions.
     * Base models are recommended; Instruct and Thinking models may work.
     *
     * @param text The input text for the language model to continue.
     * @param options The generation options - use the `option_` functions to create this, for instance `option_language_model`
     *
     * @returns The generated reply.
     *
     * @attribute suffix with_options
     */
    string generate_text(string text, language_model_options options)
    {
        return __generate_common(text, options, false);
    }

    string generate_text(language_model model, string text, int max_tokens)
    {
        language_model_options opts = option_language_model(model);
        opts.max_tokens = max_tokens;
        return generate_text(text, opts);
    }    

    string generate_text(string text, int length)
    {
        return generate_text(DEFAULT_BASE_LANGUAGE_MODEL, text, length);
    }    

    string generate_text(string text)
    {
        return generate_text(DEFAULT_BASE_LANGUAGE_MODEL, text, DEFAULT_MAX_TOKENS_BASE);
    }    

    string generate_text(language_model model, string text)
    {
        return generate_text(model, text, DEFAULT_MAX_TOKENS_BASE);
    }    


    // --------------------------------------------------------------

    // Streaming conversation

    #define CONVERSATION_CHECK(x, val) \
        if (INVALID_PTR(c, CONVERSATION_PTR))\
        {\
            LOG(WARNING) << "Passed an invalid conversation object to " x;\
            return val;\
        }

        /**
         * @brief Creates a new `conversation` object, that uses a chosen language model among other options.
         *
         * The `conversation` object can have messages added to it, and responses streamed back from it via the other Conversation functions and procedures
         *
         * @param options The options to use - use this to choose the language model, and change various parameters.
         *
         * @returns Returns a new `conversation` object.
         *
         * @attribute class       conversation
         * @attribute constructor true
         *
         * @attribute suffix with_options
         */
        conversation create_conversation(language_model_options options)
        {
            internal_sk_init();
    
            llamacpp::model model = __get_model(options);
    
            if (!model.valid) return nullptr;
    
            llamacpp::llama_tokens initial_tokens = llamacpp::tokenize_string(model, "", true);
    
            sk_conversation* c = new sk_conversation();
            c->id = CONVERSATION_PTR;
            c->model = model;
            c->context = llamacpp::start_context(model, initial_tokens, {
                options.temperature,
                options.top_p,
                options.top_k,
                options.min_p,
                options.presence_penalty,
                options.max_tokens,
                options.use_seed,
                (uint32_t)options.seed
            });;
    
            c->was_generating = false;
            c->is_generating = true;
    
            c->prompt_append = options.prompt_append;
    
            objects.push_back(c);
    
            return c;
        };

    conversation create_conversation()    
    {
        return create_conversation(option_language_model(DEFAULT_LANGUAGE_MODEL));
    }    

    conversation create_conversation(language_model model)
    {
        return create_conversation(option_language_model(model));
    }    

    void conversation_add_message(conversation c, const string& message)
    {
        CONVERSATION_CHECK("conversation_add_message", )

        // end the language model's turn
        if (c->was_generating)
        {
            c->was_generating = false;
            llamacpp::manual_end_message(c->context);
        }

        // tokenize user's prompt and add to context
        llamacpp::llama_tokens tokens = llamacpp::tokenize_string(c->model, llamacpp::format_chat(c->model, {
            {"user", message + c->prompt_append}
        }, true), false);
        llamacpp::add_to_context(c->context, tokens);

        // the model is ready to generate again
        c->is_generating = true;
    }

    void __buffer_next_token(conversation c)
    {
        if (c->next_token.type != llamacpp::token_result::token_type::NONE)
            return; // already buffered

        // attempt to get next token that is non-meta
        do
        {
            // if we reach the end of the message, return even if a meta token (shouldn't happen though)
            if (llamacpp::context_step(c->context, &c->next_token))
            {
                c->is_generating = false;
                return;
            }
        } while (c->next_token.type == llamacpp::token_result::token_type::META);
    }

    // These next three functions buffer the next token so that they can
    // return information about it
    bool conversation_is_replying(conversation c)
    {
        CONVERSATION_CHECK("conversation_is_replying", false)

        __buffer_next_token(c);

        return c->is_generating;
    }

    bool conversation_is_thinking(conversation c)
    {
        CONVERSATION_CHECK("conversation_is_thinking", false)

        __buffer_next_token(c);

        return c->next_token.type == llamacpp::token_result::token_type::THINKING;
    }

    string conversation_get_reply_piece(conversation c)
    {
        CONVERSATION_CHECK("conversation_get_reply_piece", "")

        // if the user wants a token, we can resume generating even if we already finished
        c->is_generating = true;
        c->was_generating = true;

        __buffer_next_token(c);

        // token is consumed
        c->next_token.type = llamacpp::token_result::token_type::NONE;

        return c->next_token.text;
    }

    string conversation_get_reply(conversation conv, bool with_thoughts)
    {
        std::stringstream result;
        string last_piece = "\n";

        while(conversation_is_replying(conv))
        {
            
            // Skip the thinking
            if (conversation_is_thinking(conv) && !with_thoughts)
            {
                conversation_get_reply_piece(conv);
                continue;
            }
            
            string piece = conversation_get_reply_piece(conv);

            // avoid double newlines
            if (piece == "\n" && last_piece == "\n")
                continue;

            if (piece == "\n\n")
                piece = "\n";

            result << piece;
            last_piece = piece;
        }

        return trim(result.str());
    }

    string conversation_get_reply(conversation conv)
    {
        return conversation_get_reply(conv, false);
    }

    void __free_conversation_resource(conversation c)
    {
        llamacpp::delete_context(c->context);
        llamacpp::delete_model(c->model);
    }

    void free_conversation(conversation c)
    {
        CONVERSATION_CHECK("free_conversation", )

        __free_conversation_resource(c);

        for (auto it = objects.begin(); it != objects.end(); it++)
        {
            if (*it == c)
            {
                notify_of_free(c);

                delete *it;

                it = objects.erase(it);
                return;
            }
        }
    }

    void free_all_conversations()
    {
        for (conversation c : objects)
        {
            __free_conversation_resource(c);
        }

        objects.clear();
    }

    // --------------------------------------------------------------

    /**
     * Use this option to choose which language model to use, and initialize its default settings
     *
     * @param  model The language model to use
     *
     * @return       Language model options that will use that model and its default settings.
     */
    language_model_options option_language_model(language_model model)
    {
        if (model < 0 || model >= models.size() || models[model].name == "")
        {
            model = DEFAULT_LANGUAGE_MODEL;
            CLOG(WARNING, "GenAI") << "Invalid model selected, defaulting to '" << models[model].name << "'";
        }

        string home_path = path_from( {path_to_user_home(), ".splashkit", "models"} );

        // test that home_path exists, or create
        try {
            std::error_code ec;
            if (!std::filesystem::exists(home_path)) {
                if (!std::filesystem::create_directories(home_path, ec)) {
                    CLOG(ERROR, "GenAI") << "Unable to create models directory: '" << home_path << "' - " << ec.message();
                }
            }
        } catch (const std::exception& e) {
            CLOG(ERROR, "GenAI") << "Exception while ensuring models directory exists: " << e.what();
        }

        language_model_options options = models[model];
        options.path =  home_path + options.path;
        options.seed = 0;

        return options;
    }

    // --------------------------------------------------------------


    // default model definitions

    const std::array<language_model_options, 26> models = {{
        [0]={}, [1]={}, [2]={}, [3]={},

        [QWEN3_0_6B_BASE] = {
            "Qwen3 0.6B Base",
            "https://huggingface.co/mradermacher/Qwen3-0.6B-Base-GGUF/resolve/main/Qwen3-0.6B-Base.Q8_0.gguf?download=true",
            "Qwen3-0.6B-Base.Q8_0.gguf",
            DEFAULT_MAX_TOKENS_BASE, 0.7, 0.8, 20, 0, 1.5
        },
        [QWEN3_0_6B_INSTRUCT] = {
            "Qwen3 0.6B Instruct",
            "https://huggingface.co/Qwen/Qwen3-0.6B-GGUF/resolve/main/Qwen3-0.6B-Q8_0.gguf?download=true",
            "Qwen3-0.6B-Q8_0.gguf",
            DEFAULT_MAX_TOKENS_INSTRUCT, 0.7, 0.8, 20, 0, 1.5, " /no_think"
        },
        [QWEN3_0_6B_THINKING] = {
            "Qwen3 0.6B Thinking",
            "https://huggingface.co/Qwen/Qwen3-0.6B-GGUF/resolve/main/Qwen3-0.6B-Q8_0.gguf?download=true",
            "Qwen3-0.6B-Q8_0.gguf",
            DEFAULT_MAX_TOKENS_THINKING, 0.6, 0.95, 20, 0, 1.5
        },

        [7]={},

        [QWEN3_1_7B_BASE] = {
            "Qwen3 1.7B Base",
            "https://huggingface.co/mradermacher/Qwen3-1.7B-Base-GGUF/resolve/main/Qwen3-1.7B-Base.Q8_0.gguf?download=true",
            "Qwen3-1.7B-Base.Q8_0.gguf",
            DEFAULT_MAX_TOKENS_BASE, 0.7, 0.8, 20, 0, 1.5
        },
        [QWEN3_1_7B_INSTRUCT] = {
            "Qwen3 1.7B Instruct",
            "https://huggingface.co/Qwen/Qwen3-1.7B-GGUF/resolve/main/Qwen3-1.7B-Q8_0.gguf?download=true",
            "Qwen3-1.7B-Q8_0.gguf",
            DEFAULT_MAX_TOKENS_INSTRUCT, 0.7, 0.8, 20, 0, 1.5, " /no_think"
        },
        [QWEN3_1_7B_THINKING] = {
            "Qwen3 1.7B Thinking",
            "https://huggingface.co/Qwen/Qwen3-1.7B-GGUF/resolve/main/Qwen3-1.7B-Q8_0.gguf?download=true",
            "Qwen3-1.7B-Q8_0.gguf",
            DEFAULT_MAX_TOKENS_THINKING, 0.6, 0.95, 20, 0, 1.5
        },

        [11]={},

        [QWEN3_4B_BASE] = {
            "Qwen3 4B Base",
            "https://huggingface.co/mradermacher/Qwen3-4B-Base-GGUF/resolve/main/Qwen3-4B-Base.Q2_K.gguf?download=true",
            "Qwen3-4B-Base.Q2_K.gguf",
            DEFAULT_MAX_TOKENS_BASE, 0.7, 0.8, 20, 0, 0
        },
        [QWEN3_4B_INSTRUCT] = {
            "Qwen3 4B Instruct",
            "https://huggingface.co/unsloth/Qwen3-4B-Instruct-2507-GGUF/resolve/main/Qwen3-4B-Instruct-2507-UD-Q2_K_XL.gguf?download=true",
            "Qwen3-4B-Instruct-2507-UD-Q2_K_XL.gguf",
            DEFAULT_MAX_TOKENS_INSTRUCT, 0.7, 0.8, 20, 0, 0
        },
        [QWEN3_4B_THINKING] = {
            "Qwen3 4B Thinking",
            "https://huggingface.co/unsloth/Qwen3-4B-Thinking-2507-GGUF/resolve/main/Qwen3-4B-Thinking-2507-UD-Q2_K_XL.gguf?download=true",
            "Qwen3-4B-Thinking-2507-UD-Q2_K_XL.gguf",
            DEFAULT_MAX_TOKENS_THINKING, 0.6, 0.95, 20, 0, 0
        },

        [15]={},

        [GEMMA3_270M_BASE] = {
            "Gemma3 270M Base",
            "https://huggingface.co/ggml-org/gemma-3-270m-GGUF/resolve/main/gemma-3-270m-Q8_0.gguf?download=true",
            "gemma-3-270m-Q8_0.gguf",
            DEFAULT_MAX_TOKENS_BASE, 1.0, 0.95, 64, 0, 0
        },
        [GEMMA3_270M_INSTRUCT] = {
            "Gemma3 270M Instruct",
            "https://huggingface.co/unsloth/gemma-3-270m-it-GGUF/resolve/main/gemma-3-270m-it-Q8_0.gguf?download=true",
            "gemma-3-270m-it-Q8_0.gguf",
            DEFAULT_MAX_TOKENS_INSTRUCT, 1.0, 0.95, 64, 0, 0
        },

        [18]={}, [19]={},

        [GEMMA3_1B_BASE] = {
            "Gemma3 1B Base",
            "https://huggingface.co/mradermacher/gemma-3-1b-pt-GGUF/resolve/main/gemma-3-1b-pt.Q8_0.gguf?download=true",
            "gemma-3-1b-pt.Q8_0.gguf",
            DEFAULT_MAX_TOKENS_BASE, 1.0, 0.95, 64, 0, 0
        },
        [GEMMA3_1B_INSTRUCT] = {
            "Gemma3 1B Instruct",
            "https://huggingface.co/unsloth/gemma-3-1b-it-GGUF/resolve/main/gemma-3-1b-it-Q8_0.gguf?download=true",
            "gemma-3-1b-it-Q8_0.gguf",
            DEFAULT_MAX_TOKENS_INSTRUCT, 1.0, 0.95, 64, 0, 0
        },

        [22]={}, [23]={},

        [GEMMA3_4B_BASE] = {
            "Gemma3 4B Base",
            "https://huggingface.co/mradermacher/gemma-3-4b-pt-GGUF/resolve/main/gemma-3-4b-pt.Q2_K.gguf?download=true",
            "gemma-3-4b-pt.Q2_K.gguf",
            DEFAULT_MAX_TOKENS_BASE, 1.0, 0.95, 64, 0, 0
        },
        [GEMMA3_4B_INSTRUCT] = {
            "Gemma3 4B Instruct",
            "https://huggingface.co/unsloth/gemma-3-4b-it-GGUF/resolve/main/gemma-3-4b-it-UD-IQ3_XXS.gguf?download=true",
            "gemma-3-4b-it-UD-IQ3_XXS.gguf",
            DEFAULT_MAX_TOKENS_INSTRUCT, 1.0, 0.95, 64, 0, 0
        }
    }};
}
