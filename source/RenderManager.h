#pragma once
#include <list>
#include "Singleton.h"
#include "RenderObject.h"

class RenderManager : public Singleton<RenderManager> {

private:

	std::list<RenderObject*> objects;

public:

	void addObject(RenderObject* object) {

		if (std::find(objects.begin(), objects.end(), object) == objects.end())
			objects.push_back(object);

	}

	void removeObject(RenderObject* object) {

		auto it = std::find(objects.begin(), objects.end(), object);

		if (it != objects.end())
			objects.erase(it);
	}

	void render(int w, int h) {

		for (auto it : objects)
			it->show(w, h);
	}
};