
#include "animations.h"
#include "audio.h"
#include "basics.h"
#include "bundles.h"
#include "camera.h"
#include "circle_drawing.h"
#include "circle_geometry.h"
#include "clipping.h"
#include "collisions.h"
#include "color.h"
#include "database.h"
#include "drawing_options.h"
#include "ellipse_drawing.h"
#include "geometry.h"
#include "graphics.h"
#include "images.h"
#include "input.h"
#include "json.h"
#include "keyboard_input.h"
#include "line_drawing.h"
#include "line_geometry.h"
#include "logging.h"
#include "matrix_2d.h"
#include "mouse_input.h"
#include "music.h"
#include "networking.h"
#include "physics.h"
#include "point_drawing.h"
#include "point_geometry.h"
#include "quad_geometry.h"
#include "random.h"
#include "rectangle_drawing.h"
#include "rectangle_geometry.h"
#include "resources.h"
#include "sound.h"
#include "sprites.h"
#include "terminal.h"
#include "text.h"
#include "text_input.h"
#include "timers.h"
#include "triangle_drawing.h"
#include "twitter.h"
#include "types.h"
#include "utils.h"
#include "vector_2d.h"
#include "web_server.h"
#include "window_manager.h"

#include <cstring>

using namespace splashkit_lib;

char* outputCStr(std::string str)
{
    char* ret = new char[str.size()+1];
    memcpy( ret, str.c_str(), str.size());
    ret[str.size()] = '\0';
    return ret;
}

template<typename T>
std::vector<T> inputArrayToVector(T** items)
{
    std::vector<T> out;
    while(*items!=nullptr)
    {
        out.push_back(**items);
        items++;
    }
    return std::move(out);
}
std::vector<string> inputArrayToVector(char** items)
{
    std::vector<string> out;
    while(*items!=nullptr)
    {
        out.push_back((string)*items);
        items++;
    }
    return std::move(out);
}
template<typename T>
std::vector<T> inputArrayToVector(T* items)
{
    std::vector<T> out;
    while(*items!=nullptr)
    {
        out.push_back(*items);
        items++;
    }
    return std::move(out);
}

template<typename T>
T** outputVectorToArrayStruct(const std::vector<T> items)
{
    T** ret = new T*[items.size()+1];
    for(std::size_t i = 0; i < items.size(); i++)
    {
        ret[i] = new T();
        *ret[i] = std::move(items[i]);
    }
    ret[items.size()] = nullptr;
    return ret;
}
template<typename T>
T* outputVectorToArray(const std::vector<T> items)
{
    T* ret = new T[items.size()+1];
    for(std::size_t i = 0; i < items.size(); i++)
    {
        *ret[i] = items[i];
    }
    ret[items.size()] = nullptr;
    return ret;
}
char** outputVectorToArray(const std::vector<string> items)
{
    char** ret = new char*[items.size()+1];
    for(std::size_t i = 0; i < items.size(); i++)
    {
        ret[i] = outputCStr(items[i]);
    }
    ret[items.size()] = nullptr;
    return ret;
}


typedef window SKwindow;
class SplashKitJavascript
{
	public:
        int animation_count(animation_script script){
            return splashkit_lib::animation_count(script);
        }

        int animation_current_cell(animation anim){
            return splashkit_lib::animation_current_cell(anim);
        }

        vector_2d animation_current_vector(animation anim){
            return splashkit_lib::animation_current_vector(anim);
        }

        bool animation_ended(animation anim){
            return splashkit_lib::animation_ended(anim);
        }

        bool animation_entered_frame(animation anim){
            return splashkit_lib::animation_entered_frame(anim);
        }

        float animation_frame_time(animation anim){
            return splashkit_lib::animation_frame_time(anim);
        }

        int animation_index(animation_script script,char*& name){
            return splashkit_lib::animation_index(script,(string)name);
        }

        char* animation_name(animation temp){
            return outputCStr(splashkit_lib::animation_name(temp));
        }

        char* animation_script_name(animation_script script){
            return outputCStr(splashkit_lib::animation_script_name(script));
        }

        animation_script animation_script_named(char*& name){
            return splashkit_lib::animation_script_named((string)name);
        }

        void assign_animation_with_script(animation anim,animation_script script,char*& name){
            return splashkit_lib::assign_animation(anim,script,(string)name);
        }

        void assign_animation_with_script_and_sound(animation anim,animation_script script,char*& name,bool with_sound){
            return splashkit_lib::assign_animation(anim,script,(string)name,with_sound);
        }

        void assign_animation_index_with_script(animation anim,animation_script script,int idx){
            return splashkit_lib::assign_animation(anim,script,idx);
        }

        void assign_animation_index_with_script_and_sound(animation anim,animation_script script,int idx,bool with_sound){
            return splashkit_lib::assign_animation(anim,script,idx,with_sound);
        }

        void assign_animation_with_script_named(animation anim,char*& script_name,char*& name){
            return splashkit_lib::assign_animation(anim,(string)script_name,(string)name);
        }

        void assign_animation_with_script_named_and_sound(animation anim,char*& script_name,char*& name,bool with_sound){
            return splashkit_lib::assign_animation(anim,(string)script_name,(string)name,with_sound);
        }

        void assign_animation_index(animation anim,int idx){
            return splashkit_lib::assign_animation(anim,idx);
        }

        void assign_animation_index_with_sound(animation anim,int idx,bool with_sound){
            return splashkit_lib::assign_animation(anim,idx,with_sound);
        }

        void assign_animation(animation anim,char* name){
            return splashkit_lib::assign_animation(anim,(string)name);
        }

        void assign_animation_with_sound(animation anim,char* name,bool with_sound){
            return splashkit_lib::assign_animation(anim,(string)name,with_sound);
        }

        animation create_animation_from_index_with_sound(animation_script script,int idx,bool with_sound){
            return splashkit_lib::create_animation(script,idx,with_sound);
        }

        animation create_animation(animation_script script,char*& name){
            return splashkit_lib::create_animation(script,(string)name);
        }

        animation create_animation_with_sound(animation_script script,char*& name,bool with_sound){
            return splashkit_lib::create_animation(script,(string)name,with_sound);
        }

        animation create_animation_from_script_named(char*& script_name,char*& name){
            return splashkit_lib::create_animation((string)script_name,(string)name);
        }

        animation create_animation_from_script_named_with_sound(char*& script_name,char*& name,bool with_sound){
            return splashkit_lib::create_animation((string)script_name,(string)name,with_sound);
        }

        void free_all_animation_scripts(){
            return splashkit_lib::free_all_animation_scripts();
        }

        void free_animation(animation ani){
            return splashkit_lib::free_animation(ani);
        }

        void free_animation_script(animation_script script_to_free){
            return splashkit_lib::free_animation_script(script_to_free);
        }

        void free_animation_script_with_name(char*& name){
            return splashkit_lib::free_animation_script((string)name);
        }

        bool has_animation_named(animation_script script,char*& name){
            return splashkit_lib::has_animation_named(script,(string)name);
        }

        bool has_animation_script(char*& name){
            return splashkit_lib::has_animation_script((string)name);
        }

        animation_script load_animation_script(char*& name,char*& filename){
            return splashkit_lib::load_animation_script((string)name,(string)filename);
        }

        void restart_animation(animation anim){
            return splashkit_lib::restart_animation(anim);
        }

        void restart_animation_with_sound(animation anim,bool with_sound){
            return splashkit_lib::restart_animation(anim,with_sound);
        }

        void update_animation_percent_with_sound(animation anim,float pct,bool with_sound){
            return splashkit_lib::update_animation(anim,pct,with_sound);
        }

        void update_animation(animation anim){
            return splashkit_lib::update_animation(anim);
        }

        void update_animation_percent(animation anim,float pct){
            return splashkit_lib::update_animation(anim,pct);
        }

        void fade_music_in_named(char*& name,int ms){
            return splashkit_lib::fade_music_in((string)name,ms);
        }

        void fade_music_in_named_with_times(char*& name,int times,int ms){
            return splashkit_lib::fade_music_in((string)name,times,ms);
        }

        void fade_music_in(music data,int ms){
            return splashkit_lib::fade_music_in(data,ms);
        }

        void fade_music_in_with_times(music data,int times,int ms){
            return splashkit_lib::fade_music_in(data,times,ms);
        }

        void fade_music_out(int ms){
            return splashkit_lib::fade_music_out(ms);
        }

        void free_all_music(){
            return splashkit_lib::free_all_music();
        }

        void free_music(music effect){
            return splashkit_lib::free_music(effect);
        }

        bool has_music(char*& name){
            return splashkit_lib::has_music((string)name);
        }

        music load_music(char*& name,char*& filename){
            return splashkit_lib::load_music((string)name,(string)filename);
        }

        char* music_filename(music data){
            return outputCStr(splashkit_lib::music_filename(data));
        }

        char* music_name(music data){
            return outputCStr(splashkit_lib::music_name(data));
        }

        music music_named(char*& name){
            return splashkit_lib::music_named((string)name);
        }

        bool music_playing(){
            return splashkit_lib::music_playing();
        }

        float music_volume(){
            return splashkit_lib::music_volume();
        }

        void pause_music(){
            return splashkit_lib::pause_music();
        }

        void play_music_named(char*& name){
            return splashkit_lib::play_music((string)name);
        }

        void play_music_named_with_times(char*& name,int times){
            return splashkit_lib::play_music((string)name,times);
        }

        void play_music(music data){
            return splashkit_lib::play_music(data);
        }

        void play_music_with_times(music data,int times){
            return splashkit_lib::play_music(data,times);
        }

        void play_music_with_times_and_volume(music data,int times,float volume){
            return splashkit_lib::play_music(data,times,volume);
        }

        void resume_music(){
            return splashkit_lib::resume_music();
        }

        void set_music_volume(float volume){
            return splashkit_lib::set_music_volume(volume);
        }

        void stop_music(){
            return splashkit_lib::stop_music();
        }

        void fade_all_sound_effects_out(int ms){
            return splashkit_lib::fade_all_sound_effects_out(ms);
        }

        void fade_sound_effect_out(sound_effect effect,int ms){
            return splashkit_lib::fade_sound_effect_out(effect,ms);
        }

        void free_all_sound_effects(){
            return splashkit_lib::free_all_sound_effects();
        }

        void free_sound_effect(sound_effect effect){
            return splashkit_lib::free_sound_effect(effect);
        }

        bool has_sound_effect(char*& name){
            return splashkit_lib::has_sound_effect((string)name);
        }

        sound_effect load_sound_effect(char*& name,char*& filename){
            return splashkit_lib::load_sound_effect((string)name,(string)filename);
        }

        void play_sound_effect_named(char*& name){
            return splashkit_lib::play_sound_effect((string)name);
        }

        void play_sound_effect_named_with_volume(char*& name,float volume){
            return splashkit_lib::play_sound_effect((string)name,volume);
        }

        void play_sound_effect_named_with_times(char*& name,int times){
            return splashkit_lib::play_sound_effect((string)name,times);
        }

        void play_sound_effect_named_with_times_and_volume(char*& name,int times,float volume){
            return splashkit_lib::play_sound_effect((string)name,times,volume);
        }

        void play_sound_effect(sound_effect effect){
            return splashkit_lib::play_sound_effect(effect);
        }

        void play_sound_effect_with_volume(sound_effect effect,float volume){
            return splashkit_lib::play_sound_effect(effect,volume);
        }

        void play_sound_effect_with_times(sound_effect effect,int times){
            return splashkit_lib::play_sound_effect(effect,times);
        }

        void play_sound_effect_with_times_and_volume(sound_effect effect,int times,float volume){
            return splashkit_lib::play_sound_effect(effect,times,volume);
        }

        char* sound_effect_filename(sound_effect effect){
            return outputCStr(splashkit_lib::sound_effect_filename(effect));
        }

        char* sound_effect_name(sound_effect effect){
            return outputCStr(splashkit_lib::sound_effect_name(effect));
        }

        sound_effect sound_effect_named(char*& name){
            return splashkit_lib::sound_effect_named((string)name);
        }

        bool sound_effect_playing_named(char*& name){
            return splashkit_lib::sound_effect_playing((string)name);
        }

        bool sound_effect_playing(sound_effect effect){
            return splashkit_lib::sound_effect_playing(effect);
        }

        void stop_sound_effect_named(char*& name){
            return splashkit_lib::stop_sound_effect((string)name);
        }

        void stop_sound_effect(sound_effect effect){
            return splashkit_lib::stop_sound_effect(effect);
        }

        bool audio_ready(){
            return splashkit_lib::audio_ready();
        }

        void close_audio(){
            return splashkit_lib::close_audio();
        }

        void open_audio(){
            return splashkit_lib::open_audio();
        }

        point_2d camera_position(){
            return splashkit_lib::camera_position();
        }

        double camera_x(){
            return splashkit_lib::camera_x();
        }

        double camera_y(){
            return splashkit_lib::camera_y();
        }

        void center_camera_on_vector(sprite s,vector_2d& offset){
            return splashkit_lib::center_camera_on(s,offset);
        }

        void center_camera_on(sprite s,double offset_x,double offset_y){
            return splashkit_lib::center_camera_on(s,offset_x,offset_y);
        }

        void move_camera_by_vector(vector_2d& offset){
            return splashkit_lib::move_camera_by(offset);
        }

        void move_camera_by(double dx,double dy){
            return splashkit_lib::move_camera_by(dx,dy);
        }

        void move_camera_to_point(point_2d& pt){
            return splashkit_lib::move_camera_to(pt);
        }

        void move_camera_to(double x,double y){
            return splashkit_lib::move_camera_to(x,y);
        }

        bool point_in_window(window wind,point_2d& pt){
            return splashkit_lib::point_in_window(wind,pt);
        }

        bool point_on_screen(point_2d& pt){
            return splashkit_lib::point_on_screen(pt);
        }

        bool rect_in_window(window wind,rectangle& rect){
            return splashkit_lib::rect_in_window(wind,rect);
        }

        bool rect_on_screen(rectangle& rect){
            return splashkit_lib::rect_on_screen(rect);
        }

        point_2d screen_center(){
            return splashkit_lib::screen_center();
        }

        rectangle screen_rectangle(){
            return splashkit_lib::screen_rectangle();
        }

        void set_camera_position(point_2d pos){
            return splashkit_lib::set_camera_position(pos);
        }

        void set_camera_x(double x){
            return splashkit_lib::set_camera_x(x);
        }

        void set_camera_y(double y){
            return splashkit_lib::set_camera_y(y);
        }

        point_2d to_screen_point(point_2d& pt){
            return splashkit_lib::to_screen(pt);
        }

        rectangle to_screen_rectangle(rectangle& rect){
            return splashkit_lib::to_screen(rect);
        }

        double to_screen_x(double world_x){
            return splashkit_lib::to_screen_x(world_x);
        }

        double to_screen_y(double world_y){
            return splashkit_lib::to_screen_y(world_y);
        }

        point_2d to_world(point_2d& pt){
            return splashkit_lib::to_world(pt);
        }

        double to_world_x(double screen_x){
            return splashkit_lib::to_world_x(screen_x);
        }

        double to_world_y(double screen_y){
            return splashkit_lib::to_world_y(screen_y);
        }

        vector_2d vector_world_to_screen(){
            return splashkit_lib::vector_world_to_screen();
        }

        rectangle window_area(window wind){
            return splashkit_lib::window_area(wind);
        }

        int alpha_of(color c){
            return splashkit_lib::alpha_of(c);
        }

        int blue_of(color c){
            return splashkit_lib::blue_of(c);
        }

        double brightness_of(color c){
            return splashkit_lib::brightness_of(c);
        }

        color color_alice_blue(){
            return splashkit_lib::color_alice_blue();
        }

        color color_antique_white(){
            return splashkit_lib::color_antique_white();
        }

        color color_aqua(){
            return splashkit_lib::color_aqua();
        }

        color color_aquamarine(){
            return splashkit_lib::color_aquamarine();
        }

        color color_azure(){
            return splashkit_lib::color_azure();
        }

        color color_beige(){
            return splashkit_lib::color_beige();
        }

        color color_bisque(){
            return splashkit_lib::color_bisque();
        }

        color color_black(){
            return splashkit_lib::color_black();
        }

        color color_blanched_almond(){
            return splashkit_lib::color_blanched_almond();
        }

        color color_blue(){
            return splashkit_lib::color_blue();
        }

        color color_blue_violet(){
            return splashkit_lib::color_blue_violet();
        }

        color color_bright_green(){
            return splashkit_lib::color_bright_green();
        }

        color color_brown(){
            return splashkit_lib::color_brown();
        }

        color color_burly_wood(){
            return splashkit_lib::color_burly_wood();
        }

        color color_cadet_blue(){
            return splashkit_lib::color_cadet_blue();
        }

        color color_chartreuse(){
            return splashkit_lib::color_chartreuse();
        }

        color color_chocolate(){
            return splashkit_lib::color_chocolate();
        }

        color color_coral(){
            return splashkit_lib::color_coral();
        }

        color color_cornflower_blue(){
            return splashkit_lib::color_cornflower_blue();
        }

        color color_cornsilk(){
            return splashkit_lib::color_cornsilk();
        }

        color color_crimson(){
            return splashkit_lib::color_crimson();
        }

        color color_cyan(){
            return splashkit_lib::color_cyan();
        }

        color color_dark_blue(){
            return splashkit_lib::color_dark_blue();
        }

        color color_dark_cyan(){
            return splashkit_lib::color_dark_cyan();
        }

        color color_dark_goldenrod(){
            return splashkit_lib::color_dark_goldenrod();
        }

        color color_dark_gray(){
            return splashkit_lib::color_dark_gray();
        }

        color color_dark_green(){
            return splashkit_lib::color_dark_green();
        }

        color color_dark_khaki(){
            return splashkit_lib::color_dark_khaki();
        }

        color color_dark_magenta(){
            return splashkit_lib::color_dark_magenta();
        }

        color color_dark_olive_green(){
            return splashkit_lib::color_dark_olive_green();
        }

