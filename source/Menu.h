#pragma once
#include "Control.h"
#include <list>
#include <stdarg.h>

class Menu {

private:

	std::list<Control*> controls;

public:

	Menu(int argc, ...) {

		if (argc > 0) {
			va_list parametres;

			va_start(parametres, argc);
			for (int i = 0; i < argc; ++i) 
				controls.push_back(va_arg(parametres, Control*));
			va_end(parametres);
		}
	}

	~Menu() {

		for (int i = controls.size(); i > 0; --i)
			controls.pop_back();
	}

	void addControl(Control* control) {

		if (std::find(controls.begin(), controls.end(), control) == controls.end())
			controls.push_back(control);
	}

	void removeControl(Control* control) {

		auto it = std::find(controls.begin(), controls.end(), control);

		if (it != controls.end())
			controls.erase(it);
	}
};