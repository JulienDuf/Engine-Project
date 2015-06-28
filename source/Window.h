#pragma once
#include "Event.h"
#include "Ressource.h"
#include "EventObject.h"
#include "Vecteur2.h"

class Window : public EventObject{

private:
	SDL_Window* window;
	SDL_GLContext windowContext;

	bool activeWindow;
	Vecteur2ui size;

public:

	Window(int w, int h, const char* name) {

		window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL | SDL_RENDERER_PRESENTVSYNC);
		windowContext = SDL_GL_CreateContext(window);
		activeWindow = true;
		size = Vecteur2ui(w, h);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

		glClearColor(255, 25, 255, 255);

		EventManager::getInstance().addObject(this);
	}

	~Window() {

		SDL_DestroyWindow(window);
		SDL_GL_DeleteContext(windowContext);

		EventManager::getInstance().removeObject(this);
	}

	// true open
	// false close
	bool windowState() {
		return activeWindow;
	}

	void closeWindow() {
		activeWindow = false;
	}

	void clearWindow() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void renderWindow() {
		SDL_GL_SwapWindow(window);
	}

	Vecteur2ui getSize() {

		return size;
	}

	void reactToEvent(SDL_Event* event) {

		switch (event->type) {
		case SDL_QUIT:
			activeWindow = false;
			break;
		}
	}
};
