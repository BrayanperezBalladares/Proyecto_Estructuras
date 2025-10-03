#include "Motorizado.h"
#include <iostream>
#include <iomanip>
using namespace std;

// Lista global doblemente enlazada
nodoMotorizado *listaMotorizados = NULL;

Motorizado::Motorizado() {
}

Motorizado::~Motorizado() {
}

// ========== MÉTODOS AUXILIARES ==========

int nodoMotorizado::contarMotorizadosActivos() {
	int contador = 0;
	nodoMotorizado *aux = listaMotorizados;
	while (aux != NULL) {
		if (aux->activo) {
			contador++;
		}
		aux = aux->siguiente;
	}
	return contador;
}

bool nodoMotorizado::existeID(int _id) {
	nodoMotorizado *aux = listaMotorizados;
	while (aux != NULL) {
		if (aux->id == _id) {
			return true;
		}
		aux = aux->siguiente;
	}
	return false;
}

bool nodoMotorizado::existePlaca(string _placa) {
	nodoMotorizado *aux = listaMotorizados;
	while (aux != NULL) {
		if (aux->placa == _placa) {
			return true;
		}
		aux = aux->siguiente;
	}
	return false;
}

nodoMotorizado* nodoMotorizado::buscarMotorizadoPorID(int _id) {
	nodoMotorizado *aux = listaMotorizados;
	while (aux != NULL) {
		if (aux->id == _id) {
			return aux;
		}
		aux = aux->siguiente;
	}
	return NULL;
}

int nodoMotorizado::contarPaquetesMotorizado(int _id) {
	nodoMotorizado *motorizado = buscarMotorizadoPorID(_id);
	if (motorizado == NULL) {
		return 0;
	}
	
	int contador = 0;
	nodoPaquete *aux = motorizado->inicioPaquetes;
	while (aux != NULL) {
		contador++;
		aux = aux->siguiente;
	}
	return contador;
}

nodoMotorizado* nodoMotorizado::obtenerMotorizadoConMenosPaquetes() {
	nodoMotorizado *aux = listaMotorizados;
	nodoMotorizado *mejorMotorizado = NULL;
	int menorCantidad = 999999;
	
	while (aux != NULL) {
		if (aux->activo) {
			int cantidadPaquetes = contarPaquetesMotorizado(aux->id);
			if (cantidadPaquetes < menorCantidad) {
				menorCantidad = cantidadPaquetes;
				mejorMotorizado = aux;
			}
		}
		aux = aux->siguiente;
	}
	
	return mejorMotorizado;
}

// ========== AGREGAR MOTORIZADO ==========

void nodoMotorizado::agregarMotorizado(int _id, string _nombre, string _placa) {
	// Validaciones
	if (_nombre.empty()) {
		cout << "\n? ERROR: El nombre no puede estar vacío.\n";
		return;
	}
	
	if (_placa.empty()) {
		cout << "\n? ERROR: La placa no puede estar vacía.\n";
		return;
	}
	
	if (existeID(_id)) {
		cout << "\n? ERROR: Ya existe un motorizado con ID " << _id << ".\n";
		return;
	}
	
	if (existePlaca(_placa)) {
		cout << "\n? ERROR: Ya existe un motorizado con placa " << _placa << ".\n";
		return;
	}
	
	if (contarMotorizadosActivos() >= 6) {
		cout << "\n? ERROR: Ya hay 6 motorizados activos. No se pueden agregar más.\n";
		return;
	}
	
	// Crear nuevo motorizado
	nodoMotorizado *nuevo = new nodoMotorizado;
	nuevo->id = _id;
	nuevo->nombre = _nombre;
	nuevo->placa = _placa;
	nuevo->activo = true;
	nuevo->inicioPaquetes = NULL;
	nuevo->siguiente = NULL;
	nuevo->anterior = NULL;
	
	// Insertar en lista doblemente enlazada
	if (listaMotorizados == NULL) {
		listaMotorizados = nuevo;
	} else {
		nodoMotorizado *aux = listaMotorizados;
		while (aux->siguiente != NULL) {
			aux = aux->siguiente;
		}
		aux->siguiente = nuevo;
		nuevo->anterior = aux;
	}
	
	cout << "\n? Motorizado agregado exitosamente con ID: " << _id << "\n";
}

// ========== MOSTRAR MOTORIZADOS ==========

void nodoMotorizado::mostrarMotorizados() {
	if (listaMotorizados == NULL) {
		cout << "\n??? No hay motorizados registrados.\n";
		return;
	}
	
	nodoMotorizado *aux = listaMotorizados;
	
	cout << "\n+------------------------------------------------------------------------+\n";
	cout << "¦                    LISTA DE MOTORIZADOS REGISTRADOS                    ¦\n";
	cout << "+------------------------------------------------------------------------+\n\n";
	
	while (aux != NULL) {
		int cantidadPaquetes = contarPaquetesMotorizado(aux->id);
		
		cout << "+--------------------------------------------------------------------+\n";
		cout << "¦ ID:             " << aux->id << "\n";
		cout << "¦ Nombre:         " << aux->nombre << "\n";
		cout << "¦ Placa:          " << aux->placa << "\n";
		cout << "¦ Estado:         " << (aux->activo ? "? ACTIVO" : "? INACTIVO") << "\n";
		cout << "¦ Paquetes:       " << cantidadPaquetes << "\n";
		cout << "+--------------------------------------------------------------------+\n\n";
		
		aux = aux->siguiente;
	}
}

