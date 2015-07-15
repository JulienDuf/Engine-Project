#pragma once
#include "Font.h"
#include "Texture.h"

class TextTexture : public Texture {

private:

	SDL_Color color;
	Font* font;
	const char* text;

public:

	TextTexture() {
		font = nullptr;
	}

	TextTexture(const char* text, SDL_Color color, Font* font) {

		surface = TTF_RenderText_Blended(font->getFont(), text, color);
		this->color = color;
		this->font = font;
		this->text = text;

		load();
	}

	SDL_Color getColor() {
		return color;
	}

	Font* getFont() {
		return font;
	}

	const char* getText() {
		return text;
	}

	void setText(const char* text) {

		this->text = text;
		SDL_FreeSurface(surface);
		surface = TTF_RenderText_Blended(font->getFont(), text, color);
		reload();
	}
};