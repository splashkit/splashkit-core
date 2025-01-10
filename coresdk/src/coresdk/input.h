/**
 * @header  input
 * @author  Andrew Cain
 * @brief   Input handles user interaction and events such as keypresses.
 *
 * @attribute group  input
 * @attribute static input
 */

#ifndef input_hpp
#define input_hpp

#include "types.h"
#include "window_manager.h"

#include "text_input.h"
#include "mouse_input.h"
#include "keyboard_input.h"
namespace splashkit_lib
{

    /**
     * ProcessEvents allows SplashKit to react to user interactions. This
     *      procedure checks the current keyboard and mouse states and should be
     *      called once within your game loop to check user interaction.
     *
     * Side Effects
     *      - Reads user interaction events
     *      - Updates keys down, text input, etc.
     */
    void process_events();

    /**
     * Checks to see if the user has asked for the application to quit. This
     * value is updated by the `process_events` routine. Also see
     * `window_close_requested`.
     *
     * @return True if the application has been requested to close.
     */
    bool quit_requested();

    /**
     * Cancels a quit request, ensuring the quit requested will return false.
     */
    void reset_quit();

}
#endif /* input_hpp */
