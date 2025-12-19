/**
 * @header  genai
 * @author  Sean Boettger
 * @brief   SplashKit gives you a simple way to use and embed local AIs in your projects,
 * that run on your own computer.
 *
 * @attribute group  generative_ai
 * @attribute static generative_ai
 */

#ifndef genai_hpp
#define genai_hpp

#include <string>
#include <vector>

using std::string;

namespace splashkit_lib
{

    /**
     * @brief Generates a reply to a textual prompt by a language model
     *
     * The language model will respond to the textual prompt in a chat style format. It will follow instructions and answer questions.
     *
     * @param prompt The prompt for the language model to reply to.
     *
     * @returns The generated reply.
     */
    string generate_reply(string prompt);

}
#endif /* genai_hpp */
