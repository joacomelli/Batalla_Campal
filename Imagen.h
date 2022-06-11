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
    void agregarObjetosAEstado();
    void agregarAvionAEstado(int coordenadaX, int coordenadaY, int coordenadaZ);
    void agregarBarcoAEstado(int coordenadaX, int coordenadaY);
    void agregarSoldadoAEstdo(int coordenadaX, int coordenadaY);
    void agregarInactivaAEstdo(int coordenadaX, int coordenadaY);

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