// ========== MODIFICAR MOTORIZADO ==========

void nodoMotorizado::modificarMotorizado(int _id) {
	nodoMotorizado *motorizado = buscarMotorizadoPorID(_id);
	
	if (motorizado == NULL) {
		cout << "\n? ERROR: No se encontró un motorizado con ID " << _id << ".\n";
		return;
	}
	
	int opcion;
	cout << "\n--- MODIFICAR MOTORIZADO ---\n";
	cout << "1. Modificar Nombre\n";
	cout << "2. Cambiar Estado (Activo/Inactivo)\n";
	cout << "Opción: ";
	cin >> opcion;
	cin.ignore();
	
	if (opcion == 1) {
		string nuevoNombre;
		cout << "Nuevo nombre: ";
		getline(cin, nuevoNombre);
		if (!nuevoNombre.empty()) {
			motorizado->nombre = nuevoNombre;
			cout << "\n? Nombre actualizado exitosamente.\n";
		} else {
			cout << "\n? ERROR: El nombre no puede estar vacío.\n";
		}
	} else if (opcion == 2) {
		motorizado->activo = !motorizado->activo;
		cout << "\n? Estado cambiado a: " << (motorizado->activo ? "ACTIVO" : "INACTIVO") << "\n";
		if (!motorizado->activo) {
			cout << "?? Este motorizado ya no recibirá nuevos paquetes.\n";
		}
	} else {
		cout << "\n? Opción inválida.\n";
	}
}

// ========== ELIMINAR MOTORIZADO ==========

void nodoMotorizado::eliminarMotorizado(int _id) {
	nodoMotorizado *motorizado = buscarMotorizadoPorID(_id);
	
	if (motorizado == NULL) {
		cout << "\n? ERROR: No se encontró un motorizado con ID " << _id << ".\n";
		return;
	}
	
	// Verificar que no tenga paquetes pendientes
	if (motorizado->inicioPaquetes != NULL) {
		cout << "\n? ERROR: No se puede eliminar. El motorizado tiene paquetes pendientes.\n";
		return;
	}
	
	// Eliminar de la lista doblemente enlazada
	if (motorizado->anterior == NULL) {
		// Es el primero
		listaMotorizados = motorizado->siguiente;
		if (listaMotorizados != NULL) {
			listaMotorizados->anterior = NULL;
		}
	} else {
		motorizado->anterior->siguiente = motorizado->siguiente;
		if (motorizado->siguiente != NULL) {
			motorizado->siguiente->anterior = motorizado->anterior;
		}
	}
	
	delete motorizado;
	cout << "\n? Motorizado eliminado exitosamente.\n";
}

// ========== AGREGAR PAQUETE A MOTORIZADO ==========

void nodoMotorizado::agregarPaqueteAMotorizado(string _direccion, double _peso, char _tipo) {
	// Validaciones
	if (_direccion.empty()) {
		cout << "\n? ERROR: La dirección no puede estar vacía.\n";
		return;
	}
	
	if (_peso <= 0) {
		cout << "\n? ERROR: El peso debe ser un valor positivo.\n";
		return;
	}
	
	if (_tipo != 'U' && _tipo != 'u' && _tipo != 'N' && _tipo != 'n') {
		cout << "\n? ERROR: El tipo debe ser 'U' (Urgente) o 'N' (Normal).\n";
		return;
	}
	
	_tipo = toupper(_tipo);
	
	// Verificar que haya motorizados activos
	if (contarMotorizadosActivos() == 0) {
		cout << "\n? ERROR: No hay motorizados activos disponibles.\n";
		return;
	}
	
	// Obtener el motorizado con menos paquetes
	nodoMotorizado *motorizado = obtenerMotorizadoConMenosPaquetes();
	
	if (motorizado == NULL) {
		cout << "\n? ERROR: No se pudo asignar el paquete.\n";
		return;
	}
	
	// Crear nuevo paquete
	nodoPaquete *nuevo = new nodoPaquete;
	Paquete::incrementarContador();
	nuevo->codigo = Paquete::obtenerContadorCodigo();
	nuevo->direccion = _direccion;
	nuevo->peso = _peso;
	nuevo->tipo = _tipo;
	nuevo->fechaHora = obtenerFechaHoraActual();
	nuevo->siguiente = NULL;
	
	// Insertar según tipo
	if (_tipo == 'U') {
		// URGENTE: al inicio
		nuevo->siguiente = motorizado->inicioPaquetes;
		motorizado->inicioPaquetes = nuevo;
		cout << "\n? Paquete URGENTE #" << nuevo->codigo << " asignado a " << motorizado->nombre 
			<< " (ID: " << motorizado->id << ") al INICIO de su cola.\n";
	} else {
		// NORMAL: al final
		if (motorizado->inicioPaquetes == NULL) {
			motorizado->inicioPaquetes = nuevo;
		} else {
			nodoPaquete *aux = motorizado->inicioPaquetes;
			while (aux->siguiente != NULL) {
				aux = aux->siguiente;
			}
			aux->siguiente = nuevo;
		}
		cout << "\n? Paquete NORMAL #" << nuevo->codigo << " asignado a " << motorizado->nombre 
			<< " (ID: " << motorizado->id << ") al FINAL de su cola.\n";
	}
}

