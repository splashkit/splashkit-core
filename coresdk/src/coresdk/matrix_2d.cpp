//
//  matrix_2d.cpp
//  splashkit
//
//  Created by Clancy Light Townsend on 18/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "matrix_2d.h"

#include "point_geometry.h"
#include "utility_functions.h"

#include <cmath>
#include <iomanip>
#include <sstream>

using std::stringstream;
using std::endl;

namespace splashkit_lib
{
    matrix_2d identity_matrix()
    {
        matrix_2d result;

        result.elements[0][0] = 1;
        result.elements[0][1] = 0;
        result.elements[0][2] = 0;

        result.elements[1][0] = 0;
        result.elements[1][1] = 1;
        result.elements[1][2] = 0;

        result.elements[2][0] = 0;
        result.elements[2][1] = 0;
        result.elements[2][2] = 1;

        return result;
    }

    matrix_2d translation_matrix(double dx, double dy)
    {
        matrix_2d result = identity_matrix();

        result.elements[0][2] = dx;
        result.elements[1][2] = dy;

        return result;
    }

    matrix_2d translation_matrix(const vector_2d &pt)
    {
        return translation_matrix(pt.x, pt.y);
    }

    matrix_2d translation_matrix(const point_2d &pt)
    {
        return translation_matrix(pt.x, pt.y);
    }

    matrix_2d scale_matrix(double scale)
    {
        return scale_matrix(vector_to(scale, scale));
    }

    matrix_2d scale_matrix(const vector_2d &scale)
    {
        matrix_2d result;
        result.elements[0][0] = scale.x;
        result.elements[0][1] = 0;
        result.elements[0][2] = 0;

        result.elements[1][0] = 0;
        result.elements[1][1] = scale.y;
        result.elements[1][2] = 0;

        result.elements[2][0] = 0;
        result.elements[2][1] = 0;
        result.elements[2][2] = 1;

        return result;
    }

    matrix_2d scale_matrix(const point_2d &scale)
    {
        return scale_matrix(vector_to(scale));
    }

    matrix_2d rotation_matrix(double deg)
    {
        double rads = deg_to_rad(-deg);

        matrix_2d result;
        result.elements[0][0] = cos(rads);
        result.elements[0][1] = sin(rads);
        result.elements[0][2] = 0;

        result.elements[1][0] = -sin(rads);
        result.elements[1][1] = cos(rads);
        result.elements[1][2] = 0;

        result.elements[2][0] = 0;
        result.elements[2][1] = 0;
        result.elements[2][2] = 1;

        return result;
    }

    matrix_2d scale_rotate_translate_matrix(const point_2d &scale, double deg, const point_2d &translate)
    {
        double rads = deg_to_rad(-deg);

        matrix_2d result;
        result.elements[0][0] = cos(rads) * scale.x;
        result.elements[0][1] = sin(rads);
        result.elements[0][2] = translate.x;

        result.elements[1][0] = -sin(rads);
        result.elements[1][1] = cos(rads) * scale.y;
        result.elements[1][2] = translate.y;

        result.elements[2][0] = 0;
        result.elements[2][1] = 0;
        result.elements[2][2] = 1;

        return result;
    }

    matrix_2d matrix_inverse(const matrix_2d &m)
    {
        double det =  m.elements[0][0] * (m.elements[1][1] * m.elements[2][2] - m.elements[2][1] * m.elements[1][2]) -
        m.elements[0][1] * (m.elements[1][0] * m.elements[2][2] - m.elements[1][2] * m.elements[2][0]) +
        m.elements[0][2] * (m.elements[1][0] * m.elements[2][1] - m.elements[1][1] * m.elements[2][0]);

        double invdet;
        if (det == 0) //cant actually compute inverse!
        {
            invdet = 3.4E38;
            LOG(WARNING) << "Unable to compute inverse of matrix.";
        }
        else
            invdet = 1 / det;

        matrix_2d result;
        result.elements[0][0] = (m.elements[1][1] * m.elements[2][2] - m.elements[2][1] * m.elements[1][2]) * invdet;
        result.elements[0][1] = (m.elements[0][2] * m.elements[2][1] - m.elements[0][1] * m.elements[2][2]) * invdet;
        result.elements[0][2] = (m.elements[0][1] * m.elements[1][2] - m.elements[0][2] * m.elements[1][1]) * invdet;
        result.elements[1][0] = (m.elements[1][2] * m.elements[2][0] - m.elements[1][0] * m.elements[2][2]) * invdet;
        result.elements[1][1] = (m.elements[0][0] * m.elements[2][2] - m.elements[0][2] * m.elements[2][0]) * invdet;
        result.elements[1][2] = (m.elements[1][0] * m.elements[0][2] - m.elements[0][0] * m.elements[1][2]) * invdet;
        result.elements[2][0] = (m.elements[1][0] * m.elements[2][1] - m.elements[2][0] * m.elements[1][1]) * invdet;
        result.elements[2][1] = (m.elements[2][0] * m.elements[0][1] - m.elements[0][0] * m.elements[2][1]) * invdet;
        result.elements[2][2] = (m.elements[0][0] * m.elements[1][1] - m.elements[1][0] * m.elements[0][1]) * invdet;
        return result;
    }

