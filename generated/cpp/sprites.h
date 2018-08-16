//
// SplashKit Generated Sprites C++ Code
// DO NOT MODIFY
//

#ifndef __sprites_h
#define __sprites_h

#include "types.h"
#include "matrix_2d.h"
#include "sprites.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

struct _sprite_data;
typedef struct _sprite_data *sprite;
typedef enum {
    PIXEL_COLLISIONS,
    AABB_COLLISIONS
} collision_test_kind;
typedef enum {
    SPRITE_ARRIVED_EVENT,
    SPRITE_ANIMATION_ENDED_EVENT,
    SPRITE_TOUCHED_EVENT,
    SPRITE_CLICKED_EVENT
} sprite_event_kind;
typedef void (sprite_event_handler)(void *s, int evt);
typedef void (sprite_float_function)(void *s, float f);
typedef void (sprite_function)(void *s);
void call_for_all_sprites(sprite_float_function *fn, float val);
void call_for_all_sprites(sprite_function *fn);
void call_on_sprite_event(sprite_event_handler *handler);
point_2d center_point(sprite s);
sprite create_sprite(bitmap layer);
sprite create_sprite(bitmap layer, animation_script ani);
sprite create_sprite(const string &bitmap_name);
sprite create_sprite(const string &name, bitmap layer);
sprite create_sprite(const string &name, bitmap layer, animation_script ani);
sprite create_sprite(const string &bitmap_name, const string &animation_name);
void create_sprite_pack(const string &name);
string current_sprite_pack();
void draw_all_sprites();
void draw_sprite(sprite s, const vector_2d &offset);
void draw_sprite(sprite s);
void draw_sprite(sprite s, double x_offset, double y_offset);
void free_all_sprites();
void free_sprite(sprite s);
void free_sprite_pack(const string &name);
bool has_sprite(const string &name);
bool has_sprite_pack(const string &name);
void move_sprite(sprite s);
void move_sprite(sprite s, const vector_2d &distance);
void move_sprite(sprite s, const vector_2d &distance, float pct);
void move_sprite(sprite s, float pct);
void move_sprite_to(sprite s, double x, double y);
void select_sprite_pack(const string &name);
int sprite_add_layer(sprite s, bitmap new_layer, const string &layer_name);
void sprite_add_to_velocity(sprite s, const vector_2d &value);
void sprite_add_value(sprite s, const string &name);
void sprite_add_value(sprite s, const string &name, float init_val);
point_2d sprite_anchor_point(sprite s);
point_2d sprite_anchor_position(sprite s);
bool sprite_animation_has_ended(sprite s);
string sprite_animation_name(sprite s);
bool sprite_at(sprite s, const point_2d &pt);
void sprite_bring_layer_forward(sprite s, int visible_layer);
void sprite_bring_layer_to_front(sprite s, int visible_layer);
void sprite_call_on_event(sprite s, sprite_event_handler *handler);
circle sprite_circle(sprite s);
bitmap sprite_collision_bitmap(sprite s);
circle sprite_collision_circle(sprite s);
collision_test_kind sprite_collision_kind(sprite s);
rectangle sprite_collision_rectangle(sprite s);
int sprite_current_cell(sprite s);
rectangle sprite_current_cell_rectangle(sprite s);
float sprite_dx(sprite s);
float sprite_dy(sprite s);
bool sprite_has_value(sprite s, string name);
float sprite_heading(sprite s);
int sprite_height(sprite s);
void sprite_hide_layer(sprite s, const string &name);
void sprite_hide_layer(sprite s, int id);
bitmap sprite_layer(sprite s, const string &name);
bitmap sprite_layer(sprite s, int idx);
circle sprite_layer_circle(sprite s, const string &name);
circle sprite_layer_circle(sprite s, int idx);
int sprite_layer_count(sprite s);
int sprite_layer_height(sprite s, const string &name);
int sprite_layer_height(sprite s, int idx);
int sprite_layer_index(sprite s, const string &name);
string sprite_layer_name(sprite s, int idx);
vector_2d sprite_layer_offset(sprite s, const string &name);
vector_2d sprite_layer_offset(sprite s, int idx);
rectangle sprite_layer_rectangle(sprite s, const string &name);
rectangle sprite_layer_rectangle(sprite s, int idx);
int sprite_layer_width(sprite s, const string &name);
int sprite_layer_width(sprite s, int idx);
matrix_2d sprite_location_matrix(sprite s);
float sprite_mass(sprite s);
bool sprite_move_from_anchor_point(sprite s);
void sprite_move_to(sprite s, const point_2d &pt, float taking_seconds);
string sprite_name(sprite s);
sprite sprite_named(const string &name);
bool sprite_offscreen(sprite s);
bool sprite_on_screen_at(sprite s, const point_2d &pt);
bool sprite_on_screen_at(sprite s, double x, double y);
point_2d sprite_position(sprite s);
void sprite_replay_animation(sprite s);
void sprite_replay_animation(sprite s, bool with_sound);
float sprite_rotation(sprite s);
float sprite_scale(sprite s);
rectangle sprite_screen_rectangle(sprite s);
void sprite_send_layer_backward(sprite s, int visible_layer);
void sprite_send_layer_to_back(sprite s, int visible_layer);
void sprite_set_anchor_point(sprite s, const point_2d &pt);
void sprite_set_collision_bitmap(sprite s, bitmap bmp);
void sprite_set_collision_kind(sprite s, collision_test_kind value);
void sprite_set_dx(sprite s, float value);
void sprite_set_dy(sprite s, float value);
void sprite_set_heading(sprite s, float value);
void sprite_set_layer_offset(sprite s, const string &name, const vector_2d &value);
void sprite_set_layer_offset(sprite s, int idx, const vector_2d &value);
void sprite_set_mass(sprite s, float value);
void sprite_set_move_from_anchor_point(sprite s, bool value);
void sprite_set_position(sprite s, const point_2d &value);
void sprite_set_rotation(sprite s, float value);
void sprite_set_scale(sprite s, float value);
void sprite_set_speed(sprite s, float value);
void sprite_set_value(sprite s, const string &name, float val);
void sprite_set_velocity(sprite s, const vector_2d &value);
void sprite_set_x(sprite s, float value);
void sprite_set_y(sprite s, float value);
int sprite_show_layer(sprite s, const string &name);
int sprite_show_layer(sprite s, int id);
float sprite_speed(sprite s);
void sprite_start_animation(sprite s, const string &named);
void sprite_start_animation(sprite s, const string &named, bool with_sound);
void sprite_start_animation(sprite s, int idx);
void sprite_start_animation(sprite s, int idx, bool with_sound);
void sprite_stop_calling_on_event(sprite s, sprite_event_handler *handler);
void sprite_toggle_layer_visible(sprite s, const string &name);
void sprite_toggle_layer_visible(sprite s, int id);
float sprite_value(sprite s, const string &name);
int sprite_value_count(sprite s);
vector_2d sprite_velocity(sprite s);
int sprite_visible_index_of_layer(sprite s, const string &name);
int sprite_visible_index_of_layer(sprite s, int id);
int sprite_visible_layer(sprite s, int idx);
int sprite_visible_layer_count(sprite s);
int sprite_visible_layer_id(sprite s, int idx);
int sprite_width(sprite s);
float sprite_x(sprite s);
float sprite_y(sprite s);
void stop_calling_on_sprite_event(sprite_event_handler *handler);
void update_all_sprites();
void update_all_sprites(float pct);
void update_sprite(sprite s);
void update_sprite(sprite s, bool with_sound);
void update_sprite(sprite s, float pct);
void update_sprite(sprite s, float pct, bool with_sound);
void update_sprite_animation(sprite s);
void update_sprite_animation(sprite s, bool with_sound);
void update_sprite_animation(sprite s, float pct);
void update_sprite_animation(sprite s, float pct, bool with_sound);
vector_2d vector_from_center_sprite_to_point(sprite s, const point_2d &pt);
vector_2d vector_from_to(sprite s1, sprite s2);

#endif /* __sprites_h */
