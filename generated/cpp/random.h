//
// SplashKit Generated Random C++ Code
// DO NOT MODIFY
//

#ifndef __random_h
#define __random_h

#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
using std::string;
using std::vector;
using std::to_string;

/**
* Generates a random number between 'min' and `max`, including 'min' and 'max'.
* @param min the `int` representing of minimum bound.
* @param max the `int` representing of maximum bound.
* @return Returns an `int` between and including `min` and `max`
*/
int rnd(int min, int max);
/**
* Generates a random number between 0 and 1

* @return Returns a `float` between `0` and `1`
*/
float rnd();
/**
* Generates a random number between 0 and `ubound`.
* @param ubound the `int` representing the upper bound.
* @return Returns an `int` between `0` and `ubound`
*/
int rnd(int ubound);

#endif /* __random_h */
