/**
 * @header  matrix_2d
 * @author  Andrew Cain
 * @author  Clancy Light Townsend
 * @brief   Provides matrix functions to work on 2d coordinates.
 *
 * @attribute group  physics
 * @attribute static matrix_2d
 */

#ifndef matrix_2d_h
#define matrix_2d_h

#include <string>
#include "types.h"

using std::string;

namespace splashkit_lib
{

    /**
     *  In SplashKit, matrices can be used to combine together a number of
     *  operations that need to be performed on `vector_2d` values. You can
     *  translate, rotate and scale, and combine these together into a
     *  single matrix that can then be applied to vectors and points.
     *
     * Elements in the matrix can be referenced using the matrix[x][y]
     * notation. Where x is the row index and y is the column index.
     *
     * @field elements The elements of the matrix
     */
    struct matrix_2d
    {
    public:
        double **elements;
        int x, y;

        /**
         * @brief Construct a new matrix 2d object
         *
         * @param x Number of rows
         * @param y Number of columns
         */
        matrix_2d(int x = 3, int y = 3)
        {
            elements = new double *[x];
            for (size_t i = 0; i < x; i++)
            {
                elements[i] = new double[y];
            }
            this->x = x;
            this->y = y;
        }

        matrix_2d(const matrix_2d &other)
        {
            elements = new double *[other.x];
            for (size_t i = 0; i < other.x; i++)
            {
                elements[i] = new double[other.y];
            }
            this->x = other.x;
            this->y = other.y;

            for (size_t i = 0; i < x; i++)
            {
                for (size_t j = 0; j < y; j++)
                {
                    elements[i][j] = other.elements[i][j];
                }
            }
        }

        bool operator==(const matrix_2d &other)
        {
            if (x != other.x || y != other.y)
                return false;

            for (size_t i = 0; i < x; i++)
            {
                for (size_t j = 0; j < y; j++)
                {
                    if (elements[i][j] != other.elements[i][j])
                        return false;
                }
            }

            return true;
        }

        inline bool operator!=(const matrix_2d &other) { return !(*this == other); }

        /**
         * @brief Elements in the matrix can be referenced using the matrix[x][y] notation.
         * Where x is the row index and y is the column index.
         *
         * @param x The row index of the matrix
         * @param y The column index of the matrix
         * @return double
         */
        inline constexpr double *operator[](int x) { return elements[x]; }

        void operator delete(void *ptr)
        {
            matrix_2d *m = (matrix_2d *)ptr;
            for (size_t i = 0; i < m->x; i++)
            {
                delete[] m->elements[i];
            }
            delete[] m->elements;
        }

        struct iterator
        {
            size_t x = 0, y = 0;
            matrix_2d *ptr;
            iterator(matrix_2d *ptr, size_t x = 0)
            {
                this->ptr = ptr;
                this->x = x;
            }
            double &operator*() { return ptr->elements[x][y]; }
            void operator++()
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
            bool operator!=(const iterator &other) { return x != other.x || y != other.y; }
        };

        iterator begin()
        {
            return iterator(this);
        }
        iterator end()
        {
            return iterator(this, x);
        }
    };

    /**
     * @brief Returns the matrix with all elements as the given fill value
     *
     * @param x The number of rows in the resulting matrix
     * @param y The number of columns in the resulting matrix
     * @param fill The value to fill the matrix with
     * @return matrix_2d A new matrix with all elements set to the given value
     */
    matrix_2d fill_matrix(int x = 3, int y = 3, double fill = 0);

    /**
     * Returns the identity matrix. When a matrix_2d or Vector is multiplied by
     * the identity matrix the result is the original matrix or vector.
     *
     * @returns     An identify matrix.
     */
    matrix_2d identity_matrix(int n = 3);

    /**
     * Returns a matrix that can be used to translate 2d points. Moving them
     * by dx and dy.
     *
     * @param dx    The amount to move points along the x axis.
     * @param dy    The amount to move points along the y axis.
     * @returns     A matrix that will move points by dx, dy
     */
    matrix_2d translation_matrix(double dx, double dy);

    /**
     * Returns a translation matrix used to translate 2d points by the
     * distance in the vector_2d.
     *
     * @param pt    The point to translate to.
     * @returns     A matrix that will move points by amount in pt
     *
     * @attribute suffix  from_vector
     */
    matrix_2d translation_matrix(const vector_2d &pt);

    /**
     * Returns a translation matrix used to translate 2d points by the
     * distance in the point_2d.
     *
     * @param pt    The point to translate to.
     * @returns     A matrix that will move points by amount in pt
     *
     * @attribute suffix  to_point
     */
    matrix_2d translation_matrix(const point_2d &pt);

    /**
     * Returns a matrix that can be used to scale 2d points (both x and y).
     *
     * @param scale The amount to scale points by.
     * @returns     A matrix to scale points by.
     */
    matrix_2d scale_matrix(double scale);

    /**
     * Create a scale matrix that scales x and y to
     * different degrees.
     *
     * @param scale The amount to scale, with separate x and y components.
     * @returns     A matrix that will scale points based on scale parameter.
     *
     * @attribute suffix  from_vector
     */
    matrix_2d scale_matrix(const vector_2d &scale);

