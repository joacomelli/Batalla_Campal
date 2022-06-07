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
Vector<unsigned int> * BatallaCampal::pedirCoordenadas(){ //va en privado creo
	unsigned int aux;
	Vector<unsigned int> * coordenadas = new Vector<unsigned int> (3, NULL);
	while(!this->tablero->existeElCasillero(coordenadas->obtener(1),coordenadas->obtener(2),coordenadas->obtener(3))){
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

EstadoDeCasilla BatallaCampal::obtenerEstadoDeCasilla(){
	
	return this->tablero->getCasillero(vectorAux->get(x),vectorAux->get(y),vectorAux->get(z))->getEstado();
}

TipoDeCasilla BatallaCampal::obtenerTipoDeCasilla(){

	return this->tablero->getCasillero(vectorAux->get(x),vectorAux->get(y),vectorAux->get(z))->getTipo();
}

 //MODIFICAR: Ver si no permite ir al agua o si muere el soldado y si  lo verifica esta funcion o otra
bool BatallaCampal::movimientoCercano(Vector<unsigned int> * origen, Vector<unsigned int> * destino){
	int distX = (origen->get(1) - destino->get(1))
	int distY = (origen->get(2) - destino->get(2));
	if((distX*distX) > 1 || (distY*distY) > 1){
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

Vector<unsigned int> * BatallaCampal::pedirOrigenDelMovimiento(Jugador *jugador){
	Vector<unsigned int> * vectorOrigen;
	bool origenValido = FALSE;
	while(!origenValido){
		std::cout << jugador->getNombre() << ", ingresa la coordenada del soldado que desea mover." << std::endl;
		vectorOrigen = pedirCoordenadas();
		if(!tieneUnsoldado(jugador,vectorOrigen->get(1),vectorOrigen->get(2),vectorOrigen->get(3))){
			std::cout << "No tienes ningun soldado en esa posicion. Intente de nuevo." << std::endl;
			delete vectorOrigen;
		}else{
			origenValido = TRUE;
	}
	return vectorOrigen;
}

Vector<unsigned int> * BatallaCampal::pedirDestinoDelMovimiento(Jugador *jugador){
	Vector<unsigned int> * vectorDestino;
	bool destinoValido = FALSE;
	while(!destinoValido){
		std::cout << jugador->getNombre() << ", ingresa la coordenada a la cual desea mover su soldado." << std::endl;
		vectorDestino = pedirCoordenadas();
		if(tieneUnsoldado(jugador,vectorDestino->get(1),vectorDestino->get(2),vectorDestino->get(3))){
			std::cout << "Ya tienes un soldado en esa posicion. Intente de nuevo." << std::endl;
			delete vectorDestino;
		}else if(obtenerTipoDeCasilla != Tierra){
			std::cout << "Los soldados solo pueden moverse por tierra. Intente de nuevo." << std::endl;
			delete vectorDestino;
		}else if(obtenerEstadoDeCasilla == Inactiva){
			std::cout << "El casillero al que deseas moverte esta destruido. Intente de nuevo." << std::endl;
			delete vectorDestino;
		}else{
			destinoValido = TRUE;
		}	
	}
	return vectorDestino;
}



//REVISAR si lo hacemos asi y que genere un vector dinamico con dos vectores dinamicos de unsigned int (uno origen y otro destino)
// o si le pasamos 6 unsigned int* por parametro y los modifica
Vector<Vector<unsigned int> *> * BatallaCampal::pedirMovimiento(Jugador *jugador){ //va en privado creo
	
	Vector<Vector<unsigned int> *> * coordenadasDelMovimiento = new Vector<Vector<unsigned int> *>(2,NULL);
	Vector<unsigned int> * origen;
	Vector<unsigned int> * destino;
	bool valido = FALSE;
	while(!valido){
		origen = pedirOrigenDelMovimiento(jugador);
		destino = pedirDestinoDelMovimiento(jugador);
		if(movimientoCercano(origen,destino)){
			coordenadasDelMovimiento->agregar(1,origen);
			coordenadasDelMovimiento->agregar(2,destino);
			valido =  TRUE;
		}else{
			delete origen;
			delete destino;
	}
	return coordenadasDelMovimiento;
}
	
void BatallaCampal::destruirCoordenadasDelMovimiento(Vector<Vector<unsigned int> *> * coordenadas){
		
	delete coordenadas->obtener(1);
	delete coordenadas->obtener(2);
	delete coordenadas;
}
		

void BatallaCampal::mover(Vector<Vector<unsigned int> *> * coordenadasOrigenYDestino){
	
	unsigned int xOrigen = coordenadasOrigenYDestino->get(1)->get(1);
	unsigned int yOrigen = coordenadasOrigenYDestino->get(1)->get(2);
	unsigned int zOrigen = coordenadasOrigenYDestino->get(1)->get(3);
	unsigned int xDestino = coordenadasOrigenYDestino->get(2)->get(1);
	unsigned int yDestino = coordenadasOrigenYDestino->get(2)->get(2);
	unsigned int zDestino = coordenadasOrigenYDestino->get(2)->get(3);
	
	Ficha * ficha = this->tablero->getCasillero(xOrigen, yOrigen, zOrigen)->getFicha();
	this->tablero->getCasillero(xOrigen, yOrigen, zOrigen)->vaciar();

	if(this->tablero->getCasillero(xDestino, yDestino, zDestino)->estaOcupado()){
		this->tablero->getCasillero(xDestino, yDestino, zDestino)->getFicha()->eliminar();
		this->tablero->getCasillero(xDestino, yDestino, zDestino)->vaciar(); //seria destruir
		ficha->eliminar();

	}else{
		this->tablero->getCasillero(xDestino, yDestino, zDestino)->setFicha(ficha);
	}

	destruirCoordenadasDelMovimiento(coordenadasOrigenYDestino);

}







