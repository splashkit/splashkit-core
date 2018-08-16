/**
 * @header  random
 * @author  Andrew Cain
 * @brief   SplashKit random provides a simple implementation of random.
 *
 * The SplashKit`s random library provides two rnd methods, a `rnd()` which generates
 * a random number between 0 and 1, and `rnd(int ubound)` which
 * generates a random number between 0 and the value scpeficied in `ubound`.
 *
 * @attribute group  utilities
 * @attribute static random
 */

#ifndef random_hpp
#define random_hpp
namespace splashkit_lib
{
    /**
     * Generates a random number between 0 and 1
     *
     * @returns Returns a `float` between `0` and `1`
     */
    float rnd();

    /**
     * Generates a random number between 0 and `ubound`.
     *
     * @param ubound    the `int` representing the upper bound.
     * @returns Returns an `int` between `0` and `ubound`
     *
     * @attribute suffix  int
     */
    int rnd(int ubound);
    
    /**
     * Generates a random number between 'min' and `max`, including 'min' and 'max'.
     *
     * @param min    the `int` representing of minimum bound.
     * @param max    the `int` representing of maximum bound.
     * @returns Returns an `int` between and including `min` and `max`
     *
     * @attribute suffix  range
     */
    int rnd(int min, int max);

#endif /* random_hpp */
}
