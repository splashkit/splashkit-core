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
        string filename = "magical_night.ogg", name = "magical_night";
        SECTION("can load music")
        {
            REQUIRE(has_music(name) == false);
            mus = load_music(name, filename);
            REQUIRE(mus != nullptr);
            REQUIRE(has_music(name) == true);
            REQUIRE(music_valid(mus) == true);
            REQUIRE(music_name(mus) == name);
            REQUIRE(music_filename(mus) == path_to_resource(filename, SOUND_RESOURCE));
            REQUIRE(music_named(name) == mus);
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
            REQUIRE(has_music(name) == false);
        }
    }
    SECTION("can load and free multiple music files")
    {
        music mus1, mus2;
        string filename1 = "280.mp3", name1 = "280", filename2 = "dancingFrog.wav", name2 = "dancingFrog";
        SECTION("can load and create two music files")
        {
            REQUIRE(has_music(name1) == false);
            mus1 = load_music(name1, filename1);
            REQUIRE(mus1 != nullptr);
            REQUIRE(has_music(name1) == true);
            REQUIRE(music_valid(mus1) == true);
            REQUIRE(music_name(mus1) == name1);
            REQUIRE(music_filename(mus1) == path_to_resource(filename1, SOUND_RESOURCE));
            REQUIRE(music_named(name1) == mus1);

            REQUIRE(has_music(name2) == false);
            mus2 = load_music(name2, filename2);
            REQUIRE(mus2 != nullptr);
            REQUIRE(has_music(name2) == true);
            REQUIRE(music_valid(mus2) == true);
            REQUIRE(music_name(mus2) == name2);
            REQUIRE(music_filename(mus2) == path_to_resource(filename2, SOUND_RESOURCE));
            REQUIRE(music_named(name2) == mus2);
        }
        SECTION("can free all music")
        {
            free_all_music();
            REQUIRE(has_music(name1) == false);
            REQUIRE(has_music(name2) == false);
        }
    }
}
