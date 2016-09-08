//
//  resource_event_notifications.hpp
//  splashkit
//
//  Created by Andrew Cain on 24/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef resource_event_notifications_hpp
#define resource_event_notifications_hpp

#include "types.h"
namespace splashkit_lib
{
    void register_event_handler(free_notifier *handler);
    void deregister_event_handler(free_notifier *handler);
    void notify_handlers_of_free(void *ptr);
}
#endif /* resource_event_notifications_hpp */
