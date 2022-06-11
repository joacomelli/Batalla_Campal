#include "Imagen.h"
#include <string>

using namespace std; 
/////Falta armamento!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
Imagen::Imagen(){
    this->inactiva.ReadFromFile("inactiva.bmp");
    this->avion.ReadFromFile("avion.bmp");
    this->barco.ReadFromFile("barco.bmp");
    this->soldado.ReadFromFile("Soldado.bmp");
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
						this->avion.TellHeight(), 0,this->estado, 1070 - coordenadaZ*40,
						45 + coordenadaX*40,*this->avion(0,0) );

		RangedPixelToPixelCopyTransparent( this->avion, 0, this->avion.TellWidth(),
						this->avion.TellHeight(), 0,this->estado, 76 + coordenadaY*40,
						1035 - coordenadaZ*40,*this->avion(0,0) );
}

void EstadoTablero::agregarSoldadoAEstado(int coordenadaX, int coordenadaY){
		RangedPixelToPixelCopyTransparent( this->soldado, 0, this->soldado.TellWidth(),
						this->soldado.TellHeight(), 0,this->estado, 76 + coordenadaY*40,
						45 + coordenadaX*40,*this->soldado(0,0) );
}

void EstadoTablero::agregarBarcoAEstado(int coordenadaX, int coordenadaY){
		RangedPixelToPixelCopyTransparent( this->barco, 0, this->barco.TellWidth(),
						this->barco.TellHeight(), 0,this->estado, 76+ coordenadaY*40,
						45 + coordenadaX*40,*this->barco(0,0) );
}

//mejor un bool en vez de string pero no tengo ganas de pensar
void EstadoTablero::agregarInactivaAEstado(int coordenadaX, int coordenadaY, in coordenadaZ, string plano){
	if (plano == 'XY'){
		RangedPixelToPixelCopyTransparent( this->inactiva, 0, this->inactiva.TellWidth(),
				this->inactiva.TellHeight(), 0,this->estado, 76+ coordenadaY*40,
				45 + coordenadaX*40,*this->inactiva(0,0) );
	} else if (plano == 'XYZ'){
		RangedPixelToPixelCopyTransparent( this->inactiva, 0, this->inactiva.TellWidth(),
						this->inactiva.TellHeight(), 0,this->estado, 1070 - coordenadaZ*40,
						45 + coordenadaX*40,*this->inactiva(0,0) );

		RangedPixelToPixelCopyTransparent( this->inactiva, 0, this->inactiva.TellWidth(),
						this->inactiva.TellHeight(), 0,this->estado, 76 + coordenadaY*40,
						1035 - coordenadaZ*40,*this->inactiva(0,0) );
	}	
}

void Imagen::definirMapa(string background){
  if (background == "Background1" || background == "Background2"  || background == "Background3"){
    string fileName = background + ".bmp";	 
    this->background.ReadfromFile(fileName.c_str()); 
  } 
 }
  

//Lista<Lista<Lista<Casilla *> *> *> casillas
void Imagen::recorrerTablero(Tablero * tablero, Jugador * jugador){
        tablero->getCasilleros()->iniciarCursor();
        while(tablero->getCasilleros()->avanzarCursor()){
            <Lista<Lista<Casilla *> *> * casillasPlanoXY = tablero->getCasilleros()->obtenerCursor();//PLANO XY
            this->recorrerPlanoXY(casillasPlanoXY, jugador);
        }
    }

void Imagen::recorrerPlanoXY(<Lista<Lista<Casilla *> *> * casillas, Jugador * jugador){
        casillas->iniciarCursor();
        while(casillas->avanzarCursor()){
            <Lista<Casilla *> * casillasRecta = casillas->obtenerCursor();
            this->recorrerCasilla(casillasRecta, jugador);
        }
    }

void Imagen::recorrerCasilla(<Lista<Casilla *> * casillas, Jugador * jugadorActual){
        casillas->iniciarCursor();
        while(casillas->avanzarCursor()){
            Casilla * casilla = casillas->obtenerCursor();
            if((casilla->estaOcupado()) && (casilla->getFicha()->getJugador()->getNombre() == jugadorActual->getNombre())){
		TipoDeFicha tipo = casilla->getFicha()->getTipo();
               	this->chequearFicha(tipo, casilla); 
            }
            else if(casilla->getEstado() == Inactiva){
            	if (casilla->getZ() == 1){
			agregarInactivaAEstado(casilla->getX(), casilla->getY(),casilla->getZ(), "XY");
		} else if (casilla->getFicha() != NULL)	{
			agregarInactivaAEstado(casilla->getX(), casilla->getY(),casilla->getZ(), "XYZ");
		//la casilla esta inactiva pero podria haber estado vacia antes (creo) esto se fija q si devuelve
		// null el get ficha es xq taba vacia antes y no tenia ninguna ficha, en cambio al ser z mayor a 1 
		// son solo aviones las posibles fichas y como (creo) queremos mostrar solo las casillas inactivas del plano
		//ZY y ZX q taban ocupados x aviones, esto hace eso. 
            }
        }
    }
 
void Imagen::chequearFicha(TipoDeFicha tipo, Casilla * casilla){
	if (tipo == FAvion) {
		this->agregarAvionAEstado(casilla->getX(), casilla->getY(),casilla->getZ());
	} else if (tipo == FSoldado){
		this->agregarSoldadoAEstado(casilla->getX(), casilla->getY());
	} else if (tipo == FBarco) 
		this->agregarBarcoAEstado(casilla->getX(), casilla->getY());
	}
}	
	       
void Imagen::obtenerEstadoTablero( Tablero * tablero, Jugador *jugador){
  this->medidaDeEstado();
  this->agregarFondoAEstado();
  this->recorrerTablero(tablero, jugador);
  string fileName = "estadoTableroDe"+ jugador->getNombre + ".bmp";
  this->estado.WriteToFile(fileName.c_str());
}
