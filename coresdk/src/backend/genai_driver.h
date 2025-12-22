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

    namespace llamacpp
    {
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
            llama_batch batch;
            int ctx_size = 0;

            const llama_vocab* vocab;

            int n_pos;
            std::string ctx_string;
        };

        typedef std::vector<llama_token> llama_tokens;

        void init();

        model create_model(std::string path);
        void delete_model(model mdl);

        std::string format_chat(model& mdl, const std::vector<message>& messages);
        llama_tokens tokenize_string(model& mdl, const std::string& prompt);

        context start_context(model& mdl, llama_tokens& starting_context, inference_settings settings);
        int context_step(context& ctx);
        void delete_context(context& ctx);
    }
}

#endif /* defined(graphics_driver) */
