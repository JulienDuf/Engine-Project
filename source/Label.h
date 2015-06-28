#pragma once
#include "Control.h"
#include "Image.h"
#include "Text.h"

class Label : public Control {

private:

	Image* background;
	Text* text;
	Vecteur2f position;

public:

	Label() {

		text = nullptr;
		background = nullptr;

		EventManager::getInstance().addObject(this);
	}

	Label(Text* text, Vecteur2f position) : Label() {

		this->text = text;
		this->position = position;
		this->background = nullptr;
	}

	Label(Text* text, Image* background, Vecteur2f position) : Label() {

		this->text = text;
		this->position = position;
		this->background = background;
	}

	~Label() {
		delete background;
		delete text;

		EventManager::getInstance().removeObject(this);
	}

	void reactToEvent(SDL_Event* event) {

		Rectf rectTmp;

		if (background != nullptr)
			rectTmp = Rectf(background->getPosition().x, background->getPosition().y, background->getTexture()->getSurface()->w, background->getTexture()->getSurface()->h);

		else
			rectTmp = Rectf(position.x, position.y, text->getTexture()->getSurface()->w, text->getTexture()->getSurface()->h);

		if (rectTmp.contient(event->button.x, event->button.y))
			checkReaction(event->type);
		else if (event->type != SDL_MOUSEBUTTONDOWN && event->type != SDL_MOUSEBUTTONUP)
			checkReaction(event->type);
	}

	void show() {

		if (background != nullptr)
			background->show();

		text->show();
	}
};