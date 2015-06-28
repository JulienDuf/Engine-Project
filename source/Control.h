#pragma once
#include <map>
#include "EventObject.h"

class Control : public EventObject {

private:

	std::map<Uint32, void(*)(Control*)> reactions;

public:

	bool addReaction(Uint32 type, void reaction(Control*)) {
		if (reactions.find(type) == reactions.end()) {
			reactions[type] = reaction;
			return true;
		}
		return false;
	}

	bool removeReaction(Uint32 type) {
		if (reactions.find(type) != reactions.end()) {
			reactions.erase(type);
			return true;
		}
		return false;
	}

	bool checkReaction(Uint32 type) {
		if (reactions.find(type) != reactions.end()) {
			reactions[type](this);
		}
		return false;
	}

	virtual void reactToEvent(SDL_Event*) = 0;

	virtual void show() = 0;
};