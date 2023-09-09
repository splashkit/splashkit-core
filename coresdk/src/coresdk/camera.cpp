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
namespace splashkit_lib
{
    static double _camera_x = 0;
    static double _camera_y = 0;


    //---------------------------------------------------------------------------
    // Camera - position
    //---------------------------------------------------------------------------

    double camera_x()
    {
        return _camera_x;
    }

    double camera_y()
    {
        return _camera_y;
    }

    void set_camera_x(double x)
    {
        _camera_x = x;
    }

    void set_camera_y(double y)
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

    point_2d screen_center()
    {
        return point_at(_camera_x + screen_width() / 2.0f, _camera_y + screen_height() / 2.0f);
    }



    //---------------------------------------------------------------------------
    // World-To-Screen Translation
    //---------------------------------------------------------------------------

    double to_screen_x(double world_x)
    {
        return world_x - _camera_x;
    }

    double to_screen_y(double world_y)
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

    rectangle window_area(window wind)
    {
        return rectangle_from(0, 0, window_width(wind), window_height(wind));
    }

    //---------------------------------------------------------------------------
    // Screen-To-World Translation
    //---------------------------------------------------------------------------

    double to_world_x(double screen_x)
    {
        return screen_x + _camera_x;
    }

    double to_world_y(double screen_y)
    {
        return screen_y + _camera_y;
    }

    point_2d to_world(const point_2d &pt)
    {
        return point_at(pt.x + _camera_x, pt.y + _camera_y);
    }


    //---------------------------------------------------------------------------
    // Screen tests
    //---------------------------------------------------------------------------

    bool rect_on_screen(const rectangle &rect)
    {
        return rectangles_intersect(to_screen(rect), screen_rectangle());
    }

    bool point_on_screen(const point_2d &pt)
    {
        return point_in_rectangle(pt, screen_rectangle());
    }

    bool rect_in_window(window wind, const rectangle &rect)
    {
        return rectangles_intersect(to_screen(rect), window_area(wind));
    }

    bool point_in_window(window wind, const point_2d &pt)
    {
        return point_in_rectangle(pt, window_area(wind));
    }


    //---------------------------------------------------------------------------
    // Camera movement
    //---------------------------------------------------------------------------

    void move_camera_to(double x, double y)
    {
        _camera_x = x;
        _camera_y = y;
    }

    void move_camera_to(const point_2d &pt)
    {
        move_camera_to(pt.x, pt.y);
    }

    void move_camera_by(double dx, double dy)
    {
        _camera_x += dx;
        _camera_y += dy;
    }

    void move_camera_by(const vector_2d &offset)
    {
        move_camera_by(offset.x, offset.y);
    }

    void center_camera_on(vector<sprite> s, double offset_x, double offset_y) {
		
        double sc_x{0};
        double sc_y{0};
		
        for (const sprite& ele : s) {
            sc_x += (sprite_position(ele).x /s.size());
            sc_y += (sprite_position(ele).y /s.size());
        }
		
        sc_x = sc_x + offset_x - (screen_width() / 2);
        sc_y = sc_y + offset_y - (screen_height() / 2);
        move_camera_to(sc_x, sc_y);
    }
    
    void center_camera_on(sprite s[],int size, double offset_x, double offset_y) {
        double sc_x{0};
        double sc_y{0};
        
        for (int i = 0; i < size; ++i) {
            sc_x += (sprite_position(s[i]).x /size);
            sc_y += (sprite_position(s[i]).y /size);
        }
		
        sc_x = sc_x + offset_x - (screen_width() / 2);
        sc_y = sc_y + offset_y - (screen_height() / 2);
        move_camera_to(sc_x, sc_y);
    }

    void center_camera_on(sprite s, double offset_x, double offset_y) {

        point_2d center = sprite_position(s);
        double sc_x = sprite_position(s).x + offset_x - (screen_width() / 2);
        double sc_y = sprite_position(s).y + offset_y - (screen_height() / 2);

        move_camera_to(sc_x, sc_y);
    }

    void center_camera_on(sprite s, const vector_2d &offset)
    {
        center_camera_on(s, offset.x, offset.y);
    }
	
	void center_camera_on(sprite s[],int size , const vector_2d &offset)
    {
        center_camera_on(s,size, offset.x, offset.y);
    }
	
	void center_camera_on(vector<sprite> s, const vector_2d &offset)
    {
        center_camera_on(s, offset.x, offset.y);
    }
}
