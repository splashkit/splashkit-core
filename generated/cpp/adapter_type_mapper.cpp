//
// SplashKit C++ Adapter type mapping functions
// DO NOT MODIFY
//

#include "adapter_type_mapper.h"

void __skadapter__free__sklib_string(__sklib_string s) {
    free(s.ptr);
}
__sklib_string __skadapter__to_sklib_string(const std::string &s) {
    __sklib_string __skreturn;
    __skreturn.size = static_cast<unsigned int>(s.length());
    __skreturn.string = (char *)malloc(__skreturn.size + 1);
    __skreturn.ptr = __skreturn.string;
    strcpy(__skreturn.string, s.c_str());
    return __skreturn;
}
std::string __skadapter__to_string(const __sklib_string &s) {
    std:string result = std::string(s.string);
    __sklib__free__sklib_string(s);
    return result;
}
int __skadapter__to_sklib_bool(bool v) {
  return (v == true ? -1 : 0);
}
bool __skadapter__to_bool(int v) {
  return (v != 0 ? true : false);
}
__sklib_int8_t __skadapter__to_sklib_int8_t(int8_t v) {
    return v;
}
int8_t __skadapter__to_int8_t(int8_t v) {
    return v;
}
__sklib_int __skadapter__to_sklib_int(int v) {
    return v;
}
int __skadapter__to_int(int v) {
    return v;
}
__sklib_short __skadapter__to_sklib_short(short v) {
    return v;
}
short __skadapter__to_short(short v) {
    return v;
}
__sklib_int64_t __skadapter__to_sklib_int64_t(int64_t v) {
    return v;
}
int64_t __skadapter__to_int64_t(int64_t v) {
    return v;
}
__sklib_float __skadapter__to_sklib_float(float v) {
    return v;
}
float __skadapter__to_float(float v) {
    return v;
}
__sklib_double __skadapter__to_sklib_double(double v) {
    return v;
}
double __skadapter__to_double(double v) {
    return v;
}
__sklib_char __skadapter__to_sklib_char(char v) {
    return v;
}
char __skadapter__to_char(char v) {
    return v;
}
__sklib_unsigned_int __skadapter__to_sklib_unsigned_int(unsigned int v) {
    return v;
}
unsigned int __skadapter__to_unsigned_int(unsigned int v) {
    return v;
}
__sklib_unsigned_short __skadapter__to_sklib_unsigned_short(unsigned short v) {
    return v;
}
unsigned short __skadapter__to_unsigned_short(unsigned short v) {
    return v;
}
__sklib_unsigned_char __skadapter__to_sklib_unsigned_char(unsigned char v) {
    return v;
}
unsigned char __skadapter__to_unsigned_char(unsigned char v) {
    return v;
}
__sklib_ptr __skadapter__to_sklib_ptr(__sklib_ptr v) {
    return v;
}
__sklib_ptr __skadapter__to_sklib_database(database v) {
    return static_cast<__sklib_ptr>(v);
}
database __skadapter__to_database(__sklib_ptr v) {
    return static_cast<database>(v);
}
__sklib_ptr __skadapter__to_sklib_query_result(query_result v) {
    return static_cast<__sklib_ptr>(v);
}
query_result __skadapter__to_query_result(__sklib_ptr v) {
    return static_cast<query_result>(v);
}
__sklib_ptr __skadapter__to_sklib_json(json v) {
    return static_cast<__sklib_ptr>(v);
}
json __skadapter__to_json(__sklib_ptr v) {
    return static_cast<json>(v);
}
__sklib_ptr __skadapter__to_sklib_music(music v) {
    return static_cast<__sklib_ptr>(v);
}
music __skadapter__to_music(__sklib_ptr v) {
    return static_cast<music>(v);
}
__sklib_ptr __skadapter__to_sklib_connection(connection v) {
    return static_cast<__sklib_ptr>(v);
}
connection __skadapter__to_connection(__sklib_ptr v) {
    return static_cast<connection>(v);
}
__sklib_ptr __skadapter__to_sklib_message(message v) {
    return static_cast<__sklib_ptr>(v);
}
message __skadapter__to_message(__sklib_ptr v) {
    return static_cast<message>(v);
}
__sklib_ptr __skadapter__to_sklib_server_socket(server_socket v) {
    return static_cast<__sklib_ptr>(v);
}
server_socket __skadapter__to_server_socket(__sklib_ptr v) {
    return static_cast<server_socket>(v);
}
__sklib_ptr __skadapter__to_sklib_sound_effect(sound_effect v) {
    return static_cast<__sklib_ptr>(v);
}
sound_effect __skadapter__to_sound_effect(__sklib_ptr v) {
    return static_cast<sound_effect>(v);
}
__sklib_ptr __skadapter__to_sklib_sprite(sprite v) {
    return static_cast<__sklib_ptr>(v);
}
sprite __skadapter__to_sprite(__sklib_ptr v) {
    return static_cast<sprite>(v);
}
__sklib_ptr __skadapter__to_sklib_timer(timer v) {
    return static_cast<__sklib_ptr>(v);
}
timer __skadapter__to_timer(__sklib_ptr v) {
    return static_cast<timer>(v);
}
__sklib_ptr __skadapter__to_sklib_animation(animation v) {
    return static_cast<__sklib_ptr>(v);
}
animation __skadapter__to_animation(__sklib_ptr v) {
    return static_cast<animation>(v);
}
__sklib_ptr __skadapter__to_sklib_animation_script(animation_script v) {
    return static_cast<__sklib_ptr>(v);
}
animation_script __skadapter__to_animation_script(__sklib_ptr v) {
    return static_cast<animation_script>(v);
}
__sklib_ptr __skadapter__to_sklib_bitmap(bitmap v) {
    return static_cast<__sklib_ptr>(v);
}
bitmap __skadapter__to_bitmap(__sklib_ptr v) {
    return static_cast<bitmap>(v);
}
__sklib_ptr __skadapter__to_sklib_display(display v) {
    return static_cast<__sklib_ptr>(v);
}
display __skadapter__to_display(__sklib_ptr v) {
    return static_cast<display>(v);
}
__sklib_ptr __skadapter__to_sklib_font(font v) {
    return static_cast<__sklib_ptr>(v);
}
font __skadapter__to_font(__sklib_ptr v) {
    return static_cast<font>(v);
}
__sklib_ptr __skadapter__to_sklib_http_response(http_response v) {
    return static_cast<__sklib_ptr>(v);
}
http_response __skadapter__to_http_response(__sklib_ptr v) {
    return static_cast<http_response>(v);
}
__sklib_ptr __skadapter__to_sklib_http_request(http_request v) {
    return static_cast<__sklib_ptr>(v);
}
http_request __skadapter__to_http_request(__sklib_ptr v) {
    return static_cast<http_request>(v);
}
__sklib_ptr __skadapter__to_sklib_web_server(web_server v) {
    return static_cast<__sklib_ptr>(v);
}
web_server __skadapter__to_web_server(__sklib_ptr v) {
    return static_cast<web_server>(v);
}
__sklib_ptr __skadapter__to_sklib_window(window v) {
    return static_cast<__sklib_ptr>(v);
}
window __skadapter__to_window(__sklib_ptr v) {
    return static_cast<window>(v);
}
int __skadapter__to_sklib_key_code(key_code v) {
    return static_cast<int>(v);
}
key_code __skadapter__to_key_code(int v) {
    return static_cast<key_code>(v);
}
int __skadapter__to_sklib_mouse_button(mouse_button v) {
    return static_cast<int>(v);
}
mouse_button __skadapter__to_mouse_button(int v) {
    return static_cast<mouse_button>(v);
}
int __skadapter__to_sklib_connection_type(connection_type v) {
    return static_cast<int>(v);
}
connection_type __skadapter__to_connection_type(int v) {
    return static_cast<connection_type>(v);
}
int __skadapter__to_sklib_resource_kind(resource_kind v) {
    return static_cast<int>(v);
}
resource_kind __skadapter__to_resource_kind(int v) {
    return static_cast<resource_kind>(v);
}
int __skadapter__to_sklib_collision_test_kind(collision_test_kind v) {
    return static_cast<int>(v);
}
collision_test_kind __skadapter__to_collision_test_kind(int v) {
    return static_cast<collision_test_kind>(v);
}
int __skadapter__to_sklib_sprite_event_kind(sprite_event_kind v) {
    return static_cast<int>(v);
}
sprite_event_kind __skadapter__to_sprite_event_kind(int v) {
    return static_cast<sprite_event_kind>(v);
}
int __skadapter__to_sklib_drawing_dest(drawing_dest v) {
    return static_cast<int>(v);
}
drawing_dest __skadapter__to_drawing_dest(int v) {
    return static_cast<drawing_dest>(v);
}
int __skadapter__to_sklib_font_style(font_style v) {
    return static_cast<int>(v);
}
font_style __skadapter__to_font_style(int v) {
    return static_cast<font_style>(v);
}
int __skadapter__to_sklib_http_status_code(http_status_code v) {
    return static_cast<int>(v);
}
http_status_code __skadapter__to_http_status_code(int v) {
    return static_cast<http_status_code>(v);
}
int __skadapter__to_sklib_http_method(http_method v) {
    return static_cast<int>(v);
}
http_method __skadapter__to_http_method(int v) {
    return static_cast<http_method>(v);
}
__sklib_matrix_2d __skadapter__to_sklib_matrix_2d(matrix_2d v) {
    __sklib_matrix_2d __skreturn;
    __skreturn.elements[0] = __skadapter__to_double(v.elements[0][0]);
    __skreturn.elements[1] = __skadapter__to_double(v.elements[0][1]);
    __skreturn.elements[2] = __skadapter__to_double(v.elements[0][2]);
    __skreturn.elements[3] = __skadapter__to_double(v.elements[1][0]);
    __skreturn.elements[4] = __skadapter__to_double(v.elements[1][1]);
    __skreturn.elements[5] = __skadapter__to_double(v.elements[1][2]);
    __skreturn.elements[6] = __skadapter__to_double(v.elements[2][0]);
    __skreturn.elements[7] = __skadapter__to_double(v.elements[2][1]);
    __skreturn.elements[8] = __skadapter__to_double(v.elements[2][2]);
    return __skreturn;
}
matrix_2d __skadapter__to_matrix_2d(__sklib_matrix_2d v) {
    matrix_2d __skreturn;
    __skreturn.elements[0][0] = __skadapter__to_double(v.elements[0]);
    __skreturn.elements[0][1] = __skadapter__to_double(v.elements[1]);
    __skreturn.elements[0][2] = __skadapter__to_double(v.elements[2]);
    __skreturn.elements[1][0] = __skadapter__to_double(v.elements[3]);
    __skreturn.elements[1][1] = __skadapter__to_double(v.elements[4]);
    __skreturn.elements[1][2] = __skadapter__to_double(v.elements[5]);
    __skreturn.elements[2][0] = __skadapter__to_double(v.elements[6]);
    __skreturn.elements[2][1] = __skadapter__to_double(v.elements[7]);
    __skreturn.elements[2][2] = __skadapter__to_double(v.elements[8]);
    return __skreturn;
}
__sklib_point_2d __skadapter__to_sklib_point_2d(point_2d v) {
    __sklib_point_2d __skreturn;
    __skreturn.x = __skadapter__to_double(v.x);
    __skreturn.y = __skadapter__to_double(v.y);
    return __skreturn;
}
point_2d __skadapter__to_point_2d(__sklib_point_2d v) {
    point_2d __skreturn;
    __skreturn.x = __skadapter__to_double(v.x);
    __skreturn.y = __skadapter__to_double(v.y);
    return __skreturn;
}
__sklib_circle __skadapter__to_sklib_circle(circle v) {
    __sklib_circle __skreturn;
    __skreturn.center = __skadapter__to_sklib_point_2d(v.center);
    __skreturn.radius = __skadapter__to_double(v.radius);
    return __skreturn;
}
circle __skadapter__to_circle(__sklib_circle v) {
    circle __skreturn;
    __skreturn.center = __skadapter__to_point_2d(v.center);
    __skreturn.radius = __skadapter__to_double(v.radius);
    return __skreturn;
}
__sklib_color __skadapter__to_sklib_color(color v) {
    __sklib_color __skreturn;
    __skreturn.r = __skadapter__to_float(v.r);
    __skreturn.g = __skadapter__to_float(v.g);
    __skreturn.b = __skadapter__to_float(v.b);
    __skreturn.a = __skadapter__to_float(v.a);
    return __skreturn;
}
color __skadapter__to_color(__sklib_color v) {
    color __skreturn;
    __skreturn.r = __skadapter__to_float(v.r);
    __skreturn.g = __skadapter__to_float(v.g);
    __skreturn.b = __skadapter__to_float(v.b);
    __skreturn.a = __skadapter__to_float(v.a);
    return __skreturn;
}
__sklib_rectangle __skadapter__to_sklib_rectangle(rectangle v) {
    __sklib_rectangle __skreturn;
    __skreturn.x = __skadapter__to_double(v.x);
    __skreturn.y = __skadapter__to_double(v.y);
    __skreturn.width = __skadapter__to_double(v.width);
    __skreturn.height = __skadapter__to_double(v.height);
    return __skreturn;
}
rectangle __skadapter__to_rectangle(__sklib_rectangle v) {
    rectangle __skreturn;
    __skreturn.x = __skadapter__to_double(v.x);
    __skreturn.y = __skadapter__to_double(v.y);
    __skreturn.width = __skadapter__to_double(v.width);
    __skreturn.height = __skadapter__to_double(v.height);
    return __skreturn;
}
__sklib_drawing_options __skadapter__to_sklib_drawing_options(drawing_options v) {
    __sklib_drawing_options __skreturn;
    __skreturn.dest = __skadapter__to_sklib_ptr(v.dest);
    __skreturn.scale_x = __skadapter__to_float(v.scale_x);
    __skreturn.scale_y = __skadapter__to_float(v.scale_y);
    __skreturn.angle = __skadapter__to_float(v.angle);
    __skreturn.anchor_offset_x = __skadapter__to_float(v.anchor_offset_x);
    __skreturn.anchor_offset_y = __skadapter__to_float(v.anchor_offset_y);
    __skreturn.flip_x = __skadapter__to_int(v.flip_x);
    __skreturn.flip_y = __skadapter__to_int(v.flip_y);
    __skreturn.is_part = __skadapter__to_int(v.is_part);
    __skreturn.part = __skadapter__to_sklib_rectangle(v.part);
    __skreturn.camera = __skadapter__to_int(v.camera);
    __skreturn.line_width = __skadapter__to_int(v.line_width);
    __skreturn.anim = __skadapter__to_sklib_animation(v.anim);
    __skreturn.draw_cell = __skadapter__to_int(v.draw_cell);
    return __skreturn;
}
drawing_options __skadapter__to_drawing_options(__sklib_drawing_options v) {
    drawing_options __skreturn;
    __skreturn.dest = __skadapter__to_sklib_ptr(v.dest);
    __skreturn.scale_x = __skadapter__to_float(v.scale_x);
    __skreturn.scale_y = __skadapter__to_float(v.scale_y);
    __skreturn.angle = __skadapter__to_float(v.angle);
    __skreturn.anchor_offset_x = __skadapter__to_float(v.anchor_offset_x);
    __skreturn.anchor_offset_y = __skadapter__to_float(v.anchor_offset_y);
    __skreturn.flip_x = __skadapter__to_bool(v.flip_x);
    __skreturn.flip_y = __skadapter__to_bool(v.flip_y);
    __skreturn.is_part = __skadapter__to_bool(v.is_part);
    __skreturn.part = __skadapter__to_rectangle(v.part);
    __skreturn.camera = __skadapter__to_drawing_dest(v.camera);
    __skreturn.line_width = __skadapter__to_int(v.line_width);
    __skreturn.anim = __skadapter__to_animation(v.anim);
    __skreturn.draw_cell = __skadapter__to_int(v.draw_cell);
    return __skreturn;
}
__sklib_line __skadapter__to_sklib_line(line v) {
    __sklib_line __skreturn;
    __skreturn.start_point = __skadapter__to_sklib_point_2d(v.start_point);
    __skreturn.end_point = __skadapter__to_sklib_point_2d(v.end_point);
    return __skreturn;
}
line __skadapter__to_line(__sklib_line v) {
    line __skreturn;
    __skreturn.start_point = __skadapter__to_point_2d(v.start_point);
    __skreturn.end_point = __skadapter__to_point_2d(v.end_point);
    return __skreturn;
}
__sklib_quad __skadapter__to_sklib_quad(quad v) {
    __sklib_quad __skreturn;
    __skreturn.points[0] = __skadapter__to_sklib_point_2d(v.points[0]);
    __skreturn.points[1] = __skadapter__to_sklib_point_2d(v.points[1]);
    __skreturn.points[2] = __skadapter__to_sklib_point_2d(v.points[2]);
    __skreturn.points[3] = __skadapter__to_sklib_point_2d(v.points[3]);
    return __skreturn;
}
quad __skadapter__to_quad(__sklib_quad v) {
    quad __skreturn;
    __skreturn.points[0] = __skadapter__to_point_2d(v.points[0]);
    __skreturn.points[1] = __skadapter__to_point_2d(v.points[1]);
    __skreturn.points[2] = __skadapter__to_point_2d(v.points[2]);
    __skreturn.points[3] = __skadapter__to_point_2d(v.points[3]);
    return __skreturn;
}
__sklib_triangle __skadapter__to_sklib_triangle(triangle v) {
    __sklib_triangle __skreturn;
    __skreturn.points[0] = __skadapter__to_sklib_point_2d(v.points[0]);
    __skreturn.points[1] = __skadapter__to_sklib_point_2d(v.points[1]);
    __skreturn.points[2] = __skadapter__to_sklib_point_2d(v.points[2]);
    return __skreturn;
}
triangle __skadapter__to_triangle(__sklib_triangle v) {
    triangle __skreturn;
    __skreturn.points[0] = __skadapter__to_point_2d(v.points[0]);
    __skreturn.points[1] = __skadapter__to_point_2d(v.points[1]);
    __skreturn.points[2] = __skadapter__to_point_2d(v.points[2]);
    return __skreturn;
}
__sklib_vector_2d __skadapter__to_sklib_vector_2d(vector_2d v) {
    __sklib_vector_2d __skreturn;
    __skreturn.x = __skadapter__to_double(v.x);
    __skreturn.y = __skadapter__to_double(v.y);
    return __skreturn;
}
vector_2d __skadapter__to_vector_2d(__sklib_vector_2d v) {
    vector_2d __skreturn;
    __skreturn.x = __skadapter__to_double(v.x);
    __skreturn.y = __skadapter__to_double(v.y);
    return __skreturn;
}
void (*__skadapter__to_key_callback(__sklib_key_callback *v))(int code) {
    return v;
}
void (*__skadapter__to_sklib_key_callback(key_callback *v))(int code) {
    return v;
}
void (*__skadapter__to_free_notifier(__sklib_free_notifier *v))(__sklib_ptr pointer) {
    return v;
}
void (*__skadapter__to_sklib_free_notifier(free_notifier *v))(__sklib_ptr pointer) {
    return v;
}
void (*__skadapter__to_sprite_event_handler(__sklib_sprite_event_handler *v))(__sklib_ptr s, int evt) {
    return v;
}
void (*__skadapter__to_sklib_sprite_event_handler(sprite_event_handler *v))(__sklib_ptr s, int evt) {
    return v;
}
void (*__skadapter__to_sprite_float_function(__sklib_sprite_float_function *v))(__sklib_ptr s, float f) {
    return v;
}
void (*__skadapter__to_sklib_sprite_float_function(sprite_float_function *v))(__sklib_ptr s, float f) {
    return v;
}
void (*__skadapter__to_sprite_function(__sklib_sprite_function *v))(__sklib_ptr s) {
    return v;
}
void (*__skadapter__to_sklib_sprite_function(sprite_function *v))(__sklib_ptr s) {
    return v;
}
void __skadapter__free__sklib_vector_line(__sklib_vector_line v) {
    free(v.data_from_app);
}
__sklib_vector_line __skadapter__to_sklib_vector_line(const std::vector<line> &v) {
    __sklib_vector_line __skreturn;
    __skreturn.size_from_lib = 0;
    __skreturn.data_from_lib = nullptr;
    __skreturn.size_from_app = static_cast<unsigned int>(v.size());
    __skreturn.data_from_app = (__sklib_line *)malloc(__skreturn.size_from_app * sizeof(__sklib_line));
    unsigned int i = 0;
    for (line d : v) {
        __skreturn.data_from_app[i] = __skadapter__to_sklib_line(d);
        i++;
    }
    return __skreturn;
}
vector<line> __skadapter__to_vector_line(const __sklib_vector_line &v) {
    vector<line> __skreturn;
    for (int i = 0; i < v.size_from_lib; i++) {
        __skreturn.push_back(__skadapter__to_line(v.data_from_lib[i]));
    }
    __sklib__free__sklib_vector_line(v);
    return __skreturn;
}
void __skadapter__update_from_vector_line(__sklib_vector_line &v, std::vector<line> &__skreturn) {
    __skreturn.clear();
    for (int i = 0; i < v.size_from_lib; i++) {
        line d = __skadapter__to_line(v.data_from_lib[i]);
        __skreturn.push_back(d);
    }
        __sklib__free__sklib_vector_line(v);
}
void __skadapter__free__sklib_vector_int8_t(__sklib_vector_int8_t v) {
    free(v.data_from_app);
}
__sklib_vector_int8_t __skadapter__to_sklib_vector_int8_t(const std::vector<int8_t> &v) {
    __sklib_vector_int8_t __skreturn;
    __skreturn.size_from_lib = 0;
    __skreturn.data_from_lib = nullptr;
    __skreturn.size_from_app = static_cast<unsigned int>(v.size());
    __skreturn.data_from_app = (unsigned char *)malloc(__skreturn.size_from_app * sizeof(unsigned char));
    unsigned int i = 0;
    for (int8_t d : v) {
        __skreturn.data_from_app[i] = __skadapter__to_sklib_int8_t(d);
        i++;
    }
    return __skreturn;
}
vector<int8_t> __skadapter__to_vector_int8_t(const __sklib_vector_int8_t &v) {
    vector<int8_t> __skreturn;
    for (int i = 0; i < v.size_from_lib; i++) {
        __skreturn.push_back(__skadapter__to_int8_t(v.data_from_lib[i]));
    }
    __sklib__free__sklib_vector_int8_t(v);
    return __skreturn;
}
void __skadapter__update_from_vector_int8_t(__sklib_vector_int8_t &v, std::vector<int8_t> &__skreturn) {
    __skreturn.clear();
    for (int i = 0; i < v.size_from_lib; i++) {
        int8_t d = __skadapter__to_int8_t(v.data_from_lib[i]);
        __skreturn.push_back(d);
    }
        __sklib__free__sklib_vector_int8_t(v);
}
void __skadapter__free__sklib_vector_triangle(__sklib_vector_triangle v) {
    free(v.data_from_app);
}
__sklib_vector_triangle __skadapter__to_sklib_vector_triangle(const std::vector<triangle> &v) {
    __sklib_vector_triangle __skreturn;
    __skreturn.size_from_lib = 0;
    __skreturn.data_from_lib = nullptr;
    __skreturn.size_from_app = static_cast<unsigned int>(v.size());
    __skreturn.data_from_app = (__sklib_triangle *)malloc(__skreturn.size_from_app * sizeof(__sklib_triangle));
    unsigned int i = 0;
    for (triangle d : v) {
        __skreturn.data_from_app[i] = __skadapter__to_sklib_triangle(d);
        i++;
    }
    return __skreturn;
}
vector<triangle> __skadapter__to_vector_triangle(const __sklib_vector_triangle &v) {
    vector<triangle> __skreturn;
    for (int i = 0; i < v.size_from_lib; i++) {
        __skreturn.push_back(__skadapter__to_triangle(v.data_from_lib[i]));
    }
    __sklib__free__sklib_vector_triangle(v);
    return __skreturn;
}
void __skadapter__update_from_vector_triangle(__sklib_vector_triangle &v, std::vector<triangle> &__skreturn) {
    __skreturn.clear();
    for (int i = 0; i < v.size_from_lib; i++) {
        triangle d = __skadapter__to_triangle(v.data_from_lib[i]);
        __skreturn.push_back(d);
    }
        __sklib__free__sklib_vector_triangle(v);
}
void __skadapter__free__sklib_vector_string(__sklib_vector_string v) {
    for (unsigned int i = 0; i < v.size_from_app; i++) {
        __skadapter__free__sklib_string(v.data_from_app[i]);
    }
    free(v.data_from_app);
}
__sklib_vector_string __skadapter__to_sklib_vector_string(const std::vector<string> &v) {
    __sklib_vector_string __skreturn;
    __skreturn.size_from_lib = 0;
    __skreturn.data_from_lib = nullptr;
    __skreturn.size_from_app = static_cast<unsigned int>(v.size());
    __skreturn.data_from_app = (__sklib_string *)malloc(__skreturn.size_from_app * sizeof(__sklib_string));
    unsigned int i = 0;
    for (string d : v) {
        __skreturn.data_from_app[i] = __skadapter__to_sklib_string(d);
        i++;
    }
    return __skreturn;
}
vector<string> __skadapter__to_vector_string(const __sklib_vector_string &v) {
    vector<string> __skreturn;
    for (int i = 0; i < v.size_from_lib; i++) {
        __skreturn.push_back(__skadapter__to_string(v.data_from_lib[i]));
    }
    __sklib__free__sklib_vector_string(v);
    return __skreturn;
}
void __skadapter__update_from_vector_string(__sklib_vector_string &v, std::vector<string> &__skreturn) {
    __skreturn.clear();
    for (int i = 0; i < v.size_from_lib; i++) {
        string d = __skadapter__to_string(v.data_from_lib[i]);
        __skreturn.push_back(d);
    }
        __sklib__free__sklib_vector_string(v);
}
void __skadapter__free__sklib_vector_double(__sklib_vector_double v) {
    free(v.data_from_app);
}
__sklib_vector_double __skadapter__to_sklib_vector_double(const std::vector<double> &v) {
    __sklib_vector_double __skreturn;
    __skreturn.size_from_lib = 0;
    __skreturn.data_from_lib = nullptr;
    __skreturn.size_from_app = static_cast<unsigned int>(v.size());
    __skreturn.data_from_app = (double *)malloc(__skreturn.size_from_app * sizeof(double));
    unsigned int i = 0;
    for (double d : v) {
        __skreturn.data_from_app[i] = __skadapter__to_sklib_double(d);
        i++;
    }
    return __skreturn;
}
vector<double> __skadapter__to_vector_double(const __sklib_vector_double &v) {
    vector<double> __skreturn;
    for (int i = 0; i < v.size_from_lib; i++) {
        __skreturn.push_back(__skadapter__to_double(v.data_from_lib[i]));
    }
    __sklib__free__sklib_vector_double(v);
    return __skreturn;
}
void __skadapter__update_from_vector_double(__sklib_vector_double &v, std::vector<double> &__skreturn) {
    __skreturn.clear();
    for (int i = 0; i < v.size_from_lib; i++) {
        double d = __skadapter__to_double(v.data_from_lib[i]);
        __skreturn.push_back(d);
    }
        __sklib__free__sklib_vector_double(v);
}
void __skadapter__free__sklib_vector_json(__sklib_vector_json v) {
    free(v.data_from_app);
}
__sklib_vector_json __skadapter__to_sklib_vector_json(const std::vector<json> &v) {
    __sklib_vector_json __skreturn;
    __skreturn.size_from_lib = 0;
    __skreturn.data_from_lib = nullptr;
    __skreturn.size_from_app = static_cast<unsigned int>(v.size());
    __skreturn.data_from_app = (__sklib_json *)malloc(__skreturn.size_from_app * sizeof(__sklib_json));
    unsigned int i = 0;
    for (json d : v) {
        __skreturn.data_from_app[i] = __skadapter__to_sklib_json(d);
        i++;
    }
    return __skreturn;
}
vector<json> __skadapter__to_vector_json(const __sklib_vector_json &v) {
    vector<json> __skreturn;
    for (int i = 0; i < v.size_from_lib; i++) {
        __skreturn.push_back(__skadapter__to_json(v.data_from_lib[i]));
    }
    __sklib__free__sklib_vector_json(v);
    return __skreturn;
}
void __skadapter__update_from_vector_json(__sklib_vector_json &v, std::vector<json> &__skreturn) {
    __skreturn.clear();
    for (int i = 0; i < v.size_from_lib; i++) {
        json d = __skadapter__to_json(v.data_from_lib[i]);
        __skreturn.push_back(d);
    }
        __sklib__free__sklib_vector_json(v);
}
void __skadapter__free__sklib_vector_bool(__sklib_vector_bool v) {
    free(v.data_from_app);
}
__sklib_vector_bool __skadapter__to_sklib_vector_bool(const std::vector<bool> &v) {
    __sklib_vector_bool __skreturn;
    __skreturn.size_from_lib = 0;
    __skreturn.data_from_lib = nullptr;
    __skreturn.size_from_app = static_cast<unsigned int>(v.size());
    __skreturn.data_from_app = (int *)malloc(__skreturn.size_from_app * sizeof(int));
    unsigned int i = 0;
    for (bool d : v) {
        __skreturn.data_from_app[i] = __skadapter__to_sklib_bool(d);
        i++;
    }
    return __skreturn;
}
vector<bool> __skadapter__to_vector_bool(const __sklib_vector_bool &v) {
    vector<bool> __skreturn;
    for (int i = 0; i < v.size_from_lib; i++) {
        __skreturn.push_back(__skadapter__to_bool(v.data_from_lib[i]));
    }
    __sklib__free__sklib_vector_bool(v);
    return __skreturn;
}
void __skadapter__update_from_vector_bool(__sklib_vector_bool &v, std::vector<bool> &__skreturn) {
    __skreturn.clear();
    for (int i = 0; i < v.size_from_lib; i++) {
        bool d = __skadapter__to_bool(v.data_from_lib[i]);
        __skreturn.push_back(d);
    }
        __sklib__free__sklib_vector_bool(v);
}
