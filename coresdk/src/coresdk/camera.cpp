//
//  camera.cpp
//  splashkit
//
//  Created by Andrew Cain on 24/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "camera.h"

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

void set_camera_pos(point_2d pos)
{
    _camera_x = pos.x;
    _camera_y = pos.y;
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
