#ifndef PAQUETE_H
#define PAQUETE_H
#include <iostream>
#include <string>
using namespace std;

typedef class Paquete {
public:
	Paquete();
	~Paquete();
	
	// Atributos públicos
	int codigo;
	string direccion;
	string fechaHora;
	double peso;
	char tipo; // 'U' = Urgente, 'N' = Normal
	class Paquete *siguiente;
	
	// Métodos auxiliares estáticos
	static int obtenerContadorCodigo();
	static void incrementarContador();
	
private:
	static int contadorCodigo; // Auto-incremental
	
} nodoPaquete;

// Función auxiliar para obtener fecha y hora
string obtenerFechaHoraActual();

#endif
