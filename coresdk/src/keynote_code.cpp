
#include <splashkit.h>
#include <splashkit_starter.h>

void main()
{
    open_window("Bitmaps", 300, 300);

    load_bitmap("background", "background.png");

    draw_bitmap("background", 0, 0);

    refresh_screen();

}
