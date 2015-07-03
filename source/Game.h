#pragma once

class Game {

public:

	static void start() {
		
		Engine::createWindow(1366, 768);

		while (Engine::window->windowState()) {

			Engine::renderAndEvent();
		}
	}
};