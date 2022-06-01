#ifndef BATALLACAMPAL_H_
#define BATALLACAMPAL_H_
#include "Tablero.h"

class BatallaCampal {
private:
	Tablero * tablero;



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
