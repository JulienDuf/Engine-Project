#pragma once
#include "Image.h"

class ScrollBar : public Control {

private:

	Button* topArrow;
	Button* bottomArrow;
	Button* scrollBar;
	Image* background;
	int notDrawElements;

public:

	ScrollBar(Button* topArrow, Button* bottomArrow, Button* scrollBar, Image* background) {

		this->topArrow = topArrow;
		this->bottomArrow = bottomArrow;
		this->scrollBar = scrollBar;
		this->background = background;

		notDrawElements = 0;
		position = background->getPosition();

		int distance = bottomArrow->getPosition().y - (topArrow->getPosition().y + topArrow->getRect().h);
		scrollBar->getTexture()->setScale(Vector2f(1, scrollBar->getRect().h / distance));
	}

	bool reactToEvent(SDL_Event* event) {

		if (notDrawElements > 0) {

			if (topArrow->isOnButton(event->button.x, event->button.y) && topArrow->getButtonState() == CLICKED) {

			}
		}
	}

	void setNotDrawsNumber(int element) {

		notDrawElements = element;
	}
};