//
// SplashKit Generated Matrix 2 D C++ Code
// DO NOT MODIFY
//

#ifndef __matrix_2d_h
#define __matrix_2d_h

#include "types.h"
#include "matrix_2d.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

typedef struct {
    double elements[3][3];
} matrix_2d;
void apply_matrix(const matrix_2d &matrix, quad &q);
void apply_matrix(const matrix_2d &m, triangle &tri);
matrix_2d identity_matrix();
matrix_2d matrix_inverse(const matrix_2d &m);
point_2d matrix_multiply(const matrix_2d &m, const point_2d &pt);
matrix_2d matrix_multiply(const matrix_2d &m1, const matrix_2d &m2);
vector_2d matrix_multiply(const matrix_2d &m, const vector_2d &v);
string matrix_to_string(const matrix_2d &matrix);
matrix_2d rotation_matrix(double deg);
matrix_2d scale_matrix(const point_2d &scale);
matrix_2d scale_matrix(const vector_2d &scale);
matrix_2d scale_matrix(double scale);
matrix_2d scale_rotate_translate_matrix(const point_2d &scale, double deg, const point_2d &translate);
matrix_2d translation_matrix(const point_2d &pt);
matrix_2d translation_matrix(const vector_2d &pt);
matrix_2d translation_matrix(double dx, double dy);

#endif /* __matrix_2d_h */
