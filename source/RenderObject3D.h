#pragma once
#include "RenderObject.h"
#include "Vecteur3.h"

class RenderObject3D : public RenderObject {

protected:

	Vector3d position;
	Vector3d scale;
	Vector3d rotation;

	float transform[16];

	void calculMatrix() {

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslated(position.x, position.y, position.z);
		glRotated(rotation.x, 1, 0, 0);
		glRotated(rotation.y, 0, 1, 0);
		glRotated(rotation.z, 0, 0, 1);
		glScaled(scale.x, scale.y, scale.z);
		glGetFloatv(GL_MODELVIEW_MATRIX, transform);
	}

public:

	RenderObject3D() {

		scale = Vector3d(1,1,1);

		calculMatrix();
	}

	virtual void show(int w, int h, float* camera) = 0;

	Vector3d getPosition() {
		return position;
	}

	void setPosition(Vector3d pos) {

		position = pos;
		calculMatrix();
	}

	Vector3d getScale() {
		return scale;
	}

	void setScale(Vector3d scale) {

		this->scale = scale;
		calculMatrix();
	}

	Vector3d getRotation() {

		return rotation;
	}

	void setRotation(Vector3d rotation) {

		this->rotation = rotation;
		calculMatrix();
	}
};
