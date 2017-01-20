//
//  Input_driver.cpp
//
//  Created by Andrew Cain on 7/12/2013.
//  Copyright (c) 2013 Andrew Cain. All rights reserved.
//

#ifdef __linux__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include "backend_types.h"
#include "core_driver.h"
#include "input_driver.h"
#include "graphics_driver.h"
#include "window_manager.h"

namespace splashkit_lib
{
    sk_input_callbacks _input_callbacks = { nullptr };

    bool _sk_quit = false;
    extern map<string, window> _windows;

    map<SDL_Keycode, key_code> _sdl_key_map;
    map<key_code, SDL_Keycode> _sk_key_map;

    void _init_key_maps()
    {
        if ( _sdl_key_map.size() > 0 ) return;

        _sk_key_map[UNKNOWN_KEY] = SDLK_UNKNOWN;
        _sk_key_map[BACKSPACE_KEY] = SDLK_BACKSPACE;
        _sk_key_map[TAB_KEY] = SDLK_TAB;
        _sk_key_map[CLEAR_KEY] = SDLK_CLEAR;
        _sk_key_map[RETURN_KEY] = SDLK_RETURN;
        _sk_key_map[PAUSE_KEY] = SDLK_PAUSE;
        _sk_key_map[ESCAPE_KEY] = SDLK_ESCAPE;
        _sk_key_map[SPACE_KEY] = SDLK_SPACE;
        _sk_key_map[EXCLAIM_KEY] = SDLK_EXCLAIM;
        _sk_key_map[DOUBLE_QUOTE_KEY] = SDLK_QUOTEDBL;
        _sk_key_map[HASH_KEY] = SDLK_HASH;
        _sk_key_map[DOLLAR_KEY] = SDLK_DOLLAR;
        _sk_key_map[AMPERSAND_KEY] = SDLK_AMPERSAND;
        _sk_key_map[QUOTE_KEY] = SDLK_QUOTE;
        _sk_key_map[LEFT_PAREN_KEY] = SDLK_LEFTPAREN;
        _sk_key_map[RIGHT_PAREN_KEY] = SDLK_RIGHTPAREN;
        _sk_key_map[ASTERISK_KEY] = SDLK_ASTERISK;
        _sk_key_map[PLUS_KEY] = SDLK_PLUS;
        _sk_key_map[COMMA_KEY] = SDLK_COMMA;
        _sk_key_map[MINUS_KEY] = SDLK_MINUS;
        _sk_key_map[PERIOD_KEY] = SDLK_PERIOD;
        _sk_key_map[SLASH_KEY] = SDLK_SLASH;
        _sk_key_map[NUM_0_KEY] = SDLK_0;
        _sk_key_map[NUM_1_KEY] = SDLK_1;
        _sk_key_map[NUM_2_KEY] = SDLK_2;
        _sk_key_map[NUM_3_KEY] = SDLK_3;
        _sk_key_map[NUM_4_KEY] = SDLK_4;
        _sk_key_map[NUM_5_KEY] = SDLK_5;
        _sk_key_map[NUM_6_KEY] = SDLK_6;
        _sk_key_map[NUM_7_KEY] = SDLK_7;
        _sk_key_map[NUM_8_KEY] = SDLK_8;
        _sk_key_map[NUM_9_KEY] = SDLK_9;
        _sk_key_map[COLON_KEY] = SDLK_COLON;
        _sk_key_map[SEMI_COLON_KEY] = SDLK_SEMICOLON;
        _sk_key_map[LESS_KEY] = SDLK_LESS;
        _sk_key_map[EQUALS_KEY] = SDLK_EQUALS;
        _sk_key_map[GREATER_KEY] = SDLK_GREATER;
        _sk_key_map[QUESTION_KEY] = SDLK_QUESTION;
        _sk_key_map[AT_KEY] = SDLK_AT;
        _sk_key_map[LEFT_BRACKET_KEY] = SDLK_LEFTBRACKET;
        _sk_key_map[BACKSLASH_KEY] = SDLK_BACKSLASH;
        _sk_key_map[RIGHT_BRACKET_KEY] = SDLK_RIGHTBRACKET;
        _sk_key_map[CARET_KEY] = SDLK_CARET;
        _sk_key_map[UNDERSCORE_KEY] = SDLK_UNDERSCORE;
        _sk_key_map[BACKQUOTE_KEY] = SDLK_BACKQUOTE;
        _sk_key_map[A_KEY] = SDLK_a;
        _sk_key_map[B_KEY] = SDLK_b;
        _sk_key_map[C_KEY] = SDLK_c;
        _sk_key_map[D_KEY] = SDLK_d;
        _sk_key_map[E_KEY] = SDLK_e;
        _sk_key_map[F_KEY] = SDLK_f;
        _sk_key_map[G_KEY] = SDLK_g;
        _sk_key_map[H_KEY] = SDLK_h;
        _sk_key_map[I_KEY] = SDLK_i;
        _sk_key_map[J_KEY] = SDLK_j;
        _sk_key_map[K_KEY] = SDLK_k;
        _sk_key_map[L_KEY] = SDLK_l;
        _sk_key_map[M_KEY] = SDLK_m;
        _sk_key_map[N_KEY] = SDLK_n;
        _sk_key_map[O_KEY] = SDLK_o;
        _sk_key_map[P_KEY] = SDLK_p;
        _sk_key_map[Q_KEY] = SDLK_q;
        _sk_key_map[R_KEY] = SDLK_r;
        _sk_key_map[S_KEY] = SDLK_s;
        _sk_key_map[T_KEY] = SDLK_t;
        _sk_key_map[U_KEY] = SDLK_u;
        _sk_key_map[V_KEY] = SDLK_v;
        _sk_key_map[W_KEY] = SDLK_w;
        _sk_key_map[X_KEY] = SDLK_x;
        _sk_key_map[Y_KEY] = SDLK_y;
        _sk_key_map[Z_KEY] = SDLK_z;
        _sk_key_map[DELETE_KEY] = SDLK_DELETE;
        _sk_key_map[KEYPAD_0] = SDLK_KP_0;
        _sk_key_map[KEYPAD_1] = SDLK_KP_1;
        _sk_key_map[KEYPAD_2] = SDLK_KP_2;
        _sk_key_map[KEYPAD_3] = SDLK_KP_3;
        _sk_key_map[KEYPAD_4] = SDLK_KP_4;
        _sk_key_map[KEYPAD_5] = SDLK_KP_5;
        _sk_key_map[KEYPAD_6] = SDLK_KP_6;
        _sk_key_map[KEYPAD_7] = SDLK_KP_7;
        _sk_key_map[KEYPAD_8] = SDLK_KP_8;
        _sk_key_map[KEYPAD_9] = SDLK_KP_9;
        _sk_key_map[KEYPAD_PERIOD] = SDLK_KP_PERIOD;
        _sk_key_map[KEYPAD_DIVIDE] = SDLK_KP_DIVIDE;
        _sk_key_map[KEYPAD_MULTIPLY] = SDLK_KP_MULTIPLY;
        _sk_key_map[KEYPAD_MINUS] = SDLK_KP_MINUS;
        _sk_key_map[KEYPAD_PLUS] = SDLK_KP_PLUS;
        _sk_key_map[KEYPAD_ENTER] = SDLK_KP_ENTER;
        _sk_key_map[KEYPAD_EQUALS] = SDLK_KP_EQUALS;
        _sk_key_map[UP_KEY] = SDLK_UP;
        _sk_key_map[DOWN_KEY] = SDLK_DOWN;
        _sk_key_map[RIGHT_KEY] = SDLK_RIGHT;
        _sk_key_map[LEFT_KEY] = SDLK_LEFT;
        _sk_key_map[INSERT_KEY] = SDLK_INSERT;
        _sk_key_map[HOME_KEY] = SDLK_HOME;
        _sk_key_map[END_KEY] = SDLK_END;
        _sk_key_map[PAGE_UP_KEY] = SDLK_PAGEUP;
        _sk_key_map[PAGE_DOWN_KEY] = SDLK_PAGEDOWN;
        _sk_key_map[F1_KEY] = SDLK_F1;
        _sk_key_map[F2_KEY] = SDLK_F2;
        _sk_key_map[F3_KEY] = SDLK_F3;
        _sk_key_map[F4_KEY] = SDLK_F4;
        _sk_key_map[F5_KEY] = SDLK_F5;
        _sk_key_map[F6_KEY] = SDLK_F6;
        _sk_key_map[F7_KEY] = SDLK_F7;
        _sk_key_map[F8_KEY] = SDLK_F8;
        _sk_key_map[F9_KEY] = SDLK_F9;
        _sk_key_map[F10_KEY] = SDLK_F10;
        _sk_key_map[F11_KEY] = SDLK_F11;
        _sk_key_map[F12_KEY] = SDLK_F12;
        _sk_key_map[F13_KEY] = SDLK_F13;
        _sk_key_map[F14_KEY] = SDLK_F14;
        _sk_key_map[F15_KEY] = SDLK_F15;
        _sk_key_map[NUM_LOCK_KEY] = SDLK_NUMLOCKCLEAR;
        _sk_key_map[CAPS_LOCK_KEY] = SDLK_CAPSLOCK;
        _sk_key_map[SCROLL_LOCK_KEY] = SDLK_SCROLLLOCK;
        _sk_key_map[RIGHT_SHIFT_KEY] = SDLK_RSHIFT;
        _sk_key_map[LEFT_SHIFT_KEY] = SDLK_LSHIFT;
        _sk_key_map[RIGHT_CTRL_KEY] = SDLK_RCTRL;
        _sk_key_map[LEFT_CTRL_KEY] = SDLK_LCTRL;
        _sk_key_map[RIGHT_ALT_KEY] = SDLK_RALT;
        _sk_key_map[LEFT_ALT_KEY] = SDLK_LALT;
        _sk_key_map[LEFT_SUPER_KEY] = SDLK_LGUI;
        _sk_key_map[RIGHT_SUPER_KEY] = SDLK_RGUI;
        _sk_key_map[MODE_KEY] = SDLK_MODE;
        _sk_key_map[HELP_KEY] = SDLK_HELP;
        _sk_key_map[SYS_REQ_KEY] = SDLK_SYSREQ;
        _sk_key_map[MENU_KEY] = SDLK_MENU;
        _sk_key_map[POWER_KEY] = SDLK_POWER;

        // ----------------------

        _sdl_key_map[SDLK_UNKNOWN] = UNKNOWN_KEY;
        _sdl_key_map[SDLK_BACKSPACE] = BACKSPACE_KEY;
        _sdl_key_map[SDLK_TAB] = TAB_KEY;
        _sdl_key_map[SDLK_CLEAR] = CLEAR_KEY;
        _sdl_key_map[SDLK_RETURN] = RETURN_KEY;
        _sdl_key_map[SDLK_PAUSE] = PAUSE_KEY;
        _sdl_key_map[SDLK_ESCAPE] = ESCAPE_KEY;
        _sdl_key_map[SDLK_SPACE] = SPACE_KEY;
        _sdl_key_map[SDLK_EXCLAIM] = EXCLAIM_KEY;
        _sdl_key_map[SDLK_QUOTEDBL] = DOUBLE_QUOTE_KEY;
        _sdl_key_map[SDLK_HASH] = HASH_KEY;
        _sdl_key_map[SDLK_DOLLAR] = DOLLAR_KEY;
        _sdl_key_map[SDLK_AMPERSAND] = AMPERSAND_KEY;
        _sdl_key_map[SDLK_QUOTE] = QUOTE_KEY;
        _sdl_key_map[SDLK_LEFTPAREN] = LEFT_PAREN_KEY;
        _sdl_key_map[SDLK_RIGHTPAREN] = RIGHT_PAREN_KEY;
        _sdl_key_map[SDLK_ASTERISK] = ASTERISK_KEY;
        _sdl_key_map[SDLK_PLUS] = PLUS_KEY;
        _sdl_key_map[SDLK_COMMA] = COMMA_KEY;
        _sdl_key_map[SDLK_MINUS] = MINUS_KEY;
        _sdl_key_map[SDLK_PERIOD] = PERIOD_KEY;
        _sdl_key_map[SDLK_SLASH] = SLASH_KEY;
        _sdl_key_map[SDLK_0] = NUM_0_KEY;
        _sdl_key_map[SDLK_1] = NUM_1_KEY;
        _sdl_key_map[SDLK_2] = NUM_2_KEY;
        _sdl_key_map[SDLK_3] = NUM_3_KEY;
        _sdl_key_map[SDLK_4] = NUM_4_KEY;
        _sdl_key_map[SDLK_5] = NUM_5_KEY;
        _sdl_key_map[SDLK_6] = NUM_6_KEY;
        _sdl_key_map[SDLK_7] = NUM_7_KEY;
        _sdl_key_map[SDLK_8] = NUM_8_KEY;
        _sdl_key_map[SDLK_9] = NUM_9_KEY;
        _sdl_key_map[SDLK_COLON] = COLON_KEY;
        _sdl_key_map[SDLK_SEMICOLON] = SEMI_COLON_KEY;
        _sdl_key_map[SDLK_LESS] = LESS_KEY;
        _sdl_key_map[SDLK_EQUALS] = EQUALS_KEY;
        _sdl_key_map[SDLK_GREATER] = GREATER_KEY;
        _sdl_key_map[SDLK_QUESTION] = QUESTION_KEY;
        _sdl_key_map[SDLK_AT] = AT_KEY;
        _sdl_key_map[SDLK_LEFTBRACKET] = LEFT_BRACKET_KEY;
        _sdl_key_map[SDLK_BACKSLASH] = BACKSLASH_KEY;
        _sdl_key_map[SDLK_RIGHTBRACKET] = RIGHT_BRACKET_KEY;
        _sdl_key_map[SDLK_CARET] = CARET_KEY;
        _sdl_key_map[SDLK_UNDERSCORE] = UNDERSCORE_KEY;
        _sdl_key_map[SDLK_BACKQUOTE] = BACKQUOTE_KEY;
        _sdl_key_map[SDLK_a] = A_KEY;
        _sdl_key_map[SDLK_b] = B_KEY;
        _sdl_key_map[SDLK_c] = C_KEY;
        _sdl_key_map[SDLK_d] = D_KEY;
        _sdl_key_map[SDLK_e] = E_KEY;
        _sdl_key_map[SDLK_f] = F_KEY;
        _sdl_key_map[SDLK_g] = G_KEY;
        _sdl_key_map[SDLK_h] = H_KEY;
        _sdl_key_map[SDLK_i] = I_KEY;
        _sdl_key_map[SDLK_j] = J_KEY;
        _sdl_key_map[SDLK_k] = K_KEY;
        _sdl_key_map[SDLK_l] = L_KEY;
        _sdl_key_map[SDLK_m] = M_KEY;
        _sdl_key_map[SDLK_n] = N_KEY;
        _sdl_key_map[SDLK_o] = O_KEY;
        _sdl_key_map[SDLK_p] = P_KEY;
        _sdl_key_map[SDLK_q] = Q_KEY;
        _sdl_key_map[SDLK_r] = R_KEY;
        _sdl_key_map[SDLK_s] = S_KEY;
        _sdl_key_map[SDLK_t] = T_KEY;
        _sdl_key_map[SDLK_u] = U_KEY;
        _sdl_key_map[SDLK_v] = V_KEY;
        _sdl_key_map[SDLK_w] = W_KEY;
        _sdl_key_map[SDLK_x] = X_KEY;
        _sdl_key_map[SDLK_y] = Y_KEY;
        _sdl_key_map[SDLK_z] = Z_KEY;
        _sdl_key_map[SDLK_DELETE] = DELETE_KEY;
        _sdl_key_map[SDLK_KP_0] = KEYPAD_0;
        _sdl_key_map[SDLK_KP_1] = KEYPAD_1;
        _sdl_key_map[SDLK_KP_2] = KEYPAD_2;
        _sdl_key_map[SDLK_KP_3] = KEYPAD_3;
        _sdl_key_map[SDLK_KP_4] = KEYPAD_4;
        _sdl_key_map[SDLK_KP_5] = KEYPAD_5;
        _sdl_key_map[SDLK_KP_6] = KEYPAD_6;
        _sdl_key_map[SDLK_KP_7] = KEYPAD_7;
        _sdl_key_map[SDLK_KP_8] = KEYPAD_8;
        _sdl_key_map[SDLK_KP_9] = KEYPAD_9;
        _sdl_key_map[SDLK_KP_PERIOD] = KEYPAD_PERIOD;
        _sdl_key_map[SDLK_KP_DIVIDE] = KEYPAD_DIVIDE;
        _sdl_key_map[SDLK_KP_MULTIPLY] = KEYPAD_MULTIPLY;
        _sdl_key_map[SDLK_KP_MINUS] = KEYPAD_MINUS;
        _sdl_key_map[SDLK_KP_PLUS] = KEYPAD_PLUS;
        _sdl_key_map[SDLK_KP_ENTER] = KEYPAD_ENTER;
        _sdl_key_map[SDLK_KP_EQUALS] = KEYPAD_EQUALS;
        _sdl_key_map[SDLK_UP] = UP_KEY;
        _sdl_key_map[SDLK_DOWN] = DOWN_KEY;
        _sdl_key_map[SDLK_RIGHT] = RIGHT_KEY;
        _sdl_key_map[SDLK_LEFT] = LEFT_KEY;
        _sdl_key_map[SDLK_INSERT] = INSERT_KEY;
        _sdl_key_map[SDLK_HOME] = HOME_KEY;
        _sdl_key_map[SDLK_END] = END_KEY;
        _sdl_key_map[SDLK_PAGEUP] = PAGE_UP_KEY;
        _sdl_key_map[SDLK_PAGEDOWN] = PAGE_DOWN_KEY;
        _sdl_key_map[SDLK_F1] = F1_KEY;
        _sdl_key_map[SDLK_F2] = F2_KEY;
        _sdl_key_map[SDLK_F3] = F3_KEY;
        _sdl_key_map[SDLK_F4] = F4_KEY;
        _sdl_key_map[SDLK_F5] = F5_KEY;
        _sdl_key_map[SDLK_F6] = F6_KEY;
        _sdl_key_map[SDLK_F7] = F7_KEY;
        _sdl_key_map[SDLK_F8] = F8_KEY;
        _sdl_key_map[SDLK_F9] = F9_KEY;
        _sdl_key_map[SDLK_F10] = F10_KEY;
        _sdl_key_map[SDLK_F11] = F11_KEY;
        _sdl_key_map[SDLK_F12] = F12_KEY;
        _sdl_key_map[SDLK_F13] = F13_KEY;
        _sdl_key_map[SDLK_F14] = F14_KEY;
        _sdl_key_map[SDLK_F15] = F15_KEY;
        _sdl_key_map[SDLK_NUMLOCKCLEAR] = NUM_LOCK_KEY;
        _sdl_key_map[SDLK_CAPSLOCK] = CAPS_LOCK_KEY;
        _sdl_key_map[SDLK_SCROLLLOCK] = SCROLL_LOCK_KEY;
        _sdl_key_map[SDLK_RSHIFT] = RIGHT_SHIFT_KEY;
        _sdl_key_map[SDLK_LSHIFT] = LEFT_SHIFT_KEY;
        _sdl_key_map[SDLK_RCTRL] = RIGHT_CTRL_KEY;
        _sdl_key_map[SDLK_LCTRL] = LEFT_CTRL_KEY;
        _sdl_key_map[SDLK_RALT] = RIGHT_ALT_KEY;
        _sdl_key_map[SDLK_LALT] = LEFT_ALT_KEY;
        _sdl_key_map[SDLK_LGUI] = LEFT_SUPER_KEY;
        _sdl_key_map[SDLK_RGUI] = RIGHT_SUPER_KEY;
        _sdl_key_map[SDLK_MODE] = MODE_KEY;
        _sdl_key_map[SDLK_HELP] = HELP_KEY;
        _sdl_key_map[SDLK_SYSREQ] = SYS_REQ_KEY;
        _sdl_key_map[SDLK_MENU] = MENU_KEY;
        _sdl_key_map[SDLK_POWER] = POWER_KEY;
    }

