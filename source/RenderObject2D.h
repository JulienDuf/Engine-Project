#pragma once
#include "RenderObject.h"
#include "Vector2.h"

class RenderObject2D : public RenderObject {
	
protected:

	Vector2f position;
	Vector2f scale;

public:

	RenderObject2D() {

		scale = Vector2f(1, 1);
	}

	virtual void show(int w, int h, float* camera, Vector3f pos) = 0;

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
