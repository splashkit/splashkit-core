//
//  window_manager.cpp
//  splashkit
//
//  Created by Andrew Cain on 15/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "window_manager.h"
#include "graphics_driver.h"
#include "resources.h"
#include "backend_types.h"
#include "utility_functions.h"
#include "input_driver.h"
#include "sk_input_backend.h"

#include <map>

using namespace std;

static window _primary_window = nullptr;
window _current_window = nullptr;
map<string, window> _windows;

window open_window(string caption, int width, int height)
{
    sk_color clr;
    string real_caption;
    int idx;
    window result;
    
    real_caption = caption;
    idx = 0;
    
    while ( has_window(real_caption) )
    {
        real_caption = caption + ": " + std::to_string(idx);
        idx++;
    }
    
    result = new _window_data();
    
    result->id = WINDOW_PTR;
    result->caption = real_caption;
    
    result->image.surface = sk_open_window(caption.c_str(), width, height);
    
    sk_window_position(&result->image.surface, &result->x, &result->y);
    
    result->open = true;
    result->fullscreen = false;
    result->border = true;
    
    result->eventData.close_requested = false;
    result->eventData.has_focus = false;
    result->eventData.mouse_over = false;
    result->eventData.shown = true;
    
    result->screen_rect = { 0, 0, float(width), float(height) };
    
    result->temp_string = "";
    result->max_string_len = 0;
    
//    result->text_bitmap = nullptr;
//    result->cursor_bitmap = nullptr;
//    result->font = nullptr;
//    result->foreColor := RGBAColor(0, 0, 0, 255);
//    result->background_color := RGBAColor(255, 255, 255, 255);
//    result->input_area := RectangleFrom(0,0,0,0);
    
//    result^.readingString := false;
//    result^.textCancelled := false;
    
    clr = { 1.0f, 1.0f, 1.0f, 1.0f };
    sk_clear_drawing_surface(&result->image.surface, clr);
    
    clr = { 0.5f, 0.5f, 0.5f, 1.0f };
//    _sg_functions^.text.draw_text( @result^.image.surface, nil, screenWidth div 2 - 60, screenHeight div 2, 'Getting ready to make a Splash!', clr);
    
    refresh_window(result);
    
    _windows[real_caption] = result;
    
    if ( ! _primary_window)
    {
        _primary_window = result;
        _current_window = result;
    }
    
    return result;
}

void refresh_window(window wind)
{
    if ( INVALID_PTR(wind, WINDOW_PTR))
    {
        raise_warning("Attempting to refresh an invalid window!");
        return;
    }
    
    //TODO: DrawCollectedText(w);
    sk_refresh_window(&wind->image.surface);
}

void clear_window(window wind, color clr)
{
    if ( not VALID_PTR(wind, WINDOW_PTR))
    {
        raise_warning("Attempting to clear an invalid window!");
        return;
    }
    
    sk_clear_drawing_surface(&wind->image.surface, clr);
}

void close_window(window wind)
{
    if ( not VALID_PTR(wind, WINDOW_PTR) )
    {
        raise_warning("Close window called without valid window parameter");
        return;
    }
    
    if ( wind == _current_window )
        _current_window = _primary_window;
    
    if ( wind == _primary_window )
    {
        _sk_quit = true;
        _primary_window = nullptr;
    
        if ( wind == _current_window ) // in case they ignore the quit!
            _current_window = nullptr;
    }
    
    sk_close_drawing_surface(&wind->image.surface);
    wind->id = NONE_PTR;
    _windows.erase(wind->caption);
    delete(wind);
}

void close_window(string name)
{
    close_window(window_named(name));
}

bool has_window(string caption)
{
    return _windows.count(caption) > 0;
}

window window_named(string caption)
{
    if (has_window(caption))
        return _windows[caption];
    else
        return nullptr;
}

