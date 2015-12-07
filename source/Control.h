#pragma once
#include <map>
#include "EventObject.h"

class Control : public EventObject {

private:

	std::map<Uint32, void(*)(Control*)> reactions;

protected:

	Vector2f position;

public:

	virtual ~Control() {

	}

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
			return true;
		}
		return false;
	}

	Vector2f getPosition() {
		return position;
	}

	void setPosition(Vector2f& pos) {
		position = pos;
	}

	virtual bool reactToEvent(SDL_Event*) = 0;
};