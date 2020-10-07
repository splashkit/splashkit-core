/**
 * @header  physics
 * @author  Andrew Cain
 * @attribute group  physics
 */

#ifndef physics_hpp
#define physics_hpp

#include "matrix_2d.h"
#include "vector_2d.h"
#include "collisions.h"

#include "drawing_options.h"
#include "sprites.h"
#include <vector>
#include <utility>


#include "box2d/box2d.h"


namespace splashkit_lib
{
    // Constant for gravity for box2d. It is positive because
    // the vertical axis increases towards the bottom of the screen.
    constexpr float GRAVITY = 9.82f;
    constexpr float RESOLUTION = 1.0/60.0;
    constexpr int BOX2D_VELCOITY_ITERATIONS = 6;
    constexpr int BOX2D_POSITION_ITERATIONS = 2;
    constexpr float SCALE_X = 100.0f;
    constexpr float SCALE_Y = 100.0f;

    /**
     * Holds the context for interacting with the box2d library.
     * You are expected to allocate and hold a reference to this.
     * This will create a box2d world and keep it alive until this is
     * destroyed
     * 
     * Allocating bodies into this world with sprites will cause the sprite's
     * position and angle to be updated by this world.
     **/
    class Box2DContext
    {
    public:
        Box2DContext();
        /**
         * This creates and allocates a box2d body and fixture to act in the world
         * and keeps a reference to the sprite to be updated.
         **/
        std::pair<sprite, b2Body*>* add_sprite_to_world(sprite, const b2BodyDef&);
        std::pair<sprite, b2Body*>* add_sprite_to_world(sprite s){
            return add_sprite_to_world(s, default_body_definition);
        }
        void step();
        /**
         * Find a sprite and remove it from the world.
         * This will also remove the box2d body.
         */
        sprite remove_sprite_from_world(sprite);
        sprite remove_sprite_from_world(int);

        /**
         * Locate the sprite in the world and return the sprite, box2d body pair.
         */
        const std::pair<sprite, b2Body *>* find(sprite sprite);
        auto find_sprite(sprite);
        b2BodyDef get_default_body_definition(){
            return default_body_definition;
        }

    private:
        b2BodyDef default_body_definition;
        b2World world{{0.0f, GRAVITY}};
        drawing_options options;
        std::vector<std::pair<sprite, b2Body*>*> sprites_in_the_world;
    };
} // namespace splaskit_lib
#endif /* physics_hpp */
