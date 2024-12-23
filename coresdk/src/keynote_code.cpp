#include <splashkit.h>
#include <splashkit_starter.h>


void test_bitmaps()
{
    open_window("Bitmaps", 300, 300);

    load_bitmap("background", "background.png");

    draw_bitmap("background", 0, 0);

    refresh_screen();
}

void how_to_download()
{
    download_bitmap("logo", "http://.../img.jpg", 80);
    draw_bitmap("logo", 100, 100);

    download_sound_effect("boom", "http://...", 80);
    play_sound_effect("boom");

    download_music("song", "https://...", 443);
    play_music("song");

    download_font("font", "http://...", 80);
    draw_text("Hello", COLOR_RED, "font", 32, 10, 10);
}

