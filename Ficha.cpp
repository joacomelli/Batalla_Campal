#include "Ficha.h"

Ficha::Ficha(TipoDeFicha tipo, Jugador * jugador, EstadoDeFicha estado){
	if(jugador == NULL){
		throw "El jugador no puede estar vacio";
	}
	this->tipo = tipo;
	this->jugador = jugador;
	this->estado = estado;
}

Ficha::~Ficha() {

}

EstadoDeFicha Ficha::getEstado() const {
	return estado;
}

void Ficha::setEstado(EstadoDeFicha estado) {
	this->estado = estado;
}

void Ficha::eliminar(){
	if(this->estado == Eliminada){
		throw "la ficha ya esta eliminada";
	}
	this->estado = Eliminada;
}

Jugador* Ficha::getJugador(){
	return jugador;
}

void Ficha::setJugador(Jugador *jugador) {
	this->jugador = jugador;
}

TipoDeFicha Ficha::getTipo(){
	return this->tipo;
}



