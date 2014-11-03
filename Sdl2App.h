#ifndef SDL2APP_H_F74726CC_5FC4_11E4_8E19_10FEED04CD1C
#define SDL2APP_H_F74726CC_5FC4_11E4_8E19_10FEED04CD1C

#include "ISdl2App.h"

#include <SDL2/SDL.h>
#include <stdint.h>
#include <slm/mat4.h>
#include <slm/quat.h>

class Sdl2AppThread;

class Sdl2App : public ISdl2App {
	public:
		Sdl2App();
		virtual ~Sdl2App();

		virtual void init(SDL_Window * sdl_window, int w, int h);
		virtual void destroy();

		virtual void draw();
		virtual void processEvents();

	protected:
		bool eventHandler(SDL_Event & event);
		bool eventHandlerKeyboad(SDL_Event & event);
		bool eventHandlerWindow(SDL_Event & event);
		bool eventHandlerMouse(SDL_Event & event);
		bool eventHandlerJoystick(SDL_Event & event);
		bool eventHandlerUser(SDL_Event & event);

		void requestInputGrab();
		void releaseInputGrab();
		void processTextInput(const char *str, int len);
		void processKeyboardKey(int code, bool isdown);
		void processQuitRequest();

		void initGl();
		void renderGl();

	private:
		SDL_Window * mxSdlWindow;
		SDL_Renderer * mpSdlRenderer;
		SDL_GLContext mSdlGlContext;

		int miScreenWidth;
		int miScreenHeight;
		bool mbInputGrabActive;
		bool mbInputGrabRequested;
		bool mbWindowMinimized;
		bool mbUseRelativeMouse;
		bool mbCanUseRelativeMouse;
		bool mbRelativeMouseActive;
		bool mbRepeatKeys;

		uint32_t miStartClock;
		float mfFramesPerSecond;

		Sdl2AppThread * mpThread;

		Sdl2App(const Sdl2App &);
		Sdl2App & operator=(const Sdl2App &);

};

#endif // SDL2APP_H_F74726CC_5FC4_11E4_8E19_10FEED04CD1C
