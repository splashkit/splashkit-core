//
// SplashKit Generated Matrix 2 D C++ Code
// DO NOT MODIFY
//

#ifndef __matrix_2d_h
#define __matrix_2d_h

#include "types.h"
#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
using std::string;
using std::vector;
using std::to_string;

typedef struct {
    double elements[3][3];
} matrix_2d;

inline bool operator==(const matrix_2d& lhs, const matrix_2d& rhs) {
    return
        lhs.elements[0][0] == rhs.elements[0][0] &&
        lhs.elements[0][1] == rhs.elements[0][1] &&
        lhs.elements[0][2] == rhs.elements[0][2] &&
        lhs.elements[1][0] == rhs.elements[1][0] &&
        lhs.elements[1][1] == rhs.elements[1][1] &&
        lhs.elements[1][2] == rhs.elements[1][2] &&
        lhs.elements[2][0] == rhs.elements[2][0] &&
        lhs.elements[2][1] == rhs.elements[2][1] &&
        lhs.elements[2][2] == rhs.elements[2][2];
}

inline bool operator!=(const matrix_2d& lhs, const matrix_2d& rhs) {
    return !(lhs == rhs);
}

/**
* Use a matrix to transform all of the points in a quad.
* @param matrix The matrix with the transformations needed.
* @param q The quad to transform.
*
*/;
void apply_matrix(const matrix_2d &matrix, quad &q);
/**
* Use a matrix to transform all of the points in a triangle.
* @param m The matrix to be applied to the triangle.
* @param tri The triangle to tranform.
*
*/;
void apply_matrix(const matrix_2d &m, triangle &tri);
/**
* Returns the identity matrix. When a matrix_2d or Vector is multiplied by
* the identity matrix the result is the original matrix or vector.

* @return An identify matrix.
*/;
matrix_2d identity_matrix();
/**
* Calculate the inverse of a matrix.
* @param m The matrix to invert.
* @return A matrix that is the inverse of m
*/;
matrix_2d matrix_inverse(const matrix_2d &m);
/**
* Multiplies the `point_2d` parameter `v with the `matrix_2d` `m and
* returns the result as a `point_2d`. Use this to transform the vector with
* the matrix (to apply scaling, rotation or translation effects).
* @param m The matrix with the transformation to apply.
* @param pt The point to be transformed.
* @return A new point, the result of applying the transformation to pt.
*/;
point_2d matrix_multiply(const matrix_2d &m, const point_2d &pt);
/**
* Multiplies the two `matrix_2d` parameters, `m1` by `m2`, and returns
* the result as a new `matrix_2d`. Use this to combine the effects to two
* matrix transformations.
* @param m1 The first matrix
* @param m2 The second matrix
* @return The result of multiplying m1 by m2
*/;
matrix_2d matrix_multiply(const matrix_2d &m1, const matrix_2d &m2);
/**
* Multiplies the `Vector` parameter `v` with the `matrix_2d` `m` and
* returns the result as a `Vector`. Use this to transform the vector with
* the matrix (to apply scaling, rotation or translation effects).
* @param m The matrix with the transformation to apply.
* @param v The vector to be transformed.
* @return A new vector, the result of applying the transformation to v.
*/;
vector_2d matrix_multiply(const matrix_2d &m, const vector_2d &v);
/**
* This function returns a string representation of a Matrix.
* @param matrix The matrix to convert to a string.
* @return A string representation of the matrix.
*/;
string matrix_to_string(const matrix_2d &matrix);
/**
* Returns a rotation matrix that rotates 2d points by the angle.
* @param deg The amount to rotate points
* @return A matrix that encodes the rotation by a number of degrees.
*/;
matrix_2d rotation_matrix(double deg);
/**
* Create a scale matrix that scales x and y to
* different degrees.
* @param scale The amount to scale, with separate x and y components.
* @return A matrix that will scale points based on scale parameter.
*/;
matrix_2d scale_matrix(const point_2d &scale);
/**
* Create a scale matrix that scales x and y to
* different degrees.
* @param scale The amount to scale, with separate x and y components.
* @return A matrix that will scale points based on scale parameter.
*/;
matrix_2d scale_matrix(const vector_2d &scale);
/**
* Returns a matrix that can be used to scale 2d points (both x and y).
* @param scale The amount to scale points by.
* @return A matrix to scale points by.
*/;
matrix_2d scale_matrix(double scale);
/**
* Create a matrix that can scale, rotate then translate geometry points.
* @param scale The amount to scale
* @param deg The amount to rotate
* @param translate The amount to move
* @return A matrix that will scale, rotate, and translate.
*/;
matrix_2d scale_rotate_translate_matrix(const point_2d &scale, double deg, const point_2d &translate);
/**
* Returns a translation matric used to translate 2d points by the
* distance in the point_2d.
* @param pt The point to translate to.
* @return A matrix that will move points by amount in pt
*/;
matrix_2d translation_matrix(const point_2d &pt);
/**
* Returns a translation matric used to translate 2d points by the
* distance in the vector_2d.
* @param pt The point to translate to.
* @return A matrix that will move points by amount in pt
*/;
matrix_2d translation_matrix(const vector_2d &pt);
/**
* Returns a matrix that can be used to translate 2d points. Moving them
* by dx and dy.
* @param dx The amount to move points along the x axis.
* @param dy The amount to move points along the y axis.
* @return A matrix that will move points by dx, dy
*/;
matrix_2d translation_matrix(double dx, double dy);

#endif /* __matrix_2d_h */
