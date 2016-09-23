//
//  audio_test.cpp
//  splashkit
//
//  Created by Andrew Cain on 24/06/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "audio.h"
#include "music.h"
#include "web_client.h"

#include "utils.h"

#include <iostream>
using namespace std;
using namespace splashkit_lib;

void run_audio_tests()
{
    cout << "Starting Audio Tests..." << endl;

    cout << "    Audio should be ready? " << audio_ready() << endl;
    
    cout << "    Closing audio..." << endl;
    close_audio();

    cout << "    Audio should not be ready? " << audio_ready() << endl;

    delay(500);
    
    cout << "    Opening audio..." << endl;
    open_audio();

    cout << "    Is audio ready? " << audio_ready() << endl;
    
    cout << "    Have not loaded a sound yet. Is a sound effect loaded? " << has_sound_effect("test") << endl;

    sound_effect s1 = load_sound_effect("test", "test.ogg");
    
    cout << "    Loaded sound effect. Is there a sound effect loaded? " << has_sound_effect("test") << endl;
    
    cout << "    Downloading sound effect..." << endl;
    download_sound_effect("text message 2", "http://soundbible.com/grab.php?id=2155&type=wav", 80);
    play_sound_effect("text message 2", 2, 0.8);
    delay(5000);
    
    cout << "    Downloading music..." << endl;
    download_music("music", "http://www.royaltyfreemusic.com/music_clips/free/Heartland_1.mp3", 80);
    play_music("music");
    delay(5000);
    
    play_sound_effect(s1, 1, 1.0f);
    
    delay(2000);
    
    cout << "    Playing named sound effect once at full volume" << endl;
    play_sound_effect(sound_effect_named("test"), 1, 1.0f);
    
    
    delay(2000);
    
    cout << "    Playing sound effect twice" << endl;
    play_sound_effect(sound_effect_named("test"), 2);
    
    delay(5000);
    
    cout << "    Playing sound effect" << endl;
    play_sound_effect(sound_effect_named("test"), 1);
    delay(1000);
    cout << "    Stopping sound effect" << endl;
    stop_sound_effect(sound_effect_named("test1"));
    
    sound_effect s2 = load_sound_effect("dancing","dancingFrog.wav");
    cout << "    Fading out sound effect over 2 seconds" << endl;
    play_sound_effect(s2);
    fade_sound_effect_out(s2, 2000);
    delay(3000);
    cout << "    Fading out all sound effects over 5 seconds" << endl;
    play_sound_effect(s2);
    fade_all_sound_effects_out(5000);
    
    delay(6000);
    
    free_sound_effect(s1);

    load_sound_effect("test2", "error.wav");
    load_sound_effect("test3", "30248__streety__sword7.flac");

    free_all_sound_effects();
    
    load_music("dance", "dancingFrog.wav");
    
    cout << "    Playing music..." << endl;
    play_music(music_named("dance"), 1, 1.0f);
    
    delay(5000);
    
    cout << "    Pausing music..." << endl;
    pause_music();
    
    delay(2000);
    
    cout << "    Resuming music..." << endl;
    resume_music();
    
    delay(5000);
    
    cout << "    Stopping music..." << endl;
    stop_music();
    
    delay(2000);
    cout << "    Fading in music over 2 secs..." << endl;
    fade_music_in("dance", 2000);
    delay(5000);
    cout << "    Fading out music over 5 secs..." << endl;
    fade_music_out(5000);
    delay(5000);

    cout << "    Closing audio..." << endl;
    close_audio();

    cout << "    Is audio ready? " << audio_ready() << endl;

    cout << "Audio Tests Ended" << endl;
    delay(5000);
}
