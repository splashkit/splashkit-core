//
//  matrix_2d.cpp
//  splashkit
//
//  Created by Clancy Light Townsend on 18/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "matrix_2d.h"

#include <iomanip>
#include <sstream>

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


matrix_2d matrix_multiply(const matrix_2d &m1,const matrix_2d &m2)
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



