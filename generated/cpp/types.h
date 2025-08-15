//
// SplashKit Generated Types C++ Code
// DO NOT MODIFY
//

#ifndef __types_h
#define __types_h

#include <string>
#include <vector>
#include <cmath>
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
    ADC_PIN_0 = 0,
    ADC_PIN_1 = 1,
    ADC_PIN_2 = 2,
    ADC_PIN_3 = 3,
    ADC_PIN_4 = 4,
    ADC_PIN_5 = 5,
    ADC_PIN_6 = 6,
    ADC_PIN_7 = 7
} adc_pin;
typedef enum {
    ADS7830 = 0
} adc_type;
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
} gpio_pin;
typedef enum {
    GPIO_INPUT = 0,
    GPIO_OUTPUT = 1,
    GPIO_ALT0 = 4,
    GPIO_ALT1 = 5,
    GPIO_ALT2 = 6,
    GPIO_ALT3 = 7,
    GPIO_ALT4 = 3,
    GPIO_ALT5 = 2,
    GPIO_DEFAULT_MODE = -1
} gpio_pin_mode;
typedef enum {
    GPIO_DEFAULT_VALUE = -1,
    GPIO_LOW = 0,
    GPIO_HIGH = 1
} gpio_pin_value;
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
    FLAT_DARK_STYLE = 0,
    SHADED_DARK_STYLE = 1,
    FLAT_LIGHT_STYLE = 2,
    SHADED_LIGHT_STYLE = 3,
    BUBBLE = 4,
    BUBBLE_MULTICOLORED = 5
} interface_style;
typedef enum {
    MOTOR_FORWARD,
    MOTOR_BACKWARD
} motor_direction;
typedef enum {
    L298N = 0
} motor_driver_type;
typedef enum {
    PUD_OFF = 0,
    PUD_DOWN = 1,
    PUD_UP = 2
} pull_up_down;
typedef struct {
    double x;
    double y;
} point_2d;

inline bool operator==(const point_2d& lhs, const point_2d& rhs) {
    return
        lhs.x == rhs.x &&
        lhs.y == rhs.y;
}

inline bool operator!=(const point_2d& lhs, const point_2d& rhs) {
    return !(lhs == rhs);
}

typedef struct {
    point_2d center;
    double radius;
} circle;

inline bool operator==(const circle& lhs, const circle& rhs) {
    return
        lhs.center == rhs.center &&
        lhs.radius == rhs.radius;
}

inline bool operator!=(const circle& lhs, const circle& rhs) {
    return !(lhs == rhs);
}

typedef struct {
    float r;
    float g;
    float b;
    float a;
} color;

inline bool operator==(const color& lhs, const color& rhs) {
    return
        std::abs(lhs.r - rhs.r) < 0.004 &&
        std::abs(lhs.g - rhs.g) < 0.004 &&
        std::abs(lhs.b - rhs.b) < 0.004 &&
        std::abs(lhs.a - rhs.a) < 0.004;
}

inline bool operator!=(const color& lhs, const color& rhs) {
    return !(lhs == rhs);
}

typedef struct {
    double x;
    double y;
    double width;
    double height;
} rectangle;

inline bool operator==(const rectangle& lhs, const rectangle& rhs) {
    return
        lhs.x == rhs.x &&
        lhs.y == rhs.y &&
        lhs.width == rhs.width &&
        lhs.height == rhs.height;
}

inline bool operator!=(const rectangle& lhs, const rectangle& rhs) {
    return !(lhs == rhs);
}

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

inline bool operator==(const drawing_options& lhs, const drawing_options& rhs) {
    return
        lhs.dest == rhs.dest &&
        lhs.scale_x == rhs.scale_x &&
        lhs.scale_y == rhs.scale_y &&
        lhs.angle == rhs.angle &&
        lhs.anchor_offset_x == rhs.anchor_offset_x &&
        lhs.anchor_offset_y == rhs.anchor_offset_y &&
        lhs.flip_x == rhs.flip_x &&
        lhs.flip_y == rhs.flip_y &&
        lhs.is_part == rhs.is_part &&
        lhs.part == rhs.part &&
        lhs.draw_cell == rhs.draw_cell &&
        lhs.camera == rhs.camera &&
        lhs.line_width == rhs.line_width &&
        lhs.anim == rhs.anim;
}

inline bool operator!=(const drawing_options& lhs, const drawing_options& rhs) {
    return !(lhs == rhs);
}

typedef struct {
    point_2d start_point;
    point_2d end_point;
} line;

inline bool operator==(const line& lhs, const line& rhs) {
    return
        lhs.start_point == rhs.start_point &&
        lhs.end_point == rhs.end_point;
}

inline bool operator!=(const line& lhs, const line& rhs) {
    return !(lhs == rhs);
}

typedef struct {
    point_2d points[4];
} quad;

inline bool operator==(const quad& lhs, const quad& rhs) {
    return
        lhs.points[0] == rhs.points[0] &&
        lhs.points[1] == rhs.points[1] &&
        lhs.points[2] == rhs.points[2] &&
        lhs.points[3] == rhs.points[3];
}

inline bool operator!=(const quad& lhs, const quad& rhs) {
    return !(lhs == rhs);
}

typedef struct {
    point_2d points[3];
} triangle;

inline bool operator==(const triangle& lhs, const triangle& rhs) {
    return
        lhs.points[0] == rhs.points[0] &&
        lhs.points[1] == rhs.points[1] &&
        lhs.points[2] == rhs.points[2];
}

inline bool operator!=(const triangle& lhs, const triangle& rhs) {
    return !(lhs == rhs);
}

typedef struct {
    double x;
    double y;
} vector_2d;

inline bool operator==(const vector_2d& lhs, const vector_2d& rhs) {
    return
        lhs.x == rhs.x &&
        lhs.y == rhs.y;
}

inline bool operator!=(const vector_2d& lhs, const vector_2d& rhs) {
    return !(lhs == rhs);
}


#endif /* __types_h */
