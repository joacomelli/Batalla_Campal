#include "Vector.h"

Vector::Vector(int longitud, T datoInicial) {
		if (longitud < 1) {
			throw "La longitud debe ser mayor o igual a 1";
		}
		this->datos = new T[longitud];
		this->longitud = longitud;
		for(int i = 0; i < this->longitud; i++){
			this->datos[i] = datoInicial;
		}
	}

Vector::~Vector() {
		delete [] this->datos;
}

int Vector::getLongitud() {
		return this->longitud;
}

void Vector::agregar(int posicion, T dato) {
		if ((posicion < 1) ||
		   (posicion > this->longitud)) {
			throw "La " + posicion + " no esta en el rango 1 y " + this->longitud + " inclusive";
		}
		this->datos[posicion - 1] = dato;
}


T& Vector::obtener(int posicion) {
		if ((posicion < 1) ||
		   (posicion > this->longitud)) {
			throw "La " + posicion + " no esta en el rango 1 y " + this->longitud + " inclusive";
		}
		return this->datos[posicion - 1];
}
