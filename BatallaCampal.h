#ifndef BATALLACAMPAL_H_
#define BATALLACAMPAL_H_

#include <iostream>
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

enum TiposDeCartas{
	Avion,
	Barco,
	Misil,
	OtroTurno,
	ReconstruirTerreno,
	RondaSinCartas,
	EnBlanco
};
	

class BatallaCampal {
private:
	Tablero * tablero;
	Lista <Jugador *> * jugadores;


public:

	//PRE:-
	//POST: Inicializa el tablero en NULL y los jugadores en NULL
	BatallaCampal();

	//PRE:
	//POST:
	virtual ~BatallaCampal();

	//PRE:-
	//POST: Inicia el tablero en el escenario 1 pre configurado con sus maximos.
	void iniciarEscenarioUno(unsigned int xMaximo, unsigned int yMaximo, unsigned int zMaximo);

	//PRE:-
	//POST: Inicia el tablero en el escenario 2 pre configurado con sus maximos.
	void iniciarEscenarioDos(unsigned int xMaximo, unsigned int yMaximo, unsigned int zMaximo);

	//PRE:-
	//POST: Pide por consola una coordenada (x,y,z) y la retorna como vector dinamico.
	Vector<unsigned int> * pedirCoordenadas();
	 
	// PRE: Debe existir una ficha.
	// POS: Devuelve la ficha que se ubica en la posicion que se pasa por parametro.
	Ficha * obtenerFicha( unsigned int x, unsigned int y, unsigned int z);
	
	//PRE: Debe existir la casilla 
	//POST: Devuelve el estado en el que se encuentra la casilla que se pasa por parametro.
	EstadoDeCasilla obtenerEstadoDeCasilla(unsigned int x, unsigned int y, unsigned int z);
	
	//PRE: Debe existir la casilla 
	//POST: Devuelve el tipo de casilla que se pasa por parametro.
	TipoDeCasilla obtenerTipoDeCasilla(unsigned int x, unsigned int y, unsigned int z);
	
	//PRE: Debe existir un jugador y las coordenadas validas. 
	//POST: Devolvera true si hay un soldado en las posiciones pasadas por parametro, false si no hay un soldado. 
	bool tieneUnSoldado(Jugador * jugador, unsigned int x, unsigned int y, unsigned int z);
	
	//
	//
	Vector<unsigned int> * pedirOrigenDelMovimiento(Jugador *jugador);

	//PRE: Debe existir el jugador.
	//POST: Se le pedira al jugador que ingrese coordenadas donde desee mover su jugador, comparara la posicion si hay otro soldado,
	//      si la casilla no es tierra y si la casilla no esta inactiva, retorta el destino del soldado.
	Vector<unsigned int> * pedirDestinoDelMovimiento(Jugador *jugador);

	//PRE: Debe existir el jugador
	//POST: Pedira al jugador coordenadas para mover sus fichas. 
	Vector<Vector<unsigned int> *> * pedirMovimiento(Jugador *jugador);

	//PRE: -
	//POST: Destruira las coordenadas que se les pase por consola el jugador.
	void destruirCoordenadasDelMovimiento(Vector<Vector<unsigned int> *> * coordenadas);
	
	//
	//
	void mover(Vector<Vector<unsigned int> *> * coordenadasOrigenYDestino);

	//PRE: Recibe coordendas en
	//
	bool movimientoCercano(Vector<unsigned int> * origen, Vector<unsigned int> * destino);
	

	//
	//
	void colocarAvion(Jugador * jugador);
	
	//
	//
	void sacarCarta(Jugador * jugador);

};

#endif
