//
//  test_windows.cpp
//  splashkit
//
//  Created by Andrew Cain on 15/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "window_manager.h"
#include "input.h"
#include "images.h"
#include "graphics.h"
#include "utils.h"
#include "text.h"
#include "web_client.h"
#include "utils.h"

#include <iostream>
using namespace std;
using namespace splashkit_lib;

void run_windows_tests()
{
    window w1 = open_window("Hello World", 800, 600);
    
    display_dialog("Tests", "About to run window tests...", load_font("dialog", "hara.ttf"), 14);
    
    font fnt = load_font("hara", "hara.ttf");
    bitmap light = load_bitmap("light", "on_med.png");
    
    window_set_icon(w1, light);
    
    bitmap test = download_bitmap("blah", "http://www.swinburne.edu.au/cwis/php_pages/webapps/marketing/promotiles-v3/assets/img/RgakQ.jpg", 80);
    
    cout << "Expecting bad bitmap pointer error: " << endl;
    draw_bitmap("fred", 75, 100);
    
    while ( ! quit_requested() )
    {
        process_events();
        
        draw_circle(COLOR_RED, 10, 10, 10);
        fill_circle(COLOR_GREEN, 50, 10, 10);
        
        draw_bitmap(test, 0, 0);
        draw_bitmap(light, 10, 100);
        draw_bitmap("light", 75, 100);
        
        draw_text("Hello World", COLOR_BLUE, fnt, 64, 200, 100);
        
        refresh_screen();
    }
    
    free_bitmap(light);
    close_window(window_named("Hello World"));
    
    delay(500);
}
