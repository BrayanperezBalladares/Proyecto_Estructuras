#include <iostream>
#include <limits>
#include "Motorizado.h"
using namespace std;

void limpiarBuffer() {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void mostrarMenuPrincipal() {
	cout << "\n+----------------------------------------------------------------+\n";
	cout << "¦          SISTEMA DE GESTIÓN DE PAQUETERÍA - EnvíoExpress      ¦\n";
	cout << "+----------------------------------------------------------------+\n";
	cout << "+----------------------------------------------------------------+\n";
	cout << "¦                    MÓDULO DE MOTORIZADOS                       ¦\n";
	cout << "+----------------------------------------------------------------¦\n";
	cout << "¦ 1. Agregar Motorizado                                          ¦\n";
	cout << "¦ 2. Mostrar Motorizados                                         ¦\n";
	cout << "¦ 3. Modificar Motorizado                                        ¦\n";
	cout << "¦ 4. Eliminar Motorizado                                         ¦\n";
	cout << "+----------------------------------------------------------------¦\n";
	cout << "¦                     MÓDULO DE PAQUETES                         ¦\n";
	cout << "+----------------------------------------------------------------¦\n";
	cout << "¦ 5. Agregar Paquete                                             ¦\n";
	cout << "¦ 6. Mostrar Paquetes de un Motorizado                           ¦\n";
	cout << "¦ 7. Eliminar Paquete por Código                                 ¦\n";
	cout << "¦ 8. Entregar Paquetes                                           ¦\n";
	cout << "+----------------------------------------------------------------¦\n";
	cout << "¦ 0. Salir                                                       ¦\n";
	cout << "+----------------------------------------------------------------+\n";
	cout << "Seleccione una opción: ";
}

int main() {
	Motorizado m;
	int opcion;
	int id;
	string nombre, placa, direccion;
	double peso;
	char tipo;
	int codigo;
	
	do {
		mostrarMenuPrincipal();
		cin >> opcion;
		
		if (cin.fail()) {
			limpiarBuffer();
			cout << "\n? ERROR: Ingrese un número válido.\n";
			continue;
		}
		
		limpiarBuffer();
		
		switch(opcion) {
		case 1: // Agregar Motorizado
			cout << "\n+--------------------------------------+\n";
			cout << "¦      AGREGAR NUEVO MOTORIZADO        ¦\n";
			cout << "+--------------------------------------+\n";
			cout << "ID del motorizado: ";
			cin >> id;
			limpiarBuffer();
			cout << "Nombre: ";
			getline(cin, nombre);
			cout << "Placa: ";
			getline(cin, placa);
			m.agregarMotorizado(id, nombre, placa);
			break;
			
		case 2: // Mostrar Motorizados
			m.mostrarMotorizados();
			break;
			
		case 3: // Modificar Motorizado
			cout << "\nIngrese el ID del motorizado a modificar: ";
			cin >> id;
			limpiarBuffer();
			m.modificarMotorizado(id);
			break;
			
		case 4: // Eliminar Motorizado
			cout << "\nIngrese el ID del motorizado a eliminar: ";
			cin >> id;
			limpiarBuffer();
			m.eliminarMotorizado(id);
			break;
			
		case 5: // Agregar Paquete
			cout << "\n+--------------------------------------+\n";
			cout << "¦        AGREGAR NUEVO PAQUETE         ¦\n";
			cout << "+--------------------------------------+\n";
			cout << "Dirección de destino: ";
			getline(cin, direccion);
			cout << "Peso (kg): ";
			cin >> peso;
			limpiarBuffer();
			cout << "Tipo (U=Urgente / N=Normal): ";
			cin >> tipo;
			limpiarBuffer();
			m.agregarPaqueteAMotorizado(direccion, peso, tipo);
			break;
			
		case 6: // Mostrar Paquetes de un Motorizado
			cout << "\nIngrese el ID del motorizado: ";
			cin >> id;
			limpiarBuffer();
			m.mostrarPaquetesMotorizado(id);
			break;
			
		case 7: // Eliminar Paquete
			cout << "\nIngrese el código del paquete a eliminar: ";
			cin >> codigo;
			limpiarBuffer();
			m.eliminarPaquete(codigo);
			break;
			
		case 8: // Entregar Paquetes
			m.entregarPaquetes();
			break;
			
		case 0:
			cout << "\n+--------------------------------------+\n";
			cout << "¦  Gracias por usar EnvíoExpress ??    ¦\n";
			cout << "+--------------------------------------+\n";
			break;
			
		default:
			cout << "\n? Opción inválida. Intente de nuevo.\n";
		}
		
		if (opcion != 0) {
			cout << "\nPresione ENTER para continuar...";
			cin.get();
		}
		
	} while(opcion != 0);
	
	return 0;
}

