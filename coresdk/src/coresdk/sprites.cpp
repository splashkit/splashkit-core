//
//  sprites.cpp
//  splashkit
//
//  Created by Andrew Cain on 23/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "sprites.h"

#include "utility_functions.h"
#include "backend_types.h"
#include "timers.h"
#include "vector_2d.h"
#include "images.h"
#include "geometry.h"

#include "resource_event_notifications.h"

#include <map>
#include <vector>
using namespace std;


vector<vector<sprite>> _sprite_packs;
vector<sprite> *__current_pack = nullptr;

timer _sprite_timer;
vector<sprite_event_handler *> _global_sprite_event_handlers;

map<string, sprite> _sprites;

struct _sprite_data
{
    pointer_identifier  id;
    string name;                          // The name of the sprite for resource management

    vector<bitmap>      layers;           // Layers of the sprites
    map<string, int>    layer_names;
    vector<int>         visible_layers;   // The indexes of the visible layers
    vector<vector_2d>   layer_offsets;    // Offsets from drawing the layers

    map<string, float>  values;           // Values associated with this sprite


    animation           animation_info;   // The data used to animate this sprite
    animation_script    script;           // The template for this sprite"s animations

    point_2d            position;         // The game location of the sprite
    vector_2d           velocity;         // The velocity of the sprite

    collision_test_kind collision_kind;   //The kind of collisions used by this sprite
    bitmap              collision_bitmap; // The bitmap used for collision testing (default to first image)

    point_2d            anchor_point;
    bool                position_at_anchor_point;

    bool                is_moving;          // Used for events to indicate the sprite is moving
    point_2d            destination;        // The destination the sprite is moving to
    vector_2d           moving_vec;         // The sprite"s movement vector
    float               arrive_in_sec;      // Amount of time in seconds to arrive at point
    int                 last_update;        // Time of last update

    bool                announced_animation_end; // Used to avoid multiple announcements of an end of an animation

    vector<sprite_event_handler *> evts;    // The call backs listening for sprite events

    vector<sprite>      &pack;              // Points the the SpritePack that contains this sprite

    _sprite_data() : pack(*__current_pack)
    {
    }
};


//-----------------------------------------------------------------------------
// Event Utility Code
//-----------------------------------------------------------------------------

//
// loop through all event listeners and notif(y them of the event )
//
void sprite_raise_event(sprite s, sprite_event_kind evt)
{
    if( ( INVALID_PTR(s, SPRITE_PTR) ) )
    {
        raise_warning("Attempting to use invalid sprite");
        return;
    }
    int i;

    // this sprite"s event handlers
    for (i = 0; i < s->evts.size(); i++)
    {
        s->evts[i](s, evt);
    }

    // global sprite event handlers
    for (i = 0; i < _global_sprite_event_handlers.size(); i++)
    {
        _global_sprite_event_handlers[i](s, evt);
    }
}


//-----------------------------------------------------------------------------
// Vector stuff...
//-----------------------------------------------------------------------------


vector_2d  vector_from_to(sprite s1, sprite s2)
{
    return vector_point_to_point(center_point(s1), center_point(s2));
}

vector_2d  vector_from_center_sprite_to_point(sprite s, const point_2d &pt)
{
    return vector_point_to_point(center_point(s), pt);
}

//-----------------------------------------------------------------------------
// Sprite creation...
//-----------------------------------------------------------------------------

sprite create_sprite(bitmap layer)
{
    return create_sprite(layer, nullptr);
}

sprite create_sprite(const string &bitmap_name, const string &animation_name)
{
    return create_sprite(bitmap_named(bitmap_name), animation_script_named(animation_name));
}

sprite create_sprite(bitmap layer, animation_script ani)
{
    return create_sprite("sprite", layer, ani);
}

sprite create_sprite(const string &name, bitmap layer)
{
    return create_sprite(name, layer, nullptr);
}

sprite create_sprite(const string &name, bitmap layer, animation_script ani)
{
    string sn;
    int idx;

    // Find a unique name for this sprite
    idx = 0;
    sn = name;

    while (has_sprite(sn))
    {
        sn = name + to_string(idx);
        idx += 1;
    }

    //allocate the space for the sprite
    sprite result = new _sprite_data();

    result->id = SPRITE_PTR;
    result->name = sn;

    //Set lengths of the layer arrays
    result->layer_names["base_layer"] = 0;
    result->layers.push_back(layer);
    result->layer_offsets.push_back(vector_to(0,0));

    result->anchor_point = point_at(bitmap_width(layer) / 2, bitmap_height(layer) / 2);
    result->position_at_anchor_point = false;

    // Set the first layer as visible.
    result->visible_layers.push_back(0);                //The first layer (at idx 0) is drawn

    // Setup the values
    result->values["mass"] = 1;
    result->values["rotation"] = 0;
    result->values["scale"] = 1;

    // Position the sprite
    result->position = point_at(0,0);

    // Initialise sprite movement
    result->velocity = vector_to(0,0);

    // Setup animation detials
    result->script         = ani;
    result->animation_info           = nullptr;

    // Setup collision details
    result->collision_kind           = PIXEL_COLLISIONS;
    result->collision_bitmap         = layer;

    // Event details
    result->announced_animation_end = false;
    result->is_moving = false;
    result->destination = point_at(0,0);
    result->moving_vec = vector_to(0,0);
    result->arrive_in_sec = 0;
    result->last_update = timer_ticks(_sprite_timer);

    // Write_ln("adding for ", name, " ", Hex_str(obj));
    _sprites[name] = result;

    (*__current_pack).push_back(result);

    return result;
}

