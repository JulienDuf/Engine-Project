#pragma once

#include <list>
#include <stdarg.h>
#include "EventObject.h"
#include "Vecteur2.h"
#include "Control.h"

class Window : public EventObject{

private:
	SDL_Window* window;
	SDL_GLContext windowContext;

	bool activeWindow;
	Vecteur2ui size;

	std::list<Control*> controls;

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

	void addControl(Control* control) {

		if (std::find(controls.begin(), controls.end(), control) == controls.end())
			controls.push_back(control);
	}

	void removeControl(Control* control) {

		auto it = std::find(controls.begin(), controls.end(), control);

		if (it != controls.end())
			controls.erase(it);
	}

	void addControls(int argc, ...) {

		if (argc > 0) {
			va_list parametres;

			va_start(parametres, argc);
			for (int i = 0; i < argc; ++i)
				controls.push_back(va_arg(parametres, Control*));
			va_end(parametres);
		}
	}

	void clearControls() {

		auto it = controls.begin();

		for (int i = controls.size(); i > 0; --i) {
			delete (*it);
			controls.erase(it);
			it = controls.begin();
		}
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

	void setWindowSize(Vecteur2ui size) {

		this->size = size;
		SDL_SetWindowSize(window, size.x, size.y);
		glViewport(0, 0, size.x, size.y);
	}

	Vecteur2ui getSize() {

		return size;
	}

	bool reactToEvent(SDL_Event* event) {

		switch (event->type) {
		case SDL_QUIT:
			activeWindow = false;
			return true;
			break;
		}
		return false;
	}
};
