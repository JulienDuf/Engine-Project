#pragma once
#include "Vector2.h"

class RenderObject {
	
protected:

	Vector2f position;
	Vector2f scale;

public:

	RenderObject() {

		scale = Vector2f(1, 1);
	}

	virtual void show(int w, int h) = 0;

	Vector2f getPosition() {
		return position;
	}

	void setPosition(Vector2f pos) {

		position = pos;
	}

	Vector2f getScale() {
		return scale;
	}

	void setScale(Vector2f scale) {

		this->scale = scale;
	}
};
