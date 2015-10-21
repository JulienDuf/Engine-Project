#pragma once

#include "Vector3.h"

class RenderObject {

public:

	virtual void show(int w, int h, float* camera, Vector3f pos) = 0;

};