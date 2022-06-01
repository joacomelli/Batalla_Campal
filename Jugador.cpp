#include "Jugador.h"

Jugador::Jugador(unsigned int numero, std::string nombre) {
	this->numero = numero;
	this->nombre = nombre;
	this->fichas  = NULL;
}

Jugador::~Jugador() {
	//falta lista.h tiene que destruir la lista de fichas

}

const std::string& Jugador::getNombre() const {
	return nombre;
}

int Jugador::getNumero() const {
	return numero;
}

Lista<Ficha*> * Jugador::getFichas(){
	return this->fichas;
}

void Jugador::agregarFicha(Ficha* ficha){
	//falta lista.h
	if(ficha == NULL){
		throw "La ficha debe existir";
	}
	//agregar al principio
}	

void Jugador::eliminarFicha(Ficha* ficha){
	if(ficha == NULL){
		throw "La ficha debe existir";
	}
	//eliminar dato  de lista.h
}
	
}



Lista
