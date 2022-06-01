#include "Tablero.h"
#include "Casilla.h"

Tablero::Tablero(unsigned int xMaximo, unsigned int yMaximo, unsigned int zMaximo){
	if(xMaximo < 1){
		throw " X no puede ser menor a 1";
	}
	if(yMaximo < 1){
		throw " Y no puede ser menor a 1";
	}
	if(zMaximo < 1){
		throw " Z no puede ser menor a 1";
	}
	this->xMaximo = xMaximo;
	this->yMaximo = yMaximo;
	this->zMaximo = zMaximo;
	this->casilleros = new Vector<Vector<Vector<Casilla *> *> *> (xMaximo, NULL);
	for(int x = 1; x <= this->xMaximo; x++){
		this->casilleros->agregar(x, new Vector<Vector<Casilla *> *> (yMaximo, NULL));
		for(int y = 1; y <= this->yMaximo; y++){
			this->casilleros->obtener(x)->agregar(y, new Vector<Casilla *> (zMaximo, NULL));
			for(int z = 1; z <= this->zMaximo; z++){
				this->casilleros->obtener(x)->obtener(y)->agregar(z, new Casilla (x,y,z, General));
			}
		}
	}
}

Tablero::~Tablero() {
	for(int x = 1; x <= this->xMaximo; x++){
		for(int y = 1; y <= this->yMaximo; y++){
			for(int z = 1; z <= this->zMaximo; z++){
				delete this->casilleros->obtener(x)->obtener(y)->obtener(z);
			}
			delete this->casilleros->obtener(x)->obtener(y);
		}
		delete this->casilleros->obtener(x);
	}
	delete this->casilleros;
}


Casilla * Tablero::getCasillero(unsigned int x, unsigned int y, unsigned int z){
	validarRango(x,y,z);
	return this->casilleros->obtener(x)->obtener(y)->obtener(z);
}


void Tablero::validarRango(unsigned int x, unsigned int y, unsigned int z){
	if(x < 1 && x > this->xMaximo){
		throw " X no puede ser menor a 1 o mayor al maximo que es " + this->xMaximo;
	}
	if(y < 1 && y > this->yMaximo){
		throw " Y no puede ser menor a 1 o mayor al maximo que es " + this->yMaximo;
	}
	if(z < 1 && z > this->zMaximo){
		throw " Z no puede ser menor a 1 o mayor al maximo que es " + this->zMaximo;
	}
}

