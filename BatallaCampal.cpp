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



//REVISAR si lo hacemos asi y que genere un vector dinamico de unsigned int o unsigned int* 
// o si le pasamos tres punteros a unsigned int por parametro y los modifica
// falta crear la funcion coordenadasEnRango en tablero.h
Vector<unsigned int> * BatallaCampal::pedirCoordenadas(){ //va en privado creo
	unsigned int aux;
	Vector<unsigned int> * coordenadas = new Vector<unsigned int> (3, NULL);
	while(!coordenadasEnRango(coordenadas->obtener(1),coordenadas->obtener(2),coordenadas->obtener(3))){
		std::cout << "Inserte coordenada X" << std::endl;
		std::cin >> aux;
		coordenadas->agregar(1,aux);
		
		std::cout "Inserte coordenada Y" << std::endl;
		std::cin >> aux;
		coordenadas->agregar(2,aux);

		std::cout "Inserte coordenada z" << std::endl;
		std::cin >> aux;
		coordenadas->agregar(3,aux);
	}
}

//Habria q agregar una funcion que directamente devuelva la ficha de una casilla para no estar poniendo
// this->tablero->getCasillero(vectorAux->get(1),vectorAux->get(2),vectorAux->get(3))->getFicha()  cada vez

//REVISAR si lo hacemos asi y que genere un vector dinamico con dos vectores dinamicos a unsigned int (uno origen y otro destino)
// o si le pasamos 6 unsigned int* por parametro y los modifica
Vector<Vector<unsigned int> *> * BatallaCampal::pedirMovimiento(Jugador * jugador){ //va en privado creo
	Vector<unsigned int> * vectorAux;
	bool soldadoNoValido = TRUE;
	while(soldadoNoValido){
		vectorAux = pedirCoordenadas();
		soldadoNoValido = ((this->tablero->getCasillero(vectorAux->get(1),vectorAux->get(2),vectorAux->get(3))->getFicha()->getJugador() != jugador)
				   || (this->tablero->getCasillero(vectorAux->get(1),vectorAux->get(2),vectorAux->get(3))->getFicha()->getTipo() != Soldado)); //meter la funcion que devuelve la ficha directo
		if(soldadoNoValido){
			std::cout << "No tienes ningun soldado en esa posicion" << std::endl;
		} //seguir
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







