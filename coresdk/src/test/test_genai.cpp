//
//  test_genai.cpp
//  splashkit
//
//  Created by Sean Boettger on 20/12/2025.
//

#include "genai.h"
#include "terminal.h"
#include "basics.h"
#include "utils.h"
#include <vector>
#include <iostream>

using namespace std;
using namespace splashkit_lib;

void run_genai_test()
{
    const string THINKING_STYLE = "\033[37;3m";
    const string RESET_STYLE = "\033[0m";

    conversation conv = create_conversation(QWEN3_1_7B_THINKING);

    while(true)
    {
        write("\n> ");
        string prompt = read_line();

        // See if the user wants to exit
        string exit = trim(generate_reply(QWEN3_1_7B_INSTRUCT, "User A: "+prompt+"\nDoes user A want to end the conversation? Answer with one word, either CONTINUE or END:"));

        write_line("["+exit+"]");

        if (exit == "END")
            break;

        // otherwise continue the conversation
        conversation_add_message(conv, prompt);

        bool thinking = false;
        string last_piece = "\n";
        while(conversation_is_replying(conv))
        {
            if (conversation_is_thinking(conv) != thinking)
            {
                thinking = conversation_is_thinking(conv);

                if (thinking)
                    write(THINKING_STYLE);
                else
                    write(RESET_STYLE);
            }

            string piece = conversation_get_reply_piece(conv);

            // avoid double newlines - ideally this will be filtered on SplashKit's side instead
            if (piece == "\n" && last_piece == "\n")
                continue;

            if (piece == "\n\n")
                piece = "\n";

            write(piece);
            last_piece = piece;
        }

        if (last_piece != "\n")
            write("\n");
    }

    free_conversation(conv);
}
