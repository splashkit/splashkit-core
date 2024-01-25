//
// SplashKit Generated Types C++ Code
// DO NOT MODIFY
//

#ifndef __types_h
#define __types_h

#include <string>
#include <vector>
#include <cstdint>
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
    HTTP_STATUS_MOVED_PERMANENTLY = 301,
    HTTP_STATUS_FOUND = 302,
    HTTP_STATUS_SEE_OTHER = 303,
    HTTP_STATUS_BAD_REQUEST = 400,
    HTTP_STATUS_UNAUTHORIZED = 401,
    HTTP_STATUS_FORBIDDEN = 403,
    HTTP_STATUS_NOT_FOUND = 404,
    HTTP_STATUS_METHOD_NOT_ALLOWED = 405,
    HTTP_STATUS_REQUEST_TIMEOUT = 408,
    HTTP_STATUS_CONFLICT = 409,
    HTTP_STATUS_INTERNAL_SERVER_ERROR = 500,
    HTTP_STATUS_NOT_IMPLEMENTED = 501,
    HTTP_STATUS_SERVICE_UNAVAILABLE = 503
} http_status_code;
typedef enum {
    GPIO_INPUT = 0,
    GPIO_OUTPUT = 1,
    GPIO_ALT0 = 4,
    GPIO_ALT1 = 5,
    GPIO_ALT2 = 6,
    GPIO_ALT3 = 7,
    GPIO_ALT4 = 3,
    GPIO_ALT5 = 2,
    GPIO_DEFAULT_MODE = 1
} pin_modes;
typedef enum {
    GPIO_LOW = 0,
    GPIO_HIGH = 1,
    GPIO_DEFAULT_VALUE = 1
} pin_values;
typedef enum {
    PIN_1 = 1,
    PIN_2 = 2,
    PIN_3 = 3,
    PIN_4 = 4,
    PIN_5 = 5,
    PIN_6 = 6,
    PIN_7 = 7,
    PIN_8 = 8,
    PIN_9 = 9,
    PIN_10 = 10,
    PIN_11 = 11,
    PIN_12 = 12,
    PIN_13 = 13,
    PIN_14 = 14,
    PIN_15 = 15,
    PIN_16 = 16,
    PIN_17 = 17,
    PIN_18 = 18,
    PIN_19 = 19,
    PIN_20 = 20,
    PIN_21 = 21,
    PIN_22 = 22,
    PIN_23 = 23,
    PIN_24 = 24,
    PIN_25 = 25,
    PIN_26 = 26,
    PIN_27 = 27,
    PIN_28 = 28,
    PIN_29 = 29,
    PIN_30 = 30,
    PIN_31 = 31,
    PIN_32 = 32,
    PIN_33 = 33,
    PIN_34 = 34,
    PIN_35 = 35,
    PIN_36 = 36,
    PIN_37 = 37,
    PIN_38 = 38,
    PIN_39 = 39,
    PIN_40 = 40
} pins;
typedef enum {
    PUD_OFF = 0,
    PUD_DOWN = 1,
    PUD_UP = 2
} pull_up_down;
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
