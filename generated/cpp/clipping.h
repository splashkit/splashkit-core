//
// SplashKit Generated Clipping C++ Code
// DO NOT MODIFY
//

#ifndef __clipping_h
#define __clipping_h

#include "window_manager.h"
#include "types.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

rectangle current_clip();
rectangle current_clip(bitmap bmp);
rectangle current_clip(window wnd);
void pop_clip(window wnd);
void pop_clip();
void pop_clip(bitmap bmp);
void push_clip(window wnd, const rectangle &r);
void push_clip(bitmap bmp, const rectangle &r);
void push_clip(const rectangle &r);
void reset_clip(bitmap bmp);
void reset_clip();
void reset_clip(window wnd);
void set_clip(const rectangle &r);
void set_clip(bitmap bmp, const rectangle &r);
void set_clip(window wnd, const rectangle &r);

#endif /* __clipping_h */
