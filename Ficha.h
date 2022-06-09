#ifndef FICHA_H_
#define FICHA_H_
#include "Jugador.h"


enum TipoDeFicha{
	FSoldado,
	FAvion,
	FBarco
};
enum EstadoDeFicha{
	Eliminada,
	Activa
};


class Ficha {
private:
	TipoDeFicha tipo;
	Jugador * jugador;
	EstadoDeFicha estado;

public:

	//PRE: Jugador no puede ser vacio.
	//POST: Crea la ficha con el tipo y el jugador.
	Ficha(TipoDeFicha tipo, Jugador * jugador,EstadoDeFicha estado);

	//PRE: -
	//POST: Elimina la ficha.
	virtual ~Ficha();

	//PRE: -
	//POST: Devuelve en el estado que esta la ficha
	EstadoDeFicha getEstado() const;

	//PRE: -
	//POST: Cambia el estado de la casilla.
	void setEstado(EstadoDeFicha estado);

	//PRE: -
	//POST: Elimina la ficha.
	void eliminar();

	//PRE: Debe existir el jugador 
	//POST: Retorna el jugador actual.
	Jugador* getJugador();

	//PRE:-
	//POST: Cambia al jugador
	void setJugador(Jugador *jugador);

	//PRE:-
	//POST: Devuelve el tipo
	TipoDeFicha getTipo();

};

#endif
