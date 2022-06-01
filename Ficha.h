#ifndef FICHA_H_
#define FICHA_H_
#include "Jugador.h"


enum TipoDeFicha{
	Soldado,
	Avion,
	Barco
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
	EstadoDeFicha getEstado() const ;

	//PRE: -
	//POST: Cambia el estado de la casilla.
	void setEstado(EstadoDeFicha estado);

	//PRE: -
	//POST: ELimina la casilla.
	void eliminar();

	//PRE:-
	//POST: Devuelve el jugador
	const Jugador* getJugador() const;

	//PRE:-
	//POST: Cambia al jugador
	void setJugador(Jugador *jugador);

};

#endif
