//
// SplashKit Generated Audio C++ Code
// DO NOT MODIFY
//

#ifndef __audio_h
#define __audio_h

#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
using std::string;
using std::vector;
using std::to_string;

/**
* Checks if SplashKit audio currently ready to be used.
* 
* Should this return `false`, you may want to use `open_audio`
* to enable audio.

* @return Returns `true` if the audio has been initalised.
*/;
bool audio_ready();
/**
* Turns off audio, stopping all current sounds effects and music.

*
*/;
void close_audio();
/**
* Starts the SplashKit audio system working.

*
*/;
void open_audio();

#endif /* __audio_h */
