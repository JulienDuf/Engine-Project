#pragma once
#include "Control.h"

class TextContainer : public Control {

private:

	Image* container;
	std::vector<Text*> texts;
	Vector2f nextTextPosition;
	Font* font;

	bool isTextOk(const char* text) {

		int w, h;
		Engine::getTextSize(text, font, w, h);

		if (nextTextPosition.x + w > container->getRect().x + container->getRect().w)
			return false;
		return true;
	}

public:

	TextContainer(Image* image, Font* font) {

		this->container = image;
		this->font = font;
		this->position = image->getPosition();
		nextTextPosition = position;
		nextTextPosition.x += 10;
		nextTextPosition.y += 10;

		RenderManager::getInstance().addObject(container);
	}

	bool reactToEvent(SDL_Event* event) {
		return false;
	}

	void addText(std::string text) {

		std::string textShow = std::string(text);
		int checkWord;
		bool ok = false;
		bool noSpace = false;
		std::vector<SDL_Surface*> surfaceTexts;
		TextTexture* texture = new TextTexture();
		SDL_Surface* surface;
		SDL_Rect surfacePosition = { 0, 0, 0, 0 };

		if (isTextOk(textShow.c_str())) {
			surfaceTexts.push_back(TTF_RenderText_Blended(font->getFont(), textShow.c_str(), { 0, 0, 0, 255 }));
			ok = true;
		}
		while (!ok) {
			checkWord = textShow.size() - 1;
			while (!isTextOk(textShow.c_str())) {

				--checkWord;
				while ((textShow[checkWord] != ' ') && (checkWord != 0)) {
					--checkWord;
					if (checkWord == 0) {
						noSpace = true;
					}
				}
				if (noSpace) {
					checkWord = textShow.size() - 1;
					while (!isTextOk(textShow.c_str())) {
						--checkWord;
						textShow.erase(checkWord, textShow.size());
					}
				}
				textShow.erase(checkWord, textShow.size());
			}
			surfaceTexts.push_back(TTF_RenderText_Blended(font->getFont(), textShow.c_str(), { 0, 0, 0, 255 }));
			textShow = text;
			textShow.erase(0, checkWord + 1);
			text = textShow;
			ok = (textShow.size() == 0);
		}

		int w, h;
		h = w = 0;
		if (surfaceTexts.size() > 1) {
			for (int i = 0; i < surfaceTexts.size(); ++i) {

				if (w < surfaceTexts[i]->w)
					w = surfaceTexts[i]->w;
				h += (surfaceTexts[i]->h + 2);
			}

			surface = SDL_CreateRGBSurface(0, w, h - 2, 32, 0, 0, 0, 0);

			for (int i = 0; i < surfaceTexts.size(); ++i) {

				SDL_BlitSurface(surfaceTexts[i], NULL, surface, &surfacePosition);
				surfacePosition.y += (surfaceTexts[i]->h + 2);
				SDL_FreeSurface(surfaceTexts[i]);
				texture->changeSurface(surface);
			}
			surfaceTexts.clear();
		}
		else {
			texture->changeSurface(surfaceTexts[0]);
		}
		texts.push_back(new Text(texture, nextTextPosition));
		nextTextPosition.y += texture->getSurface()->h + 5;
		RenderManager::getInstance().addObject(texts[texts.size() - 1]);
	}
};