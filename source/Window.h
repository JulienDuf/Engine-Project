#pragma once

#include <list>
#include <stdarg.h>
#include "EventObject.h"
#include "Vector2.h"
#include "Control.h"

class Window : public EventObject{

private:
	SDL_Window* window;
	SDL_GLContext windowContext;

	bool activeWindow;
	bool fullScreen;
	bool boderLess;
	Vector2ui size;

	std::map<std::string, Control*> controls;

public:
	
	Window(unsigned int w, unsigned int h, const char* name) {

		fullScreen = false;
		boderLess = false;

		window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL | SDL_RENDERER_PRESENTVSYNC);
		windowContext = SDL_GL_CreateContext(window);
		activeWindow = true;
		size = Vector2ui(w, h);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_MakeCurrent(window, windowContext);

#if defined (_WIN32)
		glewInit();
#endif
		EventManager::getInstance().addObject(this);
	}

	~Window() {

		SDL_DestroyWindow(window);
		SDL_GL_DeleteContext(windowContext);

		EventManager::getInstance().removeObject(this);
	}

	void addControl(const char* name, Control* control) {

		if (controls.find(name) == controls.end())
			controls[name] = control;
	}

	void removeControl(const char* name) {

		if (controls.find(name) != controls.end())
			controls.erase(name);
	}

	Control* getControl(const char* name) {
		if (controls.find(name) != controls.end())
			return controls[name];
	}

	void clearControls() {

		auto it = controls.begin();

		for (int i = controls.size(); i > 0; --i) {
			delete (*it).second;
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

	void setWindowSize(Vector2ui size) {

		this->size = size;
		SDL_SetWindowSize(window, size.x, size.y);
		glViewport(0, 0, size.x, size.y);
	}

	void setWindowFullScreen() {

		fullScreen = true;
		boderLess = false;

		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	}

	void setWindowBorderLess() {

		fullScreen = false;
		boderLess = true;

		SDL_SetWindowBordered(window, SDL_FALSE);
	}

	void setWindowBordered() {

		fullScreen = false;
		boderLess = true;

		SDL_SetWindowBordered(window, SDL_TRUE);
	}

	Vector2ui getSize() {

		return size;
	}

	bool reactToEvent(SDL_Event* event) {

		switch (event->type) {
			case SDL_QUIT:
				activeWindow = false;
				return true;

			case SDL_KEYDOWN:

				if (event->key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
					activeWindow = false;
					return true;
				}
			default:break;
		}
		return false;
	}
};
