#ifndef MOTORIZADO_H
#define MOTORIZADO_H
#include <iostream>
#include <string>
#include "Paquete.h"
using namespace std;

typedef class Motorizado {
public:
	Motorizado();
	~Motorizado();
	
	// M�todos principales
	void agregarMotorizado(int id, string nombre, string placa);
	void mostrarMotorizados();
	void modificarMotorizado(int id);
	void eliminarMotorizado(int id);
	
	// M�todos para paquetes
	void agregarPaqueteAMotorizado(string direccion, double peso, char tipo);
	void eliminarPaquete(int codigo);
	void entregarPaquetes();
	
	// M�todos auxiliares
	int contarMotorizadosActivos();
	bool existeID(int id);
	bool existePlaca(string placa);
	Motorizado* buscarMotorizadoPorID(int id);
	Motorizado* obtenerMotorizadoConMenosPaquetes();
	int contarPaquetesMotorizado(int id);
	void mostrarPaquetesMotorizado(int id);
	
	// Atributos p�blicos
	int id;
	string nombre;
	string placa;
	bool activo;
	nodoPaquete *inicioPaquetes; // Lista simple de paquetes
	class Motorizado *siguiente;
	class Motorizado *anterior;
	
private:
	
} nodoMotorizado;

#endif
