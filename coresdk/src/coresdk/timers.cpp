//
//  timers.cpp
//  splashkit
//
//  Created by Andrew Cain on 12/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "timers.h"

#include "utils_driver.h"
#include "backend_types.h"
#include "utility_functions.h"

#include <map>

using std::map;

namespace splashkit_lib
{
    static map<string, timer> _timers;

    struct _timer_data
    {
        pointer_identifier id;
        unsigned int start_ticks;
        unsigned int paused_ticks;
        bool paused;
        bool started;
        string name;
    };

    timer create_timer(string name)
    {
        if (has_timer(name)) return timer_named(name);

        timer result;
        result = new(_timer_data);
        result->id = TIMER_PTR;
        result->name = name;

        result->start_ticks = 0;
        result->paused_ticks = 0;
        result->paused = false;
        result->started = false;

        _timers[to_lower(name)] = result;
        return result;
    }

    /**
     * Free the memory used to store this timer.
     *
     * @attribute class timer
     * @attribute destructor true
     */
    void free_timer(timer to_free)
    {
        if ( INVALID_PTR(to_free, TIMER_PTR) )
        {
            LOG(WARNING) << "Trying to free timer with invalid pointer";
            return;
        }

        notify_of_free(to_free);

        _timers.erase(to_lower(to_free->name));

        to_free->id = NONE_PTR;

        delete(to_free);
    }

    void free_all_timers()
    {
        FREE_ALL_FROM_MAP(_timers, TIMER_PTR, free_timer);
    }

    timer timer_named(string name)
    {
        if (not has_timer(name)) return nullptr;

        return _timers[to_lower(name)];
    }

    bool has_timer(string name)
    {
        return _timers.count(to_lower(name)) > 0;
    }

    void start_timer(timer to_start)
    {
        if (INVALID_PTR(to_start, TIMER_PTR))
        {
            LOG(WARNING) << "Attempting to start invalid timer";
            return;
        }

        to_start->started = true;
        to_start->paused = false;
        to_start->start_ticks = sk_get_ticks();
    }

    void start_timer(string name)
    {
        start_timer(timer_named(name));
    }

    void stop_timer(timer to_stop)
    {
        if (INVALID_PTR(to_stop, TIMER_PTR))
        {
            LOG(WARNING) << "Attempting to stop invalid timer";
            return;
        }

        to_stop->started = false;
        to_stop->paused = false;
    }

    void stop_timer(string name)
    {
        stop_timer(timer_named(name));
    }

    void pause_timer(timer to_pause)
    {
        if (INVALID_PTR(to_pause, TIMER_PTR))
        {
            LOG(WARNING) << "Attempting to pause invalid timer";
            return;
        }

        if (to_pause->started and (not to_pause->paused))
        {
            to_pause->paused = true;
            to_pause->paused_ticks = sk_get_ticks() - to_pause->start_ticks;
        }
    }

    void pause_timer(string name)
    {
        pause_timer(timer_named(name));
    }

    void resume_timer(timer to_resume)
    {
        if (INVALID_PTR(to_resume, TIMER_PTR))
        {
            LOG(WARNING) << "Attempting to resume invalid timer";
            return;
        }

        if (to_resume->paused)
        {
            to_resume->paused = false;
            to_resume->start_ticks = sk_get_ticks() - to_resume->paused_ticks;
            to_resume->paused_ticks = 0;
        }
    }

    void resume_timer(string name)
    {
        resume_timer(timer_named(name));
    }

    void reset_timer(timer tmr)
    {
        if (INVALID_PTR(tmr, TIMER_PTR))
        {
            LOG(WARNING) << "Attempting to reset invalid timer";
            return;
        }

        tmr->start_ticks = sk_get_ticks();
        tmr->paused_ticks = 0;
    }

    void reset_timer(string name)
    {
        reset_timer(timer_named(name));
    }

    unsigned int timer_ticks(timer to_get)
    {
        if (INVALID_PTR(to_get, TIMER_PTR))
        {
            LOG(WARNING) << "Attempting to get time from invalid timer";
            return 0;
        }

        if (to_get->started)
        {
            if (to_get->paused)
                return to_get->paused_ticks;
            else
                return sk_get_ticks() - to_get->start_ticks;
        }

        return 0;
    }

    unsigned int timer_ticks(string name)
    {
        return timer_ticks(timer_named(name));
    }

    bool timer_paused(timer to_get)
    {
        if (INVALID_PTR(to_get, TIMER_PTR))
        {
            LOG(WARNING) << "Attempting to check pause from invalid timer";
            return 0;
        }

        return to_get->paused;
    }

    bool timer_paused(string name)
    {
        return timer_paused(timer_named(name));
    }

    bool timer_started(timer to_get)
    {
        if (INVALID_PTR(to_get, TIMER_PTR))
        {
            LOG(WARNING) << "Attempting to check started from invalid timer";
            return 0;
        }

        return to_get->started;
    }

    bool timer_started(string name)
    {
        return timer_started(timer_named(name));
    }
}
