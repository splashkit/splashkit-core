//
//  vector_2d.cpp
//  splashkit
//
//  Created by Andrew Cain on 19/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "vector_2d.h"

#include "point_geometry.h"
#include "line_geometry.h"
#include "circle_geometry.h"
#include "utility_functions.h"

#include <cmath>

using std::to_string;

namespace splashkit_lib
{
    string vector_to_string(const vector_2d &v)
    {
        return "Vec -> " + to_string(v.x) + ":" + to_string(v.y);
    }

    vector_2d vector_to(double x, double y)
    {
        return { x, y };
    }

    vector_2d vector_to(const point_2d &p1)
    {
        vector_2d result;
        result.x = p1.x;
        result.y = p1.y;
        return result;
    }

    vector_2d vector_point_to_point(const point_2d &start, const point_2d &end_pt)
    {
        vector_2d result;
        result.x = end_pt.x - start.x;
        result.y = end_pt.y - start.y;
        return result;
    }

    vector_2d vector_invert(const vector_2d &v)
    {
        return { -v.x, -v.y };
    }

    vector_2d vector_from_angle(double angle, double magnitude)
    {
        return vector_to(magnitude * cosine(angle), magnitude * sine(angle));
    }

    vector_2d vector_from_line(const line &l)
    {
        return vector_point_to_point(l.start_point, l.end_point);
    }

    vector_2d vector_add(const vector_2d &v1, const vector_2d &v2)
    {
        return { v1.x +  v2.x, v1.y + v2.y };
    }

    vector_2d vector_subtract(const vector_2d &v1, const vector_2d &v2)
    {
        return { v1.x - v2.x, v1.y - v2.y };
    }

    vector_2d vector_multiply(const vector_2d &v1, double s)
    {
        return { v1.x * s, v1.y * s };
    }

    bool vectors_equal(const vector_2d &v1, const vector_2d v2)
    {
        return abs(v1.x - v2.x) < EPSEPS and abs(v1.y - v2.y) < EPSEPS;
    }

    bool vectors_not_equal(const vector_2d &v1, const vector_2d v2)
    {
        return not vectors_equal(v1, v2);
    }

    double dot_product(const vector_2d &v1, const vector_2d &v2)
    {
        return (v1.x * v2.x) + (v1.y * v2.y);
    }

    double vector_angle(const vector_2d v)
    {
        if (v.x == 0)
        {
            if (v.y < 0) return -90;
            else return 90; //Default to down screen if x and y are both 0
        }
        else if (v.y == 0)
        {
            if (v.x < 0) return 180;
            else return 0;
        }
        else
        {
            double result = rad_to_deg(atan(v.y / v.x));

            if (v.x < 0)
            {
                if (v.y < 0) result -= 180;
                else result += 180;
            }
            return result;
        }
    }

    double angle_between(const vector_2d &v1, const vector_2d &v2)
    {
        return vector_angle( vector_subtract(v2, v1) );
    }

    vector_2d vector_normal(const vector_2d &v)
    {
        double magnitude = vector_magnitude(v);

        if (magnitude == 0)
        {
            LOG(WARNING) << "Attempting to get normal of null/zero vector";
            return { 0,0 };
        }

        return { -v.y / magnitude, v.x / magnitude };
    }

    double vector_magnitude_sqared(const vector_2d &v)
    {
        return (v.x * v.x) + (v.y * v.y);
    }

    double vector_magnitude(const vector_2d &v)
    {
        return sqrt(vector_magnitude_sqared(v));
    }

    vector_2d vector_limit(const vector_2d &v, double limit)
    {
        if ( abs(vector_magnitude(v)) > abs(limit) )
        {
            return vector_multiply(unit_vector(v), limit);
        }
        return v;
    }

    vector_2d unit_vector(const vector_2d &v)
    {
        double tmp;
        double mag = vector_magnitude(v);

        if ( mag == 0 )
            tmp = 0;
        else
            tmp = 1 / mag;

        return { tmp * v.x, tmp * v.y };
    }

    bool is_zero_vector(const vector_2d &v)
    {
        return (v.x == 0) && (v.y == 0);
    }

    bool ray_intersection_point(const point_2d &from_pt, const vector_2d &heading, const line &l, point_2d &pt)
    {
        line ray_line;
        double comb_mag;

        ray_line = line_from(from_pt, heading);

        // Get where the line intersect
        if (not line_intersection_point(ray_line, l, pt)) return false;
        //DrawLine(ColorWhite, fromPt, pt);

        comb_mag = vector_magnitude(vector_add(unit_vector(vector_point_to_point(from_pt, pt)), unit_vector(heading)));
        // WriteLn(combMag:4:2);
        // Test that pt is forward of fromPt (given heading)
        if ( comb_mag < 1 ) return false; //behind point

        return true;
    }

