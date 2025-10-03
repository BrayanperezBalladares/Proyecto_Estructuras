#include "Paquete.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
using namespace std;

// Inicializaci�n del contador est�tico
int Paquete::contadorCodigo = 1000;

Paquete::Paquete() {
}

Paquete::~Paquete() {
}

// M�todos est�ticos
int Paquete::obtenerContadorCodigo() {
	return contadorCodigo;
}

void Paquete::incrementarContador() {
	contadorCodigo++;
}

// Funci�n auxiliar para obtener fecha y hora actual
string obtenerFechaHoraActual() {
	time_t ahora = time(0);
	tm *ltm = localtime(&ahora);
	
	stringstream ss;
	ss << setfill('0') << setw(2) << ltm->tm_mday << "/"
		<< setfill('0') << setw(2) << (1 + ltm->tm_mon) << "/"
		<< (1900 + ltm->tm_year) << " "
		<< setfill('0') << setw(2) << ltm->tm_hour << ":"
		<< setfill('0') << setw(2) << ltm->tm_min << ":"
		<< setfill('0') << setw(2) << ltm->tm_sec;
	
	return ss.str();
}
