//
//  test_main.cpp
//  splashkit
//
//  Created by Andrew Cain on 24/06/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "input.h"

#include "test_main.h"

#include <iostream>
using namespace std;

int main()
{
    int opt;
    do
    {
        cout << "---------------------" << endl;
        cout << " SplashKit Dev Tests " << endl;
        cout << "---------------------" << endl;
        cout << " -1: Quit" << endl;
        cout << "  1: Animations" << endl;
        cout << "  2: Audio" << endl;
        cout << "  3: Databse" << endl;
        cout << "  4: Graphics" << endl;
        cout << "  5: Input" << endl;
        cout << "  6: Resources" << endl;
        cout << "  7: Shape drawing" << endl;
        cout << "  8: Text" << endl;
        cout << "  9: Timers" << endl;
        cout << " 10: Windows" << endl;
        cout << "---------------------" << endl;
        cout << " Select test to run: ";
        
        cin >> opt;
        
        switch (opt) {
            case 1:
                run_animation_test();
                break;
            case 2:
                run_audio_tests();
                break;
            case 3:
                run_database_tests();
                break;
            case 4:
                run_graphics_test();
                break;
            case 5:
                run_input_test();
                break;
            case 6:
                run_resources_tests();
                break;
            case 7:
                run_shape_drawing_test();
                break;
            case 8:
                run_text_test();
                break;
            case 9:
                run_timer_test();
                break;
            case 10:
                run_windows_tests();
                break;
                
            default:
                break;
        }
        
        reset_quit();
    } while (opt != -1);
    return 0;
}
