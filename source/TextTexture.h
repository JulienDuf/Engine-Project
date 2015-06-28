#pragma once
#include "Font.h"
#include "Texture.h"

class TextTexture : public Texture {

private:

	SDL_Color color;
	Font* font;
	const char* text;

public:

	TextTexture(const char* text, SDL_Color color, Font* font) {

		surface = TTF_RenderText_Blended(font->getFont(), text, color);
		this->color = color;
		this->font = font;
		this->text = text;

		if (surface != nullptr) {
			glBindTexture(GL_TEXTURE_2D, ID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
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
};