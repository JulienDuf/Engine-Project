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

	bool contient(T x, T y){
		bool estDansX = x >= this->x && x <= (this->x + this->w);
		bool estDansY = y >= this->y && y <= (this->y + this->h);
		return estDansX && estDansY;
	}

	bool contient(Vecteur2<T> point){
		return contient(point.x, point.y);
	}

	bool intersecte(Rect<T> rect){
		if (contient(rect.x, rect.y) || contient(rect.x, rect.y + rect.h) || contient(rect.x + rect.w, rect.y) || contient(rect.x + rect.w, rect.y + rect.h))
			return true;
		return false;
	}
};
typedef Rect<int> Recti;
typedef Rect<float> Rectf;
typedef Rect<double> Rectd;