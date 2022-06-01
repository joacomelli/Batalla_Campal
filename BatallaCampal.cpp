#include "BatallaCampal.h"

BatallaCampal::BatallaCampal() {


}

BatallaCampal::~BatallaCampal() {

}
void BatallaCampal::iniciarEscenarioUno(unsigned int xMaximo, unsigned int yMaximo, unsigned int zMaximo){
	this->tablero = new Tablero(xMaximo,yMaximo,zMaximo);
	for(int x = 1; x <= xMaximo; x++){
		for(int y = 1; y <= yMaximo; y++){
			for(int z = 1; z <= zMaximo; z++){
				if(x == 1){
					this->tablero->getCasillero(x,y,z)->setTipo(Tierra);
				}
				else{
					this->tablero->getCasillero(x,y,z)->setTipo(Aire);
				}
			}
		}
	}
}

void BatallaCampal::iniciarEscenarioDos(unsigned int xMaximo, unsigned int yMaximo, unsigned int zMaximo){
	this->tablero = new Tablero(xMaximo,yMaximo,zMaximo);
	for(int x = 1; x <= xMaximo; x++){
		for(int y = 1; y <= yMaximo; y++){
			for(int z = 1; z <= zMaximo; z++){
				if(x == 1){
					if(y < z){

				        this->tablero->getCasillero(x,y,z)->setTipo(Tierra);
					}
					else{
					    this->tablero->getCasillero(x,y,z)->setTipo(Agua);
					}
				}
				else{
					this->tablero->getCasillero(x,y,z)->setTipo(Aire);
				}
			}
		}
	}
}

void BatallaCampal::mover(unsigned int xOrigen, unsigned int yOrigen, unsigned int zOrigen,
		   unsigned int xDestino,unsigned int yDestino,unsigned int zDestino){

	Ficha * ficha = this->tablero->getCasillero(xOrigen, yOrigen, zOrigen)->getFicha();
	this->tablero->getCasillero(xOrigen, yOrigen, zOrigen)->vaciar();

	if(this->tablero->getCasillero(xDestino, yDestino, zDestino)->estaOcupado()){
		this->tablero->getCasillero(xDestino, yDestino, zDestino)->getFicha()->eliminar();
		this->tablero->getCasillero(xDestino, yDestino, zDestino)->vaciar();
		ficha->eliminar();

	}else{
		this->tablero->getCasillero(xDestino, yDestino, zDestino)->setFicha(ficha);
	}


}







