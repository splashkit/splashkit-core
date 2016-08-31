//
//  camera.cpp
//  splashkit
//
//  Created by Andrew Cain on 24/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "camera.h"

#include "vector_2d.h"
#include "graphics.h"

static float _camera_x = 0;
static float _camera_y = 0;


//---------------------------------------------------------------------------
// Camera - position
//---------------------------------------------------------------------------

float camera_x()
{
    return _camera_x;
}

float camera_y()
{
    return _camera_y;
}

void set_camera_x(float x)
{
    _camera_x = x;
}

void set_camera_y(float y)
{
    _camera_y = y;
}

void set_camera_position(point_2d pos)
{
    _camera_x = pos.x;
    _camera_y = pos.y;
}

point_2d camera_position()
{
    return point_at(_camera_x, _camera_y);
}



//---------------------------------------------------------------------------
// World-To-Screen Translation
//---------------------------------------------------------------------------

float to_screen_x(float world_x)
{
    return world_x - _camera_x;
}

float to_screen_y(float world_y)
{
    return world_y - _camera_y;
}

point_2d to_screen(const point_2d &pt)
{
    return point_at(pt.x - _camera_x, pt.y - _camera_y);
}

vector_2d vector_world_to_screen()
{
    return vector_to(-_camera_x, -_camera_y);
}

rectangle to_screen(const rectangle &rect)
{
    return rectangle_offset_by(rect, vector_world_to_screen());
}

rectangle screen_rectangle()
{
    return rectangle_from(0, 0, screen_width(), screen_height());
}

//---------------------------------------------------------------------------
// Screen-To-World Translation
//---------------------------------------------------------------------------

float to_world_x(float screen_x)
{
    return screen_x + _camera_x;
}

float to_world_y(float screen_y)
{
    return screen_y + _camera_y;
}

point_2d to_world(const point_2d &pt)
{
    return point_at(pt.x + _camera_x, pt.y + _camera_y);
}
