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
#include <climits>

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
        cout << "  3: Database" << endl;
        cout << "  4: Geometry" << endl;
        cout << "  5: Graphics" << endl;
        cout << "  6: Input" << endl;
        cout << "  7: Physics" << endl;
        cout << "  8: Resources" << endl;
        cout << "  9: Shape drawing" << endl;
        cout << " 10: Sprite tests" << endl;
        cout << " 11: Text" << endl;
        cout << " 12: Timers" << endl;
        cout << " 13: Web Server" << endl;
        cout << " 14: Windows" << endl;
        cout << " 15: Bundles" << endl;
        cout << "---------------------" << endl;
        cout << " Select test to run: ";

//        cin.ignore(INT_MAX);
        cin >> opt;
        cin.clear();
        cin.ignore(INT_MAX,'\n');

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
                run_geometry_test();
                break;
            case 5:
                run_graphics_test();
                break;
            case 6:
                run_input_test();
                break;
            case 7:
                run_physics_test();
                break;
            case 8:
                run_resources_tests();
                break;
            case 9:
                run_shape_drawing_test();
                break;
            case 10:
                run_sprite_test();
                break;
            case 11:
                run_text_test();
                break;
            case 12:
                run_timer_test();
                break;
            case 13:
                run_web_server_tests();
                break;
            case 14:
                run_windows_tests();
                break;
            case 15:
                run_bundle_test();
                break;
            default:
                break;
        }

        reset_quit();
    } while (opt != -1);
    return 0;
}
