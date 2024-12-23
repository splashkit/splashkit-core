/**
 * This is the entry point for all unit tests. Catch will auto-generate a main
 * method within this file. No other file should define CATCH_CONFIG_MAIN.
 *
 * Run target skunit_tests to execute the tests.
 *
 * Created by James Armstrong http://github.com/jarmstrong
 */

#ifdef __linux__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
