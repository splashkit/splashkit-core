//
//  BackendTypes.hpp
//  splashkit
//
//  Created by Andrew Cain on 14/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef BackendTypes_hpp
#define BackendTypes_hpp

#include "geometry.h"

#include <string>
#include <vector>
using namespace std;

typedef void *pointer;

/// An identifier for the splashkit pointers.
/// Each resource will start with an identifier to
/// Make sure that the dereferenced pointers are likely
/// to refer to the right type of data...
///
/// Convert a string for each to hex: http://www.unit-conversion.info/texttools/hexadecimal/#data
enum pointer_identifier
{
    AUDIO_PTR =     0x41554449, //"AUDI"
    MUSIC_PTR =     0x4d555349, //'MUSI'
    ANIMATION_PTR = 0x414e494d, //'ANIM'
    ANIMATION_SCRIPT_PTR = 0x41534352, //'ASCR';
    BITMAP_PTR =    0x424d502a, //'BMP*';
    SPRITE_PTR =    0x53505254, //'SPRT';
    REGION_PTR =    0x52454749, //'REGI';
    PANEL_PTR =     0x50414e4c, //'PANL';
    ARDUINO_PTR =   0x41524455, //'ARDU';
    TIMER_PTR =     0x54494d52, //'TIMR';
    FONT_PTR =      0x464f4e54, //'FONT';
    WINDOW_PTR =    0x57494e44, //'WIND';
    HTTP_REQUEST_PTR =  0x48524551, //'HREQ';
    HTTP_RESPONSE_PTR = 0x48524553, //'HRES';
    CONNECTION_PTR =    0x434f4e50, //'CONP';
    MESSAGE_PTR =       0x4d534750, //'MSGP';
    SERVER_SOCKET_PTR = 0x53565253, //'SVRS';
    NONE_PTR =          0x4e4f4e45  //'NONE';
};

struct sk_color
{
    float r, g, b, a;
};

//
// A list of the available kinds of drawing surface.
// Drivers must support drawing onto these.
//
enum sk_drawing_surface_kind
{
    SGDS_Unknown = 0,   // Unknown, so do not draw onto this!
    SGDS_Window = 1,    // A window
    SGDS_Bitmap = 2     // A surface, bitmap, or texture
};

//
// A drawing surface is something the user can draw onto.
// The driver is then required to provide the ability to
// perform the requested drawing actions on the different
// kinds of drawing surface.
//
struct sk_drawing_surface
{
    sk_drawing_surface_kind kind;
    int width;
    int height;
    
    // private data used by the backend
    void * _data;
};

enum sk_renderer_flip
{
    sk_FLIP_NONE = 0,
    sk_FLIP_HORIZONTAL = 1,
    sk_FLIP_VERTICAL = 2,
    sk_FLIP_BOTH = 3
};

struct sk_window_data
{
    int close_requested;
    int has_focus;
    int mouse_over;
    int shown;
};

struct image_data
{
    sk_drawing_surface surface;  // The actual bitmap image
    vector<rectangle> clipStack;         // The clipping rectangle history for the bitmap
};

struct _window_data
{
    pointer_identifier  id;
    string              caption;
    image_data          image;
    
    int     x, y;
    
    bool    open;
    bool    fullscreen;
    bool    border;
    
    sk_window_data  eventData;
    
    rectangle   screen_rect;
    
    string temp_string;
    int max_string_len;
    
    //    bitmap  text_bitmap;
    //    bitmap  cursor_bitmap;
    //    font    text_font;
    //    sk_color    fore_color, background_color;
    //    rectangle   input_area; // area for input text
    //    bool        reading_string;
    //    bool        text_cancelled;
};


#endif /* BackendTypes_hpp */
