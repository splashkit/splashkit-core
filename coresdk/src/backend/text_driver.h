//
//  SGSDL2Text.h
//  sgsdl2
//
//  Created by James Armstrong on 11/12/2013.
//

#ifndef sgsdl2_SGSDL2Text_h
#define sgsdl2_SGSDL2Text_h

#include "backend_types.h"
namespace splashkit_lib
{
    void sk_init_text();

    void sk_finalize_text();


    sk_font_data* sk_load_font(const char * filename, int font_size);
    void sk_add_font_size(sk_font_data *font, int font_size);
    bool sk_contains_valid_font(sk_font_data* font);
    void sk_close_font(sk_font_data* font);
    int sk_text_line_skip(sk_font_data* font, int font_size);
    int sk_text_size(sk_font_data* font, int font_size, const string &text, int* w, int* h);
    void sk_set_font_style(sk_font_data* font, int font_size, int style);
    int sk_get_font_style(sk_font_data* font, int font_size);
    void _sk_draw_bitmap_text( sk_drawing_surface * surface,
                              double x, double y,
                              const char * text,
                              sk_color clr );
    void sk_draw_text(
                      sk_drawing_surface * surface,
                      sk_font_data* font,
                      int font_size,
                      double x, double y,
                      const char * text,
                      sk_color clr);
    
}
#endif /* defined(__sgsdl2__SGSDL2Text__) */
