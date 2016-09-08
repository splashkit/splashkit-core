//
//  test_animation.cpp
//  splashkit
//
//  Created by Andrew Cain on 12/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "animations.h"
#include "images.h"
#include "graphics.h"
#include "window_manager.h"
#include "utils.h"
#include "audio.h"
#include "input.h"

#include <vector>
#include <iostream>
using namespace std;
using namespace splashkit_lib;

void run_animation_test()
{
    vector<string> sequence = { "Walkfront", "WalkLeft", "WalkRight", "WALKBACK", "dance" };
    
    cout << "Script should not be loaded: " << has_animation_script("kermit");
    
    animation_script kermit = load_animation_script("kermit", "kermit.txt");
    
    cout << "Script should be loaded: " << has_animation_script("kermit");
    
    animation anim = create_animation(kermit, "MoonWalkBack");
    
    open_window("Test Animation", 600, 600);
    
    bitmap frog = load_bitmap("frog", "frog.png");
    bitmap_set_cell_details(frog, 73, 105, 4, 4, 16);
    
    auto it = sequence.begin();
    
    while( not quit_requested() )
    {
        process_events();
        
        clear_screen(COLOR_WHITE);
        
        draw_bitmap(frog, 100, 100, option_with_animation(anim));
        
        update_animation(anim);
        
        if ( animation_ended(anim) )
        {
            if ( it == sequence.end() ) break;
            
            assign_animation(anim, kermit, *it);
            
            it++;
        }
        
        refresh_screen();
        
        if (quit_requested() ) break;
    }
    
    free_animation_script(kermit);
    free_bitmap(frog);
    close_window(window_named("Test Animation"));
}