//
//  audio_test.cpp
//  splashkit
//
//  Created by Andrew Cain on 24/06/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "audio.h"

#include "audio_test.hpp"

#include "utils.h"

#include <iostream>
using namespace std;

void run_audio_tests()
{
    cout << "Starting Audio Tests..." << endl;

    cout << "    Is audio ready? " << audio_ready() << endl;

    cout << "    Opening audio..." << endl;
    open_audio();

    cout << "    Is audio ready? " << audio_ready() << endl;

    sound_effect s1 = load_sound_effect("test", "test.ogg");

    play_sound_effect(s1, 1, 1.0f);

    delay(500);

    play_sound_effect(sound_effect_named("test"), 1, 1.0f);
    
    sk_delay(5000);

    free_sound_effect(s1);

    load_sound_effect("test2", "error.wav");
    load_sound_effect("test3", "30248__streety__sword7.flac");

    free_all_sound_effects();

    cout << "    Closing audio..." << endl;
    close_audio();

    cout << "    Is audio ready? " << audio_ready() << endl;

    cout << "Audio Tests Ended" << endl;
}
