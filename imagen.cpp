#include "imagen.h"
#include <string>

using namespace std; 

Imagen::Imagen(){
    this->inactiva.ReadFromFile("inactiva.bmp");
    this->avion.ReadFromFile("avion.bmp");
    this->barco.ReadFromFile("barco.bmp");
    this->soldado.ReadFromFile("soldado.bmp");
    this->estado.SetBitDeph(24);
}

void Imagen::definirMapa(string background){
  if (background == 'background1' ││ background == 'background2' ││ background == 'background3'){
    this->background.ReadfromFile( background + ".bmp"); 
 }
  
void Imagen::medidaDeEstado(){
  this->estado.SetSize( this->background.TellWidth(), this->background.TellHeight()); 
}
 
void Imagen::agregarFondoAEstado(){
  RangedPixelToPixelCopy(this->background,0,this->background.TellWidth(),
                         this->background.TellHeight(),0
                         this->estado,0,0); 
}

void Imagen::obtenerEstado( Tablero * tablero, Jugador *jugador){
  this->medidaDeEstado();
  this->agregarFondoAEstado();
  this->estado.WriteToFile("estadoTableroDe"+ jugador->getNombre + ".bmp");
}

//||||||||||||||||||||||||||||||||||||||||||
//Lista<Lista<Lista<Casilla *> *> *> casillas
    void Imagen::recorrerTablero(Tablero tablero){
        tablero->getCasilleros()->iniciarCursor();
        while(tablero->getCasilleros()->avanzarCursor()){
            <Lista<Lista<Casilla *> *> casillasPlanoXY = tablero->getCasilleros()->obtenerCursor();//PLANO XY
            //Casilla casilla = recorrerPlanoXY(casillasPlanoXY);
            recorrerPlanoXY(casillasPlanoXY);
        }
    }

    void Imagen::recorrerPlanoXY(<Lista<Lista<Casilla *> *> casillas){
        casillas->iniciarCursor();
        while(casillas->avanzarCursor()){
            <Lista<Casilla *> casillasRecta = casillas->obtenerCursor();
            //Casilla casilla = recorrerCasilla();
            recorrerCasilla();
        }
    }

    void Imagen::recorrerCasilla(<Lista<Casilla *> casillas, Jugador jugadorActual){
        casillas->iniciarCursor();
        while(casillas->avanzarCursor()){
            Casilla* casilla = casillas->obtenerCursor();
            if((casilla->getEstado() == Ocupada) && (getFicha()->getJugador()->getNombre() == jugadorActual->getNombre())){
                //printear casilla en el tablero
            }
            else if((casilla->getEstado() == Inactiva) && (getFicha()->getJugador()->getNombre() == jugadorActual->getNombre())){
                //printear casilla inactiva
            }
        }
    }
 
  