    /**
     * Create a scale matrix that scales x and y to
     * different degrees.
     *
     * @param scale The amount to scale, with separate x and y components.
     * @returns     A matrix that will scale points based on scale parameter.
     *
     * @attribute suffix  from_point
     */
    matrix_2d scale_matrix(const point_2d &scale);

    /**
     * Returns a rotation matrix that rotates 2d points by the angle.
     *
     * @param deg   The amount to rotate points
     * @returns     A matrix that encodes the rotation by a number of degrees.
     */
    matrix_2d rotation_matrix(double deg);

    /**
     * Create a matrix that can scale, rotate then translate geometry points.
     *
     * @param scale     The amount to scale
     * @param deg       The amount to rotate
     * @param translate The amount to move
     * @returns         A matrix that will scale, rotate, and translate.
     */
    matrix_2d scale_rotate_translate_matrix(const point_2d &scale, double deg, const point_2d &translate);

    /**
     *  Multiplies the two `matrix_2d` parameters, `m1` by `m2`, and returns
     *  the result as a new `matrix_2d`. Use this to combine the effects to two
     *  matrix transformations.
     *
     * @param m1    The first matrix
     * @param m2    The second matrix
     * @returns     The result of multiplying m1 by m2
     *
     * @attribute suffix  matrix
     */
    matrix_2d matrix_multiply(const matrix_2d &m1, const matrix_2d &m2);

    /**
     * @brief Multiplies each component of the matrix with the given scalar, and returns
     *  the result as a new `matrix_2d`.
     *
     * @param m             The matrix to multiply against
     * @param scalar        The scalar to multiply by
     * @return matrix_2d    A new matrix
     */
    matrix_2d matrix_multiply(const matrix_2d &m, double scalar);

    /**
     *  Multiplies the `Vector` parameter `v` with the `matrix_2d` `m` and
     *  returns the result as a `Vector`. Use this to transform the vector with
     *  the matrix (to apply scaling, rotation or translation effects).
     *
     * @param m     The matrix with the transformation to apply.
     * @param v     The vector to be transformed.
     * @returns     A new vector, the result of applying the transformation to v.
     *
     * @attribute suffix  vector
     */
    vector_2d matrix_multiply(const matrix_2d &m, const vector_2d &v);

    /**
     *  Multiplies the `point_2d` parameter `v with the `matrix_2d` `m and
     *  returns the result as a `point_2d`. Use this to transform the vector with
     *  the matrix (to apply scaling, rotation or translation effects).
     *
     * @param m     The matrix with the transformation to apply.
     * @param pt    The point to be transformed.
     * @returns     A new point, the result of applying the transformation to pt.
     *
     * @attribute suffix  point
     */
    point_2d matrix_multiply(const matrix_2d &m, const point_2d &pt);

    /**
     * @brief Performs component-wise multiplication between the two matrices. The Hadamard product. Returns
     *  the result as a new `matrix_2d`.
     *
     * @param m1    The first matrix
     * @param m2    The second matrix
     * @returns     The result of multiplying m1 by m2
     */
    matrix_2d matrix_multiply_components(const matrix_2d &m1, const matrix_2d &m2);

    /**
     *  Calculate the inverse of a matrix.
     *
     * @param m     The matrix to invert.
     * @returns     A matrix that is the inverse of m
     */
    matrix_2d matrix_inverse(const matrix_2d &m);

    /**
     * Use a matrix to transform all of the points in a triangle.
     *
     * @param m     The matrix to be applied to the triangle.
     * @param tri   The triangle to transform.
     *
     * @attribute suffix  to_triangle
     */
    void apply_matrix(const matrix_2d &m, triangle &tri);

    /**
     * Use a matrix to transform all of the points in a quad.
     *
     * @param matrix    The matrix with the transformations needed.
     * @param q         The quad to transform.
     *
     * @attribute suffix  to_quad
     */
    void apply_matrix(const matrix_2d &matrix, quad &q);

    /**
     * This function returns a string representation of a Matrix.
     *
     * @param matrix    The matrix to convert to a string.
     * @returns         A string representation of the matrix.
     */
    string matrix_to_string(const matrix_2d &matrix);

    /**
     * @brief Matrix Addition. Adds each component of m1 and m2 (component-wise addition).
     *
     * @param m1
     * @param m2
     * @return matrix_2d
     */
    matrix_2d matrix_add(const matrix_2d &m1, const matrix_2d &m2);

    /**
     * @brief Transposes the given matrix. Returns a flipped version of the original matrix where rows and columns are swapped.
     *
     * @param m
     * @return matrix_2d A new matrix where rows and columns are swapped.
     */
    matrix_2d matrix_transpose(const matrix_2d &m);

    /**
     * @brief Combines two matrices with the same number of rows.
     *
     * @param m1 The first matrix (can be referenced using the same x, y values)
     * @param m2 The second matrix to be concatenated onto the end of the first
     * @return matrix_2d A new matrix
     */
    matrix_2d matrix_horizontal_concat(const matrix_2d &m1, const matrix_2d &m2);
}
#endif /* matrix_2d_h */