    void _stop_reading_text(window current)
    {
        if ( sk_get_window_event_data(&current->image.surface).has_focus )
        {
            SDL_StopTextInput();
        }
        current->reading_text = false;
    }

    void _handle_key_type(SDL_Keycode code)
    {
        if ( not SDL_IsTextInputActive() ) return;

        window current = window_with_focus();
        if ( not current ) return;

        switch (code)
        {
            case SDLK_BACKSPACE:
            {
                if ( current->composition.size() > 0 )
                    current->composition.pop_back();
                else if ( current->input_text.size() > 0 )
                    current->input_text.pop_back();
                break;
            }

            case SDLK_KP_ENTER:
            case SDLK_RETURN:
            case SDLK_RETURN2:
            {
                _stop_reading_text(current);
                current->cancelled_text_reading = false;
                break;
            }

            case SDLK_c:
            {
#ifdef __APPLE__
                if ( SDL_GetModState() & KMOD_GUI )
#else
                    if (SDL_GetModState() & KMOD_CTRL)
#endif
                    {
                        SDL_SetClipboardText( current->input_text.c_str() );
                    }
                break;
            }

            case SDLK_v:
            {
#ifdef __APPLE__
                if ( SDL_GetModState() & KMOD_GUI )
#else
                    if (SDL_GetModState() & KMOD_CTRL)
#endif
                    {
                        current->input_text += SDL_GetClipboardText( );
                    }
                break;
            }

            case SDLK_ESCAPE:
            {
                _stop_reading_text(current);
                current->cancelled_text_reading = true;
                current->input_text = "";
                break;
            }

            default:
                break;
        }
    }

