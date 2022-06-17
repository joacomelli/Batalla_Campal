#ifndef IMAGEN_H_
#define IMAGEN_H_

#include "imagen/EasyBMP.h"
#include "Vector.h"
#include "Casilla.h"
#include "Lista.h"
#include "Ficha.h"
#include "Jugador.h"
#include "Tablero.h"


class Imagen {
private:
 
  BMP background; 
  BMP inactiva;
  BMP avion; 
  BMP barco;
  BMP soldado;
  BMP estado;
  
  //PRE:
  //POST:
  void medidaDeEstado();
  
  //PRE:
  //POST:
  void agregarFondoAEstado();
  
  //PRE:
  //POST:
  void agregarAvionAEstado(int coordenadaX, int coordenadaY, int coordenadaZ);
  
  //PRE:
  //POST:
  void agregarBarcoAEstado(int coordenadaX, int coordenadaY);
  
  //PRE:
  //POST:
  void agregarSoldadoAEstado(int coordenadaX, int coordenadaY);
  
  //PRE:
  //POST:
  void agregarInactivaAEstado(int coordenadaX, int coordenadaY, int coordenadaZ);
  
  //PRE:
  //POST:
  void recorrerTablero(Tablero * tablero, Jugador * jugador);
  
  //PRE:
  //POST:
  void recorrerPlanoXY(Lista<Lista<Casilla *> *> *casillas, Jugador * jugador);
  
  //PRE:
  //POST:
  void recorrerCasilla(Lista<Casilla *>* casillas, Jugador * jugadorActual);
  
  //PRE:
  //POST:
  void chequearFicha(Casilla * casilla);

public:
  
  //PRE:
  //POST:
  Imagen();
  
  //PRE:
  //POST:
  void definirMapa(std::string background); 
  
  //PRE:
  //POST:
  void obtenerEstadoTablero(Tablero * tablero,Jugador * jugador);

};

#endif
