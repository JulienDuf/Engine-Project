#pragma once
#include "Engine.h"

class Box {

private:

	Label* box;
	bool bomb;
	bool open;
	bool flag;
	static int iii;

public:

	Box() {
		box = nullptr;
	}

	Box(Label* box) {

		this->box = box;
		this->bomb = false;
		this->open = false;
		this->flag = false;
	}

	void initialyseBomb(bool bomb) {

		this->bomb = bomb;
	}

	void initialyseBox(bool open) {

		this->open = open;
		++iii;
		std::cout << "open : " << iii << std::endl;
	}

	void initialyseFlag(bool flag) {

		this->flag = flag;
	}

	void reset(Image* texture) {

		box->setBackground(texture);
		bomb = false;
		open = false;
	}

	bool isBomb() {
		return bomb;
	}

	bool isOpen() {
		return open;
	}

	bool isFlag() {
		return flag;
	}

	Label* getBox() {
		return box;
	}
}; 

int Box::iii = 0;