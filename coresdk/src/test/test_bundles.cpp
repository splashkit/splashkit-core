//
//  test_bundles.cpp
//  splashkit
//
//  Created by Andrew Cain on 29/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "bundles.h"
#include "resources.h"

#include "window_manager.h"
#include "audio.h"
#include "images.h"
#include "timers.h"
#include "text.h"

#include <iostream>
using namespace std;
using namespace splashkit_lib;

void free_notification(void *resource)
{
    cout << "Freeing: " << hex << resource << dec << endl;
}

void run_bundle_test()
{
    register_free_notifier(&free_notification);

    cout << "Before loading:" << endl;
    
    cout << "  Animation:   " << has_animation_script("WalkingScript") << endl;
    cout << "  Bitmap:      " << has_bitmap("FrogBmp") << endl;
    cout << "  Font:        " << has_font("hara") << endl;
    cout << "  Sound:       " << has_sound_effect("error") << endl;
    cout << "  Music:       " << has_music("background") << endl;
    cout << "  Timer:       " << has_timer("my timer") << endl;
    cout << "  Bundle:      " << has_resource_bundle("blah") << endl;
    cout << "  Ufo:         " << has_bitmap("ufo") << endl;
    cout << "  Bundle test: " << has_resource_bundle("test") << endl;
    
    load_resource_bundle("test", "test.txt");

    cout << "After loading:" << endl;
    
    cout << "  Animation:   " << has_animation_script("WalkingScript") << endl;
    cout << "  Bitmap:      " << has_bitmap("FrogBmp") << endl;
    cout << "  Font:        " << has_font("hara") << endl;
    cout << "  Sound:       " << has_sound_effect("error") << endl;
    cout << "  Music:       " << has_music("background") << endl;
    cout << "  Timer:       " << has_timer("my timer") << endl;
    cout << "  Bundle:      " << has_resource_bundle("blah") << endl;
    cout << "  Ufo:         " << has_bitmap("ufo") << endl;
    cout << "  Bundle test: " << has_resource_bundle("test") << endl;

    free_resource_bundle("test");
    
    cout << "After freeing:" << endl;
    
    cout << "  Animation:   " << has_animation_script("WalkingScript") << endl;
    cout << "  Bitmap:      " << has_bitmap("FrogBmp") << endl;
    cout << "  Font:        " << has_font("hara") << endl;
    cout << "  Sound:       " << has_sound_effect("error") << endl;
    cout << "  Music:       " << has_music("background") << endl;
    cout << "  Timer:       " << has_timer("my timer") << endl;
    cout << "  Bundle:      " << has_resource_bundle("blah") << endl;
    cout << "  Ufo:         " << has_bitmap("ufo") << endl;
    cout << "  Bundle test: " << has_resource_bundle("test") << endl;
    
}