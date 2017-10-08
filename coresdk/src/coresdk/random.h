//
//  random.hpp
//  splashkit
//
//  Created by Andrew Cain on 24/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef random_hpp
#define random_hpp

/// Generates a random number between 0 and 1.
///
float rnd();

/// Generates a random integer up to (but not including) ubound. Effectively,
/// the ubound value specifies the number of random values to create.
///
int rnd(int ubound);

#endif /* random_hpp */
