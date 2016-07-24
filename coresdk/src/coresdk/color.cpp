//
//  color.cpp
//  splashkit
//
//  _created by _andrew _cain on 24/07/2016.
//  _copyright © 2016 _andrew _cain. _all rights reserved.
//

#include "color.h"
#include "random.h"
#include <cmath>
#include <sstream>
#include <iostream>
#include <iomanip>

template< typename _t >
std::string int_to_hex( _t i )
{
    std::stringstream stream;
    stream << "0x"
    << std::setfill ('0') << std::setw(sizeof(_t)*2)
    << std::hex << i;
    return stream.str();
}

color random_color()
{
    return rgba_color(rnd(), rnd(), rnd(), rnd());
}

color random_rgb_color(byte alpha)
{
    return rgba_color(rnd(), rnd(), rnd(), alpha / 255.0f);
}

color rgba_color(byte red, byte green, byte blue, byte alpha)
{
    return rgba_color(red / 255.0f, green / 255.0f, blue / 255.0f, alpha / 255.0f);
}

/// _gets a color given its color components. Each of the components has
/// a value between 0 and 1
///
color rgba_color(float red, float green, float blue, float alpha)
{
    color result;
    result.r = fabs(red) > 1.0f ? 1.0f: fabs(red);
    result.g = fabs(green) > 1.0f ? 1.0f: fabs(green);
    result.b = fabs(blue) > 1.0f ? 1.0f: fabs(blue);
    result.a = fabs(alpha) > 1.0f ? 1.0f: fabs(alpha);

    return result;
}

/// _gets a color given its _r_g_b components. Each of the components has
/// a value between 0 and 1.0f.
///
color rgb_color(byte red, byte green, byte blue)
{
    return rgba_color(red / 255.0f, green / 255.0f, blue / 255.0f, 1.0f);
}

/// _gets a color given its _r_g_b components. Each of the components has
/// a value between 0 and 1.
///
color rgb_color(float red, float green, float blue)
{
    return rgba_color(red, green, blue, 1.0f);
}

/// returns color to string.
///
string color_to_string(color c)
{
    string r, g, b, a;
    r =  static_cast<byte>(c.r * 1.0f);
    g =  static_cast<byte>(c.g * 1.0f);
    b =  static_cast<byte>(c.b * 1.0f);
    a =  static_cast<byte>(c.a * 1.0f);

    return string("#") + int_to_hex(r) + int_to_hex(g) + int_to_hex(b) + int_to_hex(a);
}


/// _returs a color from a combination of hue, saturation, and brightness.
///
/// @param hue, saturation, brightness: _values between 0 and 1
/// @returns _the matching color
///
color hsb_color(float hue, float saturation, float brightness)
{
    float domain_offset;
    float red, green, blue;

    if (brightness == 0)
        return COLOR_BLACK;

    if (saturation == 0)
        return rgb_color(brightness, brightness, brightness);

    if (hue < 1.0 / 6) // red domain... green ascends
    {
        domain_offset = hue;
        red   = brightness;
        blue  = brightness * (1.0 - saturation);
        green = blue + (brightness - blue) * domain_offset * 6;
    }
    else if (hue < 2.0 / 6) // yellow domain; red descends
    {
        domain_offset = hue - 1.0 / 6;
        green = brightness;
        blue  = brightness * (1.0 - saturation);
        red   = green - (brightness - blue) * domain_offset * 6;
    }
    else if (hue < 3.0 / 6) // green domain; blue ascends
    {
        domain_offset = hue - 2.0 / 6;
        green = brightness;
        red   = brightness * (1.0 - saturation);
        blue  = red + (brightness - red) * domain_offset * 6;
    }
    else if (hue < 4.0 / 6) // cyan domain; green descends
    {
        domain_offset = hue - 3.0 / 6;
        blue  = brightness;
        red   = brightness * (1.0 - saturation);
        green = blue - (brightness - red) * domain_offset * 6;
    }
    else if (hue < 5.0 / 6) // blue domain; red ascends
    {
        domain_offset = hue - 4.0 / 6;
        blue  = brightness;
        green = brightness * (1.0 - saturation);
        red   = green + (brightness - green) * domain_offset * 6;
    }
    else // magenta domain; blue descends
    {
        domain_offset = hue - 5.0 / 6;
        red   = brightness;
        green = brightness * (1.0 - saturation);
        blue  = red - (brightness - green) * domain_offset * 6;
    }

    return rgb_color(red, green, blue);
}

color color_grey()
{
    return rgba_color(0.5f, 0.5f, 0.5f, 1);
}

