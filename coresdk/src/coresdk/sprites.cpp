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
    pointer_identifier id;
    string name;                          // The name of the sprite for resource management
    
    vector<bitmap>      layers;           // Layers of the sprites
    map<string, int>    layer_names;
    vector<int>         visible_layers;   // The indexes of the visible layers
    vector<point_2d>    layer_offsets;    // Offsets from drawing the layers
    
    map<string, float>  values;           // Values associated with this sprite

    
    animation           animation_info;   // The data used to animate this sprite
    animation_script    script;           // The template for this sprite's animations
    
    point_2d            position;         // The game location of the sprite
    vector_2d           velocity;         // The velocity of the sprite
    
    collision_test_kind collision_kind;   //The kind of collisions used by this sprite
    bitmap              collision_bitmap; // The bitmap used for collision testing (default to first image)
    
    point_2d            anchor_point;
    bool                position_at_anchor_point;
    
    bool                is_moving;          // Used for events to indicate the sprite is moving
    point_2d            destination;        // The destination the sprite is moving to
    vector_2d           moving_vec;         // The sprite's movement vector
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
// loop through all event listeners and notify them of the event
//
void sprite_raise_event(sprite s, sprite_event_kind evt)
{
    if ( INVALID_PTR(s, SPRITE_PTR) )
    {
        raise_warning("Attempting to use invalid sprite");
        return;
    }
    int i;
    
    // this sprite's event handlers
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
    result->layer_offsets.push_back(point_at(0,0));
    
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

    // Write_ln('adding for ', name, ' ', Hex_str(obj));
    _sprites[name] = result;
    
    (*__current_pack).push_back(result);
    
    return result;
}



bool has_sprite(const string &name)
{
    return _sprites.count(name) > 0;
}

sprite sprite_named(const string &name)
{
    if (has_sprite(name))
        return _sprites[name];
    else
        return nullptr;
}