        color color_dark_orange(){
            return splashkit_lib::color_dark_orange();
        }

        color color_dark_orchid(){
            return splashkit_lib::color_dark_orchid();
        }

        color color_dark_red(){
            return splashkit_lib::color_dark_red();
        }

        color color_dark_salmon(){
            return splashkit_lib::color_dark_salmon();
        }

        color color_dark_sea_green(){
            return splashkit_lib::color_dark_sea_green();
        }

        color color_dark_slate_blue(){
            return splashkit_lib::color_dark_slate_blue();
        }

        color color_dark_slate_gray(){
            return splashkit_lib::color_dark_slate_gray();
        }

        color color_dark_turquoise(){
            return splashkit_lib::color_dark_turquoise();
        }

        color color_dark_violet(){
            return splashkit_lib::color_dark_violet();
        }

        color color_deep_pink(){
            return splashkit_lib::color_deep_pink();
        }

        color color_deep_sky_blue(){
            return splashkit_lib::color_deep_sky_blue();
        }

        color color_dim_gray(){
            return splashkit_lib::color_dim_gray();
        }

        color color_dodger_blue(){
            return splashkit_lib::color_dodger_blue();
        }

        color color_firebrick(){
            return splashkit_lib::color_firebrick();
        }

        color color_floral_white(){
            return splashkit_lib::color_floral_white();
        }

        color color_forest_green(){
            return splashkit_lib::color_forest_green();
        }

        color color_fuchsia(){
            return splashkit_lib::color_fuchsia();
        }

        color color_gainsboro(){
            return splashkit_lib::color_gainsboro();
        }

        color color_ghost_white(){
            return splashkit_lib::color_ghost_white();
        }

        color color_gold(){
            return splashkit_lib::color_gold();
        }

        color color_goldenrod(){
            return splashkit_lib::color_goldenrod();
        }

        color color_gray(){
            return splashkit_lib::color_gray();
        }

        color color_green(){
            return splashkit_lib::color_green();
        }

        color color_green_yellow(){
            return splashkit_lib::color_green_yellow();
        }

        color color_honeydew(){
            return splashkit_lib::color_honeydew();
        }

        color color_hot_pink(){
            return splashkit_lib::color_hot_pink();
        }

        color color_indian_red(){
            return splashkit_lib::color_indian_red();
        }

        color color_indigo(){
            return splashkit_lib::color_indigo();
        }

        color color_ivory(){
            return splashkit_lib::color_ivory();
        }

        color color_khaki(){
            return splashkit_lib::color_khaki();
        }

        color color_lavender(){
            return splashkit_lib::color_lavender();
        }

        color color_lavender_blush(){
            return splashkit_lib::color_lavender_blush();
        }

        color color_lawn_green(){
            return splashkit_lib::color_lawn_green();
        }

        color color_lemon_chiffon(){
            return splashkit_lib::color_lemon_chiffon();
        }

        color color_light_blue(){
            return splashkit_lib::color_light_blue();
        }

        color color_light_coral(){
            return splashkit_lib::color_light_coral();
        }

        color color_light_cyan(){
            return splashkit_lib::color_light_cyan();
        }

        color color_light_goldenrod_yellow(){
            return splashkit_lib::color_light_goldenrod_yellow();
        }

        color color_light_gray(){
            return splashkit_lib::color_light_gray();
        }

        color color_light_green(){
            return splashkit_lib::color_light_green();
        }

        color color_light_pink(){
            return splashkit_lib::color_light_pink();
        }

        color color_light_salmon(){
            return splashkit_lib::color_light_salmon();
        }

        color color_light_sea_green(){
            return splashkit_lib::color_light_sea_green();
        }

        color color_light_sky_blue(){
            return splashkit_lib::color_light_sky_blue();
        }

        color color_light_slate_gray(){
            return splashkit_lib::color_light_slate_gray();
        }

        color color_light_steel_blue(){
            return splashkit_lib::color_light_steel_blue();
        }

        color color_light_yellow(){
            return splashkit_lib::color_light_yellow();
        }

        color color_lime(){
            return splashkit_lib::color_lime();
        }

        color color_lime_green(){
            return splashkit_lib::color_lime_green();
        }

        color color_linen(){
            return splashkit_lib::color_linen();
        }

        color color_magenta(){
            return splashkit_lib::color_magenta();
        }

        color color_maroon(){
            return splashkit_lib::color_maroon();
        }

        color color_medium_aquamarine(){
            return splashkit_lib::color_medium_aquamarine();
        }

        color color_medium_blue(){
            return splashkit_lib::color_medium_blue();
        }

        color color_medium_orchid(){
            return splashkit_lib::color_medium_orchid();
        }

        color color_medium_purple(){
            return splashkit_lib::color_medium_purple();
        }

        color color_medium_sea_green(){
            return splashkit_lib::color_medium_sea_green();
        }

        color color_medium_slate_blue(){
            return splashkit_lib::color_medium_slate_blue();
        }

        color color_medium_spring_green(){
            return splashkit_lib::color_medium_spring_green();
        }

        color color_medium_turquoise(){
            return splashkit_lib::color_medium_turquoise();
        }

        color color_medium_violet_red(){
            return splashkit_lib::color_medium_violet_red();
        }

        color color_midnight_blue(){
            return splashkit_lib::color_midnight_blue();
        }

        color color_mint_cream(){
            return splashkit_lib::color_mint_cream();
        }

        color color_misty_rose(){
            return splashkit_lib::color_misty_rose();
        }

        color color_moccasin(){
            return splashkit_lib::color_moccasin();
        }

        color color_navajo_white(){
            return splashkit_lib::color_navajo_white();
        }

        color color_navy(){
            return splashkit_lib::color_navy();
        }

        color color_old_lace(){
            return splashkit_lib::color_old_lace();
        }

        color color_olive(){
            return splashkit_lib::color_olive();
        }

        color color_olive_drab(){
            return splashkit_lib::color_olive_drab();
        }

        color color_orange(){
            return splashkit_lib::color_orange();
        }

        color color_orange_red(){
            return splashkit_lib::color_orange_red();
        }

        color color_orchid(){
            return splashkit_lib::color_orchid();
        }

        color color_pale_goldenrod(){
            return splashkit_lib::color_pale_goldenrod();
        }

        color color_pale_green(){
            return splashkit_lib::color_pale_green();
        }

        color color_pale_turquoise(){
            return splashkit_lib::color_pale_turquoise();
        }

        color color_pale_violet_red(){
            return splashkit_lib::color_pale_violet_red();
        }

        color color_papaya_whip(){
            return splashkit_lib::color_papaya_whip();
        }

        color color_peach_puff(){
            return splashkit_lib::color_peach_puff();
        }

        color color_peru(){
            return splashkit_lib::color_peru();
        }

        color color_pink(){
            return splashkit_lib::color_pink();
        }

        color color_plum(){
            return splashkit_lib::color_plum();
        }

        color color_powder_blue(){
            return splashkit_lib::color_powder_blue();
        }

        color color_purple(){
            return splashkit_lib::color_purple();
        }

        color color_red(){
            return splashkit_lib::color_red();
        }

        color color_rosy_brown(){
            return splashkit_lib::color_rosy_brown();
        }

        color color_royal_blue(){
            return splashkit_lib::color_royal_blue();
        }

        color color_saddle_brown(){
            return splashkit_lib::color_saddle_brown();
        }

        color color_salmon(){
            return splashkit_lib::color_salmon();
        }

        color color_sandy_brown(){
            return splashkit_lib::color_sandy_brown();
        }

        color color_sea_green(){
            return splashkit_lib::color_sea_green();
        }

        color color_sea_shell(){
            return splashkit_lib::color_sea_shell();
        }

        color color_sienna(){
            return splashkit_lib::color_sienna();
        }

        color color_silver(){
            return splashkit_lib::color_silver();
        }

        color color_sky_blue(){
            return splashkit_lib::color_sky_blue();
        }

        color color_slate_blue(){
            return splashkit_lib::color_slate_blue();
        }

        color color_slate_gray(){
            return splashkit_lib::color_slate_gray();
        }

        color color_snow(){
            return splashkit_lib::color_snow();
        }

        color color_spring_green(){
            return splashkit_lib::color_spring_green();
        }

        color color_steel_blue(){
            return splashkit_lib::color_steel_blue();
        }

        color color_swinburne_red(){
            return splashkit_lib::color_swinburne_red();
        }

        color color_tan(){
            return splashkit_lib::color_tan();
        }

        color color_teal(){
            return splashkit_lib::color_teal();
        }

        color color_thistle(){
            return splashkit_lib::color_thistle();
        }

        char* color_to_string(color c){
            return outputCStr(splashkit_lib::color_to_string(c));
        }

        color color_tomato(){
            return splashkit_lib::color_tomato();
        }

        color color_transparent(){
            return splashkit_lib::color_transparent();
        }

        color color_turquoise(){
            return splashkit_lib::color_turquoise();
        }

        color color_violet(){
            return splashkit_lib::color_violet();
        }

        color color_wheat(){
            return splashkit_lib::color_wheat();
        }

        color color_white(){
            return splashkit_lib::color_white();
        }

        color color_white_smoke(){
            return splashkit_lib::color_white_smoke();
        }

        color color_yellow(){
            return splashkit_lib::color_yellow();
        }

        color color_yellow_green(){
            return splashkit_lib::color_yellow_green();
        }

        int green_of(color c){
            return splashkit_lib::green_of(c);
        }

        color hsb_color(double hue,double saturation,double brightness){
            return splashkit_lib::hsb_color(hue,saturation,brightness);
        }

        double hue_of(color c){
            return splashkit_lib::hue_of(c);
        }

        color random_color(){
            return splashkit_lib::random_color();
        }

        color random_rgb_color(int alpha){
            return splashkit_lib::random_rgb_color(alpha);
        }

        int red_of(color c){
            return splashkit_lib::red_of(c);
        }

        color rgb_color_from_double(double red,double green,double blue){
            return splashkit_lib::rgb_color(red,green,blue);
        }

        color rgb_color(int red,int green,int blue){
            return splashkit_lib::rgb_color(red,green,blue);
        }

        color rgba_color_from_double(double red,double green,double blue,double alpha){
            return splashkit_lib::rgba_color(red,green,blue,alpha);
        }

        color rgba_color(int red,int green,int blue,int alpha){
            return splashkit_lib::rgba_color(red,green,blue,alpha);
        }

        double saturation_of(color c){
            return splashkit_lib::saturation_of(c);
        }

        color string_to_color(char* str){
            return splashkit_lib::string_to_color((string)str);
        }

        database database_named(char* name){
            return splashkit_lib::database_named((string)name);
        }

        char* error_message(query_result query){
            return outputCStr(splashkit_lib::error_message(query));
        }

        void free_all_databases(){
            return splashkit_lib::free_all_databases();
        }

        void free_all_query_results(){
            return splashkit_lib::free_all_query_results();
        }

        void free_database(database db_to_close){
            return splashkit_lib::free_database(db_to_close);
        }

        void free_database_named(char* name_of_db_to_close){
            return splashkit_lib::free_database((string)name_of_db_to_close);
        }

        void free_query_result(query_result query){
            return splashkit_lib::free_query_result(query);
        }

        bool get_next_row(query_result db_result){
            return splashkit_lib::get_next_row(db_result);
        }

        bool has_database(char* name){
            return splashkit_lib::has_database((string)name);
        }

        bool has_row(query_result db_result){
            return splashkit_lib::has_row(db_result);
        }

        database open_database(char* name,char* filename){
            return splashkit_lib::open_database((string)name,(string)filename);
        }

        int query_column_count(query_result db_result){
            return splashkit_lib::query_column_count(db_result);
        }

        bool query_column_for_bool(query_result db_result,int col){
            return splashkit_lib::query_column_for_bool(db_result,col);
        }

        double query_column_for_double(query_result db_result,int col){
            return splashkit_lib::query_column_for_double(db_result,col);
        }

        int query_column_for_int(query_result db_result,int col){
            return splashkit_lib::query_column_for_int(db_result,col);
        }

        char* query_column_for_string(query_result db_result,int col){
            return outputCStr(splashkit_lib::query_column_for_string(db_result,col));
        }

        bool query_success(query_result db_result){
            return splashkit_lib::query_success(db_result);
        }

        char* query_type_of_col(query_result db_result,int col){
            return outputCStr(splashkit_lib::query_type_of_col(db_result,col));
        }

        void reset_query_result(query_result db_result){
            return splashkit_lib::reset_query_result(db_result);
        }

        int rows_changed(database db){
            return splashkit_lib::rows_changed(db);
        }

        query_result run_sql(database db,char* sql){
            return splashkit_lib::run_sql(db,(string)sql);
        }

        query_result run_sql_from_name(char* database_name,char* sql){
            return splashkit_lib::run_sql((string)database_name,(string)sql);
        }

        point_2d closest_point_on_line(point_2d from_pt,line& l){
            return splashkit_lib::closest_point_on_line(from_pt,l);
        }

        point_2d closest_point_on_lines(point_2d from_pt,line**& lines,int& line_idx){
            return splashkit_lib::closest_point_on_lines(from_pt,inputArrayToVector(lines),line_idx);
        }

        line line_from_point_to_point(point_2d& start,point_2d& end_pt){
            return splashkit_lib::line_from(start,end_pt);
        }

        line line_from_start_with_offset(point_2d& start,vector_2d& offset){
            return splashkit_lib::line_from(start,offset);
        }

        line line_from_vector(vector_2d& v){
            return splashkit_lib::line_from(v);
        }

        line line_from(double x1,double y1,double x2,double y2){
            return splashkit_lib::line_from(x1,y1,x2,y2);
        }

        bool line_intersection_point(line& line1,line& line2,point_2d& pt){
            return splashkit_lib::line_intersection_point(line1,line2,pt);
        }

        bool line_intersects_circle(line& l,circle& c){
            return splashkit_lib::line_intersects_circle(l,c);
        }

        bool line_intersects_lines(line& l,line**& lines){
            return splashkit_lib::line_intersects_lines(l,inputArrayToVector(lines));
        }

        bool line_intersects_rect(line& l,rectangle& rect){
            return splashkit_lib::line_intersects_rect(l,rect);
        }

        float line_length(line& l){
            return splashkit_lib::line_length(l);
        }

        float line_length_squared(line& l){
            return splashkit_lib::line_length_squared(l);
        }

        point_2d line_mid_point(line& l){
            return splashkit_lib::line_mid_point(l);
        }

        vector_2d line_normal(line& l){
            return splashkit_lib::line_normal(l);
        }

        char* line_to_string(line& ln){
            return outputCStr(splashkit_lib::line_to_string(ln));
        }

        bool lines_intersect(line& l1,line& l2){
            return splashkit_lib::lines_intersect(l1,l2);
        }

        rectangle inset_rectangle(rectangle& rect,float inset_amount){
            return splashkit_lib::inset_rectangle(rect,inset_amount);
        }

        rectangle intersection(rectangle& rect1,rectangle& rect2){
            return splashkit_lib::intersection(rect1,rect2);
        }

        rectangle rectangle_around_circle(circle& c){
            return splashkit_lib::rectangle_around(c);
        }

        rectangle rectangle_around_line(line& l){
            return splashkit_lib::rectangle_around(l);
        }

        rectangle rectangle_around_quad(quad& q){
            return splashkit_lib::rectangle_around(q);
        }

        rectangle rectangle_around_triangle(triangle& t){
            return splashkit_lib::rectangle_around(t);
        }

        float rectangle_bottom(rectangle& rect){
            return splashkit_lib::rectangle_bottom(rect);
        }

        point_2d rectangle_center(rectangle& rect){
            return splashkit_lib::rectangle_center(rect);
        }

        rectangle rectangle_from_point_and_size(point_2d pt,double width,double height){
            return splashkit_lib::rectangle_from(pt,width,height);
        }

        rectangle rectangle_from_points(point_2d pt1,point_2d pt2){
            return splashkit_lib::rectangle_from(pt1,pt2);
        }

        rectangle rectangle_from(double x,double y,double width,double height){
            return splashkit_lib::rectangle_from(x,y,width,height);
        }

        float rectangle_left(rectangle& rect){
            return splashkit_lib::rectangle_left(rect);
        }

        rectangle rectangle_offset_by(rectangle& rect,vector_2d& offset){
            return splashkit_lib::rectangle_offset_by(rect,offset);
        }

        float rectangle_right(rectangle& rect){
            return splashkit_lib::rectangle_right(rect);
        }

        char* rectangle_to_string(rectangle& rect){
            return outputCStr(splashkit_lib::rectangle_to_string(rect));
        }

        float rectangle_top(rectangle& rect){
            return splashkit_lib::rectangle_top(rect);
        }

        bool rectangles_intersect(rectangle& rect1,rectangle& rect2){
            return splashkit_lib::rectangles_intersect(rect1,rect2);
        }

        point_2d triangle_barycenter(triangle& tri){
            return splashkit_lib::triangle_barycenter(tri);
        }

        triangle triangle_from(point_2d& p1,point_2d& p2,point_2d& p3){
            return splashkit_lib::triangle_from(p1,p2,p3);
        }

        triangle triangle_from__from_coordinates(double x1,double y1,double x2,double y2,double x3,double y3){
            return splashkit_lib::triangle_from(x1,y1,x2,y2,x3,y3);
        }

        bool triangle_rectangle_intersect(triangle& tri,rectangle& rect){
            return splashkit_lib::triangle_rectangle_intersect(tri,rect);
        }

        char* triangle_to_string(triangle& tri){
            return outputCStr(splashkit_lib::triangle_to_string(tri));
        }

        bool triangles_intersect(triangle& t1,triangle& t2){
            return splashkit_lib::triangles_intersect(t1,t2);
        }

        point_2d point_at(double x,double y){
            return splashkit_lib::point_at(x,y);
        }

        point_2d point_at_origin(){
            return splashkit_lib::point_at_origin();
        }

        bool point_in_circle(point_2d& pt,circle& c){
            return splashkit_lib::point_in_circle(pt,c);
        }

        bool point_in_quad(point_2d& pt,quad& q){
            return splashkit_lib::point_in_quad(pt,q);
        }

