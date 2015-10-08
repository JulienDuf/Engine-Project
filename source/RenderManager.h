#pragma once
#include <list>
#include "Singleton.h"
#include "RenderObject.h"
#include "RenderObject2D.h"
#include "RenderedModel.h"
#include "Camera.h"

class RenderManager : public Singleton<RenderManager> {

private:

	std::list<RenderObject*> objects;
	Camera* camera;
	float projection[16];

public:

	void init(int w, int h) {
		
		double hautY, droitX, ratio, angle, planProche, planLoin;

		hautY = 70 * (M_PI / 180);
		ratio = (double)w / (double)h;
		droitX = hautY * (ratio);
		planProche = 1;
		planLoin = 100;

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-droitX, droitX, -hautY, hautY, planProche, planLoin);
		glGetFloatv(GL_PROJECTION_MATRIX, projection);
		glMatrixMode(GL_MODELVIEW);
	}

	void createCamera(Vector3d position, Vector3d target, Vector3d top) {

		camera = new Camera(position, target, top);
	}

	void addObject(RenderObject* object) {

		if (std::find(objects.begin(), objects.end(), object) == objects.end()) {
			RenderObject2D* tmp = dynamic_cast<RenderObject2D*>(object);
			if (tmp != nullptr)
				objects.push_back(object);
			else {
				objects.push_front(object);
				RenderedModel* model = dynamic_cast<RenderedModel*>(object);
				if (model != nullptr) {
					model->getShader()->use();
					model->getShader()->setUniformMatrix4x4("projection", 1, false, projection);
					model->getShader()->stopUse();

					if (camera == nullptr)
						createCamera(Vector3d(0,0,0), Vector3d(), Vector3d());
				}
			}
		}
	}

	void removeObject(RenderObject* object) {

		auto it = std::find(objects.begin(), objects.end(), object);

		if (it != objects.end())
			objects.erase(it);
	}

	void render(int w, int h) {

		for (auto it : objects) {
			if (camera != nullptr)
				it->show(w, h, camera->getMatrix());
			else
				it->show(w, h, nullptr);
		}
	}
};