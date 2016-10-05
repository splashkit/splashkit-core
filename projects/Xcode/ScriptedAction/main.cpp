/**
 * This program creates a scripted sequence for a "knock knock" joke.
 *
 * @author Andrew Cain
 */

#include <splashkit.h>
#include <splashkit_starter.h>

void load_resources()
{
    load_bitmap("door", "cottage_door_and_window_199195.jpg");
    load_sound_effect("knock", "Knocking-84643603.wav");
    load_sound_effect("giggle", "Giggle-1295238132.wav");
    load_font("joke", "hara.ttf");
}


void announce_knock_knock()
{
    draw_bitmap("door", 0, 0);
    draw_text("Knock Knock", COLOR_WHITE_SMOKE, "joke", 60, 50, 200);
    play_sound_effect("knock");
    refresh_screen();
    delay(3500);
}

void ask_whos_there()
{
    draw_bitmap("door", 0, 0);
    draw_text("Who's there?", COLOR_WHITE_SMOKE, "joke", 60, 50, 200);
    refresh_screen();
    delay(2000);
}

void say_boo()
{
    draw_bitmap("door", 0, 0);
    draw_text("Boo", COLOR_WHITE_SMOKE, "joke", 60, 50, 200);
    refresh_screen();
    delay(2000);
}

void ask_boo_who()
{
    draw_bitmap("door", 0, 0);
    draw_text("Boo who?", COLOR_WHITE_SMOKE, "joke", 60, 50, 200);
    refresh_screen();
    delay(2000);
}

void deliver_dont_cry_punchline()
{
    draw_bitmap("door", 0, 0);
    draw_text("Don't cry its", COLOR_WHITE_SMOKE, "joke", 60, 50, 200);
    draw_text("its only a joke!", COLOR_WHITE_SMOKE, "joke", 60, 50, 250);
    refresh_screen();
    delay(1000);
    play_sound_effect("giggle");
    delay(2000);
}

/**
 * This is the entry point, execution starts here. This has the "main"
 * steps for the program.
 */
void main()
{
    open_window("Knock Knock", 500, 333);
    load_resources();

    announce_knock_knock();
    ask_whos_there();
    say_boo();
    ask_boo_who();
    deliver_dont_cry_punchline();
}
