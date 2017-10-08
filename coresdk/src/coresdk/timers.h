//
//  timers.hpp
//  splashkit
//
//  Created by Andrew Cain on 12/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef timers_h
#define timers_h

#include <string>
using namespace std;

typedef struct _timer_data *timer;

/**
 * Create and return a new Timer. The timer will not be started, and will have
 * an initial 'ticks' of 0.
 *
 * @attribute class timer
 * @attribute constructor true
 */
timer create_timer(string name);

/**
 * Free the memory used to store this timer.
 *
 * @attribute class timer
 * @attribute destructor true
 */
void free_timer(timer to_free);

/**
 * Free all of timers that have been created.
 *
 * @attribute class timers
 * @attribute method release_all_timers
 */
void free_all_timers();

/**
 * Get the timer created with the indicated name.
 *
 * @attribute class timers
 * @attribute method get_timer_named
 */
timer timer_named(string name);

/**
 * Checks if SplashKit has a timer with the indicated name.
 *
 * @attribute class timers
 * @attribute method has_timer
 */
bool has_timer(string name);

/**
 * Start a timer. The timer will then start recording the time that has passed.
 * You can check how long has past since the timer was started using the
 * `timer_ticks` function.
 *
 * @attribute class timer
 * @attribute method start
 */
void start_timer(timer to_start);

/**
 * Start a timer. The timer will then start recording the time that has passed.
 * You can check how long has past since the timer was started using the
 * `timer_ticks` function.
 *
 */
void start_timer(string name);

/**
 * Stop the timer. The time is reset to 0 and you must
 * recall start to begin the timer ticking again.
 * 
 * @attribute class timer
 * @attribute method stop
 */
void stop_timer(timer to_stop);

/**
 * Stop the timer. The time is reset to 0 and you must
 * recall start to begin the timer ticking again.
 */
void stop_timer(string name);

/**
 * Pause the timer, getting ticks from a paused timer
 * will continue to return the same time.
 *
 * @attribute class timer
 * @attribute method pause
 */
 void pause_timer(timer to_pause);

/**
 * Pause the timer, getting ticks from a paused timer
 * will continue to return the same time.
 */
void pause_timer(string name);

/**
 * Resumes a paused timer.
 *
 * @attribute class timer
 * @attribute method resume
 */
void resume_timer(timer to_resume);

/**
 * Resumes the named timer.
 */
void resume_timer(string name);

/**
 * Resets the time of a given timer
 *
 * @attribute class timer
 * @attribute method reset
 */
void reset_timer(timer tmr);

/**
 * Resets the named timer
 */
void reset_timer(string name);

/**
 * Gets the number of ticks (milliseconds) that have passed since the timer
 * was started/reset. When paused the timer's ticks will not advance until
 * the timer is once again resumed.
 *
 * @attribute class timer
 * @attribute getter ticks
 */
unsigned int timer_ticks(timer to_get);

/**
 * Gets the number of ticks (milliseconds) that have passed since the timer
 * was started/reset. When paused the timer's ticks will not advance until
 * the timer is once again resumed.
 */
unsigned int timer_ticks(string name);

/**
 * Indicates if the timer is paused.
 *
 * @attribute class timer
 * @attribute getter is_paused
 */
bool timer_paused(timer to_get);

/**
 * Indicates if the timer is paused.
 */
bool timer_paused(string name);

/**
 * Indicates if the timer is started.
 *
 * @attribute class timer
 * @attribute getter is_started
 */
bool timer_started(timer to_get);

/**
 * Indicates if the timer is started.
 */
bool timer_started(string name);


#endif /* timers_hpp */