    vector_2d vector_out_of_rect_from_point(const point_2d &pt, const rectangle &rect, const vector_2d &velocity)
    {
        point_2d pt_on_line;
        vector_2d ray, v_out;
        int i;
        double dist, max_dist;

        // Cast ray searching back from pts... looking for the impact point
        ray = vector_invert(velocity);  // the ray
        v_out = vector_to(0,0);          // the vector out (from the point to over the line, i.e. moving the point along this vector moves it back over the line)

        line lines[4] = {
            { {rect.x, rect.y}, {rect.x + rect.width, rect.y} },
            { {rect.x, rect.y}, {rect.x, rect.y + rect.height} },
            { {rect.x + rect.width, rect.y}, {rect.x + rect.width, rect.y + rect.height} },
            { {rect.x, rect.y + rect.height}, {rect.x + rect.width, rect.y + rect.height} }
        };

        // Indicate no find so far....
        int max_idx = -1;
        max_dist = -1;

        //Search all lines for hit points
        for (i = 0; i < 4; i++)
        {
            //DrawCircle(ColorWhite, pts[j], 2);

            // Cast a ray back from this point to find line pts... out on ptOnLine
            // ptOnLine is then the point that the ray intersects with the line
            if ( ray_intersection_point(pt, ray, lines[i], pt_on_line) )
            {
                //DrawCircle(ColorRed, ptOnLine, 1);
                //DrawLine(ColorRed, pts[j], ptOnLine);

                if (not point_on_line(pt_on_line, lines[i])) continue; //this points ray misses the line

                // Calculate the distance from the point on the line to the point being tested
                dist = point_point_distance(pt_on_line, pt);

                // Check if the distance is the new max distance
                if ((dist > max_dist) or (max_idx == -1))
                {
                    max_dist = dist;
                    max_idx = i;
                    v_out = vector_point_to_point(pt, pt_on_line);
                    v_out = vector_multiply(unit_vector(v_out), vector_magnitude(v_out) + 1.4);
                }
            }
        }

        return v_out;
    }

    struct double_pt
    {
        point_2d pt_on_circle, pt_on_line;
    };

    //
    // This internal function is used to calculate the vector and determine if a hit has occurred...
    //
    vector_2d vector_over_lines_from_circle(const circle &c, const vector<line> lines, const vector_2d &velocity, int &max_idx)
    {
        point_2d pt_on_line, pt_on_circle;
        point_2d tmp[4], edge;
        double_pt chk_pts[4];
        vector_2d line_vec, normal_mvmt, normal_line, to_edge, ray, v_out;

        int i, j, hits;
        double dot_prod, dist, max_dist;

        // If there is no velocity then we cannot determine
        // the hit location etc. Return a 0,0 vector.
        if ( vector_magnitude(velocity) == 0 )
        {
            LOG(WARNING) << "Attempting to determine collision with a zero/null vector.";
            // velocity has no magnitude, so it can be returned
            return velocity;
        }

        // Cast ray searching for points back from shape
        ray = vector_invert(velocity);
        normal_mvmt = vector_normal(velocity);
        v_out = vector_to(0,0);
        pt_on_circle = point_at(0,0);

        max_idx = -1;
        max_dist = -1;

        // fix for tmp initialized warning
        for (i = 0; i < 4; i++) tmp[i] = point_at(0,0);

        //Search all lines for hit points
        for (i = 0; i < lines.size(); i++)
        {
            line_vec = vector_from_line(lines[i]);
            //Get the normal of the line we hit
            normal_line = vector_normal(line_vec);
            hits = 0;

            //tmp 0 and tmp 1 are the widest points to detect collision with line
            widest_points(c, normal_mvmt, tmp[0], tmp[1]);
            //tmp 2 and tmp 3 are the closest and furthest points from the line
            widest_points(c, normal_line, tmp[2], tmp[3]);

            // for both points...
            for (j = 0; j < 4; j++)
            {
                //DrawCircle(ColorWhite, tmp[j], 2);

                // Cast a ray back from the test points to find line pts... out on pt_on_line
                if ( ray_intersection_point(tmp[j], ray, lines[i], pt_on_line) )
                {
                    //DrawCircle(ColorRed, pt_on_line, 1);
                    //DrawLine(ColorRed, tmp[j], pt_on_line);

                    chk_pts[hits].pt_on_line = pt_on_line;
                    chk_pts[hits].pt_on_circle = tmp[j];
                    hits = hits + 1;
                }
            }

            // for each of the hits on this line...
            // search for the longest hit.
            for (j = 0; j < hits; j++)
            {
                //if not maxLine then DrawCircle(ColorWhite, chk_pts[j].pt_on_circle, 1);
                to_edge = vector_point_to_point(c.center, chk_pts[j].pt_on_circle);
                //if not maxLine then DrawLine(ColorRed, c.center, chk_pts[j].pt_on_circle);
                dot_prod = dot_product(to_edge, normal_line);

                // 2d: Most distant edge pt is on a line this distance (dot_prod) from the center
                edge = point_offset_by(c.center, vector_multiply(normal_line, dot_prod));
                //DrawPixel(ColorWhite, edge); // Draws pt on line to distant pt

                //  Find the point we hit on the line... pt_on_line receives intersection point...
                if (not line_intersection_point(line_from(edge, velocity), lines[i], pt_on_line)) continue;
                // Move back onto line segment... linePt -> closest point on line to intersect point
                //if not maxLine then DrawCircle(ColorRed, pt_on_line, 1); // point on line, but not necessarily the line segment
                //if not maxLine then DrawLine(ColorWhite, edge, pt_on_line);

                pt_on_line = closest_point_on_line(pt_on_line, lines[i]);
                //if not maxLine then FillCircle(ColorBlue, pt_on_line, 1); // point on segment

                // Find the most distant point on the circle, given the velocity vector
                if (not distant_point_on_circle_heading(pt_on_line, c, velocity, pt_on_circle)) continue;
                // if not maxLine then FillCircle(ColorBlue, pt_on_circle, 2); // point on segment
                // if not maxLine then DrawLine(ColorBlue, pt_on_line, pt_on_circle);

                dist = point_point_distance(pt_on_line, pt_on_circle);

                if ((dist > max_dist) or (max_idx == -1))
                {
                    max_dist = dist;
                    max_idx = i;
                    v_out = vector_point_to_point(pt_on_circle, pt_on_line);
                    v_out = vector_multiply(unit_vector(v_out), vector_magnitude(v_out) + 1.42);
                }
            }
        }

        return v_out; //vector_to(ceil(v_out.x), ceil(v_out.y));
    }