        bool point_in_rectangle(point_2d& pt,rectangle& rect){
            return splashkit_lib::point_in_rectangle(pt,rect);
        }

        bool point_in_triangle(point_2d& pt,triangle& tri){
            return splashkit_lib::point_in_triangle(pt,tri);
        }

        float point_line_distance(point_2d& pt,line& l){
            return splashkit_lib::point_line_distance(pt,l);
        }

        point_2d point_offset_by(point_2d& start_point,vector_2d& offset){
            return splashkit_lib::point_offset_by(start_point,offset);
        }

        point_2d point_offset_from_origin(vector_2d& offset){
            return splashkit_lib::point_offset_from_origin(offset);
        }

        bool point_on_line(point_2d& pt,line& l){
            return splashkit_lib::point_on_line(pt,l);
        }

        bool point_on_line_with_proximity(point_2d& pt,line& l,float proximity){
            return splashkit_lib::point_on_line(pt,l,proximity);
        }

        float point_point_angle(point_2d& pt1,point_2d& pt2){
            return splashkit_lib::point_point_angle(pt1,pt2);
        }

        float point_point_distance(point_2d& pt1,point_2d& pt2){
            return splashkit_lib::point_point_distance(pt1,pt2);
        }

        char* point_to_string(point_2d& pt){
            return outputCStr(splashkit_lib::point_to_string(pt));
        }

        point_2d random_bitmap_point(bitmap bmp){
            return splashkit_lib::random_bitmap_point(bmp);
        }

        point_2d random_screen_point(){
            return splashkit_lib::random_screen_point();
        }

        point_2d random_window_point(window wind){
            return splashkit_lib::random_window_point(wind);
        }

        bool same_point(point_2d& pt1,point_2d& pt2){
            return splashkit_lib::same_point(pt1,pt2);
        }

        point_2d center_point_circle(circle& c){
            return splashkit_lib::center_point(c);
        }

        circle circle_at(point_2d& pt,double radius){
            return splashkit_lib::circle_at(pt,radius);
        }

        circle circle_at_from_points(double x,double y,double radius){
            return splashkit_lib::circle_at(x,y,radius);
        }

        float circle_radius(circle c){
            return splashkit_lib::circle_radius(c);
        }

        float circle_x(circle& c){
            return splashkit_lib::circle_x(c);
        }

        float circle_y(circle& c){
            return splashkit_lib::circle_y(c);
        }

        bool circles_intersect(circle c1,circle c2){
            return splashkit_lib::circles_intersect(c1,c2);
        }

        point_2d closest_point_on_circle(point_2d& from_pt,circle& c){
            return splashkit_lib::closest_point_on_circle(from_pt,c);
        }

        point_2d closest_point_on_line_from_circle(circle& c,line& l){
            return splashkit_lib::closest_point_on_line_from_circle(c,l);
        }

        point_2d closest_point_on_rect_from_circle(circle& c,rectangle& rect){
            return splashkit_lib::closest_point_on_rect_from_circle(c,rect);
        }

        point_2d distant_point_on_circle(point_2d& pt,circle& c){
            return splashkit_lib::distant_point_on_circle(pt,c);
        }

        bool distant_point_on_circle_heading(point_2d& pt,circle& c,vector_2d& heading,point_2d& opposite_pt){
            return splashkit_lib::distant_point_on_circle_heading(pt,c,heading,opposite_pt);
        }

        float ray_circle_intersect_distance(point_2d& ray_origin,vector_2d& ray_heading,circle& c){
            return splashkit_lib::ray_circle_intersect_distance(ray_origin,ray_heading,c);
        }

        bool tangent_points(point_2d& from_pt,circle& c,point_2d& p1,point_2d& p2){
            return splashkit_lib::tangent_points(from_pt,c,p1,p2);
        }

        void widest_points(circle& c,vector_2d& along,point_2d& pt1,point_2d& pt2){
            return splashkit_lib::widest_points(c,along,pt1,pt2);
        }

        quad quad_from_points(point_2d& p1,point_2d& p2,point_2d& p3,point_2d& p4){
            return splashkit_lib::quad_from(p1,p2,p3,p4);
        }

        quad quad_from_rectangle(rectangle& rect){
            return splashkit_lib::quad_from(rect);
        }

        quad quad_from_rectangle_with_transformation(rectangle& rect,matrix_2d& transform){
            return splashkit_lib::quad_from(rect,transform);
        }

        quad quad_from(double x_top_left,double y_top_left,double x_top_right,double y_top_right,double x_bottom_left,double y_bottom_left,double x_bottom_right,double y_bottom_right){
            return splashkit_lib::quad_from(x_top_left,y_top_left,x_top_right,y_top_right,x_bottom_left,y_bottom_left,x_bottom_right,y_bottom_right);
        }

        bool quads_intersect(quad& q1,quad& q2){
            return splashkit_lib::quads_intersect(q1,q2);
        }

        void set_quad_point(quad& q,int idx,point_2d& value){
            return splashkit_lib::set_quad_point(q,idx,value);
        }

        float cosine(float degrees){
            return splashkit_lib::cosine(degrees);
        }

        float sine(float degrees){
            return splashkit_lib::sine(degrees);
        }

        float tangent(float degrees){
            return splashkit_lib::tangent(degrees);
        }

        void draw_circle_record(color clr,circle& c){
            return splashkit_lib::draw_circle(clr,c);
        }

        void draw_circle_record_with_options(color clr,circle& c,drawing_options opts){
            return splashkit_lib::draw_circle(clr,c,opts);
        }

        void draw_circle(color clr,double x,double y,double radius){
            return splashkit_lib::draw_circle(clr,x,y,radius);
        }

        void draw_circle_with_options(color clr,double x,double y,double radius,drawing_options opts){
            return splashkit_lib::draw_circle(clr,x,y,radius,opts);
        }

        void draw_circle_on_bitmap(bitmap destination,color clr,double x,double y,double radius){
            return splashkit_lib::draw_circle_on_bitmap(destination,clr,x,y,radius);
        }

        void draw_circle_on_bitmap_with_options(bitmap destination,color clr,double x,double y,double radius,drawing_options opts){
            return splashkit_lib::draw_circle_on_bitmap(destination,clr,x,y,radius,opts);
        }

        void draw_circle_on_window(window destination,color clr,double x,double y,double radius){
            return splashkit_lib::draw_circle_on_window(destination,clr,x,y,radius);
        }

        void draw_circle_on_window_with_options(window destination,color clr,double x,double y,double radius,drawing_options opts){
            return splashkit_lib::draw_circle_on_window(destination,clr,x,y,radius,opts);
        }

        void fill_circle_record(color clr,circle& c){
            return splashkit_lib::fill_circle(clr,c);
        }

        void fill_circle_record_with_options(color clr,circle& c,drawing_options opts){
            return splashkit_lib::fill_circle(clr,c,opts);
        }

        void fill_circle(color clr,double x,double y,double radius){
            return splashkit_lib::fill_circle(clr,x,y,radius);
        }

        void fill_circle_with_options(color clr,double x,double y,double radius,drawing_options opts){
            return splashkit_lib::fill_circle(clr,x,y,radius,opts);
        }

        void fill_circle_on_bitmap(bitmap destination,color clr,double x,double y,double radius){
            return splashkit_lib::fill_circle_on_bitmap(destination,clr,x,y,radius);
        }

        void fill_circle_on_bitmap_with_options(bitmap destination,color clr,double x,double y,double radius,drawing_options opts){
            return splashkit_lib::fill_circle_on_bitmap(destination,clr,x,y,radius,opts);
        }

        void fill_circle_on_window(window destination,color clr,double x,double y,double radius){
            return splashkit_lib::fill_circle_on_window(destination,clr,x,y,radius);
        }

        void fill_circle_on_window_with_options(window destination,color clr,double x,double y,double radius,drawing_options opts){
            return splashkit_lib::fill_circle_on_window(destination,clr,x,y,radius,opts);
        }

        void draw_text_font_as_string(char*& text,color& clr,char*& fnt,int font_size,double x,double y){
            return splashkit_lib::draw_text((string)text,clr,(string)fnt,font_size,x,y);
        }

        void draw_text_with_options_font_as_string(char*& text,color& clr,char*& fnt,int font_size,double x,double y,drawing_options& opts){
            return splashkit_lib::draw_text((string)text,clr,(string)fnt,font_size,x,y,opts);
        }

        void draw_text_no_font_no_size(char*& text,color& clr,double x,double y){
            return splashkit_lib::draw_text((string)text,clr,x,y);
        }

        void draw_text_no_font_no_size_with_options(char*& text,color& clr,double x,double y,drawing_options& opts){
            return splashkit_lib::draw_text((string)text,clr,x,y,opts);
        }

        void draw_text(char*& text,color& clr,font fnt,int font_size,double x,double y){
            return splashkit_lib::draw_text((string)text,clr,fnt,font_size,x,y);
        }

        void draw_text_with_options(char*& text,color& clr,font fnt,int font_size,double x,double y,drawing_options& opts){
            return splashkit_lib::draw_text((string)text,clr,fnt,font_size,x,y,opts);
        }

        void draw_text_on_bitmap_font_as_string(bitmap bmp,char*& text,color& clr,char*& fnt,int font_size,double x,double y){
            return splashkit_lib::draw_text_on_bitmap(bmp,(string)text,clr,(string)fnt,font_size,x,y);
        }

        void draw_text_on_bitmap_with_options_font_as_string(bitmap bmp,char*& text,color& clr,char*& fnt,int font_size,double x,double y,drawing_options& opts){
            return splashkit_lib::draw_text_on_bitmap(bmp,(string)text,clr,(string)fnt,font_size,x,y,opts);
        }

        void draw_text_on_bitmap_no_font_no_size(bitmap bmp,char*& text,color& clr,double x,double y){
            return splashkit_lib::draw_text_on_bitmap(bmp,(string)text,clr,x,y);
        }

        void draw_text_on_bitmap_no_font_no_size_with_options(bitmap bmp,char*& text,color& clr,double x,double y,drawing_options& opts){
            return splashkit_lib::draw_text_on_bitmap(bmp,(string)text,clr,x,y,opts);
        }

        void draw_text_on_bitmap(bitmap bmp,char*& text,color& clr,font fnt,int font_size,double x,double y){
            return splashkit_lib::draw_text_on_bitmap(bmp,(string)text,clr,fnt,font_size,x,y);
        }

        void draw_text_on_bitmap_with_options(bitmap bmp,char*& text,color& clr,font fnt,int font_size,double x,double y,drawing_options& opts){
            return splashkit_lib::draw_text_on_bitmap(bmp,(string)text,clr,fnt,font_size,x,y,opts);
        }

        void draw_text_on_window_font_as_string(window wnd,char*& text,color& clr,char*& fnt,int font_size,double x,double y){
            return splashkit_lib::draw_text_on_window(wnd,(string)text,clr,(string)fnt,font_size,x,y);
        }

        void draw_text_on_window_with_options_font_as_string(window wnd,char*& text,color& clr,char*& fnt,int font_size,double x,double y,drawing_options& opts){
            return splashkit_lib::draw_text_on_window(wnd,(string)text,clr,(string)fnt,font_size,x,y,opts);
        }

        void draw_text_on_window_no_font_no_size(window wnd,char*& text,color& clr,double x,double y){
            return splashkit_lib::draw_text_on_window(wnd,(string)text,clr,x,y);
        }

        void draw_text_on_window_no_font_no_size_with_options(window wnd,char*& text,color& clr,double x,double y,drawing_options& opts){
            return splashkit_lib::draw_text_on_window(wnd,(string)text,clr,x,y,opts);
        }

        void draw_text_on_window(window wnd,char*& text,color& clr,font fnt,int font_size,double x,double y){
            return splashkit_lib::draw_text_on_window(wnd,(string)text,clr,fnt,font_size,x,y);
        }

        void draw_text_on_window_with_options(window wnd,char*& text,color& clr,font fnt,int font_size,double x,double y,drawing_options& opts){
            return splashkit_lib::draw_text_on_window(wnd,(string)text,clr,fnt,font_size,x,y,opts);
        }

        bool font_has_size_name_as_string(char*& name,int font_size){
            return splashkit_lib::font_has_size((string)name,font_size);
        }

        bool font_has_size(font fnt,int font_size){
            return splashkit_lib::font_has_size(fnt,font_size);
        }

        void font_load_size_name_as_string(char*& name,int font_size){
            return splashkit_lib::font_load_size((string)name,font_size);
        }

        void font_load_size(font fnt,int font_size){
            return splashkit_lib::font_load_size(fnt,font_size);
        }

        font font_named(char* name){
            return splashkit_lib::font_named((string)name);
        }

        void free_all_fonts(){
            return splashkit_lib::free_all_fonts();
        }

        void free_font(font fnt){
            return splashkit_lib::free_font(fnt);
        }

        font_style get_font_style_name_as_string(char*& name){
            return splashkit_lib::get_font_style((string)name);
        }

        font_style get_font_style(font fnt){
            return splashkit_lib::get_font_style(fnt);
        }

        bool has_font(font fnt){
            return splashkit_lib::has_font(fnt);
        }

        bool has_font_name_as_string(char* name){
            return splashkit_lib::has_font((string)name);
        }

        font load_font(char*& name,char*& filename){
            return splashkit_lib::load_font((string)name,(string)filename);
        }

        void set_font_style_name_as_string(char*& name,font_style style){
            return splashkit_lib::set_font_style((string)name,style);
        }

        void set_font_style(font fnt,font_style style){
            return splashkit_lib::set_font_style(fnt,style);
        }

        int text_height_font_named(char*& text,char*& fnt,int font_size){
            return splashkit_lib::text_height((string)text,(string)fnt,font_size);
        }

        int text_height(char*& text,font fnt,int font_size){
            return splashkit_lib::text_height((string)text,fnt,font_size);
        }

        int text_width_font_named(char*& text,char*& fnt,int font_size){
            return splashkit_lib::text_width((string)text,(string)fnt,font_size);
        }

        int text_width(char*& text,font fnt,int font_size){
            return splashkit_lib::text_width((string)text,fnt,font_size);
        }

        void draw_quad(color clr,quad& q){
            return splashkit_lib::draw_quad(clr,q);
        }

        void draw_quad_with_options(color clr,quad& q,drawing_options& opts){
            return splashkit_lib::draw_quad(clr,q,opts);
        }

        void draw_quad_on_bitmap(bitmap destination,color clr,quad& q){
            return splashkit_lib::draw_quad_on_bitmap(destination,clr,q);
        }

        void draw_quad_on_bitmap_with_options(bitmap destination,color clr,quad& q,drawing_options& opts){
            return splashkit_lib::draw_quad_on_bitmap(destination,clr,q,opts);
        }

        void draw_quad_on_window(window destination,color clr,quad& q){
            return splashkit_lib::draw_quad_on_window(destination,clr,q);
        }

        void draw_quad_on_window_with_options(window destination,color clr,quad& q,drawing_options& opts){
            return splashkit_lib::draw_quad_on_window(destination,clr,q,opts);
        }

        void draw_rectangle_record(color clr,rectangle& rect){
            return splashkit_lib::draw_rectangle(clr,rect);
        }

        void draw_rectangle_record_with_options(color clr,rectangle& rect,drawing_options& opts){
            return splashkit_lib::draw_rectangle(clr,rect,opts);
        }

        void draw_rectangle(color clr,double x,double y,double width,double height){
            return splashkit_lib::draw_rectangle(clr,x,y,width,height);
        }

        void draw_rectangle_with_options(color clr,double x,double y,double width,double height,drawing_options& opts){
            return splashkit_lib::draw_rectangle(clr,x,y,width,height,opts);
        }

        void draw_rectangle_on_bitmap_record(bitmap destination,color clr,rectangle& rect){
            return splashkit_lib::draw_rectangle_on_bitmap(destination,clr,rect);
        }

        void draw_rectangle_on_bitmap_record_with_options(bitmap destination,color clr,rectangle& rect,drawing_options& opts){
            return splashkit_lib::draw_rectangle_on_bitmap(destination,clr,rect,opts);
        }

        void draw_rectangle_on_bitmap(bitmap destination,color clr,double x,double y,double width,double height){
            return splashkit_lib::draw_rectangle_on_bitmap(destination,clr,x,y,width,height);
        }

        void draw_rectangle_on_bitmap_with_options(bitmap destination,color clr,double x,double y,double width,double height,drawing_options opts){
            return splashkit_lib::draw_rectangle_on_bitmap(destination,clr,x,y,width,height,opts);
        }

        void draw_rectangle_on_window_record(window destination,color clr,rectangle& rect){
            return splashkit_lib::draw_rectangle_on_window(destination,clr,rect);
        }

        void draw_rectangle_on_window_record_with_options(window destination,color clr,rectangle& rect,drawing_options& opts){
            return splashkit_lib::draw_rectangle_on_window(destination,clr,rect,opts);
        }

        void draw_rectangle_on_window(window destination,color clr,double x,double y,double width,double height){
            return splashkit_lib::draw_rectangle_on_window(destination,clr,x,y,width,height);
        }

        void draw_rectangle_on_window_with_options(window destination,color clr,double x,double y,double width,double height,drawing_options opts){
            return splashkit_lib::draw_rectangle_on_window(destination,clr,x,y,width,height,opts);
        }

        void fill_quad(color clr,quad& q){
            return splashkit_lib::fill_quad(clr,q);
        }

        void fill_quad_with_options(color clr,quad& q,drawing_options& opts){
            return splashkit_lib::fill_quad(clr,q,opts);
        }

        void fill_quad_on_bitmap(bitmap destination,color clr,quad& q){
            return splashkit_lib::fill_quad_on_bitmap(destination,clr,q);
        }

        void fill_quad_on_bitmap_with_options(bitmap destination,color clr,quad& q,drawing_options& opts){
            return splashkit_lib::fill_quad_on_bitmap(destination,clr,q,opts);
        }

        void fill_quad_on_window(window destination,color clr,quad& q){
            return splashkit_lib::fill_quad_on_window(destination,clr,q);
        }

