//
//  SGSDL2Input.h
//  sgsdl2
//
//  Created by Andrew Cain on 7/12/2013.
//  Copyright (c) 2013 Andrew Cain. All rights reserved.
//

#ifndef sgsdl2_SGSDL2Input_h
#define sgsdl2_SGSDL2Input_h

#include "backend_types.h"
#include "keyboard_input.h"
namespace splashkit_lib
{
    typedef struct _window_data *window;

    extern bool _sk_quit;

    typedef void (sk_empty_procedure)( void );
    typedef void (sk_intp_proc)( int ms );
    typedef void (sk_int_intp_proc)( int x, int y );
    typedef void (sk_charp_proc)(char* text);
    typedef void (sk_window_xy_proc)(pointer window, int x, int y);
    typedef void (sk_window_proc)(pointer window);
    typedef void (sk_charp_int_int_proc)(char * text, int x, int y);

    typedef void (sk_key_callback)(key_code code);

    struct sk_input_callbacks
    {
        sk_empty_procedure * do_quit;

        sk_key_callback * handle_key_down;
        sk_key_callback * handle_key_up;

        sk_intp_proc * handle_mouse_up;
        sk_intp_proc * handle_mouse_down;
        sk_int_intp_proc * handle_mouse_wheel;

        sk_charp_proc * handle_input_text;
        sk_charp_int_int_proc * handle_editing_text;

        sk_window_xy_proc * handle_window_resize;
        sk_window_xy_proc *handle_window_move;
        sk_window_proc *handle_window_gain_focus;
    };

    extern sk_input_callbacks _input_callbacks;

    void sk_process_events();
    int sk_window_close_requested(sk_drawing_surface* surf);
    int sk_key_pressed(int key_code);
    void sk_start_unicode_text_input(int x, int y, int w, int h);
    void sk_warp_mouse(sk_drawing_surface *surface, int x, int y);
    pointer sk_focus_window();
    void sk_window_position(sk_drawing_surface *surface, int *x, int *y);
    sk_window_data sk_get_window_event_data(sk_drawing_surface *surface);
    void sk_move_window(sk_drawing_surface *surface, int x, int y);

    void sk_start_reading_text(window wind, double x, double y, double width, double height, string initial_text);

    void sk_mouse_position(double &x, double &y);
    void sk_mouse_movement(double &x, double &y);
    
    bool sk_mouse_button_down(uint32_t button);
    
    bool sk_show_mouse(int value);
    
    string sk_key_name(key_code key);
}
#endif /* defined(__sgsdl2__SGSDL2Input__) */
