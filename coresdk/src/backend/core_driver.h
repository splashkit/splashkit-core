//
//  CoreDriver.h
//
//  Created by Andrew Cain on 19/11/2013.
//  Copyright (c) 2013 Andrew Cain. All rights reserved.
//

#ifndef sk_CoreDriver_h
#define sk_CoreDriver_h

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

typedef struct sk_display
{
    const char *    name;
    int             x, y;
    int             width, height, refresh_rate;
    unsigned int    format;
    unsigned int    num_modes;
    sk_mode *       modes;

    // private data used by the backend
    void * _data;
} sk_display;


typedef struct sk_system_data
{
    unsigned int    num_displays;
    sk_display    * displays;
    sk_audiospec    audio_specs;
    
} sk_system_data;

//
// Storage for the system data
//
extern sk_system_data _sk_system_data;

void internal_sk_init();

#endif /* defined(sk__CoreDriver) */