color color_light_grey()
{
    return rgba_color(0.784313f, 0.784313f, 0.784313f, 1.0f);
}

color color_transparent()
{
    return rgba_color(1.0f, 1.0f, 1.0f, 0);
}

color color_alice_blue()
{
    return rgba_color(240, 248, 1.0f, 1.0f);
}

color color_antique_white()
{
    return rgba_color(250, 235, 215, 1.0f);
}

color color_aqua()
{
    return rgba_color(0, 1.0f, 1.0f, 1.0f);
}

color color_aquamarine()
{
    return rgba_color(127, 1.0f, 212, 1.0f);
}

color color_azure()
{
    return rgba_color(240, 1.0f, 1.0f, 1.0f);
}

color color_beige()
{
    return rgba_color(245, 245, 220, 1.0f);
}

color color_bisque()
{
    return rgba_color(1.0f, 228, 196, 1.0f);
}

color color_black()
{
    return rgba_color(0, 0, 0, 1.0f);
}

color color_blanched_almond()
{
    return rgba_color(1.0f, 235, 205, 1.0f);
}

color color_blue()
{
    return rgba_color(0, 0, 1.0f, 1.0f);
}

color color_blue_violet()
{
    return rgba_color(138, 43, 226, 1.0f);
}

color color_brown()
{
    return rgba_color(165, 42, 42, 1.0f);
}

color color_burly_wood()
{
    return rgba_color(222, 184, 135, 1.0f);
}

color color_cadet_blue()
{
    return rgba_color(95, 158, 160, 1.0f);
}

color color_chartreuse()
{
    return rgba_color(127, 1.0f, 0, 1.0f);
}

color color_chocolate()
{
    return rgba_color(210, 105, 30, 1.0f);
}

color color_coral()
{
    return rgba_color(1.0f, 127, 80, 1.0f);
}

color color_cornflower_blue()
{
    return rgba_color(100, 149, 237, 1.0f);
}

color color_cornsilk()
{
    return rgba_color(1.0f, 248, 220, 1.0f);
}

color color_crimson()
{
    return rgba_color(220, 20, 60, 1.0f);
}

color color_cyan()
{
    return rgba_color(0, 1.0f, 1.0f, 1.0f);
}

color color_dark_blue()
{
    return rgba_color(0, 0, 139, 1.0f);
}

color color_dark_cyan()
{
    return rgba_color(0, 139, 139, 1.0f);
}

color color_dark_goldenrod()
{
    return rgba_color(184, 134, 11, 1.0f);
}

color color_dark_gray()
{
    return rgba_color(169, 169, 169, 1.0f);
}

color color_dark_green()
{
    return rgba_color(0, 100, 0, 1.0f);
}

color color_dark_khaki()
{
    return rgba_color(189, 183, 107, 1.0f);
}

color color_dark_magenta()
{
    return rgba_color(139, 0, 139, 1.0f);
}

color color_dark_olive_green()
{
    return rgba_color(85, 107, 47, 1.0f);
}

color color_dark_orange()
{
    return rgba_color(1.0f, 140, 0, 1.0f);
}

color color_dark_orchid()
{
    return rgba_color(153, 50, 204, 1.0f);
}

color color_dark_red()
{
    return rgba_color(139, 0, 0, 1.0f);
}

color color_dark_salmon()
{
    return rgba_color(233, 150, 122, 1.0f);
}

color color_dark_sea_green()
{
    return rgba_color(143, 188, 139, 1.0f);
}

color color_dark_slate_blue()
{
    return rgba_color(72, 61, 139, 1.0f);
}

color color_dark_slate_gray()
{
    return rgba_color(47, 79, 79, 1.0f);
}

color color_dark_turquoise()
{
    return rgba_color(0, 206, 209, 1.0f);
}

color color_dark_violet()
{
    return rgba_color(148, 0, 211, 1.0f);
}

color color_deep_pink()
{
    return rgba_color(1.0f, 20, 147, 1.0f);
}

color color_deep_sky_blue()
{
    return rgba_color(0, 191, 1.0f, 1.0f);
}

color color_dim_gray()
{
    return rgba_color(105, 105, 105, 1.0f);
}

color color_dodger_blue()
{
    return rgba_color(30, 144, 1.0f, 1.0f);
}

color color_firebrick()
{
    return rgba_color(178, 34, 34, 1.0f);
}

color color_floral_white()
{
    return rgba_color(1.0f, 250, 240, 1.0f);
}

color color_forest_green()
{
    return rgba_color(34, 139, 34, 1.0f);
}

color color_fuchsia()
{
    return rgba_color(1.0f, 0, 1.0f, 1.0f);
}

