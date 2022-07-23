#include "catch.hpp"

#include "terminal.h"
#include "random.h"
#include "matrix_2d.h"

#include <iostream>

using namespace std;
using namespace splashkit_lib;

/*/ Example? Trying out unit test format? May be useful
TEST_CASE("matrix manipulation", "[matrix]")
{
	SECTION("identity matrix multiplication")
	{
		for (size_t n = 1; n <= 5; n++)
		{
			matrix_2d mi = identity_matrix(n); // identity matrix
			
			matrix_2d result = matrix_multiply(mi, mi);
	
			REQUIRE(mi == mi);
			REQUIRE(result == result);
			REQUIRE(mi == result);
			REQUIRE(!(mi != result));

			for (size_t i = 0; i < n; i++)
			{
				for (size_t j = 0; j < n; j++)
				{
					if (i == j)
					{
						REQUIRE(result.elements[i][j] == 1);
					}
					else
					{
						REQUIRE(result.elements[i][j] == 0);
					}
				}
			}
		}
	}
	
	SECTION("regular matrix multiplication")
	{
		matrix_2d mi = identity_matrix();
		matrix_2d m2 = matrix_2d(2, 3);
		m2[0][0] = 1; m2[0][1] = 2; m2[0][2] = 3;
		m2[1][0] = 4; m2[1][1] = 5; m2[1][2] = 6;

		matrix_2d m3 = matrix_2d(m2);
		SECTION("matrix copies")
		{
			REQUIRE(m2 == m3);

			m3[0][0] = 0;
			REQUIRE(m2 != m3);
		}

		m3 = matrix_2d(3, 2);
		m3[0][0] = 10; m3[0][1] = 11;
		m3[1][0] = 20; m3[1][1] = 21;
		m3[2][0] = 30; m3[2][1] = 31;
	
		REQUIRE(matrix_multiply(m2, mi) == m2);
		REQUIRE(matrix_multiply(m2, m3) != mi);
		REQUIRE(matrix_multiply(m2, m3) != m2);

		matrix_2d m4 = matrix_2d(2, 2);
		m4[0][0] = 140; m4[0][1] = 146;
		m4[1][0] = 320; m4[1][1] = 335;
		REQUIRE(matrix_multiply(m2, m3) == m4);
	}
}
//*/

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
	if (m1 != m2) throw logic_error("Identity matrices must be equal!");

	write_line("TEST: matrix_multiply identity matrices");
	if (matrix_multiply(m1, m2) != m1) throw logic_error("Matrix multiply must be equal!");

	m2 = matrix_2d(2, 3);
	m2[0][0] = 1; m2[0][1] = 2; m2[0][2] = 3;
	m2[1][0] = 4; m2[1][1] = 5; m2[1][2] = 6;

	matrix_2d m3 = matrix_2d(m2);
	if (m2 != m3) throw logic_error("Matrix should be copied by value");
	m3[0][0] = 0;
	if (m2 == m3) throw logic_error("Matrix should be copied by value, changing copy should not change original");

	m3 = matrix_2d(3, 2);
	m3[0][0] = 10; m3[0][1] = 11;
	m3[1][0] = 20; m3[1][1] = 21;
	m3[2][0] = 30; m3[2][1] = 31;

	write("Matrix 2 ("); write(m2.x); write(", "); write(m2.y);
	write_line("): \n" + matrix_to_string(m2));

	write("Matrix 3 ("); write(m3.x); write(", "); write(m3.y);
	write_line("): \n" + matrix_to_string(m3));
	
	if (matrix_multiply(m2, m1) != m2) throw logic_error("Matrix multiply must be equal after identity multiplication!");

	write_line("Matrix 2 * Matrix 3: \n" + matrix_to_string(matrix_multiply(m2, m3)));
	if (matrix_multiply(m2, m3) == m1) throw logic_error("After multiply should not be identity!");
	if (matrix_multiply(m2, m3) == m2) throw logic_error("After multiply should not be the same!");

	matrix_2d m4 = matrix_2d(2, 2);
	m4[0][0] = 140; m4[0][1] = 146;
	m4[1][0] = 320; m4[1][1] = 335;
	if (matrix_multiply(m2, m3) != m4) throw logic_error("Multiplication should result in the specified matrix!");

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
	if (m6 != identity_matrix(4)) throw logic_error("Matrix 6 should be the identity matrix!");

	write_line(matrix_to_string(m5[m6]));
}