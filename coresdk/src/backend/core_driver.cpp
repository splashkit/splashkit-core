//
//  CoreDriver.cpp
//
//  Created by Andrew Cain on 19/11/2013.
//  Copyright (c) 2013 Andrew Cain. All rights reserved.
//

#ifdef __linux__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include "core_driver.h"
#include "text_driver.h"
#include "logging_driver.h"
#include "network_driver.h"

#include <stdlib.h>

#include "audio_driver.h"
#include "web_driver.h"

#include "easylogging++.h"

namespace splashkit_lib
{
    // Storage for the system data
    sk_system_data _sk_system_data;


    void sk_setup_displays();
    void _init_key_maps();

    void internal_sk_init()
    {
        static bool done_init = false;
        if ( done_init ) return;
        done_init = true;

        el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "%datetime %level: %msg");

        //    cout << "pre init" << endl;
        if ( -1 == SDL_Init( SDL_INIT_EVERYTHING ) )
        {
            // fatal error so...
            // no other functions can now be called

            //TODO: Report error : set_error_state(SDL_GetError());
            return;
        }
        //    cout << "post init" << endl;

        // SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");

        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 0);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 0);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE,    8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,  8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,   8);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,  8);

        // SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL,  1);

        sk_setup_displays();
        sk_init_audio();

        sk_init_text();

        sk_init_web();

        sk_init_logging();

        sk_network_init();

        _init_key_maps();

        open_audio();
    }

    void sk_setup_display(int idx, sk_display &disp)
    {
        SDL_DisplayMode mode;
        SDL_Rect rect;

        disp.id = DISPLAY_PTR;

        disp.name = SDL_GetDisplayName(idx);

        SDL_GetCurrentDisplayMode(idx, &mode);
        disp.width = mode.w;
        disp.height = mode.h;
        disp.format = mode.format;
        disp.refresh_rate = mode.refresh_rate;

        SDL_GetDisplayBounds(idx, &rect);
        disp.x = rect.x;
        disp.y = rect.y;

        disp.num_modes = 0;
        disp.modes = NULL;
        int max_modes = SDL_GetNumDisplayModes(idx);
        if ( max_modes < 1 ) return;
        bool add;

        for (int i = 0; i < max_modes; i++)
        {
            SDL_GetDisplayMode(idx, i, &mode);
            add = true;

            for ( unsigned int m = 0; m < disp.num_modes; m++)
            {
                if ( disp.modes[m].width == mode.w && disp.modes[m].height == mode.h )
                {
                    add = false;
                    break;
                }
            }

            if ( add )
            {
                disp.num_modes++;
                sk_mode * new_modes = static_cast<sk_mode *>(realloc(disp.modes, disp.num_modes * sizeof(sk_mode)));
                if ( new_modes == NULL )
                {
                    //                set_error_state("Out of memory loading video modes.");
                    free(disp.modes);
                    disp.modes = NULL;
                    disp.num_modes = 0;
                    return; //TODO: add error!
                }
                disp.modes = new_modes;
                disp.modes[disp.num_modes - 1].width = mode.w;
                disp.modes[disp.num_modes - 1].height = mode.h;
                disp.modes[disp.num_modes - 1].format = mode.format;
                disp.modes[disp.num_modes - 1].refresh_rate = mode.refresh_rate;
            }
        }
    }

    void sk_setup_displays()
    {
        int num_displays = SDL_GetNumVideoDisplays();
        if (num_displays <= 0) {
            exit(-1);
        }

        _sk_system_data.num_displays = static_cast<unsigned int>(num_displays);

        _sk_system_data.displays = static_cast<sk_display *>(malloc(sizeof(sk_display) * _sk_system_data.num_displays));
        
        for (unsigned int i = 0; i < _sk_system_data.num_displays; i++)
        {
            sk_setup_display(static_cast<int>(i), _sk_system_data.displays[i]);
        }
    }
    
    sk_system_data * sk_read_system_data()
    {
        internal_sk_init();
        return &_sk_system_data;
    }
    
    void sk_finalise()
    {
        //    sk_finalise_graphics();
        
        for (unsigned int i = 0; i < _sk_system_data.num_displays; i++)
        {
            free(_sk_system_data.displays[i].modes);
        }
        
        free(_sk_system_data.displays);
        
        //    sk_finalize_text();
        
        //    sk_finalise_web();
        
        SDL_Quit();
    }
}
