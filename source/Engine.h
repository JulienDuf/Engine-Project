#pragma once
#include <iostream>
#include <time.h>
#include "EventManager.h"
#include "RenderManager.h"
#include "RessourceManager.h"
#include "Button.h"
#include "Label.h"
#include "TextTexture.h"

namespace Engine {

	Window* window;

	void init() {

		SDL_Init(SDL_INIT_VIDEO);
		TTF_Init();
		IMG_Init(IMG_INIT_PNG);
		Mix_Init(MIX_INIT_OGG);
	}

	void close() {
		SDL_Quit();
		TTF_Quit();
		IMG_Quit();
		Mix_Quit();
	}

	void renderAndEvent() {

		EventManager::getInstance().checkEvent();
		window->clearWindow();
		RenderManager::getInstance().render(window->getSize().x, window->getSize().y);
		window->renderWindow();
	}

	void createWindow(int w, int h) {

		window = new Window(w, h, "");
	}
}