        void fill_quad_on_window_with_options(window destination,color clr,quad& q,drawing_options& opts){
            return splashkit_lib::fill_quad_on_window(destination,clr,q,opts);
        }

        void fill_rectangle_record(color clr,rectangle& rect){
            return splashkit_lib::fill_rectangle(clr,rect);
        }

        void fill_rectangle_record_with_options(color clr,rectangle& rect,drawing_options& opts){
            return splashkit_lib::fill_rectangle(clr,rect,opts);
        }

        void fill_rectangle(color clr,double x,double y,double width,double height){
            return splashkit_lib::fill_rectangle(clr,x,y,width,height);
        }

        void fill_rectangle_with_options(color clr,double x,double y,double width,double height,drawing_options& opts){
            return splashkit_lib::fill_rectangle(clr,x,y,width,height,opts);
        }

        void fill_rectangle_on_bitmap_record(bitmap destination,color clr,rectangle& rect){
            return splashkit_lib::fill_rectangle_on_bitmap(destination,clr,rect);
        }

        void fill_rectangle_on_bitmap_record_with_options(bitmap destination,color clr,rectangle& rect,drawing_options& opts){
            return splashkit_lib::fill_rectangle_on_bitmap(destination,clr,rect,opts);
        }

        void fill_rectangle_on_bitmap(bitmap destination,color clr,double x,double y,double width,double height){
            return splashkit_lib::fill_rectangle_on_bitmap(destination,clr,x,y,width,height);
        }

        void fill_rectangle_on_bitmap_with_options(bitmap destination,color clr,double x,double y,double width,double height,drawing_options& opts){
            return splashkit_lib::fill_rectangle_on_bitmap(destination,clr,x,y,width,height,opts);
        }

        void fill_rectangle_on_window_record(window destination,color clr,rectangle& rect){
            return splashkit_lib::fill_rectangle_on_window(destination,clr,rect);
        }

        void fill_rectangle_on_window_record_with_options(window destination,color clr,rectangle& rect,drawing_options& opts){
            return splashkit_lib::fill_rectangle_on_window(destination,clr,rect,opts);
        }

        void fill_rectangle_on_window(window destination,color clr,double x,double y,double width,double height){
            return splashkit_lib::fill_rectangle_on_window(destination,clr,x,y,width,height);
        }

        void fill_rectangle_on_window_with_options(window destination,color clr,double x,double y,double width,double height,drawing_options& opts){
            return splashkit_lib::fill_rectangle_on_window(destination,clr,x,y,width,height,opts);
        }

        rectangle current_clip(){
            return splashkit_lib::current_clip();
        }

        rectangle current_clip_for_bitmap(bitmap bmp){
            return splashkit_lib::current_clip(bmp);
        }

        rectangle current_clip_for_window(window wnd){
            return splashkit_lib::current_clip(wnd);
        }

        void pop_clip_for_window(window wnd){
            return splashkit_lib::pop_clip(wnd);
        }

        void pop_clip(){
            return splashkit_lib::pop_clip();
        }

        void pop_clip_for_bitmap(bitmap bmp){
            return splashkit_lib::pop_clip(bmp);
        }

        void push_clip_for_window(window wnd,rectangle& r){
            return splashkit_lib::push_clip(wnd,r);
        }

        void push_clip_for_bitmap(bitmap bmp,rectangle& r){
            return splashkit_lib::push_clip(bmp,r);
        }

        void push_clip(rectangle& r){
            return splashkit_lib::push_clip(r);
        }

        void reset_clip_for_bitmap(bitmap bmp){
            return splashkit_lib::reset_clip(bmp);
        }

        void reset_clip(){
            return splashkit_lib::reset_clip();
        }

        void reset_clip_for_window(window wnd){
            return splashkit_lib::reset_clip(wnd);
        }

        void set_clip(rectangle& r){
            return splashkit_lib::set_clip(r);
        }

        void set_clip_for_bitmap(bitmap bmp,rectangle& r){
            return splashkit_lib::set_clip(bmp,r);
        }

        void set_clip_for_window(window wnd,rectangle& r){
            return splashkit_lib::set_clip(wnd,r);
        }

        void draw_triangle_record(color clr,triangle& tri){
            return splashkit_lib::draw_triangle(clr,tri);
        }

        void draw_triangle_record_with_options(color clr,triangle& tri,drawing_options opts){
            return splashkit_lib::draw_triangle(clr,tri,opts);
        }

        void draw_triangle(color clr,double x1,double y1,double x2,double y2,double x3,double y3){
            return splashkit_lib::draw_triangle(clr,x1,y1,x2,y2,x3,y3);
        }

        void draw_triangle_with_options(color clr,double x1,double y1,double x2,double y2,double x3,double y3,drawing_options opts){
            return splashkit_lib::draw_triangle(clr,x1,y1,x2,y2,x3,y3,opts);
        }

        void draw_triangle_on_bitmap_record(bitmap destination,color clr,triangle& tri){
            return splashkit_lib::draw_triangle_on_bitmap(destination,clr,tri);
        }

        void draw_triangle_on_bitmap_record_with_options(bitmap destination,color clr,triangle& tri,drawing_options opts){
            return splashkit_lib::draw_triangle_on_bitmap(destination,clr,tri,opts);
        }

        void draw_triangle_on_bitmap(bitmap destination,color clr,double x1,double y1,double x2,double y2,double x3,double y3){
            return splashkit_lib::draw_triangle_on_bitmap(destination,clr,x1,y1,x2,y2,x3,y3);
        }

        void draw_triangle_on_bitmap_with_options(bitmap destination,color clr,double x1,double y1,double x2,double y2,double x3,double y3,drawing_options opts){
            return splashkit_lib::draw_triangle_on_bitmap(destination,clr,x1,y1,x2,y2,x3,y3,opts);
        }

        void draw_triangle_on_window_record(window destination,color clr,triangle& tri){
            return splashkit_lib::draw_triangle_on_window(destination,clr,tri);
        }

        void draw_triangle_on_window_record_with_options(window destination,color clr,triangle& tri,drawing_options opts){
            return splashkit_lib::draw_triangle_on_window(destination,clr,tri,opts);
        }

        void draw_triangle_on_window(window destination,color clr,double x1,double y1,double x2,double y2,double x3,double y3){
            return splashkit_lib::draw_triangle_on_window(destination,clr,x1,y1,x2,y2,x3,y3);
        }

        void draw_triangle_on_window_with_options(window destination,color clr,double x1,double y1,double x2,double y2,double x3,double y3,drawing_options opts){
            return splashkit_lib::draw_triangle_on_window(destination,clr,x1,y1,x2,y2,x3,y3,opts);
        }

        void fill_triangle_record(color clr,triangle& tri){
            return splashkit_lib::fill_triangle(clr,tri);
        }

        void fill_triangle_record_with_options(color clr,triangle& tri,drawing_options opts){
            return splashkit_lib::fill_triangle(clr,tri,opts);
        }

        void fill_triangle(color clr,double x1,double y1,double x2,double y2,double x3,double y3){
            return splashkit_lib::fill_triangle(clr,x1,y1,x2,y2,x3,y3);
        }

        void fill_triangle_with_options(color clr,double x1,double y1,double x2,double y2,double x3,double y3,drawing_options opts){
            return splashkit_lib::fill_triangle(clr,x1,y1,x2,y2,x3,y3,opts);
        }

        void fill_triangle_on_bitmap_record(bitmap destination,color clr,triangle& tri){
            return splashkit_lib::fill_triangle_on_bitmap(destination,clr,tri);
        }

        void fill_triangle_on_bitmap_record_with_options(bitmap destination,color clr,triangle& tri,drawing_options opts){
            return splashkit_lib::fill_triangle_on_bitmap(destination,clr,tri,opts);
        }

        void fill_triangle_on_bitmap(bitmap destination,color clr,double x1,double y1,double x2,double y2,double x3,double y3){
            return splashkit_lib::fill_triangle_on_bitmap(destination,clr,x1,y1,x2,y2,x3,y3);
        }

        void fill_triangle_on_bitmap_with_options(bitmap destination,color clr,double x1,double y1,double x2,double y2,double x3,double y3,drawing_options opts){
            return splashkit_lib::fill_triangle_on_bitmap(destination,clr,x1,y1,x2,y2,x3,y3,opts);
        }

        void fill_triangle_on_window_record(window destination,color clr,triangle& tri){
            return splashkit_lib::fill_triangle_on_window(destination,clr,tri);
        }

        void fill_triangle_on_window_record_with_options(window destination,color clr,triangle& tri,drawing_options opts){
            return splashkit_lib::fill_triangle_on_window(destination,clr,tri,opts);
        }

        void fill_triangle_on_window(window destination,color clr,double x1,double y1,double x2,double y2,double x3,double y3){
            return splashkit_lib::fill_triangle_on_window(destination,clr,x1,y1,x2,y2,x3,y3);
        }

        void fill_triangle_on_window_with_options(window destination,color clr,double x1,double y1,double x2,double y2,double x3,double y3,drawing_options opts){
            return splashkit_lib::fill_triangle_on_window(destination,clr,x1,y1,x2,y2,x3,y3,opts);
        }

        void draw_ellipse_within_rectangle(color clr,rectangle rect){
            return splashkit_lib::draw_ellipse(clr,rect);
        }

        void draw_ellipse_within_rectangle_with_options(color clr,rectangle rect,drawing_options opts){
            return splashkit_lib::draw_ellipse(clr,rect,opts);
        }

        void draw_ellipse(color clr,double x,double y,double width,double height){
            return splashkit_lib::draw_ellipse(clr,x,y,width,height);
        }

        void draw_ellipse_with_options(color clr,double x,double y,double width,double height,drawing_options opts){
            return splashkit_lib::draw_ellipse(clr,x,y,width,height,opts);
        }

        void draw_ellipse_on_bitmap_within_rectangle(bitmap destination,color clr,rectangle rect){
            return splashkit_lib::draw_ellipse_on_bitmap(destination,clr,rect);
        }

        void draw_ellipse_on_bitmap_within_rectangle_with_options(bitmap destination,color clr,rectangle rect,drawing_options opts){
            return splashkit_lib::draw_ellipse_on_bitmap(destination,clr,rect,opts);
        }

        void draw_ellipse_on_bitmap(bitmap destination,color clr,double x,double y,double width,double height){
            return splashkit_lib::draw_ellipse_on_bitmap(destination,clr,x,y,width,height);
        }

        void draw_ellipse_on_bitmap_with_options(bitmap destination,color clr,double x,double y,double width,double height,drawing_options opts){
            return splashkit_lib::draw_ellipse_on_bitmap(destination,clr,x,y,width,height,opts);
        }

        void draw_ellipse_on_window_within_rectangle(window destination,color clr,rectangle rect){
            return splashkit_lib::draw_ellipse_on_window(destination,clr,rect);
        }

        void draw_ellipse_on_window_within_rectangle_with_options(window destination,color clr,rectangle rect,drawing_options opts){
            return splashkit_lib::draw_ellipse_on_window(destination,clr,rect,opts);
        }

        void draw_ellipse_on_window(window destination,color clr,double x,double y,double width,double height){
            return splashkit_lib::draw_ellipse_on_window(destination,clr,x,y,width,height);
        }

        void draw_ellipse_on_window_with_options(window destination,color clr,double x,double y,double width,double height,drawing_options opts){
            return splashkit_lib::draw_ellipse_on_window(destination,clr,x,y,width,height,opts);
        }

        void fill_ellipse_within_rectangle(color clr,rectangle rect){
            return splashkit_lib::fill_ellipse(clr,rect);
        }

        void fill_ellipse_within_rectangle_with_options(color clr,rectangle rect,drawing_options opts){
            return splashkit_lib::fill_ellipse(clr,rect,opts);
        }

        void fill_ellipse(color clr,double x,double y,double width,double height){
            return splashkit_lib::fill_ellipse(clr,x,y,width,height);
        }

        void fill_ellipse_with_options(color clr,double x,double y,double width,double height,drawing_options opts){
            return splashkit_lib::fill_ellipse(clr,x,y,width,height,opts);
        }

        void fill_ellipse_on_bitmap_within_rectangle(bitmap destination,color clr,rectangle rect){
            return splashkit_lib::fill_ellipse_on_bitmap(destination,clr,rect);
        }

        void fill_ellipse_on_bitmap_within_rectangle_with_options(bitmap destination,color clr,rectangle rect,drawing_options opts){
            return splashkit_lib::fill_ellipse_on_bitmap(destination,clr,rect,opts);
        }

        void fill_ellipse_on_bitmap(bitmap destination,color clr,double x,double y,double width,double height){
            return splashkit_lib::fill_ellipse_on_bitmap(destination,clr,x,y,width,height);
        }

        void fill_ellipse_on_bitmap_with_options(bitmap destination,color clr,double x,double y,double width,double height,drawing_options opts){
            return splashkit_lib::fill_ellipse_on_bitmap(destination,clr,x,y,width,height,opts);
        }

        void fill_ellipse_on_window_within_rectangle(window destination,color clr,rectangle rect){
            return splashkit_lib::fill_ellipse_on_window(destination,clr,rect);
        }

        void fill_ellipse_on_window_within_rectangle_with_options(window destination,color clr,rectangle rect,drawing_options opts){
            return splashkit_lib::fill_ellipse_on_window(destination,clr,rect,opts);
        }

        void fill_ellipse_on_window(window destination,color clr,double x,double y,double width,double height){
            return splashkit_lib::fill_ellipse_on_window(destination,clr,x,y,width,height);
        }

        void fill_ellipse_on_window_with_options(window destination,color clr,double x,double y,double width,double height,drawing_options opts){
            return splashkit_lib::fill_ellipse_on_window(destination,clr,x,y,width,height,opts);
        }

        circle bitmap_bounding_circle(bitmap bmp,point_2d& pt){
            return splashkit_lib::bitmap_bounding_circle(bmp,pt);
        }

        rectangle bitmap_bounding_rectangle(bitmap bmp){
            return splashkit_lib::bitmap_bounding_rectangle(bmp);
        }

        rectangle bitmap_bounding_rectangle_at_location(bitmap bmp,double x,double y){
            return splashkit_lib::bitmap_bounding_rectangle(bmp,x,y);
        }

        point_2d bitmap_cell_center(bitmap bmp){
            return splashkit_lib::bitmap_cell_center(bmp);
        }

        circle bitmap_cell_circle(bitmap bmp,double x,double y){
            return splashkit_lib::bitmap_cell_circle(bmp,x,y);
        }

        circle bitmap_cell_circle_at_point(bitmap bmp,point_2d pt){
            return splashkit_lib::bitmap_cell_circle(bmp,pt);
        }

        circle bitmap_cell_circle_at_point_with_scale(bitmap bmp,point_2d pt,double scale){
            return splashkit_lib::bitmap_cell_circle(bmp,pt,scale);
        }

        int bitmap_cell_columns(bitmap bmp){
            return splashkit_lib::bitmap_cell_columns(bmp);
        }

        int bitmap_cell_count(bitmap bmp){
            return splashkit_lib::bitmap_cell_count(bmp);
        }

        int bitmap_cell_height(bitmap bmp){
            return splashkit_lib::bitmap_cell_height(bmp);
        }

        vector_2d bitmap_cell_offset(bitmap src,int cell){
            return splashkit_lib::bitmap_cell_offset(src,cell);
        }

        rectangle bitmap_cell_rectangle(bitmap src){
            return splashkit_lib::bitmap_cell_rectangle(src);
        }

        rectangle bitmap_cell_rectangle_at_point(bitmap src,point_2d& pt){
            return splashkit_lib::bitmap_cell_rectangle(src,pt);
        }

        int bitmap_cell_rows(bitmap bmp){
            return splashkit_lib::bitmap_cell_rows(bmp);
        }

        int bitmap_cell_width(bitmap bmp){
            return splashkit_lib::bitmap_cell_width(bmp);
        }

        point_2d bitmap_center(bitmap bmp){
            return splashkit_lib::bitmap_center(bmp);
        }

        char* bitmap_filename(bitmap bmp){
            return outputCStr(splashkit_lib::bitmap_filename(bmp));
        }

        int bitmap_height(bitmap bmp){
            return splashkit_lib::bitmap_height(bmp);
        }

        int bitmap_height_of_bitmap_named(char* name){
            return splashkit_lib::bitmap_height((string)name);
        }

        char* bitmap_name(bitmap bmp){
            return outputCStr(splashkit_lib::bitmap_name(bmp));
        }

        bitmap bitmap_named(char* name){
            return splashkit_lib::bitmap_named((string)name);
        }

        rectangle bitmap_rectangle_of_cell(bitmap src,int cell){
            return splashkit_lib::bitmap_rectangle_of_cell(src,cell);
        }

        void bitmap_set_cell_details(bitmap bmp,int width,int height,int columns,int rows,int count){
            return splashkit_lib::bitmap_set_cell_details(bmp,width,height,columns,rows,count);
        }

        int bitmap_width(bitmap bmp){
            return splashkit_lib::bitmap_width(bmp);
        }

        int bitmap_width_of_bitmap_named(char* name){
            return splashkit_lib::bitmap_width((string)name);
        }

        void clear_bitmap(bitmap bmp,color clr){
            return splashkit_lib::clear_bitmap(bmp,clr);
        }

        void clear_bitmap_named(char* name,color clr){
            return splashkit_lib::clear_bitmap((string)name,clr);
        }

        bitmap create_bitmap(char* name,int width,int height){
            return splashkit_lib::create_bitmap((string)name,width,height);
        }

        void draw_bitmap(bitmap bmp,double x,double y){
            return splashkit_lib::draw_bitmap(bmp,x,y);
        }

        void draw_bitmap_with_options(bitmap bmp,double x,double y,drawing_options opts){
            return splashkit_lib::draw_bitmap(bmp,x,y,opts);
        }

        void draw_bitmap_named(char* name,double x,double y){
            return splashkit_lib::draw_bitmap((string)name,x,y);
        }

