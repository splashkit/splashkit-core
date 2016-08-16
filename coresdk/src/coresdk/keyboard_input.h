//
//  keyboard_input.hpp
//  splashkit
//
//  Created by Andrew Cain on 16/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef keyboard_input_hpp
#define keyboard_input_hpp

#include <string>
using namespace std;

enum key_code
{
    UNKNOWN_KEY = 0,
    BACKSPACE_KEY = 8,
    TAB_KEY = 9,
    CLEAR_KEY = 12,
    RETURN_KEY = 13,
    PAUSE_KEY = 19,
    ESCAPE_KEY = 27,
    SPACE_KEY = 32,
    EXCLAIM_KEY = 33,
    DOUBLE_QUOTE_KEY = 34,
    HASH_KEY = 35,
    DOLLAR_KEY = 36,
    AMPERSAND_KEY = 38,
    QUOTE_KEY = 39,
    LEFT_PAREN_KEY = 40,
    RIGHT_PAREN_KEY = 41,
    ASTERISK_KEY = 42,
    PLUS_KEY = 43,
    COMMA_KEY = 44,
    MINUS_KEY = 45,
    PERIOD_KEY = 46,
    SLASH_KEY = 47,
    NUM_0_KEY = 48,
    NUM_1_KEY = 49,
    NUM_2_KEY = 50,
    NUM_3_KEY = 51,
    NUM_4_KEY = 52,
    NUM_5_KEY = 53,
    NUM_6_KEY = 54,
    NUM_7_KEY = 55,
    NUM_8_KEY = 56,
    NUM_9_KEY = 57,
    COLON_KEY = 58,
    SEMI_COLON_KEY = 59,
    LESS_KEY = 60,
    EQUALS_KEY = 61,
    GREATER_KEY = 62,
    QUESTION_KEY = 63,
    AT_KEY = 64,
    LEFT_BRACKET_KEY = 91,
    BACKSLASH_KEY = 92,
    RIGHT_BRACKET_KEY = 93,
    CARET_KEY = 94,
    UNDERSCORE_KEY = 95,
    BACKQUOTE_KEY = 96,
    A_KEY = 97,
    B_KEY = 98,
    C_KEY = 99,
    D_KEY = 100,
    E_KEY = 101,
    F_KEY = 102,
    G_KEY = 103,
    H_KEY = 104,
    I_KEY = 105,
    J_KEY = 106,
    K_KEY = 107,
    L_KEY = 108,
    M_KEY = 109,
    N_KEY = 110,
    O_KEY = 111,
    P_KEY = 112,
    Q_KEY = 113,
    R_KEY = 114,
    S_KEY = 115,
    T_KEY = 116,
    U_KEY = 117,
    V_KEY = 118,
    W_KEY = 119,
    X_KEY = 120,
    Y_KEY = 121,
    Z_KEY = 122,
    DELETE_KEY = 127,
    KEY_PAD0 = 256,
    KEY_PAD1 = 257,
    KEY_PAD2 = 258,
    KEY_PAD3 = 259,
    KEY_PAD4 = 260,
    KEY_PAD5 = 261,
    KEY_PAD6 = 262,
    KEY_PAD7 = 263,
    KEY_PAD8 = 264,
    KEY_PAD9 = 265,
    KEY_PAD_PERIOD = 266,
    KEY_PAD_DIVIDE = 267,
    KEY_PAD_MULTIPLY = 268,
    KEY_PAD_MINUS = 269,
    KEY_PAD_PLUS = 270,
    KEY_PAD_ENTER = 271,
    KEY_PAD_EQUALS = 272,
    UP_KEY = 273,
    DOWN_KEY = 274,
    RIGHT_KEY = 275,
    LEFT_KEY = 276,
    INSERT_KEY = 277,
    HOME_KEY = 278,
    END_KEY = 279,
    PAGE_UP_KEY = 280,
    PAGE_DOWN_KEY = 281,
    F1_KEY = 282,
    F2_KEY = 283,
    F3_KEY = 284,
    F4_KEY = 285,
    F5_KEY = 286,
    F6_KEY = 287,
    F7_KEY = 288,
    F8_KEY = 289,
    F9_KEY = 290,
    F10_KEY = 291,
    F11_KEY = 292,
    F12_KEY = 293,
    F13_KEY = 294,
    F14_KEY = 295,
    F15_KEY = 296,
    NUM_LOCK_KEY = 300,
    CAPS_LOCK_KEY = 301,
    SCROLL_LOCK_KEY = 302,
    RIGHT_SHIFT_KEY = 303,
    LEFT_SHIFT_KEY = 304,
    RIGHT_CTRL_KEY = 305,
    LEFT_CTRL_KEY = 306,
    RIGHT_ALT_KEY = 307,
    LEFT_ALT_KEY = 308,
    RIGHT_META_KEY = 309,
    LEFT_META_KEY = 310,
    LEFT_SUPER_KEY = 311,
    RIGHT_SUPER_KEY = 312,
    MODE_KEY = 313,
    HELP_KEY = 315,
    SYS_REQ_KEY = 317,
    MENU_KEY = 319,
    POWER_KEY = 320,
    SHIFT_KEY = 321,
    CTRL_KEY = 322,
    ALT_KEY = 323,
    COMMAND_KEY = 324,
    SUPER_KEY = 325,
    WINDOWS_KEY = 326,
    OPTION_KEY = 327
};

typedef void (key_callback)(key_code code);

/**
 *  Returns true when the key requested is being held down. This is updated
 *  as part of the `process_events` call. Use the key codes from `key_code`
 *  to specify the key to be checked.
 */
bool key_down(key_code key);

/**
 *  Returns true when the key requested is just pressed down. This is updated
 *  as part of the `process_events` call. Use the key codes from `key_code`
 *  to specify the key to be checked. this will only occur once for that key that is
 *  pressed and will not return true again until the key is released and presssed down again
 */
bool key_typed(key_code key);

/**
 *  Returns true if the specified key was released since the last time
 *  `process_events` was called. This occurs only once for the key that is
 *  released and will not return true again until the key is pressed down and
 *  released again.
 */
bool key_released(key_code key);

/**
 *  Checks to see if any key has been pressed since the last time
 *  `process_events` was called.
 */
bool any_key_pressed();

/**
 *  The `key_name` function returns a string name for a given `key_code`. For
 *  example, `COMMA_KEY` returns the string 'Comma'. This function could be used
 *  to display more meaningful key names for configuring game controls, etc.
 */
string key_name(key_code key);

/**
 *  Returns false when the key requested is being held down. This is updated
 *  as part of the `process_events` call. Use the key codes from `key_code`
 *  to specify the key to be checked.
 */
bool key_up(key_code key);

void register_callback_on_key_down(key_callback *callback);

void register_callback_on_key_up(key_callback *callback);

void register_callback_on_key_typed(key_callback *callback);

void deregister_callback_on_key_down(key_callback *callback);

void deregister_callback_on_key_up(key_callback *callback);

void deregister_callback_on_key_typed(key_callback *callback);


#endif /* keyboard_input_hpp */
