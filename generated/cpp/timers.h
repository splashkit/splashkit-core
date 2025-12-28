//
// SplashKit Generated Timers C++ Code
// DO NOT MODIFY
//

#ifndef __timers_h
#define __timers_h

#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
using std::string;
using std::vector;
using std::to_string;

struct _timer_data;
typedef struct _timer_data *timer;
/**
* Create and return a new Timer. The timer will not be started, and will have
* an initial 'ticks' of 0.
* @param name The name of the timer for resource tracking
* @return A new timer.
*/
timer create_timer(string name);
/**
* Free all of timers that have been created.

*
*/
void free_all_timers();
/**
* Free the memory used to store this timer.
* @param to_free The time to be released.
*
*/
void free_timer(timer to_free);
/**
* Checks if SplashKit has a timer with the indicated name.
* @param name The name of the timer
* @return True if SplashKit has created a timer with that name.
*/
bool has_timer(string name);
/**
* Pause the timer, getting ticks from a paused timer
* will continue to return the same time.
* @param name The name of the timer
*
*/
void pause_timer(string name);
/**
* Pause the timer, getting ticks from a paused timer
* will continue to return the same time.
* @param to_pause The timer
*
*/
void pause_timer(timer to_pause);
/**
* Resets the named timer
* @param name The name of the timer
*
*/
void reset_timer(string name);
/**
* Resets the time of a given timer
* @param tmr The timer
*
*/
void reset_timer(timer tmr);
/**
* Resumes the named timer.
* @param name The name of the timer
*
*/
void resume_timer(string name);
/**
* Resumes a paused timer.
* @param to_resume The timer
*
*/
void resume_timer(timer to_resume);
/**
* Start a timer. The timer will then start recording the time that has passed.
* You can check how long has past since the timer was started using the
* `timer_ticks` function.
* @param name The name of the timer
*
*/
void start_timer(string name);
/**
* Start a timer. The timer will then start recording the time that has passed.
* You can check how long has past since the timer was started using the
* `timer_ticks` function.
* @param to_start The timer
*
*/
void start_timer(timer to_start);
/**
* Stop the timer. The time is reset to 0 and you must
* recall start to begin the timer ticking again.
* @param name The name of the timer
*
*/
void stop_timer(string name);
/**
* Stop the timer. The time is reset to 0 and you must
* recall start to begin the timer ticking again.
* @param to_stop The timer
*
*/
void stop_timer(timer to_stop);
/**
* Get the timer created with the indicated name.
* @param name The name of the timer to fetch
* @return Returns the timer fetched from SplashKit
*/
timer timer_named(string name);
/**
* Indicates if the timer is paused.
* @param name The name of the timer
* @return True if the timer is paused
*/
bool timer_paused(string name);
/**
* Indicates if the timer is paused.
* @param to_get The timer
* @return True if the timer is paused
*/
bool timer_paused(timer to_get);
/**
* Indicates if the timer is started.
* @param name The name of the timer
* @return True if the timer has been started
*/
bool timer_started(string name);
/**
* Indicates if the timer is started.
* @param to_get The timer
* @return True if the timer has been started
*/
bool timer_started(timer to_get);
/**
* Gets the number of ticks (milliseconds) that have passed since the timer
* was started/reset. When paused the timer's ticks will not advance until
* the timer is once again resumed.
* @param name The name of the Timer
* @return The number of milliseconds that have passed since the
timer was created (excluding the time the timer was
paused)
*/
unsigned int timer_ticks(string name);
/**
* Gets the number of ticks (milliseconds) that have passed since the timer
* was started/reset. When paused the timer's ticks will not advance until
* the timer is once again resumed.
* @param to_get The timer
* @return The number of milliseconds that have passed since the
timer was created (excluding the time the timer was
paused)
*/
unsigned int timer_ticks(timer to_get);

#endif /* __timers_h */