    vector<point_2d> points_from(const rectangle &rect)
    {
        vector<point_2d> result;
        result.push_back(point_at(rect.x, rect.y));
        result.push_back(point_at(rect.x + rect.width, rect.y));
        result.push_back(point_at(rect.x, rect.y + rect.height));
        result.push_back(point_at(rect.x + rect.width, rect.y + rect.height));
        return result;
    }

    vector<point_2d> points_from(const line &l)
    {
        vector<point_2d> result;
        result.push_back(l.start_point);
        result.push_back(l.end_point);
        return result;
    }

    vector_2d vector_over_lines_from_lines(const vector<line> &src_lines, const vector<line> &bound_lines, const vector_2d &velocity, int &max_idx)
    {
        vector_2d ray, v_out;
        int i, j, k;
        double max_dist;
        vector<point_2d> ln_points, bound_ln_points;
        bool both_did_hit;

        // Search from the start_pt for the ray
        auto ray_from_pt_hit_line = [&] (point_2d start_pt, const line &to_line, vector_2d my_ray)
        {
            point_2d pt_on_line;
            double dist;

            //DrawCircle(ColorWhite, pts[j], 2);

            // Cast my_ray back from start_pt to find line pts... out on pt_on_line
            // pt_on_line is then the point that the ray intersects with the line
            if ( ray_intersection_point(start_pt, my_ray, to_line, pt_on_line) )
            {
                if (not point_on_line(pt_on_line, to_line))
                    return false; //this points ray misses the line

                // FillCircle(ColorRed, start_pt, 2);
                // DrawCircle(ColorRed, pt_on_line, 2);
                // DrawLine(ColorRed, start_pt, pt_on_line);

                // Calculate the distance from the point on the line to the point being tested
                dist = point_point_distance(pt_on_line, start_pt);

                // Check if the distance is the new max distance
                if ((dist > max_dist) or (max_idx == -1))
                {
                    max_dist = dist;
                    max_idx = i;  //  We hit with the current line
                    if (vectors_equal(my_ray, ray)) // if we are searching back...
                        v_out = vector_point_to_point(start_pt, pt_on_line);
                    else // if we are searching forward (using velocity)
                        v_out = vector_point_to_point(pt_on_line, start_pt);
                    v_out = vector_multiply(unit_vector(v_out), vector_magnitude(v_out) + 1); //TODO: check this further
                }
                return true;
            }
            return false;
        };

        // Cast ray searching back from pts... looking for the impact point
        ray = vector_invert(velocity);  // the ray
        v_out = vector_to(0,0);          // the vector out (from the point to over the line, i.e. moving the point along this vector moves it back over the line)

        // Indicate no find so far....
        max_idx = -1;
        max_dist = -1;

        //
        //  Search all lines for hit points - cast ray back from line ends and find where these intersect with the bound lines
        //
        for (i = 0; i < bound_lines.size(); i++)
        {
            //WriteLn('Testing bound line: ', LineToString(bound_lines[i]));
            bound_ln_points = points_from(bound_lines[i]);

            // for all source lines...
            for (j = 0; j < src_lines.size(); j++)
            {
                //WriteLn('Testing src line: ', LineToString(src_lines[j]));

                // Get the points from the srcLine
                ln_points = points_from(src_lines[j]);
                both_did_hit = true;

                for (k = 0; k < ln_points.size(); k++)
                {
                    //WriteLn('Point ', k, ' in line is at ', PointToString(ln_points[k]));
                    both_did_hit = ray_from_pt_hit_line(ln_points[k], bound_lines[i], ray) and both_did_hit;
                }

                if (both_did_hit) continue;

                // Search from the bound line to the source

                for (k = 0; k < bound_ln_points.size(); k++)
                {
                    ray_from_pt_hit_line(bound_ln_points[k], src_lines[j], velocity);
                }
            }
        }

        return v_out;
    }

