#ifndef JUGADOR_H_
#define JUGADOR_H_

#include <string>

class Jugador {
private:
	unsigned int numero;
	std::string nombre;

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
};

#endif
