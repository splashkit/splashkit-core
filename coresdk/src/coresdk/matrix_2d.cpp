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

using std::endl;
using std::stringstream;

namespace splashkit_lib
{
    /* #region matrix_2d */
    matrix_2d::matrix_2d(int x, int y)
    {
        elements = new double *[x];
        for (size_t i = 0; i < x; i++)
            elements[i] = new double[y];
        this->x = x;
        this->y = y;
    }

    matrix_2d::matrix_2d(const matrix_2d &other)
    {
        elements = new double *[other.x];
        for (size_t i = 0; i < other.x; i++)
            elements[i] = new double[other.y];
        this->x = other.x;
        this->y = other.y;

        for (size_t i = 0; i < x; i++)
            for (size_t j = 0; j < y; j++)
                elements[i][j] = other.elements[i][j];
    }

    matrix_2d::~matrix_2d()
    {
        for (size_t i = 0; i < x; i++)
            delete[] elements[i]; // delete each row
        delete[] elements;        // delete pointers to each row
    }

    matrix_2d &matrix_2d::operator=(const matrix_2d &other)
    {
        if (this != &other)
        {
            if (x != other.x || y != other.y)
            {
                for (size_t i = 0; i < x; i++)
                    delete[] elements[i];
                delete[] elements;
                elements = new double *[other.x];
                for (size_t i = 0; i < other.x; i++)
                    elements[i] = new double[other.y];
                x = other.x;
                y = other.y;
            }

            for (size_t i = 0; i < x; i++)
                for (size_t j = 0; j < y; j++)
                    elements[i][j] = other.elements[i][j];
        }
        return *this;
    }

    matrix_2d matrix_2d::operator==(const matrix_2d &other) const
    {
        if (x != other.x || y != other.y)
            return matrix_2d(0, 0);

        matrix_2d result(x, y);
        for (size_t i = 0; i < x; i++)
            for (size_t j = 0; j < y; j++)
                result.elements[i][j] = (elements[i][j] == other.elements[i][j]);

        return result;
    }

    matrix_2d matrix_2d::operator!=(const matrix_2d &other) const
    {
        if (x != other.x || y != other.y)
        {
            static matrix_2d result(1, 1);
            result.elements[0][0] = 1.0; // true
            return result;
        }

        matrix_2d result(x, y);
        for (size_t i = 0; i < x; i++)
            for (size_t j = 0; j < y; j++)
                result.elements[i][j] = (elements[i][j] != other.elements[i][j]);

        return result;
    }

    matrix_2d matrix_2d::operator[](const matrix_2d &other) const
    {
        matrix_2d result(x, y);
        for (size_t i = 0; i < x; i++)
            for (size_t j = 0; j < y; j++)
                result.elements[i][j] = other.elements[i][j] ? elements[i][j] : 0;
        return result;
    }

    bool matrix_2d::all()
    {
        if (x <= 0 || y <= 0)
            return false;
        for (size_t i = 0; i < x; i++)
            for (size_t j = 0; j < y; j++)
                if (!elements[i][j])
                    return false;
        return true;
    }

    bool matrix_2d::any()
    {
        if (x <= 0 || y <= 0)
            return false;
        for (size_t i = 0; i < x; i++)
            for (size_t j = 0; j < y; j++)
                if (elements[i][j])
                    return true;
        return false;
    }

    matrix_2d::iterator::iterator(matrix_2d *ptr, size_t x = 0)
    {
        this->ptr = ptr;
        this->x = x;
    }

    double &matrix_2d::iterator::operator*() { return ptr->elements[x][y]; }

    void matrix_2d::iterator::operator++()
    {
        if (y >= ptr->y - 1)
        {
            y = 0;
            x++;
        }
        else
        {
            y++;
        }
    }

    bool matrix_2d::iterator::operator!=(const iterator &other) { return x != other.x || y != other.y; }
    /* #endregion */

    matrix_2d fill_matrix(int x, int y, double fill)
    {
        matrix_2d result(x, y);

        for (size_t i = 0; i < x; i++)
            for (size_t j = 0; j < y; j++)
                result.elements[i][j] = fill;

        return result;
    }

    matrix_2d identity_matrix(int n)
    {
        matrix_2d result = fill_matrix(n, n, 0);
        for (int i = 0; i < n; i++)
            result.elements[i][i] = 1;
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
        double det = m.elements[0][0] * (m.elements[1][1] * m.elements[2][2] - m.elements[2][1] * m.elements[1][2]) -
                     m.elements[0][1] * (m.elements[1][0] * m.elements[2][2] - m.elements[1][2] * m.elements[2][0]) +
                     m.elements[0][2] * (m.elements[1][0] * m.elements[2][1] - m.elements[1][1] * m.elements[2][0]);

        double invdet;
        if (det == 0) // cant actually compute inverse!
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
        result << " " << string(10 * matrix.y, '-') << endl;

        for (size_t i = 0; i < matrix.x; i++)
        {
            result << '|';
            for (size_t j = 0; j < matrix.y; j++)
            {
                result << ' ' << std::setw(8) << std::setprecision(3) << matrix.elements[i][j] << ' ';
            }
            result << '|' << endl;
        }
        result << " " << string(10 * matrix.y, '-');
        return result.str();
    }