    void _handle_input_text(char *input)
    {
        window current = window_with_focus();
        if ( not current ) return;

        current->composition = "";
        current->cursor = 0;
        current->input_text += input;
    }

    void _handle_editing_text(char *text, int cursor, int selection_length)
    {
        window current = window_with_focus();
        if ( not current ) return;

        current->composition = string(text);
        current->cursor = cursor;
    }

    void sk_start_reading_text(window wind, double x, double y, double width, double height, string initial_text)
    {
        SDL_Rect rect = {
            static_cast<int>(x),
            static_cast<int>(y),
            static_cast<int>(width),
            static_cast<int>(height)
        };

        wind->composition = "";
        wind->input_text = initial_text;
        wind->cursor = 0;
        wind->input_area = rectangle_from(x, y, width, height);
        wind->reading_text = true;

        if ( sk_get_window_event_data(&wind->image.surface).has_focus )
        {
            SDL_SetTextInputRect(&rect);
            SDL_StartTextInput();
        }
    }

    string sk_end_reading_text()
    {
        window current = current_window();
        if ( not current ) return "";

        _stop_reading_text(current);

        return current->input_text;
    }

    window window_for_window_be(sk_window_be *data)
    {
        for(auto win_itr : _windows)
        {
            window wind = win_itr.second;
            if ( wind->image.surface._data == data ) return wind;
        }

        return nullptr;
    }

