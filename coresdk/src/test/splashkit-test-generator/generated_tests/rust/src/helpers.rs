use splashkit_backend::*;
use std::sync::{Arc, Mutex};

pub struct SpriteDelegates {
  event_called: Arc<Mutex<bool>>,
  float_function_call_count: Arc<Mutex<i32>>,
  function_call_count: Arc<Mutex<i32>>,
}

impl SpriteDelegates {
    pub fn new() -> Self {
        SpriteDelegates {
            event_called: Arc::new(Mutex::new(false)),
            float_function_call_count: Arc::new(Mutex::new(0)),
            function_call_count: Arc::new(Mutex::new(0)),
        }
    }

    pub fn sprite_float_function(&self) -> SpriteFloatFunction {
        let event_called = self.event_called.clone();
        let count = self.float_function_call_count.clone();
        Box::new(move |_ptr, _value| {
            *count.lock().unwrap() += 1;
            *event_called.lock().unwrap() = true;
        })
    }

    pub fn sprite_function(&self) -> SpriteFunction {
        let event_called = self.event_called.clone();
        let count = self.function_call_count.clone();
        Box::new(move |_ptr| {
            *count.lock().unwrap() += 1;
            *event_called.lock().unwrap() = true;
        })
    }

    pub fn sprite_event_handler(&self) -> SpriteEventHandler {
        let event_called = self.event_called.clone();
        Box::new(move |_ptr, _evt| {
            *event_called.lock().unwrap() = true;
        })
    }

    pub fn reset(&self) {
        *self.float_function_call_count.lock().unwrap() = 0;
        *self.function_call_count.lock().unwrap() = 0;
        *self.event_called.lock().unwrap() = false;
    }

    pub fn event_called(&self) -> bool {
        *self.event_called.lock().unwrap()
    }

    pub fn float_function_call_count(&self) -> i32 {
        *self.float_function_call_count.lock().unwrap()
    }

    pub fn function_call_count(&self) -> i32 {
        *self.function_call_count.lock().unwrap()
    }
}

struct KeyState {
    typed: KeyCode,
    down: KeyCode,
    up: KeyCode,
}

pub struct KeyCallbacks {
    state: Arc<Mutex<KeyState>>,
}

impl KeyCallbacks {
    pub fn new() -> Self {
        let state = Arc::new(Mutex::new(KeyState {
            typed: KeyCode::UnknownKey,
            down: KeyCode::UnknownKey,
            up: KeyCode::UnknownKey,
        }));

        KeyCallbacks {
            state,
        }
    }

    pub fn on_key_typed(&self) -> KeyCallback {
        let state = self.state.clone();
        Box::new(move |key| {
            state.lock().unwrap().typed = KeyCode::from(key);
        })
    }

    pub fn on_key_down(&self) -> KeyCallback {
        let state = self.state.clone();
        Box::new(move |key| {
            state.lock().unwrap().down = KeyCode::from(key);
        })
    }

    pub fn on_key_up(&self) -> KeyCallback {
        let state = self.state.clone();
        Box::new(move |key| {
            state.lock().unwrap().up = KeyCode::from(key);
        })
    }

    pub fn get_key_typed(&self) -> KeyCode {
        self.state.lock().unwrap().typed
    }

    pub fn get_key_down(&self) -> KeyCode {
        self.state.lock().unwrap().down
    }

    pub fn get_key_up(&self) -> KeyCode {
        self.state.lock().unwrap().up
    }

    pub fn reset(&self) {
        let mut state = self.state.lock().unwrap();
        state.typed = KeyCode::UnknownKey;
        state.down = KeyCode::UnknownKey;
        state.up = KeyCode::UnknownKey;
    }
}

pub struct NotifierTracker {
    was_notified: Arc<Mutex<bool>>,
}

impl NotifierTracker {
    pub fn new() -> Self {
        NotifierTracker {
            was_notified: Arc::new(Mutex::new(false)),
        }
    }

    pub fn on_free(&self) -> FreeNotifier {
        let was_notified = self.was_notified.clone();
        Box::new(move |_ptr| {
            *was_notified.lock().unwrap() = true;
        })
    }

    pub fn reset(&self) {
        *self.was_notified.lock().unwrap() = false;
    }

    pub fn was_notified(&self) -> bool {
        *self.was_notified.lock().unwrap()
    }
}

pub struct AnimationScriptCleanup;
impl AnimationScriptCleanup {
    pub fn new() -> Self { Self }
}
impl Drop for AnimationScriptCleanup {
    fn drop(&mut self) {
        free_all_animation_scripts();
    }
}