    string matrix_to_string(const matrix_2d &matrix)
    {
        stringstream result;
        result << " ------------------------------" << endl;

        for (int i = 0; i < 3; i++)
        {
            result << '|';
            for(int j = 0; j < 3; j++)
            {
                result << ' ' << std::setw( 8 ) << std::setprecision( 3 ) << matrix.elements[i][j] << ' ';
            }
            result << '|' << endl;
        }
        result << " ------------------------------";
        return result.str();
    }

    matrix_2d matrix_multiply(const matrix_2d &m2, const matrix_2d &m1)
    {
        matrix_2d result;

        result.elements[0][0] = m1.elements[0][0] * m2.elements[0][0] +
        m1.elements[0][1] * m2.elements[1][0] +
        m1.elements[0][2] * m2.elements[2][0];
        result.elements[0][1] = m1.elements[0][0] * m2.elements[0][1] +
        m1.elements[0][1] * m2.elements[1][1] +
        m1.elements[0][2] * m2.elements[2][1];
        result.elements[0][2] = m1.elements[0][0] * m2.elements[0][2] +
        m1.elements[0][1] * m2.elements[1][2] +
        m1.elements[0][2] * m2.elements[2][2];

        result.elements[1][0] = m1.elements[1][0] * m2.elements[0][0] +
        m1.elements[1][1] * m2.elements[1][0] +
        m1.elements[1][2] * m2.elements[2][0];
        result.elements[1][1] = m1.elements[1][0] * m2.elements[0][1] +
        m1.elements[1][1] * m2.elements[1][1] +
        m1.elements[1][2] * m2.elements[2][1];
        result.elements[1][2] = m1.elements[1][0] * m2.elements[0][2] +
        m1.elements[1][1] * m2.elements[1][2] +
        m1.elements[1][2] * m2.elements[2][2];

        result.elements[2][0] = m1.elements[2][0] * m2.elements[0][0] +
        m1.elements[2][1] * m2.elements[1][0] +
        m1.elements[2][2] * m2.elements[2][0];
        result.elements[2][1] = m1.elements[2][0] * m2.elements[0][1] +
        m1.elements[2][1] * m2.elements[1][1] +
        m1.elements[2][2] * m2.elements[2][1];
        result.elements[2][2] = m1.elements[2][0] * m2.elements[0][2] +
        m1.elements[2][1] * m2.elements[1][2] +
        m1.elements[2][2] * m2.elements[2][2];
        return result;
    }

    point_2d matrix_multiply(const matrix_2d &m, const point_2d &pts)
    {
        point_2d result;

        result.x = pts.x * m.elements[0][0] + pts.y * m.elements[0][1] + m.elements[0][2];
        result.y = pts.x * m.elements[1][0] + pts.y * m.elements[1][1] + m.elements[1][2];

        return result;
    }

    vector_2d matrix_multiply(const matrix_2d &m, const vector_2d &v)
    {
        vector_2d result;

        result.x = v.x * m.elements[0][0]  +  v.y * m.elements[0][1] + m.elements[0][2];
        result.y = v.x * m.elements[1][0]  +  v.y * m.elements[1][1] + m.elements[1][2];

        return result;
    }

    void apply_matrix(const matrix_2d &m, triangle &tri)
    {
        tri.points[0] = matrix_multiply(m, tri.points[0]);
        tri.points[1] = matrix_multiply(m, tri.points[1]);
        tri.points[2] = matrix_multiply(m, tri.points[2]);
    }

    void apply_matrix(const matrix_2d &m, quad &q)
    {
        for(int i = 0; i < 4; i++)
        {
            q.points[i] = matrix_multiply(m, q.points[i]);
        }
    }
}