    void _handle_new_focus(sk_window_be *data)
    {
        window wind = window_for_window_be(data);

        if ( not wind ) return;

        if ( wind->reading_text )
        {
            SDL_Rect rect;

            rect.x = static_cast<int>(wind->input_area.x);
            rect.y = static_cast<int>(wind->input_area.y);
            rect.w = static_cast<int>(wind->input_area.width);
            rect.h = static_cast<int>(wind->input_area.height);
            SDL_SetTextInputRect(&rect);
            SDL_StartTextInput();
        }
        else
        {
            if ( SDL_IsTextInputActive() )
            {
                SDL_StopTextInput();
            }
        }
    }

    void _sk_handle_window_event(SDL_Event * event)
    {
        sk_window_be *window = _sk_get_window_with_id(event->window.windowID);

        if (! window) {
            return;
        }

        switch (event->window.event)
        {
            case SDL_WINDOWEVENT_SHOWN:
                window->event_data.shown = true;
                //SDL_Log("Window %d shown", event->window.windowID);
                break;
            case SDL_WINDOWEVENT_HIDDEN:
                window->event_data.shown = false;
                //            SDL_Log("Window %d hidden", event->window.windowID);
                break;
            case SDL_WINDOWEVENT_EXPOSED:
                //            SDL_Log("Window %d exposed", event->window.windowID);
                break;
            case SDL_WINDOWEVENT_MOVED:
                //            SDL_Log("Window %d moved to %d,%d",
                //                    event->window.windowID, event->window.data1,
                //                    event->window.data2);
                if (_input_callbacks.handle_window_move)
                {
                    _input_callbacks.handle_window_move(_sk_get_window_with_id(event->window.windowID), event->window.data1, event->window.data2);
                }

                break;
            case SDL_WINDOWEVENT_RESIZED:
                if (_input_callbacks.handle_window_resize)
                {
                    _input_callbacks.handle_window_resize(_sk_get_window_with_id(event->window.windowID), event->window.data1, event->window.data2);
                }

                break;
            case SDL_WINDOWEVENT_MINIMIZED:
                //            SDL_Log("Window %d minimized", event->window.windowID);
                break;
            case SDL_WINDOWEVENT_MAXIMIZED:
                //            SDL_Log("Window %d maximized", event->window.windowID);
                break;
            case SDL_WINDOWEVENT_RESTORED:
                //            SDL_Log("Window %d restored", event->window.windowID);
                break;
            case SDL_WINDOWEVENT_ENTER:
                window->event_data.mouse_over = true;
                //            SDL_Log("Mouse entered window %d",
                //                    event->window.windowID);
                break;
            case SDL_WINDOWEVENT_LEAVE:
                //            SDL_Log("Mouse left window %d", event->window.windowID);
                window->event_data.mouse_over = false;
                break;
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                window->event_data.has_focus = true;
                _handle_new_focus(window);
                if (_input_callbacks.handle_window_gain_focus)
                    _input_callbacks.handle_window_gain_focus(window);
                //            SDL_Log("Window %d gained keyboard focus",
                //                    event->window.windowID);
                break;
            case SDL_WINDOWEVENT_FOCUS_LOST:
                window->event_data.has_focus = false;
                //            SDL_Log("Window %d lost keyboard focus",
                //                    event->window.windowID);
                break;
            case SDL_WINDOWEVENT_CLOSE:
                //            SDL_Log("Window %d closed", event->window.windowID);
                window->event_data.close_requested = true;
                break;
            default:
                //            SDL_Log("Window %d got unknown event %d",
                //                    event->window.windowID, event->window.event);
                break;
        }
    }

