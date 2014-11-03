#include "Sdl2App.h"
#include "Threads.h"

#include "GL/gl.h"
#include "GL/glu.h"

struct Sdl2AppThread : public ThreadBase {
	Sdl2AppThread(Sdl2App * app) : App(app), KeepRunning(true) {
	}

	bool stop() {
		KeepRunning = false;
		return join();
	}

	virtual void run();
	Sdl2App * App;
	volatile bool KeepRunning;
};

void Sdl2AppThread::run() {
	printf("Thread ON\n");

	while (KeepRunning) {
	}

	printf("Thread OFF\n");
}

Sdl2App::Sdl2App() : mxSdlWindow(NULL) {
	mpSdlRenderer = NULL;

	mpThread = new Sdl2AppThread(this);
	if (!mpThread->start()) {
		delete mpThread;
		mpThread = NULL;
	}
}

Sdl2App::~Sdl2App() {
	printf("Waiting for thread to stop...\n");
	if (NULL != mpThread) {
		mpThread->stop();
		delete mpThread;
		mpThread = NULL;
	}

}

void Sdl2App::init(SDL_Window * sdl_window, int w, int h) {
	mxSdlWindow = sdl_window;

	miStartClock = SDL_GetTicks();
	mfFramesPerSecond = 0.0;

	miScreenWidth = w;
	miScreenHeight = h;
	mbInputGrabActive = false;
	mbInputGrabRequested = false;
	mbWindowMinimized = false;
	mbUseRelativeMouse = true;
	mbCanUseRelativeMouse = true;
	mbRelativeMouseActive = false;
	mbRepeatKeys = false;

	printf ("Initializing renderer\n");
	int i;
	int num = SDL_GetNumRenderDrivers();
	for (i=0;i<num;i++) {
		SDL_RendererInfo info;
		SDL_GetRenderDriverInfo(i, &info);
		printf ("Renderer %d: %s\n",i, info.name);
	}

	Uint32 window_flags = SDL_GetWindowFlags(mxSdlWindow);
	if (!(window_flags & SDL_WINDOW_OPENGL)) {
		printf ("Window doesn't support OpenGL, using software rendering\n");
		mpSdlRenderer = SDL_CreateRenderer(mxSdlWindow, -1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_TARGETTEXTURE);
	} else {
		mpSdlRenderer = SDL_CreateRenderer(mxSdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	}

	mSdlGlContext = SDL_GL_CreateContext(mxSdlWindow);
	if (!mSdlGlContext) {
		fprintf(stderr, "SDL_GL_CreateContext(): %s\n", SDL_GetError());
	}

	initGl();
}

void Sdl2App::destroy() {
	if (mSdlGlContext) {
		SDL_GL_DeleteContext(mSdlGlContext);
	}
	if (NULL != mpSdlRenderer) {
		SDL_DestroyRenderer (mpSdlRenderer);
		mpSdlRenderer = NULL;
	}

	mxSdlWindow = NULL;
}

void Sdl2App::initGl() {
	SDL_DisplayMode mode;
	SDL_GetCurrentDisplayMode(0, &mode);
	printf("Screen BPP: %d\n", SDL_BITSPERPIXEL(mode.format));
	printf("\n");
	printf("Vendor     : %s\n", glGetString(GL_VENDOR));
	printf("Renderer   : %s\n", glGetString(GL_RENDERER));
	printf("Version    : %s\n", glGetString(GL_VERSION));
	printf("Extensions : %s\n", glGetString(GL_EXTENSIONS));
	printf("\n");

	int status;
	int value;

    status = SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &value);
    if (!status) {
        printf("SDL_GL_RED_SIZE: %d\n", value);
    } else {
        printf("Failed to get SDL_GL_RED_SIZE: %s\n", SDL_GetError());
    }
    status = SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &value);
    if (!status) {
        printf("SDL_GL_GREEN_SIZE: %d\n", value);
    } else {
        printf("Failed to get SDL_GL_GREEN_SIZE: %s\n", SDL_GetError());
    }
    status = SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &value);
    if (!status) {
        printf("SDL_GL_BLUE_SIZE: %d\n", value);
    } else {
        printf("Failed to get SDL_GL_BLUE_SIZE: %s\n", SDL_GetError());
    }
    status = SDL_GL_GetAttribute(SDL_GL_DEPTH_SIZE, &value);
    if (!status) {
        printf("SDL_GL_DEPTH_SIZE: %d\n", value);
    } else {
        printf("Failed to get SDL_GL_DEPTH_SIZE: %s\n", SDL_GetError());
    }

	status = SDL_GL_GetAttribute(SDL_GL_MULTISAMPLEBUFFERS, &value);
	if (!status) {
		printf("SDL_GL_MULTISAMPLEBUFFERS: %d\n", value);
	} else {
		printf("Failed to get SDL_GL_MULTISAMPLEBUFFERS: %s\n", SDL_GetError());
	}
	status = SDL_GL_GetAttribute(SDL_GL_MULTISAMPLESAMPLES, &value);
	if (!status) {
		printf("SDL_GL_MULTISAMPLESAMPLES: %d\n", value);
	} else {
		printf("Failed to get SDL_GL_MULTISAMPLESAMPLES: %s\n", SDL_GetError());
	}

	status = SDL_GL_GetAttribute(SDL_GL_ACCELERATED_VISUAL, &value);
	if (!status) {
		printf("SDL_GL_ACCELERATED_VISUAL: %d\n", value);
	} else {
		printf("Failed to get SDL_GL_ACCELERATED_VISUAL: %s\n", SDL_GetError());
	}

	/* Set rendering settings */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -20.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glShadeModel(GL_SMOOTH);
}