color color_gainsboro()
{
    return rgba_color(220, 220, 220, 1.0f);
}

color color_ghost_white()
{
    return rgba_color(248, 248, 1.0f, 1.0f);
}

color color_gold()
{
    return rgba_color(1.0f, 215, 0, 1.0f);
}

color color_goldenrod()
{
    return rgba_color(218, 165, 32, 1.0f);
}

color color_gray()
{
    return rgba_color(0.5f, 0.5f, 0.5f, 1.0f);
}

color color_green()
{
    return rgba_color(0, 0.5f, 0, 1.0f);
}

color color_bright_green()
{
    return rgba_color(0, 1.0f, 0, 1.0f);
}

color color_green_yellow()
{
    return rgba_color(173, 1.0f, 47, 1.0f);
}

color color_honeydew()
{
    return rgba_color(240, 1.0f, 240, 1.0f);
}

color color_hot_pink()
{
    return rgba_color(1.0f, 105, 180, 1.0f);
}

color color_indian_red()
{
    return rgba_color(205, 92, 92, 1.0f);
}

color color_indigo()
{
    return rgba_color(75, 0, 130, 1.0f);
}

color color_ivory()
{
    return rgba_color(1.0f, 1.0f, 240, 1.0f);
}

color color_khaki()
{
    return rgba_color(240, 230, 140, 1.0f);
}

color color_lavender()
{
    return rgba_color(230, 230, 250, 1.0f);
}

color color_lavender_blush()
{
    return rgba_color(1.0f, 240, 245, 1.0f);
}

color color_lawn_green()
{
    return rgba_color(124, 252, 0, 1.0f);
}

color color_lemon_chiffon()
{
    return rgba_color(1.0f, 250, 205, 1.0f);
}

color color_light_blue()
{
    return rgba_color(173, 216, 230, 1.0f);
}

color color_light_coral()
{
    return rgba_color(240, 0.5f, 0.5f, 1.0f);
}

color color_light_cyan()
{
    return rgba_color(224, 1.0f, 1.0f, 1.0f);
}

color color_light_goldenrod_yellow()
{
    return rgba_color(250, 250, 210, 1.0f);
}

color color_light_green()
{
    return rgba_color(144, 238, 144, 1.0f);
}

color color_light_gray()
{
    return rgba_color(211, 211, 211, 1.0f);
}

color color_light_pink()
{
    return rgba_color(1.0f, 182, 193, 1.0f);
}

color color_light_salmon()
{
    return rgba_color(1.0f, 160, 122, 1.0f);
}

color color_light_sea_green()
{
    return rgba_color(32, 178, 170, 1.0f);
}

color color_light_sky_blue()
{
    return rgba_color(135, 206, 250, 1.0f);
}

color color_light_slate_gray()
{
    return rgba_color(119, 136, 153, 1.0f);
}

color color_light_steel_blue()
{
    return rgba_color(176, 196, 222, 1.0f);
}

color color_light_yellow()
{
    return rgba_color(1.0f, 1.0f, 224, 1.0f);
}

color color_lime()
{
    return rgba_color(0, 1.0f, 0, 1.0f);
}

color color_lime_green()
{
    return rgba_color(50, 205, 50, 1.0f);
}

color color_linen()
{
    return rgba_color(250, 240, 230, 1.0f);
}

color color_magenta()
{
    return rgba_color(1.0f, 0, 1.0f, 1.0f);
}

color color_maroon()
{
    return rgba_color(0.5f, 0, 0, 1.0f);
}

color color_medium_aquamarine()
{
    return rgba_color(102, 205, 170, 1.0f);
}

color color_medium_blue()
{
    return rgba_color(0, 0, 205, 1.0f);
}

color color_medium_orchid()
{
    return rgba_color(186, 85, 211, 1.0f);
}

color color_medium_purple()
{
    return rgba_color(147, 112, 219, 1.0f);
}

color color_medium_sea_green()
{
    return rgba_color(60, 179, 113, 1.0f);
}

color color_medium_slate_blue()
{
    return rgba_color(123, 104, 238, 1.0f);
}

color color_medium_spring_green()
{
    return rgba_color(0, 250, 154, 1.0f);
}

color color_medium_turquoise()
{
    return rgba_color(72, 209, 204, 1.0f);
}

color color_medium_violet_red()
{
    return rgba_color(199, 21, 133, 1.0f);
}

color color_midnight_blue()
{
    return rgba_color(25, 25, 112, 1.0f);
}

color color_mint_cream()
{
    return rgba_color(245, 1.0f, 250, 1.0f);
}

