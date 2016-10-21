//
// SplashKit Generated Timers C++ Code
// DO NOT MODIFY
//

#ifndef __timers_h
#define __timers_h

#include "timers.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

struct _timer_data;
typedef struct _timer_data *timer;
timer create_timer(string name);
void free_all_timers();
void free_timer(timer to_free);
bool has_timer(string name);
void pause_timer(string name);
void pause_timer(timer to_pause);
void reset_timer(string name);
void reset_timer(timer tmr);
void resume_timer(string name);
void resume_timer(timer to_resume);
void start_timer(string name);
void start_timer(timer to_start);
void stop_timer(string name);
void stop_timer(timer to_stop);
timer timer_named(string name);
bool timer_paused(string name);
bool timer_paused(timer to_get);
bool timer_started(string name);
bool timer_started(timer to_get);
unsigned int timer_ticks(string name);
unsigned int timer_ticks(timer to_get);

#endif /* __timers_h */