void Sdl2App::renderGl() {

    static float color[8][3] = {
        {1.0, 1.0, 0.0},
        {1.0, 0.0, 0.0},
        {0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 1.0, 1.0},
        {1.0, 1.0, 1.0},
        {1.0, 0.0, 1.0},
        {0.0, 0.0, 1.0}
    };

    static float cube[8][3] = {
        {0.5, 0.5, -0.5},
        {0.5, -0.5, -0.5},
        {-0.5, -0.5, -0.5},
        {-0.5, 0.5, -0.5},
        {-0.5, 0.5, 0.5},
        {0.5, 0.5, 0.5},
        {0.5, -0.5, 0.5},
        {-0.5, -0.5, 0.5}
    };

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_QUADS);

    glColor3fv(color[0]);
    glVertex3fv(cube[0]);
    glColor3fv(color[1]);
    glVertex3fv(cube[1]);
    glColor3fv(color[2]);
    glVertex3fv(cube[2]);
    glColor3fv(color[3]);
    glVertex3fv(cube[3]);

    glColor3fv(color[3]);
    glVertex3fv(cube[3]);
    glColor3fv(color[4]);
    glVertex3fv(cube[4]);
    glColor3fv(color[7]);
    glVertex3fv(cube[7]);
    glColor3fv(color[2]);
    glVertex3fv(cube[2]);

    glColor3fv(color[0]);
    glVertex3fv(cube[0]);
    glColor3fv(color[5]);
    glVertex3fv(cube[5]);
    glColor3fv(color[6]);
    glVertex3fv(cube[6]);
    glColor3fv(color[1]);
    glVertex3fv(cube[1]);

    glColor3fv(color[5]);
    glVertex3fv(cube[5]);
    glColor3fv(color[4]);
    glVertex3fv(cube[4]);
    glColor3fv(color[7]);
    glVertex3fv(cube[7]);
    glColor3fv(color[6]);
    glVertex3fv(cube[6]);

    glColor3fv(color[5]);
    glVertex3fv(cube[5]);
    glColor3fv(color[0]);
    glVertex3fv(cube[0]);
    glColor3fv(color[3]);
    glVertex3fv(cube[3]);
    glColor3fv(color[4]);
    glVertex3fv(cube[4]);

    glColor3fv(color[6]);
    glVertex3fv(cube[6]);
    glColor3fv(color[1]);
    glVertex3fv(cube[1]);
    glColor3fv(color[2]);
    glVertex3fv(cube[2]);
    glColor3fv(color[7]);
    glVertex3fv(cube[7]);

    glEnd();

    glMatrixMode(GL_MODELVIEW);
    glRotatef(5.0, 1.0, 1.0, 1.0);
}

