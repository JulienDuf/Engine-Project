#pragma once
template<class T>

class Vector2{
public:
	T x, y;

	Vector2(T x = 0, T y = 0) {
		this->x = x; this->y = y; 
	}

	Vector2<T> operator+(Vector2<T> vec) {
		return Vector2(this->x + vec.x, this->y + vec.y);
	}
		
	void operator+=(Vector2<T> other) {
		x += other.x; y += other.y;
	}

	Vector2<T> operator-(Vector2<T> vec) {
		return Vector2(this->x - vec.x, this->y - vec.y);
	}
		
	void operator-=(Vector2<T> other) {
		x -= other.x; y -= other.y;
	}

	Vector2<T> operator*(float scalar) {
		return Vector2(this->x * scalar, this->y * scalar);
	}
		
	void operator*=(Vector2<T> other) {
		x *= other.x; y *= other.y;
	}
		
	bool operator==(Vector2<T> other) {
		return x == other.x && y == other.y;
	}
		
	bool operator!=(Vector2<T> other) {
		return !operator==(other);
	}

	float norm() {
		return sqrt(x * x + y * y); 
	}

	void normalize() {
		float module = norm();
		this->x /= module; this->y /= module; 
	}
	
	T dotProduct(Vector2<T> other) {
		return ((this->x * other.x) + (this->y * other.y));
	}

	double angleBetweenVectors(Vector2<T> other) {

		return acos(this->produitScalaire(other) / (this->norm() * other.norm()));

	}	
};
typedef Vector2<int> Vector2i;
typedef Vector2<unsigned int> Vector2ui;
typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;