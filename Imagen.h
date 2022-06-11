#ifndef IMAGEN_H_
#define IMAGEN_H_

#include "EasyBMP.h"
#include "Vector.h"
#include "Casilla.h"
#include "Lista.h"
#include "Ficha.h"
#include "Jugador.h"
#include "Tablero.h"
#include "BatallaCampal.h"

class Imagen {
  private:
    BMP background; 
    BMP inactiva;
    BMP avion; 
    BMP barco;
    BMP soldado;
    BMP estado;
    void medidaDeEstado();
    void agregarFondoDeEstado(); 
    void agregarObjetosAEstado();
    void agregarAvionAEstado(int coordenadaX, int coordenadaY, int coordenadaZ);
    void agregarBarcoAEstado(int coordenadaX, int coordenadaY);
    void agregarSoldadoAEstdo(int coordenadaX, int coordenadaY);
    void agregarInactivaAEstdo(int coordenadaX, int coordenadaY, int coordenadaZ, std::string plano);
    void recorrerTablero(Tablero * tablero, Jugador * jugador);
    void recorrerPlanoXY(<Lista<Lista<Casilla *> *> *casillas, Jugador * jugador);
    void recorrerCasilla(<Lista<Casilla *> casillas, Jugador * jugadorActual);
    void chequearFicha(Casilla * casilla);


public:
  Imagen();
  void definirMapa(std::string background); 
  void obtenerEstadoTablero(Tablero * tablero,Jugador * jugador);
};

#endif
