#pragma once
#include "Texture.h"
#include "RenderObject.h"

class Image : public RenderObject{

private:

	Texture* texture;

public:

	Image(Texture* texture, Vecteur2f position) {

		this->texture = texture;
		this->position = position;

	}

	void show() {

		glDisable(GL_DEPTH_TEST);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, RessourceManager::getInstance().window->getSize().x, RessourceManager::getInstance().window->getSize().y, 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);

		glPushMatrix();
		glLoadIdentity();
		glEnable(GL_TEXTURE_2D);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glBindTexture(GL_TEXTURE_2D, texture->getID());

		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex2f(position.x, position.y);  //1

		glTexCoord2f(1, 0);
		glVertex2f(texture->getSurface()->w + position.x, position.y); //2

		glTexCoord2f(1, 1);
		glVertex2f(texture->getSurface()->w + position.x, texture->getSurface()->h + position.y); //3

		glTexCoord2f(0, 1);
		glVertex2f(position.x, texture->getSurface()->h + position.y); //4
		glEnd();

		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();

	}

	Texture* getTexture() {
		return texture;
	}
};