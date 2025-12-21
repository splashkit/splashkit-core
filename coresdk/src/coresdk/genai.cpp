//
//  genai.cpp
//  splashkit
//
//  Created by Sean Boettger on 20/12/25.
//

#include "genai_driver.h"
#include "utility_functions.h"
#include "web_driver.h"
#include "terminal.h"

#include <filesystem>

using std::to_string;

namespace splashkit_lib
{

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
                progress_bar[progress_bar_filled] = spinner[spinner_index++ % spinner.size()];

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

    string generate_reply(string prompt)
    {
        llamacpp::init();

        string path = path_from( {path_to_user_home(), ".splashkit", "models"} );
        path += "Qwen3-4B-Instruct-2507-UD-Q2_K_XL.gguf";

        string model_name = "Qwen3 4B Instruct";

        if (!ensure_exists_or_download(path,
                      "https://huggingface.co/unsloth/Qwen3-4B-Instruct-2507-GGUF/resolve/main/Qwen3-4B-Instruct-2507-UD-Q2_K_XL.gguf?download=true",
                      " ::: Downloading Language Model: "+model_name + " |"
        ))
        {
            CLOG(ERROR, "GenAI") << "Failed to download language model - see error above.";
            return "";
        }

        // TODO: add auto download & choices for at least the following
        //"Qwen3-4B-Instruct-2507-UD-Q2_K_XL.gguf"
        //"Qwen3-1.7B-Q8_0.gguf"
        //"Qwen3-0.6B-Q8_0.gguf"
        llamacpp::model model = llamacpp::create_model(path);

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
