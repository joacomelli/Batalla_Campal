#include "BatallaCampal.h"

BatallaCampal::BatallaCampal() {
	this->tablero = NULL;
	this->jugadores = NULL;

}

BatallaCampal::~BatallaCampal() {

}

void BatallaCampal::iniciarEscenarioUno(unsigned int xMaximo, unsigned int yMaximo, unsigned int zMaximo){
	this->tablero = new Tablero(xMaximo,yMaximo,zMaximo);
	for(unsigned int x = 1; x <= xMaximo; x++){
		for(unsigned int y = 1; y <= yMaximo; y++){
			for(unsigned int z = 1; z <= zMaximo; z++){
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
	for(unsigned int x = 1; x <= xMaximo; x++){
		for(unsigned int y = 1; y <= yMaximo; y++){
			for(unsigned int z = 1; z <= zMaximo; z++){
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



//REVISAR
Vector<unsigned int> * BatallaCampal::pedirCoordenadas(){ //va en privado creo
	unsigned int aux;
	Vector<unsigned int> * coordenadas = new Vector<unsigned int> (3, NULL);
	while(!this->tablero->existeElCasillero(coordenadas->obtener(1),coordenadas->obtener(2),coordenadas->obtener(3))){
		std::cout << "Ingrese coordenada X" << std::endl;
		std::cin >> aux;
		coordenadas->agregar(1,aux);
		
		std::cout << "Ingrese coordenada Y" << std::endl;
		std::cin >> aux;
		coordenadas->agregar(2,aux);

		std::cout << "Ingrese coordenada z" << std::endl;
		std::cin >> aux;
		coordenadas->agregar(3,aux);
	}
	
	return coordenadas;
}


Ficha * BatallaCampal::obtenerFicha( unsigned int x, unsigned int y, unsigned int z){

	return this->tablero->getCasillero(x,y,z)->getFicha();
}

EstadoDeCasilla BatallaCampal::obtenerEstadoDeCasilla(unsigned int x, unsigned int y, unsigned int z){
	
	return this->tablero->getCasillero(x,y,z)->getEstado();
}

TipoDeCasilla BatallaCampal::obtenerTipoDeCasilla(unsigned int x, unsigned int y, unsigned int z){

	return this->tablero->getCasillero(x,y,z)->getTipo();
}

 //REVISAR
bool BatallaCampal::movimientoCercano(Vector<unsigned int> * origen, Vector<unsigned int> * destino){
	int distX = (origen->obtener(1) - destino->obtener(1));
	int distY = (origen->obtener(2) - destino->obtener(2));
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

//REVISAR
Vector<unsigned int> * BatallaCampal::pedirOrigenDelMovimiento(Jugador *jugador){
	Vector<unsigned int> * vectorOrigen;
	bool origenValido = FALSE;
	while(!origenValido){
		std::cout << jugador->getNombre() << ", ingresa la coordenada del soldado que desea mover." << std::endl;
		vectorOrigen = pedirCoordenadas();
		if(!tieneUnsoldado(jugador,vectorOrigen->obtener(1),vectorOrigen->obtener(2),vectorOrigen->obtener(3))){
			std::cout << "No tienes ningun soldado en esa posicion. Intente de nuevo." << std::endl;
			delete vectorOrigen;
		}else{
			origenValido = TRUE;
	}
	return vectorOrigen;
}

//REVISAR
Vector<unsigned int> * BatallaCampal::pedirDestinoDelMovimiento(Jugador *jugador){
	Vector<unsigned int> * vectorDestino;
	bool destinoValido = FALSE;
	while(!destinoValido){
		std::cout << jugador->getNombre() << ", ingresa la coordenada a la cual desea mover su soldado." << std::endl;
		vectorDestino = pedirCoordenadas();
		if(tieneUnsoldado(jugador,vectorDestino->obtener(1),vectorDestino->obtener(2),vectorDestino->obtener(3))){
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



//REVISAR
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
		
//REVISAR
void BatallaCampal::mover(Vector<Vector<unsigned int> *> * coordenadasOrigenYDestino){
	
	unsigned int xOrigen = coordenadasOrigenYDestino->obtener(1)->obtener(1);
	unsigned int yOrigen = coordenadasOrigenYDestino->obtener(1)->obtener(2);
	unsigned int zOrigen = coordenadasOrigenYDestino->obtener(1)->obtener(3);
	unsigned int xDestino = coordenadasOrigenYDestino->obtener(2)->obtener(1);
	unsigned int yDestino = coordenadasOrigenYDestino->obtener(2)->obtener(2);
	unsigned int zDestino = coordenadasOrigenYDestino->obtener(2)->obtener(3);
	
	Ficha * ficha = this->tablero->getCasillero(xOrigen, yOrigen, zOrigen)->getFicha();
	this->tablero->getCasillero(xOrigen, yOrigen, zOrigen)->vaciar();

	if(this->tablero->getCasillero(xDestino, yDestino, zDestino)->estaOcupado()){
		this->tablero->getCasillero(xDestino, yDestino, zDestino)->getFicha()->eliminar();
		this->tablero->getCasillero(xDestino, yDestino, zDestino)->vaciar();
		this->tablero->getCasillero(xDestino, yDestino, zDestino)->destruir();
		ficha->eliminar();

	}else{
		this->tablero->getCasillero(xDestino, yDestino, zDestino)->setFicha(ficha);
	}

	destruirCoordenadasDelMovimiento(coordenadasOrigenYDestino);

}

	
void BatallaCampal::colocarAvion(Jugador * jugador){
	Vector<unsigned int> * vectorPosicion;
	bool posicionValida = FALSE;
	while(!posicionValida){
		std::cout << jugador->getNombre() << ", ingresa la coordenada en la cual desea colocar su avion." << std::endl;
		vectorPosicion = pedirCoordenadas();
		unsigned int x = vectorPosicion->obtener(1);
		unsigned int y = vectorPosicion->obtener(2);
		unsigned int z = vectorPosicion->obtener(3);
		if(obtenerTipoDeCasilla(x,y,z) != Aire){
			std::cout << "Solo puedes colocar un avion en el aire. Intente de nuevo." << std::endl;
			delete vectorPosicion;
		
		}else if(this->tablero->getCasillero(xDestino, yDestino, zDestino)->estaOcupado()){
			Jugador * jugadorContrario = this->tablero->getCasillero(xDestino, yDestino, zDestino)->getFicha()->getJugador();
			jugadorContrario->eliminarFicha(his->tablero->getCasillero(xDestino, yDestino, zDestino)->getFicha());
			this->tablero->getCasillero(xDestino, yDestino, zDestino)->vaciar();
			std::cout << "Tu avion choco con otro avion." << std::endl;

		}else{
			Ficha * fichaAvion = new Ficha(Avion, jugador, Activa);
			this->tablero->getCasillero(x,y,z)->setFicha(fichaAvion);
			jugador->agregarFicha(fichaAvion);
			disparar();//completar
			disparar();
		}
	}
	
	delete vectorDestino;

}

void BatallaCampal::sacarCarta(Jugador * jugador){//AL final del turno
	
	srand(time(NULL));
	int numeroDeCarta  = rand() % 12;
	
	if(numeroDeCarta == Avion){
		colocarAvion(jugador);
	}else if(numeroDeCarta == Barco){
		colocarBarco(jugador);
	}else if(numeroDeCarta == Misil){
		dispararMisil(jugador);
	}else if(numeroDeCarta == OtroTurno){
		jugarTurno(jugador);
	}else if(numeroDeCarta == ReconstruirTerreno){
		recontruirTerreno(jugador);
	}else if(numeroDeCarta == RondaSinCartas){
		jugarRonda()//revisar
	}
}