    matrix_2d matrix_multiply(const matrix_2d &m1, const matrix_2d &m2)
    {
        if (m1.y != m2.x)
            LOG(WARNING) << __FUNCTION__ << ": Matrix dimensions do not match.";

        matrix_2d result = matrix_2d(m1.x, m2.y);
        for (size_t x = 0; x < m1.x; x++)
        {
            for (size_t y = 0; y < m2.y; y++)
            {
                result.elements[x][y] = 0;
                for (size_t inner = 0; inner < m1.y; inner++)
                {
                    result.elements[x][y] += m1.elements[x][inner] * m2.elements[inner][y];
                }
            }
        }
        return result;
    }

    matrix_2d matrix_multiply(const matrix_2d &m, double scalar)
    {
        matrix_2d result = matrix_2d(m);
        for (size_t x = 0; x < m.x; x++)
        {
            for (size_t y = 0; y < m.y; y++)
            {
                result.elements[x][y] *= scalar;
            }
        }
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

        result.x = v.x * m.elements[0][0] + v.y * m.elements[0][1] + m.elements[0][2];
        result.y = v.x * m.elements[1][0] + v.y * m.elements[1][1] + m.elements[1][2];

        return result;
    }

    matrix_2d matrix_multiply_components(const matrix_2d &m1, const matrix_2d &m2)
    {
        if (m1.x != m2.x || m1.y != m2.y)
            LOG(WARNING) << __FUNCTION__ << ": Matrix dimensions do not match.";

        matrix_2d result = matrix_2d(m1.x, m1.y);
        for (size_t x = 0; x < m1.x; x++)
        {
            for (size_t y = 0; y < m1.y; y++)
            {
                result.elements[x][y] = m1.elements[x][y] * m2.elements[x][y];
            }
        }
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
        for (int i = 0; i < 4; i++)
        {
            q.points[i] = matrix_multiply(m, q.points[i]);
        }
    }

    matrix_2d matrix_add(const matrix_2d &m1, const matrix_2d &m2)
    {
        if (m1.x != m2.x || m1.y != m2.y)
            LOG(WARNING) << __FUNCTION__ << ": Matrix dimensions do not match.";

        matrix_2d result = matrix_2d(m1.x, m1.y);
        for (size_t x = 0; x < m1.x; x++)
        {
            for (size_t y = 0; y < m1.y; y++)
            {
                result.elements[x][y] = m1.elements[x][y] + m2.elements[x][y];
            }
        }
        return result;
    }

    matrix_2d matrix_transpose(const matrix_2d &m)
    {
        matrix_2d result = matrix_2d(m.y, m.x);
        for (size_t x = 0; x < m.x; x++)
        {
            for (size_t y = 0; y < m.y; y++)
            {
                result.elements[y][x] = m.elements[x][y];
            }
        }
        return result;
    }

    matrix_2d matrix_horizontal_concat(const matrix_2d &m1, const matrix_2d &m2)
    {
        if (m1.x != m2.x)
            LOG(WARNING) << __FUNCTION__ << ": Matrix dimensions do not match.";

        matrix_2d result(m1.x, m1.y + m2.y);
        for (size_t x = 0; x < m1.x; x++)
        {
            for (size_t y = 0; y < m1.y; y++)
            {
                result.elements[x][y] = m1.elements[x][y];
            }
        }
        for (size_t x = 0; x < m2.x; x++)
        {
            for (size_t y = 0; y < m2.y; y++)
            {
                result.elements[x][m1.y + y] = m2.elements[x][y];
            }
        }
        return result;
    }

    inline constexpr int negative_index(int max, int index)
    {
        return index < 0 ? max + index : index;
    }

    matrix_2d matrix_slice(const matrix_2d &m, int x_start, int x_end, int y_start, int y_end)
    {
        x_start = negative_index(m.x, x_start);
        x_end = negative_index(m.x, x_end);
        y_start = negative_index(m.y, y_start);
        y_end = negative_index(m.y, y_end);
        matrix_2d result(x_end - x_start + 1, y_end - y_start + 1);

        for (size_t x = 0; x <= x_end - x_start; x++)
            for (size_t y = 0; y <= y_end - y_start; y++)
                result.elements[x][y] = m.elements[x_start + x][y_start + y];

        return result;
    }
}
