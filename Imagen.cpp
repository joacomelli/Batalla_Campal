#include "Imagen.h"
#include <string>

using namespace std; 

Imagen::Imagen(){
    this->inactiva.ReadFromFile("inactiva.bmp");
    this->avion.ReadFromFile("avion.bmp");
    this->barco.ReadFromFile("barco.bmp");
    this->soldado.ReadFromFile("soldado.bmp");
    this->estado.SetBitDeph(24);
}

void Imagen::medidaDeEstado(){
  this->estado.SetSize( this->background.TellWidth(), this->background.TellHeight()); 
}
 
void Imagen::agregarFondoAEstado(){
  RangedPixelToPixelCopy(this->background,0,this->background.TellWidth(),
                         this->background.TellHeight(),0
                         this->estado,0,0); 
}

void EstadoTablero::agregarAvionAEstado(int coordenadaX, int coordenadaY, int coordenadaZ){
		RangedPixelToPixelCopyTransparent( this->avion, 0, this->avion.TellWidth(),
						this->avion.TellHeight(), 0,this->estado, 1030 - coordenadaZ*40,
						85 + coordenadaX*40,*this->avion(0,0) );

		RangedPixelToPixelCopyTransparent( this->avion, 0, this->avion.TellWidth(),
						this->avion.TellHeight(), 0,this->estado, 116 + coordenadaY*40,
						995 - coordenadaZ*40,*this->avion(0,0) );
}

void EstadoTablero::agregarSoldadoAEstado(int coordenadaX, int coordenadaY){
		RangedPixelToPixelCopyTransparent( this->soldado, 0, this->soldado.TellWidth(),
						this->soldado.TellHeight(), 0,this->estado, 116 + coordenadaY*40,
						85 + coordenadaX*40,*this->soldado(0,0) );
}

void EstadoTablero::agregarBarcoAEstado(int coordenadaX, int coordenadaY){
		RangedPixelToPixelCopyTransparent( this->barco, 0, this->barco.TellWidth(),
						this->barco.TellHeight(), 0,this->estado, 116+ coordenadaY*40,
						85 + coordenadaX*40,*this->barco(0,0) );
}

void EstadoTablero::agregarInactivaAEstado(int coordenadaX, int coordenadaY){
		RangedPixelToPixelCopyTransparent( this->inactiva, 0, this->inactiva.TellWidth(),
				this->inactiva.TellHeight(), 0,this->estado, 116+ coordenadaY*40,
				85 + coordenadaX*40,*this->inactiva(0,0) );
}

void Imagen::definirMapa(string background){
  if (background == 'Background1'){
    this->background.ReadfromFile( "Background1.bmp"); 
  } else if  (background == 'Background2'){
    this->background.ReadfromFile( "Background2.bmp"); 
  } else if  (background == 'Background3'){
    this->background.ReadfromFile( "Background3.bmp"); 
  }
 }
  
void Imagen::obtenerEstadoTablero( Tablero * tablero, Jugador *jugador){
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
            else if(casilla->getEstado() == Inactiva){
                //printear casilla inactiva
            }
        }
    }
 
  
