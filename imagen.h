#ifndef IMAGEN_H_
#define IMAGEN_H_

#include "EasyBMP.h"

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

public:
  Imagen();
  void definirMapa(std::string background); 
  void obtenerEstado(Jugador * jugador);
  //||||||||||||||||||||||||||||||||||||||||||||||||||||
  void recorrerTablero(Tablero casillas);
  void recorrerPlanoXY(<Lista<Lista<Casilla *> *> casillas);
  void recorrerCasilla(<Lista<Casilla *> casillas, Jugador jugadorActual);
};

#endif
