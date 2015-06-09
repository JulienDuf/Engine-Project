#pragma once
#include <iostream>

class Window {

private:
	SDL_Window* window;
	SDL_GLContext windowContext;
	SDL_Event event;

	bool activeWindow;
public:

	Window(int w, int h, const char* name) {
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

		window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL);
		windowContext = SDL_GL_CreateContext(window);
		SDL_GL_MakeCurrent(window, windowContext);
		activeWindow = true;
	}

	// true open
	// false close
	bool windowState() {
		return activeWindow;
	}

	void renderWindow() {
		SDL_GL_SwapWindow(window);
	}

	void pollEvent() {

		while (SDL_PollEvent(&event)) {

			switch (event.type) {
			case SDL_QUIT:
				activeWindow = false;
				break;
			}
		}
	}
};