void Sdl2App::draw() {
	if (mSdlGlContext) {
		int w, h;
		SDL_GL_MakeCurrent(mxSdlWindow, mSdlGlContext);
		SDL_GetWindowSize(mxSdlWindow, &w, &h);
		glViewport(0, 0, w, h);

		renderGl();
		SDL_GL_SwapWindow(mxSdlWindow);
	}

	int delta = SDL_GetTicks() - miStartClock;
	miStartClock = SDL_GetTicks();
	if (delta != 0) {
		mfFramesPerSecond = 1000.0 / delta;
		//printf("%2.2f fps\n", mfFramesPerSecond);
	}
}

void Sdl2App::processEvents() {
	SDL_Event event;
	while ( SDL_PollEvent( &event ) ) {
			eventHandler(event);
	}
}

bool Sdl2App::eventHandler(SDL_Event & event) {
	printf("eventHandler\n");
	switch(event.type) {
		case SDL_QUIT: {
			processQuitRequest();
			return true;
		}

		case SDL_TEXTINPUT: {
			processTextInput(event.text.text, strlen(event.text.text));
			return true;
		}

		case SDL_KEYDOWN:
		case SDL_KEYUP:
			return eventHandlerKeyboad(event);

		case SDL_WINDOWEVENT:
			return eventHandlerWindow(event);

		case SDL_MOUSEMOTION:
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEWHEEL:
			return eventHandlerMouse(event);

		case SDL_JOYBUTTONDOWN:
		case SDL_JOYBUTTONUP:
		case SDL_JOYAXISMOTION:
		case SDL_JOYHATMOTION:
		case SDL_JOYBALLMOTION:
			return eventHandlerJoystick(event);

		case SDL_USEREVENT:
			return eventHandlerUser(event);
	}

	return false;
}

void printModifiers(Uint16 mod) {
	printf( "Modifers: " );

	if( mod == KMOD_NONE ) { // If there are none then say so and return
		printf( "None\n" );
		return;
	}

	if( mod & KMOD_NUM )    printf( "NUMLOCK " );
	if( mod & KMOD_CAPS )   printf( "CAPSLOCK " );
	if( mod & KMOD_LCTRL )  printf( "LCTRL " );
	if( mod & KMOD_RCTRL )  printf( "RCTRL " );
	if( mod & KMOD_RSHIFT ) printf( "RSHIFT " );
	if( mod & KMOD_LSHIFT ) printf( "LSHIFT " );
	if( mod & KMOD_RALT )   printf( "RALT " );
	if( mod & KMOD_LALT )   printf( "LALT " );
	if( mod & KMOD_CTRL )   printf( "CTRL " );
	if( mod & KMOD_SHIFT )  printf( "SHIFT " );
	if( mod & KMOD_ALT )    printf( "ALT " );
	printf( "\n" );
}

static void printKeyEventInfo( SDL_KeyboardEvent & key_event ) {
	if( key_event.type == SDL_KEYUP ) { // Is it a key release or a key press?
		printf( "Release:- " );
	} else {
		printf( "Press:- " );
	}

	printf( "Scancode: 0x%02X", key_event.keysym.scancode );
	printf( ", Name: %s", SDL_GetKeyName( key_event.keysym.sym ) );
	printf( "\n" );

	printModifiers(key_event.keysym.mod);
}

bool Sdl2App::eventHandlerKeyboad(SDL_Event & event) {
	printf("Key\n");
	printKeyEventInfo(*(SDL_KeyboardEvent*)(&event));
	switch (event.type) {
		case SDL_KEYDOWN:
		case SDL_KEYUP: {
			if(mbRepeatKeys || !event.key.repeat) {
				processKeyboardKey(event.key.keysym.sym, SDL_PRESSED == event.key.state);
			}
			return true;
		}
		default:
			return false;
	}
}

// https://wiki.libsdl.org/SDL_WindowEventID

