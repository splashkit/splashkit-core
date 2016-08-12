//
//  BackendTypes.h
//  splashkit
//
//  Created by Andrew Cain on 14/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef BackendTypes_h
#define BackendTypes_h

#include "drawing_options.h"
#include "geometry.h"
#include "audio.h"
#include "color.h"

#include <string>
#include <vector>
#include <map>
using namespace std;

typedef void *pointer;

/// An identifier for the splashkit pointers.
/// Each resource will start with an identifier to
/// Ensure that the dereferenced pointers are likely
/// to refer to the right type of data...
///
/// Convert a string for each to hex: http://www.unit-conversion.info/texttools/hexadecimal/#data
enum pointer_identifier
{
    DATABASE_PTR =          0x44415442, //'DATB';
    AUDIO_PTR =             0x41554449, //'AUDI';
    MUSIC_PTR =             0x4d555349, //'MUSI';
    ANIMATION_PTR =         0x414e494d, //'ANIM';
    ANIMATION_SCRIPT_PTR =  0x41534352, //'ASCR';
    BITMAP_PTR =            0x424d502a, //'BMP*';
    SPRITE_PTR =            0x53505254, //'SPRT';
    REGION_PTR =            0x52454749, //'REGI';
    PANEL_PTR =             0x50414e4c, //'PANL';
    ARDUINO_PTR =           0x41524455, //'ARDU';
    TIMER_PTR =             0x54494d52, //'TIMR';
    FONT_PTR =              0x464f4e54, //'FONT';
    WINDOW_PTR =            0x57494e44, //'WIND';
    HTTP_REQUEST_PTR =      0x48524551, //'HREQ';
    HTTP_RESPONSE_PTR =     0x48524553, //'HRES';
    CONNECTION_PTR =        0x434f4e50, //'CONP';
    MESSAGE_PTR =           0x4d534750, //'MSGP';
    SERVER_SOCKET_PTR =     0x53565253, //'SVRS';
    NONE_PTR =              0x4e4f4e45  //'NONE';
};

typedef color sk_color;

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
    vector<rectangle> clipStack; // The clipping rectangle history for the bitmap
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

struct _bitmap_data
{
    pointer_identifier  id;
    image_data          image;
    string              filename, name;
    
    //Used for bitmaps that are made up of cells
    int cell_w;      // The width of a cell
    int cell_h;      // The height of a cell
    int cell_cols;   // The columns of cells in the bitmap
    int cell_rows;   // The rows of cells in the bitmap
    int cell_count;  // The total number of cells in the bitmap
    
    bool *pixel_mask;   // Pixel mask used for pixel level collisions
};

enum sk_font_kind
{
    SKFT_UNKNOWN = 0,
    SKFT_TTF = 1
};

struct sk_font_data
{
    sk_font_kind kind;
    
    // private data used by backend
    void * _data;
};

enum sk_http_method
{
    HTTP_GET,
    HTTP_POST,
    HTTP_PUT,
    HTTP_DELETE
};

struct sk_http_request
{
    sk_http_method request_type;
    const char *url;
    unsigned short port;
    const char *body;
    const char *filename;
};

struct sk_http_response
{
    unsigned short status;
    unsigned int size;
    char *data;
};

struct animation_frame
{
    int index;                // The index of the frame in the animation template
    int cell_index;           // Which cell of the current bitmap is drawn
    sound_effect sound;       // Which sound should be played on entry
    float duration;           // How long should this animation frame play for
    vector_2d movement;          // Movement data associated with the frame
    animation_frame *next;    // What is the next frame in this animation
};

struct _animation_data
{
    pointer_identifier id;
    animation_frame *first_frame;       // Where did it start?
    animation_frame *current_frame;     // Where is the animation up to
    animation_frame *last_frame;        // The last frame used, so last image can be drawn
    float frame_time;                   // How long have we spent in this frame?
    bool entered_frame;                 // Did we just enter this frame? (can be used for sound playing)
    animation_script script;            // Which script was it created from?
    string animation_name;              // The name of the animation - when it was started
};

struct _animation_script_data
{
    pointer_identifier id;
    string name;           // The name of the animation template so it can be retrieved from resources
    string filename;       // The filename from which this template was loaded
    
    map<string, int> animation_ids;     // A map that links names to indexes
    vector<string> animation_names;     // The names of the animations
    vector<int> animations;             // The starting index of the animations in this template.
    vector<animation_frame> frames;  // The frames of the animations within this template.
    
    vector<animation>   anim_objs;         // The animations created from this script
};


#endif /* BackendTypes_h */