pub struct AnimationCleanup {
    animation: Animation,
}
impl AnimationCleanup {
    pub fn new(animation: Animation) -> Self {
        Self { animation }
    }
}
impl Drop for AnimationCleanup {
    fn drop(&mut self) {
        free_animation(self.animation);
    }
}

pub struct AudioCleanup;
impl AudioCleanup {
    pub fn new() -> Self { Self }
}
impl Drop for AudioCleanup {
    fn drop(&mut self) {
        close_audio();
    }
}

pub struct SoundEffectCleanup;
impl SoundEffectCleanup {
    pub fn new() -> Self { Self }
}
impl Drop for SoundEffectCleanup {
    fn drop(&mut self) {
        free_all_sound_effects();
    }
}

pub struct MusicCleanup;
impl MusicCleanup {
    pub fn new() -> Self { Self }
}
impl Drop for MusicCleanup {
    fn drop(&mut self) {
        free_all_music();
    }
}

pub struct WindowCleanup;
impl WindowCleanup {
    pub fn new() -> Self { Self }
}
impl Drop for WindowCleanup {
    fn drop(&mut self) {
        close_all_windows();
        set_camera_position(point_at(0.0, 0.0));
    }
}

pub struct BitmapCleanup;
impl BitmapCleanup {
    pub fn new() -> Self { Self }
}
impl Drop for BitmapCleanup {
    fn drop(&mut self) {
        close_all_windows();
        free_all_bitmaps();
    }
}

pub struct SpriteCleanup;
impl SpriteCleanup {
    pub fn new() -> Self { Self }
}
impl Drop for SpriteCleanup {
    fn drop(&mut self) {
        free_all_sprites();
    }
}

pub struct FontCleanup;
impl FontCleanup {
    pub fn new() -> Self { Self }
}
impl Drop for FontCleanup {
    fn drop(&mut self) {
        free_all_fonts();
    }
}

pub struct RaspberryCleanup;
impl RaspberryCleanup {
    pub fn new() -> Self { Self }
}
impl Drop for RaspberryCleanup {
    fn drop(&mut self) {
        raspi_cleanup();
    }
}

pub struct JsonCleanup;
impl JsonCleanup {
    pub fn new() -> Self { Self }
}
impl Drop for JsonCleanup {
    fn drop(&mut self) {
        free_all_json();
    }
}

pub struct ServerCleanup;
impl ServerCleanup {
    pub fn new() -> Self { Self }
}
impl Drop for ServerCleanup {
    fn drop(&mut self) {
        close_all_servers();
    }
}

pub struct ConnectionCleanup;
impl ConnectionCleanup {
    pub fn new() -> Self { Self }
}
impl Drop for ConnectionCleanup {
    fn drop(&mut self) {
        close_all_connections();
    }
}

pub struct ResourceCleanup {
    bundle_name: String,
}
impl ResourceCleanup {
    pub fn new(bundle_name: String) -> Self {
        Self { bundle_name }
    }
}
impl Drop for ResourceCleanup {
    fn drop(&mut self) {
        if has_resource_bundle(self.bundle_name.clone()) {  
            free_resource_bundle(self.bundle_name.clone());
        }
    }
}

pub struct SpritePackCleanup {
    pack_name: String,
}
impl SpritePackCleanup {
    pub fn new(pack_name: String) -> Self {
        Self { pack_name }
    }
}
impl Drop for SpritePackCleanup {
    fn drop(&mut self) {
        free_sprite_pack(self.pack_name.clone());
    }
}

pub struct TimerCleanup;
impl TimerCleanup {
    pub fn new() -> Self { Self }
}
impl Drop for TimerCleanup {
    fn drop(&mut self) {
        free_all_timers();
    }
}

pub struct LoggerCleanup;
impl LoggerCleanup {
    pub fn new() -> Self { Self }
}
impl Drop for LoggerCleanup {
    fn drop(&mut self) {
        close_log_process();
    }
}

pub struct LayoutCleanup;
impl LayoutCleanup {
    pub fn new() -> Self { Self }
}
impl Drop for LayoutCleanup {
    fn drop(&mut self) {
        process_events();
        reset_layout();
        set_interface_style(InterfaceStyle::ShadedDarkStyle);
        process_events();
    }
}

pub struct InterfaceFontCleanup;
impl InterfaceFontCleanup {
    pub fn new() -> Self { Self }
}
impl Drop for InterfaceFontCleanup {
    fn drop(&mut self) {
        set_interface_font(get_system_font());
    }
}
