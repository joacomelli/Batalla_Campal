#include "BatallaCampal.h"


BatallaCampal::BatallaCampal() {
	this->tablero = NULL;
	this->jugadores = NULL;
	this->cantidadDeJugadores = 0;

}

BatallaCampal::~BatallaCampal() {

}

// TERMINAR
void BatallaCampal::menuDeJuego(unsigned int * numeroDeEscenario){
	
	std::cout << "Bienvenido a la BatallaCampal." << std::endl;
	while(cantidadDeJugadores > MAXIMO_DE_JUGADORES || cantidadDeJugadores < MINIMO_DE_JUGADORES){ 
		std::cout << "Ingrese la cantidad de jugadores que van a participar. (" << MINIMO_DE_JUGADORES << " a " << MAXIMO_DE_JUGADORES << ")" << std::endl;
		std::cin >> this->cantidadDeJugadores;
		if(cantidadDeJugadores > MAXIMO_DE_JUGADORES || cantidadDeJugadores < MINIMO_DE_JUGADORES){
			std::cout << "La cantidad de jugadores elegida no es valida. (" << MINIMO_DE_JUGADORES << " a " << MAXIMO_DE_JUGADORES << ")" << std::endl;
		}
	}
	
	this->jugadores = new Lista <Jugador *>();
	for(unsigned int i = 1; i <= cantidadDeJugadores; i++){
		std::string nombreJugador;
		std::cout << "Jugador " <<  i << " ingrese su nombre." << std::endl;
		std::cin >> nombreJugador;
		
		this->jugadores->agregar(new Jugador(i,nombreJugador),i);
		
	}
	*numeroDeEscenario = 0;
	while(numeroDeEscenario < 1 || numeroDeEscenario > NUM_MAPA_MAXIMO){ 
		std::cout << "Ingrese el numero de mapa que desea jugar. (1 a " << NUM_MAPA_MAXIMO << ")" << std::endl;
		std::cin >> *numeroDeEscenario;
		if(numeroDeEscenario < 1 || numeroDeEscenario > NUM_MAPA_MAXIMO){
			std::cout << "El numero de mapa ingresado no es valido. (1 a " << NUM_MAPA_MAXIMO << ")" << std::endl;
		}
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
	Vector<unsigned int> * coordenadas = new Vector<unsigned int> (3, 0);
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
	
void BatallaCampal::inicializarSoldados(){
	for(unsigned int i = 1; i <= SOLDADOS_INICIALES; i++){
		for(unsigned int j = 1; j <= this->cantidadDeJugadores; j++){
			std::cout << "Jugador " << this->jugadores->obtener(j)->getNombre() << " ingrese la coordenada para su soldado " << i << std::endl;
			Vector<unsigned int> * coordenadas = pedirDestinoDelSoldado(Jugador * jugador);
			colocarSoldado(new Ficha(Soldado,this->jugadores->obtener(j),Activa),coordenadas);
		}
	}
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
		&& (obtenerFicha(x, y, z)->getTipo() == FSoldado));
}

//REVISAR
Vector<unsigned int> * BatallaCampal::pedirOrigenDelMovimiento(Jugador *jugador){
	Vector<unsigned int> * vectorOrigen;
	bool origenValido = false;
	while(!origenValido){
		std::cout << jugador->getNombre() << ", ingresa la coordenada del soldado que desea mover." << std::endl;
		vectorOrigen = pedirCoordenadas();
		if(!tieneUnSoldado(jugador,vectorOrigen->obtener(1),vectorOrigen->obtener(2),vectorOrigen->obtener(3))){
			std::cout << "No tienes ningun soldado en esa posicion. Intente de nuevo." << std::endl;
			delete vectorOrigen;
		}else{
			origenValido = true;
		}
	}
	return vectorOrigen;
}

//REVISAR
Vector<unsigned int> * BatallaCampal::pedirDestinoDelSoldado(Jugador *jugador){
	Vector<unsigned int> * vectorDestino;
	bool destinoValido = false;
	while(!destinoValido){
		std::cout << jugador->getNombre() << ", ingresa la coordenada en la cual desea colocar su soldado." << std::endl;
		vectorDestino = pedirCoordenadas();
		unsigned int x = vectorDestino->obtener(1);
		unsigned int y = vectorDestino->obtener(2);
		unsigned int z = vectorDestino->obtener(3);

		if(tieneUnSoldado(jugador,x,y,z)){
			std::cout << "Ya tienes un soldado en esa posicion. Intente de nuevo." << std::endl;
			delete vectorDestino;
		}else if(obtenerTipoDeCasilla(x,y,z) != Tierra){
			std::cout << "Los soldados solo pueden moverse por tierra. Intente de nuevo." << std::endl;
			delete vectorDestino;
		}else if(obtenerEstadoDeCasilla(x,y,z) == Inactiva){
			std::cout << "El casillero al que deseas moverte esta destruido. Intente de nuevo." << std::endl;
			delete vectorDestino;
		}else{
			destinoValido = true;
		}	
	}
	return vectorDestino;
}



//REVISAR
Vector<Vector<unsigned int> *> * BatallaCampal::pedirMovimiento(Jugador *jugador){ //va en privado creo
	
	Vector<Vector<unsigned int> *> * coordenadasDelMovimiento = new Vector<Vector<unsigned int> *>(2,NULL);
	Vector<unsigned int> * origen;
	Vector<unsigned int> * destino;
	bool valido = false;
	while(!valido){
		origen = pedirOrigenDelMovimiento(jugador);
		destino = pedirDestinoDelSoldado(jugador);
		if(movimientoCercano(origen,destino)){
			coordenadasDelMovimiento->agregar(1,origen);
			coordenadasDelMovimiento->agregar(2,destino);
			valido = true;
		}else{
			delete origen;
			delete destino;
		}
	}
	return coordenadasDelMovimiento;
}
	
void BatallaCampal::destruirCoordenadasDelMovimiento(Vector<Vector<unsigned int> *> * coordenadas){
		
	delete coordenadas->obtener(1);
	delete coordenadas->obtener(2);
	delete coordenadas;
}

void BatallaCampal::colocarSoldado(Ficha * fichaSoldado, Vector<unsigned int> * posicion){
	unsigned int x = posicion->obtener(1);
	unsigned int y = posicion->obtener(2);
	unsigned int z = posicion->obtener(3);

	if(this->tablero->getCasillero(x,y,z)->estaOcupado()){
		Jugador * jugadorContrario = this->tablero->getCasillero(x,y,z)->getFicha()->getJugador();
		jugadorContrario->eliminarFicha(this->tablero->getCasillero(x,y,z)->getFicha());
		this->tablero->getCasillero(x,y,z)->destruir();
		ficha->eliminar();

	}else{
		this->tablero->getCasillero(x,y,z)->setFicha(ficha);
	}
}

//REVISAR
void BatallaCampal::mover(Vector<Vector<unsigned int> *> * coordenadasOrigenYDestino){
	
	unsigned int xOrigen = coordenadasOrigenYDestino->obtener(1)->obtener(1);
	unsigned int yOrigen = coordenadasOrigenYDestino->obtener(1)->obtener(2);
	unsigned int zOrigen = coordenadasOrigenYDestino->obtener(1)->obtener(3);
	
	Ficha * ficha = this->tablero->getCasillero(xOrigen, yOrigen, zOrigen)->getFicha();
	this->tablero->getCasillero(xOrigen, yOrigen, zOrigen)->vaciar();

	colocarSoldado(ficha,coordenadasOrigenYDestino->obtener(2));

	destruirCoordenadasDelMovimiento(coordenadasOrigenYDestino);

}


//TERMINAR
void BatallaCampal::lanzarMisil(Jugador * jugador){

	
	
	
	
}

void BatallaCampal::disparar(Jugador * jugador){
	Vector<unsigned int> * vectorPosicion;
	std::cout << jugador->getNombre() << ", ingresa la coordenada a la cual desea disparar." << std::endl;
	vectorPosicion = pedirCoordenadas();
	unsigned int x = vectorPosicion->obtener(1);
	unsigned int y = vectorPosicion->obtener(2);
	unsigned int z = vectorPosicion->obtener(3);
	
	if(obtenerEstadoDeCasilla(x,y,z) != Vacia){
		Jugador * jugadorContrario = this->tablero->getCasillero(x, y, z)->getFicha()->getNombre();
		jugadorContrario->eliminarFicha(this->tablero->getCasillero(x, y, z)->getFicha());
		std::cout << "Has conseguido una baja." << std::endl;
	}
	
	if(obtenerTipoDeCasilla(x,y,z) == Tierra){
			this->tablero->getCasillero(x,y,z)->destruir();
	}else{
			this->tablero->getCasillero(x,y,z)->vaciar();
	}
}

	
void BatallaCampal::colocarAvion(Jugador * jugador){
	Vector<unsigned int> * vectorPosicion;
	bool posicionValida = false;
	while(!posicionValida){
		std::cout << jugador->getNombre() << ", ingresa la coordenada en la cual desea colocar su avion." << std::endl;
		vectorPosicion = pedirCoordenadas();
		unsigned int x = vectorPosicion->obtener(1);
		unsigned int y = vectorPosicion->obtener(2);
		unsigned int z = vectorPosicion->obtener(3);
		if(obtenerTipoDeCasilla(x,y,z) != Aire){
			std::cout << "Solo puedes colocar un avion en el aire. Intente de nuevo." << std::endl;
			delete vectorPosicion;
		
		}else if(this->tablero->getCasillero(x, y, z)->estaOcupado()){
			Jugador * jugadorContrario = this->tablero->getCasillero(x, y, z)->getFicha()->getJugador();
			jugadorContrario->eliminarFicha(this->tablero->getCasillero(x, y, z)->getFicha());
			this->tablero->getCasillero(x, y, z)->vaciar();
			std::cout << "Tu avion choco con otro avion." << std::endl;
			posicionValida = true;

		}else{
			Ficha * fichaAvion = new Ficha(FAvion, jugador, Activa);
			this->tablero->getCasillero(x,y,z)->setFicha(fichaAvion);
			jugador->agregarFicha(fichaAvion);
			disparar(jugador);
			disparar(jugador);
			posicionValida = true;
		}
	}
	
	delete vectorPosicion;

}

void BatallaCampal::colocarBarco(Jugador * jugador){
	Vector<unsigned int> * vectorPosicion;
	bool posicionValida = false;
	while(!posicionValida){
		std::cout << jugador->getNombre() << ", ingresa la coordenada en la cual desea colocar su avion." << std::endl;
		vectorPosicion = pedirCoordenadas();
		unsigned int x = vectorPosicion->obtener(1);
		unsigned int y = vectorPosicion->obtener(2);
		unsigned int z = vectorPosicion->obtener(3);
		if(obtenerTipoDeCasilla(x,y,z) != Agua){
			std::cout << "Solo puedes colocar un barco en el agua. Intente de nuevo." << std::endl;
			delete vectorPosicion;
		
		}else if(this->tablero->getCasillero(x, y, z)->estaOcupado()){
			Jugador * jugadorContrario = this->tablero->getCasillero(x, y, z)->getFicha()->getJugador();
			jugadorContrario->eliminarFicha(this->tablero->getCasillero(x, y, z)->getFicha());
			this->tablero->getCasillero(x, y, z)->vaciar();
			std::cout << "Tu barco choco con otro barco." << std::endl;
			posicionValida = true;

		}else{
			Ficha * fichaBarco = new Ficha(FBarco, jugador, Activa);
			this->tablero->getCasillero(x,y,z)->setFicha(fichaBarco);
			jugador->agregarFicha(fichaBarco);
			//lanzarMisil();       //completar
			posicionValida = true;
			
		}
	}
	
	delete vectorPosicion;

}

//TERMINAR
void BatallaCampal::jugarTurno(Jugador * jugador){
	
}

//TERMINAR
void BatallaCampal::jugarRonda(){
	

}

//TERMINAR
void BatallaCampal::reconstruirTerreno(Jugador * jugador){
	Vector<unsigned int> * vectorPosicion;
	std::cout << jugador->getNombre() << ", ingresa la coordenada de la casilla que quiera reconstruir." << std::endl;
	vectorPosicion = pedirCoordenadas();
	unsigned int x = vectorPosicion->obtener(1);
	unsigned int y = vectorPosicion->obtener(2);
	unsigned int z = vectorPosicion->obtener(3);
	if(obtenerEstadoDeCasilla(x,y,z) == Vacia){
		
		
		
	}
	
	
	
}


void BatallaCampal::sacarCarta(Jugador * jugador){//AL final del turno
	srand(time(NULL));
	int numeroDeCarta  = rand() % 12;
	std::cout << jugador->getNombre() << " saco la carta ";
	switch(numeroDeCarta){
   		case Avion:
			std::cout << "de Avion." << std::endl;
			colocarAvion(jugador);
   			break;
   		case Barco:
			std::cout << "de Barco." << std::endl;
			colocarBarco(jugador);
    			break;
   		case Misil:
			std::cout << "de Misil." << std::endl;
			lanzarMisil(jugador);
   			break;
		case OtroTurno:
			std::cout << "Otro Turno. Juega de nuevo." << std::endl;
			jugarTurno(jugador);
			break;
		case OtroSoldado:
			std::cout << "de Otro Soldado" << std::endl;
			if(//chequea cuantos soldados tiene){
				Vector<unsigned int> * posicion = pedirDestinoDelSoldado(jugador);
				colocarSoldado(new Ficha(Soldado,jugador,Activa),posicion);
			}	
				
			break;
		case RondaSinCartas:
			std::cout << "de Ronda Sin Cartas." << std::endl;
			jugarRonda();//cartas desactivadas);
			break;
   		default:
			std::cout << "en Blanco." << std::endl;
			break;
	}
}

void BatallaCampal::mostrarEstadoTablero(Jugador * jugador){
	//va a recorrer tablero, x casilla se fija en las de estado ocupada, segun el 
	//jugador va a agregar a la imagen el tipo de ficha, y tmb las de estado inactiva. 
}
					      
