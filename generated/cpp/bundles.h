/*
 * SplashKit Bundles
 *
 * This file is generated from the SplashKit source.
 * Modifying it will cause failures.
 *
 */

#ifndef __bundles_h
#define __bundles_h

#include <string>
#include <vector>
using std::string;
using std::vector;

void free_resource_bundle(const string name);
bool has_resource_bundle(const string &name);
void load_resource_bundle(const string &name, const string &filename);

#endif /* __bundles_h */
