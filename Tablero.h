#ifndef TABLERO_H_
#define TABLERO_H_
#include "Vector.h"
#include "Casilla.h"



class Tablero {
private:
	Vector<Vector<Vector<Casilla *> *> *> * casilleros;
	unsigned int xMaximo;
	unsigned int yMaximo;
	unsigned int zMaximo;


public:
	//PRE: Las dimenciones deben ser mayores o iguales a 1.
	//POST: Crea un tablero con las dimensiones dadas, con todos los casilleros vacios.
	Tablero(unsigned int xMaximo, unsigned int yMaximo, unsigned int zMaximo);

	//PRE:
	//POST: Elimina el tablero.
	virtual ~Tablero();

	//PRE: Las dimensiones deben ser mayores o iguales a 1 y menores o iguales al maximo.
	//POST: Devuelve el casillero indicado.
	Casilla * getCasillero(unsigned int x, unsigned int y, unsigned int z);



private:
	//PRE: -
	//POST: Si los valores no son correctos tira una excepcion.
	void validarRango(unsigned int x, unsigned int y, unsigned int z);

};

#endif
