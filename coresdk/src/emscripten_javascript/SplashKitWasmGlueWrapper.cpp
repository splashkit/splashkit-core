#include "graphics.h"
#include "window_manager.h"
#include "utils.h"

using namespace splashkit_lib;

typedef window SKwindow;
class SplashKitJavascript
{
	public:
	void clear_screen(::color col){
		::clear_screen(col);
	}
	SKwindow open_window(char* name, int width, int height){
		return ::open_window((std::string)name, width, height);
	}
	void refresh_screen(){
		::refresh_screen();
	}
	color color(float r, float g, float b, float a)
	{
		return (::color){r,g,b,a};
	}
	void fill_ellipse(::color c, int x1, int y1, int x2, int y2){
		return ::fill_ellipse(c, x1, y1, x2, y2);
	}
	void fill_rectangle(::color c, int x1, int y1, int x2, int y2){
		return ::fill_rectangle(c, x1, y1, x2, y2);
	}
	void fill_triangle(::color c, int x1, int y1, int x2, int y2, int x3, int y3){
		return ::fill_triangle(c, x1, y1, x2, y2, x3, y3);
	}
};




#include "generated/SplashKitWasmGlue.cpp"