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

#include "types.h"

#include <string>
#include <vector>

using std::string;

namespace splashkit_lib
{

    /**
     * @brief Generates a reply to a textual prompt by a language model
     *
     * The language model will respond to the textual prompt in a chat style format. It will follow instructions and answer questions.
     * Instruct or Thinking models are recommended. Base models likely won't output sensible results.
     *
     * @param prompt The prompt for the language model to reply to.
     *
     * @returns The generated reply.
     */
    string generate_reply(string prompt);

    /**
     * @brief Generates a reply to a textual prompt by a language model
     *
     * The language model will respond to the textual prompt in a chat style format. It will follow instructions and answer questions.
     * Instruct or Thinking models are recommended. Base models likely won't output sensible results.
     *
     * @param model  The language model to use
     * @param prompt The prompt for the language model to reply to.
     *
     * @returns The generated reply.
     *
     * @attribute suffix with_model
     */
    string generate_reply(language_model model, string prompt);

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
    string generate_reply(string prompt, language_model_options options);


    /**
     * @brief Generates text that continues from a prompt
     *
     * The language model will continue predicting text based on patterns in the prompt - it will not directly follow instructions or answer questions.
     * Base models are recommended; Instruct and Thinking models may work.
     *
     * @param text The input text for the language model to continue.
     *
     * @returns The generated reply.
     */
    string generate_text(string text);

    /**
     * @brief Generates text that continues from a prompt
     *
     * The language model will continue predicting text based on patterns in the prompt - it will not directly follow instructions or answer questions.
     * Base models are recommended; Instruct and Thinking models may work.
     *
     * @param model  The language model to use
     * @param text The input text for the language model to continue.
     *
     * @returns The generated reply.
     *
     * @attribute suffix with_model
     */
    string generate_text(language_model model, string text);

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
    string generate_text(string text, language_model_options options);

    /**
     * Use this option to choose which language model to use, and initialize its default settings
     *
     * @param  model The language model to use
     *
     * @return       Language model options that will use that model and its default settings.
     */
    language_model_options option_language_model(language_model model);

}
#endif /* genai_hpp */
