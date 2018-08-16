//
// SplashKit C Library type mapping functions
// DO NOT MODIFY
//

#ifndef __splashkit_lib_type_mapper
#define __splashkit_lib_type_mapper

#include <stdlib.h>
#include <string>
#include <cstring>
#include <vector>
#include "sk_clib.h"
#include "timers.h"
#include "music.h"
#include "sound.h"
#include "circle_drawing.h"
#include "utils.h"
#include "input.h"
#include "window_manager.h"
#include "resources.h"
#include "text.h"
#include "rectangle_drawing.h"
#include "clipping.h"
#include "text_input.h"
#include "collisions.h"
#include "triangle_drawing.h"
#include "types.h"
#include "ellipse_drawing.h"
#include "bundles.h"
#include "line_geometry.h"
#include "camera.h"
#include "web_client.h"
#include "mouse_input.h"
#include "color.h"
#include "audio.h"
#include "json.h"
#include "database.h"
#include "matrix_2d.h"
#include "images.h"
#include "rectangle_geometry.h"
#include "terminal.h"
#include "web_server.h"
#include "triangle_geometry.h"
#include "line_drawing.h"
#include "sprites.h"
#include "drawing_options.h"
#include "animations.h"
#include "graphics.h"
#include "basics.h"
#include "point_geometry.h"
#include "circle_geometry.h"
#include "point_drawing.h"
#include "quad_geometry.h"
#include "twitter.h"
#include "networking.h"
#include "keyboard_input.h"
#include "physics.h"
#include "random.h"
#include "geometry.h"
#include "vector_2d.h"

using std::string;
using std::vector;
using namespace splashkit_lib;

