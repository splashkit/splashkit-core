//
//  geometry.hpp
//  splashkit
//
//  Created by Andrew Cain on 15/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef geometry_hpp
#define geometry_hpp

/// A Point2D represents an location in Cartesian coordinates (x,y).
/// The x value represents the distance from the left edge of the window or bitmap, increasing
/// in value as you travel right. The y value represents the distance from the top
/// edge of the window or bitmap, and increases as you travel down toward the bottom.
///
/// Point2D is a great way to keep track of the location of something in a 2D space like
/// a Window or Bitmap.
///
/// @struct Point2D
/// @sameas Vector
struct point_2d
{
    float x, y;
};

/// Vectors represent a direction and distance, and can be visualised as an arrow from
/// one point to another in 2 dimensional space. Internally, the Vector is stored as its
/// x and y components (same as a `Point2D`).
///
/// Vector is a great way to represent movement or forces. You could use a vector to track
/// how much a character moves each update (as the Vector stores the direction and distance).
/// Similarly, you could use a Vector to represent gravity or other forces. You can then
/// add a number of force vectors together to get a final force to be applied to a character.
///
/// @struct Vector2D
/// @field x: Single
/// @field y: Single
/// @sameas Point2D
typedef point_2d vector_2d;

/// Rectangles are simple rectangle shapes that exist at a point and have a set width
/// and height. This means that the rectangle always has edges that follow the sides of
/// the Window or Bitmap (so they are aligned with the x and y axes). The rectangle's
/// position is its top left corner - it then extends to the right and down from
/// this position.
///
/// @struct Rectangle
struct rectangle
{
    float x, y;
    float width, height;
};




#endif /* geometry_hpp */
