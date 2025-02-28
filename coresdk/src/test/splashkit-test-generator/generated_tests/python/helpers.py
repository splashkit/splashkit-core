import sys
import os
import contextlib
sys.path.append(os.path.join(os.path.dirname(__file__), "../../data/language_files/python"))
from splashkit_test import *

class SpriteDelegates:
   def __init__(self):
       self._event_called = False
       self._float_function_call_count = 0
       self._function_call_count = 0
       
       def float_callback(sprite, value):
           self._float_function_call_count += 1
           self._event_called = True
       
       def function_callback(sprite):
           self._function_call_count += 1
           self._event_called = True
       
       def event_callback(sprite, evt):
           self._event_called = True
           
       self._float_fn = SpriteFloatFunction(float_callback)
       self._function_fn = SpriteFunction(function_callback)
       self._event_fn = SpriteEventHandler(event_callback)
   
   def sprite_float_function(self):
       return self._float_fn
   
   def sprite_function(self):
       return self._function_fn
   
   def sprite_event_handler(self):
       return self._event_fn
   
   def reset(self):
       self._float_function_call_count = 0
       self._function_call_count = 0
       self._event_called = False

   def event_called(self):
       return self._event_called
   
   def float_function_call_count(self):
       return self._float_function_call_count
   
   def function_call_count(self):
       return self._function_call_count

class KeyCallbacks:
   def __init__(self):
       self._key_typed = KeyCode.unknown_key
       self._key_down = KeyCode.unknown_key
       self._key_up = KeyCode.unknown_key
       
       def typed_callback(key):
           self._key_typed = KeyCode(key)
       def down_callback(key):
           self._key_down = KeyCode(key)
       def up_callback(key):
           self._key_up = KeyCode(key)
           
       # Store the wrapped callbacks
       self._typed_fn = KeyCallback(typed_callback)
       self._down_fn = KeyCallback(down_callback)
       self._up_fn = KeyCallback(up_callback)
   
   def on_key_typed(self):
       return self._typed_fn
   
   def on_key_down(self):
       return self._down_fn

   def on_key_up(self):
       return self._up_fn
   
   def get_key_typed(self):
       return self._key_typed
        
   def get_key_down(self):
       return self._key_down
        
   def get_key_up(self):
       return self._key_up
    
   def reset(self):
       self._key_typed = KeyCode.unknown_key
       self._key_down = KeyCode.unknown_key
       self._key_up = KeyCode.unknown_key

class NotifierTracker:
   def __init__(self):
       self._was_notified = False
       
       def free_callback(resource):
           self._was_notified = True
           
       self._free_fn = FreeNotifier(free_callback)
   
   def on_free(self):
       return self._free_fn
   
   def reset(self):
       self._was_notified = False

   def was_notified(self):
       return self._was_notified

@contextlib.contextmanager
def animation_script_cleanup():
    try:
        yield
    finally:
        free_all_animation_scripts()

@contextlib.contextmanager
def animation_cleanup(animation):
    try:
        yield
    finally:
        free_animation(animation)

@contextlib.contextmanager
def audio_cleanup():
    try:
        yield
    finally:
        close_audio()

@contextlib.contextmanager
def sound_effect_cleanup():
    try:
        yield
    finally:
        free_all_sound_effects()

@contextlib.contextmanager
def music_cleanup():
    try:
        yield
    finally:
        free_all_music()

@contextlib.contextmanager
def window_cleanup():
    try:
        yield
    finally:
        close_all_windows()
        set_camera_position(point_at(0, 0))

@contextlib.contextmanager
def bitmap_cleanup():
    try:
        yield
    finally:
        close_all_windows()
        free_all_bitmaps()

@contextlib.contextmanager
def sprite_cleanup():
    try:
        yield
    finally:
        free_all_sprites()

@contextlib.contextmanager
def font_cleanup():
    try:
        yield
    finally:
        free_all_fonts()

@contextlib.contextmanager
def raspberry_cleanup():
    try:
        yield
    finally:
        raspi_cleanup()

@contextlib.contextmanager
def json_cleanup():
    try:
        yield
    finally:
        free_all_json()

@contextlib.contextmanager
def server_cleanup():
    try:
        yield
    finally:
        close_all_servers()

@contextlib.contextmanager
def connection_cleanup():
    try:
        yield
    finally:
        close_all_connections()

@contextlib.contextmanager
def resource_cleanup(bundle_name: str):
    try:
        yield
    finally:
        free_resource_bundle(bundle_name)

@contextlib.contextmanager
def sprite_pack_cleanup(pack_name: str):
    try:
        yield
    finally:
        free_sprite_pack(pack_name)

@contextlib.contextmanager
def timer_cleanup():
    try:
        yield
    finally:
        free_all_timers()

@contextlib.contextmanager
def logger_cleanup():
    try:
        yield
    finally:
        close_log_process()

@contextlib.contextmanager
def interface_font_cleanup():
    try:
        yield
    finally:
        set_interface_font(get_system_font())

@contextlib.contextmanager
def layout_cleanup():
    try:
        yield
    finally:
        process_events()
        reset_layout()
        set_interface_style(InterfaceStyle.shaded_dark_style)
        process_events()