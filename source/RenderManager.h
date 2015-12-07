#pragma once
#include <list>
#include "Singleton.h"
#include "RenderObject.h"
#include "RenderedModel.h"
#include "Camera.h"
#include "Scene.h"

class RenderManager : public Singleton<RenderManager> {

private:

	std::list<RenderObject*> objects;

	std::list<Scene*> scenes;

	Mat4 projection;

public:

	Camera* camera;

	void init(int w, int h) {
		
		double hautY, droitX, ratio, angle, planProche, planLoin;

		hautY = 30 * (M_PI / 180);
		ratio = (double)w / (double)h;
		droitX = hautY * (ratio);
		planProche = 1;
		planLoin = 100;

		projection = Math::perspective(-droitX, droitX, -hautY, hautY, planProche, planLoin);

	}

	void createCamera(Vector3f position, Vector3f top) {

		camera = new Camera(position, top);
	}

	void addObject(RenderObject* object) {

		if (std::find(objects.begin(), objects.end(), object) == objects.end())
			objects.push_back(object);

	}

	void addScene(Scene* scene) {

		if (std::find(scenes.begin(), scenes.end(), scene) == scenes.end()) {
			scenes.push_back(scene);

			if (camera == nullptr)
				createCamera(Vector3f(0, 22.20, 0), Vector3f(0,1,0));

		}
	}

	void removeObject(RenderObject* object) {

		auto it = std::find(objects.begin(), objects.end(), object);

		if (it != objects.end())
			objects.erase(it);
	}

	void removeScene(Scene* object) {

		auto it = std::find(scenes.begin(), scenes.end(), object);

		if (it != scenes.end())
			scenes.erase(it);
	}

	void render(int w, int h) {

		for (auto item : scenes)
			item->show(camera->getMatrix(), projection);

		for (auto it : objects)
			it->show(w, h);

	}
};
