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
     * The `conversation` type is used to refer to conversations between the user
     * and a language model. You can use it to send messages to the language model,
     * and stream responses back.
     *
     *
     * All `conversation` objects are:
     *
     *
     *   - created with `create_conversation()`, `create_conversation(language_model model)` or
     *   `create_conversation(language_model_options options)`
     *
     *
     *   - and must be released using `free_conversation()` (to release a specific `conversation` object)
     *   or `free_all_conversation()` (to release all created `conversation` objects).
     *
     *
     * @attribute class conversation
     */
    typedef struct sk_conversation *conversation;

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
     * @brief Creates a new `conversation` object, that uses the default language model.
     *
     * The `conversation` object can have messages added to it, and responses streamed back from it via the other Conversation functions and procedures
     *
     * @returns Returns a new `conversation` object.
     *
     * @attribute class       conversation
     * @attribute constructor true
     */
    conversation create_conversation();

    /**
     * @brief Creates a new `conversation` object, that uses a chosen language model.
     *
     * The `conversation` object can have messages added to it, and responses streamed back from it via the other Conversation functions and procedures
     *
     * @param model The language model to use
     *
     * @returns Returns a new `conversation` object.
     *
     * @attribute class       conversation
     * @attribute constructor true
     *
     * @attribute suffix with_model
     */
    conversation create_conversation(language_model model);

    /**
     * @brief Creates a new `conversation` object, that uses a chosen language model among other options.
     *
     * The `conversation` object can have messages added to it, and responses streamed back from it via the other Conversation functions and procedures
     *
     * @param options The options to use - use this to choose the language model, and change various parameters.
     *
     * @returns Returns a new `conversation` object.
     *
     * @attribute class       conversation
     * @attribute constructor true
     *
     * @attribute suffix with_options
     */
    conversation create_conversation(language_model_options options);

    /**
     * Checks if a language model is currently generating a reply within a `conversation`.
     * If so, you can continue to receive the message with `conversation_get_reply_piece(conversation c)`
     *
     * @param c The `conversation` object to check
     *
     * @returns Returns whether the language model is still generating a reply
     *
     * @attribute class conversation
     * @attribute method is_replying
     * @attribute self c
     */
    bool conversation_is_replying(conversation c);

    /**
     * Checks if a language model is currently "thinking" while generating a reply within a `conversation`.
     * You can use this to filter out the "thoughts" and display them differently (or hide them entirely)
     *
     * @param c The `conversation` object to check
     *
     * @returns Returns whether the language model is currently thinking while generating a reply
     *
     * @attribute class conversation
     * @attribute method is_thinking
     * @attribute self c
     */
    bool conversation_is_thinking(conversation c);

    /**
     * Adds a message to a `conversation`, that the language model will begin replying to.
     * You can receive the reply one piece at a time by calling `conversation_get_reply_piece(conversation c)` in a loop
     *
     * @param c The `conversation` object to check
     * @param message The user message to add to the conversation - the language model will reply to this
     *
     * @attribute class conversation
     * @attribute method add_message
     * @attribute self c
     */
    void conversation_add_message(conversation c, const string& message);

    /**
     * Returns a single piece of a reply (generally one word at a time) from the `conversation`
     * You can use a loop while checking `conversation_is_replying` to retrieve the reply as it generates
     *
     * @param c The `conversation` object to recieve the reply from
     *
     * @returns Returns a small piece of the reply (generally 1 word or less)
     *
     * @attribute class conversation
     * @attribute method get_reply_piece
     * @attribute self c
     */
    string conversation_get_reply_piece(conversation c);

    /**
     * Frees the resources associated with the `conversation` object.
     *
     * @param c The `conversation` object whose resources should be released.
     *
     * @attribute class      conversation
     * @attribute destructor true
     * @attribute self       c
     * @attribute method     free
     */
    void free_conversation(conversation c);

    /**
     * Releases all of the `conversation` objects which have been loaded.
     *
     * @attribute static conversations
     * @attribute method free_all
     */
    void free_all_conversations();

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
