//
//  genai_driver.h
//  sk
//
//  Created by Sean Boettger on 19/12/2025.
//

#ifndef genai_driver_h
#define genai_driver_h

#include "backend_types.h"

#include "llama.h"

namespace splashkit_lib
{
    typedef unsigned int uint;

    /**
     * Language model options allow you to customize the language model used. These should be
     * initialised using functions such as `option_language_model`.
     *
     * @field name             The name of the model (used in diagnostic messages).
     * @field url              A URL to download a model from.
     * @field path             A path to a custom language model (.gguf) file on your computer/a place to download it to.
     * @field max_tokens       The maximum number of tokens to output when replying. One word is approximately two tokens.
     * @field temperature      Increases the likelihood of unlikely tokens to be chosen.
     * @field top_p            Only choose from the top P most likely tokens.
     * @field top_k            Only choose from the top K most likely tokens.
     * @field min_p            Remove tokens less likely than P.
     * @field presence_penalty Penalizes words that have been used once, making them less likely. Can reduce repetition.
     * @field prompt_append    A string to append to prompts automatically.
     * 
     * @attribute class language_model_options
     */
    struct language_model_options
    {
        string name;
        string url;
        string path;
        int max_tokens;
        double temperature;
        double top_p;
        int top_k;
        double min_p;
        double presence_penalty;
        string prompt_append;
        int seed;
    };

    namespace llamacpp
    {
        typedef std::vector<llama_token> llama_tokens;

        struct model
        {
            bool valid;
            llama_model* model;
            const llama_vocab* vocab;
            const char* tmpl;
        };

        struct inference_settings
        {
            double temperature = 0.6;
            double top_p = 0.95;
            int top_k = 20;
            double min_p = 0;
            double presence_penalty = 0;
            int max_length = 256;
            uint32_t seed = 42;
        };

        struct message
        {
            std::string role;
            std::string content;
        };

        struct context
        {
            llama_context* ctx;
            llama_sampler* smpl;
            llama_tokens next_batch;
            int ctx_size = 0;

            const llama_vocab* vocab;
            llama_token newline_token;

            int n_pos;
            llama_tokens total_context;

            bool in_thinking = false;
        };

        struct token_result
        {
            enum token_type {
                NONE,
                CONTENT,
                THINKING,
                META
            };
            string text;
            token_type type;
        };

        void init();

        model create_model(std::string path);
        void delete_model(model mdl);

        std::string format_chat(model& mdl, const std::vector<message>& messages, bool add_assistant);
        llama_tokens tokenize_string(model& mdl, const std::string& prompt, bool is_first);

        context start_context(model& mdl, llama_tokens& starting_context, inference_settings settings);
        void delete_context(context& ctx);

        int context_step(context& ctx, token_result* token);
        void add_to_context(context& ctx, llama_tokens& message);
        void manual_end_message(context& ctx);

        void __print_debug_context(context& ctx);
    }

    struct sk_conversation
    {
        pointer_identifier id;

        llamacpp::model model;
        llamacpp::context context;

        bool was_generating;
        bool is_generating;

        string prompt_append;

        llamacpp::token_result next_token;
    };
}

#endif /* defined(graphics_driver) */