    void sk_process_events()
    {
        internal_sk_init();
        SDL_Event event;

        while (SDL_WaitEventTimeout(&event, 0))
        {
            switch ( event.type )
            {
                case SDL_WINDOWEVENT:
                {
                    _sk_handle_window_event(&event);
                    break;
                }

                case SDL_QUIT:
                {
                    // Use callback to inform front end of quit
                    if (_input_callbacks.do_quit)
                    {
                        _input_callbacks.do_quit();
                    }
                    break;
                }

                case SDL_KEYDOWN:
                {
                    if (_input_callbacks.handle_key_down)
                    {
                        key_code key_code = _sdl_key_map[event.key.keysym.sym];
                        _input_callbacks.handle_key_down(key_code);
                    }
                    break;
                }

                case SDL_KEYUP:
                {
                    if (_input_callbacks.handle_key_up)
                    {
                        key_code key_code = _sdl_key_map[event.key.keysym.sym];
                        _handle_key_type(event.key.keysym.sym);
                        _input_callbacks.handle_key_up(key_code);
                    }
                    break;
                }

                case SDL_MOUSEBUTTONUP:
                {
                    if (_input_callbacks.handle_mouse_up)
                    {
                        int mouse_button = event.button.button;
                        _input_callbacks.handle_mouse_up(mouse_button);
                    }
                    break;
                }

                case SDL_MOUSEBUTTONDOWN:
                {
                    if (_input_callbacks.handle_mouse_down)
                    {
                        int mouse_button = event.button.button;
                        _input_callbacks.handle_mouse_down(mouse_button);
                    }
                    break;
                }

                case SDL_MOUSEWHEEL:
                {
                    if (_input_callbacks.handle_mouse_wheel)
                    {
                        _input_callbacks.handle_mouse_wheel(event.wheel.x, event.wheel.y);
                    }
                    break;
                }

                case SDL_TEXTEDITING:
                {
                    if (&_handle_editing_text)
                    {
                        char* text = event.edit.text;
                        int cursor = event.edit.start;
                        int selection_len = event.edit.length;

                        _handle_editing_text(text, cursor, selection_len);
                    }
                    break;
                }

                case SDL_TEXTINPUT:
                {
                    if (&_handle_input_text)
                    {
                        char* text = event.text.text;

                        _handle_input_text(text);
                    }
                    break;
                }
            }
        }
    }

