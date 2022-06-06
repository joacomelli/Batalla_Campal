#include "Jugador.h"

Jugador::Jugador(unsigned int numero, std::string nombre) {
	this->numero = numero;
	this->nombre = nombre;
	this->fichas  = NULL;
}

Jugador::~Jugador() {
	~this->fichas; //era asi?

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
	if(ficha == NULL){
		throw "La ficha debe existir";
	}
	this->fichas->add(ficha);
}	

//REVISAR esta funcion me genera duda si solo tiene q sacar la ficha de la lista o si tambien la destruye pq el casillero va  a estar apuntando a la misma ficha
// si uso la funcion remover de lista.h borra la ficha a menos q implementemos q la lista de fichas del jugador son todas copias de las fichas
void Jugador::eliminarFicha(Ficha* ficha){
	if(ficha == NULL){
		throw "La ficha debe existir";
	}
	unsigned int pos = 0;
	this->fichas->reiniciarCursor();
	while(avanzarCursor()){
		pos++;
		if(getCursor() == ficha){
			this->fichas->remover(pos);
		}	
	}
}
	
}



Lista