        void draw_bitmap_named_with_options(char* name,double x,double y,drawing_options opts){
            return splashkit_lib::draw_bitmap((string)name,x,y,opts);
        }

        void draw_bitmap_on_bitmap_on_bitmap(bitmap destination,bitmap bmp,double x,double y){
            return splashkit_lib::draw_bitmap_on_bitmap(destination,bmp,x,y);
        }

        void draw_bitmap_on_bitmap_on_bitmap_with_options(bitmap destination,bitmap bmp,double x,double y,drawing_options opts){
            return splashkit_lib::draw_bitmap_on_bitmap(destination,bmp,x,y,opts);
        }

        void draw_bitmap_on_window(window destination,bitmap bmp,double x,double y){
            return splashkit_lib::draw_bitmap_on_window(destination,bmp,x,y);
        }

        void draw_bitmap_on_window_with_options(window destination,bitmap bmp,double x,double y,drawing_options opts){
            return splashkit_lib::draw_bitmap_on_window(destination,bmp,x,y,opts);
        }

        void free_all_bitmaps(){
            return splashkit_lib::free_all_bitmaps();
        }

        void free_bitmap(bitmap to_delete){
            return splashkit_lib::free_bitmap(to_delete);
        }

        bool has_bitmap(char* name){
            return splashkit_lib::has_bitmap((string)name);
        }

        bitmap load_bitmap(char* name,char* filename){
            return splashkit_lib::load_bitmap((string)name,(string)filename);
        }

        bool pixel_drawn_at_point_pt(bitmap bmp,point_2d& pt){
            return splashkit_lib::pixel_drawn_at_point(bmp,pt);
        }

        bool pixel_drawn_at_point(bitmap bmp,double x,double y){
            return splashkit_lib::pixel_drawn_at_point(bmp,x,y);
        }

        bool pixel_drawn_at_point_in_cell_pt(bitmap bmp,int cell,point_2d& pt){
            return splashkit_lib::pixel_drawn_at_point(bmp,cell,pt);
        }

        bool pixel_drawn_at_point_in_cell(bitmap bmp,int cell,double x,double y){
            return splashkit_lib::pixel_drawn_at_point(bmp,cell,x,y);
        }

        void setup_collision_mask(bitmap bmp){
            return splashkit_lib::setup_collision_mask(bmp);
        }

        void draw_line_record(color clr,line& l){
            return splashkit_lib::draw_line(clr,l);
        }

        void draw_line_record_with_options(color clr,line& l,drawing_options opts){
            return splashkit_lib::draw_line(clr,l,opts);
        }

        void draw_line_point_to_point(color clr,point_2d& from_pt,point_2d& to_pt){
            return splashkit_lib::draw_line(clr,from_pt,to_pt);
        }

        void draw_line_point_to_point_with_options(color clr,point_2d& from_pt,point_2d& to_pt,drawing_options& opts){
            return splashkit_lib::draw_line(clr,from_pt,to_pt,opts);
        }

        void draw_line(color clr,double x1,double y1,double x2,double y2){
            return splashkit_lib::draw_line(clr,x1,y1,x2,y2);
        }

        void draw_line_with_options(color clr,double x1,double y1,double x2,double y2,drawing_options& opts){
            return splashkit_lib::draw_line(clr,x1,y1,x2,y2,opts);
        }

        void draw_line_on_bitmap_record(bitmap destination,color clr,line& l){
            return splashkit_lib::draw_line_on_bitmap(destination,clr,l);
        }

        void draw_line_on_bitmap_record_with_options(bitmap destination,color clr,line& l,drawing_options opts){
            return splashkit_lib::draw_line_on_bitmap(destination,clr,l,opts);
        }

        void draw_line_on_bitmap_point_to_point(bitmap destination,color clr,point_2d& from_pt,point_2d& to_pt){
            return splashkit_lib::draw_line_on_bitmap(destination,clr,from_pt,to_pt);
        }

        void draw_line_on_bitmap_point_to_point_with_options(bitmap destination,color clr,point_2d& from_pt,point_2d& to_pt,drawing_options& opts){
            return splashkit_lib::draw_line_on_bitmap(destination,clr,from_pt,to_pt,opts);
        }

        void draw_line_on_bitmap(bitmap destination,color clr,double x1,double y1,double x2,double y2){
            return splashkit_lib::draw_line_on_bitmap(destination,clr,x1,y1,x2,y2);
        }

        void draw_line_on_bitmap_with_options(bitmap destination,color clr,double x1,double y1,double x2,double y2,drawing_options& opts){
            return splashkit_lib::draw_line_on_bitmap(destination,clr,x1,y1,x2,y2,opts);
        }

        void draw_line_on_window_record(window destination,color clr,line& l){
            return splashkit_lib::draw_line_on_window(destination,clr,l);
        }

        void draw_line_on_window_record_with_options(window destination,color clr,line& l,drawing_options opts){
            return splashkit_lib::draw_line_on_window(destination,clr,l,opts);
        }

        void draw_line_on_window_point_to_point(window destination,color clr,point_2d& from_pt,point_2d& to_pt){
            return splashkit_lib::draw_line_on_window(destination,clr,from_pt,to_pt);
        }

        void draw_line_on_window_point_to_point_with_options(window destination,color clr,point_2d& from_pt,point_2d& to_pt,drawing_options& opts){
            return splashkit_lib::draw_line_on_window(destination,clr,from_pt,to_pt,opts);
        }

        void draw_line_on_window(window destination,color clr,double x1,double y1,double x2,double y2){
            return splashkit_lib::draw_line_on_window(destination,clr,x1,y1,x2,y2);
        }

        void draw_line_on_window_with_options(window destination,color clr,double x1,double y1,double x2,double y2,drawing_options& opts){
            return splashkit_lib::draw_line_on_window(destination,clr,x1,y1,x2,y2,opts);
        }

        drawing_options option_defaults(){
            return splashkit_lib::option_defaults();
        }

        drawing_options option_draw_to_bitmap(bitmap dest){
            return splashkit_lib::option_draw_to(dest);
        }

        drawing_options option_draw_to_bitmap_with_options(bitmap dest,drawing_options opts){
            return splashkit_lib::option_draw_to(dest,opts);
        }

        drawing_options option_draw_to_window(window dest){
            return splashkit_lib::option_draw_to(dest);
        }

        drawing_options option_draw_to_window_with_options(window dest,drawing_options opts){
            return splashkit_lib::option_draw_to(dest,opts);
        }

        drawing_options option_flip_x(){
            return splashkit_lib::option_flip_x();
        }

        drawing_options option_flip_x_with_options(drawing_options opts){
            return splashkit_lib::option_flip_x(opts);
        }

        drawing_options option_flip_xy(){
            return splashkit_lib::option_flip_xy();
        }

        drawing_options option_flip_xy_with_options(drawing_options opts){
            return splashkit_lib::option_flip_xy(opts);
        }

        drawing_options option_flip_y(){
            return splashkit_lib::option_flip_y();
        }

        drawing_options option_flip_y_with_options(drawing_options opts){
            return splashkit_lib::option_flip_y(opts);
        }

        drawing_options option_line_width(int width){
            return splashkit_lib::option_line_width(width);
        }

        drawing_options option_line_width_with_options(int width,drawing_options opts){
            return splashkit_lib::option_line_width(width,opts);
        }

        drawing_options option_part_bmp(double x,double y,double w,double h){
            return splashkit_lib::option_part_bmp(x,y,w,h);
        }

        drawing_options option_part_bmp_with_options(double x,double y,double w,double h,drawing_options opts){
            return splashkit_lib::option_part_bmp(x,y,w,h,opts);
        }

        drawing_options option_part_bmp_from_rectangle(rectangle part){
            return splashkit_lib::option_part_bmp(part);
        }

        drawing_options option_part_bmp_from_rectangle_with_options(rectangle part,drawing_options opts){
            return splashkit_lib::option_part_bmp(part,opts);
        }

        drawing_options option_rotate_bmp(double angle){
            return splashkit_lib::option_rotate_bmp(angle);
        }

        drawing_options option_rotate_bmp_with_anchor(double angle,double anchor_x,double anchor_y){
            return splashkit_lib::option_rotate_bmp(angle,anchor_x,anchor_y);
        }

        drawing_options option_rotate_bmp_with_anchor_and_options(double angle,double anchor_x,double anchor_y,drawing_options opts){
            return splashkit_lib::option_rotate_bmp(angle,anchor_x,anchor_y,opts);
        }

        drawing_options option_rotate_bmp_with_options(double angle,drawing_options opts){
            return splashkit_lib::option_rotate_bmp(angle,opts);
        }

        drawing_options option_scale_bmp(double scale_x,double scale_y){
            return splashkit_lib::option_scale_bmp(scale_x,scale_y);
        }

        drawing_options option_scale_bmp_with_options(double scale_x,double scale_y,drawing_options opts){
            return splashkit_lib::option_scale_bmp(scale_x,scale_y,opts);
        }

        drawing_options option_to_screen(){
            return splashkit_lib::option_to_screen();
        }

        drawing_options option_to_screen_with_options(drawing_options opts){
            return splashkit_lib::option_to_screen(opts);
        }

        drawing_options option_to_world(){
            return splashkit_lib::option_to_world();
        }

        drawing_options option_to_world_with_options(drawing_options opts){
            return splashkit_lib::option_to_world(opts);
        }

        drawing_options option_with_animation(animation anim){
            return splashkit_lib::option_with_animation(anim);
        }

        drawing_options option_with_animation_with_options(animation anim,drawing_options opts){
            return splashkit_lib::option_with_animation(anim,opts);
        }

        drawing_options option_with_bitmap_cell(int cell){
            return splashkit_lib::option_with_bitmap_cell(cell);
        }

        drawing_options option_with_bitmap_cell_with_options(int cell,drawing_options opts){
            return splashkit_lib::option_with_bitmap_cell(cell,opts);
        }

        void clear_screen_to_white(){
            return splashkit_lib::clear_screen();
        }

        void clear_screen(color clr){
            return splashkit_lib::clear_screen(clr);
        }

        display display_details(unsigned int index){
            return splashkit_lib::display_details(index);
        }

        int display_height(display disp){
            return splashkit_lib::display_height(disp);
        }

        char* display_name(display disp){
            return outputCStr(splashkit_lib::display_name(disp));
        }

        int display_width(display disp){
            return splashkit_lib::display_width(disp);
        }

        int display_x(display disp){
            return splashkit_lib::display_x(disp);
        }

        int display_y(display disp){
            return splashkit_lib::display_y(disp);
        }

        int number_of_displays(){
            return splashkit_lib::number_of_displays();
        }

        void refresh_screen(){
            return splashkit_lib::refresh_screen();
        }

        void refresh_screen_with_target_fps(unsigned int target_fps){
            return splashkit_lib::refresh_screen(target_fps);
        }

        void save_bitmap(bitmap bmp,char*& basename){
            return splashkit_lib::save_bitmap(bmp,(string)basename);
        }

        int screen_height(){
            return splashkit_lib::screen_height();
        }

        int screen_width(){
            return splashkit_lib::screen_width();
        }

        void take_screenshot(char*& basename){
            return splashkit_lib::take_screenshot((string)basename);
        }

        void take_screenshot_of_window(window wind,char*& basename){
            return splashkit_lib::take_screenshot(wind,(string)basename);
        }

        void draw_pixel_at_point(color clr,point_2d& pt){
            return splashkit_lib::draw_pixel(clr,pt);
        }

        void draw_pixel_at_point_with_options(color clr,point_2d& pt,drawing_options opts){
            return splashkit_lib::draw_pixel(clr,pt,opts);
        }

        void draw_pixel(color clr,double x,double y){
            return splashkit_lib::draw_pixel(clr,x,y);
        }

        void draw_pixel_with_options(color clr,double x,double y,drawing_options opts){
            return splashkit_lib::draw_pixel(clr,x,y,opts);
        }

        void draw_pixel_on_bitmap_at_point(bitmap destination,color clr,point_2d& pt){
            return splashkit_lib::draw_pixel_on_bitmap(destination,clr,pt);
        }

        void draw_pixel_on_bitmap_at_point_with_options(bitmap destination,color clr,point_2d& pt,drawing_options opts){
            return splashkit_lib::draw_pixel_on_bitmap(destination,clr,pt,opts);
        }

        void draw_pixel_on_bitmap(bitmap destination,color clr,double x,double y){
            return splashkit_lib::draw_pixel_on_bitmap(destination,clr,x,y);
        }

        void draw_pixel_on_bitmap_with_options(bitmap destination,color clr,double x,double y,drawing_options opts){
            return splashkit_lib::draw_pixel_on_bitmap(destination,clr,x,y,opts);
        }

        void draw_pixel_on_window_at_point(window destination,color clr,point_2d& pt){
            return splashkit_lib::draw_pixel_on_window(destination,clr,pt);
        }

        void draw_pixel_on_window_at_point_with_options(window destination,color clr,point_2d& pt,drawing_options opts){
            return splashkit_lib::draw_pixel_on_window(destination,clr,pt,opts);
        }

        void draw_pixel_on_window(window destination,color clr,double x,double y){
            return splashkit_lib::draw_pixel_on_window(destination,clr,x,y);
        }

        void draw_pixel_on_window_with_options(window destination,color clr,double x,double y,drawing_options opts){
            return splashkit_lib::draw_pixel_on_window(destination,clr,x,y,opts);
        }

        color get_pixel_from_bitmap_at_point(bitmap bmp,point_2d& pt){
            return splashkit_lib::get_pixel(bmp,pt);
        }

        color get_pixel_from_bitmap(bitmap bmp,double x,double y){
            return splashkit_lib::get_pixel(bmp,x,y);
        }

        color get_pixel_at_point(point_2d& pt){
            return splashkit_lib::get_pixel(pt);
        }

        color get_pixel(double x,double y){
            return splashkit_lib::get_pixel(x,y);
        }

        color get_pixel_from_window_at_point(window wnd,point_2d& pt){
            return splashkit_lib::get_pixel(wnd,pt);
        }

        color get_pixel_from_window(window wnd,double x,double y){
            return splashkit_lib::get_pixel(wnd,x,y);
        }

        color get_pixel_from_window_at_point_from_window(window destination,point_2d& pt){
            return splashkit_lib::get_pixel_from_window(destination,pt);
        }

        color get_pixel_from_window_from_window(window destination,double x,double y){
            return splashkit_lib::get_pixel_from_window(destination,x,y);
        }

        void process_events(){
            return splashkit_lib::process_events();
        }

        bool quit_requested(){
            return splashkit_lib::quit_requested();
        }

        void reset_quit(){
            return splashkit_lib::reset_quit();
        }

        void draw_collected_text(color clr,font fnt,int font_size,drawing_options& opts){
            return splashkit_lib::draw_collected_text(clr,fnt,font_size,opts);
        }

        void end_reading_text(){
            return splashkit_lib::end_reading_text();
        }

        void end_reading_text_in_window(window wind){
            return splashkit_lib::end_reading_text(wind);
        }

        bool reading_text(){
            return splashkit_lib::reading_text();
        }

        bool reading_text_in_window(window wind){
            return splashkit_lib::reading_text(wind);
        }

        void start_reading_text(rectangle rect){
            return splashkit_lib::start_reading_text(rect);
        }

        void start_reading_text_with_initial_text(rectangle rect,char* initial_text){
            return splashkit_lib::start_reading_text(rect,(string)initial_text);
        }

        void start_reading_text_in_window(window wind,rectangle rect){
            return splashkit_lib::start_reading_text(wind,rect);
        }

        void start_reading_text_in_window_with_initial_text(window wind,rectangle rect,char* initial_text){
            return splashkit_lib::start_reading_text(wind,rect,(string)initial_text);
        }

        bool text_entry_cancelled(){
            return splashkit_lib::text_entry_cancelled();
        }

        bool text_entry_cancelled_in_window(window wind){
            return splashkit_lib::text_entry_cancelled(wind);
        }

        char* text_input(){
            return outputCStr(splashkit_lib::text_input());
        }

        char* text_input_in_window(window wind){
            return outputCStr(splashkit_lib::text_input(wind));
        }

        void hide_mouse(){
            return splashkit_lib::hide_mouse();
        }

        bool mouse_clicked(mouse_button button){
            return splashkit_lib::mouse_clicked(button);
        }

        bool mouse_down(mouse_button button){
            return splashkit_lib::mouse_down(button);
        }

        vector_2d mouse_movement(){
            return splashkit_lib::mouse_movement();
        }

        point_2d mouse_position(){
            return splashkit_lib::mouse_position();
        }

        vector_2d mouse_position_vector(){
            return splashkit_lib::mouse_position_vector();
        }

        bool mouse_shown(){
            return splashkit_lib::mouse_shown();
        }

        bool mouse_up(mouse_button button){
            return splashkit_lib::mouse_up(button);
        }

        vector_2d mouse_wheel_scroll(){
            return splashkit_lib::mouse_wheel_scroll();
        }

        float mouse_x(){
            return splashkit_lib::mouse_x();
        }

        float mouse_y(){
            return splashkit_lib::mouse_y();
        }

        void move_mouse(double x,double y){
            return splashkit_lib::move_mouse(x,y);
        }

        void move_mouse_to_point(point_2d point){
            return splashkit_lib::move_mouse(point);
        }

        void show_mouse(){
            return splashkit_lib::show_mouse();
        }

        void show_mouse_with_boolean(bool show){
            return splashkit_lib::show_mouse(show);
        }

        bool any_key_pressed(){
            return splashkit_lib::any_key_pressed();
        }

        bool key_down(key_code key){
            return splashkit_lib::key_down(key);
        }

        char* key_name(key_code key){
            return outputCStr(splashkit_lib::key_name(key));
        }

        bool key_released(key_code key){
            return splashkit_lib::key_released(key);
        }

        bool key_typed(key_code key){
            return splashkit_lib::key_typed(key);
        }

        bool key_up(key_code key){
            return splashkit_lib::key_up(key);
        }

        json create_json(){
            return splashkit_lib::create_json();
        }

        json create_json_from_string(char* json_string){
            return splashkit_lib::create_json((string)json_string);
        }