    int sk_window_close_requested(sk_drawing_surface* surf)
    {
        if (surf->kind == SGDS_Window)
        {
            if (static_cast<sk_window_be*>(surf->_data)->event_data.close_requested)
            {
                return -1;
            }
        }
        return 0;
    }
    
    int sk_key_pressed(int key_code)
    {
        internal_sk_init();
        
        const Uint8 *keys;
        int key_scancode = SDL_GetScancodeFromKey(key_code);
        int sz;
        
        keys = SDL_GetKeyboardState(&sz);
        
        if ( (! keys) || sz <= key_scancode ) return 0;
        
        if ( keys[key_scancode] == 1 ) return -1;
        else return 0;
    }
    
    
    
    void sk_start_unicode_text_input(int x, int y, int w, int h)
    {
        internal_sk_init();
        SDL_Rect rect = {x,y,w,h};
        SDL_SetTextInputRect(&rect);
        
        SDL_StartTextInput();
    }
    
    void sk_warp_mouse(sk_drawing_surface *surface, int x, int y)
    {
        if ( ! surface || ! surface->_data ) return;
        
        switch (surface->kind)
        {
            case SGDS_Window:
            {
                sk_window_be * window_be;
                window_be = static_cast<sk_window_be *>(surface->_data);
                
                SDL_WarpMouseInWindow(window_be->window, x, y);
                break;
            }
                
            case SGDS_Bitmap:
                break;
                
            case SGDS_Unknown:
                break;
        }
    }
    