// ========== MOSTRAR PAQUETES DE UN MOTORIZADO ==========

void nodoMotorizado::mostrarPaquetesMotorizado(int _id) {
	nodoMotorizado *motorizado = buscarMotorizadoPorID(_id);
	
	if (motorizado == NULL) {
		cout << "\n? ERROR: No se encontró un motorizado con ID " << _id << ".\n";
		return;
	}
	
	cout << "\n+------------------------------------------------------------------------+\n";
	cout << "¦  Paquetes de: " << motorizado->nombre << " (ID: " << motorizado->id << ")\n";
	cout << "+------------------------------------------------------------------------+\n\n";
	
	if (motorizado->inicioPaquetes == NULL) {
		cout << "?? Este motorizado no tiene paquetes asignados.\n";
		return;
	}
	
	nodoPaquete *aux = motorizado->inicioPaquetes;
	int contador = 1;
	
	while (aux != NULL) {
		cout << "+--------------------------------------------------------------------+\n";
		cout << "¦ Paquete #" << contador << "\n";
		cout << "+--------------------------------------------------------------------¦\n";
		cout << "¦ Código:         " << aux->codigo << "\n";
		cout << "¦ Dirección:      " << aux->direccion << "\n";
		cout << "¦ Peso:           " << fixed << setprecision(2) << aux->peso << " kg\n";
		cout << "¦ Tipo:           " << (aux->tipo == 'U' ? "URGENTE ??" : "NORMAL ??") << "\n";
		cout << "¦ Fecha y Hora:   " << aux->fechaHora << "\n";
		cout << "+--------------------------------------------------------------------+\n\n";
		
		aux = aux->siguiente;
		contador++;
	}
}

// ========== ELIMINAR PAQUETE POR CÓDIGO ==========

void nodoMotorizado::eliminarPaquete(int _codigo) {
	nodoMotorizado *aux = listaMotorizados;
	bool encontrado = false;
	
	while (aux != NULL && !encontrado) {
		nodoPaquete *paquete = aux->inicioPaquetes;
		nodoPaquete *anterior = NULL;
		
		while (paquete != NULL && !encontrado) {
			if (paquete->codigo == _codigo) {
				encontrado = true;
				
				// Eliminar el paquete
				if (anterior == NULL) {
					aux->inicioPaquetes = paquete->siguiente;
				} else {
					anterior->siguiente = paquete->siguiente;
				}
				
				delete paquete;
				cout << "\n? Paquete #" << _codigo << " eliminado del motorizado " 
					<< aux->nombre << " (ID: " << aux->id << ").\n";
			} else {
				anterior = paquete;
				paquete = paquete->siguiente;
			}
		}
		
		aux = aux->siguiente;
	}
	
	if (!encontrado) {
		cout << "\n? ERROR: No se encontró un paquete con código " << _codigo << ".\n";
	}
}

// ========== ENTREGAR PAQUETES ==========

void nodoMotorizado::entregarPaquetes() {
	if (listaMotorizados == NULL) {
		cout << "\n? No hay motorizados registrados.\n";
		return;
	}
	
	nodoMotorizado *aux = listaMotorizados;
	bool seEntregoAlguno = false;
	
	cout << "\n+------------------------------------------------------------------------+\n";
	cout << "¦                        PROCESO DE ENTREGA                              ¦\n";
	cout << "+------------------------------------------------------------------------+\n\n";
	
	while (aux != NULL) {
		if (aux->activo && aux->inicioPaquetes != NULL) {
			// Contar antes
			int cantidadAntes = contarPaquetesMotorizado(aux->id);
			
			// Entregar primer paquete
			nodoPaquete *entregado = aux->inicioPaquetes;
			aux->inicioPaquetes = entregado->siguiente;
			
			cout << "??? Motorizado: " << aux->nombre << " (ID: " << aux->id << ")\n";
			cout << "   ?? Entregó paquete #" << entregado->codigo << "\n";
			cout << "   ?? Dirección: " << entregado->direccion << "\n";
			cout << "   ?? Paquetes antes: " << cantidadAntes << " ? Después: " << (cantidadAntes - 1) << "\n\n";
			
			delete entregado;
			seEntregoAlguno = true;
		}
		
		aux = aux->siguiente;
	}
	
	if (!seEntregoAlguno) {
		cout << "?? No hay paquetes para entregar.\n";
	}
}