        void free_all_json(){
            return splashkit_lib::free_all_json();
        }

        void free_json(json j){
            return splashkit_lib::free_json(j);
        }

        int json_count_keys(json j){
            return splashkit_lib::json_count_keys(j);
        }

        json json_from_color(color clr){
            return splashkit_lib::json_from_color(clr);
        }

        json json_from_file(char*& filename){
            return splashkit_lib::json_from_file((string)filename);
        }

        json json_from_string(char*& j_string){
            return splashkit_lib::json_from_string((string)j_string);
        }

        bool json_has_key(json j,char* key){
            return splashkit_lib::json_has_key(j,(string)key);
        }

        bool json_read_bool(json j,char* key){
            return splashkit_lib::json_read_bool(j,(string)key);
        }

        float json_read_number(json j,char* key){
            return splashkit_lib::json_read_number(j,(string)key);
        }

        double json_read_number_as_double(json j,char* key){
            return splashkit_lib::json_read_number_as_double(j,(string)key);
        }

        int json_read_number_as_int(json j,char* key){
            return splashkit_lib::json_read_number_as_int(j,(string)key);
        }

        json json_read_object(json j,char* key){
            return splashkit_lib::json_read_object(j,(string)key);
        }

        char* json_read_string(json j,char* key){
            return outputCStr(splashkit_lib::json_read_string(j,(string)key));
        }

        void json_set_bool(json j,char* key,bool value){
            return splashkit_lib::json_set_bool(j,(string)key,value);
        }

        void json_set_number_integer(json j,char* key,int value){
            return splashkit_lib::json_set_number(j,(string)key,value);
        }

        void json_set_number_double(json j,char* key,double value){
            return splashkit_lib::json_set_number(j,(string)key,value);
        }

        void json_set_number_float(json j,char* key,float value){
            return splashkit_lib::json_set_number(j,(string)key,value);
        }

        void json_set_object(json j,char* key,json obj){
            return splashkit_lib::json_set_object(j,(string)key,obj);
        }

        void json_set_string(json j,char* key,char* value){
            return splashkit_lib::json_set_string(j,(string)key,(string)value);
        }

        color json_to_color(json j){
            return splashkit_lib::json_to_color(j);
        }

        void json_to_file(json j,char*& filename){
            return splashkit_lib::json_to_file(j,(string)filename);
        }

        char* json_to_string(json j){
            return outputCStr(splashkit_lib::json_to_string(j));
        }

        void close_log_process(){
            return splashkit_lib::close_log_process();
        }

        void init_custom_logger(log_mode mode){
            return splashkit_lib::init_custom_logger(mode);
        }

        void init_custom_logger__name_override_mode(char* app_name,bool override_prev_log,log_mode mode){
            return splashkit_lib::init_custom_logger((string)app_name,override_prev_log,mode);
        }

        void log(log_level level,char* message){
            return splashkit_lib::log(level,(string)message);
        }

        bitmap download_bitmap(char*& name,char*& url,unsigned short port){
            return splashkit_lib::download_bitmap((string)name,(string)url,port);
        }

        font download_font(char*& name,char*& url,unsigned short port){
            return splashkit_lib::download_font((string)name,(string)url,port);
        }

        music download_music(char*& name,char*& url,unsigned short port){
            return splashkit_lib::download_music((string)name,(string)url,port);
        }

        sound_effect download_sound_effect(char*& name,char*& url,unsigned short port){
            return splashkit_lib::download_sound_effect((string)name,(string)url,port);
        }

        void free_response(http_response response){
            return splashkit_lib::free_response(response);
        }

        http_response http_get(char*& url,unsigned short port){
            return splashkit_lib::http_get((string)url,port);
        }

        char* http_response_to_string(http_response response){
            return outputCStr(splashkit_lib::http_response_to_string(response));
        }

        void save_response_to_file(http_response response,char* path){
            return splashkit_lib::save_response_to_file(response,(string)path);
        }

        bool has_incoming_requests(web_server server){
            return splashkit_lib::has_incoming_requests(server);
        }

        bool is_delete_request_for(http_request request,char*& path){
            return splashkit_lib::is_delete_request_for(request,(string)path);
        }

        bool is_get_request_for(http_request request,char*& path){
            return splashkit_lib::is_get_request_for(request,(string)path);
        }

        bool is_options_request_for(http_request request,char*& path){
            return splashkit_lib::is_options_request_for(request,(string)path);
        }

        bool is_post_request_for(http_request request,char*& path){
            return splashkit_lib::is_post_request_for(request,(string)path);
        }

        bool is_put_request_for(http_request request,char*& path){
            return splashkit_lib::is_put_request_for(request,(string)path);
        }

        bool is_request_for(http_request request,http_method method,char*& path){
            return splashkit_lib::is_request_for(request,method,(string)path);
        }

        bool is_trace_request_for(http_request request,char*& path){
            return splashkit_lib::is_trace_request_for(request,(string)path);
        }

        http_request next_web_request(web_server server){
            return splashkit_lib::next_web_request(server);
        }

        char* request_body(http_request r){
            return outputCStr(splashkit_lib::request_body(r));
        }

        bool request_has_query_parameter(http_request r,char*& name){
            return splashkit_lib::request_has_query_parameter(r,(string)name);
        }

        http_method request_method(http_request r){
            return splashkit_lib::request_method(r);
        }

        char* request_query_parameter(http_request r,char*& name,char*& default_value){
            return outputCStr(splashkit_lib::request_query_parameter(r,(string)name,(string)default_value));
        }

        char* request_query_string(http_request r){
            return outputCStr(splashkit_lib::request_query_string(r));
        }

        char* request_uri(http_request r){
            return outputCStr(splashkit_lib::request_uri(r));
        }

        void send_css_file_response(http_request r,char*& filename){
            return splashkit_lib::send_css_file_response(r,(string)filename);
        }

        void send_file_response(http_request r,char*& filename,char*& content_type){
            return splashkit_lib::send_file_response(r,(string)filename,(string)content_type);
        }

        void send_html_file_response(http_request r,char*& filename){
            return splashkit_lib::send_html_file_response(r,(string)filename);
        }

        void send_javascript_file_response(http_request r,char*& filename){
            return splashkit_lib::send_javascript_file_response(r,(string)filename);
        }

        web_server start_web_server_with_default_port(){
            return splashkit_lib::start_web_server();
        }

        web_server start_web_server(unsigned short port){
            return splashkit_lib::start_web_server(port);
        }

        void stop_web_server(web_server server){
            return splashkit_lib::stop_web_server(server);
        }

        bool accept_all_new_connections(){
            return splashkit_lib::accept_all_new_connections();
        }

        bool accept_new_connection(server_socket server){
            return splashkit_lib::accept_new_connection(server);
        }

        void broadcast_message(char*& a_msg,server_socket svr){
            return splashkit_lib::broadcast_message((string)a_msg,svr);
        }

        void broadcast_message_to_all(char*& a_msg){
            return splashkit_lib::broadcast_message((string)a_msg);
        }

        void broadcast_message_to_server_named(char*& a_msg,char*& name){
            return splashkit_lib::broadcast_message((string)a_msg,(string)name);
        }

        void check_network_activity(){
            return splashkit_lib::check_network_activity();
        }

        void clear_messages_from_name(char*& name){
            return splashkit_lib::clear_messages((string)name);
        }

        void clear_messages_from_connection(connection a_connection){
            return splashkit_lib::clear_messages(a_connection);
        }

        void clear_messages_from_server(server_socket svr){
            return splashkit_lib::clear_messages(svr);
        }

        void close_all_connections(){
            return splashkit_lib::close_all_connections();
        }

        void close_all_servers(){
            return splashkit_lib::close_all_servers();
        }

        bool close_connection(connection a_connection){
            return splashkit_lib::close_connection(a_connection);
        }

        bool close_connection_named(char*& name){
            return splashkit_lib::close_connection((string)name);
        }

        void close_message(message msg){
            return splashkit_lib::close_message(msg);
        }

        bool close_server_named(char*& name){
            return splashkit_lib::close_server((string)name);
        }

        bool close_server(server_socket svr){
            return splashkit_lib::close_server(svr);
        }

        unsigned int connection_count_named(char*& name){
            return splashkit_lib::connection_count((string)name);
        }

        unsigned int connection_count(server_socket server){
            return splashkit_lib::connection_count(server);
        }

        unsigned int connection_ip(connection a_connection){
            return splashkit_lib::connection_ip(a_connection);
        }

        unsigned int connection_ip_from_name(char*& name){
            return splashkit_lib::connection_ip((string)name);
        }

        connection connection_named(char*& name){
            return splashkit_lib::connection_named((string)name);
        }

        unsigned short connection_port(connection a_connection){
            return splashkit_lib::connection_port(a_connection);
        }

        unsigned short connection_port_from_name(char*& name){
            return splashkit_lib::connection_port((string)name);
        }

        server_socket create_server_with_port(char*& name,unsigned short port){
            return splashkit_lib::create_server((string)name,port);
        }

        server_socket create_server_with_port_and_protocol(char*& name,unsigned short port,connection_type protocol){
            return splashkit_lib::create_server((string)name,port,protocol);
        }

        char* dec_to_hex(unsigned int a_dec){
            return outputCStr(splashkit_lib::dec_to_hex(a_dec));
        }

        connection fetch_new_connection(server_socket server){
            return splashkit_lib::fetch_new_connection(server);
        }

        bool has_connection(char*& name){
            return splashkit_lib::has_connection((string)name);
        }

        bool has_messages(){
            return splashkit_lib::has_messages();
        }

        bool has_messages_on_connection(connection con){
            return splashkit_lib::has_messages(con);
        }

        bool has_messages_on_name(char*& name){
            return splashkit_lib::has_messages((string)name);
        }

        bool has_messages_on_server(server_socket svr){
            return splashkit_lib::has_messages(svr);
        }

        bool has_new_connections(){
            return splashkit_lib::has_new_connections();
        }

        bool has_server(char*& name){
            return splashkit_lib::has_server((string)name);
        }

        char* hex_str_to_ipv4(char*& a_hex){
            return outputCStr(splashkit_lib::hex_str_to_ipv4((string)a_hex));
        }

        char* hex_to_dec_string(char*& a_hex){
            return outputCStr(splashkit_lib::hex_to_dec_string((string)a_hex));
        }

        unsigned int ipv4_to_dec(char*& a_ip){
            return splashkit_lib::ipv4_to_dec((string)a_ip);
        }

        char* ipv4_to_hex(char*& a_ip){
            return outputCStr(splashkit_lib::ipv4_to_hex((string)a_ip));
        }

        char* ipv4_to_str(unsigned int ip){
            return outputCStr(splashkit_lib::ipv4_to_str(ip));
        }

        bool is_connection_open(connection con){
            return splashkit_lib::is_connection_open(con);
        }

        bool is_connection_open_from_name(char*& name){
            return splashkit_lib::is_connection_open((string)name);
        }

        connection last_connection_named(char*& name){
            return splashkit_lib::last_connection((string)name);
        }

        connection last_connection(server_socket server){
            return splashkit_lib::last_connection(server);
        }

        connection message_connection(message msg){
            return splashkit_lib::message_connection(msg);
        }

        unsigned int message_count_on_server(server_socket svr){
            return splashkit_lib::message_count(svr);
        }

        unsigned int message_count_on_connection(connection a_connection){
            return splashkit_lib::message_count(a_connection);
        }

        unsigned int message_count_from_name(char*& name){
            return splashkit_lib::message_count((string)name);
        }

        char* message_data(message msg){
            return outputCStr(splashkit_lib::message_data(msg));
        }

        char* message_host(message msg){
            return outputCStr(splashkit_lib::message_host(msg));
        }

        unsigned short message_port(message msg){
            return splashkit_lib::message_port(msg);
        }

        connection_type message_protocol(message msg){
            return splashkit_lib::message_protocol(msg);
        }

        char* my_ip(){
            return outputCStr(splashkit_lib::my_ip());
        }

        char* name_for_connection(char* host,unsigned int port){
            return outputCStr(splashkit_lib::name_for_connection((string)host,port));
        }

        int new_connection_count(server_socket server){
            return splashkit_lib::new_connection_count(server);
        }

        connection open_connection(char*& name,char*& host,unsigned short port){
            return splashkit_lib::open_connection((string)name,(string)host,port);
        }

        connection open_connection_with_protocol(char*& name,char*& host,unsigned short port,connection_type protocol){
            return splashkit_lib::open_connection((string)name,(string)host,port,protocol);
        }

        message read_message(){
            return splashkit_lib::read_message();
        }

        message read_message_from_connection(connection a_connection){
            return splashkit_lib::read_message(a_connection);
        }

        message read_message_from_name(char*& name){
            return splashkit_lib::read_message((string)name);
        }

        message read_message_from_server(server_socket svr){
            return splashkit_lib::read_message(svr);
        }

        char* read_message_data_from_name(char*& name){
            return outputCStr(splashkit_lib::read_message_data((string)name));
        }

        char* read_message_data_from_connection(connection a_connection){
            return outputCStr(splashkit_lib::read_message_data(a_connection));
        }

        char* read_message_data_from_server(server_socket svr){
            return outputCStr(splashkit_lib::read_message_data(svr));
        }

        void reconnect(connection a_connection){
            return splashkit_lib::reconnect(a_connection);
        }

        void reconnect_from_name(char*& name){
            return splashkit_lib::reconnect((string)name);
        }

        void release_all_connections(){
            return splashkit_lib::release_all_connections();
        }

        void reset_new_connection_count(server_socket server){
            return splashkit_lib::reset_new_connection_count(server);
        }

        connection retrieve_connection_named(char*& name,int idx){
            return splashkit_lib::retrieve_connection((string)name,idx);
        }

        connection retrieve_connection(server_socket server,int idx){
            return splashkit_lib::retrieve_connection(server,idx);
        }

        bool send_message_to_connection(char*& a_msg,connection a_connection){
            return splashkit_lib::send_message_to((string)a_msg,a_connection);
        }

        bool send_message_to_name(char*& a_msg,char*& name){
            return splashkit_lib::send_message_to((string)a_msg,(string)name);
        }

        bool server_has_new_connection_named(char*& name){
            return splashkit_lib::server_has_new_connection((string)name);
        }

        bool server_has_new_connection(server_socket server){
            return splashkit_lib::server_has_new_connection(server);
        }

        server_socket server_named(char*& name){
            return splashkit_lib::server_named((string)name);
        }

        void set_udp_packet_size(unsigned int udp_packet_size){
            return splashkit_lib::set_udp_packet_size(udp_packet_size);
        }

        unsigned int udp_packet_size(){
            return splashkit_lib::udp_packet_size();
        }

        bool bitmap_circle_collision_at_point(bitmap bmp,point_2d& pt,circle& circ){
            return splashkit_lib::bitmap_circle_collision(bmp,pt,circ);
        }

        bool bitmap_circle_collision(bitmap bmp,double x,double y,circle& circ){
            return splashkit_lib::bitmap_circle_collision(bmp,x,y,circ);
        }

        bool bitmap_circle_collision_for_cell_with_translation(bitmap bmp,int cell,matrix_2d& translation,circle& circ){
            return splashkit_lib::bitmap_circle_collision(bmp,cell,translation,circ);
        }

        bool bitmap_circle_collision_for_cell_at_point(bitmap bmp,int cell,point_2d& pt,circle& circ){
            return splashkit_lib::bitmap_circle_collision(bmp,cell,pt,circ);
        }

        bool bitmap_circle_collision_for_cell(bitmap bmp,int cell,double x,double y,circle& circ){
            return splashkit_lib::bitmap_circle_collision(bmp,cell,x,y,circ);
        }

        bool bitmap_collision(bitmap bmp1,double x1,double y1,bitmap bmp2,double x2,double y2){
            return splashkit_lib::bitmap_collision(bmp1,x1,y1,bmp2,x2,y2);
        }

        bool bitmap_collision_at_points(bitmap bmp1,point_2d& pt1,bitmap bmp2,point_2d& pt2){
            return splashkit_lib::bitmap_collision(bmp1,pt1,bmp2,pt2);
        }

        bool bitmap_collision_for_cells_with_translations(bitmap bmp1,int cell1,matrix_2d& matrix1,bitmap bmp2,int cell2,matrix_2d& matrix2){
            return splashkit_lib::bitmap_collision(bmp1,cell1,matrix1,bmp2,cell2,matrix2);
        }

        bool bitmap_collision_for_cells_at_points(bitmap bmp1,int cell1,point_2d& pt1,bitmap bmp2,int cell2,point_2d& pt2){
            return splashkit_lib::bitmap_collision(bmp1,cell1,pt1,bmp2,cell2,pt2);
        }

        bool bitmap_collision_for_cells(bitmap bmp1,int cell1,double x1,double y1,bitmap bmp2,int cell2,double x2,double y2){
            return splashkit_lib::bitmap_collision(bmp1,cell1,x1,y1,bmp2,cell2,x2,y2);
        }

        bool bitmap_point_collision_with_translation(bitmap bmp,matrix_2d& translation,point_2d& pt){
            return splashkit_lib::bitmap_point_collision(bmp,translation,pt);
        }

        bool bitmap_point_collision_at_point(bitmap bmp,point_2d& bmp_pt,point_2d& pt){
            return splashkit_lib::bitmap_point_collision(bmp,bmp_pt,pt);
        }

        bool bitmap_point_collision(bitmap bmp,double bmp_x,double bmp_y,double x,double y){
            return splashkit_lib::bitmap_point_collision(bmp,bmp_x,bmp_y,x,y);
        }

        bool bitmap_point_collision_for_cell_with_translation(bitmap bmp,int cell,matrix_2d& translation,point_2d& pt){
            return splashkit_lib::bitmap_point_collision(bmp,cell,translation,pt);
        }

        bool bitmap_point_collision_for_cell_at_point(bitmap bmp,int cell,point_2d& bmp_pt,point_2d& pt){
            return splashkit_lib::bitmap_point_collision(bmp,cell,bmp_pt,pt);
        }

