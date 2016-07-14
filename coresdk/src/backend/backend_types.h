//
//  BackendTypes.hpp
//  splashkit
//
//  Created by Andrew Cain on 14/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef BackendTypes_hpp
#define BackendTypes_hpp

/// An identifier for the splashkit pointers.
/// Each resource will start with an identifier to
/// Make sure that the dereferenced pointers are likely
/// to refer to the right type of data...
///
/// Convert a string for each to hex: http://www.unit-conversion.info/texttools/hexadecimal/#data
enum pointer_identifier
{
    AUDIO_PTR =     0x41554449, //"AUDI"
    MUSIC_PTR =     0x4d555349, //'MUSI'
    ANIMATION_PTR = 0x414e494d, //'ANIM'
    ANIMATION_SCRIPT_PTR = 0x41534352, //'ASCR';
    BITMAP_PTR =    0x424d502a, //'BMP*';
    SPRITE_PTR =    0x53505254, //'SPRT';
    REGION_PTR =    0x52454749, //'REGI';
    PANEL_PTR =     0x50414e4c, //'PANL';
    ARDUINO_PTR =   0x41524455, //'ARDU';
    TIMER_PTR =     0x54494d52, //'TIMR';
    FONT_PTR =      0x464f4e54, //'FONT';
    WINDOW_PTR =    0x57494e44, //'WIND';
    HTTP_REQUEST_PTR =  0x48524551, //'HREQ';
    HTTP_RESPONSE_PTR = 0x48524553, //'HRES';
    CONNECTION_PTR =    0x434f4e50, //'CONP';
    MESSAGE_PTR =       0x4d534750, //'MSGP';
    SERVER_SOCKET_PTR = 0x53565253, //'SVRS';
    NONE_PTR =          0x4e4f4e45  //'NONE';
};

#endif /* BackendTypes_hpp */
