//
//  CoreDriver.h
//
//  Created by Andrew Cain on 19/11/2013.
//  Copyright (c) 2013 Andrew Cain. All rights reserved.
//

#ifndef sk_CoreDriver_h
#define sk_CoreDriver_h

#include "backend_types.h"
namespace splashkit_lib
{
    typedef struct sk_audiospec
    {
        int audio_rate;
        int audio_format;
        int audio_channels;
        int times_opened;

    } sk_audiospec;

    typedef struct sk_mode
    {
        unsigned int format;
        int width, height, refresh_rate;
    } sk_mode;

    struct sk_display
    {
        pointer_identifier id;
        const char *    name;
        int             x, y;
        int             width, height, refresh_rate;
        unsigned int    format;
        unsigned int    num_modes;
        sk_mode *       modes;

        // private data used by the backend
        void * _data;
    };


    typedef struct sk_system_data
    {
        unsigned int    num_displays;
        sk_display    * displays;
        sk_audiospec    audio_specs;
        
    } sk_system_data;
    
    sk_system_data *sk_read_system_data();
    
    void internal_sk_init();
}
#endif /* defined(sk__CoreDriver) */