        bool bitmap_point_collision_for_cell(bitmap bmp,int cell,double bmp_x,double bmp_y,double x,double y){
            return splashkit_lib::bitmap_point_collision(bmp,cell,bmp_x,bmp_y,x,y);
        }

        bool bitmap_rectangle_collision_at_point(bitmap bmp,point_2d& pt,rectangle& rect){
            return splashkit_lib::bitmap_rectangle_collision(bmp,pt,rect);
        }

        bool bitmap_rectangle_collision(bitmap bmp,double x,double y,rectangle& rect){
            return splashkit_lib::bitmap_rectangle_collision(bmp,x,y,rect);
        }

        bool bitmap_rectangle_collision_for_cell_with_translation(bitmap bmp,int cell,matrix_2d& translation,rectangle& rect){
            return splashkit_lib::bitmap_rectangle_collision(bmp,cell,translation,rect);
        }

        bool bitmap_rectangle_collision_for_cell_at_point(bitmap bmp,int cell,point_2d& pt,rectangle& rect){
            return splashkit_lib::bitmap_rectangle_collision(bmp,cell,pt,rect);
        }

        bool bitmap_rectangle_collision_for_cell(bitmap bmp,int cell,double x,double y,rectangle& rect){
            return splashkit_lib::bitmap_rectangle_collision(bmp,cell,x,y,rect);
        }

        bool sprite_bitmap_collision(sprite s,bitmap bmp,double x,double y){
            return splashkit_lib::sprite_bitmap_collision(s,bmp,x,y);
        }

        bool sprite_bitmap_collision_with_cell_at_point(sprite s,bitmap bmp,int cell,point_2d& pt){
            return splashkit_lib::sprite_bitmap_collision(s,bmp,cell,pt);
        }

        bool sprite_bitmap_collision_with_cell(sprite s,bitmap bmp,int cell,double x,double y){
            return splashkit_lib::sprite_bitmap_collision(s,bmp,cell,x,y);
        }

        bool sprite_collision(sprite s1,sprite s2){
            return splashkit_lib::sprite_collision(s1,s2);
        }

        bool sprite_point_collision(sprite s,point_2d& pt){
            return splashkit_lib::sprite_point_collision(s,pt);
        }

        bool sprite_rectangle_collision(sprite s,rectangle& rect){
            return splashkit_lib::sprite_rectangle_collision(s,rect);
        }

        void apply_matrix_to_quad(matrix_2d& matrix,quad& q){
            return splashkit_lib::apply_matrix(matrix,q);
        }

        void apply_matrix_to_triangle(matrix_2d& m,triangle& tri){
            return splashkit_lib::apply_matrix(m,tri);
        }

        matrix_2d identity_matrix(){
            return splashkit_lib::identity_matrix();
        }

        matrix_2d matrix_inverse(matrix_2d& m){
            return splashkit_lib::matrix_inverse(m);
        }

        point_2d matrix_multiply_point(matrix_2d& m,point_2d& pt){
            return splashkit_lib::matrix_multiply(m,pt);
        }

        matrix_2d matrix_multiply_matrix(matrix_2d& m1,matrix_2d& m2){
            return splashkit_lib::matrix_multiply(m1,m2);
        }

        vector_2d matrix_multiply_vector(matrix_2d& m,vector_2d& v){
            return splashkit_lib::matrix_multiply(m,v);
        }

        char* matrix_to_string(matrix_2d& matrix){
            return outputCStr(splashkit_lib::matrix_to_string(matrix));
        }

        matrix_2d rotation_matrix(double deg){
            return splashkit_lib::rotation_matrix(deg);
        }

        matrix_2d scale_matrix_from_point(point_2d& scale){
            return splashkit_lib::scale_matrix(scale);
        }

        matrix_2d scale_matrix_from_vector(vector_2d& scale){
            return splashkit_lib::scale_matrix(scale);
        }

        matrix_2d scale_matrix(double scale){
            return splashkit_lib::scale_matrix(scale);
        }

        matrix_2d scale_rotate_translate_matrix(point_2d& scale,double deg,point_2d& translate){
            return splashkit_lib::scale_rotate_translate_matrix(scale,deg,translate);
        }

        matrix_2d translation_matrix_to_point(point_2d& pt){
            return splashkit_lib::translation_matrix(pt);
        }

        matrix_2d translation_matrix_from_vector(vector_2d& pt){
            return splashkit_lib::translation_matrix(pt);
        }

        matrix_2d translation_matrix(double dx,double dy){
            return splashkit_lib::translation_matrix(dx,dy);
        }

        double angle_between(vector_2d& v1,vector_2d& v2){
            return splashkit_lib::angle_between(v1,v2);
        }

        double dot_product(vector_2d& v1,vector_2d& v2){
            return splashkit_lib::dot_product(v1,v2);
        }

        bool is_zero_vector(vector_2d& v){
            return splashkit_lib::is_zero_vector(v);
        }

        bool ray_intersection_point(point_2d& from_pt,vector_2d& heading,line& l,point_2d& pt){
            return splashkit_lib::ray_intersection_point(from_pt,heading,l,pt);
        }

        vector_2d unit_vector(vector_2d& v){
            return splashkit_lib::unit_vector(v);
        }

        vector_2d vector_add(vector_2d& v1,vector_2d& v2){
            return splashkit_lib::vector_add(v1,v2);
        }

        double vector_angle(vector_2d v){
            return splashkit_lib::vector_angle(v);
        }

        vector_2d vector_from_angle(double angle,double magnitude){
            return splashkit_lib::vector_from_angle(angle,magnitude);
        }

        vector_2d vector_from_line(line& l){
            return splashkit_lib::vector_from_line(l);
        }

        vector_2d vector_from_point_to_rect(point_2d& pt,rectangle& rect){
            return splashkit_lib::vector_from_point_to_rect(pt,rect);
        }

        bool vector_in_rect(vector_2d& v,rectangle& rect){
            return splashkit_lib::vector_in_rect(v,rect);
        }

        vector_2d vector_invert(vector_2d& v){
            return splashkit_lib::vector_invert(v);
        }

        vector_2d vector_limit(vector_2d& v,double limit){
            return splashkit_lib::vector_limit(v,limit);
        }

        double vector_magnitude(vector_2d& v){
            return splashkit_lib::vector_magnitude(v);
        }

        double vector_magnitude_sqared(vector_2d& v){
            return splashkit_lib::vector_magnitude_sqared(v);
        }

        vector_2d vector_multiply(vector_2d& v1,double s){
            return splashkit_lib::vector_multiply(v1,s);
        }

        vector_2d vector_normal(vector_2d& v){
            return splashkit_lib::vector_normal(v);
        }

        vector_2d vector_out_of_circle_from_circle(circle& src,circle& bounds,vector_2d& velocity){
            return splashkit_lib::vector_out_of_circle_from_circle(src,bounds,velocity);
        }

        vector_2d vector_out_of_circle_from_point(point_2d& pt,circle& c,vector_2d& velocity){
            return splashkit_lib::vector_out_of_circle_from_point(pt,c,velocity);
        }

        vector_2d vector_out_of_rect_from_circle(circle& c,rectangle& rect,vector_2d& velocity){
            return splashkit_lib::vector_out_of_rect_from_circle(c,rect,velocity);
        }

        vector_2d vector_out_of_rect_from_point(point_2d& pt,rectangle& rect,vector_2d& velocity){
            return splashkit_lib::vector_out_of_rect_from_point(pt,rect,velocity);
        }

        vector_2d vector_out_of_rect_from_rect(rectangle& src,rectangle& bounds,vector_2d& velocity){
            return splashkit_lib::vector_out_of_rect_from_rect(src,bounds,velocity);
        }

        vector_2d vector_point_to_point(point_2d& start,point_2d& end_pt){
            return splashkit_lib::vector_point_to_point(start,end_pt);
        }

        vector_2d vector_subtract(vector_2d& v1,vector_2d& v2){
            return splashkit_lib::vector_subtract(v1,v2);
        }

        vector_2d vector_to_point(point_2d& p1){
            return splashkit_lib::vector_to(p1);
        }

        vector_2d vector_to(double x,double y){
            return splashkit_lib::vector_to(x,y);
        }

        char* vector_to_string(vector_2d& v){
            return outputCStr(splashkit_lib::vector_to_string(v));
        }

        bool vectors_equal(vector_2d& v1,vector_2d v2){
            return splashkit_lib::vectors_equal(v1,v2);
        }

        bool vectors_not_equal(vector_2d& v1,vector_2d v2){
            return splashkit_lib::vectors_not_equal(v1,v2);
        }

        void free_resource_bundle(char* name){
            return splashkit_lib::free_resource_bundle((string)name);
        }

        bool has_resource_bundle(char*& name){
            return splashkit_lib::has_resource_bundle((string)name);
        }

        void load_resource_bundle(char*& name,char*& filename){
            return splashkit_lib::load_resource_bundle((string)name,(string)filename);
        }

        char* path_to_resource(char*& filename,resource_kind kind){
            return outputCStr(splashkit_lib::path_to_resource((string)filename,kind));
        }

        char* path_to_resources(){
            return outputCStr(splashkit_lib::path_to_resources());
        }

        char* path_to_resources_for_kind(resource_kind kind){
            return outputCStr(splashkit_lib::path_to_resources(kind));
        }

        void set_resources_path(char*& path){
            return splashkit_lib::set_resources_path((string)path);
        }

        point_2d center_point_sprite(sprite s){
            return splashkit_lib::center_point(s);
        }

        sprite create_sprite(bitmap layer){
            return splashkit_lib::create_sprite(layer);
        }

        sprite create_sprite_with_animation(bitmap layer,animation_script ani){
            return splashkit_lib::create_sprite(layer,ani);
        }

        sprite create_sprite_with_bitmap_named(char*& bitmap_name){
            return splashkit_lib::create_sprite((string)bitmap_name);
        }

        sprite create_sprite_named(char*& name,bitmap layer){
            return splashkit_lib::create_sprite((string)name,layer);
        }

        sprite create_sprite_named_with_animation(char*& name,bitmap layer,animation_script ani){
            return splashkit_lib::create_sprite((string)name,layer,ani);
        }

        sprite create_sprite_with_bitmap_and_animation_named(char*& bitmap_name,char*& animation_name){
            return splashkit_lib::create_sprite((string)bitmap_name,(string)animation_name);
        }

        void create_sprite_pack(char*& name){
            return splashkit_lib::create_sprite_pack((string)name);
        }

        char* current_sprite_pack(){
            return outputCStr(splashkit_lib::current_sprite_pack());
        }

        void draw_all_sprites(){
            return splashkit_lib::draw_all_sprites();
        }

        void draw_sprite_offset_by(sprite s,vector_2d& offset){
            return splashkit_lib::draw_sprite(s,offset);
        }

        void draw_sprite(sprite s){
            return splashkit_lib::draw_sprite(s);
        }

        void draw_sprite_offset_x_y(sprite s,double x_offset,double y_offset){
            return splashkit_lib::draw_sprite(s,x_offset,y_offset);
        }

        void free_all_sprites(){
            return splashkit_lib::free_all_sprites();
        }

        void free_sprite(sprite s){
            return splashkit_lib::free_sprite(s);
        }

        void free_sprite_pack(char*& name){
            return splashkit_lib::free_sprite_pack((string)name);
        }

        bool has_sprite(char*& name){
            return splashkit_lib::has_sprite((string)name);
        }

        bool has_sprite_pack(char*& name){
            return splashkit_lib::has_sprite_pack((string)name);
        }

        void move_sprite(sprite s){
            return splashkit_lib::move_sprite(s);
        }

        void move_sprite_by_vector(sprite s,vector_2d& distance){
            return splashkit_lib::move_sprite(s,distance);
        }

        void move_sprite_by_vector_percent(sprite s,vector_2d& distance,float pct){
            return splashkit_lib::move_sprite(s,distance,pct);
        }

        void move_sprite_percent(sprite s,float pct){
            return splashkit_lib::move_sprite(s,pct);
        }

        void move_sprite_to(sprite s,double x,double y){
            return splashkit_lib::move_sprite_to(s,x,y);
        }

        void select_sprite_pack(char*& name){
            return splashkit_lib::select_sprite_pack((string)name);
        }

        int sprite_add_layer(sprite s,bitmap new_layer,char*& layer_name){
            return splashkit_lib::sprite_add_layer(s,new_layer,(string)layer_name);
        }

        void sprite_add_to_velocity(sprite s,vector_2d& value){
            return splashkit_lib::sprite_add_to_velocity(s,value);
        }

        void sprite_add_value(sprite s,char*& name){
            return splashkit_lib::sprite_add_value(s,(string)name);
        }

        void sprite_add_value_with_default(sprite s,char*& name,float init_val){
            return splashkit_lib::sprite_add_value(s,(string)name,init_val);
        }

        point_2d sprite_anchor_point(sprite s){
            return splashkit_lib::sprite_anchor_point(s);
        }

        point_2d sprite_anchor_position(sprite s){
            return splashkit_lib::sprite_anchor_position(s);
        }

        bool sprite_animation_has_ended(sprite s){
            return splashkit_lib::sprite_animation_has_ended(s);
        }

        char* sprite_animation_name(sprite s){
            return outputCStr(splashkit_lib::sprite_animation_name(s));
        }

        bool sprite_at(sprite s,point_2d& pt){
            return splashkit_lib::sprite_at(s,pt);
        }

        void sprite_bring_layer_forward(sprite s,int visible_layer){
            return splashkit_lib::sprite_bring_layer_forward(s,visible_layer);
        }

        void sprite_bring_layer_to_front(sprite s,int visible_layer){
            return splashkit_lib::sprite_bring_layer_to_front(s,visible_layer);
        }

        circle sprite_circle(sprite s){
            return splashkit_lib::sprite_circle(s);
        }

        bitmap sprite_collision_bitmap(sprite s){
            return splashkit_lib::sprite_collision_bitmap(s);
        }

        circle sprite_collision_circle(sprite s){
            return splashkit_lib::sprite_collision_circle(s);
        }

        collision_test_kind sprite_collision_kind(sprite s){
            return splashkit_lib::sprite_collision_kind(s);
        }

        rectangle sprite_collision_rectangle(sprite s){
            return splashkit_lib::sprite_collision_rectangle(s);
        }

        int sprite_current_cell(sprite s){
            return splashkit_lib::sprite_current_cell(s);
        }

        rectangle sprite_current_cell_rectangle(sprite s){
            return splashkit_lib::sprite_current_cell_rectangle(s);
        }

        float sprite_dx(sprite s){
            return splashkit_lib::sprite_dx(s);
        }

        float sprite_dy(sprite s){
            return splashkit_lib::sprite_dy(s);
        }

        bool sprite_has_value(sprite s,char* name){
            return splashkit_lib::sprite_has_value(s,(string)name);
        }

        float sprite_heading(sprite s){
            return splashkit_lib::sprite_heading(s);
        }

        int sprite_height(sprite s){
            return splashkit_lib::sprite_height(s);
        }

        void sprite_hide_layer_named(sprite s,char*& name){
            return splashkit_lib::sprite_hide_layer(s,(string)name);
        }

        void sprite_hide_layer(sprite s,int id){
            return splashkit_lib::sprite_hide_layer(s,id);
        }

        bitmap sprite_layer_named(sprite s,char*& name){
            return splashkit_lib::sprite_layer(s,(string)name);
        }

        bitmap sprite_layer_at_index(sprite s,int idx){
            return splashkit_lib::sprite_layer(s,idx);
        }

        circle sprite_layer_circle_named(sprite s,char*& name){
            return splashkit_lib::sprite_layer_circle(s,(string)name);
        }

        circle sprite_layer_circle_at_index(sprite s,int idx){
            return splashkit_lib::sprite_layer_circle(s,idx);
        }

        int sprite_layer_count(sprite s){
            return splashkit_lib::sprite_layer_count(s);
        }

        int sprite_layer_height_named(sprite s,char*& name){
            return splashkit_lib::sprite_layer_height(s,(string)name);
        }

        int sprite_layer_height(sprite s,int idx){
            return splashkit_lib::sprite_layer_height(s,idx);
        }

        int sprite_layer_index(sprite s,char*& name){
            return splashkit_lib::sprite_layer_index(s,(string)name);
        }

        char* sprite_layer_name(sprite s,int idx){
            return outputCStr(splashkit_lib::sprite_layer_name(s,idx));
        }

        vector_2d sprite_layer_offset_named(sprite s,char*& name){
            return splashkit_lib::sprite_layer_offset(s,(string)name);
        }

        vector_2d sprite_layer_offset(sprite s,int idx){
            return splashkit_lib::sprite_layer_offset(s,idx);
        }

        rectangle sprite_layer_rectangle_named(sprite s,char*& name){
            return splashkit_lib::sprite_layer_rectangle(s,(string)name);
        }

        rectangle sprite_layer_rectangle_at_index(sprite s,int idx){
            return splashkit_lib::sprite_layer_rectangle(s,idx);
        }

        int sprite_layer_width_named(sprite s,char*& name){
            return splashkit_lib::sprite_layer_width(s,(string)name);
        }

        int sprite_layer_width(sprite s,int idx){
            return splashkit_lib::sprite_layer_width(s,idx);
        }

        matrix_2d sprite_location_matrix(sprite s){
            return splashkit_lib::sprite_location_matrix(s);
        }

        float sprite_mass(sprite s){
            return splashkit_lib::sprite_mass(s);
        }

        bool sprite_move_from_anchor_point(sprite s){
            return splashkit_lib::sprite_move_from_anchor_point(s);
        }

        void sprite_move_to_taking_seconds(sprite s,point_2d& pt,float taking_seconds){
            return splashkit_lib::sprite_move_to(s,pt,taking_seconds);
        }

        char* sprite_name(sprite s){
            return outputCStr(splashkit_lib::sprite_name(s));
        }

        sprite sprite_named(char*& name){
            return splashkit_lib::sprite_named((string)name);
        }

        bool sprite_offscreen(sprite s){
            return splashkit_lib::sprite_offscreen(s);
        }

