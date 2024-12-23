/**
 * @header line_geometry
 * @author Andrew Cain
 * @attribute group  geometry
 * @attribute static geometry
 */

#ifndef line_geometry_hpp
#define line_geometry_hpp

#include "types.h"

#include <vector>
using std::vector;

namespace splashkit_lib
{
    /**
     * Create a line from one point to another.
     *
     * @param  start The start of the line
     * @param  end_pt   The end of the line
     * @return       A line from the start to the end point
     *
     * @attribute suffix  point_to_point
     */
    line line_from(const point_2d &start, const point_2d &end_pt);

    /**
     * Create a line from one point to another.
     *
     * @param  x1 The x value of the start of the line
     * @param  y1 The y value of the start of the line
     * @param  x2 The x value of the end of the line
     * @param  y2 The y value of the end of the line
     * @return       A line from the start to the end point
     */
    line line_from(double x1, double y1, double x2, double y2);

    /**
     * Creates a line that starts at a point, and follows a given vector.
     *
     * @param  start  The start of the line
     * @param  offset The offset to the end of the line
     * @return        A line from the start to end point
     *
     * @attribute suffix  start_with_offset
     */
    line line_from(const point_2d &start, const vector_2d &offset);

    /**
     * Returns the squared length of the line. You can also get the
     * `line_length`.
     *
     * @param  l The line
     * @return   The squared length of the line
     */
    float line_length_squared(const line &l);

    /**
     * Returns the length of a line.
     *
     * @param  l The line
     * @return   The length of the line
     */
    float line_length(const line &l);

    /**
     * Gets a line that goes from the origin and ends at the end of the vector.
     *
     * @param  v The offset from the origin for the end of the line
     * @return   A line from the origin to the end point
     *
     * @attribute suffix  vector
     */
    line line_from(const vector_2d &v);

    /**
     * Returns an array of lines from the details in the triangle.
     *
     * @param t The triangle
     * @return  The lines from the triangle
     *
     * @attribute suffix  triangle
     */
    vector<line> lines_from(const triangle &t);

    /**
     * Returns an array of lines from a supplied rectangle.
     *
     * @param rect  The rectangle to get the lines from
     * @return      An array containing 4 lines
     *
     * @attribute suffix  rectangle
     */
    vector<line> lines_from(const rectangle &rect);

    /**
     * Returns the point at which two lines would intersect. This point may lie
     * past the end of one or both lines.
     *
     * @param  line1 The first line
     * @param  line2 The other line
     * @param  pt    The resulting point where they intersect
     * @return       [description]
     */
    bool line_intersection_point(const line &line1, const line &line2, point_2d &pt);

    /**
     * Gets the closest point on the line to a given point.
     *
     * @param  from_pt The point to test (usually somewhere near the line)
     * @param  l       The line
     * @return         The point on the line that is closest to `from_pt`
     */
    point_2d closest_point_on_line(const point_2d from_pt, const line &l);

    /**
     * Get the point closest to `from pt` that is on one of the supplied lines.
     *
     * @param  from_pt The point to test
     * @param  lines   The lines to check
     * @param  line_idx After the call this will store the index of the line that
     *                  had the matching point.
     * @return         The point on one of the lines that is the closest point
     *                 on these lines to the `from pt`.
     */
    point_2d closest_point_on_lines(const point_2d from_pt, const vector<line> &lines, int &line_idx);

    /**
     * Returns true if the two lines intersect.
     *
     * @param  l1 The first line
     * @param  l2 The other line
     * @return    True if the two lines intersect (share a common point).
     */
    bool lines_intersect(const line &l1, const line &l2);

    /**
     * Returns true if the line intersects the circle.
     *
     * @param  l The line
     * @param  c The circle
     * @return   True if the line `l` intersects the circle `c`
     */
    bool line_intersects_circle(const line &l, const circle &c);

    /**
     * Returns true if the line intersects the rectangle.
     *
     * @param  l    The line
     * @param  rect The rectangle
     * @return      True if `l` intersects `rect`
     */
    bool line_intersects_rect(const line &l, const rectangle &rect);

    /**
     * Returns the center point of the line.
     *
     * @param  l The line
     * @return   The point that is at the center of the line
     */
    point_2d line_mid_point(const line &l);

    /**
     * The line normal (a perpendicular vector).
     *
     * @param  l The line
     * @return   The line's normal vector
     */
    vector_2d line_normal(const line &l);

    /**
     * Returns a text description of the line.
     *
     * @param  ln The line
     * @return    A text description of the line
     */
    string line_to_string(const line &ln);

    /**
     * Returns true if the line intersects any of the lines.
     *
     * @param  l     The line to check
     * @param  lines The lines to check against
     * @return       True if `line` intersects any of the lines in `lines`
     */
    bool line_intersects_lines(const line &l, const vector<line> &lines);


}
#endif /* line_geometry_hpp */
