//
//  test_text.cpp
//  splashkit
//
//  Created by Kai Renshaw on 27/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "test_text.hpp"

#include "text.h"
#include "graphics.h"
#include "input.h"
#include "color.h"
#include "utils.h"
#include "random.h"

#include <iostream>
#include <string>
using namespace std;

string stringify_font_style(int style) {
    switch (style) {
        case NORMAL_FONT: return "NORMAL_FONT";
        case BOLD_FONT: return "BOLD_FONT";
        case ITALIC_FONT: return "ITALIC_FONT";
        case UNDERLINE_FONT: return "UNDERLINE_FONT";
        default: return "NO_STYLE_FONT";
    }
}

void test_load_font()
{
    cout << "Has hara.ttf (expect 0): " << has_font("hara") << endl;
    cout << "Has LeagueGothic.otf (expect 0): " << has_font("leaguegothic") << endl;

    load_font("hara", "hara.ttf", 25);
    font fnt = load_font("leaguegothic", "LeagueGothic.otf", 25);

    cout << "Has hara.ttf (expect 1): " << has_font("hara") << endl;
    cout << "Has LeagueGothic.otf (expect 1): " << has_font("leaguegothic") << endl;

    draw_text("Text draws weee!", COLOR_BLACK, fnt, 0, 0);
}

void test_font_styles()
{
    cout << "Setting font styles on hara.ttf" << endl;
    
    font fnt = font_named("leaguegothic");
    
    font_style style = get_font_style(fnt);
    cout << "Initial font style: " << stringify_font_style(style) << endl;
    
    set_font_style(fnt, ITALIC_FONT);
    style = get_font_style(fnt);
    cout << "After setting the font style to ITALIC: " << stringify_font_style(style) << endl;
    
    draw_text("Text draws in ITALICS weee!", COLOR_BLACK, fnt, 0, 25);
    set_font_style(fnt, BOLD_FONT);
    draw_text("Text draws in BOLD weee!", COLOR_BLACK, fnt, 0, 50);
    set_font_style(fnt, UNDERLINE_FONT);
    draw_text("Text draws with UNDERLINES weee!", COLOR_BLACK, fnt, 0, 75);
    set_font_style(fnt, ITALIC_FONT|UNDERLINE_FONT);
    draw_text("Text draws with ITALICS AND UNDERLINES weee!", COLOR_BLACK, fnt, 0, 100);
}

void run_text_test()
{
    open_window("Test Text", 800, 600);
    
    cout << "Testing text API" << endl;
    test_load_font();
    test_font_styles();
    
    refresh_screen();
    delay(3000);

    close_window(window_named("Test Text"));
}