        bool sprite_on_screen_at_point(sprite s,point_2d& pt){
            return splashkit_lib::sprite_on_screen_at(s,pt);
        }

        bool sprite_on_screen_at(sprite s,double x,double y){
            return splashkit_lib::sprite_on_screen_at(s,x,y);
        }

        point_2d sprite_position(sprite s){
            return splashkit_lib::sprite_position(s);
        }

        void sprite_replay_animation(sprite s){
            return splashkit_lib::sprite_replay_animation(s);
        }

        void sprite_replay_animation_with_sound(sprite s,bool with_sound){
            return splashkit_lib::sprite_replay_animation(s,with_sound);
        }

        float sprite_rotation(sprite s){
            return splashkit_lib::sprite_rotation(s);
        }

        float sprite_scale(sprite s){
            return splashkit_lib::sprite_scale(s);
        }

        rectangle sprite_screen_rectangle(sprite s){
            return splashkit_lib::sprite_screen_rectangle(s);
        }

        void sprite_send_layer_backward(sprite s,int visible_layer){
            return splashkit_lib::sprite_send_layer_backward(s,visible_layer);
        }

        void sprite_send_layer_to_back(sprite s,int visible_layer){
            return splashkit_lib::sprite_send_layer_to_back(s,visible_layer);
        }

        void sprite_set_anchor_point(sprite s,point_2d& pt){
            return splashkit_lib::sprite_set_anchor_point(s,pt);
        }

        void sprite_set_collision_bitmap(sprite s,bitmap bmp){
            return splashkit_lib::sprite_set_collision_bitmap(s,bmp);
        }

        void sprite_set_collision_kind(sprite s,collision_test_kind value){
            return splashkit_lib::sprite_set_collision_kind(s,value);
        }

        void sprite_set_dx(sprite s,float value){
            return splashkit_lib::sprite_set_dx(s,value);
        }

        void sprite_set_dy(sprite s,float value){
            return splashkit_lib::sprite_set_dy(s,value);
        }

        void sprite_set_heading(sprite s,float value){
            return splashkit_lib::sprite_set_heading(s,value);
        }

        void sprite_set_layer_offset_named(sprite s,char*& name,vector_2d& value){
            return splashkit_lib::sprite_set_layer_offset(s,(string)name,value);
        }

        void sprite_set_layer_offset_at_index(sprite s,int idx,vector_2d& value){
            return splashkit_lib::sprite_set_layer_offset(s,idx,value);
        }

        void sprite_set_mass(sprite s,float value){
            return splashkit_lib::sprite_set_mass(s,value);
        }

        void sprite_set_move_from_anchor_point(sprite s,bool value){
            return splashkit_lib::sprite_set_move_from_anchor_point(s,value);
        }

        void sprite_set_position(sprite s,point_2d& value){
            return splashkit_lib::sprite_set_position(s,value);
        }

        void sprite_set_rotation(sprite s,float value){
            return splashkit_lib::sprite_set_rotation(s,value);
        }

        void sprite_set_scale(sprite s,float value){
            return splashkit_lib::sprite_set_scale(s,value);
        }

        void sprite_set_speed(sprite s,float value){
            return splashkit_lib::sprite_set_speed(s,value);
        }

        void sprite_set_value_named(sprite s,char*& name,float val){
            return splashkit_lib::sprite_set_value(s,(string)name,val);
        }

        void sprite_set_velocity(sprite s,vector_2d& value){
            return splashkit_lib::sprite_set_velocity(s,value);
        }

        void sprite_set_x(sprite s,float value){
            return splashkit_lib::sprite_set_x(s,value);
        }

        void sprite_set_y(sprite s,float value){
            return splashkit_lib::sprite_set_y(s,value);
        }

        int sprite_show_layer_named(sprite s,char*& name){
            return splashkit_lib::sprite_show_layer(s,(string)name);
        }

        int sprite_show_layer(sprite s,int id){
            return splashkit_lib::sprite_show_layer(s,id);
        }

        float sprite_speed(sprite s){
            return splashkit_lib::sprite_speed(s);
        }

        void sprite_start_animation_named(sprite s,char*& named){
            return splashkit_lib::sprite_start_animation(s,(string)named);
        }

        void sprite_start_animation_named_with_sound(sprite s,char*& named,bool with_sound){
            return splashkit_lib::sprite_start_animation(s,(string)named,with_sound);
        }

        void sprite_start_animation(sprite s,int idx){
            return splashkit_lib::sprite_start_animation(s,idx);
        }

        void sprite_start_animation_with_sound(sprite s,int idx,bool with_sound){
            return splashkit_lib::sprite_start_animation(s,idx,with_sound);
        }

        void sprite_toggle_layer_visible_named(sprite s,char*& name){
            return splashkit_lib::sprite_toggle_layer_visible(s,(string)name);
        }

        void sprite_toggle_layer_visible(sprite s,int id){
            return splashkit_lib::sprite_toggle_layer_visible(s,id);
        }

        float sprite_value(sprite s,char*& name){
            return splashkit_lib::sprite_value(s,(string)name);
        }

        int sprite_value_count(sprite s){
            return splashkit_lib::sprite_value_count(s);
        }

        vector_2d sprite_velocity(sprite s){
            return splashkit_lib::sprite_velocity(s);
        }

        int sprite_visible_index_of_layer_named(sprite s,char*& name){
            return splashkit_lib::sprite_visible_index_of_layer(s,(string)name);
        }

        int sprite_visible_index_of_layer(sprite s,int id){
            return splashkit_lib::sprite_visible_index_of_layer(s,id);
        }

        int sprite_visible_layer(sprite s,int idx){
            return splashkit_lib::sprite_visible_layer(s,idx);
        }

        int sprite_visible_layer_count(sprite s){
            return splashkit_lib::sprite_visible_layer_count(s);
        }

        int sprite_visible_layer_id(sprite s,int idx){
            return splashkit_lib::sprite_visible_layer_id(s,idx);
        }

        int sprite_width(sprite s){
            return splashkit_lib::sprite_width(s);
        }

        float sprite_x(sprite s){
            return splashkit_lib::sprite_x(s);
        }

        float sprite_y(sprite s){
            return splashkit_lib::sprite_y(s);
        }

        void update_all_sprites(){
            return splashkit_lib::update_all_sprites();
        }

        void update_all_sprites_percent(float pct){
            return splashkit_lib::update_all_sprites(pct);
        }

        void update_sprite(sprite s){
            return splashkit_lib::update_sprite(s);
        }

        void update_sprite_with_sound(sprite s,bool with_sound){
            return splashkit_lib::update_sprite(s,with_sound);
        }

        void update_sprite_percent(sprite s,float pct){
            return splashkit_lib::update_sprite(s,pct);
        }

        void update_sprite_percent_with_sound(sprite s,float pct,bool with_sound){
            return splashkit_lib::update_sprite(s,pct,with_sound);
        }

        void update_sprite_animation(sprite s){
            return splashkit_lib::update_sprite_animation(s);
        }

        void update_sprite_animation_with_sound(sprite s,bool with_sound){
            return splashkit_lib::update_sprite_animation(s,with_sound);
        }

        void update_sprite_animation_percent(sprite s,float pct){
            return splashkit_lib::update_sprite_animation(s,pct);
        }

        void update_sprite_animation_percent_with_sound(sprite s,float pct,bool with_sound){
            return splashkit_lib::update_sprite_animation(s,pct,with_sound);
        }

        vector_2d vector_from_center_sprite_to_point_point(sprite s,point_2d& pt){
            return splashkit_lib::vector_from_center_sprite_to_point(s,pt);
        }

        vector_2d vector_from_to(sprite s1,sprite s2){
            return splashkit_lib::vector_from_to(s1,s2);
        }

        void activate_advanced_terminal(){
            return splashkit_lib::activate_advanced_terminal();
        }

        bool advanced_terminal_active(){
            return splashkit_lib::advanced_terminal_active();
        }

        void clear_terminal(){
            return splashkit_lib::clear_terminal();
        }

        void end_advanced_terminal(){
            return splashkit_lib::end_advanced_terminal();
        }

        void move_cursor_to(int x,int y){
            return splashkit_lib::move_cursor_to(x,y);
        }

        char read_char(){
            return splashkit_lib::read_char();
        }

        char* read_line(){
            return outputCStr(splashkit_lib::read_line());
        }

        void refresh_terminal(){
            return splashkit_lib::refresh_terminal();
        }

        void set_terminal_bold(bool value){
            return splashkit_lib::set_terminal_bold(value);
        }

        void set_terminal_colors(color foreground,color background){
            return splashkit_lib::set_terminal_colors(foreground,background);
        }

        void set_terminal_echo_input(bool value){
            return splashkit_lib::set_terminal_echo_input(value);
        }

        int terminal_height(){
            return splashkit_lib::terminal_height();
        }

        int terminal_width(){
            return splashkit_lib::terminal_width();
        }

        void write_char(char data){
            return splashkit_lib::write(data);
        }

        void write_double(double data){
            return splashkit_lib::write(data);
        }

        void write_int(int data){
            return splashkit_lib::write(data);
        }

        void write(char* text){
            return splashkit_lib::write((string)text);
        }

        void write_at(char* text,int x,int y){
            return splashkit_lib::write_at((string)text,x,y);
        }

        void write_line_char(char data){
            return splashkit_lib::write_line(data);
        }

        void write_line_empty(){
            return splashkit_lib::write_line();
        }

        void write_line_double(double data){
            return splashkit_lib::write_line(data);
        }

        void write_line_int(int data){
            return splashkit_lib::write_line(data);
        }

        void write_line(char* line){
            return splashkit_lib::write_line((string)line);
        }

        timer create_timer(char* name){
            return splashkit_lib::create_timer((string)name);
        }

        void free_all_timers(){
            return splashkit_lib::free_all_timers();
        }

        void free_timer(timer to_free){
            return splashkit_lib::free_timer(to_free);
        }

        bool has_timer__named(char* name){
            return splashkit_lib::has_timer((string)name);
        }

        void pause_timer__named(char* name){
            return splashkit_lib::pause_timer((string)name);
        }

        void pause_timer(timer to_pause){
            return splashkit_lib::pause_timer(to_pause);
        }

        void reset_timer__named(char* name){
            return splashkit_lib::reset_timer((string)name);
        }

        void reset_timer(timer tmr){
            return splashkit_lib::reset_timer(tmr);
        }

        void resume_timer__named(char* name){
            return splashkit_lib::resume_timer((string)name);
        }

        void resume_timer(timer to_resume){
            return splashkit_lib::resume_timer(to_resume);
        }

        void start_timer__named(char* name){
            return splashkit_lib::start_timer((string)name);
        }

        void start_timer(timer to_start){
            return splashkit_lib::start_timer(to_start);
        }

        void stop_timer__named(char* name){
            return splashkit_lib::stop_timer((string)name);
        }

        void stop_timer(timer to_stop){
            return splashkit_lib::stop_timer(to_stop);
        }

        timer timer_named(char* name){
            return splashkit_lib::timer_named((string)name);
        }

        bool timer_paused__named(char* name){
            return splashkit_lib::timer_paused((string)name);
        }

        bool timer_paused(timer to_get){
            return splashkit_lib::timer_paused(to_get);
        }

        bool timer_started__named(char* name){
            return splashkit_lib::timer_started((string)name);
        }

        bool timer_started(timer to_get){
            return splashkit_lib::timer_started(to_get);
        }

        unsigned int timer_ticks__named(char* name){
            return splashkit_lib::timer_ticks((string)name);
        }

        unsigned int timer_ticks(timer to_get){
            return splashkit_lib::timer_ticks(to_get);
        }

        unsigned int current_ticks(){
            return splashkit_lib::current_ticks();
        }

        void delay(unsigned int milliseconds){
            return splashkit_lib::delay(milliseconds);
        }

        void display_dialog(char*& title,char*& msg,font output_font,int font_size){
            return splashkit_lib::display_dialog((string)title,(string)msg,output_font,font_size);
        }

        char* file_as_string(char* filename,resource_kind kind){
            return outputCStr(splashkit_lib::file_as_string((string)filename,kind));
        }

        double convert_to_double(char*& text){
            return splashkit_lib::convert_to_double((string)text);
        }

        int convert_to_integer(char*& text){
            return splashkit_lib::convert_to_integer((string)text);
        }

        bool is_double(char*& text){
            return splashkit_lib::is_double((string)text);
        }

        bool is_integer(char*& text){
            return splashkit_lib::is_integer((string)text);
        }

        bool is_number(char*& text){
            return splashkit_lib::is_number((string)text);
        }

        char* to_lowercase(char*& text){
            return outputCStr(splashkit_lib::to_lowercase((string)text));
        }

        char* to_uppercase(char*& text){
            return outputCStr(splashkit_lib::to_uppercase((string)text));
        }

        char* trim(char*& text){
            return outputCStr(splashkit_lib::trim((string)text));
        }

        int rnd_range(int min,int max){
            return splashkit_lib::rnd(min,max);
        }

        float rnd(){
            return splashkit_lib::rnd();
        }

        int rnd_int(int ubound){
            return splashkit_lib::rnd(ubound);
        }

        void clear_window(window wind,color clr){
            return splashkit_lib::clear_window(wind,clr);
        }

        void close_all_windows(){
            return splashkit_lib::close_all_windows();
        }

        void close_current_window(){
            return splashkit_lib::close_current_window();
        }

        void close_window_named(char*& name){
            return splashkit_lib::close_window((string)name);
        }

        void close_window(window wind){
            return splashkit_lib::close_window(wind);
        }

        window current_window(){
            return splashkit_lib::current_window();
        }

        bool current_window_has_border(){
            return splashkit_lib::current_window_has_border();
        }

        int current_window_height(){
            return splashkit_lib::current_window_height();
        }

        bool current_window_is_fullscreen(){
            return splashkit_lib::current_window_is_fullscreen();
        }

        point_2d current_window_position(){
            return splashkit_lib::current_window_position();
        }

        void current_window_toggle_border(){
            return splashkit_lib::current_window_toggle_border();
        }

        void current_window_toggle_fullscreen(){
            return splashkit_lib::current_window_toggle_fullscreen();
        }

        int current_window_width(){
            return splashkit_lib::current_window_width();
        }

        int current_window_x(){
            return splashkit_lib::current_window_x();
        }

        int current_window_y(){
            return splashkit_lib::current_window_y();
        }

        bool has_window(char* caption){
            return splashkit_lib::has_window((string)caption);
        }

        bool is_current_window(window wind){
            return splashkit_lib::is_current_window(wind);
        }

        void move_current_window_to(int x,int y){
            return splashkit_lib::move_current_window_to(x,y);
        }

        void move_window_to_named(char*& name,int x,int y){
            return splashkit_lib::move_window_to((string)name,x,y);
        }

        void move_window_to(window wind,int x,int y){
            return splashkit_lib::move_window_to(wind,x,y);
        }

        window open_window(char* caption,int width,int height){
            return splashkit_lib::open_window((string)caption,width,height);
        }

        void refresh_window(window wind){
            return splashkit_lib::refresh_window(wind);
        }

        void refresh_window_with_target_fps(window wind,unsigned int target_fps){
            return splashkit_lib::refresh_window(wind,target_fps);
        }

        void resize_current_window(int width,int height){
            return splashkit_lib::resize_current_window(width,height);
        }

        void resize_window(window wnd,int width,int height){
            return splashkit_lib::resize_window(wnd,width,height);
        }

        void set_current_window_named(char*& name){
            return splashkit_lib::set_current_window((string)name);
        }

        void set_current_window(window wind){
            return splashkit_lib::set_current_window(wind);
        }

        char* window_caption(window wind){
            return outputCStr(splashkit_lib::window_caption(wind));
        }

        bool window_close_requested_named(char*& name){
            return splashkit_lib::window_close_requested((string)name);
        }

        bool window_close_requested(window wind){
            return splashkit_lib::window_close_requested(wind);
        }

        bool window_has_border_named(char*& name){
            return splashkit_lib::window_has_border((string)name);
        }

        bool window_has_border(window wnd){
            return splashkit_lib::window_has_border(wnd);
        }

        bool window_has_focus(window wind){
            return splashkit_lib::window_has_focus(wind);
        }

        int window_height_named(char*& name){
            return splashkit_lib::window_height((string)name);
        }

        int window_height(window wind){
            return splashkit_lib::window_height(wind);
        }

        bool window_is_fullscreen_named(char*& name){
            return splashkit_lib::window_is_fullscreen((string)name);
        }

        bool window_is_fullscreen(window wnd){
            return splashkit_lib::window_is_fullscreen(wnd);
        }

        window window_named(char* caption){
            return splashkit_lib::window_named((string)caption);
        }

        point_2d window_position_named(char*& name){
            return splashkit_lib::window_position((string)name);
        }

        point_2d window_position(window wnd){
            return splashkit_lib::window_position(wnd);
        }

        void window_set_icon(window wind,bitmap bmp){
            return splashkit_lib::window_set_icon(wind,bmp);
        }

        void window_toggle_border_named(char*& name){
            return splashkit_lib::window_toggle_border((string)name);
        }

        void window_toggle_border(window wnd){
            return splashkit_lib::window_toggle_border(wnd);
        }

        void window_toggle_fullscreen_named(char*& name){
            return splashkit_lib::window_toggle_fullscreen((string)name);
        }

        void window_toggle_fullscreen(window wnd){
            return splashkit_lib::window_toggle_fullscreen(wnd);
        }

        int window_width_named(char*& name){
            return splashkit_lib::window_width((string)name);
        }

        int window_width(window wind){
            return splashkit_lib::window_width(wind);
        }

        window window_with_focus(){
            return splashkit_lib::window_with_focus();
        }

        int window_x_named(char*& name){
            return splashkit_lib::window_x((string)name);
        }

        int window_x(window wnd){
            return splashkit_lib::window_x(wnd);
        }

        int window_y_named(char*& name){
            return splashkit_lib::window_y((string)name);
        }

        int window_y(window wnd){
            return splashkit_lib::window_y(wnd);
        }


};


#include "generated/SplashKitWasmGlue.cpp"
