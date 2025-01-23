#include "splashkit.h"

template<typename T>
std::string to_string_custom(const T& value) {
    if constexpr (std::is_same_v<T, bool>) {
        return value ? "true" : "false";
    } 
    else if constexpr (std::is_same_v<T, std::string>) {
        return value;
    }
    else {
        return std::to_string(value);
    }
}

class sprite_delegates {
private:
    int _float_function_call_count = 0;
    int _function_call_count = 0;
    bool _event_called = false;
    static sprite_delegates* current_instance;

public:
    sprite_delegates() {
        current_instance = this;
    }

    static void event_handler_wrapper(void*, int evt) {
        if (current_instance) {
            current_instance->sprite_event_handler(nullptr, evt);
        }
    }

    static void float_function_wrapper(void*, float value) {
        if (current_instance) {
            current_instance->sprite_float_function(nullptr, value);
        }
    }

    static void function_wrapper(void*) {
        if (current_instance) {
            current_instance->sprite_function(nullptr);
        }
    }

    void (*sprite_event_handler())(void*, int) {
        return &event_handler_wrapper;
    }

    void (*sprite_float_function())(void*, float) {
        return &float_function_wrapper;
    }

    void (*sprite_function())(void*) {
        return &function_wrapper;
    }

    void sprite_float_function(void* ptr, float value) {
        _float_function_call_count++;
        _event_called = true;
    }

    void sprite_function(void* ptr) {
        _function_call_count++;
        _event_called = true;
    }

    void sprite_event_handler(void* ptr, int evt) {
        _event_called = true;
    }

    void reset() {
        _float_function_call_count = 0;
        _function_call_count = 0;
        _event_called = false;
    }

    bool event_called() const { return _event_called; }
    int float_function_call_count() const { return _float_function_call_count; }
    int function_call_count() const { return _function_call_count; }
};

class key_callbacks {
private:
    key_code _key_typed = key_code(0);
    key_code _key_down = key_code(0);
    key_code _key_up = key_code(0);
    static key_callbacks* current_instance;

public:
    key_callbacks() {
        current_instance = this;
    }

    static void key_typed_wrapper(int key) {
        if (current_instance) {
            current_instance->_key_typed = key_code(key);
        }
    }

    static void key_down_wrapper(int key) {
        if (current_instance) {
            current_instance->_key_down = key_code(key);
        }
    }

    static void key_up_wrapper(int key) {
        if (current_instance) {
            current_instance->_key_up = key_code(key);
        }
    }

    void (*on_key_typed())(int) {
        return &key_typed_wrapper;
    }

    void (*on_key_down())(int) {
        return &key_down_wrapper;
    }

    void (*on_key_up())(int) {
        return &key_up_wrapper;
    }

    void reset() {
        _key_typed = key_code(0);
        _key_down = key_code(0);
        _key_up = key_code(0);
    }

    key_code get_key_typed() const { return _key_typed; }
    key_code get_key_down() const { return _key_down; }
    key_code get_key_up() const { return _key_up; }
};

class notifier_tracker {
private:
    bool _was_notified = false;
    static notifier_tracker* current_instance;

public:
    notifier_tracker() {
        current_instance = this;
    }

    static void free_notify_wrapper(void*) {
        if (current_instance) {
            current_instance->on_free_impl();
        }
    }

    void (*on_free())(void*) {
        return &free_notify_wrapper;
    }

    void on_free_impl() {
        _was_notified = true;
    }

    void reset() {
        _was_notified = false;
    }

    bool was_notified() const {
        return _was_notified;
    }
};

sprite_delegates* sprite_delegates::current_instance = nullptr;
key_callbacks* key_callbacks::current_instance = nullptr;
notifier_tracker* notifier_tracker::current_instance = nullptr;

class animation_script_cleanup {
public:
    ~animation_script_cleanup() {
        free_all_animation_scripts();
    }
};

class animation_cleanup {
private:
    animation _animation;
public:
    animation_cleanup(animation anim) : _animation(anim) {}
    ~animation_cleanup() {
        free_animation(_animation);
    }
};

class audio_cleanup {
public:
    ~audio_cleanup() {
        close_audio();
    }
};

class sound_effect_cleanup {
public:
    ~sound_effect_cleanup() {
        free_all_sound_effects();
    }
};

class music_cleanup {
public:
    ~music_cleanup() {
        free_all_music();
    }   
};

class window_cleanup {
public:
    ~window_cleanup() {
        close_all_windows();
        set_camera_position(point_at(0, 0));
    }
};

class bitmap_cleanup {
public:
    ~bitmap_cleanup() {
        free_all_bitmaps();
    }
};

class sprite_cleanup {
public:
    ~sprite_cleanup() {
        free_all_sprites();
    }
};

class font_cleanup {
public:
    ~font_cleanup() {
        free_all_fonts();
    }
};

class raspberry_cleanup {
public:
    ~raspberry_cleanup() {
        raspi_cleanup();
    }
};

class json_cleanup {
public:
    ~json_cleanup() {
        free_all_json();
    }
};

class server_cleanup {
public:
    ~server_cleanup() {
        close_all_servers();
    }
};

class connection_cleanup {
public:
    ~connection_cleanup() {
        close_all_connections();
    }
};

class resource_cleanup {
private:
    string _bundle_name;
public:
    resource_cleanup(const string& bundle_name) : _bundle_name(bundle_name) {}
    ~resource_cleanup() {
        free_resource_bundle(_bundle_name);
    }
};

class sprite_pack_cleanup {
private:
    string _sprite_pack_name;
public:
    sprite_pack_cleanup(const string& pack_name) : _sprite_pack_name(pack_name) {}
    ~sprite_pack_cleanup() {
        free_sprite_pack(_sprite_pack_name);
    }
};

class timer_cleanup {
public:
    ~timer_cleanup() {
        free_all_timers();
    }
};

class logger_cleanup {
public:
    ~logger_cleanup() {
        close_log_process();
    }
};

class layout_cleanup {
public:
    ~layout_cleanup() {
        process_events();
        reset_layout();
        set_interface_style(interface_style::SHADED_DARK_STYLE);
        process_events();
    }
};


class interface_font_cleanup {
public:
    ~interface_font_cleanup() {
        set_interface_font(get_system_font());
    }
};
