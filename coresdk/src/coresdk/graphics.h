//
//  graphics.hpp
//  splashkit
//
//  Created by Andrew Cain on 23/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef graphics_hpp
#define graphics_hpp

/// Refreshes the current drawing on all open windows. This must be called to display
/// anything to the screen. This will show all drawing operations, as well
/// as any text being entered by the user. This will add in delays to limit the framerate
/// to around 60 frames per second.
///
/// Side Effects:
/// - The current drawing is shown on the screen.
void refresh_screen();

/// Refresh with a target FPS. This will delay a period of time that will
/// approximately meet the targetted frames per second.
void refresh_screen(unsigned int target_fps);



#endif /* graphics_hpp */
