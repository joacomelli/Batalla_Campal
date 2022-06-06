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
		std::cout << "Ingrese coordenada X" << std::endl;
		std::cin >> aux;
		coordenadas->agregar(1,aux);
		
		std::cout "Ingrese coordenada Y" << std::endl;
		std::cin >> aux;
		coordenadas->agregar(2,aux);

		std::cout "Ingrese coordenada z" << std::endl;
		std::cin >> aux;
		coordenadas->agregar(3,aux);
	}
}


Ficha * BatallaCampal::obtenerFicha( unsigned int x, unsigned int y, unsigned int z){

	return this->tablero->getCasillero(vectorAux->get(x),vectorAux->get(y),vectorAux->get(z))->getFicha();
}

 //MODIFICAR: Ver si no permite ir al agua o si muere el soldado y si  lo verifica esta funcion o otra
bool BatallaCampal::movimientoCercanoValido(unsigned int xOrigen, unsigned int yOrigen, unsigned int zOrigen,
		   unsigned int xDestino,unsigned int yDestino,unsigned int zDestino){
	if(zDestino > 1){
		std::cout << "Los soldados solo pueden moverse por tierra. Elige otra coordenada" << std::endl;
		return false;
	}
	int distX = (xOrigen-xDestino)*(xOrigen-xDestino);
	int distY = (yOrigen-yDestino)*(yOrigen-yDestino);
	if(distX > 1 || distY > 1){
		std::cout << "Solo puedes moverte un casillero. Elige otra coordenada" << std::endl;
		return false;
	}
	return true;
}

bool BatallaCampal::tieneUnSoldado(Jugador * jugador, unsigned int x, unsigned int y, unsigned int z){
	return ((obtenerFicha(x, y, z) != NULL)
		&& (obtenerFicha(x, y, z)->getJugador() == jugador)
		&& (obtenerFicha(x, y, z)->getTipo() == Soldado));
}

//REVISAR si lo hacemos asi y que genere un vector dinamico con dos vectores dinamicos de unsigned int (uno origen y otro destino)
// o si le pasamos 6 unsigned int* por parametro y los modifica
Vector<Vector<unsigned int> *> * BatallaCampal::pedirMovimiento(Jugador * jugador){ //va en privado creo
	Vector<unsigned int> * vectorAux;
	bool valido = FALSE;
	while(!valido){
		std::cout << jugador->getNombre() << " ingresa la coordenada del soldado que desea mover." << std::endl;
		vectorAux = pedirCoordenadas();
		if(!tieneUnsoldado(jugador,vectorAux->get(1),vectorAux->get(2),vectorAux->get(3))){
			std::cout << "No tienes ningun soldado en esa posicion" << std::endl;
		}else{
			//otro while que pide destino MODULARIZAR
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







