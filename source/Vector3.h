#pragma once
template<class T>
class Vector3{
public:
	T x, y, z;

	Vector3(T x = 0, T y = 0, T z = 0) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	T norm() {
		return sqrt((x * x) + (y * y) + (z * z));
	}
	
	void normalize() {
		T module = norm();
		x /= module;
		y /= module;
		z /= module;
	}

	void invert() {
		x = -x;
		y = -y;
		z = -z;
	}
	
	bool operator==(Vector3<T> other) {
		return (x == other.x && y == other.y && z == other.z);

	}

	void operator+=(Vector3<T> other) {
		x += other.x;
		y += other.y;
		z += other.z;
	}
	
	void operator-=(Vector3<T> other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
	}
	
	void operator/=(Vector3<T> other) {
		x /= other.x;
		y /= other.y;
		z /= other.z;
	}

	void operator/=(double scalar) {
		x /= scalar;
		y /= scalar;
		z /= scalar;
	}

	void operator*=(Vector3<T> other) {
		x *= other.x;
		y *= other.y;
		z *= other.z;
	}

	void operator*=(double scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
	}

	void subtract(double scalar) {
		x -= scalar;
		y -= scalar;
		y -= scalar;
	}

	void productByVector(Vector3<T> other) {
		x *= other.x;
		y *= other.y;
		z *= other.z;
	}

	T dotProduct(Vector3<T> other) {
		return ((this->x * other.x) + (this->y * other.y) + (this->z * other.z));
	}

	Vector3<T> crossProduct(Vector3<T> other) {
		Vector3<T> vectP;
		vectP.x = (this->y * other.z) - (this->z * other.y);
		vectP.y = (this->z * other.x) - (this->x * other.z);
		vectP.z = (this->x * other.y) - (this->y * other.x);
		return vectP;
	}

	double angleBetweenVectors(Vector3<T> other) {

		return acos(this->produitScalaire(other) / (this->norme() * other.norme()));

	}

	Vector3<T> operator*(double scalar) {
		return Vector3<T>(x * scalar, y * scalar, z * scalar);
	}

	Vector3<T> operator*(Vector3<T> vec) {
		return Vector3<T>(x * vec.x, y * vec.y, z * vec.z);
	}

	Vector3<T> operator/(double scalar) {
		return Vector3<T>(x / scalar, y / scalar, z / scalar);
	}

	Vector3<T> operator+(Vector3<T> other) {
		return Vector3<T>(x + other.x, y + other.y, z + other.z);
	}

	Vector3<T> operator-(Vector3<T> other) {
		return Vector3<T>(x - other.x, y - other.y, z - other.z);
	}
};
	
typedef Vector3<int> Vector3i;
typedef Vector3<unsigned int> Vector3ui;
typedef Vector3<float> Vector3f;
typedef Vector3<double> Vector3d;
