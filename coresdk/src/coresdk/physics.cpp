//
//  physics.cpp
//  splashkit
//
//  Created by Clancy Light Townsend on 18/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "physics.h"
#include <algorithm>
#define M_PI 3.14159265358979323846264338327950288

using namespace splashkit_lib;
Box2DContext::Box2DContext()
{
    options = option_defaults();
    options.scale_x = SCALE_X;
    options.scale_y = SCALE_Y;
    default_body_definition.position.Set(0, 0);
}
std::pair<sprite, b2Body*>* Box2DContext::add_sprite_to_world(sprite s, const b2BodyDef& bodyDef)
{
    b2BodyDef definition{bodyDef};
    definition.position.Set(
        (sprite_position(s).x + (sprite_width(s)/2)) / options.scale_x,
        (sprite_position(s).y + (sprite_height(s)/2)) / options.scale_y
    );
    definition.angle = sprite_rotation(s) * M_PI / 180.0f;
	b2Body* body = world.CreateBody(&definition);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(sprite_width(s)/options.scale_y/2, sprite_height(s)/options.scale_y/2);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);
    auto pair = new std::pair<sprite, b2Body*>{s, body};
    sprites_in_the_world.push_back(pair);
    return pair;
}
auto Box2DContext::find_sprite(sprite sprite){
    return std::find_if(sprites_in_the_world.begin(), sprites_in_the_world.end(),
    [&](auto& valueTest){
        return sprite == valueTest->first;
    });

}
sprite Box2DContext::remove_sprite_from_world(sprite sprite){
    sprites_in_the_world.erase(find_sprite(sprite));
    return sprite;
}

const std::pair<sprite, b2Body *>* Box2DContext::find(sprite sprite){
    return *(find_sprite(sprite)).base();
}
sprite Box2DContext::remove_sprite_from_world(int index){
    auto sprite = sprites_in_the_world.at(index);
    sprites_in_the_world.erase(sprites_in_the_world.begin() + index);

    return sprite->first;
}

void Box2DContext::step(){
    this->world.Step(RESOLUTION, BOX2D_VELCOITY_ITERATIONS, BOX2D_POSITION_ITERATIONS);
    for(auto spriteBodyPair : sprites_in_the_world){
        auto sprite = spriteBodyPair->first;
        auto body = spriteBodyPair->second;
        auto bodyExtents = body->GetFixtureList()->GetAABB(0).GetExtents();

        sprite_set_position(sprite, {(body->GetPosition().x - bodyExtents.x) * options.scale_x,
                                     (body->GetPosition().y - bodyExtents.y) * options.scale_y});

        sprite_set_rotation(sprite, body->GetAngle()*(180.0f/M_PI));

    }
}
