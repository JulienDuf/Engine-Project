#pragma once

#include <GL/gl.h>
#include "Texture.h"
#include "RenderObject.h"
#include "Rect.h"

class Image : public RenderObject {

private:

	Texture* texture;
	Rectf rect;

public:

	Image(Texture* texture, Vector2f position) {

		this->texture = texture;
		this->position = position;
		this->rect = Rectf(position.x, position.y, (float) texture->getSize().x, (float) texture->getSize().y);

	}

	void show(int w, int h) {

		glDisable(GL_DEPTH_TEST);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, w, h, 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);

		glPushMatrix();
		glLoadIdentity();
		glScaled(scale.x, scale.y, 1);
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

	Rectf getRect() {
		return rect;
	}
};