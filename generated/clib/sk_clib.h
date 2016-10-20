//
// SplashKit C Generated Library Code
//

#include <stdlib.h>
#include <string>
#include <vector>
#include "animations.h"
#include "audio.h"
#include "bundles.h"
#include "camera.h"
#include "circle_drawing.h"
#include "circle_geometry.h"
#include "clipping.h"
#include "collisions.h"
#include "color.h"
#include "database.h"
#include "drawing_options.h"
#include "ellipse_drawing.h"
#include "geometry.h"
#include "graphics.h"
#include "images.h"
#include "input.h"
#include "json.h"
#include "keyboard_input.h"
#include "line_drawing.h"
#include "line_geometry.h"
#include "matrix_2d.h"
#include "mouse_input.h"
#include "music.h"
#include "networking.h"
#include "physics.h"
#include "point_drawing.h"
#include "point_geometry.h"
#include "quad_geometry.h"
#include "random.h"
#include "rectangle_drawing.h"
#include "rectangle_geometry.h"
#include "resources.h"
#include "sound.h"
#include "sprites.h"
#include "terminal.h"
#include "text.h"
#include "text_input.h"
#include "timers.h"
#include "triangle_drawing.h"
#include "triangle_geometry.h"
#include "types.h"
#include "utils.h"
#include "vector_2d.h"
#include "web_client.h"
#include "web_server.h"
#include "window_manager.h"
using std::string;
using std::vector;
using namespace splashkit_lib;