//-----------------------------------------------------------------------------
// Free sprites
//-----------------------------------------------------------------------------

void free_sprite(sprite s)
{
    if( (INVALID_PTR(s, SPRITE_PTR)) )
    {
        raise_warning("Attempting to free invalid sprite");
        return;
    }

    //Dispose sprite
    notify_handlers_of_free(s);

    // Free pointers
    if( (ASSIGNED(s->animation_info)) )
        free_animation(s->animation_info);

    // nullptr pointers to resources managed by sgResources
    s->script = nullptr;

    //Free buffered rotation image
    s->collision_bitmap = nullptr;

    if( ( not erase_from_vector(s->pack, s) ) )
    {
        raise_warning("Error removing sprite from sprite pack!");
    }

    // Remove from hashtable
    // Write_ln("Freeing sprite named: ", s->name);
    _sprites.erase(s->name);

    s->id = NONE_PTR;
    delete s;
}

void free_all_sprites()
{
    FREE_ALL_FROM_MAP(_sprites, SPRITE_PTR, free_sprite);
}


//-----------------------------------------------------------------------------
// Sprite fetching functions
//-----------------------------------------------------------------------------

bool has_sprite(const string &name)
{
    return _sprites.count(name) > 0;
}

sprite sprite_named(const string &name)
{
    if( (has_sprite(name)) )
        return _sprites[name];
    else
        return nullptr;
}

//-----------------------------------------------------------------------------
// Sprite layer code
//-----------------------------------------------------------------------------


int  sprite_add_layer(sprite s, bitmap new_layer, const string &layer_names)
{
    if( INVALID_PTR(new_layer, BITMAP_PTR) )
    {
        raise_warning("Cannot add non-existing bitmap as layer to sprite");
        return -1;
    }

    if( INVALID_PTR(s, SPRITE_PTR)  )
    {
        raise_warning("No sprite to add layer to");
        return -1;
    }

    s->layers.push_back(new_layer);
    int result = static_cast<int>(s->layers.size() - 1);
    s->layer_names[layer_names] = result;
    s->layer_offsets.push_back(vector_to(0,0));

    return result;
}

bool sprite_has_layer(sprite s, const string &name)
{
    if ( INVALID_PTR(s, SPRITE_PTR) )
    {
        raise_warning("Attempting to access layer details of invalid sprite");
        return false;
    }
    else
    {
        return s->layer_names.count(name) > 0;
    }
}

bool sprite_has_layer(sprite s, int idx)
{
    if ( INVALID_PTR(s, SPRITE_PTR) )
    {
        raise_warning("Attempting to access layer details of invalid sprite");
        return false;
    }
    else
    {
        return idx >= 0 and idx < s->layers.size();
    }
}

bitmap  sprite_layer(sprite s, const string &name)
{
    if ( not sprite_has_layer(s, name) )
    {
        return nullptr;
    }
    else
    {
        return sprite_layer(s, s->layer_names[name]);
    }
}

bitmap  sprite_layer(sprite s, int idx)
{
    if ( not sprite_has_layer(s, idx) )
    {
        return nullptr;
    }

    return s->layers[idx];
}

int  sprite_layer_index(sprite s, const string &name)
{
    if( not sprite_has_layer(s, name) )
        return -1;
    else
        return s->layer_names[name];
}

string  sprite_layer_name(sprite s, int idx)
{
    if ( sprite_has_layer(s, idx) )
    {
        return "";
    }
    else
    {
        auto find_result = std::find_if(std::begin(s->layer_names), std::end(s->layer_names), [&](const std::pair<string, int> &pair)
        {
            return pair.second == idx;
        });

        if (find_result != std::end(s->layer_names))
        {
            return find_result->first;
        }
        else
        {
            raise_warning("Sprite has invalid state. Please report this issue to the SplashKit dev team.");
            return "";
        }
    }
}

int  sprite_show_layer(sprite s, const string &name)
{
    if ( not sprite_has_layer(s, name) )
        return -1;
    else
        return sprite_show_layer(s, s->layer_names[name]);
}

int  sprite_show_layer(sprite s, int id)
{
    if( not sprite_has_layer(s, id) )
        return -1;

    //Scan for the current ID
    int result = sprite_visible_index_of_layer(s, id);
    if ( result >= 0 ) return result;

    //Extend layers and add index
    s->visible_layers.push_back(id);

    return static_cast<int>(s->visible_layers.size() - 1);
}

