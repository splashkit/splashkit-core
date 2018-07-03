//
// SplashKit Generated Types C++ Code
// DO NOT MODIFY
//

#ifndef __types_h
#define __types_h

#include "types.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

struct _animation_data;
typedef struct _animation_data *animation;
struct _animation_script_data;
typedef struct _animation_script_data *animation_script;
struct _bitmap_data;
typedef struct _bitmap_data *bitmap;
struct _display_data;
typedef struct _display_data *display;
struct _font_data;
typedef struct _font_data *font;
typedef enum {
    DRAW_TO_SCREEN,
    DRAW_TO_WORLD,
    DRAW_DEFAULT
} drawing_dest;
typedef enum {
    NORMAL_FONT = 0,
    BOLD_FONT = 1,
    ITALIC_FONT = 2,
    UNDERLINE_FONT = 4
} font_style;
typedef enum {
    HTTP_STATUS_OK = 200,
    HTTP_STATUS_CREATED = 201,
    HTTP_STATUS_NO_CONTENT = 204,
    HTTP_STATUS_BAD_REQUEST = 400,
    HTTP_STATUS_UNAUTHORIZED = 401,
    HTTP_STATUS_FORBIDDEN = 403,
    HTTP_STATUS_NOT_FOUND = 404,
    HTTP_STATUS_METHOD_NOT_ALLOWED = 405,
    HTTP_STATUS_REQUEST_TIMEOUT = 408,
    HTTP_STATUS_INTERNAL_SERVER_ERROR = 500,
    HTTP_STATUS_NOT_IMPLEMENTED = 501,
    HTTP_STATUS_SERVICE_UNAVAILABLE = 503
} http_status_code;
typedef struct {
    double x;
    double y;
} point_2d;
typedef struct {
    point_2d center;
    double radius;
} circle;
typedef struct {
    float r;
    float g;
    float b;
    float a;
} color;
typedef struct {
    double x;
    double y;
    double width;
    double height;
} rectangle;
typedef struct {
    void *dest;
    float scale_x;
    float scale_y;
    float angle;
    float anchor_offset_x;
    float anchor_offset_y;
    bool flip_x;
    bool flip_y;
    bool is_part;
    rectangle part;
    int draw_cell;
    drawing_dest camera;
    int line_width;
    animation anim;
} drawing_options;
typedef struct {
    point_2d start_point;
    point_2d end_point;
} line;
typedef struct {
    point_2d points[4];
} quad;
typedef struct {
    point_2d points[3];
} triangle;
typedef struct {
    double x;
    double y;
} vector_2d;

#endif /* __types_h */