bool Sdl2App::eventHandlerWindow(SDL_Event & event) {
	switch (event.type) {
		case SDL_WINDOWEVENT: {
			switch(event.window.event) {
				case SDL_WINDOWEVENT_CLOSE: {
					processQuitRequest();
					return true;
				}

				case SDL_WINDOWEVENT_FOCUS_GAINED: {
					mbInputGrabRequested = true;
					return true;
				}

				case SDL_WINDOWEVENT_ENTER: {
					requestInputGrab();
					return true;
				}

				case SDL_WINDOWEVENT_LEAVE:
				case SDL_WINDOWEVENT_FOCUS_LOST: {
					releaseInputGrab();
					return true;
				}

				case SDL_WINDOWEVENT_MINIMIZED: {
					mbWindowMinimized = true;
					return true;
				}

				case SDL_WINDOWEVENT_MAXIMIZED:
				case SDL_WINDOWEVENT_RESTORED: {
					mbWindowMinimized = false;
					return true;
				}

				case SDL_WINDOWEVENT_RESIZED: {
					printf("SDL_WINDOWEVENT_RESIZED: %dx%d\n", event.window.data1, event.window.data2);
					return true;
				}

				case SDL_WINDOWEVENT_SIZE_CHANGED: {
					printf("SDL_WINDOWEVENT_SIZE_CHANGED: %dx%d\n", event.window.data1, event.window.data2);
					miScreenWidth = event.window.data1;
					miScreenHeight = event.window.data2;
					return true;
				}

				default:
					return false;
			}
		}

		default:
			return false;
	}
}

bool Sdl2App::eventHandlerMouse(SDL_Event & event) {
	switch(event.type) {
		case SDL_MOUSEMOTION: {
			printf("MOTION: x: %u, y: %u, xrel:%d, yrel: %d\n",
				event.motion.x,
				event.motion.y,
				event.motion.xrel,
				event.motion.yrel
			);
			return true;
		}

		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP: {
			printf("BUTTON: button: %d, state: %s, x: %u, y: %u\n",
				event.button.button,
				SDL_MOUSEBUTTONDOWN == event.type ? "Down" : "Up",
				event.button.x,
				event.button.y
			);
			return true;
		}

		case SDL_MOUSEWHEEL: {
			printf("WHEEL: which: %d, x: %u, y: %u\n",
				event.wheel.which,
				event.wheel.x,
				event.wheel.y
			);
			return true;
		}

		default:
			return false;
	}
}

bool Sdl2App::eventHandlerJoystick(SDL_Event & event) {
	switch(event.type) {
		case SDL_JOYBUTTONDOWN:
		case SDL_JOYBUTTONUP: {
			printf("JOY%d.BUTTON%d: %s\n", event.button.which, event.button.button, (event.button.state == SDL_PRESSED) ? "DOWN" : "UP");
			return true;
		}

		case SDL_JOYAXISMOTION: {
			printf("JOY%d.AXIS%d: %d\n", event.jaxis.which, event.jaxis.axis, event.jaxis.value);
			return true;
		}

		case SDL_JOYHATMOTION: {
			printf("JOY%d.PAD%d: %d\n", event.jhat.which, event.jhat.hat, event.jhat.value);
			return true;
		}

		case SDL_JOYBALLMOTION: {
			printf("JOY%d.BALL%d: %d, %d\n", event.jball.which, event.jball.ball, event.jball.xrel, event.jball.yrel);
			return true;
		}

		default:
			return false;
	}
}

bool Sdl2App::eventHandlerUser(SDL_Event & event) {
	switch(event.type) {
		case SDL_USEREVENT: {
			printf("USR%d\n", event.user.code);
			return true;
		}

		default:
			return false;
	}
}

void Sdl2App::requestInputGrab() {
	mbInputGrabActive = true;
	SDL_ShowCursor(SDL_FALSE);
	if (mbCanUseRelativeMouse && mbUseRelativeMouse) {
		if(SDL_SetRelativeMouseMode(SDL_TRUE) >= 0) {
			SDL_SetWindowGrab(mxSdlWindow, SDL_TRUE);
			mbRelativeMouseActive = true;
		} else {
			SDL_SetWindowGrab(mxSdlWindow, SDL_FALSE);
			mbCanUseRelativeMouse = false;
			mbRelativeMouseActive = false;
		}
	}
	mbInputGrabRequested = false;
}

void Sdl2App::releaseInputGrab() {
	mbInputGrabActive = false;
	SDL_ShowCursor(SDL_TRUE);
	if (mbRelativeMouseActive) {
		SDL_SetRelativeMouseMode(SDL_FALSE);
		SDL_SetWindowGrab(mxSdlWindow, SDL_FALSE);
		mbRelativeMouseActive = false;
	}
	mbInputGrabRequested = false;
}

void Sdl2App::processTextInput(const char *str, int len) {
}

void Sdl2App::processKeyboardKey(int code, bool isdown) {
}

void Sdl2App::processQuitRequest() {
	exit(0);
}

