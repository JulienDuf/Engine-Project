#pragma once
#include "Engine.h"
#include "RenderedModel.h"
#include "Button.h"
#include "ScrollBar.h"
#include "Label.h"
#include "TextBox.h"
#include "TextContainer.h"
#include "Chrono.h"

class Game {

public:

	static void start() {
		
		Engine::createWindow(1920, 1080);

		while (Engine::window->windowState()) {

			Engine::renderAndEvent();
		}
	}
};
