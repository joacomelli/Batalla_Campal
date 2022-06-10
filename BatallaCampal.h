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
#include "Imagen.h"

const unsigned int MAXIMO_TABLERO_X = 15;
const unsigned int MAXIMO_TABLERO_Y = 15;
const unsigned int MAXIMO_TABLERO_Z = 5;

const unsigned int MINIMO_DE_JUGADORES = 2;
const unsigned int MAXIMO_DE_JUGADORES = 4;

const unsigned int NUM_MAPA_MAXIMO = 2;


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
	unsigned int * cantidadDeJugadores;
	Imagen imagen;


public:

	//PRE:-
	//POST: Inicializa el tablero en NULL y los jugadores en NULL
	BatallaCampal();

	//PRE:
	//POST:
	virtual ~BatallaCampal();
	
	//PRE:-
	//POST: Pedira la cantidad de jugadores.
	void menuDeJuego(unsigned int * numeroDeEscenario);

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
	
	//PRE: Debe existir el jugador y tener minimo un soldado en el tablero. 
	//POS:Pide al jugador las coordenadas donde se ubica uno de sus soldados para seleccionar el soldado que quiere mover.
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
	
	//PRE: -
	//POST: movera el soldado elegido por el jugador a una casilla destino, verifica si la casilla esta ocupada o no.
	void mover(Vector<Vector<unsigned int> *> * coordenadasOrigenYDestino);
	
	//PRE: Recibe coordendas en donde se ubica el soldado del jugador y las coordendas de la casilla a la que se lo quiere mover.
	//POST: Compara si las coordendas destino estan a una casilla de distancia de las coordenadas origen que son las del soldado.
	bool movimientoCercano(Vector<unsigned int> * origen, Vector<unsigned int> * destino);
	
	//PRE: -
	//POST: Lanzara un misil que destruye 27 casilleros en el tablero (3x3x3).
	void lanzarMisil(Jugador * jugador);
	
	//PRE: El jugador tiene que estar en juego.
	//POST:Pedira coordenadas (x,y,z) para que el jugador dispare y si la casilla no esta Vacia, eliminara una ficha del jugador contrario,
	//      destruira la casilla si es tierra dejandola inactiva, de lo contrario la vaciara.
	void disparar(Jugador * jugador);
	
	//PRE: -
	//POST: Pedira al jugador coordenadas (x,y,z) para ubicar su Avion, solo se puede ubicar en una casilla que sea del tipo Aire, y si hay un
	//      Avion contrario se eliminan los dos Aviones.
	void colocarAvion(Jugador * jugador);
	
	//PRE: -
	//POST: Pedira al jugador coordenadas (x,y,z) para ubicar su Barco, solo se puede ubicar en una casilla que sea del tipo Agua, y si hay un
	//      Barco contrario se eliminan los dos Barcos.
	void colocarBarco(Jugador * jugador);

	//PRE:
	//POST:
	void jugarTurno(Jugador * jugador);
	
	//PRE:
	//POST:
        void jugarRonda();
	
	//PRE:-
	//POST:Volvera activa la casilla que elija el jugador actual
	void reconstruirTerreno(Jugador * jugador);
		
	//PRE: -
	//POST: El jugador sacara una carta al finalizar el turno y ..
	void sacarCarta(Jugador * jugador);
	
	//PRE: -
	//POST: Devuelve imagen del tablero segun el jugador actual. 
	void mostrarEstadoTablero(Jugador * jugador);

};

#endif