extern "C" typedef struct {
    char *string;
    unsigned int size;
} __sklib_string;
extern "C" void __sklib__free__sklib_string(__sklib_string s) {
    free(s.string);
}
__sklib_string __sklib__to_sklib_string(const std::string &s) {
    __sklib_string __skreturn;
    __skreturn.size = static_cast<unsigned int>(s.length());
    __skreturn.string = (char *)malloc(__skreturn.size + 1);
    strcpy(__skreturn.string, s.c_str());
    return __skreturn;
}
std::string __sklib__to_string(const __sklib_string &s) {
    std:string result = std::string(s.string);
    return result;
}
#define __sklib__to_sklib_bool(v)\
(v == true ? 1 : 0)
#define __sklib__to_bool(v)\
(v == 1 ? true : false)
typedef bool __sklib_bool;
typedef int __sklib_int;
__sklib_int __sklib__to_sklib_int(int v) { return v; }
int __sklib__to_int(int v) { return v; }
typedef short __sklib_short;
__sklib_short __sklib__to_sklib_short(short v) { return v; }
short __sklib__to_short(short v) { return v; }
typedef long __sklib_long;
__sklib_long __sklib__to_sklib_long(long v) { return v; }
long __sklib__to_long(long v) { return v; }
typedef float __sklib_float;
__sklib_float __sklib__to_sklib_float(float v) { return v; }
float __sklib__to_float(float v) { return v; }
typedef double __sklib_double;
__sklib_double __sklib__to_sklib_double(double v) { return v; }
double __sklib__to_double(double v) { return v; }
typedef char __sklib_char;
__sklib_char __sklib__to_sklib_char(char v) { return v; }
char __sklib__to_char(char v) { return v; }
typedef unsigned int __sklib_unsigned_int;
__sklib_unsigned_int __sklib__to_sklib_unsigned_int(unsigned int v) { return v; }
unsigned int __sklib__to_unsigned_int(unsigned int v) { return v; }
typedef unsigned short __sklib_unsigned_short;
__sklib_unsigned_short __sklib__to_sklib_unsigned_short(unsigned short v) { return v; }
unsigned short __sklib__to_unsigned_short(unsigned short v) { return v; }
typedef unsigned char __sklib_unsigned_char;
__sklib_unsigned_char __sklib__to_sklib_unsigned_char(unsigned char v) { return v; }
unsigned char __sklib__to_unsigned_char(unsigned char v) { return v; }
#define __sklib_ptr void *
__sklib_ptr __sklib__to_sklib_ptr(__sklib_ptr v) { return v; }
#define __sklib__make_typealias_adapter(type)\
typedef __sklib_ptr __sklib_##type;\
__sklib_ptr __sklib__to_sklib_##type(type v) { return static_cast<__sklib_ptr>(v); }\
type __sklib__to_##type(__sklib_ptr v) { return static_cast<type>(v); }
__sklib__make_typealias_adapter(database)
__sklib__make_typealias_adapter(query_result)
__sklib__make_typealias_adapter(json)
__sklib__make_typealias_adapter(music)
__sklib__make_typealias_adapter(connection)
__sklib__make_typealias_adapter(message)
__sklib__make_typealias_adapter(server_socket)
__sklib__make_typealias_adapter(sound_effect)
__sklib__make_typealias_adapter(sprite)
__sklib__make_typealias_adapter(timer)
__sklib__make_typealias_adapter(animation)
__sklib__make_typealias_adapter(animation_script)
__sklib__make_typealias_adapter(bitmap)
__sklib__make_typealias_adapter(display)
__sklib__make_typealias_adapter(font)
__sklib__make_typealias_adapter(http_response)
__sklib__make_typealias_adapter(http_request)
__sklib__make_typealias_adapter(web_server)
__sklib__make_typealias_adapter(window)
#define __sklib__make_enum_adapter(type)\
typedef int __sklib_##type;\
int __sklib__to_sklib_##type(type v) { return static_cast<int>(v); }\
type __sklib__to_##type(int v) { return static_cast<type>(v); }
__sklib__make_enum_adapter(key_code)
__sklib__make_enum_adapter(mouse_button)
__sklib__make_enum_adapter(connection_type)
__sklib__make_enum_adapter(resource_kind)
__sklib__make_enum_adapter(collision_test_kind)
__sklib__make_enum_adapter(sprite_event_kind)
__sklib__make_enum_adapter(drawing_dest)
__sklib__make_enum_adapter(font_style)
__sklib__make_enum_adapter(http_status_code)
__sklib__make_enum_adapter(http_method)
typedef struct {
    __sklib_double elements[9];
} __sklib_matrix_2d;
__sklib_matrix_2d __sklib__to_sklib_matrix_2d(matrix_2d v) {
    __sklib_matrix_2d __skreturn;
    __skreturn.elements[0] = __sklib__to_double(v.elements[0][0]);
    __skreturn.elements[1] = __sklib__to_double(v.elements[0][1]);
    __skreturn.elements[2] = __sklib__to_double(v.elements[0][2]);
    __skreturn.elements[3] = __sklib__to_double(v.elements[1][0]);
    __skreturn.elements[4] = __sklib__to_double(v.elements[1][1]);
    __skreturn.elements[5] = __sklib__to_double(v.elements[1][2]);
    __skreturn.elements[6] = __sklib__to_double(v.elements[2][0]);
    __skreturn.elements[7] = __sklib__to_double(v.elements[2][1]);
    __skreturn.elements[8] = __sklib__to_double(v.elements[2][2]);
    return __skreturn;
}
matrix_2d __sklib__to_matrix_2d(__sklib_matrix_2d v) {
    matrix_2d __skreturn;
    __skreturn.elements[0][0] = __sklib__to_double(v.elements[0]);
    __skreturn.elements[0][1] = __sklib__to_double(v.elements[1]);
    __skreturn.elements[0][2] = __sklib__to_double(v.elements[2]);
    __skreturn.elements[1][0] = __sklib__to_double(v.elements[3]);
    __skreturn.elements[1][1] = __sklib__to_double(v.elements[4]);
    __skreturn.elements[1][2] = __sklib__to_double(v.elements[5]);
    __skreturn.elements[2][0] = __sklib__to_double(v.elements[6]);
    __skreturn.elements[2][1] = __sklib__to_double(v.elements[7]);
    __skreturn.elements[2][2] = __sklib__to_double(v.elements[8]);
    return __skreturn;
}
typedef struct {
    __sklib_float x;
    __sklib_float y;
} __sklib_point_2d;
__sklib_point_2d __sklib__to_sklib_point_2d(point_2d v) {
    __sklib_point_2d __skreturn;
    __skreturn.x = __sklib__to_float(v.x);
    __skreturn.y = __sklib__to_float(v.y);
    return __skreturn;
}
point_2d __sklib__to_point_2d(__sklib_point_2d v) {
    point_2d __skreturn;
    __skreturn.x = __sklib__to_float(v.x);
    __skreturn.y = __sklib__to_float(v.y);
    return __skreturn;
}
typedef struct {
    __sklib_point_2d center;
    __sklib_float radius;
} __sklib_circle;
__sklib_circle __sklib__to_sklib_circle(circle v) {
    __sklib_circle __skreturn;
    __skreturn.center = __sklib__to_sklib_point_2d(v.center);
    __skreturn.radius = __sklib__to_float(v.radius);
    return __skreturn;
}
circle __sklib__to_circle(__sklib_circle v) {
    circle __skreturn;
    __skreturn.center = __sklib__to_point_2d(v.center);
    __skreturn.radius = __sklib__to_float(v.radius);
    return __skreturn;
}
typedef struct {
    __sklib_float r;
    __sklib_float g;
    __sklib_float b;
    __sklib_float a;
} __sklib_color;
__sklib_color __sklib__to_sklib_color(color v) {
    __sklib_color __skreturn;
    __skreturn.r = __sklib__to_float(v.r);
    __skreturn.g = __sklib__to_float(v.g);
    __skreturn.b = __sklib__to_float(v.b);
    __skreturn.a = __sklib__to_float(v.a);
    return __skreturn;
}
color __sklib__to_color(__sklib_color v) {
    color __skreturn;
    __skreturn.r = __sklib__to_float(v.r);
    __skreturn.g = __sklib__to_float(v.g);
    __skreturn.b = __sklib__to_float(v.b);
    __skreturn.a = __sklib__to_float(v.a);
    return __skreturn;
}
typedef struct {
    __sklib_float x;
    __sklib_float y;
    __sklib_float width;
    __sklib_float height;
} __sklib_rectangle;
__sklib_rectangle __sklib__to_sklib_rectangle(rectangle v) {
    __sklib_rectangle __skreturn;
    __skreturn.x = __sklib__to_float(v.x);
    __skreturn.y = __sklib__to_float(v.y);
    __skreturn.width = __sklib__to_float(v.width);
    __skreturn.height = __sklib__to_float(v.height);
    return __skreturn;
}
rectangle __sklib__to_rectangle(__sklib_rectangle v) {
    rectangle __skreturn;
    __skreturn.x = __sklib__to_float(v.x);
    __skreturn.y = __sklib__to_float(v.y);
    __skreturn.width = __sklib__to_float(v.width);
    __skreturn.height = __sklib__to_float(v.height);
    return __skreturn;
}
typedef struct {
    __sklib_ptr dest;
    __sklib_float scale_x;
    __sklib_float scale_y;
    __sklib_float angle;
    __sklib_float anchor_offset_x;
    __sklib_float anchor_offset_y;
    __sklib_bool flip_x;
    __sklib_bool flip_y;
    __sklib_bool is_part;
    __sklib_rectangle part;
    __sklib_drawing_dest camera;
    __sklib_int line_width;
    __sklib_animation anim;
} __sklib_drawing_options;
__sklib_drawing_options __sklib__to_sklib_drawing_options(drawing_options v) {
    __sklib_drawing_options __skreturn;
    __skreturn.dest = __sklib__to_sklib_ptr(v.dest);
    __skreturn.scale_x = __sklib__to_float(v.scale_x);
    __skreturn.scale_y = __sklib__to_float(v.scale_y);
    __skreturn.angle = __sklib__to_float(v.angle);
    __skreturn.anchor_offset_x = __sklib__to_float(v.anchor_offset_x);
    __skreturn.anchor_offset_y = __sklib__to_float(v.anchor_offset_y);
    __skreturn.flip_x = __sklib__to_int(v.flip_x);
    __skreturn.flip_y = __sklib__to_int(v.flip_y);
    __skreturn.is_part = __sklib__to_int(v.is_part);
    __skreturn.part = __sklib__to_sklib_rectangle(v.part);
    __skreturn.camera = __sklib__to_int(v.camera);
    __skreturn.line_width = __sklib__to_int(v.line_width);
    __skreturn.anim = __sklib__to_sklib_animation(v.anim);
    return __skreturn;
}
drawing_options __sklib__to_drawing_options(__sklib_drawing_options v) {
    drawing_options __skreturn;
    __skreturn.dest = __sklib__to_sklib_ptr(v.dest);
    __skreturn.scale_x = __sklib__to_float(v.scale_x);
    __skreturn.scale_y = __sklib__to_float(v.scale_y);
    __skreturn.angle = __sklib__to_float(v.angle);
    __skreturn.anchor_offset_x = __sklib__to_float(v.anchor_offset_x);
    __skreturn.anchor_offset_y = __sklib__to_float(v.anchor_offset_y);
    __skreturn.flip_x = __sklib__to_bool(v.flip_x);
    __skreturn.flip_y = __sklib__to_bool(v.flip_y);
    __skreturn.is_part = __sklib__to_bool(v.is_part);
    __skreturn.part = __sklib__to_rectangle(v.part);
    __skreturn.camera = __sklib__to_drawing_dest(v.camera);
    __skreturn.line_width = __sklib__to_int(v.line_width);
    __skreturn.anim = __sklib__to_animation(v.anim);
    return __skreturn;
}
typedef struct {
    __sklib_point_2d start_point;
    __sklib_point_2d end_point;
} __sklib_line;
__sklib_line __sklib__to_sklib_line(line v) {
    __sklib_line __skreturn;
    __skreturn.start_point = __sklib__to_sklib_point_2d(v.start_point);
    __skreturn.end_point = __sklib__to_sklib_point_2d(v.end_point);
    return __skreturn;
}
line __sklib__to_line(__sklib_line v) {
    line __skreturn;
    __skreturn.start_point = __sklib__to_point_2d(v.start_point);
    __skreturn.end_point = __sklib__to_point_2d(v.end_point);
    return __skreturn;
}
typedef struct {
    __sklib_point_2d points[4];
} __sklib_quad;
__sklib_quad __sklib__to_sklib_quad(quad v) {
    __sklib_quad __skreturn;
    __skreturn.points[0] = __sklib__to_sklib_point_2d(v.points[0]);
    __skreturn.points[1] = __sklib__to_sklib_point_2d(v.points[1]);
    __skreturn.points[2] = __sklib__to_sklib_point_2d(v.points[2]);
    __skreturn.points[3] = __sklib__to_sklib_point_2d(v.points[3]);
    return __skreturn;
}
quad __sklib__to_quad(__sklib_quad v) {
    quad __skreturn;
    __skreturn.points[0] = __sklib__to_point_2d(v.points[0]);
    __skreturn.points[1] = __sklib__to_point_2d(v.points[1]);
    __skreturn.points[2] = __sklib__to_point_2d(v.points[2]);
    __skreturn.points[3] = __sklib__to_point_2d(v.points[3]);
    return __skreturn;
}
typedef struct {
    __sklib_point_2d points[3];
} __sklib_triangle;
__sklib_triangle __sklib__to_sklib_triangle(triangle v) {
    __sklib_triangle __skreturn;
    __skreturn.points[0] = __sklib__to_sklib_point_2d(v.points[0]);
    __skreturn.points[1] = __sklib__to_sklib_point_2d(v.points[1]);
    __skreturn.points[2] = __sklib__to_sklib_point_2d(v.points[2]);
    return __skreturn;
}
triangle __sklib__to_triangle(__sklib_triangle v) {
    triangle __skreturn;
    __skreturn.points[0] = __sklib__to_point_2d(v.points[0]);
    __skreturn.points[1] = __sklib__to_point_2d(v.points[1]);
    __skreturn.points[2] = __sklib__to_point_2d(v.points[2]);
    return __skreturn;
}
typedef struct {
    __sklib_double x;
    __sklib_double y;
} __sklib_vector_2d;
__sklib_vector_2d __sklib__to_sklib_vector_2d(vector_2d v) {
    __sklib_vector_2d __skreturn;
    __skreturn.x = __sklib__to_double(v.x);
    __skreturn.y = __sklib__to_double(v.y);
    return __skreturn;
}
vector_2d __sklib__to_vector_2d(__sklib_vector_2d v) {
    vector_2d __skreturn;
    __skreturn.x = __sklib__to_double(v.x);
    __skreturn.y = __sklib__to_double(v.y);
    return __skreturn;
}
typedef void (__sklib_key_callback)(key_code code);
void (*__sklib__to_key_callback(__sklib_key_callback *v))(key_code code) { return v; }
void (*__sklib__to_sklib_key_callback(key_callback *v))(key_code code) { return v; }
typedef void (__sklib_free_notifier)(void *pointer);
void (*__sklib__to_free_notifier(__sklib_free_notifier *v))(void *pointer) { return v; }
void (*__sklib__to_sklib_free_notifier(free_notifier *v))(void *pointer) { return v; }
typedef void (__sklib_sprite_event_handler)(sprite s, sprite_event_kind evt);
void (*__sklib__to_sprite_event_handler(__sklib_sprite_event_handler *v))(sprite s, sprite_event_kind evt) { return v; }
void (*__sklib__to_sklib_sprite_event_handler(sprite_event_handler *v))(sprite s, sprite_event_kind evt) { return v; }
typedef void (__sklib_sprite_float_function)(sprite s, float f);
void (*__sklib__to_sprite_float_function(__sklib_sprite_float_function *v))(sprite s, float f) { return v; }
void (*__sklib__to_sklib_sprite_float_function(sprite_float_function *v))(sprite s, float f) { return v; }
typedef void (__sklib_sprite_function)(sprite s);
void (*__sklib__to_sprite_function(__sklib_sprite_function *v))(sprite s) { return v; }
void (*__sklib__to_sklib_sprite_function(sprite_function *v))(sprite s) { return v; }
typedef struct {
        __sklib_line *data_from_app;
    unsigned int size_from_app;
        __sklib_line *data_from_lib;
    unsigned int size_from_lib;
} __sklib_vector_line;
extern "C" void __sklib__free__sklib_vector_line(__sklib_vector_line v) {
    free(v.data_from_lib);
}
__sklib_vector_line __sklib__to_sklib_vector_line(const std::vector<line> &v) {
    __sklib_vector_line __skreturn;
    __skreturn.size_from_app = 0;
    __skreturn.data_from_app = nullptr;
    __skreturn.size_from_lib = static_cast<unsigned int>(v.size());
    __skreturn.data_from_lib = (__sklib_line *)malloc(__skreturn.size_from_lib * sizeof(__sklib_line));
    unsigned int i = 0;
    for (line d : v) {
        __skreturn.data_from_lib[i] = __sklib__to_sklib_line(d);
        i++;
    }
    return __skreturn;
}
vector<line> __sklib__to_vector_line(const __sklib_vector_line &v) {
    vector<line> __skreturn;
    for (int i = 0; i < v.size_from_app; i++) {
        __skreturn.push_back(__sklib__to_line(v.data_from_app[i]));
    }
    return __skreturn;
}
void __sklib__update_from_vector_line(const std::vector<line> &v, __sklib_vector_line *__skreturn) {
    __skreturn->size_from_lib = static_cast<unsigned int>(v.size());
    __skreturn->data_from_lib = (__sklib_line *)malloc(__skreturn->size_from_lib * sizeof(__sklib_line));
    unsigned int i = 0;
    for (line d : v) {
        __skreturn->data_from_lib[i] = __sklib__to_sklib_line(d);
        i++;
    }
}
typedef struct {
        __sklib_triangle *data_from_app;
    unsigned int size_from_app;
        __sklib_triangle *data_from_lib;
    unsigned int size_from_lib;
} __sklib_vector_triangle;
extern "C" void __sklib__free__sklib_vector_triangle(__sklib_vector_triangle v) {
    free(v.data_from_lib);
}
__sklib_vector_triangle __sklib__to_sklib_vector_triangle(const std::vector<triangle> &v) {
    __sklib_vector_triangle __skreturn;
    __skreturn.size_from_app = 0;
    __skreturn.data_from_app = nullptr;
    __skreturn.size_from_lib = static_cast<unsigned int>(v.size());
    __skreturn.data_from_lib = (__sklib_triangle *)malloc(__skreturn.size_from_lib * sizeof(__sklib_triangle));
    unsigned int i = 0;
    for (triangle d : v) {
        __skreturn.data_from_lib[i] = __sklib__to_sklib_triangle(d);
        i++;
    }
    return __skreturn;
}
vector<triangle> __sklib__to_vector_triangle(const __sklib_vector_triangle &v) {
    vector<triangle> __skreturn;
    for (int i = 0; i < v.size_from_app; i++) {
        __skreturn.push_back(__sklib__to_triangle(v.data_from_app[i]));
    }
    return __skreturn;
}
void __sklib__update_from_vector_triangle(const std::vector<triangle> &v, __sklib_vector_triangle *__skreturn) {
    __skreturn->size_from_lib = static_cast<unsigned int>(v.size());
    __skreturn->data_from_lib = (__sklib_triangle *)malloc(__skreturn->size_from_lib * sizeof(__sklib_triangle));
    unsigned int i = 0;
    for (triangle d : v) {
        __skreturn->data_from_lib[i] = __sklib__to_sklib_triangle(d);
        i++;
    }
}
typedef struct {
        __sklib_string *data_from_app;
    unsigned int size_from_app;
        __sklib_string *data_from_lib;
    unsigned int size_from_lib;
} __sklib_vector_string;
extern "C" void __sklib__free__sklib_vector_string(__sklib_vector_string v) {
    free(v.data_from_lib);
}
__sklib_vector_string __sklib__to_sklib_vector_string(const std::vector<string> &v) {
    __sklib_vector_string __skreturn;
    __skreturn.size_from_app = 0;
    __skreturn.data_from_app = nullptr;
    __skreturn.size_from_lib = static_cast<unsigned int>(v.size());
    __skreturn.data_from_lib = (__sklib_string *)malloc(__skreturn.size_from_lib * sizeof(__sklib_string));
    unsigned int i = 0;
    for (string d : v) {
        __skreturn.data_from_lib[i] = __sklib__to_sklib_string(d);
        i++;
    }
    return __skreturn;
}
vector<string> __sklib__to_vector_string(const __sklib_vector_string &v) {
    vector<string> __skreturn;
    for (int i = 0; i < v.size_from_app; i++) {
        __skreturn.push_back(__sklib__to_string(v.data_from_app[i]));
    }
    return __skreturn;
}
void __sklib__update_from_vector_string(const std::vector<string> &v, __sklib_vector_string *__skreturn) {
    __skreturn->size_from_lib = static_cast<unsigned int>(v.size());
    __skreturn->data_from_lib = (__sklib_string *)malloc(__skreturn->size_from_lib * sizeof(__sklib_string));
    unsigned int i = 0;
    for (string d : v) {
        __skreturn->data_from_lib[i] = __sklib__to_sklib_string(d);
        i++;
    }
}
typedef struct {
        double *data_from_app;
    unsigned int size_from_app;
        double *data_from_lib;
    unsigned int size_from_lib;
} __sklib_vector_double;
extern "C" void __sklib__free__sklib_vector_double(__sklib_vector_double v) {
    free(v.data_from_lib);
}
__sklib_vector_double __sklib__to_sklib_vector_double(const std::vector<double> &v) {
    __sklib_vector_double __skreturn;
    __skreturn.size_from_app = 0;
    __skreturn.data_from_app = nullptr;
    __skreturn.size_from_lib = static_cast<unsigned int>(v.size());
    __skreturn.data_from_lib = (double *)malloc(__skreturn.size_from_lib * sizeof(double));
    unsigned int i = 0;
    for (double d : v) {
        __skreturn.data_from_lib[i] = __sklib__to_sklib_double(d);
        i++;
    }
    return __skreturn;
}
vector<double> __sklib__to_vector_double(const __sklib_vector_double &v) {
    vector<double> __skreturn;
    for (int i = 0; i < v.size_from_app; i++) {
        __skreturn.push_back(__sklib__to_double(v.data_from_app[i]));
    }
    return __skreturn;
}
void __sklib__update_from_vector_double(const std::vector<double> &v, __sklib_vector_double *__skreturn) {
    __skreturn->size_from_lib = static_cast<unsigned int>(v.size());
    __skreturn->data_from_lib = (double *)malloc(__skreturn->size_from_lib * sizeof(double));
    unsigned int i = 0;
    for (double d : v) {
        __skreturn->data_from_lib[i] = __sklib__to_sklib_double(d);
        i++;
    }
}
typedef struct {
        __sklib_json *data_from_app;
    unsigned int size_from_app;
        __sklib_json *data_from_lib;
    unsigned int size_from_lib;
} __sklib_vector_json;
extern "C" void __sklib__free__sklib_vector_json(__sklib_vector_json v) {
    free(v.data_from_lib);
}
__sklib_vector_json __sklib__to_sklib_vector_json(const std::vector<json> &v) {
    __sklib_vector_json __skreturn;
    __skreturn.size_from_app = 0;
    __skreturn.data_from_app = nullptr;
    __skreturn.size_from_lib = static_cast<unsigned int>(v.size());
    __skreturn.data_from_lib = (__sklib_json *)malloc(__skreturn.size_from_lib * sizeof(__sklib_json));
    unsigned int i = 0;
    for (json d : v) {
        __skreturn.data_from_lib[i] = __sklib__to_sklib_json(d);
        i++;
    }
    return __skreturn;
}
vector<json> __sklib__to_vector_json(const __sklib_vector_json &v) {
    vector<json> __skreturn;
    for (int i = 0; i < v.size_from_app; i++) {
        __skreturn.push_back(__sklib__to_json(v.data_from_app[i]));
    }
    return __skreturn;
}
void __sklib__update_from_vector_json(const std::vector<json> &v, __sklib_vector_json *__skreturn) {
    __skreturn->size_from_lib = static_cast<unsigned int>(v.size());
    __skreturn->data_from_lib = (__sklib_json *)malloc(__skreturn->size_from_lib * sizeof(__sklib_json));
    unsigned int i = 0;
    for (json d : v) {
        __skreturn->data_from_lib[i] = __sklib__to_sklib_json(d);
        i++;
    }
}
typedef struct {
        int *data_from_app;
    unsigned int size_from_app;
        int *data_from_lib;
    unsigned int size_from_lib;
} __sklib_vector_bool;
extern "C" void __sklib__free__sklib_vector_bool(__sklib_vector_bool v) {
    free(v.data_from_lib);
}
__sklib_vector_bool __sklib__to_sklib_vector_bool(const std::vector<bool> &v) {
    __sklib_vector_bool __skreturn;
    __skreturn.size_from_app = 0;
    __skreturn.data_from_app = nullptr;
    __skreturn.size_from_lib = static_cast<unsigned int>(v.size());
    __skreturn.data_from_lib = (int *)malloc(__skreturn.size_from_lib * sizeof(int));
    unsigned int i = 0;
    for (bool d : v) {
        __skreturn.data_from_lib[i] = __sklib__to_sklib_bool(d);
        i++;
    }
    return __skreturn;
}
vector<bool> __sklib__to_vector_bool(const __sklib_vector_bool &v) {
    vector<bool> __skreturn;
    for (int i = 0; i < v.size_from_app; i++) {
        __skreturn.push_back(__sklib__to_bool(v.data_from_app[i]));
    }
    return __skreturn;
}
void __sklib__update_from_vector_bool(const std::vector<bool> &v, __sklib_vector_bool *__skreturn) {
    __skreturn->size_from_lib = static_cast<unsigned int>(v.size());
    __skreturn->data_from_lib = (int *)malloc(__skreturn->size_from_lib * sizeof(int));
    unsigned int i = 0;
    for (bool d : v) {
        __skreturn->data_from_lib[i] = __sklib__to_sklib_bool(d);
        i++;
    }
}
extern "C" int __sklib__animation_count__animation_script(__sklib_animation_script script);
extern "C" int __sklib__animation_current_cell__animation(__sklib_animation anim);
extern "C" __sklib_vector_2d __sklib__animation_current_vector__animation(__sklib_animation anim);
extern "C" int __sklib__animation_ended__animation(__sklib_animation anim);
extern "C" int __sklib__animation_entered_frame__animation(__sklib_animation anim);
extern "C" float __sklib__animation_frame_time__animation(__sklib_animation anim);
extern "C" int __sklib__animation_index__animation_script__string_ref(__sklib_animation_script script, const __sklib_string name);
extern "C" __sklib_string __sklib__animation_name__animation(__sklib_animation temp);
extern "C" __sklib_string __sklib__animation_script_name__animation_script(__sklib_animation_script script);
extern "C" __sklib_animation_script __sklib__animation_script_named__string_ref(const __sklib_string name);
extern "C" void __sklib__assign_animation__animation__animation_script__string_ref(__sklib_animation anim, __sklib_animation_script script, const __sklib_string name);
extern "C" void __sklib__assign_animation__animation__animation_script__string_ref__bool(__sklib_animation anim, __sklib_animation_script script, const __sklib_string name, int with_sound);
extern "C" void __sklib__assign_animation__animation__animation_script__int(__sklib_animation anim, __sklib_animation_script script, int idx);
extern "C" void __sklib__assign_animation__animation__animation_script__int__bool(__sklib_animation anim, __sklib_animation_script script, int idx, int with_sound);
extern "C" void __sklib__assign_animation__animation__string_ref__string_ref(__sklib_animation anim, const __sklib_string script_name, const __sklib_string name);
extern "C" void __sklib__assign_animation__animation__string_ref__string_ref__bool(__sklib_animation anim, const __sklib_string script_name, const __sklib_string name, int with_sound);
extern "C" __sklib_animation __sklib__create_animation__animation_script__int__bool(__sklib_animation_script script, int idx, int with_sound);
extern "C" __sklib_animation __sklib__create_animation__animation_script__string_ref(__sklib_animation_script script, const __sklib_string name);
extern "C" __sklib_animation __sklib__create_animation__animation_script__string_ref__bool(__sklib_animation_script script, const __sklib_string name, int with_sound);
extern "C" __sklib_animation __sklib__create_animation__string_ref__string_ref(const __sklib_string script_name, const __sklib_string name);
extern "C" __sklib_animation __sklib__create_animation__string_ref__string_ref__bool(const __sklib_string script_name, const __sklib_string name, int with_sound);
extern "C" void __sklib__free_all_animation_scripts();
extern "C" void __sklib__free_animation__animation(__sklib_animation ani);
extern "C" void __sklib__free_animation_script__animation_script(__sklib_animation_script script_to_free);
extern "C" void __sklib__free_animation_script__string_ref(const __sklib_string name);
extern "C" int __sklib__has_animation_named__animation_script__string_ref(__sklib_animation_script script, const __sklib_string name);
extern "C" int __sklib__has_animation_script__string_ref(const __sklib_string name);
extern "C" __sklib_animation_script __sklib__load_animation_script__string_ref__string_ref(const __sklib_string name, const __sklib_string filename);
extern "C" void __sklib__restart_animation__animation(__sklib_animation anim);
extern "C" void __sklib__restart_animation__animation__bool(__sklib_animation anim, int with_sound);
extern "C" void __sklib__update_animation__animation__float__bool(__sklib_animation anim, float pct, int with_sound);
extern "C" void __sklib__update_animation__animation(__sklib_animation anim);
extern "C" void __sklib__update_animation__animation__float(__sklib_animation anim, float pct);
extern "C" int __sklib__audio_ready();
extern "C" void __sklib__close_audio();
extern "C" void __sklib__open_audio();
extern "C" void __sklib__free_resource_bundle__string(const __sklib_string name);
extern "C" int __sklib__has_resource_bundle__string_ref(const __sklib_string name);
extern "C" void __sklib__load_resource_bundle__string_ref__string_ref(const __sklib_string name, const __sklib_string filename);
extern "C" __sklib_point_2d __sklib__camera_position();
extern "C" float __sklib__camera_x();
extern "C" float __sklib__camera_y();
extern "C" void __sklib__center_camera_on__sprite__vector_2d_ref(__sklib_sprite s, const __sklib_vector_2d offset);
extern "C" void __sklib__center_camera_on__sprite__float__float(__sklib_sprite s, float offset_x, float offset_y);
extern "C" void __sklib__move_camera_by__vector_2d_ref(const __sklib_vector_2d offset);
extern "C" void __sklib__move_camera_by__float__float(float dx, float dy);
extern "C" void __sklib__move_camera_to__point_2d_ref(const __sklib_point_2d pt);
extern "C" void __sklib__move_camera_to__float__float(float x, float y);
extern "C" int __sklib__point_on_screen__point_2d_ref(const __sklib_point_2d pt);
extern "C" int __sklib__rect_on_screen__rectangle_ref(const __sklib_rectangle rect);
extern "C" __sklib_point_2d __sklib__screen_center();
extern "C" __sklib_rectangle __sklib__screen_rectangle();
extern "C" void __sklib__set_camera_position__point_2d(__sklib_point_2d pos);
extern "C" void __sklib__set_camera_y__float(float y);
extern "C" __sklib_point_2d __sklib__to_screen__point_2d_ref(const __sklib_point_2d pt);
extern "C" __sklib_rectangle __sklib__to_screen__rectangle_ref(const __sklib_rectangle rect);
extern "C" float __sklib__to_screen_x__float(float world_x);
extern "C" float __sklib__to_screen_y__float(float world_y);
extern "C" __sklib_point_2d __sklib__to_world__point_2d_ref(const __sklib_point_2d pt);
extern "C" float __sklib__to_world_x__float(float screen_x);
extern "C" float __sklib__to_world_y__float(float screen_y);
extern "C" __sklib_vector_2d __sklib__vector_world_to_screen();
extern "C" void __sklib__draw_circle__color__circle_ref(__sklib_color clr, const __sklib_circle c);
extern "C" void __sklib__draw_circle__color__circle_ref__drawing_options(__sklib_color clr, const __sklib_circle c, __sklib_drawing_options opts);
extern "C" void __sklib__draw_circle__color__float__float__float(__sklib_color clr, float x, float y, float radius);
extern "C" void __sklib__draw_circle__color__float__float__float__drawing_options(__sklib_color clr, float x, float y, float radius, __sklib_drawing_options opts);
extern "C" void __sklib__fill_circle__color__circle_ref(__sklib_color clr, const __sklib_circle c);
extern "C" void __sklib__fill_circle__color__circle_ref__drawing_options(__sklib_color clr, const __sklib_circle c, __sklib_drawing_options opts);
extern "C" void __sklib__fill_circle__color__float__float__float(__sklib_color clr, float x, float y, float radius);
extern "C" void __sklib__fill_circle__color__float__float__float__drawing_options(__sklib_color clr, float x, float y, float radius, __sklib_drawing_options opts);
extern "C" __sklib_point_2d __sklib__center_point__circle_ref(const __sklib_circle c);
extern "C" __sklib_circle __sklib__circle_at__point_2d_ref__float(const __sklib_point_2d pt, float radius);
extern "C" __sklib_circle __sklib__circle_at__float__float__float(float x, float y, float radius);
extern "C" float __sklib__circle_radius__circle(const __sklib_circle c);
extern "C" float __sklib__circle_x__circle_ref(const __sklib_circle c);
extern "C" float __sklib__circle_y__circle_ref(const __sklib_circle c);
extern "C" int __sklib__circles_intersect__circle__circle(__sklib_circle c1, __sklib_circle c2);
extern "C" __sklib_point_2d __sklib__closest_point_on_circle__point_2d_ref__circle_ref(const __sklib_point_2d from_pt, const __sklib_circle c);
extern "C" __sklib_point_2d __sklib__closest_point_on_line_from_circle__circle_ref__line_ref(const __sklib_circle c, const __sklib_line l);
extern "C" __sklib_point_2d __sklib__closest_point_on_rect_from_circle__circle_ref__rectangle_ref(const __sklib_circle c, const __sklib_rectangle rect);
extern "C" __sklib_point_2d __sklib__distant_point_on_circle__point_2d_ref__circle_ref(const __sklib_point_2d pt, const __sklib_circle c);
extern "C" int __sklib__distant_point_on_circle_heading__point_2d_ref__circle_ref__vector_2d_ref__point_2d_ref(const __sklib_point_2d pt, const __sklib_circle c, const __sklib_vector_2d heading, __sklib_point_2d *opposite_pt);
extern "C" float __sklib__ray_circle_intersect_distance__point_2d_ref__vector_2d_ref__circle_ref(const __sklib_point_2d ray_origin, const __sklib_vector_2d ray_heading, const __sklib_circle c);
extern "C" int __sklib__tangent_points__point_2d_ref__circle_ref__point_2d_ref__point_2d_ref(const __sklib_point_2d from_pt, const __sklib_circle c, __sklib_point_2d *p1, __sklib_point_2d *p2);
extern "C" void __sklib__widest_points__circle_ref__vector_2d_ref__point_2d_ref__point_2d_ref(const __sklib_circle c, const __sklib_vector_2d along, __sklib_point_2d *pt1, __sklib_point_2d *pt2);
extern "C" __sklib_rectangle __sklib__current_clip();
extern "C" __sklib_rectangle __sklib__current_clip__bitmap(__sklib_bitmap bmp);
extern "C" __sklib_rectangle __sklib__current_clip__window(__sklib_window wnd);
extern "C" void __sklib__pop_clip__window(__sklib_window wnd);
extern "C" void __sklib__pop_clip();
extern "C" void __sklib__pop_clip__bitmap(__sklib_bitmap bmp);
extern "C" void __sklib__push_clip__window__rectangle_ref(__sklib_window wnd, const __sklib_rectangle r);
extern "C" void __sklib__push_clip__bitmap__rectangle_ref(__sklib_bitmap bmp, const __sklib_rectangle r);
extern "C" void __sklib__push_clip__rectangle_ref(const __sklib_rectangle r);
extern "C" void __sklib__reset_clip__bitmap(__sklib_bitmap bmp);
extern "C" void __sklib__reset_clip();
extern "C" void __sklib__reset_clip__window(__sklib_window wnd);
extern "C" void __sklib__set_clip__rectangle_ref(const __sklib_rectangle r);
extern "C" void __sklib__set_clip__bitmap__rectangle_ref(__sklib_bitmap bmp, const __sklib_rectangle r);
extern "C" void __sklib__set_clip__window__rectangle_ref(__sklib_window wnd, const __sklib_rectangle r);
extern "C" int __sklib__bitmap_collision__bitmap__float__float__bitmap__float__float(__sklib_bitmap bmp1, float x1, float y1, __sklib_bitmap bmp2, float x2, float y2);
extern "C" int __sklib__bitmap_collision__bitmap__point_2d_ref__bitmap__point_2d_ref(__sklib_bitmap bmp1, const __sklib_point_2d pt1, __sklib_bitmap bmp2, const __sklib_point_2d pt2);
extern "C" int __sklib__bitmap_collision__bitmap__int__matrix_2d_ref__bitmap__int__matrix_2d_ref(__sklib_bitmap bmp1, int cell1, const __sklib_matrix_2d matrix1, __sklib_bitmap bmp2, int cell2, const __sklib_matrix_2d matrix2);
extern "C" int __sklib__bitmap_collision__bitmap__int__point_2d_ref__bitmap__int__point_2d_ref(__sklib_bitmap bmp1, int cell1, const __sklib_point_2d pt1, __sklib_bitmap bmp2, int cell2, const __sklib_point_2d pt2);
extern "C" int __sklib__bitmap_collision__bitmap__int__float__float__bitmap__int__float__float(__sklib_bitmap bmp1, int cell1, float x1, float y1, __sklib_bitmap bmp2, int cell2, float x2, float y2);
extern "C" int __sklib__bitmap_point_collision__bitmap__matrix_2d_ref__point_2d_ref(__sklib_bitmap bmp, const __sklib_matrix_2d translation, const __sklib_point_2d pt);
extern "C" int __sklib__bitmap_point_collision__bitmap__point_2d_ref__point_2d_ref(__sklib_bitmap bmp, const __sklib_point_2d pt, const __sklib_point_2d bmp_pt);
extern "C" int __sklib__bitmap_point_collision__bitmap__float__float__float__float(__sklib_bitmap bmp, float bmp_x, float bmp_y, float x, float y);
extern "C" int __sklib__bitmap_point_collision__bitmap__int__matrix_2d_ref__point_2d_ref(__sklib_bitmap bmp, int cell, const __sklib_matrix_2d translation, const __sklib_point_2d pt);
extern "C" int __sklib__bitmap_rectangle_collision__bitmap__int__matrix_2d_ref__rectangle_ref(__sklib_bitmap bmp, int cell, const __sklib_matrix_2d translation, const __sklib_rectangle rect);
extern "C" int __sklib__bitmap_rectangle_collision__bitmap__int__point_2d_ref__rectangle_ref(__sklib_bitmap bmp, int cell, const __sklib_point_2d pt, const __sklib_rectangle rect);
extern "C" int __sklib__sprite_bitmap_collision__sprite__bitmap__float__float(__sklib_sprite s, __sklib_bitmap bmp, float x, float y);
extern "C" int __sklib__sprite_bitmap_collision__sprite__bitmap__int__point_2d_ref(__sklib_sprite s, __sklib_bitmap bmp, int cell, const __sklib_point_2d pt);
extern "C" int __sklib__sprite_bitmap_collision__sprite__bitmap__int__float__float(__sklib_sprite s, __sklib_bitmap bmp, int cell, float x, float y);
extern "C" int __sklib__sprite_collision__sprite__sprite(__sklib_sprite s1, __sklib_sprite s2);
extern "C" int __sklib__sprite_point_collision__sprite__point_2d_ref(__sklib_sprite s, const __sklib_point_2d pt);
extern "C" int __sklib__sprite_rectangle_collision__sprite__rectangle_ref(__sklib_sprite s, const __sklib_rectangle rect);
extern "C" int __sklib__alpha_of__color(__sklib_color c);
extern "C" int __sklib__blue_of__color(__sklib_color c);
extern "C" float __sklib__brightness_of__color(__sklib_color c);
extern "C" __sklib_color __sklib__color_alice_blue();
extern "C" __sklib_color __sklib__color_antique_white();
extern "C" __sklib_color __sklib__color_aqua();
extern "C" __sklib_color __sklib__color_aquamarine();
extern "C" __sklib_color __sklib__color_azure();
extern "C" __sklib_color __sklib__color_beige();
extern "C" __sklib_color __sklib__color_bisque();
extern "C" __sklib_color __sklib__color_black();
extern "C" __sklib_color __sklib__color_blanched_almond();
extern "C" __sklib_color __sklib__color_blue();
extern "C" __sklib_color __sklib__color_blue_violet();
extern "C" __sklib_color __sklib__color_bright_green();
extern "C" __sklib_color __sklib__color_brown();
extern "C" __sklib_color __sklib__color_burly_wood();
extern "C" __sklib_color __sklib__color_cadet_blue();
extern "C" __sklib_color __sklib__color_chartreuse();
extern "C" __sklib_color __sklib__color_chocolate();
extern "C" __sklib_color __sklib__color_coral();
extern "C" __sklib_color __sklib__color_cornflower_blue();
extern "C" __sklib_color __sklib__color_cornsilk();
extern "C" __sklib_color __sklib__color_crimson();
extern "C" __sklib_color __sklib__color_cyan();
extern "C" __sklib_color __sklib__color_dark_blue();
extern "C" __sklib_color __sklib__color_dark_cyan();
extern "C" __sklib_color __sklib__color_dark_goldenrod();
extern "C" __sklib_color __sklib__color_dark_gray();
extern "C" __sklib_color __sklib__color_dark_green();
extern "C" __sklib_color __sklib__color_dark_khaki();
extern "C" __sklib_color __sklib__color_dark_magenta();
extern "C" __sklib_color __sklib__color_dark_olive_green();
extern "C" __sklib_color __sklib__color_dark_orange();
extern "C" __sklib_color __sklib__color_dark_orchid();
extern "C" __sklib_color __sklib__color_dark_red();
extern "C" __sklib_color __sklib__color_dark_salmon();
extern "C" __sklib_color __sklib__color_dark_sea_green();
extern "C" __sklib_color __sklib__color_dark_slate_blue();
extern "C" __sklib_color __sklib__color_dark_slate_gray();
extern "C" __sklib_color __sklib__color_dark_turquoise();
extern "C" __sklib_color __sklib__color_dark_violet();
extern "C" __sklib_color __sklib__color_deep_pink();
extern "C" __sklib_color __sklib__color_deep_sky_blue();
extern "C" __sklib_color __sklib__color_dim_gray();
extern "C" __sklib_color __sklib__color_dodger_blue();
extern "C" __sklib_color __sklib__color_firebrick();
extern "C" __sklib_color __sklib__color_floral_white();
extern "C" __sklib_color __sklib__color_forest_green();
extern "C" __sklib_color __sklib__color_fuchsia();
extern "C" __sklib_color __sklib__color_gainsboro();
extern "C" __sklib_color __sklib__color_ghost_white();
extern "C" __sklib_color __sklib__color_gold();
extern "C" __sklib_color __sklib__color_goldenrod();
extern "C" __sklib_color __sklib__color_gray();
extern "C" __sklib_color __sklib__color_green();
extern "C" __sklib_color __sklib__color_green_yellow();
extern "C" __sklib_color __sklib__color_honeydew();
extern "C" __sklib_color __sklib__color_hot_pink();
extern "C" __sklib_color __sklib__color_indian_red();
extern "C" __sklib_color __sklib__color_indigo();
extern "C" __sklib_color __sklib__color_ivory();
extern "C" __sklib_color __sklib__color_khaki();
extern "C" __sklib_color __sklib__color_lavender();
extern "C" __sklib_color __sklib__color_lavender_blush();
extern "C" __sklib_color __sklib__color_lawn_green();
extern "C" __sklib_color __sklib__color_lemon_chiffon();
extern "C" __sklib_color __sklib__color_light_blue();
extern "C" __sklib_color __sklib__color_light_coral();
extern "C" __sklib_color __sklib__color_light_cyan();
extern "C" __sklib_color __sklib__color_light_goldenrod_yellow();
extern "C" __sklib_color __sklib__color_light_gray();
extern "C" __sklib_color __sklib__color_light_green();
extern "C" __sklib_color __sklib__color_light_pink();
extern "C" __sklib_color __sklib__color_light_salmon();
extern "C" __sklib_color __sklib__color_light_sea_green();
extern "C" __sklib_color __sklib__color_light_sky_blue();
extern "C" __sklib_color __sklib__color_light_slate_gray();
extern "C" __sklib_color __sklib__color_light_steel_blue();
extern "C" __sklib_color __sklib__color_light_yellow();
extern "C" __sklib_color __sklib__color_lime();
extern "C" __sklib_color __sklib__color_lime_green();
extern "C" __sklib_color __sklib__color_linen();
extern "C" __sklib_color __sklib__color_magenta();
extern "C" __sklib_color __sklib__color_maroon();
extern "C" __sklib_color __sklib__color_medium_aquamarine();
extern "C" __sklib_color __sklib__color_medium_blue();
extern "C" __sklib_color __sklib__color_medium_orchid();
extern "C" __sklib_color __sklib__color_medium_purple();
extern "C" __sklib_color __sklib__color_medium_sea_green();
extern "C" __sklib_color __sklib__color_medium_slate_blue();
extern "C" __sklib_color __sklib__color_medium_spring_green();
extern "C" __sklib_color __sklib__color_medium_turquoise();
extern "C" __sklib_color __sklib__color_medium_violet_red();
extern "C" __sklib_color __sklib__color_midnight_blue();
extern "C" __sklib_color __sklib__color_mint_cream();
extern "C" __sklib_color __sklib__color_misty_rose();
extern "C" __sklib_color __sklib__color_moccasin();
extern "C" __sklib_color __sklib__color_navajo_white();
extern "C" __sklib_color __sklib__color_navy();
extern "C" __sklib_color __sklib__color_old_lace();
extern "C" __sklib_color __sklib__color_olive();
extern "C" __sklib_color __sklib__color_olive_drab();
extern "C" __sklib_color __sklib__color_orange();
extern "C" __sklib_color __sklib__color_orange_red();
extern "C" __sklib_color __sklib__color_orchid();
extern "C" __sklib_color __sklib__color_pale_goldenrod();
extern "C" __sklib_color __sklib__color_pale_green();
extern "C" __sklib_color __sklib__color_pale_turquoise();
extern "C" __sklib_color __sklib__color_pale_violet_red();
extern "C" __sklib_color __sklib__color_papaya_whip();
extern "C" __sklib_color __sklib__color_peach_puff();
extern "C" __sklib_color __sklib__color_peru();
extern "C" __sklib_color __sklib__color_pink();
extern "C" __sklib_color __sklib__color_plum();
extern "C" __sklib_color __sklib__color_powder_blue();
extern "C" __sklib_color __sklib__color_purple();
extern "C" __sklib_color __sklib__color_red();
extern "C" __sklib_color __sklib__color_rosy_brown();
extern "C" __sklib_color __sklib__color_royal_blue();
extern "C" __sklib_color __sklib__color_saddle_brown();
extern "C" __sklib_color __sklib__color_salmon();
extern "C" __sklib_color __sklib__color_sandy_brown();
extern "C" __sklib_color __sklib__color_sea_green();
extern "C" __sklib_color __sklib__color_sea_shell();
extern "C" __sklib_color __sklib__color_sienna();
extern "C" __sklib_color __sklib__color_silver();
extern "C" __sklib_color __sklib__color_sky_blue();
extern "C" __sklib_color __sklib__color_slate_blue();
extern "C" __sklib_color __sklib__color_slate_gray();
extern "C" __sklib_color __sklib__color_snow();
extern "C" __sklib_color __sklib__color_spring_green();
extern "C" __sklib_color __sklib__color_steel_blue();
extern "C" __sklib_color __sklib__color_swinburne_red();
extern "C" __sklib_color __sklib__color_tan();
extern "C" __sklib_color __sklib__color_teal();
extern "C" __sklib_color __sklib__color_thistle();
extern "C" __sklib_string __sklib__color_to_string__color(__sklib_color c);
extern "C" __sklib_color __sklib__color_tomato();
extern "C" __sklib_color __sklib__color_transparent();
extern "C" __sklib_color __sklib__color_turquoise();
extern "C" __sklib_color __sklib__color_violet();
extern "C" __sklib_color __sklib__color_wheat();
extern "C" __sklib_color __sklib__color_white();
extern "C" __sklib_color __sklib__color_white_smoke();
extern "C" __sklib_color __sklib__color_yellow();
extern "C" __sklib_color __sklib__color_yellow_green();
extern "C" int __sklib__green_of__color(__sklib_color c);
extern "C" __sklib_color __sklib__hsb_color__float__float__float(float hue, float saturation, float brightness);
extern "C" float __sklib__hue_of__color(__sklib_color c);
extern "C" __sklib_color __sklib__random_color();
extern "C" __sklib_color __sklib__random_rgb_color__int(int alpha);
extern "C" int __sklib__red_of__color(__sklib_color c);
extern "C" __sklib_color __sklib__rgb_color__float__float__float(float red, float green, float blue);
extern "C" __sklib_color __sklib__rgb_color__int__int__int(int red, int green, int blue);
extern "C" __sklib_color __sklib__rgba_color__float__float__float__float(float red, float green, float blue, float alpha);
extern "C" __sklib_color __sklib__rgba_color__int__int__int__int(int red, int green, int blue, int alpha);
extern "C" float __sklib__saturation_of__color(__sklib_color c);
extern "C" __sklib_color __sklib__string_to_color__string(__sklib_string str);
extern "C" __sklib_database __sklib__database_named__string(__sklib_string name);
extern "C" void __sklib__free_all_databases();
extern "C" void __sklib__free_all_query_results();
extern "C" void __sklib__free_database__database(__sklib_database db_to_close);
extern "C" void __sklib__free_database__string(__sklib_string name_of_db_to_close);
extern "C" void __sklib__free_query_result__query_result(__sklib_query_result query);
extern "C" int __sklib__get_next_row__query_result(__sklib_query_result result);
extern "C" int __sklib__has_database__string(__sklib_string name);
extern "C" int __sklib__has_row__query_result(__sklib_query_result result);
extern "C" __sklib_database __sklib__open_database__string__string(__sklib_string name, __sklib_string filename);
extern "C" int __sklib__query_column_for_bool__query_result__int(__sklib_query_result result, int col);
extern "C" double __sklib__query_column_for_double__query_result__int(__sklib_query_result result, int col);
extern "C" int __sklib__query_column_for_int__query_result__int(__sklib_query_result result, int col);
extern "C" __sklib_string __sklib__query_column_for_string__query_result__int(__sklib_query_result result, int col);
extern "C" int __sklib__query_success__query_result(__sklib_query_result result);
extern "C" __sklib_string __sklib__query_type_of_col__query_result__int(__sklib_query_result result, int col);
extern "C" void __sklib__reset_query_result__query_result(__sklib_query_result result);
extern "C" int __sklib__rows_changed__database(__sklib_database db);
extern "C" __sklib_query_result __sklib__run_sql__database__string(__sklib_database db, __sklib_string sql);
extern "C" __sklib_query_result __sklib__run_sql__string__string(__sklib_string database_name, __sklib_string sql);
extern "C" __sklib_drawing_options __sklib__option_defaults();
extern "C" __sklib_drawing_options __sklib__option_draw_to__bitmap(__sklib_bitmap dest);
extern "C" __sklib_drawing_options __sklib__option_draw_to__bitmap__drawing_options(__sklib_bitmap dest, __sklib_drawing_options opts);
extern "C" __sklib_drawing_options __sklib__option_draw_to__window(__sklib_window dest);
extern "C" __sklib_drawing_options __sklib__option_draw_to__window__drawing_options(__sklib_window dest, __sklib_drawing_options opts);
extern "C" __sklib_drawing_options __sklib__option_flip_x();
extern "C" __sklib_drawing_options __sklib__option_flip_x__drawing_options(__sklib_drawing_options opts);
extern "C" __sklib_drawing_options __sklib__option_flip_xy();
extern "C" __sklib_drawing_options __sklib__option_flip_xy__drawing_options(__sklib_drawing_options opts);
extern "C" __sklib_drawing_options __sklib__option_flip_y();
extern "C" __sklib_drawing_options __sklib__option_flip_y__drawing_options(__sklib_drawing_options opts);
extern "C" __sklib_drawing_options __sklib__option_line_width__int(int width);
extern "C" __sklib_drawing_options __sklib__option_line_width__int__drawing_options(int width, __sklib_drawing_options opts);
extern "C" __sklib_drawing_options __sklib__option_part_bmp__float__float__float__float(float x, float y, float w, float h);
extern "C" __sklib_drawing_options __sklib__option_part_bmp__float__float__float__float__drawing_options(float x, float y, float w, float h, __sklib_drawing_options opts);
extern "C" __sklib_drawing_options __sklib__option_part_bmp__rectangle(__sklib_rectangle part);
extern "C" __sklib_drawing_options __sklib__option_part_bmp__rectangle__drawing_options(__sklib_rectangle part, __sklib_drawing_options opts);
extern "C" __sklib_drawing_options __sklib__option_rotate_bmp__float(float angle);
extern "C" __sklib_drawing_options __sklib__option_rotate_bmp__float__drawing_options(float angle, __sklib_drawing_options opts);
extern "C" __sklib_drawing_options __sklib__option_rotate_bmp__float__float__float(float angle, float anchor_x, float anchor_y);
extern "C" __sklib_drawing_options __sklib__option_rotate_bmp__float__float__float__drawing_options(float angle, float anchor_x, float anchor_y, __sklib_drawing_options opts);
extern "C" __sklib_drawing_options __sklib__option_scale_bmp__float__float(float scale_x, float scale_y);
extern "C" __sklib_drawing_options __sklib__option_scale_bmp__float__float__drawing_options(float scale_x, float scale_y, __sklib_drawing_options opts);
extern "C" __sklib_drawing_options __sklib__option_to_screen();
extern "C" __sklib_drawing_options __sklib__option_to_screen__drawing_options(__sklib_drawing_options opts);
extern "C" __sklib_drawing_options __sklib__option_to_world();
extern "C" __sklib_drawing_options __sklib__option_to_world__drawing_options(__sklib_drawing_options opts);
extern "C" __sklib_drawing_options __sklib__option_with_animation__animation(__sklib_animation anim);
extern "C" __sklib_drawing_options __sklib__option_with_animation__animation__drawing_options(__sklib_animation anim, __sklib_drawing_options opts);
extern "C" void __sklib__draw_ellipse__color__rectangle(__sklib_color clr, const __sklib_rectangle rect);
extern "C" void __sklib__draw_ellipse__color__rectangle__drawing_options(__sklib_color clr, const __sklib_rectangle rect, __sklib_drawing_options opts);
extern "C" void __sklib__draw_ellipse__color__float__float__float__float(__sklib_color clr, float x, float y, float width, float height);
extern "C" void __sklib__draw_ellipse__color__float__float__float__float__drawing_options(__sklib_color clr, float x, float y, float width, float height, __sklib_drawing_options opts);
extern "C" void __sklib__fill_ellipse__color__rectangle(__sklib_color clr, const __sklib_rectangle rect);
extern "C" void __sklib__fill_ellipse__color__rectangle__drawing_options(__sklib_color clr, const __sklib_rectangle rect, __sklib_drawing_options opts);
extern "C" void __sklib__fill_ellipse__color__float__float__float__float(__sklib_color clr, float x, float y, float width, float height);
extern "C" void __sklib__fill_ellipse__color__float__float__float__float__drawing_options(__sklib_color clr, float x, float y, float width, float height, __sklib_drawing_options opts);
extern "C" float __sklib__cosine__float(float degrees);
extern "C" float __sklib__sine__float(float degrees);
extern "C" float __sklib__tangent__float(float degrees);
extern "C" void __sklib__clear_screen();
extern "C" void __sklib__clear_screen__color(__sklib_color clr);
extern "C" __sklib_display __sklib__display_details__unsigned_int(unsigned int index);
extern "C" int __sklib__display_height__display(__sklib_display disp);
extern "C" __sklib_string __sklib__display_name__display(__sklib_display disp);
extern "C" int __sklib__display_width__display(__sklib_display disp);
extern "C" int __sklib__display_x__display(__sklib_display disp);
extern "C" int __sklib__display_y__display(__sklib_display disp);
extern "C" int __sklib__number_of_displays();
extern "C" void __sklib__refresh_screen();
extern "C" void __sklib__refresh_screen__unsigned_int(unsigned int target_fps);
extern "C" void __sklib__save_bitmap__bitmap__string_ref(__sklib_bitmap bmp, const __sklib_string basename);
extern "C" int __sklib__screen_height();
extern "C" int __sklib__screen_width();
extern "C" void __sklib__take_screenshot__string_ref(const __sklib_string basename);
extern "C" void __sklib__take_screenshot__window__string_ref(__sklib_window wind, const __sklib_string basename);
extern "C" __sklib_point_2d __sklib__bitmap_cell_center__bitmap(__sklib_bitmap bmp);
extern "C" __sklib_circle __sklib__bitmap_cell_circle__bitmap__float__float(__sklib_bitmap bmp, float x, float y);
extern "C" __sklib_circle __sklib__bitmap_cell_circle__bitmap__point_2d(__sklib_bitmap bmp, const __sklib_point_2d pt);
extern "C" __sklib_circle __sklib__bitmap_cell_circle__bitmap__point_2d__float(__sklib_bitmap bmp, const __sklib_point_2d pt, float scale);
extern "C" int __sklib__bitmap_cell_columns__bitmap(__sklib_bitmap bmp);
extern "C" int __sklib__bitmap_cell_count__bitmap(__sklib_bitmap bmp);
extern "C" int __sklib__bitmap_cell_height__bitmap(__sklib_bitmap bmp);
extern "C" __sklib_vector_2d __sklib__bitmap_cell_offset__bitmap__int(__sklib_bitmap src, int cell);
extern "C" __sklib_rectangle __sklib__bitmap_cell_rectangle__bitmap(__sklib_bitmap src);
extern "C" __sklib_rectangle __sklib__bitmap_cell_rectangle__bitmap__point_2d_ref(__sklib_bitmap src, const __sklib_point_2d pt);
extern "C" int __sklib__bitmap_cell_rows__bitmap(__sklib_bitmap bmp);
extern "C" int __sklib__bitmap_cell_width__bitmap(__sklib_bitmap bmp);
extern "C" __sklib_point_2d __sklib__bitmap_center__bitmap(__sklib_bitmap bmp);
extern "C" __sklib_circle __sklib__bitmap_circle__bitmap__point_2d_ref(__sklib_bitmap bmp, const __sklib_point_2d pt);
extern "C" __sklib_string __sklib__bitmap_filename__bitmap(__sklib_bitmap bmp);
extern "C" int __sklib__bitmap_height__bitmap(__sklib_bitmap bmp);
extern "C" int __sklib__bitmap_height__string(__sklib_string name);
extern "C" __sklib_string __sklib__bitmap_name__bitmap(__sklib_bitmap bmp);
extern "C" __sklib_bitmap __sklib__bitmap_named__string(__sklib_string name);
extern "C" __sklib_rectangle __sklib__bitmap_rectangle__bitmap(__sklib_bitmap bmp);
extern "C" __sklib_rectangle __sklib__bitmap_rectangle__bitmap__float__float(__sklib_bitmap bmp, float x, float y);
extern "C" __sklib_rectangle __sklib__bitmap_rectangle_of_cell__bitmap__int(__sklib_bitmap src, int cell);
extern "C" void __sklib__bitmap_set_cell_details__bitmap__int__int__int__int__int(__sklib_bitmap bmp, int width, int height, int columns, int rows, int count);
extern "C" int __sklib__bitmap_width__bitmap(__sklib_bitmap bmp);
extern "C" int __sklib__bitmap_width__string(__sklib_string name);
extern "C" void __sklib__clear_bitmap__bitmap__color(__sklib_bitmap bmp, __sklib_color clr);
extern "C" void __sklib__clear_bitmap__string__color(__sklib_string name, __sklib_color clr);
extern "C" __sklib_bitmap __sklib__create_bitmap__string__int__int(__sklib_string name, int width, int height);
extern "C" void __sklib__draw_bitmap__bitmap__float__float(__sklib_bitmap bmp, float x, float y);
extern "C" void __sklib__draw_bitmap__bitmap__float__float__drawing_options(__sklib_bitmap bmp, float x, float y, __sklib_drawing_options opts);
extern "C" void __sklib__draw_bitmap__string__float__float(__sklib_string name, float x, float y);
extern "C" void __sklib__draw_bitmap__string__float__float__drawing_options(__sklib_string name, float x, float y, __sklib_drawing_options opts);
extern "C" void __sklib__free_all_bitmaps();
extern "C" void __sklib__free_bitmap__bitmap(__sklib_bitmap to_delete);
extern "C" int __sklib__has_bitmap__string(__sklib_string name);
extern "C" __sklib_bitmap __sklib__load_bitmap__string__string(__sklib_string name, __sklib_string filename);
extern "C" int __sklib__pixel_drawn_at_point__bitmap__point_2d_ref(__sklib_bitmap bmp, const __sklib_point_2d pt);
extern "C" int __sklib__pixel_drawn_at_point__bitmap__float__float(__sklib_bitmap bmp, float x, float y);
extern "C" int __sklib__pixel_drawn_at_point__bitmap__int__point_2d_ref(__sklib_bitmap bmp, int cell, const __sklib_point_2d pt);
extern "C" int __sklib__pixel_drawn_at_point__bitmap__int__float__float(__sklib_bitmap bmp, int cell, float x, float y);
extern "C" void __sklib__process_events();
extern "C" int __sklib__quit_requested();
extern "C" void __sklib__reset_quit();
extern "C" __sklib_json __sklib__create_json();
extern "C" __sklib_json __sklib__create_json__string(__sklib_string json_string);
extern "C" void __sklib__free_all_json();
extern "C" void __sklib__free_json__json(__sklib_json j);
extern "C" int __sklib__json_count_keys__json(__sklib_json j);
extern "C" __sklib_json __sklib__json_from_color__color(__sklib_color clr);
extern "C" __sklib_json __sklib__json_from_file__string_ref(const __sklib_string filename);
extern "C" __sklib_json __sklib__json_from_string__string_ref(const __sklib_string j_string);
extern "C" int __sklib__json_has_key__json__string(__sklib_json j, __sklib_string key);
extern "C" void __sklib__json_read_array__json__string__vector_double_ref(__sklib_json j, __sklib_string key, __sklib_vector_double *out);
extern "C" void __sklib__json_read_array__json__string__vector_json_ref(__sklib_json j, __sklib_string key, __sklib_vector_json *out);
extern "C" void __sklib__json_read_array__json__string__vector_string_ref(__sklib_json j, __sklib_string key, __sklib_vector_string *out);
extern "C" void __sklib__json_read_array__json__string__vector_bool_ref(__sklib_json j, __sklib_string key, __sklib_vector_bool *out);
extern "C" int __sklib__json_read_bool__json__string(__sklib_json j, __sklib_string key);
extern "C" float __sklib__json_read_number__json__string(__sklib_json j, __sklib_string key);
extern "C" double __sklib__json_read_number_as_double__json__string(__sklib_json j, __sklib_string key);
extern "C" int __sklib__json_read_number_as_int__json__string(__sklib_json j, __sklib_string key);
extern "C" __sklib_json __sklib__json_read_object__json__string(__sklib_json j, __sklib_string key);
extern "C" __sklib_string __sklib__json_read_string__json__string(__sklib_json j, __sklib_string key);
extern "C" void __sklib__json_set_array__json__string__vector_string(__sklib_json j, __sklib_string key, __sklib_vector_string value);
extern "C" void __sklib__json_set_array__json__string__vector_double(__sklib_json j, __sklib_string key, __sklib_vector_double value);
extern "C" void __sklib__json_set_array__json__string__vector_bool(__sklib_json j, __sklib_string key, __sklib_vector_bool value);
extern "C" void __sklib__json_set_array__json__string__vector_json(__sklib_json j, __sklib_string key, __sklib_vector_json value);
extern "C" void __sklib__json_set_bool__json__string__bool(__sklib_json j, __sklib_string key, int value);
extern "C" void __sklib__json_set_number__json__string__int(__sklib_json j, __sklib_string key, int value);
extern "C" void __sklib__json_set_number__json__string__double(__sklib_json j, __sklib_string key, double value);
extern "C" void __sklib__json_set_number__json__string__float(__sklib_json j, __sklib_string key, float value);
extern "C" void __sklib__json_set_object__json__string__json(__sklib_json j, __sklib_string key, __sklib_json object);
extern "C" void __sklib__json_set_string__json__string__string(__sklib_json j, __sklib_string key, __sklib_string value);
extern "C" __sklib_color __sklib__json_to_color__json(__sklib_json j);
extern "C" void __sklib__json_to_file__json__string_ref(__sklib_json j, const __sklib_string filename);
extern "C" __sklib_string __sklib__json_to_string__json(__sklib_json j);
extern "C" int __sklib__any_key_pressed();
extern "C" void __sklib__deregister_callback_on_key_down__key_callback_ptr(__sklib_key_callback *callback);
extern "C" void __sklib__deregister_callback_on_key_typed__key_callback_ptr(__sklib_key_callback *callback);
extern "C" void __sklib__deregister_callback_on_key_up__key_callback_ptr(__sklib_key_callback *callback);
extern "C" int __sklib__key_down__key_code(int key);
extern "C" __sklib_string __sklib__key_name__key_code(int key);
extern "C" int __sklib__key_released__key_code(int key);
extern "C" int __sklib__key_typed__key_code(int key);
extern "C" int __sklib__key_up__key_code(int key);
extern "C" void __sklib__register_callback_on_key_down__key_callback_ptr(__sklib_key_callback *callback);
extern "C" void __sklib__register_callback_on_key_typed__key_callback_ptr(__sklib_key_callback *callback);
extern "C" void __sklib__register_callback_on_key_up__key_callback_ptr(__sklib_key_callback *callback);
extern "C" void __sklib__draw_line__color__line_ref(__sklib_color clr, const __sklib_line l);
extern "C" void __sklib__draw_line__color__line_ref__drawing_options(__sklib_color clr, const __sklib_line l, __sklib_drawing_options opts);
extern "C" void __sklib__draw_line__color__point_2d_ref__point_2d_ref(__sklib_color clr, const __sklib_point_2d from_pt, const __sklib_point_2d to_pt);
extern "C" void __sklib__draw_line__color__point_2d_ref__point_2d_ref__drawing_options_ref(__sklib_color clr, const __sklib_point_2d from_pt, const __sklib_point_2d to_pt, const __sklib_drawing_options opts);
extern "C" void __sklib__draw_line__color__float__float__float__float(__sklib_color clr, float x1, float y1, float x2, float y2);
extern "C" void __sklib__draw_line__color__float__float__float__float__drawing_options_ref(__sklib_color clr, float x1, float y1, float x2, float y2, const __sklib_drawing_options opts);
extern "C" __sklib_point_2d __sklib__closest_point_on_line__point_2d__line_ref(const __sklib_point_2d from_pt, const __sklib_line l);
extern "C" __sklib_point_2d __sklib__closest_point_on_lines__point_2d__vector_line_ref__int_ref(const __sklib_point_2d from_pt, const __sklib_vector_line lines, int *line_idx);
extern "C" __sklib_line __sklib__line_from__point_2d_ref__point_2d_ref(const __sklib_point_2d start, const __sklib_point_2d end);
extern "C" __sklib_line __sklib__line_from__point_2d_ref__vector_2d_ref(const __sklib_point_2d start, const __sklib_vector_2d offset);
extern "C" __sklib_line __sklib__line_from__vector_2d_ref(const __sklib_vector_2d v);
extern "C" __sklib_line __sklib__line_from__float__float__float__float(float x1, float y1, float x2, float y2);
extern "C" int __sklib__line_intersection_point__line_ref__line_ref__point_2d_ref(const __sklib_line line1, const __sklib_line line2, __sklib_point_2d *pt);
extern "C" int __sklib__line_intersects_circle__line_ref__circle_ref(const __sklib_line l, const __sklib_circle c);
extern "C" int __sklib__line_intersects_lines__line_ref__vector_line_ref(const __sklib_line l, const __sklib_vector_line lines);
extern "C" int __sklib__line_intersects_rect__line_ref__rectangle_ref(const __sklib_line l, const __sklib_rectangle rect);
extern "C" float __sklib__line_length__line_ref(const __sklib_line l);
extern "C" float __sklib__line_length_squared__line_ref(const __sklib_line l);
extern "C" __sklib_point_2d __sklib__line_mid_point__line_ref(const __sklib_line l);
extern "C" __sklib_vector_2d __sklib__line_normal__line_ref(const __sklib_line l);
extern "C" __sklib_string __sklib__line_to_string__line_ref(const __sklib_line ln);
extern "C" __sklib_vector_line __sklib__lines_from__rectangle_ref(const __sklib_rectangle rect);
extern "C" __sklib_vector_line __sklib__lines_from__triangle_ref(const __sklib_triangle t);
extern "C" int __sklib__lines_intersect__line_ref__line_ref(const __sklib_line l1, const __sklib_line l2);
extern "C" void __sklib__apply_matrix__matrix_2d_ref__quad_ref(const __sklib_matrix_2d matrix, __sklib_quad *q);
extern "C" void __sklib__apply_matrix__matrix_2d_ref__triangle_ref(const __sklib_matrix_2d m, __sklib_triangle *tri);
extern "C" __sklib_matrix_2d __sklib__identity_matrix();
extern "C" __sklib_matrix_2d __sklib__matrix_inverse__matrix_2d_ref(const __sklib_matrix_2d m);
extern "C" __sklib_point_2d __sklib__matrix_multiply__matrix_2d_ref__point_2d_ref(const __sklib_matrix_2d m, const __sklib_point_2d pt);
extern "C" __sklib_matrix_2d __sklib__matrix_multiply__matrix_2d_ref__matrix_2d_ref(const __sklib_matrix_2d m1, const __sklib_matrix_2d m2);
extern "C" __sklib_vector_2d __sklib__matrix_multiply__matrix_2d_ref__vector_2d_ref(const __sklib_matrix_2d m, const __sklib_vector_2d v);
extern "C" __sklib_string __sklib__matrix_to_string__matrix_2d_ref(const __sklib_matrix_2d matrix);
extern "C" __sklib_matrix_2d __sklib__rotation_matrix__float(float deg);
extern "C" __sklib_matrix_2d __sklib__scale_matrix__point_2d_ref(const __sklib_point_2d scale);
extern "C" __sklib_matrix_2d __sklib__scale_matrix__float(float scale);
extern "C" __sklib_matrix_2d __sklib__scale_rotate_translate_matrix__point_2d_ref__float__point_2d_ref(const __sklib_point_2d scale, float deg, const __sklib_point_2d translate);
extern "C" __sklib_matrix_2d __sklib__translation_matrix__point_2d_ref(const __sklib_point_2d pt);
extern "C" __sklib_matrix_2d __sklib__translation_matrix__float__float(float dx, float dy);
extern "C" void __sklib__hide_mouse();
extern "C" int __sklib__mouse_clicked__mouse_button(int button);
extern "C" int __sklib__mouse_down__mouse_button(int button);
extern "C" __sklib_vector_2d __sklib__mouse_movement();
extern "C" __sklib_point_2d __sklib__mouse_position();
extern "C" __sklib_vector_2d __sklib__mouse_position_vector();
extern "C" int __sklib__mouse_shown();
extern "C" int __sklib__mouse_up__mouse_button(int button);
extern "C" __sklib_vector_2d __sklib__mouse_wheel_scroll();
extern "C" float __sklib__mouse_x();
extern "C" float __sklib__mouse_y();
extern "C" void __sklib__move_mouse__float__float(float x, float y);
extern "C" void __sklib__move_mouse__point_2d(__sklib_point_2d point);
extern "C" void __sklib__show_mouse();
extern "C" void __sklib__show_mouse__bool(int show);
extern "C" void __sklib__fade_music_in__string_ref__int(const __sklib_string name, int ms);
extern "C" void __sklib__fade_music_in__string_ref__int__int(const __sklib_string name, int times, int ms);
extern "C" void __sklib__fade_music_in__music__int(__sklib_music data, int ms);
extern "C" void __sklib__fade_music_in__music__int__int(__sklib_music data, int times, int ms);
extern "C" void __sklib__fade_music_out__int(int ms);
extern "C" void __sklib__free_all_music();
extern "C" void __sklib__free_music__music(__sklib_music effect);
extern "C" int __sklib__has_music__string_ref(const __sklib_string name);
extern "C" __sklib_music __sklib__load_music__string_ref__string_ref(const __sklib_string name, const __sklib_string filename);
extern "C" __sklib_string __sklib__music_filename__music(__sklib_music data);
extern "C" __sklib_string __sklib__music_name__music(__sklib_music data);
extern "C" __sklib_music __sklib__music_named__string_ref(const __sklib_string name);
extern "C" int __sklib__music_playing();
extern "C" float __sklib__music_volume();
extern "C" void __sklib__pause_music();
extern "C" void __sklib__play_music__string_ref(const __sklib_string name);
extern "C" void __sklib__play_music__string_ref__int(const __sklib_string name, int times);
extern "C" void __sklib__play_music__music(__sklib_music data);
extern "C" void __sklib__play_music__music__int(__sklib_music data, int times);
extern "C" void __sklib__play_music__music__int__float(__sklib_music data, int times, float volume);
extern "C" void __sklib__resume_music();
extern "C" void __sklib__set_music_volume__float(float volume);
extern "C" void __sklib__stop_music();
extern "C" __sklib_string __sklib__dec_to_hex__unsigned_int(unsigned int a_dec);
extern "C" __sklib_string __sklib__hex_str_to_ipv4__string_ref(const __sklib_string a_hex);
extern "C" __sklib_string __sklib__hex_to_dec_string__string_ref(const __sklib_string a_hex);
extern "C" unsigned int __sklib__ipv4_to_dec__string_ref(const __sklib_string a_ip);
extern "C" __sklib_string __sklib__ipv4_to_hex__string_ref(const __sklib_string a_ip);
extern "C" __sklib_string __sklib__ipv4_to_str__unsigned_int(unsigned int ip);
extern "C" __sklib_string __sklib__my_ip();
extern "C" void __sklib__draw_pixel__color__point_2d_ref(__sklib_color clr, const __sklib_point_2d pt);
extern "C" void __sklib__draw_pixel__color__point_2d_ref__drawing_options(__sklib_color clr, const __sklib_point_2d pt, __sklib_drawing_options opts);
extern "C" void __sklib__draw_pixel__color__float__float(__sklib_color clr, float x, float y);
extern "C" void __sklib__draw_pixel__color__float__float__drawing_options(__sklib_color clr, float x, float y, __sklib_drawing_options opts);
extern "C" __sklib_color __sklib__get_pixel__bitmap__point_2d_ref(__sklib_bitmap bmp, const __sklib_point_2d pt);
extern "C" __sklib_color __sklib__get_pixel__bitmap__float__float(__sklib_bitmap bmp, float x, float y);
extern "C" __sklib_color __sklib__get_pixel__point_2d_ref(const __sklib_point_2d pt);
extern "C" __sklib_color __sklib__get_pixel__float__float(float x, float y);
extern "C" __sklib_color __sklib__get_pixel__window__point_2d_ref(__sklib_window wnd, const __sklib_point_2d pt);
extern "C" __sklib_color __sklib__get_pixel__window__float__float(__sklib_window wnd, float x, float y);
extern "C" __sklib_point_2d __sklib__point_at__float__float(float x, float y);
extern "C" __sklib_point_2d __sklib__point_at_origin();
extern "C" int __sklib__point_in_circle__point_2d_ref__circle_ref(const __sklib_point_2d pt, const __sklib_circle c);
extern "C" int __sklib__point_in_quad__point_2d_ref__quad_ref(const __sklib_point_2d pt, const __sklib_quad q);
extern "C" int __sklib__point_in_rectangle__point_2d_ref__rectangle_ref(const __sklib_point_2d pt, const __sklib_rectangle rect);
extern "C" int __sklib__point_in_triangle__point_2d_ref__triangle_ref(const __sklib_point_2d pt, const __sklib_triangle tri);
extern "C" float __sklib__point_line_distance__point_2d_ref__line_ref(const __sklib_point_2d pt, const __sklib_line l);
extern "C" __sklib_point_2d __sklib__point_offset_by__point_2d_ref__vector_2d_ref(const __sklib_point_2d start_point, const __sklib_vector_2d offset);
extern "C" __sklib_point_2d __sklib__point_offset_from_origin__vector_2d_ref(const __sklib_vector_2d offset);
extern "C" int __sklib__point_on_line__point_2d_ref__line_ref(const __sklib_point_2d pt, const __sklib_line l);
extern "C" int __sklib__point_on_line__point_2d_ref__line_ref__float(const __sklib_point_2d pt, const __sklib_line l, float proximity);
extern "C" float __sklib__point_point_angle__point_2d_ref__point_2d_ref(const __sklib_point_2d pt1, const __sklib_point_2d pt2);
extern "C" float __sklib__point_point_distance__point_2d_ref__point_2d_ref(const __sklib_point_2d pt1, const __sklib_point_2d pt2);
extern "C" __sklib_string __sklib__point_to_string__point_2d_ref(const __sklib_point_2d pt);
extern "C" __sklib_point_2d __sklib__random_bitmap_point__bitmap(__sklib_bitmap bmp);
extern "C" __sklib_point_2d __sklib__random_screen_point();
extern "C" __sklib_point_2d __sklib__random_window_point__window(__sklib_window wind);
extern "C" int __sklib__same_point__point_2d_ref__point_2d_ref(const __sklib_point_2d pt1, const __sklib_point_2d pt2);
extern "C" __sklib_quad __sklib__quad_from__point_2d_ref__point_2d_ref__point_2d_ref__point_2d_ref(const __sklib_point_2d p1, const __sklib_point_2d p2, const __sklib_point_2d p3, const __sklib_point_2d p4);
extern "C" __sklib_quad __sklib__quad_from__rectangle_ref(const __sklib_rectangle rect);
extern "C" __sklib_quad __sklib__quad_from__rectangle_ref__matrix_2d_ref(const __sklib_rectangle rect, const __sklib_matrix_2d transform);
extern "C" __sklib_quad __sklib__quad_from__float__float__float__float__float__float__float__float(float x_top_left, float y_top_left, float x_top_right, float y_top_right, float x_bottom_left, float y_bottom_left, float x_bottom_right, float y_bottom_right);
extern "C" int __sklib__quads_intersect__quad_ref__quad_ref(const __sklib_quad q1, const __sklib_quad q2);
extern "C" void __sklib__set_quad_point__quad_ref__int__point_2d_ref(__sklib_quad *q, int idx, const __sklib_point_2d value);
extern "C" __sklib_vector_triangle __sklib__triangles_from__quad_ref(const __sklib_quad q);
extern "C" float __sklib__rnd();
extern "C" int __sklib__rnd__int(int ubound);
extern "C" void __sklib__draw_quad__color__quad_ref(__sklib_color clr, const __sklib_quad q);
extern "C" void __sklib__draw_quad__color__quad_ref__drawing_options_ref(__sklib_color clr, const __sklib_quad q, const __sklib_drawing_options opts);
extern "C" void __sklib__draw_rectangle__color__rectangle_ref(__sklib_color clr, const __sklib_rectangle rect);
extern "C" void __sklib__draw_rectangle__color__rectangle_ref__drawing_options_ref(__sklib_color clr, const __sklib_rectangle rect, const __sklib_drawing_options opts);
extern "C" void __sklib__draw_rectangle__color__float__float__float__float(__sklib_color clr, float x, float y, float width, float height);
extern "C" void __sklib__draw_rectangle__color__float__float__float__float__drawing_options_ref(__sklib_color clr, float x, float y, float width, float height, const __sklib_drawing_options opts);
extern "C" void __sklib__fill_quad__color__quad_ref(__sklib_color clr, const __sklib_quad q);
extern "C" void __sklib__fill_quad__color__quad_ref__drawing_options_ref(__sklib_color clr, const __sklib_quad q, const __sklib_drawing_options opts);
extern "C" void __sklib__fill_rectangle__color__rectangle_ref(__sklib_color clr, const __sklib_rectangle rect);
extern "C" void __sklib__fill_rectangle__color__rectangle_ref__drawing_options_ref(__sklib_color clr, const __sklib_rectangle rect, const __sklib_drawing_options opts);
extern "C" void __sklib__fill_rectangle__color__float__float__float__float(__sklib_color clr, float x, float y, float width, float height);
extern "C" void __sklib__fill_rectangle__color__float__float__float__float__drawing_options_ref(__sklib_color clr, float x, float y, float width, float height, const __sklib_drawing_options opts);
extern "C" __sklib_rectangle __sklib__inset_rectangle__rectangle_ref__float(const __sklib_rectangle rect, float inset_amount);
extern "C" __sklib_rectangle __sklib__intersection__rectangle_ref__rectangle_ref(const __sklib_rectangle rect1, const __sklib_rectangle rect2);
extern "C" __sklib_rectangle __sklib__rectangle_around__triangle_ref(const __sklib_triangle t);
extern "C" __sklib_rectangle __sklib__rectangle_around__circle_ref(const __sklib_circle c);
extern "C" __sklib_rectangle __sklib__rectangle_around__line_ref(const __sklib_line l);
extern "C" float __sklib__rectangle_bottom__rectangle_ref(const __sklib_rectangle rect);
extern "C" __sklib_point_2d __sklib__rectangle_center__rectangle_ref(const __sklib_rectangle rect);
extern "C" __sklib_rectangle __sklib__rectangle_from__point_2d__float__float(const __sklib_point_2d pt, const float width, const float height);
extern "C" __sklib_rectangle __sklib__rectangle_from__point_2d__point_2d(const __sklib_point_2d pt1, const __sklib_point_2d pt2);
extern "C" __sklib_rectangle __sklib__rectangle_from__float__float__float__float(float x, float y, float width, float height);
extern "C" float __sklib__rectangle_left__rectangle_ref(const __sklib_rectangle rect);
extern "C" __sklib_rectangle __sklib__rectangle_offset_by__rectangle_ref__vector_2d_ref(const __sklib_rectangle rect, const __sklib_vector_2d offset);
extern "C" float __sklib__rectangle_right__rectangle_ref(const __sklib_rectangle rect);
extern "C" __sklib_string __sklib__rectangle_to_string__rectangle_ref(const __sklib_rectangle rect);
extern "C" float __sklib__rectangle_top__rectangle_ref(const __sklib_rectangle rect);
extern "C" int __sklib__rectangles_intersect__rectangle_ref__rectangle_ref(const __sklib_rectangle rect1, const __sklib_rectangle rect2);
extern "C" void __sklib__deregister_free_notifier__free_notifier_ptr(__sklib_free_notifier *handler);
extern "C" __sklib_string __sklib__path_to_resource__string_ref__resource_kind(const __sklib_string filename, int kind);
extern "C" __sklib_string __sklib__path_to_resources();
extern "C" __sklib_string __sklib__path_to_resources__resource_kind(int kind);
extern "C" void __sklib__register_free_notifier__free_notifier_ptr(__sklib_free_notifier *fn);
extern "C" void __sklib__set_resources_path__string_ref(const __sklib_string path);
extern "C" void __sklib__fade_all_sound_effects_out__int(int ms);
extern "C" void __sklib__fade_sound_effect_out__sound_effect__int(__sklib_sound_effect effect, int ms);
extern "C" void __sklib__free_all_sound_effects();
extern "C" void __sklib__free_sound_effect__sound_effect(__sklib_sound_effect effect);
extern "C" int __sklib__has_sound_effect__string_ref(const __sklib_string name);
extern "C" __sklib_sound_effect __sklib__load_sound_effect__string_ref__string_ref(const __sklib_string name, const __sklib_string filename);
extern "C" void __sklib__play_sound_effect__string_ref(const __sklib_string name);
extern "C" void __sklib__play_sound_effect__string_ref__float(const __sklib_string name, float volume);
extern "C" void __sklib__play_sound_effect__string_ref__int(const __sklib_string name, int times);
extern "C" void __sklib__play_sound_effect__string_ref__int__float(const __sklib_string name, int times, float volume);
extern "C" void __sklib__play_sound_effect__sound_effect(__sklib_sound_effect effect);
extern "C" void __sklib__play_sound_effect__sound_effect__float(__sklib_sound_effect effect, float volume);
extern "C" void __sklib__play_sound_effect__sound_effect__int(__sklib_sound_effect effect, int times);
extern "C" void __sklib__play_sound_effect__sound_effect__int__float(__sklib_sound_effect effect, int times, float volume);
extern "C" __sklib_string __sklib__sound_effect_filename__sound_effect(__sklib_sound_effect effect);
extern "C" __sklib_string __sklib__sound_effect_name__sound_effect(__sklib_sound_effect effect);
extern "C" __sklib_sound_effect __sklib__sound_effect_named__string_ref(const __sklib_string name);
extern "C" int __sklib__sound_effect_playing__string_ref(const __sklib_string name);
extern "C" int __sklib__sound_effect_playing__sound_effect(__sklib_sound_effect effect);
extern "C" void __sklib__stop_sound_effect__string_ref(const __sklib_string name);
extern "C" void __sklib__stop_sound_effect__sound_effect(__sklib_sound_effect effect);
extern "C" void __sklib__call_for_all_sprites__sprite_float_function_ptr__float(__sklib_sprite_float_function *fn, float val);
extern "C" void __sklib__call_for_all_sprites__sprite_function_ptr(__sklib_sprite_function *fn);
extern "C" void __sklib__call_on_sprite_event__sprite_event_handler_ptr(__sklib_sprite_event_handler *handler);
extern "C" __sklib_point_2d __sklib__center_point__sprite(__sklib_sprite s);
extern "C" __sklib_sprite __sklib__create_sprite__bitmap(__sklib_bitmap layer);
extern "C" __sklib_sprite __sklib__create_sprite__bitmap__animation_script(__sklib_bitmap layer, __sklib_animation_script ani);
extern "C" __sklib_sprite __sklib__create_sprite__string_ref(const __sklib_string bitmap_name);
extern "C" __sklib_sprite __sklib__create_sprite__string_ref__bitmap(const __sklib_string name, __sklib_bitmap layer);
extern "C" __sklib_sprite __sklib__create_sprite__string_ref__bitmap__animation_script(const __sklib_string name, __sklib_bitmap layer, __sklib_animation_script ani);
extern "C" __sklib_sprite __sklib__create_sprite__string_ref__string_ref(const __sklib_string bitmap_name, const __sklib_string animation_name);
extern "C" void __sklib__create_sprite_pack__string_ref(const __sklib_string name);
extern "C" __sklib_string __sklib__current_sprite_pack();
extern "C" void __sklib__draw_all_sprites();
extern "C" void __sklib__draw_sprite__sprite__vector_2d_ref(__sklib_sprite s, const __sklib_vector_2d offset);
extern "C" void __sklib__draw_sprite__sprite(__sklib_sprite s);
extern "C" void __sklib__draw_sprite__sprite__float__float(__sklib_sprite s, float x_offset, float y_offset);
extern "C" void __sklib__free_all_sprites();
extern "C" void __sklib__free_sprite__sprite(__sklib_sprite s);
extern "C" void __sklib__free_sprite_pack__string_ref(const __sklib_string name);
extern "C" int __sklib__has_sprite__string_ref(const __sklib_string name);
extern "C" int __sklib__has_sprite_pack__string_ref(const __sklib_string name);
extern "C" void __sklib__move_sprite__sprite(__sklib_sprite s);
extern "C" void __sklib__move_sprite__sprite__vector_2d_ref(__sklib_sprite s, const __sklib_vector_2d distance);
extern "C" void __sklib__move_sprite__sprite__vector_2d_ref__float(__sklib_sprite s, const __sklib_vector_2d distance, float pct);
extern "C" void __sklib__move_sprite__sprite__float(__sklib_sprite s, float pct);
extern "C" void __sklib__move_sprite_to__sprite__float__float(__sklib_sprite s, float x, float y);
extern "C" void __sklib__select_sprite_pack__string_ref(const __sklib_string name);
extern "C" int __sklib__sprite_add_layer__sprite__bitmap__string_ref(__sklib_sprite s, __sklib_bitmap new_layer, const __sklib_string layer_name);
extern "C" void __sklib__sprite_add_to_velocity__sprite__vector_2d_ref(__sklib_sprite s, const __sklib_vector_2d value);
extern "C" void __sklib__sprite_add_value__sprite__string_ref(__sklib_sprite s, const __sklib_string name);
extern "C" void __sklib__sprite_add_value__sprite__string_ref__float(__sklib_sprite s, const __sklib_string name, float init_val);
extern "C" __sklib_point_2d __sklib__sprite_anchor_point__sprite(__sklib_sprite s);
extern "C" __sklib_point_2d __sklib__sprite_anchor_position__sprite(__sklib_sprite s);
extern "C" int __sklib__sprite_animation_has_ended__sprite(__sklib_sprite s);
extern "C" __sklib_string __sklib__sprite_animation_name__sprite(__sklib_sprite s);
extern "C" int __sklib__sprite_at__sprite__point_2d_ref(__sklib_sprite s, const __sklib_point_2d pt);
extern "C" void __sklib__sprite_bring_layer_forward__sprite__int(__sklib_sprite s, int visible_layer);
extern "C" void __sklib__sprite_bring_layer_to_front__sprite__int(__sklib_sprite s, int visible_layer);
extern "C" void __sklib__sprite_call_on_event__sprite__sprite_event_handler_ptr(__sklib_sprite s, __sklib_sprite_event_handler *handler);
extern "C" __sklib_circle __sklib__sprite_circle__sprite(__sklib_sprite s);
extern "C" __sklib_bitmap __sklib__sprite_collision_bitmap__sprite(__sklib_sprite s);
extern "C" __sklib_circle __sklib__sprite_collision_circle__sprite(__sklib_sprite s);
extern "C" int __sklib__sprite_collision_kind__sprite(__sklib_sprite s);
extern "C" __sklib_rectangle __sklib__sprite_collision_rectangle__sprite(__sklib_sprite s);
extern "C" int __sklib__sprite_current_cell__sprite(__sklib_sprite s);
extern "C" __sklib_rectangle __sklib__sprite_current_cell_rectangle__sprite(__sklib_sprite s);
extern "C" float __sklib__sprite_dx__sprite(__sklib_sprite s);
extern "C" float __sklib__sprite_dy__sprite(__sklib_sprite s);
extern "C" int __sklib__sprite_has_value__sprite__string(__sklib_sprite s, __sklib_string name);
extern "C" float __sklib__sprite_heading__sprite(__sklib_sprite s);
extern "C" int __sklib__sprite_height__sprite(__sklib_sprite s);
extern "C" void __sklib__sprite_hide_layer__sprite__string_ref(__sklib_sprite s, const __sklib_string name);
extern "C" void __sklib__sprite_hide_layer__sprite__int(__sklib_sprite s, int id);
extern "C" __sklib_bitmap __sklib__sprite_layer__sprite__string_ref(__sklib_sprite s, const __sklib_string name);
extern "C" __sklib_bitmap __sklib__sprite_layer__sprite__int(__sklib_sprite s, int idx);
extern "C" __sklib_circle __sklib__sprite_layer_circle__sprite__string_ref(__sklib_sprite s, const __sklib_string name);
extern "C" __sklib_circle __sklib__sprite_layer_circle__sprite__int(__sklib_sprite s, int idx);
extern "C" int __sklib__sprite_layer_count__sprite(__sklib_sprite s);
extern "C" int __sklib__sprite_layer_height__sprite__string_ref(__sklib_sprite s, const __sklib_string name);
extern "C" int __sklib__sprite_layer_height__sprite__int(__sklib_sprite s, int idx);
extern "C" int __sklib__sprite_layer_index__sprite__string_ref(__sklib_sprite s, const __sklib_string name);
extern "C" __sklib_string __sklib__sprite_layer_name__sprite__int(__sklib_sprite s, int idx);
extern "C" __sklib_vector_2d __sklib__sprite_layer_offset__sprite__string_ref(__sklib_sprite s, const __sklib_string name);
extern "C" __sklib_vector_2d __sklib__sprite_layer_offset__sprite__int(__sklib_sprite s, int idx);
extern "C" __sklib_rectangle __sklib__sprite_layer_rectangle__sprite__string_ref(__sklib_sprite s, const __sklib_string name);
extern "C" __sklib_rectangle __sklib__sprite_layer_rectangle__sprite__int(__sklib_sprite s, int idx);
extern "C" int __sklib__sprite_layer_width__sprite__string_ref(__sklib_sprite s, const __sklib_string name);
extern "C" int __sklib__sprite_layer_width__sprite__int(__sklib_sprite s, int idx);
extern "C" __sklib_matrix_2d __sklib__sprite_location_matrix__sprite(__sklib_sprite s);
extern "C" float __sklib__sprite_mass__sprite(__sklib_sprite s);
extern "C" int __sklib__sprite_move_from_anchor_point__sprite(__sklib_sprite s);
extern "C" void __sklib__sprite_move_to__sprite__point_2d_ref__float(__sklib_sprite s, const __sklib_point_2d pt, float taking_seconds);
extern "C" __sklib_string __sklib__sprite_name__sprite(__sklib_sprite s);
extern "C" __sklib_sprite __sklib__sprite_named__string_ref(const __sklib_string name);
extern "C" int __sklib__sprite_offscreen__sprite(__sklib_sprite s);
extern "C" int __sklib__sprite_on_screen_at__sprite__point_2d_ref(__sklib_sprite s, const __sklib_point_2d pt);
extern "C" int __sklib__sprite_on_screen_at__sprite__float__float(__sklib_sprite s, float x, float y);
extern "C" __sklib_point_2d __sklib__sprite_position__sprite(__sklib_sprite s);
extern "C" void __sklib__sprite_replay_animation__sprite(__sklib_sprite s);
extern "C" void __sklib__sprite_replay_animation__sprite__bool(__sklib_sprite s, int with_sound);
extern "C" float __sklib__sprite_rotation__sprite(__sklib_sprite s);
extern "C" float __sklib__sprite_scale__sprite(__sklib_sprite s);
extern "C" __sklib_rectangle __sklib__sprite_screen_rectangle__sprite(__sklib_sprite s);
extern "C" void __sklib__sprite_send_layer_backward__sprite__int(__sklib_sprite s, int visible_layer);
extern "C" void __sklib__sprite_send_layer_to_back__sprite__int(__sklib_sprite s, int visible_layer);
extern "C" void __sklib__sprite_set_anchor_point__sprite__point_2d_ref(__sklib_sprite s, const __sklib_point_2d pt);
extern "C" void __sklib__sprite_set_collision_bitmap__sprite__bitmap(__sklib_sprite s, __sklib_bitmap bmp);
extern "C" void __sklib__sprite_set_collision_kind__sprite__collision_test_kind(__sklib_sprite s, int value);
extern "C" void __sklib__sprite_set_dx__sprite__float(__sklib_sprite s, float value);
extern "C" void __sklib__sprite_set_dy__sprite__float(__sklib_sprite s, float value);
extern "C" void __sklib__sprite_set_heading__sprite__float(__sklib_sprite s, float value);
extern "C" void __sklib__sprite_set_layer_offset__sprite__string_ref__vector_2d_ref(__sklib_sprite s, const __sklib_string name, const __sklib_vector_2d value);
extern "C" void __sklib__sprite_set_layer_offset__sprite__int__vector_2d_ref(__sklib_sprite s, int idx, const __sklib_vector_2d value);
extern "C" void __sklib__sprite_set_mass__sprite__float(__sklib_sprite s, float value);
extern "C" void __sklib__sprite_set_move_from_anchor_point__sprite__bool(__sklib_sprite s, int value);
extern "C" void __sklib__sprite_set_position__sprite__point_2d_ref(__sklib_sprite s, const __sklib_point_2d value);
extern "C" void __sklib__sprite_set_rotation__sprite__float(__sklib_sprite s, float value);
extern "C" void __sklib__sprite_set_scale__sprite__float(__sklib_sprite s, float value);
extern "C" void __sklib__sprite_set_speed__sprite__float(__sklib_sprite s, float value);
extern "C" void __sklib__sprite_set_value__sprite__string_ref__float(__sklib_sprite s, const __sklib_string name, float val);
extern "C" void __sklib__sprite_set_velocity__sprite__vector_2d_ref(__sklib_sprite s, const __sklib_vector_2d value);
extern "C" void __sklib__sprite_set_x__sprite__float(__sklib_sprite s, float value);
extern "C" void __sklib__sprite_set_y__sprite__float(__sklib_sprite s, float value);
extern "C" int __sklib__sprite_show_layer__sprite__string_ref(__sklib_sprite s, const __sklib_string name);
extern "C" int __sklib__sprite_show_layer__sprite__int(__sklib_sprite s, int id);
extern "C" float __sklib__sprite_speed__sprite(__sklib_sprite s);
extern "C" void __sklib__sprite_start_animation__sprite__string_ref(__sklib_sprite s, const __sklib_string named);
extern "C" void __sklib__sprite_start_animation__sprite__string_ref__bool(__sklib_sprite s, const __sklib_string named, int with_sound);
extern "C" void __sklib__sprite_start_animation__sprite__int(__sklib_sprite s, int idx);
extern "C" void __sklib__sprite_start_animation__sprite__int__bool(__sklib_sprite s, int idx, int with_sound);
extern "C" void __sklib__sprite_stop_calling_on_event__sprite__sprite_event_handler_ptr(__sklib_sprite s, __sklib_sprite_event_handler *handler);
extern "C" void __sklib__sprite_toggle_layer_visible__sprite__string_ref(__sklib_sprite s, const __sklib_string name);
extern "C" void __sklib__sprite_toggle_layer_visible__sprite__int(__sklib_sprite s, int id);
extern "C" float __sklib__sprite_value__sprite__string_ref(__sklib_sprite s, const __sklib_string name);
extern "C" int __sklib__sprite_value_count__sprite(__sklib_sprite s);
extern "C" __sklib_vector_2d __sklib__sprite_velocity__sprite(__sklib_sprite s);
extern "C" int __sklib__sprite_visible_index_of_layer__sprite__string_ref(__sklib_sprite s, const __sklib_string name);
extern "C" int __sklib__sprite_visible_index_of_layer__sprite__int(__sklib_sprite s, int id);
extern "C" int __sklib__sprite_visible_layer__sprite__int(__sklib_sprite s, int idx);
extern "C" int __sklib__sprite_visible_layer_count__sprite(__sklib_sprite s);
extern "C" int __sklib__sprite_visible_layer_id__sprite__int(__sklib_sprite s, int idx);
extern "C" int __sklib__sprite_width__sprite(__sklib_sprite s);
extern "C" float __sklib__sprite_x__sprite(__sklib_sprite s);
extern "C" float __sklib__sprite_y__sprite(__sklib_sprite s);
extern "C" void __sklib__stop_calling_on_sprite_event__sprite_event_handler_ptr(__sklib_sprite_event_handler *handler);
extern "C" void __sklib__update_all_sprites();
extern "C" void __sklib__update_all_sprites__float(float pct);
extern "C" void __sklib__update_sprite__sprite(__sklib_sprite s);
extern "C" void __sklib__update_sprite__sprite__bool(__sklib_sprite s, int with_sound);
extern "C" void __sklib__update_sprite__sprite__float(__sklib_sprite s, float pct);
extern "C" void __sklib__update_sprite__sprite__float__bool(__sklib_sprite s, float pct, int with_sound);
extern "C" void __sklib__update_sprite_animation__sprite(__sklib_sprite s);
extern "C" void __sklib__update_sprite_animation__sprite__bool(__sklib_sprite s, int with_sound);
extern "C" void __sklib__update_sprite_animation__sprite__float(__sklib_sprite s, float pct);
extern "C" void __sklib__update_sprite_animation__sprite__float__bool(__sklib_sprite s, float pct, int with_sound);
extern "C" __sklib_vector_2d __sklib__vector_from_center_sprite_to_point__sprite__point_2d_ref(__sklib_sprite s, const __sklib_point_2d pt);
extern "C" __sklib_vector_2d __sklib__vector_from_to__sprite__sprite(__sklib_sprite s1, __sklib_sprite s2);
extern "C" void __sklib__activate_advanced_terminal();
extern "C" int __sklib__advanced_terminal_active();
extern "C" void __sklib__clear_terminal();
extern "C" void __sklib__end_advanced_terminal();
extern "C" void __sklib__move_cursor_to__int__int(int x, int y);
extern "C" char __sklib__read_char();
extern "C" __sklib_string __sklib__read_line();
extern "C" void __sklib__refresh_terminal();
extern "C" void __sklib__set_terminal_bold__bool(int value);
extern "C" void __sklib__set_terminal_colors__color__color(__sklib_color foreground, __sklib_color background);
extern "C" void __sklib__set_terminal_echo_input__bool(int value);
extern "C" int __sklib__terminal_height();
extern "C" int __sklib__terminal_width();
extern "C" void __sklib__write__string(__sklib_string text);
extern "C" void __sklib__write_at__string__int__int(__sklib_string text, int x, int y);
extern "C" void __sklib__write_line();
extern "C" void __sklib__write_line__string(__sklib_string line);
extern "C" void __sklib__draw_text__string_ref__color_ref__string_ref__int__float__float(const __sklib_string text, const __sklib_color clr, const __sklib_string fnt, int font_size, float x, float y);
extern "C" void __sklib__draw_text__string_ref__color_ref__string_ref__int__float__float__drawing_options_ref(const __sklib_string text, const __sklib_color clr, const __sklib_string fnt, int font_size, float x, float y, const __sklib_drawing_options opts);
extern "C" void __sklib__draw_text__string_ref__color_ref__float__float(const __sklib_string text, const __sklib_color clr, float x, float y);
extern "C" void __sklib__draw_text__string_ref__color_ref__float__float__drawing_options_ref(const __sklib_string text, const __sklib_color clr, float x, float y, const __sklib_drawing_options opts);
extern "C" void __sklib__draw_text__string_ref__color_ref__font__int__float__float(const __sklib_string text, const __sklib_color clr, __sklib_font fnt, int font_size, float x, float y);
extern "C" void __sklib__draw_text__string_ref__color_ref__font__int__float__float__drawing_options_ref(const __sklib_string text, const __sklib_color clr, __sklib_font fnt, int font_size, float x, float y, const __sklib_drawing_options opts);
extern "C" int __sklib__font_has_size__string_ref__int(const __sklib_string name, int font_size);
extern "C" int __sklib__font_has_size__font__int(__sklib_font fnt, int font_size);
extern "C" void __sklib__font_load_size__string_ref__int(const __sklib_string name, int font_size);
extern "C" void __sklib__font_load_size__font__int(__sklib_font fnt, int font_size);
extern "C" __sklib_font __sklib__font_named__string(__sklib_string name);
extern "C" void __sklib__free_all_fonts();
extern "C" void __sklib__free_font__font(__sklib_font fnt);
extern "C" int __sklib__get_font_style__string_ref(const __sklib_string name);
extern "C" int __sklib__get_font_style__font(__sklib_font fnt);
extern "C" int __sklib__has_font__font(__sklib_font fnt);
extern "C" int __sklib__has_font__string(__sklib_string name);
extern "C" __sklib_font __sklib__load_font__string_ref__string_ref(const __sklib_string name, const __sklib_string filename);
extern "C" void __sklib__set_font_style__string_ref__font_style(const __sklib_string name, int style);
extern "C" void __sklib__set_font_style__font__font_style(__sklib_font fnt, int style);
extern "C" int __sklib__text_height__string_ref__string_ref__int(const __sklib_string text, const __sklib_string fnt, int font_size);
extern "C" int __sklib__text_height__string_ref__font__int(const __sklib_string text, __sklib_font fnt, int font_size);
extern "C" int __sklib__text_width__string_ref__string_ref__int(const __sklib_string text, const __sklib_string fnt, int font_size);
extern "C" int __sklib__text_width__string_ref__font__int(const __sklib_string text, __sklib_font fnt, int font_size);
extern "C" void __sklib__draw_collected_text__color__font__int__drawing_options_ref(__sklib_color clr, __sklib_font fnt, int font_size, const __sklib_drawing_options opts);
extern "C" void __sklib__end_reading_text();
extern "C" void __sklib__end_reading_text__window(__sklib_window wind);
extern "C" int __sklib__reading_text();
extern "C" int __sklib__reading_text__window(__sklib_window wind);
extern "C" void __sklib__start_reading_text__rectangle(__sklib_rectangle rect);
extern "C" void __sklib__start_reading_text__rectangle__string(__sklib_rectangle rect, __sklib_string initial_text);
extern "C" void __sklib__start_reading_text__window__rectangle(__sklib_window wind, __sklib_rectangle rect);
extern "C" void __sklib__start_reading_text__window__rectangle__string(__sklib_window wind, __sklib_rectangle rect, __sklib_string initial_text);
extern "C" int __sklib__text_entry_cancelled();
extern "C" int __sklib__text_entry_cancelled__window(__sklib_window wind);
extern "C" __sklib_string __sklib__text_input();
extern "C" __sklib_string __sklib__text_input__window(__sklib_window wind);
extern "C" __sklib_timer __sklib__create_timer__string(__sklib_string name);
extern "C" void __sklib__free_all_timers();
extern "C" void __sklib__free_timer__timer(__sklib_timer to_free);
extern "C" int __sklib__has_timer__string(__sklib_string name);
extern "C" void __sklib__pause_timer__string(__sklib_string name);
extern "C" void __sklib__pause_timer__timer(__sklib_timer to_pause);
extern "C" void __sklib__reset_timer__string(__sklib_string name);
extern "C" void __sklib__reset_timer__timer(__sklib_timer tmr);
extern "C" void __sklib__resume_timer__string(__sklib_string name);
extern "C" void __sklib__resume_timer__timer(__sklib_timer to_resume);
extern "C" void __sklib__start_timer__string(__sklib_string name);
extern "C" void __sklib__start_timer__timer(__sklib_timer to_start);
extern "C" void __sklib__stop_timer__string(__sklib_string name);
extern "C" void __sklib__stop_timer__timer(__sklib_timer to_stop);
extern "C" __sklib_timer __sklib__timer_named__string(__sklib_string name);
extern "C" int __sklib__timer_paused__string(__sklib_string name);
extern "C" int __sklib__timer_paused__timer(__sklib_timer to_get);
extern "C" int __sklib__timer_started__string(__sklib_string name);
extern "C" int __sklib__timer_started__timer(__sklib_timer to_get);
extern "C" unsigned int __sklib__timer_ticks__string(__sklib_string name);
extern "C" unsigned int __sklib__timer_ticks__timer(__sklib_timer to_get);
extern "C" void __sklib__draw_triangle__color__triangle_ref(__sklib_color clr, const __sklib_triangle tri);
extern "C" void __sklib__draw_triangle__color__triangle_ref__drawing_options(__sklib_color clr, const __sklib_triangle tri, __sklib_drawing_options opts);
extern "C" void __sklib__draw_triangle__color__float__float__float__float__float__float(__sklib_color clr, float x1, float y1, float x2, float y2, float x3, float y3);
extern "C" void __sklib__draw_triangle__color__float__float__float__float__float__float__drawing_options(__sklib_color clr, float x1, float y1, float x2, float y2, float x3, float y3, __sklib_drawing_options opts);
extern "C" void __sklib__fill_triangle__color__triangle_ref(__sklib_color clr, const __sklib_triangle tri);
extern "C" void __sklib__fill_triangle__color__triangle_ref__drawing_options(__sklib_color clr, const __sklib_triangle tri, __sklib_drawing_options opts);
extern "C" void __sklib__fill_triangle__color__float__float__float__float__float__float(__sklib_color clr, float x1, float y1, float x2, float y2, float x3, float y3);
extern "C" void __sklib__fill_triangle__color__float__float__float__float__float__float__drawing_options(__sklib_color clr, float x1, float y1, float x2, float y2, float x3, float y3, __sklib_drawing_options opts);
extern "C" __sklib_point_2d __sklib__triangle_barycenter__triangle_ref(const __sklib_triangle tri);
extern "C" __sklib_triangle __sklib__triangle_from__point_2d_ref__point_2d_ref__point_2d_ref(const __sklib_point_2d p1, const __sklib_point_2d p2, const __sklib_point_2d p3);
extern "C" __sklib_triangle __sklib__triangle_from__float__float__float__float__float__float(float x1, float y1, float x2, float y2, float x3, float y3);
extern "C" int __sklib__triangle_rectangle_intersect__triangle_ref__rectangle_ref(const __sklib_triangle tri, const __sklib_rectangle rect);
extern "C" __sklib_string __sklib__triangle_to_string__triangle_ref(const __sklib_triangle tri);
extern "C" int __sklib__triangles_intersect__triangle_ref__triangle_ref(const __sklib_triangle t1, const __sklib_triangle t2);
extern "C" unsigned int __sklib__current_ticks();
extern "C" void __sklib__delay__unsigned_int(unsigned int milliseconds);
extern "C" __sklib_string __sklib__file_as_string__string__resource_kind(__sklib_string filename, int kind);
extern "C" float __sklib__angle_between__vector_2d_ref__vector_2d_ref(const __sklib_vector_2d v1, const __sklib_vector_2d v2);
extern "C" float __sklib__dot_product__vector_2d_ref__vector_2d_ref(const __sklib_vector_2d v1, const __sklib_vector_2d v2);
extern "C" int __sklib__is_zero_vector__vector_2d_ref(const __sklib_vector_2d v);
extern "C" int __sklib__ray_intersection_point__point_2d_ref__vector_2d_ref__line_ref__point_2d_ref(const __sklib_point_2d from_pt, const __sklib_vector_2d heading, const __sklib_line l, __sklib_point_2d *pt);
extern "C" __sklib_vector_2d __sklib__unit_vector__vector_2d_ref(const __sklib_vector_2d v);
extern "C" __sklib_vector_2d __sklib__vector_add__vector_2d_ref__vector_2d_ref(const __sklib_vector_2d v1, const __sklib_vector_2d v2);
extern "C" float __sklib__vector_angle__vector_2d(const __sklib_vector_2d v);
extern "C" __sklib_vector_2d __sklib__vector_from_angle__float__float(float angle, float magnitude);
extern "C" __sklib_vector_2d __sklib__vector_from_line__line_ref(const __sklib_line l);
extern "C" __sklib_vector_2d __sklib__vector_from_point_to_rect__point_2d_ref__rectangle_ref(const __sklib_point_2d pt, const __sklib_rectangle rect);
extern "C" int __sklib__vector_in_rect__vector_2d_ref__rectangle_ref(const __sklib_vector_2d v, const __sklib_rectangle rect);
extern "C" __sklib_vector_2d __sklib__vector_invert__vector_2d_ref(const __sklib_vector_2d v);
extern "C" __sklib_vector_2d __sklib__vector_limit__vector_2d_ref__float(const __sklib_vector_2d v, float limit);
extern "C" float __sklib__vector_magnitude__vector_2d_ref(const __sklib_vector_2d v);
extern "C" float __sklib__vector_magnitude_sqared__vector_2d_ref(const __sklib_vector_2d v);
extern "C" __sklib_vector_2d __sklib__vector_multiply__vector_2d_ref__float(const __sklib_vector_2d v1, float s);
extern "C" __sklib_vector_2d __sklib__vector_normal__vector_2d_ref(const __sklib_vector_2d v);
extern "C" __sklib_vector_2d __sklib__vector_out_of_circle_from_circle__circle_ref__circle_ref__vector_2d_ref(const __sklib_circle src, const __sklib_circle bounds, const __sklib_vector_2d velocity);
extern "C" __sklib_vector_2d __sklib__vector_out_of_circle_from_point__point_2d_ref__circle_ref__vector_2d_ref(const __sklib_point_2d pt, const __sklib_circle c, const __sklib_vector_2d velocity);
extern "C" __sklib_vector_2d __sklib__vector_out_of_rect_from_circle__circle_ref__rectangle_ref__vector_2d_ref(const __sklib_circle c, const __sklib_rectangle rect, const __sklib_vector_2d velocity);
extern "C" __sklib_vector_2d __sklib__vector_out_of_rect_from_point__point_2d_ref__rectangle_ref__vector_2d_ref(const __sklib_point_2d pt, const __sklib_rectangle rect, const __sklib_vector_2d velocity);
extern "C" __sklib_vector_2d __sklib__vector_out_of_rect_from_rect__rectangle_ref__rectangle_ref__vector_2d_ref(const __sklib_rectangle src, const __sklib_rectangle bounds, const __sklib_vector_2d velocity);
extern "C" __sklib_vector_2d __sklib__vector_point_to_point__point_2d_ref__point_2d_ref(const __sklib_point_2d start, const __sklib_point_2d end);
extern "C" __sklib_vector_2d __sklib__vector_subtract__vector_2d_ref__vector_2d_ref(const __sklib_vector_2d v1, const __sklib_vector_2d v2);
extern "C" __sklib_vector_2d __sklib__vector_to__point_2d_ref(const __sklib_point_2d p1);
extern "C" __sklib_vector_2d __sklib__vector_to__float__float(float x, float y);
extern "C" __sklib_string __sklib__vector_to_string__vector_2d_ref(const __sklib_vector_2d v);
extern "C" int __sklib__vectors_equal__vector_2d_ref__vector_2d(const __sklib_vector_2d v1, const __sklib_vector_2d v2);
extern "C" int __sklib__vectors_not_equal__vector_2d_ref__vector_2d(const __sklib_vector_2d v1, const __sklib_vector_2d v2);
extern "C" __sklib_bitmap __sklib__download_bitmap__string_ref__string_ref__unsigned_short(const __sklib_string name, const __sklib_string url, unsigned short port);
extern "C" __sklib_font __sklib__download_font__string_ref__string_ref__unsigned_short(const __sklib_string name, const __sklib_string url, unsigned short port);
extern "C" __sklib_music __sklib__download_music__string_ref__string_ref__unsigned_short(const __sklib_string name, const __sklib_string url, unsigned short port);
extern "C" __sklib_sound_effect __sklib__download_sound_effect__string_ref__string_ref__unsigned_short(const __sklib_string name, const __sklib_string url, unsigned short port);
extern "C" void __sklib__free_response__http_response(__sklib_http_response response);
extern "C" __sklib_http_response __sklib__http_get__string_ref__unsigned_short(const __sklib_string url, unsigned short port);
extern "C" __sklib_http_response __sklib__http_post__string_ref__unsigned_short__string(const __sklib_string url, unsigned short port, __sklib_string body);
extern "C" __sklib_string __sklib__http_response_to_string__http_response(__sklib_http_response response);
extern "C" void __sklib__save_response_to_file__http_response__string(__sklib_http_response response, __sklib_string path);
extern "C" int __sklib__has_incoming_requests__web_server(__sklib_web_server server);
extern "C" int __sklib__is_delete_request_for__http_request__string_ref(__sklib_http_request request, const __sklib_string path);
extern "C" int __sklib__is_get_request_for__http_request__string_ref(__sklib_http_request request, const __sklib_string path);
extern "C" int __sklib__is_options_request_for__http_request__string_ref(__sklib_http_request request, const __sklib_string path);
extern "C" int __sklib__is_post_request_for__http_request__string_ref(__sklib_http_request request, const __sklib_string path);
extern "C" int __sklib__is_put_request_for__http_request__string_ref(__sklib_http_request request, const __sklib_string path);
extern "C" int __sklib__is_request_for__http_request__http_method__string_ref(__sklib_http_request request, int method, const __sklib_string path);
extern "C" int __sklib__is_trace_request_for__http_request__string_ref(__sklib_http_request request, const __sklib_string path);
extern "C" __sklib_http_request __sklib__next_web_request__web_server(__sklib_web_server server);
extern "C" __sklib_string __sklib__request_body__http_request(__sklib_http_request r);
extern "C" int __sklib__request_method__http_request(__sklib_http_request r);
extern "C" __sklib_string __sklib__request_uri__http_request(__sklib_http_request r);
extern "C" __sklib_vector_string __sklib__request_uri_stubs__http_request(__sklib_http_request r);
extern "C" void __sklib__send_html_file_response__http_request__string_ref(__sklib_http_request r, const __sklib_string filename);
extern "C" void __sklib__send_response__http_request(__sklib_http_request r);
extern "C" void __sklib__send_response__http_request__string_ref(__sklib_http_request r, const __sklib_string message);
extern "C" void __sklib__send_response__http_request__http_status_code(__sklib_http_request r, int code);
extern "C" void __sklib__send_response__http_request__http_status_code__string_ref(__sklib_http_request r, int code, const __sklib_string message);
extern "C" void __sklib__send_response__http_request__http_status_code__string_ref__string_ref(__sklib_http_request r, int code, const __sklib_string message, const __sklib_string content_type);
extern "C" void __sklib__send_response__http_request__json(__sklib_http_request r, __sklib_json j);
extern "C" __sklib_vector_string __sklib__split_uri_stubs__string_ref(const __sklib_string uri);
extern "C" __sklib_web_server __sklib__start_web_server();
extern "C" __sklib_web_server __sklib__start_web_server__unsigned_short(unsigned short port);
extern "C" void __sklib__stop_web_server__web_server(__sklib_web_server server);
extern "C" void __sklib__clear_window__window__color(__sklib_window wind, __sklib_color clr);
extern "C" void __sklib__close_all_windows();
extern "C" void __sklib__close_window__string_ref(const __sklib_string name);
extern "C" void __sklib__close_window();
extern "C" void __sklib__close_window__window(__sklib_window wind);
extern "C" __sklib_window __sklib__current_window();
extern "C" int __sklib__has_window__string(__sklib_string caption);
extern "C" void __sklib__move_window__int__int(int x, int y);
extern "C" void __sklib__move_window__string_ref__int__int(const __sklib_string name, int x, int y);
extern "C" void __sklib__move_window__window__int__int(__sklib_window wind, int x, int y);
extern "C" __sklib_window __sklib__open_window__string__int__int(__sklib_string caption, int width, int height);
extern "C" void __sklib__refresh_window__window(__sklib_window wind);
extern "C" void __sklib__resize_window__int__int(int width, int height);
extern "C" void __sklib__resize_window__window__int__int(__sklib_window wnd, int width, int height);
extern "C" void __sklib__set_current_window__string_ref(const __sklib_string name);
extern "C" void __sklib__set_current_window__window(__sklib_window wind);
extern "C" int __sklib__window_close_requested__string_ref(const __sklib_string name);
extern "C" int __sklib__window_close_requested__window(__sklib_window wind);
extern "C" int __sklib__window_has_border();
extern "C" int __sklib__window_has_border__string_ref(const __sklib_string name);
extern "C" int __sklib__window_has_border__window(__sklib_window wnd);
extern "C" int __sklib__window_height();
extern "C" int __sklib__window_height__string_ref(const __sklib_string name);
extern "C" int __sklib__window_height__window(__sklib_window wind);
extern "C" int __sklib__window_is_fullscreen();
extern "C" int __sklib__window_is_fullscreen__string_ref(const __sklib_string name);
extern "C" int __sklib__window_is_fullscreen__window(__sklib_window wnd);
extern "C" __sklib_window __sklib__window_named__string(__sklib_string caption);
extern "C" __sklib_point_2d __sklib__window_position();
extern "C" __sklib_point_2d __sklib__window_position__string_ref(const __sklib_string name);
extern "C" __sklib_point_2d __sklib__window_position__window(__sklib_window wnd);
extern "C" void __sklib__window_set_icon__window__bitmap(__sklib_window wind, __sklib_bitmap bmp);
extern "C" void __sklib__window_toggle_border();
extern "C" void __sklib__window_toggle_border__string_ref(const __sklib_string name);
extern "C" void __sklib__window_toggle_border__window(__sklib_window wnd);
extern "C" void __sklib__window_toggle_fullscreen();
extern "C" void __sklib__window_toggle_fullscreen__string_ref(const __sklib_string name);
extern "C" void __sklib__window_toggle_fullscreen__window(__sklib_window wnd);
extern "C" int __sklib__window_width();
extern "C" int __sklib__window_width__string_ref(const __sklib_string name);
extern "C" int __sklib__window_width__window(__sklib_window wind);
extern "C" __sklib_window __sklib__window_with_focus();
extern "C" int __sklib__window_x();
extern "C" int __sklib__window_x__string_ref(const __sklib_string name);
extern "C" int __sklib__window_x__window(__sklib_window wnd);
extern "C" int __sklib__window_y();
extern "C" int __sklib__window_y__string_ref(const __sklib_string name);
extern "C" int __sklib__window_y__window(__sklib_window wnd);
