//
//  matrix_2d.hpp
//  splashkit
//
//  Created by Clancy Light Townsend on 18/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef matrix_2d_h
#define matrix_2d_h

#include <string>
using namespace std;

#include "types.h"

/**
 *  In SwinGame, Matrices can be used to combine together a number of
 *  operations that need to be performed on Vectors. You can translate,
 *  rotate and scale, and combine these together into a single matrix
 *  that can then be applied to vectors and points.
 *
 * @param elements foo bar qux
 */
struct matrix_2d
{
    float elements[3][3];
};

/// Use a matrix to transform all of the points in a quad.
///
/// @lib ApplyMatrixToquad
/// @sn matrix:%s applyToquad:%s
///
/// @class matrix_2d
/// @method ApplyTo
/// @updatesArrayParam 2
/// @csn applyToquad:%s
void apply_matrix(const matrix_2d &matrix, quad &q);

/// Returns the identity matrix. When a matrix_2d or Vector is multiplied by
/// the identity matrix the result is the original matrix or vector.
///
/// @lib
///
/// @class matrix_2d
/// @static
/// @method IdentityMatrix
matrix_2d identity_matrix();

/// Returns a matrix that can be used to translate 2d points. Moving them
/// by dx and dy.
///
/// @lib
/// @sn translationMatrixDx:%s dy:%s
///
/// @class matrix_2d
/// @static
/// @method TranslationMatrix
/// @csn translationMatrixDx:%s dy:%s
///
/// @doc_idx 0
matrix_2d translation_matrix(float dx, float dy);

/// Returns a translation matric used to translate 2d points by the
/// distance in the point_2d.
///
/// @lib TranslationMatrixPt
/// @sn translationMatrix:%s
///
/// @class matrix_2d
/// @static
/// @overload TranslationMatrix TranslationMatrixWithPoint
/// @csn translationMatrix:%s
matrix_2d translation_matrix(point_2d pt);

/// Returns a matrix that can be used to scale 2d points (both x and y).
///
/// @lib
/// @sn scaleMatrix:%s
///
/// @class matrix_2d
/// @static
/// @method ScaleMatrix
///
/// @doc_idx 0
matrix_2d scale_matrix(float scale);

/// Create a scale matrix that scales x and y to
/// different degrees.
///
/// @lib ScaleMatrixByPoint
/// @sn scaleMatricByPoint:%s
///
/// @class matrix_2d
/// @static
/// @overload ScaleMatrix ScaleMatrixWithPoint
/// @csn scaleMatrixByPoint:%s
matrix_2d scale_matrix(point_2d scale);

/// Returns a rotation matrix that rotates 2d points by the angle.
///
/// @lib
///
/// @class matrix_2d
/// @static
/// @method RotationMatrix
matrix_2d rotation_matrix(float deg);

/// Create a matrix that can scale, rotate then translate geometry points.
///
/// @lib
/// @sn matrixToScale:%s rotate:%s translate:%s
///
/// @class matrix_2d
/// @static
/// @method ScaleRotateTranslateMatrix
/// @csn matrixToScale:%s rotate:%s translate:%s
matrix_2d scale_rotate_translate_matrix(const point_2d &scale, float deg, const point_2d &translate);

///// Multiplies the two `matrix_2d` parameters, ``m1`` by ``m2``, and returns
///// the result as a new `matrix_2d`. Use this to combine the effects to two
///// matrix transformations.
/////
///// @lib
///// @sn matrix:%s multiplyByMatrix:%s
/////
///// @class matrix_2d
///// @method Multiply
///// @csn multiplyByMatrix:%s
//function MatrixMultiply(const m1, m2: matrix_2d): matrix_2d; overload;
//
///// Multiplies the `Vector` parameter ``v`` with the `matrix_2d` ``m`` and
///// returns the result as a `Vector`. Use this to transform the vector with
///// the matrix (to apply scaling, rotation or translation effects).
/////
///// @lib MatrixMultiplyVector
///// @sn matrix:%s multiplyByVector:%s
/////
///// @class matrix_2d
///// @overload Multiply MultiplyVector
///// @csn multiplyByVector:%s
//function MatrixMultiply(const m: matrix_2d; const v: Vector): Vector; overload;
//
///// Calculate the inverse of a matrix.
/////
///// @lib
/////
///// @class matrix_2d
///// @method Inverse
//function MatrixInverse(const m: matrix_2d): matrix_2d;
//
///// Use a matrix to transform all of the points in a triangle.
/////
///// @lib
///// @sn matrix:%s applyToTriangle:%s
/////
///// @class matrix_2d
///// @method ApplyTo
///// @updatesArrayParam 2
///// @csn applyToTriangle:%s
//void ApplyMatrix(const m: matrix_2d; var tri: Triangle);
//
//{$ifdef FPC}
///// Multiply matrix by the vector.
/////
///// @class matrix_2d
///// @calls MatrixMultiplyVector
//operator * (const m: matrix_2d; const v: Vector) r : Vector;
//{$endif}
//
//{$ifdef FPC}
///// Multiply the two matricies together.
/////
///// @class matrix_2d
///// @calls MatrixMultiply
//operator * (const m1, m2: matrix_2d) r : matrix_2d;
//{$endif}
//

/// This function returns a string representation of a Matrix.
///
/// @lib
///
/// @class matrix_2d
/// @method ToString
/// @csn description
string matrix_to_string(const matrix_2d &matrix);

#endif /* matrix_2d_h */
