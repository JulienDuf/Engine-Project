#pragma once

class EventObject {

public:

	virtual void reactToEvent(SDL_Event*) = 0;
};