__sklib_string __sklib__to_sklib_string(const std::string &s);
std::string __sklib__to_string(const __sklib_string &s);
int __sklib__to_sklib_bool(bool v);
bool __sklib__to_bool(int v);
__sklib_int8_t __sklib__to_sklib_int8_t(int8_t v);
int8_t __sklib__to_int8_t(int8_t v);
__sklib_int __sklib__to_sklib_int(int v);
int __sklib__to_int(int v);
__sklib_short __sklib__to_sklib_short(short v);
short __sklib__to_short(short v);
__sklib_int64_t __sklib__to_sklib_int64_t(int64_t v);
int64_t __sklib__to_int64_t(int64_t v);
__sklib_float __sklib__to_sklib_float(float v);
float __sklib__to_float(float v);
__sklib_double __sklib__to_sklib_double(double v);
double __sklib__to_double(double v);
__sklib_char __sklib__to_sklib_char(char v);
char __sklib__to_char(char v);
__sklib_unsigned_int __sklib__to_sklib_unsigned_int(unsigned int v);
unsigned int __sklib__to_unsigned_int(unsigned int v);
__sklib_unsigned_short __sklib__to_sklib_unsigned_short(unsigned short v);
unsigned short __sklib__to_unsigned_short(unsigned short v);
__sklib_unsigned_char __sklib__to_sklib_unsigned_char(unsigned char v);
unsigned char __sklib__to_unsigned_char(unsigned char v);
__sklib_ptr __sklib__to_sklib_ptr(__sklib_ptr v);
__sklib_ptr __sklib__to_sklib_timer(splashkit_lib::timer v);
timer __sklib__to_timer(__sklib_ptr v);
__sklib_ptr __sklib__to_sklib_music(splashkit_lib::music v);
music __sklib__to_music(__sklib_ptr v);
__sklib_ptr __sklib__to_sklib_sound_effect(splashkit_lib::sound_effect v);
sound_effect __sklib__to_sound_effect(__sklib_ptr v);
__sklib_ptr __sklib__to_sklib_window(splashkit_lib::window v);
window __sklib__to_window(__sklib_ptr v);
__sklib_ptr __sklib__to_sklib_animation(splashkit_lib::animation v);
animation __sklib__to_animation(__sklib_ptr v);
__sklib_ptr __sklib__to_sklib_animation_script(splashkit_lib::animation_script v);
animation_script __sklib__to_animation_script(__sklib_ptr v);
__sklib_ptr __sklib__to_sklib_bitmap(splashkit_lib::bitmap v);
bitmap __sklib__to_bitmap(__sklib_ptr v);
__sklib_ptr __sklib__to_sklib_display(splashkit_lib::display v);
display __sklib__to_display(__sklib_ptr v);
__sklib_ptr __sklib__to_sklib_font(splashkit_lib::font v);
font __sklib__to_font(__sklib_ptr v);
__sklib_ptr __sklib__to_sklib_http_response(splashkit_lib::http_response v);
http_response __sklib__to_http_response(__sklib_ptr v);
__sklib_ptr __sklib__to_sklib_json(splashkit_lib::json v);
json __sklib__to_json(__sklib_ptr v);
__sklib_ptr __sklib__to_sklib_database(splashkit_lib::database v);
database __sklib__to_database(__sklib_ptr v);
__sklib_ptr __sklib__to_sklib_query_result(splashkit_lib::query_result v);
query_result __sklib__to_query_result(__sklib_ptr v);
__sklib_ptr __sklib__to_sklib_http_request(splashkit_lib::http_request v);
http_request __sklib__to_http_request(__sklib_ptr v);
__sklib_ptr __sklib__to_sklib_web_server(splashkit_lib::web_server v);
web_server __sklib__to_web_server(__sklib_ptr v);
__sklib_ptr __sklib__to_sklib_sprite(splashkit_lib::sprite v);
sprite __sklib__to_sprite(__sklib_ptr v);
__sklib_ptr __sklib__to_sklib_connection(splashkit_lib::connection v);
connection __sklib__to_connection(__sklib_ptr v);
__sklib_ptr __sklib__to_sklib_message(splashkit_lib::message v);
message __sklib__to_message(__sklib_ptr v);
__sklib_ptr __sklib__to_sklib_server_socket(splashkit_lib::server_socket v);
server_socket __sklib__to_server_socket(__sklib_ptr v);
int __sklib__to_sklib_resource_kind(resource_kind v);
resource_kind __sklib__to_resource_kind(int v);
int __sklib__to_sklib_drawing_dest(drawing_dest v);
drawing_dest __sklib__to_drawing_dest(int v);
int __sklib__to_sklib_font_style(font_style v);
font_style __sklib__to_font_style(int v);
int __sklib__to_sklib_http_status_code(http_status_code v);
http_status_code __sklib__to_http_status_code(int v);
int __sklib__to_sklib_mouse_button(mouse_button v);
mouse_button __sklib__to_mouse_button(int v);
int __sklib__to_sklib_http_method(http_method v);
http_method __sklib__to_http_method(int v);
int __sklib__to_sklib_collision_test_kind(collision_test_kind v);
collision_test_kind __sklib__to_collision_test_kind(int v);
int __sklib__to_sklib_sprite_event_kind(sprite_event_kind v);
sprite_event_kind __sklib__to_sprite_event_kind(int v);
int __sklib__to_sklib_connection_type(connection_type v);
connection_type __sklib__to_connection_type(int v);
int __sklib__to_sklib_key_code(key_code v);
key_code __sklib__to_key_code(int v);
__sklib_point_2d __sklib__to_sklib_point_2d(point_2d v);
point_2d __sklib__to_point_2d(__sklib_point_2d v);
__sklib_circle __sklib__to_sklib_circle(circle v);
circle __sklib__to_circle(__sklib_circle v);
__sklib_color __sklib__to_sklib_color(color v);
color __sklib__to_color(__sklib_color v);
__sklib_rectangle __sklib__to_sklib_rectangle(rectangle v);
rectangle __sklib__to_rectangle(__sklib_rectangle v);
__sklib_drawing_options __sklib__to_sklib_drawing_options(drawing_options v);
drawing_options __sklib__to_drawing_options(__sklib_drawing_options v);
__sklib_line __sklib__to_sklib_line(line v);
line __sklib__to_line(__sklib_line v);
__sklib_quad __sklib__to_sklib_quad(quad v);
quad __sklib__to_quad(__sklib_quad v);
__sklib_triangle __sklib__to_sklib_triangle(triangle v);
triangle __sklib__to_triangle(__sklib_triangle v);
__sklib_vector_2d __sklib__to_sklib_vector_2d(vector_2d v);
vector_2d __sklib__to_vector_2d(__sklib_vector_2d v);
__sklib_matrix_2d __sklib__to_sklib_matrix_2d(matrix_2d v);
matrix_2d __sklib__to_matrix_2d(__sklib_matrix_2d v);
void (*__sklib__to_free_notifier(__sklib_free_notifier *v))(__sklib_ptr pointer);
void (*__sklib__to_sklib_free_notifier(free_notifier *v))(__sklib_ptr pointer);
void (*__sklib__to_sprite_event_handler(__sklib_sprite_event_handler *v))(__sklib_ptr s, int evt);
void (*__sklib__to_sklib_sprite_event_handler(sprite_event_handler *v))(__sklib_ptr s, int evt);
void (*__sklib__to_sprite_float_function(__sklib_sprite_float_function *v))(__sklib_ptr s, float f);
void (*__sklib__to_sklib_sprite_float_function(sprite_float_function *v))(__sklib_ptr s, float f);
void (*__sklib__to_sprite_function(__sklib_sprite_function *v))(__sklib_ptr s);
void (*__sklib__to_sklib_sprite_function(sprite_function *v))(__sklib_ptr s);
void (*__sklib__to_key_callback(__sklib_key_callback *v))(int code);
void (*__sklib__to_sklib_key_callback(key_callback *v))(int code);
__sklib_vector_line __sklib__to_sklib_vector_line(const std::vector<line> &v);
vector<line> __sklib__to_vector_line(const __sklib_vector_line &v);
void __sklib__update_from_vector_line(const std::vector<line> &v, __sklib_vector_line *__skreturn);
__sklib_vector_string __sklib__to_sklib_vector_string(const std::vector<string> &v);
vector<string> __sklib__to_vector_string(const __sklib_vector_string &v);
void __sklib__update_from_vector_string(const std::vector<string> &v, __sklib_vector_string *__skreturn);
__sklib_vector_triangle __sklib__to_sklib_vector_triangle(const std::vector<triangle> &v);
vector<triangle> __sklib__to_vector_triangle(const __sklib_vector_triangle &v);
void __sklib__update_from_vector_triangle(const std::vector<triangle> &v, __sklib_vector_triangle *__skreturn);
__sklib_vector_int8_t __sklib__to_sklib_vector_int8_t(const std::vector<int8_t> &v);
vector<int8_t> __sklib__to_vector_int8_t(const __sklib_vector_int8_t &v);
void __sklib__update_from_vector_int8_t(const std::vector<int8_t> &v, __sklib_vector_int8_t *__skreturn);
__sklib_vector_double __sklib__to_sklib_vector_double(const std::vector<double> &v);
vector<double> __sklib__to_vector_double(const __sklib_vector_double &v);
void __sklib__update_from_vector_double(const std::vector<double> &v, __sklib_vector_double *__skreturn);
__sklib_vector_json __sklib__to_sklib_vector_json(const std::vector<json> &v);
vector<json> __sklib__to_vector_json(const __sklib_vector_json &v);
void __sklib__update_from_vector_json(const std::vector<json> &v, __sklib_vector_json *__skreturn);
__sklib_vector_bool __sklib__to_sklib_vector_bool(const std::vector<bool> &v);
vector<bool> __sklib__to_vector_bool(const __sklib_vector_bool &v);
void __sklib__update_from_vector_bool(const std::vector<bool> &v, __sklib_vector_bool *__skreturn);

#endif /* __splashkit_lib_type_mapper */
