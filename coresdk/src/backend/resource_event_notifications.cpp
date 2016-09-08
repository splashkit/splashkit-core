//
//  resource_event_notifications.cpp
//  splashkit
//
//  Created by Andrew Cain on 24/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "resource_event_notifications.h"
#include "utility_functions.h"

#include <vector>
using namespace std;
namespace splashkit_lib
{
    static vector<free_notifier *> _free_event_handlers;

    void register_event_handler(free_notifier *handler)
    {
        _free_event_handlers.push_back(handler);
    }

    void deregister_event_handler(free_notifier *handler)
    {
        if (not erase_from_vector(_free_event_handlers, handler))
        {
            LOG(WARNING) << "Not able to deregister handler -- handler not registered.";
        }
    }

    void notify_handlers_of_free(void *ptr)
    {
        for (free_notifier *to_call: _free_event_handlers)
        {
            to_call(ptr);
        }
    }
}