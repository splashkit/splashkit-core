/**
 * Music Unit Tests
 */

#include "catch.hpp"

#include "types.h"
#include "audio.h"
#include "resources.h"

using namespace splashkit_lib;

TEST_CASE("music can be loaded, controlled and freed", "[music]")
{
    SECTION("can get audio ready")
    {
        open_audio();
        REQUIRE(audio_ready() == true);
    }
    SECTION("can detect non-existent music")
    {
        music no_mus = load_music("non_existent", "non_existent.mp3");
        REQUIRE(no_mus == nullptr);
        REQUIRE(has_music("non_existent") == false);
    }
    SECTION("can load, control and free music")
    {
        music mus;
        SECTION("can load music")
        {
            REQUIRE(has_music("magical_night") == false);
            mus = load_music("magical_night", "magical_night.ogg");
            REQUIRE(mus != nullptr);
            REQUIRE(has_music("magical_night") == true);
            REQUIRE(music_valid(mus) == true);
            REQUIRE(music_name(mus) == "magical_night");
            REQUIRE(music_filename(mus) == path_to_resource("magical_night.ogg", SOUND_RESOURCE));
            REQUIRE(music_named("magical_night") == mus);
        }
        SECTION("can control music")
        {
            REQUIRE(music_playing() == false);
            play_music(mus);
            REQUIRE(music_playing() == true);
            pause_music();
            REQUIRE(music_playing() == true); // music is paused, not stopped
            resume_music();
            REQUIRE(music_playing() == true);
            stop_music();
            REQUIRE(music_playing() == false);
        }
        SECTION("can set music volume")
        {
            play_music(mus, 1, 0.75f);
            REQUIRE(music_volume() == 0.75f);
            set_music_volume(1.0f);
            REQUIRE(music_volume() == 1.0f);
            set_music_volume(0.0f);
            REQUIRE(music_volume() == 0.0f);
            set_music_volume(0.5f);
            REQUIRE(music_volume() == 0.5f);
        }
        SECTION("can free music")
        {
            free_music(mus);
            REQUIRE(has_music("magical_night") == false);
        }
    }
    SECTION("can load and free multiple music files")
    {
        music mus, mus2;
        SECTION("can load and create two music files")
        {
            REQUIRE(has_music("280") == false);
            mus = load_music("280", "280.mp3");
            REQUIRE(mus != nullptr);
            REQUIRE(has_music("280") == true);
            REQUIRE(music_valid(mus) == true);
            REQUIRE(music_name(mus) == "280");
            REQUIRE(music_filename(mus) == path_to_resource("280.mp3", SOUND_RESOURCE));
            REQUIRE(music_named("280") == mus);

            REQUIRE(has_music("dancingFrog") == false);
            mus2 = load_music("dancingFrog", "dancingFrog.wav");
            REQUIRE(mus2 != nullptr);
            REQUIRE(has_music("dancingFrog") == true);
            REQUIRE(music_valid(mus2) == true);
            REQUIRE(music_name(mus2) == "dancingFrog");
            REQUIRE(music_filename(mus2) == path_to_resource("dancingFrog.wav", SOUND_RESOURCE));
            REQUIRE(music_named("dancingFrog") == mus2);
        }
        SECTION("can free all music")
        {
            free_all_music();
            REQUIRE(has_music("280") == false);
            REQUIRE(has_music("dancingFrog") == false);
        }
    }
}
