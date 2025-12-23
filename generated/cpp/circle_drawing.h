//
// SplashKit Generated Circle Drawing C++ Code
// DO NOT MODIFY
//

#ifndef __circle_drawing_h
#define __circle_drawing_h

#include "types.h"
#include "window_manager.h"
#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
using std::string;
using std::vector;
using std::to_string;

/**
* Draw a circle on the current window. The circle is centred on its x, y
* coordinates, and has the provided radius.
* @param clr The color of the circle
* @param c The circle being drawn
*
*/;
void draw_circle(color clr, const circle &c);
/**
* Draw a circle with the provided drawing options, which may include options related to
* the drawing destination.
* @param clr The color of the circle
* @param c The circle being drawn
* @param opts Drawing options to configure the drawing operation
*
*/;
void draw_circle(color clr, const circle &c, drawing_options opts);
/**
* Draw a circle at a point, with a specified radius, onto the current window.
* @param clr The color of the circle
* @param pt The location of the center of the circle
* @param radius The radius of the circle
*
*/;
void draw_circle(color clr, const point_2d &pt, double radius);
/**
* Draw a circle at a point, with a specified radius, using the supplied drawing options. This will use `drawing_options` to determine
* the destination.
* @param clr The color of the circle
* @param pt The location of the center of the circle
* @param radius The radius of the circle
* @param opts Drawing options to configure the drawing operation
*
*/;
void draw_circle(color clr, const point_2d &pt, double radius, drawing_options opts);
/**
* Draw a circle onto the current window. The circle is centred on its x, y
* coordinates, and has the provided radius.
* @param clr The color of the circle
* @param x The x location of the circle
* @param y The y location of the circle
* @param radius The radius of the circle
*
*/;
void draw_circle(color clr, double x, double y, double radius);
/**
* Draw a circle using the supplied drawing options. The circle is centred on its x, y
* coordinates, and has the provided radius. This will use `drawing_options` to determine
* the destination.
* @param clr The color of the circle
* @param x The x location of the circle
* @param y The y location of the circle
* @param radius The radius of the circle
* @param opts Drawing options to configure the drawing operation
*
*/;
void draw_circle(color clr, double x, double y, double radius, drawing_options opts);
/**
* Draw a circle onto the destination bitmap. The circle is centred on its x, y
* coordinates, and has the provided radius.
* @param destination The destination bitmap
* @param clr The color of the circle
* @param x The x location of the circle
* @param y The y location of the circle
* @param radius The radius of the circle
*
*/;
void draw_circle_on_bitmap(bitmap destination, color clr, double x, double y, double radius);
/**
* Draw a circle to the bitmap using the supplied drawing options. The circle is centred on its x, y
* coordinates, and has the provided radius.
* @param destination The destination bitmap
* @param clr The color of the circle
* @param x The x location of the circle
* @param y The y location of the circle
* @param radius The radius of the circle
* @param opts Drawing options to configure the drawing operation
*
*/;
void draw_circle_on_bitmap(bitmap destination, color clr, double x, double y, double radius, drawing_options opts);
/**
* Draw a circle onto the destination window. The circle is centred on its x, y
* coordinates, and has the provided radius.
* @param destination The destination window
* @param clr The color of the circle
* @param x The x location of the circle
* @param y The y location of the circle
* @param radius The radius of the circle
*
*/;
void draw_circle_on_window(window destination, color clr, double x, double y, double radius);
/**
* Draw a circle to the window using the supplied drawing options. The circle is centred on its x, y
* coordinates, and has the provided radius.
* @param destination The destination window
* @param clr The color of the circle
* @param x The x location of the circle
* @param y The y location of the circle
* @param radius The radius of the circle
* @param opts Drawing options to configure the drawing operation
*
*/;
void draw_circle_on_window(window destination, color clr, double x, double y, double radius, drawing_options opts);
/**
* Draw a circle on the current window. The circle is centred on its x, y
* coordinates, and has the provided radius.
* @param clr The color of the circle
* @param c The circle being drawn
*
*/;
void fill_circle(color clr, const circle &c);
/**
* Fill a circle with the provided drawing options, which may include options related to
* the drawing destination.
* @param clr The color of the circle
* @param c The circle being drawn
* @param opts Drawing options to configure the drawing operation
*
*/;
void fill_circle(color clr, const circle &c, drawing_options opts);
/**
* Fill a circle at a point, with a specified radius, onto the current window.
* @param clr The color of the circle
* @param pt The location of the center of the circle
* @param radius The radius of the circle
*
*/;
void fill_circle(color clr, const point_2d &pt, double radius);
/**
* Fill a circle at a point, with a specified radius, using the supplied drawing options. This will use `drawing_options` to determine
* the destination.
* @param clr The color of the circle
* @param pt The location of the center of the circle
* @param radius The radius of the circle
* @param opts Drawing options to configure the drawing operation
*
*/;
void fill_circle(color clr, const point_2d &pt, double radius, drawing_options opts);
/**
* Fill a circle onto the current window. The circle is centred on its x, y
* coordinates, and has the provided radius.
* @param clr The color of the circle
* @param x The x location of the circle
* @param y The y location of the circle
* @param radius The radius of the circle
*
*/;
void fill_circle(color clr, double x, double y, double radius);
/**
* Fill a circle using the supplied drawing options. The circle is centred on its x, y
* coordinates, and has the provided radius. This will use `drawing_options` to determine
* the destination.
* @param clr The color of the circle
* @param x The x location of the circle
* @param y The y location of the circle
* @param radius The radius of the circle
* @param opts Drawing options to configure the drawing operation
*
*/;
void fill_circle(color clr, double x, double y, double radius, drawing_options opts);
/**
* Fill a circle onto the destination bitmap. The circle is centred on its x, y
* coordinates, and has the provided radius.
* @param destination The destination bitmap
* @param clr The color of the circle
* @param x The x location of the circle
* @param y The y location of the circle
* @param radius The radius of the circle
*
*/;
void fill_circle_on_bitmap(bitmap destination, color clr, double x, double y, double radius);
/**
* Fill a circle to the bitmap using the supplied drawing options. The circle is centred on its x, y
* coordinates, and has the provided radius.
* @param destination The destination bitmap
* @param clr The color of the circle
* @param x The x location of the circle
* @param y The y location of the circle
* @param radius The radius of the circle
* @param opts Drawing options to configure the drawing operation
*
*/;
void fill_circle_on_bitmap(bitmap destination, color clr, double x, double y, double radius, drawing_options opts);
/**
* Fill a circle onto the destination window. The circle is centred on its x, y
* coordinates, and has the provided radius.
* @param destination The destination window
* @param clr The color of the circle
* @param x The x location of the circle
* @param y The y location of the circle
* @param radius The radius of the circle
*
*/;
void fill_circle_on_window(window destination, color clr, double x, double y, double radius);
/**
* Fill a circle to the window using the supplied drawing options. The circle is centred on its x, y
* coordinates, and has the provided radius.
* @param destination The destination window
* @param clr The color of the circle
* @param x The x location of the circle
* @param y The y location of the circle
* @param radius The radius of the circle
* @param opts Drawing options to configure the drawing operation
*
*/;
void fill_circle_on_window(window destination, color clr, double x, double y, double radius, drawing_options opts);

#endif /* __circle_drawing_h */
