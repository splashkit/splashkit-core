//
//  keyboard_input.cpp
//  splashkit
//
//  Created by Andrew Cain on 16/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "keyboard_input.h"

#include "input_driver.h"
#include "utility_functions.h"

#include <vector>
#include <map>
using namespace std;

struct key_down_data
{
    int code;
    int keyChar;
};

static vector<key_down_data> _keys_down;
static vector<int> _keys_just_typed; // i.e. those that have just gone down
static vector<int> _keys_released; // i.e. those that have just gone down
bool _key_pressed = false;

void _handle_key_up_callback(int code)
{
//    cout << "key up: " << code << endl;
}