void sprite_hide_layer(sprite s, const string &name)
{
    if ( not sprite_has_layer(s, name) )
        return;
    else
        sprite_hide_layer(s, s->layer_names[name]);
}

void sprite_hide_layer(sprite s, int id)
{
    if ( not sprite_has_layer(s, id) )
        return;

    erase_from_vector(s->visible_layers, id);
}

void sprite_toggle_layer_visible(sprite s, const string &name)
{
    if ( not sprite_has_layer(s, name) )
        return;
    else
        sprite_toggle_layer_visible(s, s->layer_names[name]);
}

void sprite_toggle_layer_visible(sprite s, int id)
{
    if ( not sprite_has_layer(s, id) ) return;

    if ( sprite_visible_index_of_layer(s, id) < 0 )
        sprite_show_layer(s, id);
    else
        sprite_hide_layer(s, id);
}

int  sprite_layer_count(sprite s)
{
    if ( INVALID_PTR(s, SPRITE_PTR) )
    {
        raise_warning("Attempting to access layer details of invalid sprite");
        return -1;
    }
    else return static_cast<int>(s->layers.size());
}

int  sprite_visible_layer_count(sprite s)
{
    if ( INVALID_PTR(s, SPRITE_PTR) )
    {
        raise_warning("Attempting to access layer details of invalid sprite");
        return -1;
    }
    else return static_cast<int>(s->visible_layers.size());
}

bool sprite_has_visible_layer(sprite s, int idx)
{
    if ( INVALID_PTR(s, SPRITE_PTR) )
    {
        raise_warning("Attempting to access layer details of invalid sprite");
        return false;
    }
    else
        return idx >= 0 && idx < s->visible_layers.size();
}

int sprite_visible_layer_id(sprite s, int idx)
{
    if ( not sprite_has_visible_layer(s, idx) ) return -1;
    else
        return s->visible_layers[idx];
}

vector_2d  sprite_layer_offset(sprite s, const string &name)
{
    if ( not sprite_has_layer(s, name) ) return vector_to(0,0);
    else return sprite_layer_offset(s, s->layer_names[name]);
}

vector_2d  sprite_layer_offset(sprite s, int idx)
{
    if ( not sprite_has_layer(s, idx) ) return vector_to(0,0);
    else return s->layer_offsets[idx];
}

void sprite_set_layer_offset(sprite s, const string &name, const vector_2d &value)
{
    if ( not sprite_has_layer(s, name) ) return;
    sprite_set_layer_offset(s, s->layer_names[name], value);
}

void sprite_set_layer_offset(sprite s, int idx, const vector_2d &value)
{
    if ( not sprite_has_layer(s, idx) )
        return;
    s->layer_offsets[idx] = value;
}

int sprite_visible_index_of_layer(sprite s, const string &name)
{
    if ( not sprite_has_layer(s, name) ) return -1;
    else return sprite_visible_index_of_layer(s, s->layer_names[name]);
}

int  sprite_visible_index_of_layer(sprite s, int id)
{
    if ( not sprite_has_layer(s, id) )
        return -1;
    else
        return index_of(s->visible_layers, id);
}

int  sprite_visible_layer(sprite s, int idx)
{
    if ( not sprite_has_layer(s, idx) ) return -1;
    else return s->visible_layers[idx];
}

void sprite_send_layer_to_back(sprite s, int visible_layer)
{
    if ( not sprite_has_visible_layer(s, visible_layer) ) return;

    if ( visible_layer < s->visible_layers.size() - 1 )
        move_range(s->visible_layers, sprite_visible_index_of_layer(s, visible_layer), 1, s->visible_layers.size() - 1 );
}

void sprite_send_layer_backward(sprite s, int visible_layer)
{
    if( not sprite_has_visible_layer(s, visible_layer) ) return;

    if ( visible_layer < s->visible_layers.size() - 1 )
        swap(s->visible_layers[visible_layer], s->visible_layers[visible_layer + 1]);
}

void sprite_bring_layer_forward(sprite s, int visible_layer)
{
    if( not sprite_has_visible_layer(s, visible_layer) ) return;

    if ( visible_layer > 0 )
        swap(s->visible_layers[visible_layer], s->visible_layers[visible_layer - 1]);
}

void sprite_bring_layer_to_front(sprite s, int visible_layer)
{
    if( not sprite_has_visible_layer(s, visible_layer) ) return;

    if ( visible_layer > 0 )
        move_range(s->visible_layers, sprite_visible_index_of_layer(s, visible_layer), 1, 0 );
}

rectangle  sprite_layer_rectangle(sprite s, const string &name)
{
    if ( not sprite_has_layer(s, name) )
        return rectangle_from(0,0,0,0);
    else
        return sprite_layer_rectangle(s, s->layer_names[name]);
}

rectangle  sprite_layer_rectangle(sprite s, int idx)
{
    if ( not sprite_has_layer(s, idx) )
        return rectangle_from(0,0,0,0);
    else
        return bitmap_cell_rectangle(s->layers[idx], point_offset_by(s->position, s->layer_offsets[idx]));
}
