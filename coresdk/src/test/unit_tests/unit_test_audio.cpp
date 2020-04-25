#include <catch.hpp>

#include "audio_driver.h"
#include "music.h"
#include "sound.h"

TEST_CASE("Audio can be setup and shutdown", "[audio]"){
    namespace sk = splashkit_lib;
    SECTION("Setup"){
        sk::sk_init_audio();
        REQUIRE(sk::sk_audio_get_last_error() != -1);
        sk::sk_open_audio();

        REQUIRE(sk::sk_audio_is_open());

        sk::stop_music();
        sk::sk_close_audio();
        sk::free_all_music();
        REQUIRE(sk::sk_audio_get_last_error() != -1);
    }

    SECTION("Get Device Attributes"){
        sk::sk_init_audio();
        REQUIRE(sk::sk_audio_get_last_error() != -1);
        sk::sk_open_audio();

        int size = 0;
        int* attributes = sk::sk_get_device_attributes(&size);
        REQUIRE(size > 0);
        REQUIRE(attributes != nullptr);
        
        delete attributes;

        sk::sk_close_audio();
        sk::free_all_music();

    }

}

TEST_CASE("Music can be played", "[audio][music]"){
    // Setup
    namespace sk = splashkit_lib;
    sk::sk_init_audio();
    REQUIRE(sk::sk_audio_get_last_error() != -1);
    sk::sk_open_audio();

    SECTION("Load Music"){
        sk::sk_init_audio();
        REQUIRE(sk::sk_audio_get_last_error() != -1);

        sk::music music = sk::load_music("magic", "magical_night.ogg");
        REQUIRE(music != nullptr);
        
        sk::free_all_music();
        sk::sk_close_audio();
    }

    SECTION("Load and play music"){

        sk::music music = sk::load_music("magic", "magical_night.ogg");
        REQUIRE(music != nullptr);
        sk::play_music(music);
        // Uncomment to hear audio playing
        int i = 0;
        // while(i < 100){
        //     struct timespec ts, rem;
        //     unsigned long nsec = 10000000;
        //     ts.tv_sec = (time_t)(nsec / 1000000000ul);
        //     ts.tv_nsec = (long)(nsec % 1000000000ul);
        //     while(nanosleep(&ts, &rem) == -1 && errno == EINTR){
        //         ts = rem;
        //     }
        //     i++;
        //     INFO("Volume is " << sk::music_volume());
        // }

        // sk::play_music(music);


    }

    SECTION("Play pause music"){

        sk::music music = sk::load_music("magic", "magical_night.ogg");
        REQUIRE(music != nullptr);
        sk::play_music(music);
        sk::pause_music();
        REQUIRE(sk::sk_audio_get_last_error() != -1);
        sk::resume_music();
        REQUIRE(sk::sk_audio_get_last_error() != -1);
        sk::stop_music();
        REQUIRE(sk::sk_audio_get_last_error() != -1);
    }

    sk::stop_music();
    sk::free_all_music();
    sk::sk_close_audio();
}

TEST_CASE("Play sound files", "[audio][sounds]"){

    namespace sk = splashkit_lib;
    sk::sk_init_audio();
    REQUIRE(sk::sk_audio_get_last_error() != -1);
    sk::sk_open_audio();


    SECTION("Play one sound"){
        sk::sound_effect test_sound = sk::load_sound_effect("test", "test.ogg");
        sk::play_sound_effect(test_sound);
        REQUIRE(sk::sound_effect_playing(test_sound));
        // Just delays so the sound can play
        // int i = 0;
        // while(i < 10000){
        //     struct timespec ts, rem;
        //     unsigned long nsec = 10000000;
        //     ts.tv_sec = (time_t)(nsec / 1000000000ul);
        //     ts.tv_nsec = (long)(nsec % 1000000000ul);
        //     while(nanosleep(&ts, &rem) == -1 && errno == EINTR){
        //         ts = rem;
        //     }
        //     i++;
        // }
        sk::stop_sound_effect(test_sound);

    }
    SECTION("Play multiple sounds"){
        sk::sound_effect test_sound = sk::load_sound_effect("test", "test.ogg");
        auto test_sound_2 = sk::load_sound_effect("test2", "280.mp3");

        REQUIRE(!sk::sound_effect_playing(test_sound));

        sk::play_sound_effect(test_sound);
        sk::play_sound_effect(test_sound_2);

        REQUIRE(sk::sound_effect_playing("test2"));
        REQUIRE(sk::sound_effect_playing(test_sound));
        // Just delays so the sound can play
        // int i = 0;
        // while(i < 10000){
        //     struct timespec ts, rem;
        //     unsigned long nsec = 10000000;
        //     ts.tv_sec = (time_t)(nsec / 1000000000ul);
        //     ts.tv_nsec = (long)(nsec % 1000000000ul);
        //     while(nanosleep(&ts, &rem) == -1 && errno == EINTR){
        //         ts = rem;
        //     }
        //     i++;
        // }
        sk::stop_sound_effect(test_sound);
        sk::stop_sound_effect(test_sound_2);

    }
    sk::stop_music();
    sk::free_all_music();
    sk::free_all_sound_effects();
    sk::sk_close_audio();

}

#include <thread>

TEST_CASE("Fade audio", "[audio][fade]"){
    namespace sk = splashkit_lib;
    sk::sk_init_audio();
    REQUIRE(sk::sk_audio_get_last_error() != -1);
    sk::sk_open_audio();

    SECTION("Fade in"){
        sk::music music = sk::load_music("magic", "magical_night.ogg");
        sk::play_music(music);
        sk::fade_music_in(music, 10);
        REQUIRE(sk::music_playing());
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        sk::stop_music();
        sk::free_music(music);

    }

    SECTION("Fade out"){
        sk::music music = sk::load_music("magic", "magical_night.ogg");
        sk::play_music(music);
        REQUIRE(sk::music_playing());
        sk::fade_music_out(10);
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        sk::stop_music();
        sk::free_music(music);


    }
    

    sk::stop_music();
    sk::free_all_music();
    sk::free_all_sound_effects();
    sk::sk_close_audio();
}