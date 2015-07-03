#pragma once

class EventObject {

public:

	virtual bool reactToEvent(SDL_Event*) = 0;
};