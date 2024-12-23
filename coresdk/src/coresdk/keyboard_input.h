/**
 * @header keyboard_input
 * @author Andrew Cain
 * @attribute group input
 */

#ifndef keyboard_input_hpp
#define keyboard_input_hpp

#include <algorithm>
#include <string>

using std::string;

namespace splashkit_lib
{
#ifdef HELP_KEY
#undef HELP_KEY
#endif

    /**
     * These are the key codes you can use to check details of keyboard actions.
     * See `key_down`, `key_up`, `key_typed`, and `key_released` functions.
     * You can get a string representation of these keys using `key_name`.
     *
     * @constant UNKNOWN_KEY    The unknown key
     * @constant BACKSPACE_KEY    The backspace key
     * @constant TAB_KEY    The tab key
     * @constant CLEAR_KEY    The clear key
     * @constant RETURN_KEY   The return key
     * @constant PAUSE_KEY    The pause key
     * @constant ESCAPE_KEY   The escape key
     * @constant SPACE_KEY    The space key
     * @constant EXCLAIM_KEY    The exclaim key
     * @constant DOUBLE_QUOTE_KEY   The double quote key
     * @constant HASH_KEY   The hash key
     * @constant DOLLAR_KEY   The dollar key
     * @constant AMPERSAND_KEY    The ampersand key
     * @constant QUOTE_KEY    The quote key
     * @constant LEFT_PAREN_KEY   The left paren key
     * @constant RIGHT_PAREN_KEY    The right paren key
     * @constant ASTERISK_KEY   The asterisk key
     * @constant PLUS_KEY   The plus key
     * @constant COMMA_KEY    The comma key
     * @constant MINUS_KEY    The minus key
     * @constant PERIOD_KEY   The period key
     * @constant SLASH_KEY    The slash key
     * @constant NUM_0_KEY    The num 0 key
     * @constant NUM_1_KEY    The num 1 key
     * @constant NUM_2_KEY    The num 2 key
     * @constant NUM_3_KEY    The num 3 key
     * @constant NUM_4_KEY    The num 4 key
     * @constant NUM_5_KEY    The num 5 key
     * @constant NUM_6_KEY    The num 6 key
     * @constant NUM_7_KEY    The num 7 key
     * @constant NUM_8_KEY    The num 8 key
     * @constant NUM_9_KEY    The num 9 key
     * @constant COLON_KEY    The colon key
     * @constant SEMI_COLON_KEY   The semi colon key
     * @constant LESS_KEY   The less key
     * @constant EQUALS_KEY   The equals key
     * @constant GREATER_KEY    The greater key
     * @constant QUESTION_KEY   The question key
     * @constant AT_KEY   The at key
     * @constant LEFT_BRACKET_KEY   The left bracket key
     * @constant BACKSLASH_KEY    The backslash (\) key
     * @constant RIGHT_BRACKET_KEY    The right bracket key
     * @constant CARET_KEY    The caret (^) key
     * @constant UNDERSCORE_KEY   The underscore (_) key
     * @constant BACKQUOTE_KEY    The backquote (`) key
     * @constant A_KEY    The a key
     * @constant B_KEY    The b key
     * @constant C_KEY    The c key
     * @constant D_KEY    The d key
     * @constant E_KEY    The e key
     * @constant F_KEY    The f key
     * @constant G_KEY    The g key
     * @constant H_KEY    The h key
     * @constant I_KEY    The i key
     * @constant J_KEY    The j key
     * @constant K_KEY    The k key
     * @constant L_KEY    The l key
     * @constant M_KEY    The m key
     * @constant N_KEY    The n key
     * @constant O_KEY    The o key
     * @constant P_KEY    The p key
     * @constant Q_KEY    The q key
     * @constant R_KEY    The r key
     * @constant S_KEY    The s key
     * @constant T_KEY    The t key
     * @constant U_KEY    The u key
     * @constant V_KEY    The v key
     * @constant W_KEY    The w key
     * @constant X_KEY    The x key
     * @constant Y_KEY    The y key
     * @constant Z_KEY    The z key
     * @constant DELETE_KEY   The delete key
     * @constant KEYPAD_0   The keypad 0 key
     * @constant KEYPAD_1   The keypad 1 key
     * @constant KEYPAD_2   The keypad 2 key
     * @constant KEYPAD_3   The keypad 3 key
     * @constant KEYPAD_4   The keypad 4 key
     * @constant KEYPAD_5   The keypad 5 key
     * @constant KEYPAD_6   The keypad 6 key
     * @constant KEYPAD_7   The keypad 7 key
     * @constant KEYPAD_8   The keypad 8 key
     * @constant KEYPAD_9   The keypad 9 key
     * @constant KEYPAD_PERIOD    The keypad period key
     * @constant KEYPAD_DIVIDE    The keypad divide key
     * @constant KEYPAD_MULTIPLY    The keypad multiply key
     * @constant KEYPAD_MINUS   The keypad minus key
     * @constant KEYPAD_PLUS    The keypad plus key
     * @constant KEYPAD_ENTER   The keypad enter key
     * @constant KEYPAD_EQUALS    The keypad equals key
     * @constant UP_KEY   The up key
     * @constant DOWN_KEY   The down key
     * @constant RIGHT_KEY    The right key
     * @constant LEFT_KEY   The left key
     * @constant INSERT_KEY   The insert key
     * @constant HOME_KEY   The home key
     * @constant END_KEY    The end key
     * @constant PAGE_UP_KEY    The page up key
     * @constant PAGE_DOWN_KEY    The page down key
     * @constant F1_KEY   The f1 key
     * @constant F2_KEY   The f2 key
     * @constant F3_KEY   The f3 key
     * @constant F4_KEY   The f4 key
     * @constant F5_KEY   The f5 key
     * @constant F6_KEY   The f6 key
     * @constant F7_KEY   The f7 key
     * @constant F8_KEY   The f8 key
     * @constant F9_KEY   The f9 key
     * @constant F10_KEY    The f10 key
     * @constant F11_KEY    The f11 key
     * @constant F12_KEY    The f12 key
     * @constant F13_KEY    The f13 key
     * @constant F14_KEY    The f14 key
     * @constant F15_KEY    The f15 key
     * @constant NUM_LOCK_KEY   The num lock key
     * @constant CAPS_LOCK_KEY    The caps lock key
     * @constant SCROLL_LOCK_KEY    The scroll lock key
     * @constant RIGHT_SHIFT_KEY    The right shift key
     * @constant LEFT_SHIFT_KEY   The left shift key
     * @constant RIGHT_CTRL_KEY   The right ctrl key
     * @constant LEFT_CTRL_KEY    The left ctrl key
     * @constant RIGHT_ALT_KEY    The right alt or option key
     * @constant LEFT_ALT_KEY   The left alt or option key
     * @constant LEFT_SUPER_KEY   The left super (windows or command) key
     * @constant RIGHT_SUPER_KEY    The right super (windows or command) key
     * @constant MODE_KEY   The mode key
     * @constant HELP_KEY   The help key
     * @constant SYS_REQ_KEY    The sys req key
     * @constant MENU_KEY   The menu key
     * @constant POWER_KEY    The power key
     */
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
        KEYPAD_0 = 256,
        KEYPAD_1 = 257,
        KEYPAD_2 = 258,
        KEYPAD_3 = 259,
        KEYPAD_4 = 260,
        KEYPAD_5 = 261,
        KEYPAD_6 = 262,
        KEYPAD_7 = 263,
        KEYPAD_8 = 264,
        KEYPAD_9 = 265,
        KEYPAD_PERIOD = 266,
        KEYPAD_DIVIDE = 267,
        KEYPAD_MULTIPLY = 268,
        KEYPAD_MINUS = 269,
        KEYPAD_PLUS = 270,
        KEYPAD_ENTER = 271,
        KEYPAD_EQUALS = 272,
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
        LEFT_SUPER_KEY = 311,
        RIGHT_SUPER_KEY = 312,
        MODE_KEY = 313,
        HELP_KEY = 315,
        SYS_REQ_KEY = 317,
        MENU_KEY = 319,
        POWER_KEY = 320,
    };

    /**
     *  The `key_callback` is a function pointer used to register your code with SplashKit
     *  or keyboard related events. See `register_callback_on_key_down`,
     *  `register_callback_on_key_up`, and `register_callback_on_key_typed`
     *
     * @param code The `key_code` related to the event.
     */
    typedef void (key_callback)(int code);

    /**
     *  Returns true when the key requested is being held down. This is updated
     *  as part of the `process_events` call. Use the key codes from `key_code`
     *  to specify the key to be checked.
     *
     * @param  key The key to check if it is down
     * @returns     True if the key is currently held down
     */
    bool key_down(key_code key);

    /**
     *  Returns true when the key requested is just pressed down. This is updated
     *  as part of the `process_events` call. Use the key codes from `key_code`
     *  to specify the key to be checked. this will only occur once for that key that is
     *  pressed and will not return true again until the key is released and presssed down again
     *
     * @param  key The key to check if it was typed
     * @returns     True if the key was just pressed down
     */
    bool key_typed(key_code key);

    /**
     *  Returns true if the specified key was released since the last time
     *  `process_events` was called. This occurs only once for the key that is
     *  released and will not return true again until the key is pressed down and
     *  released again.
     *
     * @param  key The key to check if it was released
     * @returns     True if the key was just released
     */
    bool key_released(key_code key);

    /**
     *  Checks to see if any key has been pressed since the last time
     *  `process_events` was called.
     *
     * @returns True if any key was pressed.
     */
    bool any_key_pressed();

    /**
     *  The `key_name` function returns a string name for a given `key_code`. For
     *  example, `COMMA_KEY` returns the string 'Comma'. This function could be used
     *  to display more meaningful key names for configuring game controls, etc.
     *
     * @param  key The key to get the name of
     * @returns     The name of the key
     */
    string key_name(key_code key);

    /**
     *  Returns false when the key requested is being held down. This is updated
     *  as part of the `process_events` call. Use the key codes from `key_code`
     *  to specify the key to be checked.
     *
     * @param  key The key to check if it is up
     * @returns     True if the key is currently up
     */
    bool key_up(key_code key);

    /**
     *  Register the passed in callback function to receive notification of key down
     *  calls. This will be called in response to `process_events`, for each key that
     *  the user presses down.
     *
     * @param callback The function to be called when a key is first pressed
     */
    void register_callback_on_key_down(key_callback *callback);

    /**
     *  Register the passed in callback function to receive notification of key up
     *  calls. This will be called in response to `process_events`, for each key that
     *  the user releases.
     *
     * @param callback The function to be called when a key is released
     */
    void register_callback_on_key_up(key_callback *callback);

    /**
     *  Register the passed in callback function to receive notification of key typed
     *  calls. This will be called in response to `process_events`, when the user initially
     *  presses a key down.
     *
     * @param callback The function to be called when a key is typed
     */
    void register_callback_on_key_typed(key_callback *callback);

    /**
     *  Remove the registered callback from receiving events related to key down actions.
     *
     * @param callback The function to from from key down events
     */
    void deregister_callback_on_key_down(key_callback *callback);

    /**
     *  Remove the registered callback from receiving events related to key up actions.
     *
     * @param callback The function to from from key up events
     */
    void deregister_callback_on_key_up(key_callback *callback);

    /**
     *  Remove the registered callback from receiving events related to key typed actions.
     *
     * @param callback The function to from from key typed events
     */
    void deregister_callback_on_key_typed(key_callback *callback);

}
#endif /* keyboard_input_hpp */
