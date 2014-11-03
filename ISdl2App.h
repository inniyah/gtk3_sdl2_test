#ifndef ISDL2APP_H_47F8A86A_62C3_11E4_B6C6_10FEED04CD1C
#define ISDL2APP_H_47F8A86A_62C3_11E4_B6C6_10FEED04CD1C

struct SDL_Window;

struct ISdl2App {
	virtual ~ISdl2App() { }
	virtual void init(SDL_Window * sdl_window, int w, int h) = 0;
	virtual void destroy() = 0;
	virtual void draw() = 0;
	virtual void processEvents() = 0;
};

#endif
