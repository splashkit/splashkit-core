//
//  test_physics.cpp
//  splashkit
//
//  Created by Clancy Light Townsend on 18/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include <iostream>
using namespace std;

#include "matrix_2d.h"

void run_physics_test()
{
    matrix_2d matrix = identity_matrix();
    
    cout << "Identity Matrix" << endl;
    cout << matrix_to_string(matrix) << endl;
}