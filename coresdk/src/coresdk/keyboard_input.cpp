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

using std::vector;
using std::map;

namespace splashkit_lib
{
    static map<key_code, bool> _keys_down;
    static map<key_code, bool> _keys_just_typed; // i.e. those that have just gone down
    static map<key_code, bool> _keys_released; // i.e. those that have just gone up
    static bool _key_pressed = false;

    static vector<key_callback *> _on_key_down;
    static vector<key_callback *> _on_key_up;
    static vector<key_callback *> _on_key_typed;

    void register_callback_on_key_down(key_callback *callback)
    {
        _on_key_down.push_back(callback);
    }

    void register_callback_on_key_up(key_callback *callback)
    {
        _on_key_up.push_back(callback);
    }

    void register_callback_on_key_typed(key_callback *callback)
    {
        _on_key_typed.push_back(callback);
    }

    void deregister_callback_on_key_down(key_callback *callback)
    {
        _on_key_down.erase(std::remove(_on_key_down.begin(), _on_key_down.end(), callback), _on_key_down.end());
    }

    void deregister_callback_on_key_up(key_callback *callback)
    {
        _on_key_up.erase(std::remove(_on_key_up.begin(), _on_key_up.end(), callback), _on_key_up.end());
    }

    void deregister_callback_on_key_typed(key_callback *callback)
    {
        _on_key_typed.erase(std::remove(_on_key_typed.begin(), _on_key_typed.end(), callback), _on_key_typed.end());
    }

    void _raise_key_event(vector<key_callback *> &list, key_code code)
    {
        for(auto callback: list )
        {
            try {
                callback(code);
            } catch (...) {}
        }
    }

    void _keyboard_start_process_events()
    {
        _key_pressed = false;
        _keys_just_typed.clear();
        _keys_released.clear();
    }

    void _handle_key_up_callback(key_code code)
    {
        key_code keycode = static_cast<key_code>(code);
        _keys_released[keycode] = true;
        _keys_down[keycode] = false;
        _raise_key_event(_on_key_up, keycode);
    }

    void _handle_key_down_callback(key_code code)
    {
        key_code keycode = static_cast<key_code>(code);
        if(not key_down(keycode))
        {
            _keys_down[keycode] = true;
            _keys_just_typed[keycode] = true;
            _raise_key_event(_on_key_typed, keycode);
        }
        _raise_key_event(_on_key_down, keycode);
    }

    bool key_down(key_code key)
    {
        return _keys_down.count(key) > 0 and _keys_down[key];
    }

    bool key_typed(key_code key)
    {
        return _keys_just_typed.count(key) > 0 and _keys_just_typed[key] ;
    }
    
    bool key_released(key_code key)
    {
        return _keys_released.count(key) > 0 and _keys_released[key] ;
    }
    
    bool any_key_pressed()
    {
        return _key_pressed;
    }
    
    string key_name(key_code key)
    {
        return sk_key_name(key);
    }
    
    bool key_up(key_code key)
    {
        return not key_down(key);
    }
}
