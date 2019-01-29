//
// SplashKit C++ Adapter type mapping functions
// DO NOT MODIFY
//

#ifndef __splashkit_adapter_type_mapper
#define __splashkit_adapter_type_mapper

#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include "sk_clib.h"
#include "splashkit.h"

void __skadapter__free__sklib_string(__sklib_string s);
__sklib_string __skadapter__to_sklib_string(const std::string &s);
std::string __skadapter__to_string(const __sklib_string &s);
int __skadapter__to_sklib_bool(bool v);
bool __skadapter__to_bool(int v);
__sklib_int8_t __skadapter__to_sklib_int8_t(int8_t v);
int8_t __skadapter__to_int8_t(int8_t v);
__sklib_int __skadapter__to_sklib_int(int v);
int __skadapter__to_int(int v);
__sklib_short __skadapter__to_sklib_short(short v);
short __skadapter__to_short(short v);
__sklib_int64_t __skadapter__to_sklib_int64_t(int64_t v);
int64_t __skadapter__to_int64_t(int64_t v);
__sklib_float __skadapter__to_sklib_float(float v);
float __skadapter__to_float(float v);
__sklib_double __skadapter__to_sklib_double(double v);
double __skadapter__to_double(double v);
__sklib_char __skadapter__to_sklib_char(char v);
char __skadapter__to_char(char v);
__sklib_unsigned_int __skadapter__to_sklib_unsigned_int(unsigned int v);
unsigned int __skadapter__to_unsigned_int(unsigned int v);
__sklib_unsigned_short __skadapter__to_sklib_unsigned_short(unsigned short v);
unsigned short __skadapter__to_unsigned_short(unsigned short v);
__sklib_unsigned_char __skadapter__to_sklib_unsigned_char(unsigned char v);
unsigned char __skadapter__to_unsigned_char(unsigned char v);
__sklib_ptr __skadapter__to_sklib_ptr(__sklib_ptr v);
__sklib_ptr __skadapter__to_sklib_timer(timer v);
timer __skadapter__to_timer(__sklib_ptr v);
__sklib_ptr __skadapter__to_sklib_music(music v);
music __skadapter__to_music(__sklib_ptr v);
__sklib_ptr __skadapter__to_sklib_sound_effect(sound_effect v);
sound_effect __skadapter__to_sound_effect(__sklib_ptr v);
__sklib_ptr __skadapter__to_sklib_window(window v);
window __skadapter__to_window(__sklib_ptr v);
__sklib_ptr __skadapter__to_sklib_animation(animation v);
animation __skadapter__to_animation(__sklib_ptr v);
__sklib_ptr __skadapter__to_sklib_animation_script(animation_script v);
animation_script __skadapter__to_animation_script(__sklib_ptr v);
__sklib_ptr __skadapter__to_sklib_bitmap(bitmap v);
bitmap __skadapter__to_bitmap(__sklib_ptr v);
__sklib_ptr __skadapter__to_sklib_display(display v);
display __skadapter__to_display(__sklib_ptr v);
__sklib_ptr __skadapter__to_sklib_font(font v);
font __skadapter__to_font(__sklib_ptr v);
__sklib_ptr __skadapter__to_sklib_http_response(http_response v);
http_response __skadapter__to_http_response(__sklib_ptr v);
__sklib_ptr __skadapter__to_sklib_json(json v);
json __skadapter__to_json(__sklib_ptr v);
__sklib_ptr __skadapter__to_sklib_database(database v);
database __skadapter__to_database(__sklib_ptr v);
__sklib_ptr __skadapter__to_sklib_query_result(query_result v);
query_result __skadapter__to_query_result(__sklib_ptr v);
__sklib_ptr __skadapter__to_sklib_http_request(http_request v);
http_request __skadapter__to_http_request(__sklib_ptr v);
__sklib_ptr __skadapter__to_sklib_web_server(web_server v);
web_server __skadapter__to_web_server(__sklib_ptr v);
__sklib_ptr __skadapter__to_sklib_sprite(sprite v);
sprite __skadapter__to_sprite(__sklib_ptr v);
__sklib_ptr __skadapter__to_sklib_connection(connection v);
connection __skadapter__to_connection(__sklib_ptr v);
__sklib_ptr __skadapter__to_sklib_message(message v);
message __skadapter__to_message(__sklib_ptr v);
__sklib_ptr __skadapter__to_sklib_server_socket(server_socket v);
server_socket __skadapter__to_server_socket(__sklib_ptr v);
int __skadapter__to_sklib_resource_kind(resource_kind v);
resource_kind __skadapter__to_resource_kind(int v);
int __skadapter__to_sklib_drawing_dest(drawing_dest v);
drawing_dest __skadapter__to_drawing_dest(int v);
int __skadapter__to_sklib_font_style(font_style v);
font_style __skadapter__to_font_style(int v);
int __skadapter__to_sklib_http_status_code(http_status_code v);
http_status_code __skadapter__to_http_status_code(int v);
int __skadapter__to_sklib_mouse_button(mouse_button v);
mouse_button __skadapter__to_mouse_button(int v);
int __skadapter__to_sklib_http_method(http_method v);
http_method __skadapter__to_http_method(int v);
int __skadapter__to_sklib_collision_test_kind(collision_test_kind v);
collision_test_kind __skadapter__to_collision_test_kind(int v);
int __skadapter__to_sklib_sprite_event_kind(sprite_event_kind v);
sprite_event_kind __skadapter__to_sprite_event_kind(int v);
int __skadapter__to_sklib_connection_type(connection_type v);
connection_type __skadapter__to_connection_type(int v);
int __skadapter__to_sklib_key_code(key_code v);
key_code __skadapter__to_key_code(int v);
__sklib_point_2d __skadapter__to_sklib_point_2d(point_2d v);
point_2d __skadapter__to_point_2d(__sklib_point_2d v);
__sklib_circle __skadapter__to_sklib_circle(circle v);
circle __skadapter__to_circle(__sklib_circle v);
__sklib_color __skadapter__to_sklib_color(color v);
color __skadapter__to_color(__sklib_color v);
__sklib_rectangle __skadapter__to_sklib_rectangle(rectangle v);
rectangle __skadapter__to_rectangle(__sklib_rectangle v);
__sklib_drawing_options __skadapter__to_sklib_drawing_options(drawing_options v);
drawing_options __skadapter__to_drawing_options(__sklib_drawing_options v);
__sklib_line __skadapter__to_sklib_line(line v);
line __skadapter__to_line(__sklib_line v);
__sklib_quad __skadapter__to_sklib_quad(quad v);
quad __skadapter__to_quad(__sklib_quad v);
__sklib_triangle __skadapter__to_sklib_triangle(triangle v);
triangle __skadapter__to_triangle(__sklib_triangle v);
__sklib_vector_2d __skadapter__to_sklib_vector_2d(vector_2d v);
vector_2d __skadapter__to_vector_2d(__sklib_vector_2d v);
__sklib_matrix_2d __skadapter__to_sklib_matrix_2d(matrix_2d v);
matrix_2d __skadapter__to_matrix_2d(__sklib_matrix_2d v);
void (*__skadapter__to_free_notifier(__sklib_free_notifier *v))(__sklib_ptr pointer);
void (*__skadapter__to_sklib_free_notifier(free_notifier *v))(__sklib_ptr pointer);
void (*__skadapter__to_sprite_event_handler(__sklib_sprite_event_handler *v))(__sklib_ptr s, int evt);
void (*__skadapter__to_sklib_sprite_event_handler(sprite_event_handler *v))(__sklib_ptr s, int evt);
void (*__skadapter__to_sprite_float_function(__sklib_sprite_float_function *v))(__sklib_ptr s, float f);
void (*__skadapter__to_sklib_sprite_float_function(sprite_float_function *v))(__sklib_ptr s, float f);
void (*__skadapter__to_sprite_function(__sklib_sprite_function *v))(__sklib_ptr s);
void (*__skadapter__to_sklib_sprite_function(sprite_function *v))(__sklib_ptr s);
void (*__skadapter__to_key_callback(__sklib_key_callback *v))(int code);
void (*__skadapter__to_sklib_key_callback(key_callback *v))(int code);
void __skadapter__free__sklib_vector_line(__sklib_vector_line v);
__sklib_vector_line __skadapter__to_sklib_vector_line(const std::vector<line> &v);
vector<line> __skadapter__to_vector_line(const __sklib_vector_line &v);
void __skadapter__update_from_vector_line(__sklib_vector_line &v, std::vector<line> &__skreturn);
void __skadapter__free__sklib_vector_string(__sklib_vector_string v);
__sklib_vector_string __skadapter__to_sklib_vector_string(const std::vector<string> &v);
vector<string> __skadapter__to_vector_string(const __sklib_vector_string &v);
void __skadapter__update_from_vector_string(__sklib_vector_string &v, std::vector<string> &__skreturn);
void __skadapter__free__sklib_vector_triangle(__sklib_vector_triangle v);
__sklib_vector_triangle __skadapter__to_sklib_vector_triangle(const std::vector<triangle> &v);
vector<triangle> __skadapter__to_vector_triangle(const __sklib_vector_triangle &v);
void __skadapter__update_from_vector_triangle(__sklib_vector_triangle &v, std::vector<triangle> &__skreturn);
void __skadapter__free__sklib_vector_int8_t(__sklib_vector_int8_t v);
__sklib_vector_int8_t __skadapter__to_sklib_vector_int8_t(const std::vector<int8_t> &v);
vector<int8_t> __skadapter__to_vector_int8_t(const __sklib_vector_int8_t &v);
void __skadapter__update_from_vector_int8_t(__sklib_vector_int8_t &v, std::vector<int8_t> &__skreturn);
void __skadapter__free__sklib_vector_double(__sklib_vector_double v);
__sklib_vector_double __skadapter__to_sklib_vector_double(const std::vector<double> &v);
vector<double> __skadapter__to_vector_double(const __sklib_vector_double &v);
void __skadapter__update_from_vector_double(__sklib_vector_double &v, std::vector<double> &__skreturn);
void __skadapter__free__sklib_vector_json(__sklib_vector_json v);
__sklib_vector_json __skadapter__to_sklib_vector_json(const std::vector<json> &v);
vector<json> __skadapter__to_vector_json(const __sklib_vector_json &v);
void __skadapter__update_from_vector_json(__sklib_vector_json &v, std::vector<json> &__skreturn);
void __skadapter__free__sklib_vector_bool(__sklib_vector_bool v);
__sklib_vector_bool __skadapter__to_sklib_vector_bool(const std::vector<bool> &v);
vector<bool> __skadapter__to_vector_bool(const __sklib_vector_bool &v);
void __skadapter__update_from_vector_bool(__sklib_vector_bool &v, std::vector<bool> &__skreturn);

#endif /* __splashkit_adapter_type_mapper */
