/**
 * @header  text
 * @author  Andrew Cain
 * @brief   SplashKit Text allows for drawing text in a variety of ways to
 *          graphic windows.
 *
 * @attribute group  graphics
 * @attribute static text
 */

#ifndef text_hpp
#define text_hpp

#include "types.h"
#include "drawing_options.h"

#include <string>
using std::string;

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

    /**
     * @brief Sets the style for a `font`.
     *
     * @param fnt           The `font` to set the style of.
     * @param style         The new style for the `font`.
     *
     * @attribute class     font
     * @attribute setter    style
     * @attribute self      fnt
     */
    void set_font_style(font fnt, font_style style);

    /**
     * @brief Sets the style for a `font` by name.
     *
     * @param name          The name of the `font` to set the style of.
     * @param style         The new style for the `font`.
     *
     * @attribute suffix    name_as_string
     */
    void set_font_style(const string &name, font_style style);

    /**
     * @brief Gets the font style for given `font`.
     *
     * @param fnt           The `font` to return the style of.
     *
     * @attribute class     font
     * @attribute getter    style
     * @attribute self      fnt
     *
     * @returns Returns the current `font_style` for the `font`.
     */
    font_style get_font_style(font fnt);

    /**
     * @brief Gets the font style for given `font`.
     *
     * @param name          The name of the font to return the style of.
     *
     * @attribute suffix    name_as_string
     *
     * @returns Returns the current `font_style` for the `font`.
     */
    font_style get_font_style(const string &name);

    /**
     * @brief Loads a new font from a file.
     *
     * @param name          The name of the `font` to be loaded from file.
     * @param filename      The name of the file to load the `font` from.
     *
     * @attribute class     font
     * @attribute constructor true
     *
     * @returns Returns a new `font` object.
     */
    font load_font(const string &name, const string &filename);

    /**
     * @brief Frees a loaded font.
     *
     * @param fnt           The font to be freed.
     *
     * @attribute class     font
     * @attribute method    free
     * @attribute self                fnt
     * @attribute destructor true
     */
    void free_font(font fnt);

    /**
     * @brief Frees all loaded fonts.
     *
     * @attribute static    text
     * @attribute method    free_all
     */
    void free_all_fonts();

    /**
     * @brief Loads a new size for an already loaded `font`.
     *
     * @param fnt           The `font` to load the size for.
     * @param font_size     The desired size of the `font`.
     *
     * @attribute class     font
     * @attribute method    load_size
     * @attribute self      fnt
     */
    void font_load_size(font fnt, int font_size);

    /**
     * @brief Loads a new size for an already loaded `font`.
     *
     * @param name          The name of the `font` to load the size for.
     * @param font_size     The desired size of the `font`.
     *
     * @attribute suffix    name_as_string
     */
    void font_load_size(const string &name, int font_size);

    /**
     * @brief Checks if the supplied `font` has been loaded.
     *
     * @param fnt           The `font` to check if loaded.
     *
     * @returns Returns true if the specified `font` is loaded.
     */
    bool has_font(font fnt);

    /**
     * @brief Checks if there exists a loaded font with the supplied name.
     *
     * @param name          The name of `font` to check if loaded.
     *
     * @attribute suffix    name_as_string
     *
     * @returns Returns whether there is a loaded font with the supplied name.
     */
    bool has_font(string name);

    /**
     * @brief Checks if the supplied `font` has the supplied size.
     *
     * @param fnt           The `font` to be checked.
     * @param font_size     The size to check.
     *
     * @attribute class     font
     * @attribute method    has_size
     * @attribute self                fnt
     *
     * @returns Returns true if the supplied `font` has the supplied size.
     */
    bool font_has_size(font fnt, int font_size);

    /**
     * @brief Checks if the supplied `font` has the supplied size.
     *
     * @param name          The name of the `font` to be checked.
     * @param font_size     The size to check.
     *
     * @attribute suffix    name_as_string
     *
     * @returns Returns true if there is a font with the supplied name that has the supplied size.
     */
    bool font_has_size(const string &name, int font_size);

    /**
     * @brief Finds a loaded font that has the supplied name and returns it.
     *
     * @param name          The name of the font to find.
     *
     * @returns Returns the font that has the supplied name.
     */
    font font_named(string name);

    /**
     * @brief Draws the text string provided to the screen with the supplied color, font, size at x and y to the current window.
     *
     * @param text          The text string to be written to the window.
     * @param clr           The desired `color` of the text to be written.
     * @param fnt           The `font` to be used to draw the text.
     * @param font_size     The desired size of the font.
     * @param x             The x location to draw the text.
     * @param y             The y location to draw the text.
     * @param opts          The `drawing_options` which provide extra information for how to draw the text.
     *
     * @attribute suffix    with_options
     */
    void draw_text(const string &text, const color &clr, font fnt, int font_size, double x, double y, const drawing_options &opts);

    /**
     * @brief Draws the text string provided to the screen with the supplied color, font, size at x and y to the current window.
     *
     * @param text          The text string to be written to the window.
     * @param clr           The desired `color` of the text to be written.
     * @param fnt           The `font` to be used to draw the text.
     * @param font_size     The size of the font which will be drawn.
     * @param x             The x location to draw the text.
     * @param y             The y location to draw the text.
     */
    void draw_text(const string &text, const color &clr, font fnt, int font_size, double x, double y);

    /**
     * @brief Draws the text string provided to the screen with the supplied color, font and size at x and y to the current window.
     *
     * @param text          The text string to be written to the window.
     * @param clr           The desired `color` of the text to be written.
     * @param fnt           The name of the `font` which will be used to draw the text
     * @param font_size     The size of the font which will be drawn.
     * @param x             The x location to draw the text.
     * @param y             The y location to draw the text.
     * @param opts          The `drawing_options` which provide extra information for how to draw the text.
     *
     * @attribute suffix    with_options_font_as_string
     */
    void draw_text(const string &text, const color &clr, const string &fnt, int font_size, double x, double y, const drawing_options &opts);

    /**
     * @brief Draws the text string provided to the screen with the supplied color, font and size at x and y to the current window.
     *
     * @param text          The text string to be written to the window.
     * @param clr           The desired `color` of the text to be written.
     * @param fnt           The name of the `font` which will be used to draw the text
     * @param font_size     The size of the font which will be drawn.
     * @param x             The x location to draw the text.
     * @param y             The y location to draw the text.
     *
     * @attribute suffix    font_as_string
     */
    void draw_text(const string &text, const color &clr, const string &fnt, int font_size, double x, double y);

    /**
     * @brief Draws the text string provided to the screen with the supplied color at x and y to the current window.
     *
     * @param text          The text string to be written to the window.
     * @param clr           The desired `color` of the text to be written.
     * @param x             The x location to draw the text.
     * @param y             The y location to draw the text.
     * @param opts          The `drawing_options` which provide extra information for how to draw the text.
     *
     * @attribute suffix    no_font_no_size_with_options
     */
    void draw_text(const string &text, const color &clr, double x, double y, const drawing_options &opts);

    /**
     * @brief Draws the text string provided to the screen with the supplied color at x and y to the current window.
     *
     * @param text          The text string to be written to the window.
     * @param clr           The desired `color` of the text to be written.
     * @param x             The x location to draw the text.
     * @param y             The y location to draw the text.
     *
     * @attribute suffix    no_font_no_size
     */
    void draw_text(const string &text, const color &clr, double x, double y);

    /**
     * @brief Draws the text string provided to the window with the supplied color, font, size at x and y.
     *
     * @param wnd           The window to draw to
     * @param text          The text string to be written to the window.
     * @param clr           The desired `color` of the text to be written.
     * @param fnt           The `font` to be used to draw the text.
     * @param font_size     The desired size of the font.
     * @param x             The x location to draw the text.
     * @param y             The y location to draw the text.
     * @param opts          The `drawing_options` which provide extra information for how to draw the text.
     *
     * @attribute suffix    with_options
     * @attribute class     window
     * @attribute method    draw_text
     */
    void draw_text_on_window(window wnd, const string &text, const color &clr, font fnt, int font_size, double x, double y, const drawing_options &opts);
    
    /**
     * @brief Draws the text string provided to the window with the supplied color, font, size at x and y.
     *
     * @param wnd           The window to draw to
     * @param text          The text string to be written to the window.
     * @param clr           The desired `color` of the text to be written.
     * @param fnt           The `font` to be used to draw the text.
     * @param font_size     The size of the font which will be drawn.
     * @param x             The x location to draw the text.
     * @param y             The y location to draw the text.
     *
     * @attribute class     window
     * @attribute method    draw_text
     */
    void draw_text_on_window(window wnd, const string &text, const color &clr, font fnt, int font_size, double x, double y);
    
    /**
     * @brief Draws the text string provided to the window with the supplied color, font and size at x and y.
     *
     * @param wnd           The window to draw to
     * @param text          The text string to be written to the window.
     * @param clr           The desired `color` of the text to be written.
     * @param fnt           The name of the `font` which will be used to draw the text
     * @param font_size     The size of the font which will be drawn.
     * @param x             The x location to draw the text.
     * @param y             The y location to draw the text.
     * @param opts          The `drawing_options` which provide extra information for how to draw the text.
     *
     * @attribute suffix    with_options_font_as_string
     * @attribute class     window
     * @attribute method    draw_text
     */
    void draw_text_on_window(window wnd, const string &text, const color &clr, const string &fnt, int font_size, double x, double y, const drawing_options &opts);
    
    /**
     * @brief Draws the text string provided to the screen with the supplied color, font and size at x and y to the current window.
     *
     * @param wnd           The window to draw to
     * @param text          The text string to be written to the window.
     * @param clr           The desired `color` of the text to be written.
     * @param fnt           The name of the `font` which will be used to draw the text
     * @param font_size     The size of the font which will be drawn.
     * @param x             The x location to draw the text.
     * @param y             The y location to draw the text.
     *
     * @attribute suffix    font_as_string
     * @attribute class     window
     * @attribute method    draw_text
     */
    void draw_text_on_window(window wnd, const string &text, const color &clr, const string &fnt, int font_size, double x, double y);
    
    /**
     * @brief Draws the text string provided to the window with the supplied color at x and y.
     *
     * @param wnd           The window to draw to
     * @param text          The text string to be written to the window.
     * @param clr           The desired `color` of the text to be written.
     * @param x             The x location to draw the text.
     * @param y             The y location to draw the text.
     * @param opts          The `drawing_options` which provide extra information for how to draw the text.
     *
     * @attribute suffix    no_font_no_size_with_options
     * @attribute class     window
     * @attribute method    draw_text
     */
    void draw_text_on_window(window wnd, const string &text, const color &clr, double x, double y, const drawing_options &opts);
    
    /**
     * @brief Draws the text string provided to the screen with the supplied color at x and y to the current window.
     *
     * @param wnd           The window to draw to
     * @param text          The text string to be written to the window.
     * @param clr           The desired `color` of the text to be written.
     * @param x             The x location to draw the text.
     * @param y             The y location to draw the text.
     *
     * @attribute suffix    no_font_no_size
     * @attribute class     window
     * @attribute method    draw_text
     */
    void draw_text_on_window(window wnd, const string &text, const color &clr, double x, double y);
    
    /**
     * @brief Draws the text string provided to the bitmap with the supplied color, font, size at x and y.
     *
     * @param bmp           The bitmap to draw to
     * @param text          The text string to be written to the bitmap.
     * @param clr           The desired `color` of the text to be written.
     * @param fnt           The `font` to be used to draw the text.
     * @param font_size     The desired size of the font.
     * @param x             The x location to draw the text.
     * @param y             The y location to draw the text.
     * @param opts          The `drawing_options` which provide extra information for how to draw the text.
     *
     * @attribute suffix    with_options
     * @attribute class     bitmap
     * @attribute method    draw_text
     */
    void draw_text_on_bitmap(bitmap bmp, const string &text, const color &clr, font fnt, int font_size, double x, double y, const drawing_options &opts);
    
    /**
     * @brief Draws the text string provided to the bitmap with the supplied color, font, size at x and y.
     *
     * @param bmp           The bitmap to draw to
     * @param text          The text string to be written to the bitmap.
     * @param clr           The desired `color` of the text to be written.
     * @param fnt           The `font` to be used to draw the text.
     * @param font_size     The size of the font which will be drawn.
     * @param x             The x location to draw the text.
     * @param y             The y location to draw the text.
     *
     * @attribute class     bitmap
     * @attribute method    draw_text
     */
    void draw_text_on_bitmap(bitmap bmp, const string &text, const color &clr, font fnt, int font_size, double x, double y);
    
    /**
     * @brief Draws the text string provided to the bitmap with the supplied color, font and size at x and y.
     *
     * @param bmp           The bitmap to draw to
     * @param text          The text string to be written to the bitmap.
     * @param clr           The desired `color` of the text to be written.
     * @param fnt           The name of the `font` which will be used to draw the text
     * @param font_size     The size of the font which will be drawn.
     * @param x             The x location to draw the text.
     * @param y             The y location to draw the text.
     * @param opts          The `drawing_options` which provide extra information for how to draw the text.
     *
     * @attribute suffix    with_options_font_as_string
     * @attribute class     bitmap
     * @attribute method    draw_text
     */
    void draw_text_on_bitmap(bitmap bmp, const string &text, const color &clr, const string &fnt, int font_size, double x, double y, const drawing_options &opts);
    
    /**
     * @brief Draws the text string provided to the screen with the supplied color, font and size at x and y to the current bitmap.
     *
     * @param bmp           The bitmap to draw to
     * @param text          The text string to be written to the bitmap.
     * @param clr           The desired `color` of the text to be written.
     * @param fnt           The name of the `font` which will be used to draw the text
     * @param font_size     The size of the font which will be drawn.
     * @param x             The x location to draw the text.
     * @param y             The y location to draw the text.
     *
     * @attribute suffix    font_as_string
     * @attribute class     bitmap
     * @attribute method    draw_text
     */
    void draw_text_on_bitmap(bitmap bmp, const string &text, const color &clr, const string &fnt, int font_size, double x, double y);
    
    /**
     * @brief Draws the text string provided to the bitmap with the supplied color at x and y.
     *
     * @param bmp           The bitmap to draw to
     * @param text          The text string to be written to the bitmap.
     * @param clr           The desired `color` of the text to be written.
     * @param x             The x location to draw the text.
     * @param y             The y location to draw the text.
     * @param opts          The `drawing_options` which provide extra information for how to draw the text.
     *
     * @attribute suffix    no_font_no_size_with_options
     * @attribute class     bitmap
     * @attribute method    draw_text
     */
    void draw_text_on_bitmap(bitmap bmp, const string &text, const color &clr, double x, double y, const drawing_options &opts);
    
    /**
     * @brief Draws the text string provided to the screen with the supplied color at x and y.
     *
     * @param bmp           The bitmap to draw to
     * @param text          The text string to be written to the bitmap.
     * @param clr           The desired `color` of the text to be written.
     * @param x             The x location to draw the text.
     * @param y             The y location to draw the text.
     *
     * @attribute suffix    no_font_no_size
     * @attribute class     bitmap
     * @attribute method    draw_text
     */
    void draw_text_on_bitmap(bitmap bmp, const string &text, const color &clr, double x, double y);

    /**
     * @brief Returns the width of the supplied text string.
     *
     * @param text          The text string to check the length of.
     * @param fnt           The font used for the text.
     * @param font_size     The size of the font used for the text.
     *
     * @attribute static    text
     * @attribute method    width
     *
     * @returns Returns the width of the text as an integer.
     */
    int text_width(const string &text, font fnt, int font_size);

    /**
     * @brief Returns the width of the supplied text string.
     *
     * @param text          The text string to check the length of.
     * @param fnt           The font used for the text.
     * @param font_size     The size of the font used for the text.
     *
     * @attribute static    text
     * @attribute method    width
     * @attribute suffix    font_named
     *
     * @returns Returns the width of the text as an integer.
     */
    int text_width(const string &text, const string& fnt, int font_size);

    /**
     * @brief Returns the height of the supplied text string.
     *
     * @param text          The text string to check the length of.
     * @param fnt           The font used for the text.
     * @param font_size     The size of the font used for the text.
     *
     * @attribute static    text
     * @attribute method    height
     *
     * @returns Returns the height of the text as an integer.
     */
    int text_height(const string &text, font fnt, int font_size);

    /**
     * @brief Returns the height of the supplied text string.
     *
     * @param text          The text string to check the length of.
     * @param fnt           The font used for the text.
     * @param font_size     The size of the font used for the text.
     *
     * @attribute static    text
     * @attribute method    height
     * @attribute suffix    font_named
     *
     * @returns Returns the height of the text as an integer.
     */
    int text_height(const string &text, const string& fnt, int font_size);
}

#endif /* text_hpp */
