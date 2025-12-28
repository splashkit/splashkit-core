//
// SplashKit Generated Input C++ Code
// DO NOT MODIFY
//

#ifndef __input_h
#define __input_h

#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
using std::string;
using std::vector;
using std::to_string;

/**
* ProcessEvents allows SplashKit to react to user interactions. This
* procedure checks the current keyboard and mouse states and should be
* called once within your game loop to check user interaction.
* 
* Side Effects
* - Reads user interaction events
* - Updates keys down, text input, etc.

*
*/
void process_events();
/**
* Checks to see if the user has asked for the application to quit. This
* value is updated by the `process_events` routine. Also see
* `window_close_requested`.

* @return True if the application has been requested to close.
*/
bool quit_requested();
/**
* Cancels a quit request, ensuring the quit requested will return false.

*
*/
void reset_quit();

#endif /* __input_h */
