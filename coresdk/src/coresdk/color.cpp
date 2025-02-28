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

#include "utility_functions.h"

using std::ostringstream;
using std::hex;
using std::stringstream;

namespace splashkit_lib
{
    typedef unsigned char byte;

    color random_color()
    {
        return rgba_color(rnd(), rnd(), rnd(), rnd());
    }

    color random_rgb_color(int alpha)
    {
        return rgba_color(rnd(), rnd(), rnd(), alpha / 255.0f);
    }

    color rgba_color(int red, int green, int blue, int alpha)
    {
        return rgba_color(red / 255.0f, green / 255.0f, blue / 255.0f, alpha / 255.0f);
    }

    /// _gets a color given its color components. Each of the components has
    /// a value between 0 and 1
    ///
    color rgba_color(double red, double green, double blue, double alpha)
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
    color rgb_color(int red, int green, int blue)
    {
        return rgba_color(red / 255.0f, green / 255.0f, blue / 255.0f, 1.0f);
    }

    /// _gets a color given its _r_g_b components. Each of the components has
    /// a value between 0 and 1.
    ///
    color rgb_color(double red, double green, double blue)
    {
        return rgba_color(red, green, blue, 1.0f);
    }

    /// _returs a color from a combination of hue, saturation, and brightness.
    ///
    /// @param hue, saturation, brightness: _values between 0 and 1
    /// @returns _the matching color
    ///
    color hsb_color(double hue, double saturation, double brightness)
    {
        double domain_offset;
        double red, green, blue;

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

    void hsb_value_of(color c, double &h, double &s, double &b)
    {
        double rf, gf, bf;
        double min_rgb, max_rgb, delta;

        h = 0.0 ;

        rf = c.r;
        gf = c.g;
        bf = c.b;

        min_rgb = MIN(MIN(rf, gf), bf);
        max_rgb = MAX(MAX(rf, gf), bf);
        delta = (max_rgb - min_rgb);

        b = max_rgb;
        if (max_rgb != 0.0)
            s = delta / max_rgb;
        else
            s = 0.0;

        if (s != 0.0)
        {
            if (rf == max_rgb) h = (gf - bf) / delta;
            else if (gf == max_rgb) h = 2.0 + (bf - rf) / delta;
            else if (bf == max_rgb) h = 4.0 + (rf - gf) / delta;
            else LOG(WARNING) << "Error converting color to hsb";
        }
        else
        {
            h = -1.0;
        }

        h = h * 60 ;
        if (h < 0.0) h += 360.0;

        h = h / 360.0;
    }

    string color_to_string(color c)
    {
        ostringstream result;

        result << '#' << hex << std::setfill ('0');
        result << std::setw(2) << static_cast<int>(red_of(c));
        result << std::setw(2) << static_cast<int>(green_of(c));
        result << std::setw(2) << static_cast<int>(blue_of(c));
        result << std::setw(2) << static_cast<int>(alpha_of(c));

        return result.str();
    }

    color string_to_color(string str)
    {
        if (str[0] != '#' || not ( str.length() == 7 || str.length() == 9 ))
        {
            LOG(WARNING) << "Color string needs to start with a # and be 7 or 9 characters long";
            return COLOR_WHITE;
        }

        unsigned int clr_int = 0;
        byte r, g, b, a;

        str.erase(str.begin());     // Remove the #

        stringstream ss;
        ss << hex << str;
        ss >> clr_int;

        r = static_cast<byte>(clr_int >> 24);
        g = static_cast<byte>(clr_int >> 16);
        b = static_cast<byte>(clr_int >> 8);

        if ( str.length() == 8 )
            a = static_cast<byte>(clr_int >> 0);
        else
            a = 255;


        return rgba_color(r, g, b, a);
    }

    int alpha_of(color c)
    {
        return static_cast<int>(255 * c.a);
    }

    int red_of(color c)
    {
        return static_cast<int>(255 * c.r);
    }

    int green_of(color c)
    {
        return static_cast<int>(255 * c.g);
    }

    int blue_of(color c)
    {
        return static_cast<int>(255 * c.b);
    }


    double hue_of(color c)
    {
        double h, s, b;
        hsb_value_of(c, h, s, b);
        return h;
    }


    double saturation_of(color c)
    {
        double h, s, b;
        hsb_value_of(c, h, s, b);
        return s;
    }

    double brightness_of(color c)
    {
        double h, s, b;
        hsb_value_of(c, h, s, b);
        return b;
    }

    color color_gray()
    {
        return rgba_color(127/255.0, 127/255.0, 127/255.0, 1.0);
    }

    color color_light_grey()
    {
        return rgba_color(200/255.0, 200/255.0, 200/255.0, 1.0);
    }

    color color_transparent()
    {
        return rgba_color(255/255.0, 255/255.0, 255/255.0, 1.0);
    }

    color color_alice_blue()
    {
        return rgba_color(240/255.0, 248/255.0, 255/255.0, 1.0);
    }

    color color_antique_white()
    {
        return rgba_color(250/255.0, 235/255.0, 215/255.0, 1.0);
    }

    color color_aqua()
    {
        return rgba_color(0/255.0, 255/255.0, 255/255.0, 1.0);
    }

    color color_aquamarine()
    {
        return rgba_color(127/255.0, 255/255.0, 212/255.0, 1.0);
    }

    color color_azure()
    {
        return rgba_color(240/255.0, 255/255.0, 255/255.0, 1.0);
    }

    color color_beige()
    {
        return rgba_color(245/255.0, 245/255.0, 220/255.0, 1.0);
    }

    color color_bisque()
    {
        return rgba_color(255/255.0, 228/255.0, 196/255.0, 1.0);
    }

    color color_black()
    {
        return rgba_color(0/255.0, 0/255.0, 0/255.0, 1.0);
    }

    color color_blanched_almond()
    {
        return rgba_color(255/255.0, 235/255.0, 205/255.0, 1.0);
    }

    color color_blue()
    {
        return rgba_color(0/255.0, 0/255.0, 255/255.0, 1.0);
    }

    color color_blue_violet()
    {
        return rgba_color(138/255.0, 43/255.0, 226/255.0, 1.0);
    }

    color color_brown()
    {
        return rgba_color(165/255.0, 42/255.0, 42/255.0, 1.0);
    }

    color color_burly_wood()
    {
        return rgba_color(222/255.0, 184/255.0, 135/255.0, 1.0);
    }

    color color_cadet_blue()
    {
        return rgba_color(95/255.0, 158/255.0, 160/255.0, 1.0);
    }

    color color_chartreuse()
    {
        return rgba_color(127/255.0, 255/255.0, 0/255.0, 1.0);
    }

    color color_chocolate()
    {
        return rgba_color(210/255.0, 105/255.0, 30/255.0, 1.0);
    }

    color color_coral()
    {
        return rgba_color(255/255.0, 127/255.0, 80/255.0, 1.0);
    }

    color color_cornflower_blue()
    {
        return rgba_color(100/255.0, 149/255.0, 237/255.0, 1.0);
    }

    color color_cornsilk()
    {
        return rgba_color(255/255.0, 248/255.0, 220/255.0, 1.0);
    }

    color color_crimson()
    {
        return rgba_color(220/255.0, 20/255.0, 60/255.0, 1.0);
    }

    color color_cyan()
    {
        return rgba_color(0/255.0, 255/255.0, 255/255.0, 1.0);
    }

    color color_dark_blue()
    {
        return rgba_color(0/255.0, 0/255.0, 139/255.0, 1.0);
    }

    color color_dark_cyan()
    {
        return rgba_color(0/255.0, 139/255.0, 139/255.0, 1.0);
    }

    color color_dark_goldenrod()
    {
        return rgba_color(184/255.0, 134/255.0, 11/255.0, 1.0);
    }

    color color_dark_gray()
    {
        return rgba_color(169/255.0, 169/255.0, 169/255.0, 1.0);
    }

    color color_dark_green()
    {
        return rgba_color(0/255.0, 100/255.0, 0/255.0, 1.0);
    }

    color color_dark_khaki()
    {
        return rgba_color(189/255.0, 183/255.0, 107/255.0, 1.0);
    }

    color color_dark_magenta()
    {
        return rgba_color(139/255.0, 0/255.0, 139/255.0, 1.0);
    }

    color color_dark_olive_green()
    {
        return rgba_color(85/255.0, 107/255.0, 47/255.0, 1.0);
    }

    color color_dark_orange()
    {
        return rgba_color(255/255.0, 140/255.0, 0/255.0, 1.0);
    }

    color color_dark_orchid()
    {
        return rgba_color(153/255.0, 50/255.0, 204/255.0, 1.0);
    }

    color color_dark_red()
    {
        return rgba_color(139/255.0, 0/255.0, 0/255.0, 1.0);
    }

    color color_dark_salmon()
    {
        return rgba_color(233/255.0, 150/255.0, 122/255.0, 1.0);
    }

    color color_dark_sea_green()
    {
        return rgba_color(143/255.0, 188/255.0, 139/255.0, 1.0);
    }

    color color_dark_slate_blue()
    {
        return rgba_color(72/255.0, 61/255.0, 139/255.0, 1.0);
    }

    color color_dark_slate_gray()
    {
        return rgba_color(47/255.0, 79/255.0, 79/255.0, 1.0);
    }

    color color_dark_turquoise()
    {
        return rgba_color(0/255.0, 206/255.0, 209/255.0, 1.0);
    }

    color color_dark_violet()
    {
        return rgba_color(148/255.0, 0/255.0, 211/255.0, 1.0);
    }

    color color_deep_pink()
    {
        return rgba_color(255/255.0, 20/255.0, 147/255.0, 1.0);
    }

    color color_deep_sky_blue()
    {
        return rgba_color(0/255.0, 191/255.0, 255/255.0, 1.0);
    }

    color color_dim_gray()
    {
        return rgba_color(105/255.0, 105/255.0, 105/255.0, 1.0);
    }

    color color_dodger_blue()
    {
        return rgba_color(30/255.0, 144/255.0, 255/255.0, 1.0);
    }

    color color_firebrick()
    {
        return rgba_color(178/255.0, 34/255.0, 34/255.0, 1.0);
    }

    color color_floral_white()
    {
        return rgba_color(255/255.0, 250/255.0, 240/255.0, 1.0);
    }

    color color_forest_green()
    {
        return rgba_color(34/255.0, 139/255.0, 34/255.0, 1.0);
    }

    color color_fuchsia()
    {
        return rgba_color(255/255.0, 0/255.0, 255/255.0, 1.0);
    }

    color color_gainsboro()
    {
        return rgba_color(220/255.0, 220/255.0, 220/255.0, 1.0);
    }

    color color_ghost_white()
    {
        return rgba_color(248/255.0, 248/255.0, 255/255.0, 1.0);
    }

    color color_gold()
    {
        return rgba_color(255/255.0, 215/255.0, 0/255.0, 1.0);
    }

    color color_goldenrod()
    {
        return rgba_color(218/255.0, 165/255.0, 32/255.0, 1.0);
    }

    color color_grey()
    {
        return rgba_color(127/255.0, 127/255.0, 127/255.0, 1.0);
    }

    color color_green()
    {
        return rgba_color(0/255.0, 127/255.0, 0/255.0, 1.0);
    }

    color color_bright_green()
    {
        return rgba_color(0/255.0, 255/255.0, 0/255.0, 1.0);
    }

    color color_green_yellow()
    {
        return rgba_color(173/255.0, 255/255.0, 47/255.0, 1.0);
    }

    color color_honeydew()
    {
        return rgba_color(240/255.0, 255/255.0, 240/255.0, 1.0);
    }

    color color_hot_pink()
    {
        return rgba_color(255/255.0, 105/255.0, 180/255.0, 1.0);
    }

    color color_indian_red()
    {
        return rgba_color(205/255.0, 92/255.0, 92/255.0, 1.0);
    }

    color color_indigo()
    {
        return rgba_color(75/255.0, 0/255.0, 130/255.0, 1.0);
    }

    color color_ivory()
    {
        return rgba_color(255/255.0, 255/255.0, 240/255.0, 1.0);
    }

    color color_khaki()
    {
        return rgba_color(240/255.0, 230/255.0, 140/255.0, 1.0);
    }

    color color_lavender()
    {
        return rgba_color(230/255.0, 230/255.0, 250/255.0, 1.0);
    }

    color color_lavender_blush()
    {
        return rgba_color(255/255.0, 240/255.0, 245/255.0, 1.0);
    }

    color color_lawn_green()
    {
        return rgba_color(124/255.0, 252/255.0, 0/255.0, 1.0);
    }

    color color_lemon_chiffon()
    {
        return rgba_color(255/255.0, 250/255.0, 205/255.0, 1.0);
    }

    color color_light_blue()
    {
        return rgba_color(173/255.0, 216/255.0, 230/255.0, 1.0);
    }

    color color_light_coral()
    {
        return rgba_color(240/255.0, 127/255.0, 127/255.0, 1.0);
    }

    color color_light_cyan()
    {
        return rgba_color(224/255.0, 255/255.0, 255/255.0, 1.0);
    }

    color color_light_goldenrod_yellow()
    {
        return rgba_color(250/255.0, 250/255.0, 210/255.0, 1.0);
    }

    color color_light_green()
    {
        return rgba_color(144/255.0, 238/255.0, 144/255.0, 1.0);
    }

    color color_light_gray()
    {
        return rgba_color(211/255.0, 211/255.0, 211/255.0, 1.0);
    }

    color color_light_pink()
    {
        return rgba_color(255/255.0, 182/255.0, 193/255.0, 1.0);
    }

    color color_light_salmon()
    {
        return rgba_color(255/255.0, 160/255.0, 122/255.0, 1.0);
    }

    color color_light_sea_green()
    {
        return rgba_color(32/255.0, 178/255.0, 170/255.0, 1.0);
    }

    color color_light_sky_blue()
    {
        return rgba_color(135/255.0, 206/255.0, 250/255.0, 1.0);
    }

    color color_light_slate_gray()
    {
        return rgba_color(119/255.0, 136/255.0, 153/255.0, 1.0);
    }

    color color_light_steel_blue()
    {
        return rgba_color(176/255.0, 196/255.0, 222/255.0, 1.0);
    }

    color color_light_yellow()
    {
        return rgba_color(255/255.0, 255/255.0, 224/255.0, 1.0);
    }

    color color_lime()
    {
        return rgba_color(0/255.0, 255/255.0, 0/255.0, 1.0);
    }

    color color_lime_green()
    {
        return rgba_color(50/255.0, 205/255.0, 50/255.0, 1.0);
    }

    color color_linen()
    {
        return rgba_color(250/255.0, 240/255.0, 230/255.0, 1.0);
    }

    color color_magenta()
    {
        return rgba_color(255/255.0, 0/255.0, 255/255.0, 1.0);
    }

    color color_maroon()
    {
        return rgba_color(127/255.0, 0/255.0, 0/255.0, 1.0);
    }

    color color_medium_aquamarine()
    {
        return rgba_color(102/255.0, 205/255.0, 170/255.0, 1.0);
    }

    color color_medium_blue()
    {
        return rgba_color(0/255.0, 0/255.0, 205/255.0, 1.0);
    }

    color color_medium_orchid()
    {
        return rgba_color(186/255.0, 85/255.0, 211/255.0, 1.0);
    }

    color color_medium_purple()
    {
        return rgba_color(147/255.0, 112/255.0, 219/255.0, 1.0);
    }

    color color_medium_sea_green()
    {
        return rgba_color(60/255.0, 179/255.0, 113/255.0, 1.0);
    }

    color color_medium_slate_blue()
    {
        return rgba_color(123/255.0, 104/255.0, 238/255.0, 1.0);
    }

    color color_medium_spring_green()
    {
        return rgba_color(0/255.0, 250/255.0, 154/255.0, 1.0);
    }

    color color_medium_turquoise()
    {
        return rgba_color(72/255.0, 209/255.0, 204/255.0, 1.0);
    }

    color color_medium_violet_red()
    {
        return rgba_color(199/255.0, 21/255.0, 133/255.0, 1.0);
    }

    color color_midnight_blue()
    {
        return rgba_color(25/255.0, 25/255.0, 112/255.0, 1.0);
    }

    color color_mint_cream()
    {
        return rgba_color(245/255.0, 255/255.0, 250/255.0, 1.0);
    }

    color color_misty_rose()
    {
        return rgba_color(255/255.0, 228/255.0, 225/255.0, 1.0);
    }

    color color_moccasin()
    {
        return rgba_color(255/255.0, 228/255.0, 181/255.0, 1.0);
    }

    color color_navajo_white()
    {
        return rgba_color(255/255.0, 222/255.0, 173/255.0, 1.0);
    }

    color color_navy()
    {
        return rgba_color(0/255.0, 0/255.0, 127/255.0, 1.0);
    }

    color color_old_lace()
    {
        return rgba_color(253/255.0, 245/255.0, 230/255.0, 1.0);
    }

    color color_olive()
    {
        return rgba_color(127/255.0, 127/255.0, 0/255.0, 1.0);
    }

    color color_olive_drab()
    {
        return rgba_color(107/255.0, 142/255.0, 35/255.0, 1.0);
    }

    color color_orange()
    {
        return rgba_color(255/255.0, 165/255.0, 0/255.0, 1.0);
    }

    color color_orange_red()
    {
        return rgba_color(255/255.0, 69/255.0, 0/255.0, 1.0);
    }

    color color_orchid()
    {
        return rgba_color(218/255.0, 112/255.0, 214/255.0, 1.0);
    }

    color color_pale_goldenrod()
    {
        return rgba_color(238/255.0, 232/255.0, 170/255.0, 1.0);
    }

    color color_pale_green()
    {
        return rgba_color(152/255.0, 251/255.0, 152/255.0, 1.0);
    }

    color color_pale_turquoise()
    {
        return rgba_color(175/255.0, 238/255.0, 238/255.0, 1.0);
    }

    color color_pale_violet_red()
    {
        return rgba_color(219/255.0, 112/255.0, 147/255.0, 1.0);
    }

    color color_papaya_whip()
    {
        return rgba_color(255/255.0, 239/255.0, 213/255.0, 1.0);
    }

    color color_peach_puff()
    {
        return rgba_color(255/255.0, 218/255.0, 185/255.0, 1.0);
    }

    color color_peru()
    {
        return rgba_color(205/255.0, 133/255.0, 63/255.0, 1.0);
    }

    color color_pink()
    {
        return rgba_color(255/255.0, 192/255.0, 203/255.0, 1.0);
    }

    color color_plum()
    {
        return rgba_color(221/255.0, 160/255.0, 221/255.0, 1.0);
    }

    color color_powder_blue()
    {
        return rgba_color(176/255.0, 224/255.0, 230/255.0, 1.0);
    }

    color color_purple()
    {
        return rgba_color(127/255.0, 0/255.0, 127/255.0, 1.0);
    }

    color color_red()
    {
        return rgba_color(255/255.0, 0/255.0, 0/255.0, 1.0);
    }

    color color_rosy_brown()
    {
        return rgba_color(188/255.0, 143/255.0, 143/255.0, 1.0);
    }

    color color_royal_blue()
    {
        return rgba_color(65/255.0, 105/255.0, 225/255.0, 1.0);
    }

    color color_saddle_brown()
    {
        return rgba_color(139/255.0, 69/255.0, 19/255.0, 1.0);
    }

    color color_salmon()
    {
        return rgba_color(250/255.0, 127/255.0, 114/255.0, 1.0);
    }

    color color_sandy_brown()
    {
        return rgba_color(244/255.0, 164/255.0, 96/255.0, 1.0);
    }

    color color_sea_green()
    {
        return rgba_color(46/255.0, 139/255.0, 87/255.0, 1.0);
    }

    color color_sea_shell()
    {
        return rgba_color(255/255.0, 245/255.0, 238/255.0, 1.0);
    }

    color color_sienna()
    {
        return rgba_color(160/255.0, 82/255.0, 45/255.0, 1.0);
    }

    color color_silver()
    {
        return rgba_color(192/255.0, 192/255.0, 192/255.0, 1.0);
    }

    color color_sky_blue()
    {
        return rgba_color(135/255.0, 206/255.0, 235/255.0, 1.0);
    }

    color color_slate_blue()
    {
        return rgba_color(106/255.0, 90/255.0, 205/255.0, 1.0);
    }

    color color_slate_gray()
    {
        return rgba_color(112/255.0, 127/255.0, 144/255.0, 1.0);
    }

    color color_snow()
    {
        return rgba_color(255/255.0, 250/255.0, 250/255.0, 1.0);
    }

    color color_spring_green()
    {
        return rgba_color(0/255.0, 255/255.0, 127/255.0, 1.0);
    }

    color color_steel_blue()
    {
        return rgba_color(70/255.0, 130/255.0, 180/255.0, 1.0);
    }

    color color_tan()
    {
        return rgba_color(210/255.0, 180/255.0, 140/255.0, 1.0);
    }

    color color_teal()
    {
        return rgba_color(0/255.0, 127/255.0, 127/255.0, 1.0);
    }

    color color_thistle()
    {
        return rgba_color(216/255.0, 191/255.0, 216/255.0, 1.0);
    }

    color color_tomato()
    {
        return rgba_color(255/255.0, 99/255.0, 71/255.0, 1.0);
    }

    color color_turquoise()
    {
        return rgba_color(64/255.0, 224/255.0, 208/255.0, 1.0);
    }

    color color_violet()
    {
        return rgba_color(238/255.0, 130/255.0, 238/255.0, 1.0);
    }

    color color_wheat()
    {
        return rgba_color(245/255.0, 222/255.0, 179/255.0, 1.0);
    }

    color color_white()
    {
        return rgba_color(255/255.0, 255/255.0, 255/255.0, 1.0);
    }

    color color_white_smoke()
    {
        return rgba_color(245/255.0, 245/255.0, 245/255.0, 1.0);
    }

    color color_yellow()
    {
        return rgba_color(255/255.0, 255/255.0, 0/255.0, 1.0);
    }

    color color_yellow_green()
    {
        return rgba_color(154/255.0, 205/255.0, 50/255.0, 1.0);
    }

    color color_swinburne_red()
    {
        return rgba_color(237/255.0, 36/255.0, 25/255.0, 1.0);
    }
}
