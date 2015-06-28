#pragma once
#include "Sprite.h"
#include "Font.h"
#include "Control.h"

enum button_state { DEFAULT, OVERFLOWN, CLICKED, INACTIVE };

class Button : public Control{

private:

	Sprite* buttonTextures;
	button_state buttonState;
	Vecteur2f position;
	Rectf buttonRect;

public:

	Button() {
		buttonTextures = nullptr;

		EventManager::getInstance().addObject(this);
	}

	Button(Sprite* textures, Vecteur2f position) : Button() {

		buttonTextures = textures;
		this->position = position;
		buttonState = DEFAULT;
		buttonRect = Rectf(this->position.x, this->position.y, this->buttonTextures->getWidth(), this->buttonTextures->getHeight());

		RenderManager::getInstance().addObject(buttonTextures);
	}
	
	Button(Sprite* textures, Vecteur2f position, const char* textOnButton, Font* font, SDL_Color color) : Button() {

		buttonTextures = textures;
		this->position = position;
		buttonState = DEFAULT;

		TextTexture* text = new TextTexture(textOnButton, color, font);
		SDL_Rect surfacePosition = {(buttonTextures->getWidth() - text->getSurface()->w) / 2, (buttonTextures->getHeight() - text->getSurface()->h) / 2, 0, 0 };
		SDL_Surface* surface = buttonTextures->getTexture()->getSurface();

		for (int i = 0; i < 3; ++i) {
			SDL_BlitSurface(text->getSurface(), NULL, surface, &surfacePosition);
			surfacePosition.y += buttonTextures->getHeight();
		}
		buttonTextures->getTexture()->changeSurface(surface);
		buttonRect = Rectf(this->position.x, this->position.y, this->buttonTextures->getWidth(), this->buttonTextures->getHeight());

		RenderManager::getInstance().addObject(buttonTextures);
	}

	Button(Vecteur2f position, const char* buttonText, Font* font, SDL_Color defaultColor, SDL_Color ovreflownColor, SDL_Color clickedColor) : Button() {

		TextTexture* text = new TextTexture(buttonText, defaultColor, font);
		SDL_Surface* finalSurface = SDL_CreateRGBSurface(text->getSurface()->flags, text->getSurface()->w, text->getSurface()->h * 3, 32, 0, 0, 0, 0);

		SDL_Rect surfacePosition = { 0, 0, 0, 0 };

		SDL_BlitSurface(text->getSurface(), NULL, finalSurface, &surfacePosition);
		surfacePosition.y += text->getSurface()->h;
		delete text;

		text = new TextTexture(buttonText, ovreflownColor, font);
		SDL_BlitSurface(text->getSurface(), NULL, finalSurface, &surfacePosition);
		surfacePosition.y += text->getSurface()->h;
		delete text;

		text = new TextTexture(buttonText, clickedColor, font);
		SDL_BlitSurface(text->getSurface(), NULL, finalSurface, &surfacePosition);
		delete text;

		buttonTextures = new Sprite(position, Rectf(), new Texture(finalSurface), 1, 3);
		this->position = position;
		buttonState = DEFAULT;
		buttonRect = Rectf(this->position.x, this->position.y, this->buttonTextures->getWidth(), this->buttonTextures->getHeight());

		RenderManager::getInstance().addObject(buttonTextures);
	}

	~Button() {

		delete buttonTextures;

		EventManager::getInstance().removeObject(this);
		RenderManager::getInstance().removeObject(buttonTextures);
	}

	void reactToEvent(SDL_Event* event) {
		
		switch (event->type) {

		case SDL_MOUSEMOTION:

			if (buttonRect.contient(event->button.x, event->button.y) && buttonState != CLICKED) {
				buttonTextures->changeFrame(0, OVERFLOWN);
				buttonState = OVERFLOWN;
			}
			else{
				if (!buttonRect.contient(event->button.x, event->button.y)) {
					buttonTextures->changeFrame(0, DEFAULT);
					buttonState = DEFAULT;
				}
			}

			break;

		case SDL_MOUSEBUTTONDOWN:

			if (buttonRect.contient(event->button.x, event->button.y) && event->button.button == SDL_BUTTON_LEFT) {
				buttonTextures->changeFrame(0, CLICKED);
				buttonState = CLICKED;
			}
			break;

		case SDL_MOUSEBUTTONUP:
			if (buttonRect.contient(event->button.x, event->button.y) && event->button.button == SDL_BUTTON_LEFT) {
				buttonTextures->changeFrame(0, OVERFLOWN);
				buttonState = OVERFLOWN;
			}
			else if (event->button.button == SDL_BUTTON_LEFT){
				buttonTextures->changeFrame(0, DEFAULT);
				buttonState = DEFAULT;
			}
			break;
		}
		if (buttonState != DEFAULT)
			checkReaction(event->type);
	}
};