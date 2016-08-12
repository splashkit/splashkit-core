//
//  test_animation.cpp
//  splashkit
//
//  Created by Andrew Cain on 12/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "test_animation.hpp"

#include "animations.h"
#include "images.h"
#include "graphics.h"
#include "window_manager.h"
#include "utils.h"
#include "audio.h"
#include "input.h"

void run_animation_test()
{
    open_audio();
    animation_script kermit = load_animation_script("kermit", "kermit.txt");
    animation anim = create_animation(kermit, "dance");
    
    open_window("Test Animation", 600, 600);
    
    bitmap frog = load_bitmap("frog", "frog.png");
    bitmap_set_cell_details(frog, 73, 105, 4, 4, 16);
    
    for (int i = 0; i < 60 * 20; i++)
    {
        process_events();
        
        clear_screen(COLOR_WHITE);
        
        draw_bitmap(frog, 100, 100, option_with_animation(anim));
        
        update_animation(anim);
        
        refresh_screen();
        
        if (quit_requested() ) break;
    }
    
    free_animation_script(kermit);
    free_bitmap(frog);
    close_window(window_named("Test Animation"));
}