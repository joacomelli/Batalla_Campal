#include "Tablero.h"

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
	this->casilleros = new Lista<Lista<Lista<Casilla *> *> *> ();
	for(unsigned int x = 1; x <= this->xMaximo; x++){
		this->casilleros->agregar(new Lista<Lista<Casilla *> *>());
		for(unsigned int y = 1; y <= this->yMaximo; y++){
			this->casilleros->obtener(x)->agregar(new Lista<Casilla *> ());
			for(unsigned int z = 1; z <= this->zMaximo; z++){
				this->casilleros->obtener(x)->obtener(y)->agregar(new Casilla(x,y,z,General,NULL));
			}
		}
	}
}

//
// NO TIENE QUE ESTAR ACA...       MUESTRA LA PANTALLA, ------ REVISAR -----
// REVISAR SI ES "GET ESTADO" O ES OTRO GET EL QUE HAY QUE MOSTRAR
/*void Tablero::imprimirTablero(){
	Casilla * casillero;
	this->casilleros->iniciarCursor();
	for(int x = 1; x <= this->xMaximo; x++){
		this->casilleros->avanzarCursor();
		Lista<Lista<Casilla *>*>* columna = this->casilleros->obtenerCursor();
		columna->iniciarCursor();
		for(int y = 1; y <= this->yMaximo; y++){
			columna->avanzarCursor();
			Lista<Casilla *>* fila = columna->obtenerCursor();
			fila->iniciarCursor();
			for(int z = 1; z <= this->zMaximo; z++){
				fila->avanzarCursor();
				if(fila->obtenerCursor()->getFicha() == NULL){
					std::cout <<' ';
				}else{
					std::cout << fila->obtenerCursor()->getFicha()->getEstado();
				}
				std::cout <<"|";
			}
			std::cout << std::endl;
	    }
		std::cout << std::endl << std::endl;
	}
}*/

Tablero::~Tablero() {
	for(unsigned int x = 1; x <= this->xMaximo; x++){
		for(unsigned int y = 1; y <= this->yMaximo; y++){
			for(unsigned int z = 1; z <= this->zMaximo; z++){
				delete this->casilleros->obtener(x)->obtener(y)->obtener(z);
			}
			delete this->casilleros->obtener(x)->obtener(y);
		}
		delete this->casilleros->obtener(x);
	}
	delete this->casilleros;
}

Lista<Lista<Lista<Casilla *> *> *> * Tablero::getCasilleros(){
    return this->casilleros;
}

int Tablero::getxMaximo(){
	return this->xMaximo;
}
int Tablero::getyMaximo(){
	return this->yMaximo;
}

int Tablero::getzMaximo(){
	return this->zMaximo;
}

bool Tablero::existeElCasillero(unsigned int x, unsigned int y, unsigned int z){
	try{
		validarRango(x,y,z);
		return true;
	}catch(...){}
		return false;
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

