//
//  input.hpp
//  splashkit
//
//  Created by Andrew Cain on 15/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef input_hpp
#define input_hpp

#include "types.h"
#include "window_manager.h"

#include "text_input.h"
#include "mouse_input.h"
#include "keyboard_input.h"


/// ProcessEvents allows SplashKit to react to user interactions. This
/// procedure checks the current keyboard and mouse states and should be
/// called once within your game loop to check user interaction.
///
/// Side Effects
/// - Reads user interaction events
/// - Updates keys down, text input, etc.
///
/// @lib
void process_events();

/// Checks to see if the user has asked for the application to quit. This value
/// is updated by the `ProcessEvents` routine.
///
/// @returns: True if the application has been requested to close.
///
/// @lib
bool quit_requested();

/// Cancels a quit request, ensuring the quit requested will return false.
///
void reset_quit();


#endif /* input_hpp */
