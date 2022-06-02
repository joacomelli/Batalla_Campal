#ifndef VECTOR_H_
#define VECTOR_H_

template<class T> class Vector {
private:
	T * datos;
	int longitud;

public:

	/**
	 * PRE: la longitud es mayor o igual a 1. Y el dato inicial puede ser NULL si es un puntero
	 * POST: deja un vector con las posiciones solicitadas
	 */
	Vector(int longitud, T datoInicial);

	/**
	 * PRE:
	 * POST: libera la memoria
	 */
	virtual ~Vector();

	/**
	 * PRE:
	 * POST: devuelve la longitud actual del vector
	 */
	int getLongitud();

	/**
	 * PRE: la posicion esta entre 1 y n (inclusive)
	 * POST: guarda el dato en la posicion indicada, sino devuelve error
	 */
	void agregar(int posicion, T dato);

	/**
	 * PRE: la posicion esta entre 1 y n (inclusive)
	 * POST: guarda el dato en la posicion indicada, sino devuelve error
	 */
	T& obtener(int posicion);
};

#endif /* VECTOR_H_ */
