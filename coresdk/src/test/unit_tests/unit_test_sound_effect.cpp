/**
 * Sound Effect Unit Tests
 */

#include "catch.hpp"

#include "types.h"
#include "audio.h"
#include "resources.h"

using namespace splashkit_lib;

TEST_CASE("sound effects can be loaded, played and freed", "[sound_effect]")
{
    SECTION("can get audio ready")
    {
        open_audio();
        REQUIRE(audio_ready() == true);
    }    
    SECTION("can detect non-existent sound effect")
    {
        REQUIRE(has_sound_effect("non_existent") == false);
        sound_effect no_snd = load_sound_effect("non_existent", "non_existent.mp3");
        REQUIRE(no_snd == nullptr);
        REQUIRE(has_sound_effect("non_existent") == false);
    }
    SECTION("can load, play, stop and free sound effect")
    {
        sound_effect snd;
        SECTION("can load sound effect")
        {
            REQUIRE(has_sound_effect("SwinGameStart") == false);
            snd = load_sound_effect("SwinGameStart", "SwinGameStart.wav");
            REQUIRE(snd != nullptr);
            REQUIRE(has_sound_effect("SwinGameStart") == true);
            REQUIRE(sound_effect_valid(snd) == true);
            REQUIRE(sound_effect_name(snd) == "SwinGameStart");
            REQUIRE(sound_effect_filename(snd) == path_to_resource("SwinGameStart.wav", SOUND_RESOURCE));
            REQUIRE(sound_effect_named("SwinGameStart") == snd);
        }
        SECTION("can play sound effect")
        {
            REQUIRE(sound_effect_playing(snd) == false);
            play_sound_effect(snd);
            REQUIRE(sound_effect_playing(snd) == true);
        }
        SECTION("can stop sound effect")
        {
            stop_sound_effect(snd);
            REQUIRE(sound_effect_playing(snd) == false);
        }
        SECTION("can free sound effect")
        {
            free_sound_effect(snd);
            REQUIRE(has_sound_effect("error") == false);
        }
    }
    SECTION("can load and free multiple sounds effects")
    {
        sound_effect snd, snd2;
        SECTION("can load and create two sound effects")
        {
            REQUIRE(has_sound_effect("breakdance") == false);
            snd = load_sound_effect("breakdance", "breakdance.wav");
            REQUIRE(snd != nullptr);
            REQUIRE(has_sound_effect("breakdance") == true);
            REQUIRE(sound_effect_valid(snd) == true);
            REQUIRE(sound_effect_name(snd) == "breakdance");
            REQUIRE(sound_effect_filename(snd) == path_to_resource("breakdance.wav", SOUND_RESOURCE));
            REQUIRE(sound_effect_named("breakdance") == snd);

            REQUIRE(has_sound_effect("comedy_boing") == false);
            snd2 = load_sound_effect("comedy_boing", "comedy_boing.ogg");
            REQUIRE(snd2 != nullptr);
            REQUIRE(has_sound_effect("comedy_boing") == true);
            REQUIRE(sound_effect_valid(snd2) == true);
            REQUIRE(sound_effect_name(snd2) == "comedy_boing");
            REQUIRE(sound_effect_filename(snd2) == path_to_resource("comedy_boing.ogg", SOUND_RESOURCE));
            REQUIRE(sound_effect_named("comedy_boing") == snd2);
        }
        SECTION("can free all sound effects")
        {
            free_all_sound_effects();
            REQUIRE(has_sound_effect("breakdance") == false);
            REQUIRE(has_sound_effect("comedy_boing") == false);
        }
    }
}