color color_misty_rose()
{
    return rgba_color(1.0f, 228, 225, 1.0f);
}

color color_moccasin()
{
    return rgba_color(1.0f, 228, 181, 1.0f);
}

color color_Navajo_white()
{
    return rgba_color(1.0f, 222, 173, 1.0f);
}

color color_Navy()
{
    return rgba_color(0, 0, 0.5f, 1.0f);
}

color color_old_lace()
{
    return rgba_color(253, 245, 230, 1.0f);
}

color color_olive()
{
    return rgba_color(0.5f, 0.5f, 0, 1.0f);
}

color color_olive_drab()
{
    return rgba_color(107, 142, 35, 1.0f);
}

color color_orange()
{
    return rgba_color(1.0f, 165, 0, 1.0f);
}

color color_orange_red()
{
    return rgba_color(1.0f, 69, 0, 1.0f);
}

color color_orchid()
{
    return rgba_color(218, 112, 214, 1.0f);
}

color color_pale_goldenrod()
{
    return rgba_color(238, 232, 170, 1.0f);
}

color color_pale_green()
{
    return rgba_color(152, 251, 152, 1.0f);
}

color color_pale_turquoise()
{
    return rgba_color(175, 238, 238, 1.0f);
}

color color_pale_violet_red()
{
    return rgba_color(219, 112, 147, 1.0f);
}

color color_papaya_whip()
{
    return rgba_color(1.0f, 239, 213, 1.0f);
}

color color_peach_puff()
{
    return rgba_color(1.0f, 218, 185, 1.0f);
}

color color_peru()
{
    return rgba_color(205, 133, 63, 1.0f);
}

color color_pink()
{
    return rgba_color(1.0f, 192, 203, 1.0f);
}

color color_plum()
{
    return rgba_color(221, 160, 221, 1.0f);
}

color color_powder_blue()
{
    return rgba_color(176, 224, 230, 1.0f);
}

color color_purple()
{
    return rgba_color(0.5f, 0, 0.5f, 1.0f);
}

color color_red()
{
    return rgba_color(1.0f, 0, 0, 1.0f);
}

color color_rosy_brown()
{
    return rgba_color(188, 143, 143, 1.0f);
}

color color_royal_blue()
{
    return rgba_color(65, 105, 225, 1.0f);
}

color color_saddle_brown()
{
    return rgba_color(139, 69, 19, 1.0f);
}

color color_salmon()
{
    return rgba_color(250, 0.5f, 114, 1.0f);
}

color color_sandy_brown()
{
    return rgba_color(244, 164, 96, 1.0f);
}

color color_sea_green()
{
    return rgba_color(46, 139, 87, 1.0f);
}

color color_sea_shell()
{
    return rgba_color(1.0f, 245, 238, 1.0f);
}

color color_sienna()
{
    return rgba_color(160, 82, 45, 1.0f);
}

color color_silver()
{
    return rgba_color(192, 192, 192, 1.0f);
}

color color_sky_blue()
{
    return rgba_color(135, 206, 235, 1.0f);
}

color color_slate_blue()
{
    return rgba_color(106, 90, 205, 1.0f);
}

color color_slate_gray()
{
    return rgba_color(112, 0.5f, 144, 1.0f);
}

color color_snow()
{
    return rgba_color(1.0f, 250, 250, 1.0f);
}

color color_spring_green()
{
    return rgba_color(0, 1.0f, 127, 1.0f);
}

color color_steel_blue()
{
    return rgba_color(70, 130, 180, 1.0f);
}

color color_tan()
{
    return rgba_color(210, 180, 140, 1.0f);
}

color color_teal()
{
    return rgba_color(0, 0.5f, 0.5f, 1.0f);
}

color color_thistle()
{
    return rgba_color(216, 191, 216, 1.0f);
}

color color_tomato()
{
    return rgba_color(1.0f, 99, 71, 1.0f);
}

color color_turquoise()
{
    return rgba_color(64, 224, 208, 1.0f);
}

color color_violet()
{
    return rgba_color(238, 130, 238, 1.0f);
}

color color_wheat()
{
    return rgba_color(245, 222, 179, 1.0f);
}

color color_white()
{
    return rgba_color(1.0f, 1.0f, 1.0f, 1.0f);
}

color color_white_smoke()
{
    return rgba_color(245, 245, 245, 1.0f);
}

color color_yellow()
{
    return rgba_color(1.0f, 1.0f, 0, 1.0f);
}

color color_yellow_green()
{
    return rgba_color(154, 205, 50, 1.0f);
}

color color_swinburne_red()
{
    return rgba_color(237, 36, 25, 1.0f);
}
