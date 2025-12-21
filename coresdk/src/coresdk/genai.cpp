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

#include <filesystem>

using std::to_string;

namespace splashkit_lib
{
    const language_model DEFAULT_LANGUAGE_MODEL = QWEN3_0_6B_INSTRUCT;

    const int default_max_tokens_base = 256; // base has a higher likelihood of running forever for no reason, better to limit it early
    const int default_max_tokens_instruct = 4096;
    const int default_max_tokens_thinking = 4096;

    extern const std::array<language_model_options, 26> models; // defined at end of file

    /* terminal util functions in lieu of ncurses*/
    void terminal_erase_left(int count /* -1 for all */)
    {
        if (count == 0)
            return;

        if (count == -1)
            write("\r\033[K");
        else
            write("\033["+to_string(count)+"D\033[K");
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
            terminal_push(progress_bar + "| (" + to_string(current_mb) + "mb / " + to_string(expected_mb) + "mb)");
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

    string __generate_common(string prompt, language_model_options options, bool format_chat)
    {
        llamacpp::init();

        if (options.url != "" && !ensure_exists_or_download(options.path, options.url, " ::: Downloading Language Model: " + options.name + " |"))
        {
            CLOG(ERROR, "GenAI") << "Failed to download language model - see error above.";
            return "";
        }

        llamacpp::model model = llamacpp::create_model(options.path);

        if (!model.valid) return "";

        std::string formatted = prompt;

        if (format_chat)
        {
            llamacpp::format_chat(model, {
                {
                    "user", prompt + options.prompt_append
                }
            });
        }
        llamacpp::llama_tokens tokens = llamacpp::tokenize_string(model, formatted);

        llamacpp::context ctx = llamacpp::start_context(model, tokens, options.max_tokens);
        while (!llamacpp::context_step(ctx)){
            // just wait until it completes
            // we could also stream the text to the user through a callback
        };

        std::string result = ctx.ctx_string;

        llamacpp::delete_context(ctx);
        llamacpp::delete_model(model);

        return result;
    }


    string generate_reply(string prompt)
    {
        return generate_reply(DEFAULT_LANGUAGE_MODEL, prompt);
    }

    string generate_reply(language_model model, string prompt)
    {
        return generate_reply(prompt, option_language_model(model));
    }

    string generate_reply(string prompt, language_model_options options)
    {
        return __generate_common(prompt, options, true);
    }

    string generate_text(string text)
    {
        return generate_text(DEFAULT_LANGUAGE_MODEL, text);
    }

    string generate_text(language_model model, string text)
    {
        return generate_text(text, option_language_model(model));
    }

    string generate_text(string text, language_model_options options)
    {
        return __generate_common(text, options, false);
    }

    language_model_options option_language_model(language_model model)
    {
        if (model < 0 || model >= models.size() || models[model].name == "")
        {
            model = DEFAULT_LANGUAGE_MODEL;
            CLOG(WARNING, "GenAI") << "Invalid model selected, defaulting to '" << models[model].name << "'";
        }

        string home_path = path_from( {path_to_user_home(), ".splashkit", "models"} );

        language_model_options options = models[model];
        options.path =  home_path + options.path;

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
            default_max_tokens_base, 0.7, 0.8, 20, 0, 1.5
        },
        [QWEN3_0_6B_INSTRUCT] = {
            "Qwen3 0.6B Instruct",
            "https://huggingface.co/Qwen/Qwen3-0.6B-GGUF/resolve/main/Qwen3-0.6B-Q8_0.gguf?download=true",
            "Qwen3-0.6B-Q8_0.gguf",
            default_max_tokens_instruct, 0.7, 0.8, 20, 0, 1.5, " /no_think"
        },
        [QWEN3_0_6B_THINKING] = {
            "Qwen3 0.6B Thinking",
            "https://huggingface.co/Qwen/Qwen3-0.6B-GGUF/resolve/main/Qwen3-0.6B-Q8_0.gguf?download=true",
            "Qwen3-0.6B-Q8_0.gguf",
            default_max_tokens_thinking, 0.6, 0.95, 20, 0, 1.5
        },

        [7]={},

        [QWEN3_1_7B_BASE] = {
            "Qwen3 1.7B Base",
            "https://huggingface.co/mradermacher/Qwen3-1.7B-Base-GGUF/resolve/main/Qwen3-1.7B-Base.Q8_0.gguf?download=true",
            "Qwen3-1.7B-Base.Q8_0.gguf",
            default_max_tokens_base, 0.7, 0.8, 20, 0, 1.5
        },
        [QWEN3_1_7B_INSTRUCT] = {
            "Qwen3 1.7B Instruct",
            "https://huggingface.co/Qwen/Qwen3-1.7B-GGUF/resolve/main/Qwen3-1.7B-Q8_0.gguf?download=true",
            "Qwen3-1.7B-Q8_0.gguf",
            default_max_tokens_instruct, 0.7, 0.8, 20, 0, 1.5, " /no_think"
        },
        [QWEN3_1_7B_THINKING] = {
            "Qwen3 1.7B Thinking",
            "https://huggingface.co/Qwen/Qwen3-1.7B-GGUF/resolve/main/Qwen3-1.7B-Q8_0.gguf?download=true",
            "Qwen3-1.7B-Q8_0.gguf",
            default_max_tokens_thinking, 0.6, 0.95, 20, 0, 1.5
        },

        [11]={},

        [QWEN3_4B_BASE] = {
            "Qwen3 4B Base",
            "https://huggingface.co/mradermacher/Qwen3-4B-Base-GGUF/resolve/main/Qwen3-4B-Base.Q2_K.gguf?download=true",
            "Qwen3-4B-Base.Q2_K.gguf",
            default_max_tokens_base, 0.7, 0.8, 20, 0, 0
        },
        [QWEN3_4B_INSTRUCT] = {
            "Qwen3 4B Instruct",
            "https://huggingface.co/unsloth/Qwen3-4B-Instruct-2507-GGUF/resolve/main/Qwen3-4B-Instruct-2507-UD-Q2_K_XL.gguf?download=true",
            "Qwen3-4B-Instruct-2507-UD-Q2_K_XL.gguf",
            default_max_tokens_instruct, 0.7, 0.8, 20, 0, 0
        },
        [QWEN3_4B_THINKING] = {
            "Qwen3 4B Thinking",
            "https://huggingface.co/unsloth/Qwen3-4B-Thinking-2507-GGUF/resolve/main/Qwen3-4B-Thinking-2507-UD-Q2_K_XL.gguf?download=true",
            "Qwen3-4B-Thinking-2507-UD-Q2_K_XL.gguf",
            default_max_tokens_thinking, 0.6, 0.95, 20, 0, 0
        },

        [15]={},

        [GEMMA3_270M_BASE] = {
            "Gemma3 270M Base",
            "https://huggingface.co/ggml-org/gemma-3-270m-GGUF/resolve/main/gemma-3-270m-Q8_0.gguf?download=true",
            "gemma-3-270m-Q8_0.gguf",
            default_max_tokens_base, 1.0, 0.95, 64, 0, 0
        },
        [GEMMA3_270M_INSTRUCT] = {
            "Gemma3 270M Instruct",
            "https://huggingface.co/unsloth/gemma-3-270m-it-GGUF/resolve/main/gemma-3-270m-it-Q8_0.gguf?download=true",
            "gemma-3-270m-it-Q8_0.gguf",
            default_max_tokens_instruct, 1.0, 0.95, 64, 0, 0
        },

        [18]={}, [19]={},

        [GEMMA3_1B_BASE] = {
            "Gemma3 1B Base",
            "https://huggingface.co/mradermacher/gemma-3-1b-pt-GGUF/resolve/main/gemma-3-1b-pt.Q8_0.gguf?download=true",
            "gemma-3-1b-pt.Q8_0.gguf",
            default_max_tokens_base, 1.0, 0.95, 64, 0, 0
        },
        [GEMMA3_1B_INSTRUCT] = {
            "Gemma3 1B Instruct",
            "https://huggingface.co/unsloth/gemma-3-1b-it-GGUF/resolve/main/gemma-3-1b-it-Q8_0.gguf?download=true",
            "gemma-3-1b-it-Q8_0.gguf",
            default_max_tokens_instruct, 1.0, 0.95, 64, 0, 0
        },

        [22]={}, [23]={},

        [GEMMA3_4B_BASE] = {
            "Gemma3 4B Base",
            "https://huggingface.co/mradermacher/gemma-3-4b-pt-GGUF/resolve/main/gemma-3-4b-pt.Q2_K.gguf?download=true",
            "gemma-3-4b-pt.Q2_K.gguf",
            default_max_tokens_base, 1.0, 0.95, 64, 0, 0
        },
        [GEMMA3_4B_INSTRUCT] = {
            "Gemma3 4B Instruct",
            "https://huggingface.co/unsloth/gemma-3-4b-it-GGUF/resolve/main/gemma-3-4b-it-UD-IQ3_XXS.gguf?download=true",
            "gemma-3-4b-it-UD-IQ3_XXS.gguf",
            default_max_tokens_instruct, 1.0, 0.95, 64, 0, 0
        }
    }};
}
