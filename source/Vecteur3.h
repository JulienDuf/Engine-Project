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

	T norme() {
		return sqrt((x * x) + (y * y) + (z * z));
	}
	
	void normaliser() {
		T module = norme();
		x /= module;
		y /= module;
		z /= module;
	}

	void inverser() {
		x = -x;
		y = -y;
		z = -z;
	}
	
	bool operator==(Vector3<T> autre) {
		if (x == autre.x && y == autre.y && z == autre.z)
			return true;
		return false;
	}

	void operator+=(Vector3<T> autre) {
		x += autre.x;
		y += autre.y;
		z += autre.z;
	}
	
	void operator-=(Vector3<T> autre) {
		x -= autre.x;
		y -= autre.y;
		z -= autre.z;
	}
	
	void operator/=(Vector3<T> autre) {
		x /= autre.x;
		y /= autre.y;
		z /= autre.z;
	}

	void operator/=(double scalaire) {
		x /= scalaire;
		y /= scalaire;
		z /= scalaire;
	}

	void operator*=(Vector3<T> autre) {
		x *= autre.x;
		y *= autre.y;
		z *= autre.z;
	}

	void operator*=(double scalaire) {
		x *= scalaire;
		y *= scalaire;
		z *= scalaire;
	}

	void soustraire(double scalaire) {
		x -= scalaire;
		y -= scalaire;
		y -= scalaire;
	}

	void produitParUnVecteur(Vector3<T> autre) {
		x *= autre.x;
		y *= autre.y;
		z *= autre.z;
	}

	T produitScalaire(Vector3<T> autre) {
		return ((this->x * autre.x) + (this->y * autre.y) + (this->z * autre.z));
	}

	Vector3<T> produitVectoriel(Vector3<T> autre) {
		Vector3<T> vectP;
		vectP.x = (this->y * autre.z) - (this->z * autre.y);
		vectP.y = (this->z * autre.x) - (this->x * autre.z);
		vectP.z = (this->x * autre.y) - (this->y * autre.x);
		return vectP;
	}

	double angleEntreVecteurs(Vector3<T> autre) {

		return acos(this->produitScalaire(autre) / (this->norme() * autre.norme()));

	}

	Vector3<T> operator*(double scalaire) {
		return Vector3<T>(x * scalaire, y * scalaire, z * scalaire);
	}

	Vector3<T> operator*(Vector3<T> vect) {
		return Vector3<T>(x * vect.x, y * vect.y, z * vect.z);
	}

	Vector3<T> operator/(double scalaire) {
		return Vector3<T>(x / scalaire, y / scalaire, z / scalaire);
	}

	Vector3<T> operator+(Vector3<T> autre) {
		return Vector3<T>(x + autre.x, y + autre.y, z + autre.z);
	}

	Vector3<T> operator-(Vector3<T> autre) {
		return Vector3<T>(x - autre.x, y - autre.y, z - autre.z);
	}
};
	
typedef Vector3<int> Vector3i;
typedef Vector3<unsigned int> Vector3ui;
typedef Vector3<float> Vector3f;
typedef Vector3<double> Vector3d;
