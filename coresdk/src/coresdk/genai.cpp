//
//  genai.cpp
//  splashkit
//
//  Created by Sean Boettger on 20/12/25.
//

#include "genai_driver.h"
#include "utility_functions.h"

namespace splashkit_lib
{

    string generate_reply(string prompt)
    {
        llamacpp::init();

        string path = path_from( {path_to_user_home(), ".splashkit", "models"} );

        // TODO: add auto download & choices for at least the following
        //"Qwen3-4B-Instruct-2507-UD-Q2_K_XL.gguf"
        //"Qwen3-1.7B-Q8_0.gguf"
        //"Qwen3-0.6B-Q8_0.gguf"
        llamacpp::model model = llamacpp::create_model(path + "Qwen3-4B-Instruct-2507-UD-Q2_K_XL.gguf");

        if (!model.valid) return "";

        std::string formatted = llamacpp::format_chat(model, {
            {"user", prompt}
        });
        llamacpp::llama_tokens tokens = llamacpp::tokenize_string(model, formatted);

        llamacpp::context ctx = llamacpp::start_context(model, tokens, 4096);
        while (!llamacpp::context_step(ctx)){
            // just wait until it completes
            // we could also stream the text to the user through a callback
        };

        std::string result = ctx.ctx_string;

        llamacpp::delete_context(ctx);
        llamacpp::delete_model(model);

        return result;
    }
}
