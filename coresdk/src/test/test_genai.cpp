//
//  test_genai.cpp
//  splashkit
//
//  Created by Sean Boettger on 20/12/2025.
//

#include "genai.h"
#include "terminal.h"
#include "utils.h"
#include <vector>
#include <iostream>

using namespace std;
using namespace splashkit_lib;

void run_genai_test()
{
    write("User\n> ");
    string prompt = read_line();

    write("LLM\n> (generating...)");
    string response = generate_reply(QWEN3_0_6B_INSTRUCT, prompt);
    write_line("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\033[K" + response);

    delay(300);

    write_line("-- Press enter to end --");
    read_line();
}
