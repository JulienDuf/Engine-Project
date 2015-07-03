#pragma once
#include "Vecteur2.h"

class RenderObject {

protected:

	Vecteur2f position;

public:

	virtual void show(int w, int h) = 0;


	Vecteur2f getPosition() {
		return position;
	}

	void setPosition(Vecteur2f pos) {

		position = pos;
	}
};