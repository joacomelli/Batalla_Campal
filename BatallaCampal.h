#ifndef BATALLACAMPAL_H_
#define BATALLACAMPAL_H_

#include<iostream>
#include <cstdlib>  /* Aqui estan contenidas  las funciones rand y srand */
#include <ctime> /* de aqui  haremos uso de la función time para obtener un indicador 
del tiempo actual del sistema, pese a que este cambia de segundo a segundo la semilla también cambiara */
#include "Tablero.h"
#include "Jugador.h"
#include "Lista.h"
#include "Vector.h"

const unsigned int MAXIMO_TABLERO_X = 15;
const unsigned int MAXIMO_TABLERO_Y = 15;
const unsigned int MAXIMO_TABLERO_Z = 5;

const unsigned int MINIMO_DE_JUGADORES = 2;
const unsigned int MAXIMO_DE_JUGADORES = 4;

typedef enum TiposDeCartas{
	Avion,
	Barco,
	Misil,
	OtroTurno,
	ReconstruirTerreno,
	RondaSinCartas,
	EnBlanco
}
	

class BatallaCampal {
private:
	Tablero * tablero;
	Lista <Jugadores *> * jugadores;


public:

	//PRE:-
	//POST:
	BatallaCampal();

	//PRE:
	//POST:
	virtual ~BatallaCampal();

	//PRE:-
	//POST: Inicia el tablero en el escenario 1 pre configurado.
	void iniciarEscenarioUno(unsigned int xMaximo, unsigned int yMaximo, unsigned int zMaximo);

	//PRE:-
	//POST: Inicia el tablero en el escenario 2 pre configurado.
	void iniciarEscenarioDos(unsigned int xMaximo, unsigned int yMaximo, unsigned int zMaximo);

	//PRE:
	//POST:
	void mover(unsigned int xOrigen, unsigned int yOrigen, unsigned int zOrigen,
			   unsigned int xDestino,unsigned int yDestino,unsigned int zDestino);

};

#endif
