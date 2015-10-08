#pragma once
#include "Control.h"

class TextBox : public Control {

private:

	Image* textBox;
	Text* textInBox;
	std::string text;
	bool active;
	bool noLetter;

	void setText() {

		int w, h;
		std::string drawText = text;
		Engine::getTextSize(text.c_str(), textInBox->getTexture()->getFont(), w, h);

		if (w < (textBox->getRect().w - 20))
			textInBox->getTexture()->setText(text.c_str());
		
		else {

			do {
				drawText.erase(0, 1);
				Engine::getTextSize(drawText.c_str(), textInBox->getTexture()->getFont(), w, h);
			} while (w > (textBox->getRect().w - 20));
			textInBox->getTexture()->setText(drawText.c_str());
		}
		
		textInBox->setPosition(Vecteur2f((textBox->getPosition().x + 10), textBox->getRect().y + ((textBox->getRect().h - textInBox->getTexture()->getSize().y) / 2)));

	}

public:

	TextBox(Image* box, Font* font) {

		this->textBox = box;
		text = std::string(" ");
		noLetter = true;
		textInBox = new Text(new TextTexture(" ", { 0, 0, 0, 0 }, font), Vecteur2f((box->getPosition().x + 5), (box->getRect().y + box->getRect().h) / 2));
		active = false;

		position = textBox->getPosition();

		RenderManager::getInstance().addObject(textBox);
		RenderManager::getInstance().addObject(textInBox);
		EventManager::getInstance().addObject(this);
	}

	~TextBox() {

		RenderManager::getInstance().removeObject(textBox);
		RenderManager::getInstance().removeObject(textInBox);
		EventManager::getInstance().removeObject(this);

		delete textBox;
		delete textInBox;
	}

	bool reactToEvent(SDL_Event* event) {

		char* textTmp = nullptr;
		std::string accent;
		accent.append("Ã");
		accent.push_back(-96);

		SDL_StartTextInput();
		switch (event->type) {

		case SDL_TEXTINPUT:

			if (active) {

				if (!strcmp(event->text.text, "Ã©"))
					textTmp = "é";
				else if (!strcmp(event->text.text, "Ã‰"))
					textTmp = "É";
				else if (!strcmp(event->text.text, "Ã¨"))
					textTmp = "è";
				else if (!strcmp(event->text.text, "Ãˆ"))
					textTmp = "È";
				else if (!strcmp(event->text.text, accent.c_str()))
					textTmp = "à";
				else if (!strcmp(event->text.text, "Ã€"))
					textTmp = "À";
				else if (!strcmp(event->text.text, "Ã§"))
					textTmp = "ç";
				else if (!strcmp(event->text.text, "Ã‡"))
					textTmp = "Ç";
				else if (!strcmp(event->text.text, "Ãª"))
					textTmp = "ê";
				else if (!strcmp(event->text.text, "ÃŠ"))
					textTmp = "Ê";
				else
					textTmp = event->text.text;
				if (noLetter) {
					text.clear();
					noLetter = false;
				}
				text.append(textTmp);
				setText();
			}
			break;

		case SDL_MOUSEBUTTONUP:

			if (textBox->getRect().contain(event->button.x, event->button.y))
				active = true;
			else
				active = false;
			break;

		case SDL_KEYDOWN:

			if (active) {

				switch (event->key.keysym.scancode) {

				case SDL_SCANCODE_TAB:

					active = false;
					break;
				case SDL_SCANCODE_BACKSPACE:

					if (text.size() > 0)
						text.pop_back();
					if (text.size() == 0) {
						text.push_back(' ');
						noLetter = true;
					}

					setText();
					break;

				}
			}
			break;
		case SDL_KEYUP:

			if (active) {

				switch (event->key.keysym.scancode) {

				case SDL_SCANCODE_TAB:

					active = false;
					break;
				}
			}
			break;
		}

		if (active)
			return checkReaction(event->type);

		return false;
	}

	std::string getText() {
		return text;
	}
	
	void setText(std::string text) {
		this->text = text;
		if (text[0] == ' ')
			noLetter = true;
		setText();
	}
}; 