#pragma once
#include <list>
#include "Singleton.h"
#include "RenderObject.h"
#include "Event.h"

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

	void render() {

		for (auto it : objects)
			it->show();
	}
};