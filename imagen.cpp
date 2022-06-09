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

void Imagen::obtenerEstado(Jugador *jugador){
  this->medidaDeEstado();
  this->agregarFondoAEstado();
  this->estado.WriteToFile("estadoTableroDe"+ jugador->getNombre + ".bmp");
}

 
  
