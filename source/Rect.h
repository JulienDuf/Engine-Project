#pragma once 
#include "Vecteur2.h"

template<class T>
class Rect{
public:

	T x, y, w, h;

	Rect(T x = 0, T y = 0, T w = 0, T h = 0){
		this->h = h;
		this->w = w;
		this->y = y;
		this->x = x;
	}

	bool contain(T x, T y){
		bool estDansX = x >= this->x && x <= (this->x + this->w);
		bool estDansY = y >= this->y && y <= (this->y + this->h);
		return estDansX && estDansY;
	}

	bool contain(Vecteur2<T> point){
		return contain(point.x, point.y);
	}

	bool intersecte(Rect<T> rect){
		if (contain(rect.x, rect.y) || contain(rect.x, rect.y + rect.h) || contain(rect.x + rect.w, rect.y) || contain(rect.x + rect.w, rect.y + rect.h))
			return true;
		return false;
	}

	Rect<T> contain(Rect<T> rect) {

	}
};
typedef Rect<int> Recti;
typedef Rect<float> Rectf;
typedef Rect<double> Rectd;