//
// SplashKit Generated Genai C++ Code
// DO NOT MODIFY
//

#ifndef __genai_h
#define __genai_h

#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
using std::string;
using std::vector;

struct _conversation_data;
typedef struct _conversation_data *conversation;
typedef enum {
    QWEN3_0_6B_BASE = 4,
    QWEN3_0_6B_INSTRUCT = 5,
    QWEN3_0_6B_THINKING = 6,
    QWEN3_1_7B_BASE = 8,
    QWEN3_1_7B_INSTRUCT = 9,
    QWEN3_1_7B_THINKING = 10,
    QWEN3_4B_BASE = 12,
    QWEN3_4B_INSTRUCT = 13,
    QWEN3_4B_THINKING = 14,
    GEMMA3_270M_BASE = 16,
    GEMMA3_270M_INSTRUCT = 17,
    GEMMA3_1B_BASE = 20,
    GEMMA3_1B_INSTRUCT = 21,
    GEMMA3_4B_BASE = 24,
    GEMMA3_4B_INSTRUCT = 25
} language_model;
/**
* Adds a message to a `conversation`, that the language model will begin replying to.
* You can receive the reply one piece at a time by calling `conversation_get_reply_piece(conversation c)` in a loop
* @param c The `conversation` object to check
* @param message The user message to add to the conversation - the language model will reply to this
*
*/
void conversation_add_message(conversation c, const string &message);
/**
* Returns a reply from a `conversation`, without any related thoughts.
* @param conv The `conversation` to recieve the reply from
* @return The response from the model
*/
string conversation_get_reply(conversation conv);
/**
* Returns a reply from a `conversation`, with the ability to indicate if thoughts should be included.
* @param conv The `conversation` to recieve the reply from
* @param with_thoughts A boolean to indicate if thoughts should be included in the reply
* @return The response from the model
*/
string conversation_get_reply(conversation conv, bool with_thoughts);
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
* Creates a new `conversation` object, that uses the default language model.
* 
* The `conversation` object can have messages added to it, and responses streamed back from it via the other Conversation functions and procedures

* @return Returns a new `conversation` object.
*/
conversation create_conversation();
/**
* Creates a new `conversation` object, that uses a chosen language model.
* 
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
* Generates a reply to a textual prompt by a language model
* 
* The language model will respond to the textual prompt in a chat style format. It will follow instructions and answer questions.
* Instruct or Thinking models are recommended. Base models likely won't output sensible results.
* @param model The language model to use
* @param prompt The prompt for the language model to reply to.
* @return The generated reply.
*/
string generate_reply(language_model model, string prompt);
/**
* Generates a reply to a textual prompt by a language model
* 
* The language model will respond to the textual prompt in a chat style format. It will follow instructions and answer questions.
* Instruct or Thinking models are recommended. Base models likely won't output sensible results.
* @param prompt The prompt for the language model to reply to.
* @return The generated reply.
*/
string generate_reply(string prompt);
/**
* Generates text that continues from a prompt, with a maximum of 125 tokens.
* 
* The language model will continue predicting text based on patterns in the prompt - it will not directly follow instructions or answer questions.
* Base models are recommended; Instruct and Thinking models may work.
* @param model The language model to use
* @param text The input text for the language model to continue.
* @return The generated reply.
*/
string generate_text(language_model model, string text);
/**
* Generates text that continues from a prompt, with a maximum of 125 tokens.
* 
* The language model will continue predicting text based on patterns in the prompt - it will not directly follow instructions or answer questions.
* Base models are recommended; Instruct and Thinking models may work.
* @param model The language model to use
* @param text The input text for the language model to continue.
* @param max_tokens The maximum tokens used in response - determining the length of the output and the time taken. Keep this small for reasonable execution times.
* @return The generated reply.
*/
string generate_text(language_model model, string text, int max_tokens);
/**
* Generates text that continues from a prompt - with default of 125 tokens.
* 
* The language model will continue predicting text based on patterns in the prompt - it will not directly follow instructions or answer questions.
* Base models are recommended; Instruct and Thinking models may work.
* @param text The input text for the language model to continue.
* @return The generated reply.
*/
string generate_text(string text);
/**
* Generates text that continues from a prompt.
* 
* The language model will continue predicting text based on patterns in the prompt - it will not directly follow instructions or answer questions.
* Base models are recommended; Instruct and Thinking models may work.
* @param text The input text for the language model to continue.
* @param max_tokens The maximum tokens used in response - determining the length of the output and the time taken. Keep this small for reasonable execution times.
* @return The generated reply.
*/
string generate_text(string text, int max_tokens);

#endif /* __genai_h */
