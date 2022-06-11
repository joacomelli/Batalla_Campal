#ifndef JUGADOR_H_
#define JUGADOR_H_

#include <string>
#include "Ficha.h"
#include "Lista.h"

class Jugador {
private:
	unsigned int numero;
	std::string nombre;
	Lista <Ficha*> * fichas;

public:
	//PRE: El numero debe ser mayor o igual a 1, y el nombre no puede estar vacio.
	//POST: Crea al jugador con su numero y su nombre.
	Jugador(unsigned int numero, std::string nombre);

	//PRE:
	//POST: Elimina al jugador.
	virtual ~Jugador();

	//PRE: El jugador debe existir.
	//POST: Muestra el nombre del jugador
	const std::string& getNombre() const;

	//PRE: El jugador debe existir.
	//POST: Muestra el numero del jugador.
	int getNumero() const;
	
	//PRE: El jugador debe existir.
	//POST: Devuelve un puntero a la lista de fichas del jugador.
	Lista<Ficha*> * getFichas();
	
	//PRE: La ficha recibida no debe ser NULL.
	//POST: Si la lista de fichas esta vacia la crea y agrega la ficha. Si la lista ya esta creada agrega la ficha al principio.
	void agregarFicha(Ficha* ficha);
	
	//PRE: La ficha recibida no debe ser NULL y debe pertenecer a la lista de fichas.
	//POST: Elimina el nodo de la lista correspondiente a esa ficha.
	void eliminarFicha(Ficha* ficha);
	

	//PRE: Debe existir la ficha
	//POST: Devuelve True si el jugador tiene una ficha TipoDeFicha.
	bool tieneLaFicha(TipoDeFicha tipo);
	
};

#endif
