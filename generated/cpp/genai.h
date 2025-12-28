//
// SplashKit Generated Genai C++ Code
// DO NOT MODIFY
//

#ifndef __genai_h
#define __genai_h

#include "types.h"
#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
using std::string;
using std::vector;
using std::to_string;

struct _conversation_data;
typedef struct _conversation_data *conversation;
/**
* Adds a message to a `conversation`, that the language model will begin replying to.
* You can receive the reply one piece at a time by calling `conversation_get_reply_piece(conversation c)` in a loop
* @param c The `conversation` object to check
* @param message The user message to add to the conversation - the language model will reply to this
*
*/
void conversation_add_message(conversation c, const string &message);
/**
* Returns a single piece of a reply (generally one word at a time) from the `conversation`
* You can use a loop while checking `conversation_is_replying` to retrieve the reply as it generates
* @param c The `conversation` object to recieve the reply from
* @return Returns a small piece of the reply (generally 1 word or less)
*/
string conversation_get_reply_piece(conversation c);
/**
* Checks if a language model is currently generating a reply within a `conversation`.
* If so, you can continue to receive the message with `conversation_get_reply_piece(conversation c)`
* @param c The `conversation` object to check
* @return Returns whether the language model is still generating a reply
*/
bool conversation_is_replying(conversation c);
/**
* Checks if a language model is currently "thinking" while generating a reply within a `conversation`.
* You can use this to filter out the "thoughts" and display them differently (or hide them entirely)
* @param c The `conversation` object to check
* @return Returns whether the language model is currently thinking while generating a reply
*/
bool conversation_is_thinking(conversation c);
/**
* The `conversation` object can have messages added to it, and responses streamed back from it via the other Conversation functions and procedures
* @param options The options to use - use this to choose the language model, and change various parameters.
* @return Returns a new `conversation` object.
*/
conversation create_conversation(language_model_options options);
/**
* The `conversation` object can have messages added to it, and responses streamed back from it via the other Conversation functions and procedures

* @return Returns a new `conversation` object.
*/
conversation create_conversation();
/**
* The `conversation` object can have messages added to it, and responses streamed back from it via the other Conversation functions and procedures
* @param model The language model to use
* @return Returns a new `conversation` object.
*/
conversation create_conversation(language_model model);
/**
* Releases all of the `conversation` objects which have been loaded.

*
*/
void free_all_conversations();
/**
* Frees the resources associated with the `conversation` object.
* @param c The `conversation` object whose resources should be released.
*
*/
void free_conversation(conversation c);
/**
* The language model will respond to the textual prompt in a chat style format. It will follow instructions and answer questions.
* Instruct or Thinking models are recommended. Base models likely won't output sensible results.
* @param prompt The prompt for the language model to reply to.
* @param options The generation options - use the `option_` functions to create this, for instance `option_language_model`
* @return The generated reply.
*/
string generate_reply(string prompt, language_model_options options);
/**
* The language model will respond to the textual prompt in a chat style format. It will follow instructions and answer questions.
* Instruct or Thinking models are recommended. Base models likely won't output sensible results.
* @param model The language model to use
* @param prompt The prompt for the language model to reply to.
* @return The generated reply.
*/
string generate_reply(language_model model, string prompt);
/**
* The language model will respond to the textual prompt in a chat style format. It will follow instructions and answer questions.
* Instruct or Thinking models are recommended. Base models likely won't output sensible results.
* @param prompt The prompt for the language model to reply to.
* @return The generated reply.
*/
string generate_reply(string prompt);
/**
* The language model will continue predicting text based on patterns in the prompt - it will not directly follow instructions or answer questions.
* Base models are recommended; Instruct and Thinking models may work.
* @param text The input text for the language model to continue.
* @param options The generation options - use the `option_` functions to create this, for instance `option_language_model`
* @return The generated reply.
*/
string generate_text(string text, language_model_options options);
/**
* The language model will continue predicting text based on patterns in the prompt - it will not directly follow instructions or answer questions.
* Base models are recommended; Instruct and Thinking models may work.
* @param model The language model to use
* @param text The input text for the language model to continue.
* @return The generated reply.
*/
string generate_text(language_model model, string text);
/**
* The language model will continue predicting text based on patterns in the prompt - it will not directly follow instructions or answer questions.
* Base models are recommended; Instruct and Thinking models may work.
* @param text The input text for the language model to continue.
* @return The generated reply.
*/
string generate_text(string text);
/**
* Use this option to choose which language model to use, and initialize its default settings
* @param model The language model to use
* @return Language model options that will use that model and its default settings.
*/
language_model_options option_language_model(language_model model);

#endif /* __genai_h */
