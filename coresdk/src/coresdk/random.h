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
     * @attribute class   random
     * @attribute method  rnd
     *
     * @returns Returns a `float` between `0` and `1`
     */
    float rnd();

    /**
     * Generates a random number between 0 and `ubound`.
     *
     * @param ubound    the `int` representing the upper bound.
     *
     * @attribute class       random
     *
     * @returns Returns an `int` between `0` and `ubound`
     */
    int rnd(int ubound);
    
#endif /* random_hpp */
}
