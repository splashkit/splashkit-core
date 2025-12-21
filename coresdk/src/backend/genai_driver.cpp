//
//  genai_driver.cpp
//  sk
//
//  Created by Sean Boettger on 19/12/2025.
//
#include <iostream>
#include <string.h>
#include <vector>

#include "genai_driver.h"
#include "core_driver.h"
#include "utility_functions.h"

namespace splashkit_lib
{
    namespace llamacpp {

        static void llama_log_callback_null(ggml_log_level level, const char * text, void * user_data){/* nothing, avoid unnecessary logging*/}

        void init()
        {
            static bool initialized = false;
            if (!initialized)
            {
                llama_log_set(llama_log_callback_null, NULL);

                ggml_backend_load_all();

                // Create custom logger with colouring
                el::Configurations conf;
                conf.setToDefault();
                conf.setGlobally(el::ConfigurationType::Format, "%level -> %msg");
                conf.setGlobally(el::ConfigurationType::Filename, "logs/splashkit.log");

                // `el::Loggers::addFlag(el::LoggingFlag::ColoredTerminalOutput);` would be better but has global effect
                conf.set(el::Level::Warning, el::ConfigurationType::Format, "\x1b[33m%level -> %msg\x1b[0m");
                conf.set(el::Level::Error, el::ConfigurationType::Format, "\x1b[31m%level -> %msg\x1b[0m");

                el::Loggers::reconfigureLogger("GenAI", conf);

                initialized = true;
            }
        }

        model create_model(std::string path)
        {
            ggml_backend_load_all();

            // initialize the model
            llama_model_params model_params = llama_model_default_params();
            model_params.n_gpu_layers = 0; // cpu-only

            llama_model * model = llama_model_load_from_file(path.c_str(), model_params);

            if (model == NULL)
            {
                CLOG(ERROR, "GenAI") << "Unable to load language model from " << path << " - it may be corrupted or missing.";
                return {false};
            }

            const llama_vocab * vocab = llama_model_get_vocab(model);
            const char* tmpl = llama_model_chat_template(model, /* name */ nullptr);

            return {
                true,
                model,
                vocab,
                tmpl
            };
        }

        void delete_model(model mdl)
        {
            if (!mdl.valid)
                return;

            if (!mdl.model)
                return;

            llama_model_free(mdl.model);
        }

        std::string format_chat(model& mdl, const std::vector<message>& messages)
        {
            std::vector<llama_chat_message> llama_formatted;
            std::vector<char> formatted(0);

            llama_formatted.reserve(messages.size());

            for (const message& msg : messages)
            {
                llama_formatted.push_back({msg.role.c_str(), msg.content.c_str()});
            }

            int new_len = llama_chat_apply_template(mdl.tmpl, llama_formatted.data(), llama_formatted.size(), true, formatted.data(), formatted.size());
            if (new_len > (int)formatted.size())
            {
                formatted.resize(new_len);
                new_len = llama_chat_apply_template(mdl.tmpl, llama_formatted.data(), llama_formatted.size(), true, formatted.data(), formatted.size());
            }

            return std::string(formatted.begin(), formatted.end());
        }

        llama_tokens tokenize_string(model& mdl, const std::string& prompt)
        {
            // get token count
            // note: returns a negative number, the count of tokens it would have returned if the buffer was large enough
            const int n_prompt = -llama_tokenize(mdl.vocab, prompt.data(), prompt.size(), NULL, 0, true, true);

            // create buffer
            std::vector<llama_token> prompt_tokens(n_prompt);

            // recieve the tokens
            if (llama_tokenize(mdl.vocab, prompt.data(), prompt.size(), prompt_tokens.data(), prompt_tokens.size(), true, true) < 0)
            {
                CLOG(ERROR, "GenAI") << "Failed to tokenize the prompt.";
                return {};
            }

            return prompt_tokens;
        }

        context start_context(model& mdl, llama_tokens& starting_context, int max_length)
        {
            // Create the context
            llama_context_params ctx_params = llama_context_default_params();
            ctx_params.n_ctx = starting_context.size() + max_length - 1;
            ctx_params.n_batch = starting_context.size();
            ctx_params.no_perf = true;

            llama_context * ctx = llama_init_from_model(mdl.model, ctx_params);

            if (ctx == NULL)
            {
                CLOG(ERROR, "GenAI") << "Failed to create the language model context.";
                return {nullptr};
            }

            // Create the sampler
            auto sparams = llama_sampler_chain_default_params();
            sparams.no_perf = true;
            llama_sampler * smpl = llama_sampler_chain_init(sparams);

            // Setup some reasonable defaults
            // TODO: Make these user adjustable
            llama_sampler_chain_add(smpl, llama_sampler_init_min_p(0.00f, 1));
            llama_sampler_chain_add(smpl, llama_sampler_init_temp(0.6f));
            llama_sampler_chain_add(smpl, llama_sampler_init_top_k(20));
            llama_sampler_chain_add(smpl, llama_sampler_init_top_p(0.95, 0));
            //llama_sampler_chain_add(smpl, llama_sampler_init_penalties(64, 1, 0, 0));
            llama_sampler_chain_add(smpl, llama_sampler_init_dist(LLAMA_DEFAULT_SEED));

            // Prepare batch and encode starting context
            llama_batch batch = llama_batch_get_one(starting_context.data(), starting_context.size());

            if (llama_model_has_encoder(mdl.model))
            {
                if (llama_encode(ctx, batch))
                {
                    llama_free(ctx);
                    llama_sampler_free(smpl);
                    CLOG(ERROR, "GenAI") << "Failed to encode prompt.";
                    return {nullptr};
                }

                llama_token decoder_start_token_id = llama_model_decoder_start_token(mdl.model);
                if (decoder_start_token_id == LLAMA_TOKEN_NULL)
                {
                    decoder_start_token_id = llama_vocab_bos(mdl.vocab);
                }

                batch = llama_batch_get_one(&decoder_start_token_id, 1);
            }

            return
            {
                ctx,
                smpl,
                batch,
                (int)ctx_params.n_ctx,
                mdl.vocab,
                0,
                ""
            };
        }

        int context_step(context& ctx)
        {
            if (!ctx.ctx)
                return -1;

            // Decode current batch with the model
            if (llama_decode(ctx.ctx, ctx.batch))
            {
                CLOG(ERROR, "GenAI") << "Failed to process response from language model.";
                return -1;
            }

            ctx.n_pos += ctx.batch.n_tokens;

            // Sample next token
            llama_token new_token_id = llama_sampler_sample(ctx.smpl, ctx.ctx, -1);

            // Has the model finished its response?
            if (llama_vocab_is_eog(ctx.vocab, new_token_id))
                return 1;

            char buf[128];
            int n = llama_token_to_piece(ctx.vocab, new_token_id, buf, sizeof(buf), 0, true);
            if (n < 0)
            {
                CLOG(ERROR, "GenAI") << "Failed to convert response token from language model.";
                return -1;
            }

            std::string s(buf, n);
            ctx.ctx_string += s;

            // prepare the next batch with the sampled token
            ctx.batch = llama_batch_get_one(&new_token_id, 1);

            // Have we reached the end of the context?
            // If so, stop now.
            if (ctx.n_pos + ctx.batch.n_tokens >= ctx.ctx_size)
                return 1;

            return 0;
        }

        void delete_context(context& ctx)
        {
            if (ctx.smpl)
                llama_sampler_free(ctx.smpl);

            if (ctx.ctx)
                llama_free(ctx.ctx);
        }
    }
}
