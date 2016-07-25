//
//  SGSDL2Text.h
//  sgsdl2
//
//  Created by James Armstrong on 11/12/2013.
//

#ifndef sgsdl2_SGSDL2Text_h
#define sgsdl2_SGSDL2Text_h

#include "backend_types.h"

void sk_init_text();

void sk_finalize_text();


sk_font_data sk_load_font(const char * filename, int font_size);
void sk_close_font(sk_font_data* font);
int sk_text_line_skip(sk_font_data* font);
int sk_text_size(sk_font_data* font, char* text, int* w, int* h);
void sk_set_font_style(sk_font_data* font,int style);
int sk_get_font_style(sk_font_data* font);
void _sk_draw_bitmap_text( sk_drawing_surface * surface,
                          float x, float y,
                          const char * text,
                          sk_color clr );
void sk_draw_text(
                  sk_drawing_surface * surface,
                  sk_font_data* font,
                  float x, float y,
                  const char * text,
                  sk_color clr);


#endif /* defined(__sgsdl2__SGSDL2Text__) */