    pointer sk_focus_window()
    {
        internal_sk_init();
        return _sk_get_window_with_pointer(SDL_GetMouseFocus());
    }
    
    void sk_window_position(sk_drawing_surface *surface, int *x, int *y)
    {
        if ( ! surface || ! surface->_data ) return;
        
        switch (surface->kind)
        {
            case SGDS_Window:
            {
                sk_window_be * window_be;
                window_be = static_cast<sk_window_be *>(surface->_data);
                
                SDL_GetWindowPosition(window_be->window, x, y);
                break;
            }
                
            case SGDS_Bitmap:
                break;
                
            case SGDS_Unknown:
                break;
        }
    }
    
    sk_window_data sk_get_window_event_data(sk_drawing_surface *surface)
    {
        sk_window_data result = { true, 0, 0, 0 };
        
        if ( ! surface || ! surface->_data ) return result;
        
        switch (surface->kind)
        {
            case SGDS_Window:
            {
                sk_window_be * window_be;
                window_be = static_cast<sk_window_be *>(surface->_data);
                
                return window_be->event_data;
            }
                
            default:
                return result;
        }
    }
    
    void sk_move_window(sk_drawing_surface *surface, int x, int y)
    {
        if ( ! surface || ! surface->_data ) return;
        
        switch (surface->kind)
        {
            case SGDS_Window:
            {
                sk_window_be * window_be;
                window_be = static_cast<sk_window_be *>(surface->_data);
                
                SDL_SetWindowPosition(window_be->window, x, y);
                
                return;
            }
                
            default: ;
        }
    }
    
    void sk_mouse_position(double &x, double &y)
    {
        int lx = 0, ly = 0;
        
        SDL_GetMouseState(&lx, &ly);
        x = lx;
        y = ly;
    }
    
    void sk_mouse_movement(double &x, double &y)
    {
        int lx = 0, ly = 0;
        
        SDL_GetRelativeMouseState(&lx, &ly);
        x = lx;
        y = ly;
    }
    
    bool sk_mouse_button_down(uint32_t button)
    {
        int state = SDL_GetMouseState(nullptr, nullptr);
        return state & SDL_BUTTON(button);
    }
    
    bool sk_show_mouse(int visible)
    {
        return SDL_ShowCursor(visible ? 1: 0) != 0;
    }
    
    string sk_key_name(key_code key)
    {
        return string(SDL_GetKeyName(_sk_key_map[key]));
    }
}