    vector_2d vector_out_of_rect_from_rect(const rectangle &src, const rectangle &bounds, const vector_2d &velocity)
    {
        int max_idx = 0;
        return vector_over_lines_from_lines(lines_from(src), lines_from(bounds), velocity, max_idx);
    }
    
    vector_2d vector_out_of_circle_from_point(const point_2d &pt, const circle &c, const vector_2d &velocity)
    {
        double dx, dy, cx, cy;
        double a, b, c1, det, t, mv_out;
        point_2d ipt2;
        
        // If the point is not in the radius of the circle, return a zero vector
        if (point_point_distance(pt, center_point(c)) > c.radius)
        {
            return vector_to(0, 0);
        }
        
        // Calculate the determinant (and components) from the center circle and
        // the point+velocity details
        cx = c.center.x;
        cy = c.center.y;
        dx = velocity.x;
        dy = velocity.y;
        
        a = dx * dx + dy * dy;
        b = 2 * (dx * (pt.x - cx) + dy * (pt.y - cy));
        c1 = (pt.x - cx) * (pt.x - cx) + (pt.y - cy) * (pt.y - cy) - c.radius * c.radius;
        
        det = b * b - 4 * a * c1;
        
        // If the determinate is very small, return a zero vector
        if ((det <= 0) or (a == 0))
            return vector_to(0, 0);
        else
        {
            // Calculate the vector required to "push" the vector out of the circle
            t = (-b - sqrt(det)) / (2 * a);
            ipt2.x = pt.x + t * dx;
            ipt2.y = pt.y + t * dy;
            
            mv_out = point_point_distance(pt, ipt2) + 1.42; // sqrt 2
            return vector_multiply(unit_vector(vector_invert(velocity)), mv_out);
        }
    }
    
    vector_2d vector_out_of_circle_from_circle(const circle &src, const circle &bounds, const vector_2d &velocity)
    {
        circle c = circle_at(center_point(bounds), bounds.radius + src.radius);
        return vector_out_of_circle_from_point(center_point(src), c, velocity);
    }
    
    vector_2d vector_out_of_rect_from_circle(const circle &c, const rectangle &rect, const vector_2d &velocity)
    {
        int max_idx;
        return vector_over_lines_from_circle(c, lines_from(rect), velocity, max_idx);
    }

    vector_2d vector_from_point_to_rect(const point_2d &pt, const rectangle &rect)
    {
        double px, py;

        if (pt.x < rect.x) px = rect.x;
        else if (pt.x > (rect.x + rect.width)) px = rect.x + rect.width;
        else px = pt.x;

        if (pt.y < rect.y) py = rect.y;
        else if (pt.y > (rect.y + rect.height)) py = rect.y + rect.height;
        else py = pt.y;
        
        return vector_to(px - pt.x, py - pt.y);
    }

    bool vector_in_rect(const vector_2d &v, const rectangle &rect)
    {
        if (v.x < rect.x) return false;
        else if (v.x >= rect.x + rect.width) return false;
        else if (v.y < rect.y)  return false;
        else if (v.y >= rect.y + rect.height) return false;
        else return true;
    }
}
