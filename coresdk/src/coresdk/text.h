/**
 * @header Text
 * @author Andrew Cain
 * @brief SplashKit Text allows for drawing text in a variety of ways to graphic windows.
 *
 * @attribute static text
 */

#ifndef text_hpp
#define text_hpp

#include "types.h"
#include "drawing_options.h"

#include <string>
using namespace std;
namespace splashkit_lib
{
    /// Loads a font from file with the specified side. Fonts must be freed using
    /// the FreeFont routine once finished with. Once the font is loaded you
    /// can set its style using SetFontStyle. Fonts are then used to draw and
    /// measure text in your programs.
    ///
    /// @lib
    /// @sn loadFontFile:%s size:%s
    ///
    /// @class Font
    /// @constructor
    /// @csn initWithFontName:%s andSize:%s

    void set_font_style(font fnt, font_style style);

    void set_font_style(const string &name, font_style style);

    font_style get_font_style(font fnt);

    font_style get_font_style(const string &name);

    font load_font(const string &name, const string &filename);

    void free_font(font fnt);

    void free_all_fonts();

    void font_load_size(font fnt, int font_size);

    void font_load_size(const string &name, int font_size);

    bool has_font(font fnt);

    bool has_font(string name);

    bool font_has_size(font fnt, int font_size);

    bool font_has_size(const string &name, int font_size);

    font font_named(string name);

    void draw_text(const string &text, const color &clr, font fnt, int font_size, float x, float y, const drawing_options &opts);

    void draw_text(const string &text, const color &clr, font fnt, int font_size, float x, float y);

    void draw_text(const string &text, const color &clr, const string &fnt, int font_size, float x, float y, const drawing_options &opts);

    /**
     * Draws the text provided in `text` to the screen with color `clr`, font `fnt`, size `font_size`
     *       at `x` and `y` to the current focused window.
     * @param text      The text which will be written to the window
     * @param clr       the `color` of the text to be written
     * @param fnt       the `font` which will be used to draw the text
     * @param font_size the size of the font which will be drawn.
     * @param x         the `x` location representing where the text will be drawn.
     * @param y         the `y` location representing where the text will be drawn.
     *
     */
    void draw_text(const string &text, const color &clr, const string &fnt, int font_size, float x, float y);

    void draw_text(const string &text, const color &clr, const string &fnt, float x, float y, const drawing_options &opts);

    void draw_text(const string &text, const color &clr, const string &fnt, float x, float y);

    void draw_text(const string &text, const color &clr, float x, float y, const drawing_options &opts);
    
    void draw_text(const string &text, const color &clr, float x, float y);
    
    int text_length(const string &text, font fnt, int font_size);
    
    int text_length(const string &text, string fnt, int font_size);
    
}

#endif /* text_hpp */
