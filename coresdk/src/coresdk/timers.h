/**
 * @header  timers
 * @author  Andrew Cain
 * @brief   Timers in SplashKit can be used to track the passing of time.
 *
 * @attribute static timers
 * @attribute group  timers
 */

#ifndef timers_h
#define timers_h

#include <string>
using std::string;

namespace splashkit_lib
{
    /**
     * Timers in SplashKit can be used to track the passing of time. In general
     * you will create a timer, start it, then use it to track time by asking
     * for the timer's ticks (milliseconds).
     *
     * @attribute class timer
     */
    typedef struct _timer_data *timer;

    /**
     * Create and return a new Timer. The timer will not be started, and will have
     * an initial 'ticks' of 0.
     *
     * @attribute class timer
     * @attribute constructor true
     *
     * @param  name The name of the timer for resource tracking
     * @return      A new timer.
     */
    timer create_timer(string name);

    /**
     * Free the memory used to store this timer.
     *
     * @attribute class timer
     * @attribute destructor true
     *
     * @param to_free The time to be released.
     */
    void free_timer(timer to_free);

    /**
     * Free all of timers that have been created.
     */
    void free_all_timers();

    /**
     * Get the timer created with the indicated name.
     *
     * @param  name The name of the timer to fetch
     * @return      Returns the timer fetched from SplashKit
     */
    timer timer_named(string name);

    /**
     * Checks if SplashKit has a timer with the indicated name.
     *
     * @param  name The name of the timer
     * @return      True if SplashKit has created a timer with that name.
     *
     * @attribute suffix _named
     */
    bool has_timer(string name);

    /**
     * Start a timer. The timer will then start recording the time that has passed.
     * You can check how long has past since the timer was started using the
     * `timer_ticks` function.
     *
     * @attribute class timer
     * @attribute method start
     *
     * @param to_start The timer
     */
    void start_timer(timer to_start);

    /**
     * Start a timer. The timer will then start recording the time that has passed.
     * You can check how long has past since the timer was started using the
     * `timer_ticks` function.
     *
     * @param name The name of the timer
     *
     * @attribute suffix _named
     */
    void start_timer(string name);

    /**
     * Stop the timer. The time is reset to 0 and you must
     * recall start to begin the timer ticking again.
     *
     * @attribute class timer
     * @attribute method stop
     *
     * @param to_stop The timer
     */
    void stop_timer(timer to_stop);

    /**
     * Stop the timer. The time is reset to 0 and you must
     * recall start to begin the timer ticking again.
     *
     * @param name The name of the timer
     *
     * @attribute suffix _named
     */
    void stop_timer(string name);

    /**
     * Pause the timer, getting ticks from a paused timer
     * will continue to return the same time.
     *
     * @attribute class timer
     * @attribute method pause
     *
     * @param to_pause The timer
     */
    void pause_timer(timer to_pause);

    /**
     * Pause the timer, getting ticks from a paused timer
     * will continue to return the same time.
     *
     * @param name The name of the timer
     *
     * @attribute suffix _named
     */
    void pause_timer(string name);

    /**
     * Resumes a paused timer.
     *
     * @attribute class timer
     * @attribute method resume
     *
     * @param to_resume The timer
     */
    void resume_timer(timer to_resume);

    /**
     * Resumes the named timer.
     *
     * @param name The name of the timer
     *
     * @attribute suffix _named
     */
    void resume_timer(string name);

    /**
     * Resets the time of a given timer
     *
     * @attribute class timer
     * @attribute method reset
     *
     * @param tmr The timer
     */
    void reset_timer(timer tmr);

    /**
     * Resets the named timer
     *
     * @param name The name of the timer
     *
     * @attribute suffix _named
     */
    void reset_timer(string name);

    /**
     * Gets the number of ticks (milliseconds) that have passed since the timer
     * was started/reset. When paused the timer's ticks will not advance until
     * the timer is once again resumed.
     *
     * @attribute class timer
     * @attribute getter ticks
     *
     * @param  to_get The timer
     * @return        The number of milliseconds that have passed since the
     *                timer was created (excluding the time the timer was
     *                paused)
     */
    unsigned int timer_ticks(timer to_get);

    /**
     * Gets the number of ticks (milliseconds) that have passed since the timer
     * was started/reset. When paused the timer's ticks will not advance until
     * the timer is once again resumed.
     *
     * @param  name The name of the Timer
     * @return      The number of milliseconds that have passed since the
     *              timer was created (excluding the time the timer was
     *              paused)
     *
     * @attribute suffix _named
     */
    unsigned int timer_ticks(string name);

    /**
     * Indicates if the timer is paused.
     *
     * @attribute class timer
     * @attribute getter is_paused
     *
     * @param  to_get The timer
     * @return        True if the timer is paused
     */
    bool timer_paused(timer to_get);

    /**
     * Indicates if the timer is paused.
     *
     * @param  name   The name of the timer
     * @return        True if the timer is paused
     *
     * @attribute suffix _named
     */
    bool timer_paused(string name);

    /**
     * Indicates if the timer is started.
     *
     * @attribute class timer
     * @attribute getter is_started
     *
     * @param  to_get The timer
     * @return        True if the timer has been started
     */
    bool timer_started(timer to_get);

    /**
     * Indicates if the timer is started.
     *
     * @param  name   The name of the timer
     * @return        True if the timer has been started
     *
     * @attribute suffix _named
     */
    bool timer_started(string name);
}

#endif /* timers_hpp */
