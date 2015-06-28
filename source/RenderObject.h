#pragma once
#include "Vecteur2.h"

class RenderObject {

protected:

	Vecteur2f position;

public:

	virtual void show() = 0;


	Vecteur2f getPosition() {
		return position;
	}
};