#include "catch.hpp"

#include "terminal.h"
#include "random.h"
#include "matrix_2d.h"

#include <iostream>

using namespace std;
using namespace splashkit_lib;

void run_matrix_test()
{
	write_line(matrix_to_string(identity_matrix()));
	write_line(matrix_to_string(fill_matrix()));
	write_line(matrix_to_string(fill_matrix(4, 5, rnd())));
	matrix_2d matrix = fill_matrix(1, 2);
	matrix[0][1] = 1;
	write_line(matrix_to_string(matrix));

	matrix_2d m1 = identity_matrix();
	matrix_2d m2 = identity_matrix();

	write_line("TEST: equality");
	if ((m1 != m2).any()) throw logic_error("Identity matrices must be equal!");

	write_line("TEST: matrix_multiply identity matrices");
	if ((matrix_multiply(m1, m2) != m1).any()) throw logic_error("Matrix multiply must be equal!");

	matrix_2d m5 = matrix_2d(4, 4);
	int i = 1;
	for (double &cell : m5) // left to right top to bottom, i.e. fills row-wise, NEEDS to be by reference to write data
	{
		cell = i++;
	}
	write("Matrix 5 ("); write(m5.x); write(", "); write(m5.y);
	write_line("): \n" + matrix_to_string(m5));

	for (double &cell : m5)
	{
		cell = rnd();
	}
	write("Matrix 5 ("); write(m5.x); write(", "); write(m5.y);
	write_line("): \n" + matrix_to_string(m5));

	matrix_2d m6 = matrix_2d(4, 4);
	for (matrix_2d::iterator itr = m6.begin(); itr != m6.end(); ++itr)
	{
		if (itr.x == itr.y)
			*itr = 1;
		else
			*itr = 0;
	}
	write("Matrix 6 ("); write(m6.x); write(", "); write(m6.y);
	write_line("): \n" + matrix_to_string(m6));
	if ((m6 != identity_matrix(4)).any()) throw logic_error("Matrix 6 should be the identity matrix!");

	write_line(matrix_to_string(m5[m6]));
}