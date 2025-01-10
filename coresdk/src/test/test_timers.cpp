//
//  test_timers.cpp
//  splashkit
//
//  Created by Andrew Cain on 12/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "window_manager.h"
#include "text.h"
#include "color.h"
#include "input.h"
#include "timers.h"
#include "graphics.h"

using namespace splashkit_lib;
using namespace std;

void run_timer_test()
{
    open_window("Timer Test", 400, 400);
    
    timer t1 = create_timer("timer 1");
    create_timer("timer 2");
    
    start_timer(t1);
    start_timer("Timer 2");
    
    int last = 0;
    
    while( timer_ticks(t1) < 7000)
    {
        clear_screen(COLOR_WHITE);
        if (timer_ticks(t1) / 1000 > last)
        {
            last++;
            if ( timer_paused("timer 2") )
                resume_timer("timer 2");
            else
                pause_timer("timer 2");
        }
        
        draw_text("Timer 1: " + to_string(timer_ticks(t1)), COLOR_NAVY, 40, 30, option_defaults());
        draw_text("Timer 2: " + to_string(timer_ticks("timer 2")), COLOR_NAVY, 40, 80, option_defaults());
        
        refresh_screen();
        process_events();
        if (quit_requested()) break;
    }
    
    close_window("Timer Test");
    free_all_timers();
}