//
//  sgBackendTypes.h
//  sgsdl2
//
//  Created by Andrew Cain on 20/11/2013.
//  Copyright (c) 2013 Andrew Cain. All rights reserved.
//

#ifndef sgsdl2_sgBackendTypes_h
#define sgsdl2_sgBackendTypes_h

// Align structs to one byte boundaries
//#pragma pack(push, 8)

#ifdef __cplusplus
extern "C" {
#endif

//
// A list of the available kinds of drawing surface.
// Drivers must support drawing onto these.
//
typedef enum sg_drawing_surface_kind
{
    SGDS_Unknown = 0,   // Unknown, so do not draw onto this!
    SGDS_Window = 1,    // A window
    SGDS_Bitmap = 2     // A surface, bitmap, or texture
} sg_drawing_surface_kind;

//
// A drawing surface is something the user can draw onto.
// The driver is then required to provide the ability to
// perform the requested drawing actions on the different
// kinds of drawing surface.
//
typedef struct sg_drawing_surface
{
    sg_drawing_surface_kind kind;
    int width;
    int height;

    // private data used by the backend
    void * _data;
} sg_drawing_surface;

typedef enum sg_renderer_flip
{
	SG_FLIP_NONE = 0,
	SG_FLIP_HORIZONTAL = 1,
	SG_FLIP_VERTICAL = 2,
	SG_FLIP_BOTH = 3
} sg_renderer_flip;



typedef enum sg_font_kind
{
  SGFT_UNKNOWN = 0,
  SGFT_TTF = 1
} sg_font_kind;

typedef struct sg_font_data
{
  sg_font_kind kind;

  // private data used by backend
  void * _data;
} sg_font_data;




typedef enum sg_connection_kind
{
    SGCK_UNKNOWN = 0,
    SGCK_TCP = 1,
    SGCK_UDP = 2
} sg_connection_kind;

typedef struct sg_network_connection
{
    sg_connection_kind kind;

    // private data used by the backend
    void * _socket;
} sg_network_connection;


typedef void *pointer;

typedef struct sg_window_data
{
    int close_requested;
    int has_focus;
    int mouse_over;
    int shown;
} sg_window_data;

#ifdef __cplusplus
}
#endif

// Stop aligning structs to one byte boundaries
//#pragma pack(pop)

#endif
