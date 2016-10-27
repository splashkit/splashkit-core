//
// SplashKit Generated Rectangle Drawing C++ Code
// DO NOT MODIFY
//

#ifndef __rectangle_drawing_h
#define __rectangle_drawing_h

#include "types.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

void draw_quad(color clr, const quad &q);
void draw_quad(color clr, const quad &q, const drawing_options &opts);
void draw_rectangle(color clr, const rectangle &rect);
void draw_rectangle(color clr, const rectangle &rect, const drawing_options &opts);
void draw_rectangle(color clr, float x, float y, float width, float height);
void draw_rectangle(color clr, float x, float y, float width, float height, const drawing_options &opts);
void fill_quad(color clr, const quad &q);
void fill_quad(color clr, const quad &q, const drawing_options &opts);
void fill_rectangle(color clr, const rectangle &rect);
void fill_rectangle(color clr, const rectangle &rect, const drawing_options &opts);
void fill_rectangle(color clr, float x, float y, float width, float height);
void fill_rectangle(color clr, float x, float y, float width, float height, const drawing_options &opts);

#endif /* __rectangle_drawing_h */
