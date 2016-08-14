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

sk_input_callbacks _input_callbacks = { nullptr };

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
                    int key_code = static_cast<int>(event.key.keysym.sym);
                    _input_callbacks.handle_key_down(key_code);
                }
                break;
            }

            case SDL_KEYUP:
            {
                if (_input_callbacks.handle_key_up)
                {
                    int key_code = static_cast<int>(event.key.keysym.sym);
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
                if (_input_callbacks.handle_input_text)
                {
                  char* text = event.edit.text;
                  int cursor = event.edit.start;
                  int selection_len = event.edit.length;
                  _input_callbacks.handle_editing_text(text, cursor, selection_len);
                }
                break;
            }
            case SDL_TEXTINPUT:
            {
                if (_input_callbacks.handle_input_text)
                {
                  char* text = event.text.text;
                  _input_callbacks.handle_input_text(text);
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
            window_be = (sk_window_be *)surface->_data;

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
    sk_window_data result = { 0, 0, 0, 0 };

    if ( ! surface || ! surface->_data ) return result;

    switch (surface->kind)
    {
        case SGDS_Window:
        {
            sk_window_be * window_be;
            window_be = (sk_window_be *)surface->_data;

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
            window_be = (sk_window_be *)surface->_data;

            SDL_SetWindowPosition(window_be->window, x, y);

            return;
        }

        default: ;
    }
}

void sk_start_reading_text(float x, float y, float width, float height)
{
    SDL_Rect rect = {
        static_cast<int>(x),
        static_cast<int>(y),
        static_cast<int>(width),
        static_cast<int>(height)
    };
    SDL_SetTextInputRect(&rect);
    SDL_StartTextInput();
}

