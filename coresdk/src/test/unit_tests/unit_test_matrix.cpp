#include "catch.hpp"

#include "matrix_2d.h"

using namespace splashkit_lib;

TEST_CASE("matrix manipulation", "[matrix]")
{
	SECTION("identity matrix multiplication")
	{
		for (size_t n = 1; n <= 5; n++)
		{
			matrix_2d mi = identity_matrix(n); // identity matrix

			matrix_2d result = matrix_multiply(mi, mi);

			REQUIRE((mi == mi).all());
			REQUIRE((result == result).all());
			REQUIRE((mi == result).all());
			REQUIRE(!(mi != result).any());

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
			REQUIRE((m2 == m3).all());

			m3[0][0]++;
			REQUIRE((m2 != m3).any());
		}

		m3 = matrix_2d(3, 2);
		m3[0][0] = 10; m3[0][1] = 11;
		m3[1][0] = 20; m3[1][1] = 21;
		m3[2][0] = 30; m3[2][1] = 31;

		REQUIRE((matrix_multiply(m2, mi) == m2).all());
		REQUIRE((matrix_multiply(m2, m3) != mi).any());
		REQUIRE((matrix_multiply(m2, m3) != m2).any());

		matrix_2d m4 = matrix_2d(2, 2);
		m4[0][0] = 140; m4[0][1] = 146;
		m4[1][0] = 320; m4[1][1] = 335;
		REQUIRE((matrix_multiply(m2, m3) == m4).all());
	}
}