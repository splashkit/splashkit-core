//
// SplashKit Generated Sprites C++ Code
// DO NOT MODIFY
//

#ifndef __sprites_h
#define __sprites_h

#include "matrix_2d.h"
#include "types.h"
#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
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
/**
* Call the supplied function for all sprites in the current pack.
* @param fn The sprite function to call on all sprites.
* @param val The value passed to the function for each sprite.
*
*/
void call_for_all_sprites(sprite_float_function *fn, float val);
/**
* Call the supplied function for all sprites in the current pack.
* @param fn The sprite function to call on all sprites.
*
*/
void call_for_all_sprites(sprite_function *fn);
/**
* Register a procedure to be called when an events occur on any sprite.
* @param handler The function to call when any sprite raises an event
*
*/
void call_on_sprite_event(sprite_event_handler *handler);
/**
* Creates a sprite for the passed in bitmap image. The sprite will use the
* cell information within the bitmap if it is animated at a later stage.
* 
* This version of create_sprite will initialise the sprite to use
* pixel level collisions, no animations, and have one layer named 'layer1'.
* This version of the constructor will assign a default name to the sprite
* for resource management purposes.
* @param layer The bitmap for the sprite's image.
* @return The new sprite with image.
*/
sprite create_sprite(bitmap layer);
/**
* Creates a sprite for the passed in bitmap image. The sprite will use the
* cell information within the bitmap if it is animated at a later stage.
* This version of `create_sprite` will initialise the sprite to use
* pixel level collisions, the specified animation template, the layer have
* name 'layer1'.
* 
* This version of the constructor will assign a default name to the sprite
* for resource management purposes.
* @param layer The bitmap for the sprite's image.
* @param ani The animation script for the sprite's animations.
* @return The new sprite with image and animation script.
*/
sprite create_sprite(bitmap layer, animation_script ani);
/**
* Creates a sprite for the passed in bitmap image. The sprite will use the
* cell information within the bitmap if it is animated at a later stage.
* 
* This version of create_sprite will initialise the sprite to use
* pixel level collisions, no animations, and have one layer named 'layer1'.
* This version of the constructor will assign a default name to the sprite
* for resource management purposes.
* @param bitmap_name The name of the bitmap to use as the sprite's layer
* @return The new sprite with image.
*/
sprite create_sprite(const string &bitmap_name);
/**
* Creates a sprite for the passed in bitmap image. The sprite will use the
* cell information within the sprite if it is animated at a later stage.
* This version of create_sprite will initialise the sprite to use pixel level
* collisions, no animation, the layer have name 'layer1'.
* @param name The name of the sprite for resource management.
* @param layer The bitmap for the sprite's image.
* @return The new sprite with image and name.
*/
sprite create_sprite(const string &name, bitmap layer);
/**
* Creates a sprite for the passed in bitmap image. The sprite will use the cell
* information within the sprite if it is animated at a later stage. This
* version of create_sprite will initialise the sprite to use pixel level
* collisions, the specified animation template, the layer have name 'layer1'.
* @param name The name of the sprite for resource management.
* @param layer The bitmap for the sprite's image.
* @param ani The animation script for the sprite's animations.
* @return The new sprite with image, animation, and name.
*/
sprite create_sprite(const string &name, bitmap layer, animation_script ani);
/**
* Creates a sprite. The bitmap_name is used to indicate the bitmap the sprite
* will use, and the animation_name is used to indicate which animation_script
* to use.
* @param bitmap_name The name of the bitmap to use as the sprite's image.
* @param animation_name The name of the animation script to use for this
* sprite.
* @return The new sprite with the image and animation.
*/
sprite create_sprite(const string &bitmap_name, const string &animation_name);
/**
* Create a new sprite_pack with a given name. This pack can then be
* selected and used to control which sprites are drawn/updated in
* the calls to draw_all_sprites and update_all_sprites.
* @param name The name of the new sprite pack.
*
*/
void create_sprite_pack(const string &name);
/**
* Returns the name of the currently selected sprite_pack.

* @return The name of the current sprite pack.
*/
string current_sprite_pack();
/**
* draws all of the sprites in the current sprite pack. Packs can be
* switched to select between different sets of sprites.

*
*/
void draw_all_sprites();
/**
* Draws the sprite at its position in the game offset by a given amount. Only
* use this method when you want to draw the sprite displaced from its location
* in your game. Otherwise you should change the sprite's location and then
* use the standard ''draw_sprite'' routine.
* @param s The sprite to draw.
* @param offset The amount to offset the sprite.
*
*/
void draw_sprite(sprite s, const vector_2d &offset);
/**
* Draws the sprite at its location in the world. This is affected by the
* position of the camera and the sprites current location.
* 
* This is the standard routine for drawing sprites to the screen and should be
* used in most cases.
* @param s The sprite to draw.
*
*/
void draw_sprite(sprite s);
/**
* Draws the sprite at its position in the game offset by a given amount. Only
* use this method when you want to draw the sprite displaced from its location
* in your game. Otherwise you should change the sprite's location and then
* use the standard `draw_sprite` routine.
* @param s The sprite to draw.
* @param x_offset The amount to offset on the x axis.
* @param y_offset The amount to offset on the y axis.
*
*/
void draw_sprite(sprite s, double x_offset, double y_offset);
/**
* Releases all of the sprites that have been loaded.

*
*/
void free_all_sprites();
/**
* Free the resources associated with a sprite.
* @param s The sprite to be destroyed.
*
*/
void free_sprite(sprite s);
/**
* Frees the sprite pack and all of its sprites.
* @param name The name of the sprite pack to destroy.
*
*/
void free_sprite_pack(const string &name);
/**
* Determines if SplashKit has a sprite for the supplied name.
* This checks against all sprites, those loaded without a name
* are assigned a default.
* @param name The name of the sprite to locate.
* @return True if you have created a sprite with this name.
*/
bool has_sprite(const string &name);
/**
* Indicates if a given sprite_pack has already been created.
* @param name The name for the sprite pack.
* @return True if a sprite pack exists with the indicated name.
*/
bool has_sprite_pack(const string &name);
/**
* moves the sprite as indicated by its velocity. You can call this directly ot
* alternatively, this action is performed when the sprite is updated using
* the ''update_sprite'' routine.
* @param s The sprite to move.
*
*/
void move_sprite(sprite s);
/**
* Moves the sprite a given distance based on the value passed in rather than
* based on the sprite's velocity. Typically this method is used to apply
* other movement actions to the sprite and the velocity of the sprite is
* used the intended movement of the sprite.
* @param s The sprite to move.
* @param distance The vector that represents the direction and distance to
* move the sprite.
*
*/
void move_sprite(sprite s, const vector_2d &distance);
/**
* Moves the sprite a percentage of a given distance based on the value
* passed in rather than based on the sprite's velocity. Typically this
* method is used to apply other movement actions to the sprite and the
* velocity of the sprite is used the intended movement of the sprite.
* @param s The sprite to move.
* @param distance The vector that represents the direction and distance to
* move the sprite.
* @param pct The percentage of the distance to move the sprite.
*
*/
void move_sprite(sprite s, const vector_2d &distance, float pct);
/**
* Moves the sprite as indicated by a percentage of its velocity. You can call
* this directly ot alternatively, this action is performed when the sprite is
* updated using the ''update_sprite'' routines that require a percentage.
* @param s The sprite to move.
* @param pct The percentage of the sprite's velocity to move.
*
*/
void move_sprite(sprite s, float pct);
/**
* This method moves a sprite to a given position in the game.
* @param s The sprite to move.
* @param x The sprite's new x location.
* @param y The sprite's new y location.
*
*/
void move_sprite_to(sprite s, double x, double y);
/**
* Selects the named sprite_pack (if it has been created). The
* selected sprite_pack determines which sprites are drawn and updated
* with the draw_all_sprites and update_all_sprites code.
* @param name The name of the sprite pack to select.
*
*/
void select_sprite_pack(const string &name);
/**
* Adds a new layer to the sprite.
* @param s The sprite to add the layer to.
* @param new_layer The new layer's bitmap.
* @param layer_name The name of the new layer.
* @return The index of the new layer.
*/
int sprite_add_layer(sprite s, bitmap new_layer, const string &layer_name);
/**
* Alters the current velocity of the sprite, adding the passed in vector_2d to the current velocity.
* When the sprite is updated (see `update_sprite`)
* this vector_2d is used to move the sprite.
* @param s The sprite to change.
* @param value The amount to add to the sprite's velocity.
*
*/
void sprite_add_to_velocity(sprite s, const vector_2d &value);
/**
* Adds a new kind of value to the sprite
* @param s The sprite to change.
* @param name The name of the new value to store in the sprite.
*
*/
void sprite_add_value(sprite s, const string &name);
/**
* Adds a new kind of value to the sprite, setting the initial value
* to the value passed in.
* @param s The sprite to change.
* @param name The name of the new value to store in the sprite.
* @param init_val The initial value.
*
*/
void sprite_add_value(sprite s, const string &name, float init_val);
/**
* Returns the anchor point of the sprite. This is the point around which the
* sprite rotates. This is in sprite coordinates, so as if the sprite is drawn
* at 0,0.
* @param s The sprite to get the details from.
* @return The anchor point of the sprite.
*/
point_2d sprite_anchor_point(sprite s);
/**
* The sprite anchor position, is the location of the anchor point in world
* coordinates, based upon the position of the sprite.
* @param s The sprite to find where the anchor is in world coordinates
* @return The location of the sprite's anchor point positioned at the sprite's location
*/
point_2d sprite_anchor_position(sprite s);
/**
* Indicates if the sprites animation has ended.
* @param s The sprite to get the details from.
* @return True if the sprite animation has ended.
*/
bool sprite_animation_has_ended(sprite s);
/**
* Returns the name of the sprite's current animation.
* @param s The sprite to get the details from.
* @return The name of the current animation.
*/
string sprite_animation_name(sprite s);
/**
* Determines if a sprite is at a given point.
* @param s The sprite to test
* @param pt The point to check (in world coordinates)
* @return True if the sprite is at the given point
*/
bool sprite_at(sprite s, const point_2d &pt);
/**
* Sends the layer specified forward in the visible layer order.
* @param s The sprite to change
* @param visible_layer The visible layer to bring forward
*
*/
void sprite_bring_layer_forward(sprite s, int visible_layer);
/**
* Sends the layer specified to the front in the visible layer order.
* @param s The sprite to change
* @param visible_layer The visible layer to bring to the front
*
*/
void sprite_bring_layer_to_front(sprite s, int visible_layer);
/**
* Register a procedure to call when events occur on the sprite.
* @param s The sprite to add the handler to.
* @param handler The function to call when this sprite raises an event.
*
*/
void sprite_call_on_event(sprite s, sprite_event_handler *handler);
/**
* Returns the center point of the passed in sprite. This is based on the sprite's
* Position, Width and Height.
* @param s The sprite to get the details from.
* @return The center point of the sprite
*/
point_2d sprite_center_point(sprite s);
/**
* Gets a circle in the bounds of the base layer of the indicated sprite.
* @param s The sprite to get the details from.
* @return A bounding circle that surrounds the sprite
*/
circle sprite_circle(sprite s);
/**
* Returns the bitmap used by the sprite to determine if it has collided with
* other objects in the game.
* @param s The sprite to get the details from.
* @return The bitmap used for collisions with this sprite.
*/
bitmap sprite_collision_bitmap(sprite s);
/**
* Gets a circle in the bounds of the indicated sprite's collision rectangle.
* @param s The sprite to get the details from.
* @return A bounding circle that surrounds the sprite
*/
circle sprite_collision_circle(sprite s);
/**
* Returns the kind of collision used with this sprite. This is used when
* determining if the sprite has collided with other objects in the game.
* @param s The sprite to get the details from.
* @return The kind of collisions performed with this sprite.
*/
collision_test_kind sprite_collision_kind(sprite s);
/**
* Returns the collision rectangle for the specified sprite.
* @param s The sprite to get the details from.
* @return A collision rectangle that surrounds the sprite.
*/
rectangle sprite_collision_rectangle(sprite s);
/**
* Returns the current animation cell for an animated sprite. The cell is
* updated when the sprite's animation data is updated.
* @param s The sprite to get the details from.
* @return The current cell animation of the sprite.
*/
int sprite_current_cell(sprite s);
/**
* Returns a rectangle of the current cell within the sprite's image. This is used
* to determine what part of the bitmap should be used when the sprite is drawn.
* @param s The sprite to get the details from.
* @return The current cell rectangle of the sprite.
*/
rectangle sprite_current_cell_rectangle(sprite s);
/**
* Returns the X value of the sprite's velocity.
* @param s The sprite to get the details from.
* @return The x component of the sprite's velocity.
*/
double sprite_dx(sprite s);
/**
* Returns the Y value of the sprite's velocity.
* @param s The sprite to get the details from.
* @return The y component of the sprite's velocity.
*/
double sprite_dy(sprite s);
/**
* Indicates if the sprite has a value with the given name.
* @param s The sprite to get the details from.
* @param name The name of the value to check.
* @return True if the sprite has a value with that name.
*/
bool sprite_has_value(sprite s, string name);
/**
* Returns the direction the sprite is heading in degrees.
* @param s The sprite to get the details from.
* @return The angle of the sprite velocity.
*/
float sprite_heading(sprite s);
/**
* The current height of the sprite (aligned to the Y axis).
* @param s The sprite to get the details from.
* @return The height of the sprite in pixels.
*/
int sprite_height(sprite s);
/**
* Hide the specified layer of the sprite.
* @param s The sprite to hide the layer of.
* @param name The name of the layer to hide.
*
*/
void sprite_hide_layer(sprite s, const string &name);
/**
* Hide the specified layer of the sprite.
* @param s The sprite to hide the layer of.
* @param id The index of the layer to hide.
*
*/
void sprite_hide_layer(sprite s, int id);
/**
* Returns the bitmap of the indicated layer of the sprite.
* @param s The sprite to get the layer from
* @param name The name of the layer to fetch
* @return The bitmap at the layer with the indicated name
*/
bitmap sprite_layer(sprite s, const string &name);
/**
* Returns the bitmap of the indicated layer of the sprite.
* @param s The sprite to get the layer from
* @param idx The index of the layer
* @return The bitmap of the sprite at that layer
*/
bitmap sprite_layer(sprite s, int idx);
/**
* Gets a circle in the bounds of the indicated layer.
* @param s The sprite to get the details from.
* @param name The name of the layer.
* @return A bounding circle that surrounds the sprite's layer
*/
circle sprite_layer_circle(sprite s, const string &name);
/**
* Gets a circle in the bounds of the indicated layer.
* @param s The sprite to get the details from.
* @param idx The index of the layer.
* @return A bounding circle that surrounds the sprite's layer
*/
circle sprite_layer_circle(sprite s, int idx);
/**
* Returns the number of layers within the sprite.
* @param s The sprite to get the layer count from.
* @return The number of image layers in the sprite.
*/
int sprite_layer_count(sprite s);
/**
* The height of a given layer of the sprite (aligned to the Y axis).
* @param s The sprite to get the details from.
* @param name The name of the layer to get the details of.
* @return The height of the sprite's layer in pixels.
*/
int sprite_layer_height(sprite s, const string &name);
/**
* The height of a given layer of the sprite (aligned to the Y axis).
* @param s The sprite to get the details from.
* @param idx The index of the layer to get the details of.
* @return The height of the sprite's layer in pixels.
*/
int sprite_layer_height(sprite s, int idx);
/**
* Returns the index of the specified layer.
* @param s The sprite to get the layer from
* @param name The name of the layer to get the index of
* @return The index of the layer in the sprite
*/
int sprite_layer_index(sprite s, const string &name);
/**
* Returns the name of the specified layer.
* @param s The sprite to get the layer name from
* @param idx The index of the layer you want the name of
* @return The name of the sprite's layer at that index
*/
string sprite_layer_name(sprite s, int idx);
/**
* Gets the offset of the specified layer.
* @param s The sprite to get the details from.
* @param name The name of the layer to get the offset of.
* @return The offset of the named layer in the sprite.
*/
vector_2d sprite_layer_offset(sprite s, const string &name);
/**
* Gets the offset of the specified layer.
* @param s The sprite to get the details from.
* @param idx The index of the layer to get the offset of.
* @return The offset of the layer in the sprite.
*/
vector_2d sprite_layer_offset(sprite s, int idx);
/**
* Gets a rectangle that surrounds the indicated layer.
* @param s The sprite to get the details from.
* @param name The name of the layer.
* @return A bounding rectangle that surrounds the sprite's layer
*/
rectangle sprite_layer_rectangle(sprite s, const string &name);
/**
* Gets a rectangle that surrounds the indicated layer.
* @param s The sprite to get the details from.
* @param idx The index of the layer.
* @return A bounding rectangle that surrounds the sprite's layer
*/
rectangle sprite_layer_rectangle(sprite s, int idx);
/**
* The width of a given layer of the sprite (aligned to the X axis).
* @param s The sprite to get the details from.
* @param name The name of the layer to get the details of.
* @return The width of the sprite's layer in pixels.
*/
int sprite_layer_width(sprite s, const string &name);
/**
* The width of a given layer of the sprite (aligned to the X axis).
* @param s The sprite to get the details from.
* @param idx The index of the layer to get the details of.
* @return The width of the sprite's layer in pixels.
*/
int sprite_layer_width(sprite s, int idx);
/**
* Returns a matrix that can be used to transform points into the coordinate
* space of the passed in sprite.
* @param s The sprite to get the details from.
* @return A matrix that transforms points into the sprites coordinate
space.
*/
matrix_2d sprite_location_matrix(sprite s);
/**
* This indicates the mass of the sprite for any of the collide methods from
* Physics. The mass of two colliding sprites will determine the relative
* velocitys after the collision.
* @param s The sprite to get the details from.
* @return The mass of the sprite.
*/
float sprite_mass(sprite s);
/**
* Indicates if the sprite is moved from its anchor point, or from its top left.
* When this returns true the location of the sprite will indicate its anchor point.
* When this returns false the location of the sprite is its top left corner.
* @param s The sprite to get the details of.
* @return True if the sprite moves from its anchor point.
*/
bool sprite_move_from_anchor_point(sprite s);
/**
* This void starts the sprite moving to the indicated
* destination point, over a specified number of seconds. When the
* sprite arrives it will raise the sprite_arrived event.
* @param s The sprite to move.
* @param pt The sprite's destination.
* @param taking_seconds The time the sprite should take to get to pt.
*
*/
void sprite_move_to(sprite s, const point_2d &pt, float taking_seconds);
/**
* Returns the name of the sprite. This name is used for resource management
* and can be used to interact with the sprite in various routines.
* @param s The sprite to get the details from.
* @return The name of the sprite.
*/
string sprite_name(sprite s);
/**
* Returns the `sprite` with the specified name.
* @param name The name of the sprite to locate.
* @return The sprite with that name.
*/
sprite sprite_named(const string &name);
/**
* Returns true if the sprite is entirely off the current screen.
* @param s The sprite to test.
* @return True if the sprite is entirely off the current window.
*/
bool sprite_offscreen(sprite s);
/**
* Returns true if a pixel of the `sprite` `s` is at the screen location
* specified (`pt`), which is converted to a world location.
* @param s The sprite to test.
* @param pt The location in screen coordinates to check.
* @return True if the sprite would draw something at this coordinate on
the screen when drawn.
*/
bool sprite_on_screen_at(sprite s, const point_2d &pt);
/**
* Returns true if a pixel of the `sprite` `s` is at the screen location
* specified.
* @param s The sprite to test.
* @param x The x location in screen coordinates to check.
* @param y The y location in screen coordinates to check.
* @return True if the sprite would draw something at this coordinate on
the screen when drawn.
*/
bool sprite_on_screen_at(sprite s, double x, double y);
/**
* Returns the sprite's position.
* @param s The sprite to get the details from.
* @return The location of the sprite.
*/
point_2d sprite_position(sprite s);
/**
* Restart the sprite's current animation, this will play a sound if the
* first cell of the animation is associated with a sound effect.
* @param s The sprite to replay the animation of.
*
*/
void sprite_replay_animation(sprite s);
/**
* Restart the sprite's current animation, this will play a sound if
* with_sound is true and the first cell of the animation is associated
* with a sound effect.
* @param s The sprite to replay the animation of.
* @param with_sound If false, the animation will not play associated sound
* effects when restarted.
*
*/
void sprite_replay_animation(sprite s, bool with_sound);
/**
* This indicates the angle of rotation of the sprite. This will rotate any
* images of the sprite before drawing, which can be very slow. avoid using
* this method with bitmap based sprites where possible.
* @param s The sprite to get the details from.
* @return The angle of the sprite rotation.
*/
float sprite_rotation(sprite s);
/**
* This indicates the scale of the sprite. This will scale any
* images of the sprite before drawing, which can be very slow. avoid using
* this method with bitmap based sprites where possible.
* @param s The sprite to get the details from.
* @return The scale of the sprite.
*/
float sprite_scale(sprite s);
/**
* Returns the rectangle representing the location of the sprite on the
* screen.
* @param s The sprite to get the details from.
* @return A rectangle indicating where the sprite is on the screen.
*/
rectangle sprite_screen_rectangle(sprite s);
/**
* Sends the layer specified backward in the visible layer order.
* @param s The sprite to change
* @param visible_layer The visible layer to send to backward
*
*/
void sprite_send_layer_backward(sprite s, int visible_layer);
/**
* Sends the layer specified to the back in the visible layer order.
* @param s The sprite to change
* @param visible_layer The visible layer to send to back
*
*/
void sprite_send_layer_to_back(sprite s, int visible_layer);
/**
* Allows you to set the anchor point for the sprite. This is the point around
* which the sprite rotates. This is in sprite coordinates, as if the sprite
* is drawn at 0,0.
* @param s The sprite to change.
* @param pt The new anchor point in sprite coordinates.
*
*/
void sprite_set_anchor_point(sprite s, const point_2d &pt);
/**
* Sets the bitmap used by the sprite to determine if it has collided with
* other objects in the game. By default the collision_bitmap is set to the
* bitmap from the sprite's first layer.
* @param s The sprite to change.
* @param bmp The new collision bitmap for the sprite.
*
*/
void sprite_set_collision_bitmap(sprite s, bitmap bmp);
/**
* Sets the kind of collision used with this sprite. This is used when
* determining if the sprite has collided with other objects in the game.
* @param s The sprite to change.
* @param value The new kind of collision test for this sprite.
*
*/
void sprite_set_collision_kind(sprite s, collision_test_kind value);
/**
* Sets the X value of the sprite's velocity.
* @param s The sprite to change.
* @param value The new x component of the sprite's velocity.
*
*/
void sprite_set_dx(sprite s, double value);
/**
* Sets the Y value of the sprite's velocity.
* @param s The sprite to change.
* @param value The new y component of the sprite's velocity.
*
*/
void sprite_set_dy(sprite s, double value);
/**
* Alters the direction the sprite is heading without changing the speed.
* @param s The sprite to change.
* @param value The new angle for the sprite's velocity -- distance remains the
* same.
*
*/
void sprite_set_heading(sprite s, float value);
/**
* Sets the offset of the specified layer. The offset is used when the layer
* is drawn in the sprite, and moves the image relative to the sprite.
* @param s The sprite to change.
* @param name The name of the layer to change.
* @param value The new offset.
*
*/
void sprite_set_layer_offset(sprite s, const string &name, const vector_2d &value);
/**
* Sets the offset of the specified layer.
* @param s The sprite to change.
* @param idx The index of the layer to change.
* @param value The new offset.
*
*/
void sprite_set_layer_offset(sprite s, int idx, const vector_2d &value);
/**
* Allows you to change the mass of a sprite.
* @param s The sprite to change.
* @param value The new mass for the sprite.
*
*/
void sprite_set_mass(sprite s, float value);
/**
* Allows you to indicate if the sprite is moved from its anchor point, or from its
* top left.
* 
* When set to true the location of the sprite will be its anchor point.
* When set to false the location of the sprite is its top left corner.
* @param s The sprite to change.
* @param value The value to set this option.
*
*/
void sprite_set_move_from_anchor_point(sprite s, bool value);
/**
* Sets the sprite's position.
* @param s The sprite to change.
* @param value The new location for the sprite.
*
*/
void sprite_set_position(sprite s, const point_2d &value);
/**
* Allows you to change the rotation of a sprite.
* @param s The sprite to change.
* @param value The new rotation angle for the sprite
*
*/
void sprite_set_rotation(sprite s, float value);
/**
* Allows you to change the scale of a sprite.
* @param s The sprite to change.
* @param value The new scale for the sprite.
*
*/
void sprite_set_scale(sprite s, float value);
/**
* Alters the speed of the sprite without effecting the direction.
* @param s The sprite to change.
* @param value The new speed of the sprite -- direction will remain the same.
*
*/
void sprite_set_speed(sprite s, double value);
/**
* Assigns a value to the sprite.
* @param s The sprite to change.
* @param name The name of the value to change
* @param val The new value.
*
*/
void sprite_set_value(sprite s, const string &name, float val);
/**
* Sets the current velocity of the sprite. When the sprite is updated
* (see `update_sprite`) this vector_2d is used to move the sprite.
* @param s The sprite to change.
* @param value The new sprite velocity.
*
*/
void sprite_set_velocity(sprite s, const vector_2d &value);
/**
* Sets the X position of the sprite.
* @param s The sprite to change.
* @param value The new x location.
*
*/
void sprite_set_x(sprite s, double value);
/**
* Sets the Y position of the sprite.
* @param s The sprite to change.
* @param value The new sprite y.
*
*/
void sprite_set_y(sprite s, double value);
/**
* Show the specified layer of the sprite.
* @param s The sprite to show the layer of.
* @param name The layer to show.
* @return The index of the layer shown, or -1 if no layer found.
*/
int sprite_show_layer(sprite s, const string &name);
/**
* Show the specified layer of the sprite.
* @param s The sprite to show the layer of.
* @param id The index to show.
* @return The index of the layer shown, or -1 if no layer found.
*/
int sprite_show_layer(sprite s, int id);
/**
* Returns the current speed (distance travelled per update) of the sprite.
* @param s The sprite to get the details from.
* @return The speed of the sprite (pixels per update).
*/
double sprite_speed(sprite s);
/**
* Start playing an animation from the sprite's animation template.
* This will play a sound effect if the first cell of the animation
* has a sound.
* @param s The sprite to start the animation of.
* @param named The name of the animation to start from the animation script.
*
*/
void sprite_start_animation(sprite s, const string &named);
/**
* Start playing an animation from the sprite's animation template.
* The with_sound parameter determines whether to play a sound effect
* if the first cell of the animation has a sound.
* @param s The sprite to start the animation of.
* @param named The name of the animation to start from the animation script.
* @param with_sound If false, the animation will not play associated sound
* effects when started.
*
*/
void sprite_start_animation(sprite s, const string &named, bool with_sound);
/**
* Start playing an animation from the sprite's animation template.
* This will play a sound effect if the first cell of the animation
* has a sound.
* @param s The sprite to start the animation of.
* @param idx The index of the animation to start from the animation script.
*
*/
void sprite_start_animation(sprite s, int idx);
/**
* Start playing an animation from the sprite's animation template.
* The with_sound parameter determines whether to play a sound effect
* if the first cell of the animation has a sound.
* @param s The sprite to start the animation of.
* @param idx The index of the animation to start from the animation script.
* @param with_sound If false, the animation will not play associated sound
* effects when started.
*
*/
void sprite_start_animation(sprite s, int idx, bool with_sound);
/**
* Removes an event handler from the sprite, stopping events from this
* sprite calling the indicated method.
* @param s The sprite to remove the handler from
* @param handler The function to remove from this sprites handlers
*
*/
void sprite_stop_calling_on_event(sprite s, sprite_event_handler *handler);
/**
* Toggle the visibility of the specified layer of the sprite.
* @param s The sprite to change.
* @param name The name of the layer to toggle.
*
*/
void sprite_toggle_layer_visible(sprite s, const string &name);
/**
* Toggle the visibility of the specified layer of the sprite.
* @param s The sprite to change.
* @param id The index of the layer to toggle.
*
*/
void sprite_toggle_layer_visible(sprite s, int id);
/**
* Returns the indicated value of the sprite
* @param s The sprite to get the details from.
* @param name The name of the value to fetch.
* @return The value from the sprite's data store.
*/
float sprite_value(sprite s, const string &name);
/**
* Returns the number of sprite's values.
* @param s The sprite to get the details from.
* @return The number of values stored in the sprite.
*/
int sprite_value_count(sprite s);
/**
* Returns the current velocity of the sprite. When the sprite is updated
* (see `update_sprite`) this vector_2d is used to move the sprite.
* @param s The sprite to get the details from.
* @return The sprite's velocity.
*/
vector_2d sprite_velocity(sprite s);
/**
* Returns the index (z-order) of the sprite's layer.
* @param s The sprite to get the details from.
* @param name The name of the layer to get the z index of.
* @return The z index of the sprite's layer
*/
int sprite_visible_index_of_layer(sprite s, const string &name);
/**
* Returns the index (z-order) of the sprite's layer.
* @param s The sprite to get the details from.
* @param id The index of the layer to get the z index of.
* @return The z index of the sprite's layer
*/
int sprite_visible_index_of_layer(sprite s, int id);
/**
* Returns the index of the n'th (idx parameter) visible layer.
* @param s The sprite to get the details from.
* @param idx The index of the visible layer to fetch.
* @return The layer index of the selected visible layer.
*/
int sprite_visible_layer(sprite s, int idx);
/**
* Returns the number of layers that are currently visible for the sprite.
* @param s The sprite to get the details from.
* @return The number of visible layers for the sprite.
*/
int sprite_visible_layer_count(sprite s);
/**
* Returns the id of the layer at index `idx` that is currently visible.
* Index 0 is the background, with larger indexes moving toward the foreground.
* This returns -1 if there are no visible layers.
* @param s The sprite to get the details from.
* @param idx The index of the visible layer.
* @return The layer index of the visible layer.
*/
int sprite_visible_layer_id(sprite s, int idx);
/**
* The current Width of the sprite (aligned to the X axis).
* @param s The sprite to get the details from.
* @return The width of the sprite's layer in pixels.
*/
int sprite_width(sprite s);
/**
* Returns the X position of the sprite.
* @param s The sprite to get the details from.
* @return The x location of the sprite
*/
double sprite_x(sprite s);
/**
* Returns the Y position of the sprite.
* @param s The sprite to get the details from.
* @return The sprite's y location.
*/
double sprite_y(sprite s);
/**
* Removes an global event handler, stopping events calling the indicated void.
* @param handler The function to remove from the list of sprite event handlers.
*
*/
void stop_calling_on_sprite_event(sprite_event_handler *handler);
/**
* Update all of the sprites in the current sprite pack.

*
*/
void update_all_sprites();
/**
* Update all of the sprites in the current sprite pack, passing in a
* percentage value to indicate the percentage to update.
* @param pct The percentage of the update to apply.
*
*/
void update_all_sprites(float pct);
/**
* Update the position and animation details of the sprite.
* This will play a sound effect if the new cell of the animation
* has a sound.
* @param s The sprite to update.
*
*/
void update_sprite(sprite s);
/**
* Update the position and animation details of the sprite.
* This will play a sound effect if the new cell of the animation
* has a sound and with_sound is true.
* @param s The sprite to update
* @param with_sound If false, animations will not play associated sound
* effects when updated.
*
*/
void update_sprite(sprite s, bool with_sound);
/**
* Update the position and animation details of the sprite by a
* given percentage of a single unit of movement/animation.
* This will play a sound effect if the new cell of the animation
* has a sound.
* @param s The sprite to update.
* @param pct The percent to update.
*
*/
void update_sprite(sprite s, float pct);
/**
* Update the position and animation details of the sprite by a
* given percentage of a single unit of movement/animation.
* This will play a sound effect if the new cell of the animation
* has a sound and with_sound is true.
* @param s The sprite to update.
* @param pct The percent to update.
* @param with_sound If false, animations will not play associated sound
* effects when updated.
*
*/
void update_sprite(sprite s, float pct, bool with_sound);
/**
* Updates the animation details of the sprite.
* This will play a sound effect if the new cell of the animation
* has a sound.
* @param s The sprite to update.
*
*/
void update_sprite_animation(sprite s);
/**
* Update the animation details of the sprite.
* This will play a sound effect if the new cell of the animation
* has a sound and with_sound is true.
* @param s The sprite to update.
* @param with_sound If false, animations will not play associated sound
* effects when updated.
*
*/
void update_sprite_animation(sprite s, bool with_sound);
/**
* Update the animation details of the sprite by a
* given percentage of a single unit of movement/animation.
* This will play a sound effect if the new cell of the animation
* has a sound.
* @param s The sprite to update.
* @param pct The percent to update.
*
*/
void update_sprite_animation(sprite s, float pct);
/**
* Update the position and animation details of the sprite by a
* given percentage of a single unit of movement/animation.
* This will play a sound effect if the new cell of the animation
* has a sound and with_sound is true.
* @param s The sprite to update.
* @param pct The percent to update.
* @param with_sound If false, animations will not play associated sound
* effects when updated.
*
*/
void update_sprite_animation(sprite s, float pct, bool with_sound);
/**
* Returns a `vector_2d` that is the difference in location from the center of
* the sprite `s` to the point `pt`.
* @param s The sprite that is at the start of the vector.
* @param pt The point that is at the end of the vector.
* @return A vector pointing from the sprite to the point.
*/
vector_2d vector_from_center_sprite_to_point(sprite s, const point_2d &pt);
/**
* Returns a `vector_2d` that is the difference in the position of two sprites
* (`s1` and `s2`).
* @param s1 The sprite that is at the start of the vector.
* @param s2 The sprite that is at the end of the vector.
* @return A vector that points from s1 to s2.
*/
vector_2d vector_from_to(sprite s1, sprite s2);

#endif /* __sprites_h */
