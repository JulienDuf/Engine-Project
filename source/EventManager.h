#pragma once
#include <list>
#include "Singleton.h"
#include "EventObject.h"
#include "Event.h"

class EventManager : public Singleton<EventManager> {

private:

	SDL_Event* event;
	std::list<EventObject*> objects;

public:

	EventManager() {
		event = new SDL_Event();
	}

	void addObject(EventObject* object) {

		if (std::find(objects.begin(), objects.end(), object) == objects.end())
			objects.push_back(object);

	}

	void removeObject(EventObject* object) {

		auto it = std::find(objects.begin(), objects.end(), object);

		if (it != objects.end())
			objects.erase(it);
	}

	void checkEvent() {

		while (SDL_PollEvent(event)) {

			for (auto it : objects)
				it->reactToEvent(event);

			Event::update(event);
		}
	}
};