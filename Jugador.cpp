#include "Jugador.h"

Jugador::Jugador(unsigned int numero, std::string nombre) {
	this->numero = numero;
	this->nombre = nombre;
}

Jugador::~Jugador() {

}

const std::string& Jugador::getNombre() const {
	return nombre;
}

int Jugador::getNumero() const {
	return numero;
}
