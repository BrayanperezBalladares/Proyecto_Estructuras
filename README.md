
# UNIVERSIDAD NACIONAL
## Sede Regional Chorotega, Campus Nicoya
### Carrera: Ingeniería en Sistemas de Información

---

### Nombre del curso: Estructura de Datos
### I Proyecto Programado - II Ciclo 2025
### Profesor: Msc. Walter León Chavarría

**Estudiante:** Brayan Pérez Balladares  
**Fecha de entrega:** 10 de octubre, 2025

---

## ÍNDICE

1. [Introducción](#introducción)
2. [Descripción del Problema](#descripción-del-problema)
3. [Comentarios de los Métodos Más Importantes](#comentarios-de-los-métodos-más-importantes)
4. [Manual de Usuario](#manual-de-usuario)
5. [Limitaciones del Proyecto](#limitaciones-del-proyecto)
6. [Conclusión](#conclusión)
7. [Comentarios Adicionales](#comentarios-adicionales)

---

## INTRODUCCIÓN

El presente documento describe el desarrollo e implementación del **Sistema de Gestión de Paquetería "EnvíoExpress"**, un proyecto académico diseñado para digitalizar el proceso de asignación y distribución de paquetes a unidades de transporte (motorizados) en una empresa de mensajería.

Este sistema ha sido desarrollado en C++ utilizando **estructuras de datos implementadas manualmente** (sin uso de librerías STL como `std::list` o `std::map`) y siguiendo los principios de **Programación Orientada a Objetos (POO)**.

El objetivo principal es demostrar el dominio de estructuras de datos fundamentales como:
- **Listas doblemente enlazadas** para la gestión de motorizados
- **Listas simplemente enlazadas** para la gestión de paquetes

El sistema permite:
- Gestionar motorizados con estados activos/inactivos
- Asignar paquetes de forma eficiente según su prioridad (urgente o normal)
- Realizar entregas y mantener un registro ordenado de las operaciones

---

## DESCRIPCIÓN DEL PROBLEMA

La empresa de mensajería **EnvíoExpress** enfrentaba un problema en la gestión manual de su sistema de distribución de paquetes. El proceso tradicional era ineficiente y propenso a errores humanos, lo que resultaba en:

1. **Asignación desbalanceada de paquetes** a los motorizados
2. **Pérdida de prioridad** en paquetes urgentes
3. **Dificultad para rastrear** paquetes y motorizados
4. **Falta de validaciones** en los datos ingresados

### Solución Propuesta

El sistema desarrollado resuelve estos problemas mediante:

#### **Módulo de Motorizados (Lista Doblemente Enlazada)**
- Registro de hasta 6 motorizados activos simultáneamente
- Control de estado (Activo/Inactivo)
- Validación de IDs y placas únicas
- Navegación bidireccional en la lista
- Eliminación segura (solo si no hay paquetes pendientes)

#### **Módulo de Paquetes (Lista Simplemente Enlazada)**
- Código auto-incremental para cada paquete
- Asignación automática al motorizado con menos carga
- Priorización de paquetes urgentes (al inicio de la cola)
- Paquetes normales al final de la cola
- Validaciones de datos (peso positivo, dirección no vacía)
- Registro automático de fecha y hora

#### **Sistema de Entrega**
- Entrega del primer paquete de cada motorizado activo
- Reporte detallado antes y después de cada entrega
- Actualización automática de las colas

---

## COMENTARIOS DE LOS MÉTODOS MÁS IMPORTANTES

### 1. **Método: `agregarMotorizado()`**

**Ubicación:** `Motorizado.cpp`

```cpp
void nodoMotorizado::agregarMotorizado(int _id, string _nombre, string _placa)
```

**Propósito:** Agregar un nuevo motorizado a la lista doblemente enlazada.

**Lógica implementada:**
1. **Validación de datos vacíos:** Verifica que nombre y placa no estén vacíos
2. **Validación de unicidad:** Comprueba que no exista otro motorizado con el mismo ID o placa
3. **Límite de activos:** Verifica que no haya más de 6 motorizados activos
4. **Inserción al final:** Utiliza navegación hacia adelante para encontrar el último nodo
5. **Enlace bidireccional:** Establece punteros `siguiente` y `anterior` correctamente

**Complejidad temporal:** O(n) donde n es el número de motorizados

**Importancia:** Este método es crítico porque mantiene la integridad de la lista doblemente enlazada y asegura que no se violen las reglas de negocio (máximo 6 activos, unicidad de IDs y placas).

---

### 2. **Método: `agregarPaqueteAMotorizado()`**

**Ubicación:** `Motorizado.cpp`

```cpp
void nodoMotorizado::agregarPaqueteAMotorizado(string _direccion, double _peso, char _tipo)
```

**Propósito:** Crear un paquete y asignarlo al motorizado con menos carga.

**Lógica implementada:**
1. **Validaciones de entrada:**
   - Dirección no vacía
   - Peso positivo
   - Tipo válido (U o N)

2. **Verificación de disponibilidad:** Comprueba que haya motorizados activos

3. **Asignación inteligente:** Utiliza `obtenerMotorizadoConMenosPaquetes()` para encontrar el motorizado óptimo

4. **Creación del paquete:**
   - Incrementa el contador estático
   - Genera código único
   - Registra fecha y hora actual

5. **Inserción según prioridad:**
   - **Urgente (U):** Inserta al INICIO de la lista del motorizado
   - **Normal (N):** Inserta al FINAL de la lista del motorizado

**Complejidad temporal:** O(n*m) donde n = motorizados, m = paquetes por motorizado

**Importancia:** Este es el método más importante del sistema porque implementa la lógica de negocio principal: distribución equitativa y priorización de paquetes urgentes.

---

### 3. **Método: `obtenerMotorizadoConMenosPaquetes()`**

**Ubicación:** `Motorizado.cpp`

```cpp
nodoMotorizado* nodoMotorizado::obtenerMotorizadoConMenosPaquetes()
```

**Propósito:** Encontrar el motorizado activo con la menor cantidad de paquetes asignados.

**Lógica implementada:**
1. Recorre todos los motorizados
2. Para cada motorizado activo, cuenta sus paquetes
3. Mantiene registro del motorizado con menos carga
4. Retorna un puntero al motorizado óptimo

**Algoritmo:**
```
INICIO
  menorCantidad = infinito
  mejorMotorizado = NULL
  
  PARA cada motorizado EN listaMotorizados:
    SI motorizado está activo:
      cantidadPaquetes = contar paquetes del motorizado
      SI cantidadPaquetes < menorCantidad:
        menorCantidad = cantidadPaquetes
        mejorMotorizado = motorizado
      FIN SI
    FIN SI
  FIN PARA
  
  RETORNAR mejorMotorizado
FIN
```

**Complejidad temporal:** O(n*m)

**Importancia:** Implementa el balanceo de carga, asegurando que ningún motorizado quede sobrecargado mientras otros están ociosos.

---

### 4. **Método: `entregarPaquetes()`**

**Ubicación:** `Motorizado.cpp`

```cpp
void nodoMotorizado::entregarPaquetes()
```

**Propósito:** Simular la entrega del primer paquete de cada motorizado activo.

**Lógica implementada:**
1. Recorre todos los motorizados
2. Para cada motorizado activo con paquetes:
   - Cuenta paquetes antes de la entrega
   - Elimina el primer paquete de su cola (FIFO)
   - Muestra información de la entrega
   - Libera la memoria del paquete entregado

**Estructura de datos utilizada:** Cola (Queue) implementada con lista enlazada

**Complejidad temporal:** O(n*m)

**Importancia:** Simula el proceso real de entrega y demuestra el comportamiento FIFO (First In, First Out) de las colas de paquetes, con excepción de los urgentes que se priorizan.

---

### 5. **Método: `eliminarMotorizado()`**

**Ubicación:** `Motorizado.cpp`

```cpp
void nodoMotorizado::eliminarMotorizado(int _id)
```

**Propósito:** Eliminar un motorizado de la lista doblemente enlazada.

**Lógica implementada:**
1. Busca el motorizado por ID
2. Verifica que no tenga paquetes pendientes
3. Actualiza los punteros bidireccionales:
   - Si es el primero: ajusta `listaMotorizados`
   - Si está en medio o al final: ajusta `anterior->siguiente` y `siguiente->anterior`
4. Libera la memoria

**Casos especiales:**
- **Primer nodo:** Actualiza la cabeza de la lista
- **Último nodo:** No tiene `siguiente`, solo ajusta `anterior`
- **Nodo intermedio:** Ajusta ambos punteros

**Complejidad temporal:** O(n)

**Importancia:** Demuestra el manejo correcto de eliminación en listas doblemente enlazadas, evitando fugas de memoria y manteniendo la integridad de los enlaces.

---

### 6. **Función auxiliar: `obtenerFechaHoraActual()`**

**Ubicación:** `Paquete.cpp`

```cpp
string obtenerFechaHoraActual()
```

**Propósito:** Generar una marca de tiempo para cada paquete.

**Lógica implementada:**
1. Obtiene el tiempo actual del sistema usando `time(0)`
2. Convierte a tiempo local con `localtime()`
3. Formatea la fecha en formato DD/MM/YYYY HH:MM:SS
4. Usa `stringstream` para construir la cadena
5. Aplica `setfill` y `setw` para formato consistente

**Salida ejemplo:** `03/10/2025 19:17:44`

**Importancia:** Proporciona trazabilidad temporal de cada paquete, permitiendo auditorías y análisis de tiempos de entrega.

---

### 7. **Método: `eliminarPaquete()`**

**Ubicación:** `Motorizado.cpp`

```cpp
void nodoMotorizado::eliminarPaquete(int _codigo)
```

**Propósito:** Eliminar un paquete específico sin importar a qué motorizado esté asignado.

**Lógica implementada:**
1. Recorre todos los motorizados
2. Para cada motorizado, recorre su lista de paquetes
3. Busca el paquete con el código especificado
4. Al encontrarlo:
   - Ajusta los punteros de la lista
   - Libera la memoria
   - Informa del éxito

**Complejidad temporal:** O(n*m) en el peor caso

**Importancia:** Permite la cancelación de paquetes independientemente de su ubicación en el sistema, implementando búsqueda en múltiples listas.

---

## MANUAL DE USUARIO

### **Requisitos del Sistema**
- Sistema operativo: Windows, Linux o macOS
- Compilador: g++ (compatible con C++11 o superior)
- Memoria RAM: Mínimo 512 MB

### **Instalación y Compilación**

1. **Descargar los archivos del proyecto:**
   - `main.cpp`
   - `Paquete.h`
   - `Paquete.cpp`
   - `Motorizado.h`
   - `Motorizado.cpp`

2. **Compilar el proyecto:**
   ```bash
   g++ -o EnvioExpress main.cpp Paquete.cpp Motorizado.cpp
   ```

3. **Ejecutar el programa:**
   ```bash
   ./EnvioExpress
   ```

---

### **Uso del Sistema**

#### **Menú Principal**

Al iniciar el programa, se muestra el siguiente menú:

```
╔════════════════════════════════════════════════════════════════╗
║          SISTEMA DE GESTIÓN DE PAQUETERÍA - EnvíoExpress      ║
╚════════════════════════════════════════════════════════════════╝
┌────────────────────────────────────────────────────────────────┐
│                    MÓDULO DE MOTORIZADOS                       │
├────────────────────────────────────────────────────────────────┤
│ 1. Agregar Motorizado                                          │
│ 2. Mostrar Motorizados                                         │
│ 3. Modificar Motorizado                                        │
│ 4. Eliminar Motorizado                                         │
├────────────────────────────────────────────────────────────────┤
│                     MÓDULO DE PAQUETES                         │
├────────────────────────────────────────────────────────────────┤
│ 5. Agregar Paquete                                             │
│ 6. Mostrar Paquetes de un Motorizado                           │
│ 7. Eliminar Paquete por Código                                 │
│ 8. Entregar Paquetes                                           │
├────────────────────────────────────────────────────────────────┤
│ 0. Salir                                                       │
└────────────────────────────────────────────────────────────────┘
```

---

### **Funciones Detalladas**

#### **1. Agregar Motorizado**

**Paso a paso:**
1. Seleccione la opción `1`
2. Ingrese el ID del motorizado (número entero)
3. Ingrese el nombre del motorizado
4. Ingrese la placa del vehículo

**Ejemplo:**
```
ID del motorizado: 101
Nombre: Juan Pérez
Placa: ABC-123

✅ Motorizado agregado exitosamente con ID: 101
```

**Validaciones:**
- El ID debe ser único
- La placa debe ser única
- Nombre y placa no pueden estar vacíos
- Máximo 6 motorizados activos

**Mensajes de error posibles:**
- `❌ ERROR: Ya existe un motorizado con ID 101.`
- `❌ ERROR: Ya existe un motorizado con placa ABC-123.`
- `❌ ERROR: Ya hay 6 motorizados activos. No se pueden agregar más.`

---

#### **2. Mostrar Motorizados**

**Función:** Muestra todos los motorizados registrados con su información completa.

**Ejemplo de salida:**
```
╔════════════════════════════════════════════════════════════════════════╗
║                    LISTA DE MOTORIZADOS REGISTRADOS                    ║
╚════════════════════════════════════════════════════════════════════════╝

┌────────────────────────────────────────────────────────────────────┐
│ ID:             101
│ Nombre:         Juan Pérez
│ Placa:          ABC-123
│ Estado:         ✅ ACTIVO
│ Paquetes:       3
└────────────────────────────────────────────────────────────────────┘
```

---

#### **3. Modificar Motorizado**

**Opciones:**
1. Modificar nombre
2. Cambiar estado (Activo/Inactivo)

**Ejemplo:**
```
Ingrese el ID del motorizado a modificar: 101

--- MODIFICAR MOTORIZADO ---
1. Modificar Nombre
2. Cambiar Estado (Activo/Inactivo)
Opción: 2

✅ Estado cambiado a: INACTIVO
⚠️ Este motorizado ya no recibirá nuevos paquetes.
```

**Restricciones:**
- No se puede modificar el ID ni la placa
- Si se cambia a inactivo, no se le asignarán más paquetes

---

#### **4. Eliminar Motorizado**

**Función:** Elimina un motorizado del sistema.

**Ejemplo:**
```
Ingrese el ID del motorizado a eliminar: 102

✅ Motorizado eliminado exitosamente.
```

**Restricciones:**
- Solo se puede eliminar si NO tiene paquetes pendientes
- Si tiene paquetes, primero deben ser entregados o reasignados

**Mensaje de error:**
```
❌ ERROR: No se puede eliminar. El motorizado tiene paquetes pendientes.
```

---

#### **5. Agregar Paquete**

**Paso a paso:**
1. Seleccione la opción `5`
2. Ingrese la dirección de destino
3. Ingrese el peso en kilogramos
4. Seleccione el tipo: `U` (Urgente) o `N` (Normal)

**Ejemplo - Paquete Urgente:**
```
Dirección de destino: Calle 5, Avenida 10, Casa 25
Peso (kg): 2.5
Tipo (U=Urgente / N=Normal): U

✅ Paquete URGENTE #1001 asignado a Juan Pérez (ID: 101) al INICIO de su cola.
```

**Ejemplo - Paquete Normal:**
```
Dirección de destino: Barrio Los Ángeles, Casa 42
Peso (kg): 1.8
Tipo (U=Urgente / N=Normal): N

✅ Paquete NORMAL #1002 asignado a María González (ID: 102) al FINAL de su cola.
```

**Validaciones:**
- Dirección no puede estar vacía
- Peso debe ser mayor que 0
- Tipo solo puede ser U o N
- Debe haber al menos un motorizado activo

**Asignación automática:**
- El sistema asigna el paquete al motorizado activo con MENOS paquetes
- Paquetes urgentes se colocan al INICIO de la cola
- Paquetes normales se colocan al FINAL de la cola

---

#### **6. Mostrar Paquetes de un Motorizado**

**Función:** Muestra todos los paquetes asignados a un motorizado específico.

**Ejemplo:**
```
Ingrese el ID del motorizado: 101

╔════════════════════════════════════════════════════════════════════════╗
║  Paquetes de: Juan Pérez (ID: 101)
╚════════════════════════════════════════════════════════════════════════╝

┌────────────────────────────────────────────────────────────────────┐
│ Paquete #1
├────────────────────────────────────────────────────────────────────┤
│ Código:         1001
│ Dirección:      Calle 5, Avenida 10, Casa 25
│ Peso:           2.50 kg
│ Tipo:           URGENTE 🔴
│ Fecha y Hora:   03/10/2025 19:17:44
└────────────────────────────────────────────────────────────────────┘
```

---

#### **7. Eliminar Paquete por Código**

**Función:** Elimina un paquete específico del sistema.

**Ejemplo:**
```
Ingrese el código del paquete a eliminar: 1001

✅ Paquete #1001 eliminado del motorizado Juan Pérez (ID: 101).
```

**Características:**
- Busca el paquete en TODOS los motorizados
- No requiere saber a qué motorizado está asignado
- Actualiza automáticamente la cola del motorizado

---

#### **8. Entregar Paquetes**

**Función:** Cada motorizado activo entrega su primer paquete (el más antiguo o urgente).

**Ejemplo:**
```
╔════════════════════════════════════════════════════════════════════════╗
║                        PROCESO DE ENTREGA                              ║
╚════════════════════════════════════════════════════════════════════════╝

🏍️ Motorizado: Juan Pérez (ID: 101)
   📦 Entregó paquete #1001
   📍 Dirección: Calle 5, Avenida 10, Casa 25
   📊 Paquetes antes: 3 → Después: 2

🏍️ Motorizado: María González (ID: 102)
   📦 Entregó paquete #1003
   📍 Dirección: Barrio Los Ángeles, Casa 42
   📊 Paquetes antes: 2 → Después: 1
```

**Comportamiento:**
- Solo motorizados ACTIVOS entregan paquetes
- Se entrega el PRIMER paquete de la cola (FIFO)
- Muestra reporte antes y después de cada entrega
- Si un motorizado no tiene paquetes, no aparece en el reporte

---

### **Casos de Uso Completos**

#### **Escenario 1: Configuración Inicial**

**Objetivo:** Registrar motorizados y agregar paquetes.

```
1. Agregar Motorizado
   ID: 101, Nombre: "Juan Pérez", Placa: "ABC-123"
   
2. Agregar Motorizado
   ID: 102, Nombre: "María González", Placa: "XYZ-789"
   
3. Agregar Paquete
   Dirección: "Calle Principal #45"
   Peso: 2.5 kg
   Tipo: U (Urgente)
   → Asignado a Juan Pérez (menos paquetes)
   
4. Agregar Paquete
   Dirección: "Avenida Central #88"
   Peso: 1.2 kg
   Tipo: N (Normal)
   → Asignado a María González (menos paquetes)
```

---

#### **Escenario 2: Priorización de Paquetes Urgentes**

**Situación:** Un motorizado tiene 2 paquetes normales, llega uno urgente.

```
Estado inicial de Juan Pérez:
  [Normal #1001] → [Normal #1002] → NULL

Agregar Paquete Urgente:
  Dirección: "Hospital Nacional"
  Peso: 0.5 kg
  Tipo: U

Estado final de Juan Pérez:
  [Urgente #1003] → [Normal #1001] → [Normal #1002] → NULL

Al entregar, se entrega primero el #1003 (Urgente)
```

---

#### **Escenario 3: Balanceo de Carga**

**Situación:** 3 motorizados con diferente carga de trabajo.

```
Motorizado 101 (Juan):    3 paquetes
Motorizado 102 (María):   1 paquete
Motorizado 103 (Carlos):  2 paquetes

Nuevo paquete:
  → Se asigna a María (ID: 102) porque tiene MENOS paquetes

Resultado:
Motorizado 101 (Juan):    3 paquetes
Motorizado 102 (María):   2 paquetes ← Actualizado
Motorizado 103 (Carlos):  2 paquetes
```

---

#### **Escenario 4: Motorizado Inactivo**

**Situación:** Cambiar estado de un motorizado a inactivo.

```
1. Modificar Motorizado ID 102
2. Seleccionar opción: Cambiar Estado
3. Estado cambia a INACTIVO

Comportamiento:
- Ya no recibe nuevos paquetes
- Conserva los paquetes actuales
- Puede entregar sus paquetes existentes
- No aparece en la asignación automática
```

---

### **Consejos de Uso**

1. **Siempre agregue motorizados antes de paquetes**
   - El sistema requiere al menos un motorizado activo para asignar paquetes

2. **Use códigos de paquete para rastreo**
   - Cada paquete tiene un código único auto-generado
   - Use este código para eliminar o rastrear paquetes

3. **Revise la carga antes de cambiar estados**
   - Antes de desactivar un motorizado, verifique sus paquetes pendientes

4. **Use la opción "Mostrar" frecuentemente**
   - Verifique el estado actual antes de tomar decisiones

5. **Paquetes urgentes siempre tienen prioridad**
   - Se colocan al inicio y se entregan primero

---

## LIMITACIONES DEL PROYECTO

### **1. Limitaciones Técnicas**

#### **1.1 Persistencia de Datos**
- **Limitación:** Los datos NO se guardan al cerrar el programa
- **Impacto:** Toda la información se pierde al salir
- **Solución futura:** Implementar almacenamiento en archivos (`.txt`, `.dat` o `.bin`)

#### **1.2 Máximo de Motorizados**
- **Limitación:** Solo 6 motorizados activos simultáneamente
- **Razón:** Requisito del proyecto (limitación de negocio)
- **Impacto:** En una empresa real esto podría ser insuficiente

#### **1.3 Validación de Placas**
- **Limitación:** No valida formato específico de placas (ej: ABC-123)
- **Validación actual:** Solo verifica unicidad
- **Mejora futura:** Implementar expresiones regulares para formatos válidos

#### **1.4 Fechas Manuales**
- **Limitación:** No permite ingresar fechas de entrega programadas
- **Funcionalidad actual:** Solo registra fecha/hora de ingreso
- **Mejora futura:** Agregar campo de "fecha de entrega esperada"

---

### **2. Limitaciones de Usabilidad**

#### **2.1 Interfaz de Consola**
- **Limitación:** Solo funciona en consola (CLI)
- **Impacto:** Menos intuitivo para usuarios no técnicos
- **Mejora futura:** Desarrollar interfaz gráfica (GUI) con Qt o similar

#### **2.2 Sin Sistema de Búsqueda Avanzada**
- **Limitación:** No se puede buscar por dirección, fecha, peso, etc.
- **Búsqueda actual:** Solo por ID (motorizados) o código (paquetes)
- **Mejora futura:** Implementar filtros múltiples

#### **2.3 Reportes Limitados**
- **Limitación:** No genera reportes estadísticos
- **Estadísticas faltantes:**
  - Total de paquetes entregados por día
  - Motorizado más eficiente
  - Peso total transportado
  - Tiempo promedio de entrega

---

### **3. Limitaciones Funcionales**

#### **3.1 Reasignación Manual**
- **Limitación:** No permite reasignar paquetes entre motorizados
- **Escenario problemático:** Si un motorizado se enferma, hay que entregar o eliminar sus paquetes
- **Mejora futura:** Implementar método `reasignarPaquete(codigoPaquete, nuevoMotorizadoID)`

#### **3.2 Sin Historial de Entregas**
- **Limitación:** Los paquetes entregados se eliminan sin registro
- **Impacto:** No hay trazabilidad post-entrega
- **Mejora futura:** Crear estructura `HistorialEntregas` con lista de paquetes entregados

#### **3.3 Sin Notificaciones**
- **Limitación:** No notifica cuando un motorizado está sobrecargado
- **Mejora futura:** Alertas cuando un motorizado tiene >10 paquetes

#### **3.4 Edición de Paquetes**
- **Limitación:** No se puede modificar un paquete después de crearlo
- **Operaciones faltantes:** Cambiar dirección, peso o prioridad
- **Solución actual:** Eliminar y volver a crear

---

### **4. Limitaciones de Seguridad**

#### **4.1 Sin Autenticación**
- **Limitación:** Cualquier persona puede modificar datos
- **Riesgo:** En un entorno real, esto es un problema de seguridad
- **Mejora futura:** Sistema de usuarios con roles (admin, operador, visualizador)

#### **4.2 Sin Respaldo (Backup)**
- **Limitación:** No hay mecanismo de respaldo automático
- **Riesgo:** Pérdida total de datos si hay un error crítico
- **Mejora futura:** Auto-guardado cada N operaciones

---

### **5. Limitaciones de Rendimiento**

#### **5.1 Búsqueda Lineal**
- **Limitación:** Búsquedas con complejidad O(n)
- **Impacto:** Con muchos datos, las búsquedas son lentas
- **Mejora futura:** Implementar tabla hash o árbol binario de búsqueda

#### **5.2 Conteo de Paquetes Ineficiente**
- **Limitación:** `contarPaquetesMotorizado()` recorre toda la lista cada vez
- **Solución actual:** O(m) por cada consulta
- **Mejora futura:** Mantener un atributo `cantidadPaquetes` actualizado

---

### **6. Limitaciones de Validación**

#### **6.1 Pesos Sin Límite Superior**
- **Limitación:** Acepta cualquier peso >0
- **Problema:** Un motorizado podría tener 1000 kg asignados
- **Mejora futura:** Validar peso máximo por paquete y carga máxima por motorizado

#### **6.2 Direcciones Sin Formato**
- **Limitación:** Acepta cualquier texto como dirección
- **Problema:** Inconsistencias en el formato
- **Mejora futura:** Validar campos (provincia, cantón, distrito, señas)

---

### **7. Limitaciones de Escalabilidad**

#### **7.1 Gestión de Memoria**
- **Limitación:** Toda la información en RAM
- **Problema:** Con miles de paquetes, podría consumir mucha memoria
- **Solución futura:** Base de datos (SQLite, MySQL)

#### **7.2 Sin Multi-threading**
- **Limitación:** Operaciones síncronas (una a la vez)
- **Escenario:** En un sistema real, múltiples operadores trabajarían simultáneamente
- **Mejora futura:** Implementar concurrencia con mutex/semáforos

---

### **8. Limitaciones de Integración**

#### **8.1 Sin API REST**
- **Limitación:** No se puede integrar con otros sistemas
- **Casos de uso perdidos:**
  - Aplicación móvil para motorizados
  - Portal web para clientes
  - Integración con GPS

#### **8.2 Sin Exportación de Datos**
- **Limitación:** No exporta a CSV, JSON o PDF
- **Impacto:** Dificulta análisis externo con Excel u otras herramientas

---

### **Resumen de Limitaciones Críticas**

| Limitación | Severidad | Prioridad de Mejora |
|------------|-----------|---------------------|
| Sin persistencia de datos | 🔴 Alta | 1 |
| Sin historial de entregas | 🔴 Alta | 2 |
| Sin reasignación de paquetes | 🟡 Media | 3 |
| Interfaz solo CLI | 🟡 Media | 4 |
| Sin búsqueda avanzada | 🟢 Baja | 5 |
| Sin sistema de usuarios | 🟢 Baja | 6 |

---

## CONCLUSIÓN

El desarrollo del **Sistema de Gestión de Paquetería "EnvíoExpress"** ha permitido aplicar de manera práctica los conceptos fundamentales de estructuras de datos estudiados en el curso, específicamente:

### **Logros Alcanzados:**

1. **Implementación exitosa de estructuras de datos manuales:**
   - Lista doblemente enlazada para motorizados
   - Lista simplemente enlazada para paquetes
   - Sin uso de librerías STL (std::list, std::vector, etc.)

2. **Aplicación de Programación Orientada a Objetos:**
   - Clases bien definidas (Motorizado, Paquete)
   - Encapsulamiento de datos y métodos
   - Uso de punteros y gestión manual de memoria

3. **Solución efectiva al problema planteado:**
   - Asignación automática y balanceada de paquetes
   - Priorización de entregas urgentes
   - Validaciones robustas de datos

4. **Comprensión profunda de:**
   - Manejo de punteros y memoria dinámica
   - Complejidad algorítmica (O(n), O(n*m))
   - Ventajas y desventajas de diferentes estructuras

### **Aprendizajes Clave:**

1. **Listas Doblemente Enlazadas:**
   - Permiten navegación bidireccional eficiente
   - Facilitan operaciones de inserción y eliminación
   - Requieren cuidado especial al mantener ambos punteros

2. **Listas Simplemente Enlazadas:**
   - Más eficientes en memoria que las dobles
   - Ideales para implementar colas (FIFO)
   - La inserción al final requiere recorrer toda la lista

3. **Gestión de Memoria:**
   - Importancia de liberar memoria con `delete`
   - Evitar fugas de memoria (memory leaks)
   - Manejo correcto de punteros NULL

4. **Validación de Datos:**
   - Crucial para la integridad del sistema
   - Mejora la experiencia del usuario
   - Previene estados inconsistentes

### **Competencias Desarrolladas:**

✅ Análisis y diseño de soluciones con estructuras de datos  
✅ Implementación de algoritmos de búsqueda y ordenamiento  
✅ Depuración de código con punteros  
✅ Documentación técnica de proyectos  
✅ Pensamiento lógico y resolución de problemas

### **Reflexión Final:**

Este proyecto ha demostrado que las estructuras de datos fundamentales, aunque parezcan simples, son la base de sistemas complejos. La experiencia de implementar manualmente estas estructuras (en lugar de usar librerías) proporciona una comprensión profunda que será invaluable en el desarrollo profesional futuro.

El sistema desarrollado es funcional y cumple con todos los requisitos del proyecto, siendo una base sólida que puede extenderse con las mejoras mencionadas en la sección de limitaciones.

---

## COMENTARIOS ADICIONALES

### **Desafíos Encontrados Durante el Desarrollo:**

1. **Manejo de la Lista Doblemente Enlazada:**
   - **Desafío:** Mantener sincronizados los punteros `siguiente` y `anterior`
   - **Solución:** Dibujar diagramas en papel para visualizar los cambios
   - **Aprendizaje:** La importancia de actualizar ambos punteros en cada operación

2. **Asignación Automática de Paquetes:**
   - **Desafío:** Encontrar el motorizado con menos carga eficientemente
   - **Solución:** Método auxiliar que cuenta paquetes para cada motorizado
   - **Aprendizaje:** A veces la solución más simple (O(n*m)) es suficiente

3. **Priorización de Paquetes Urgentes:**
   - **Desafío:** Insertar al inicio vs. al final según el tipo
   - **Solución:** Condicional que determina el punto de inserción
   - **Aprendizaje:** Las listas enlazadas permiten inserciones flexibles

4. **Generación de Fecha/Hora:**
   - **Desafío:** Formato consistente de timestamps
   - **Solución:** Uso de `<ctime>` y `stringstream` con `setfill`/`setw`
   - **Aprendizaje:** Importancia del formato en sistemas de información

### **Decisiones de Diseño Importantes:**

1. **¿Por qué lista doblemente enlazada para motorizados?**
   - Permite navegación hacia adelante y atrás
   - Facilita futuras implementaciones (ej: ordenamiento por placa)
   - Eliminación más eficiente cuando se tiene un puntero al nodo

2. **¿Por qué lista simple para paquetes?**
   - Menor uso de memoria
   - Suficiente para comportamiento de cola (FIFO)
   - Más simple de mantener

3. **¿Por qué asignación automática?**
   - Evita errores humanos en la distribución
   - Garantiza balanceo de carga
   - Simplifica la interfaz de usuario

### **Extensiones Futuras Planeadas:**

1. **Versión 2.0 - Persistencia:**
   ```cpp
   void guardarEnArchivo(string nombreArchivo);
   void cargarDeArchivo(string nombreArchivo);
   ```

2. **Versión 3.0 - Historial:**
   ```cpp
   class HistorialEntregas {
       nodoPaquete *paquetesEntregados;
       void agregarEntrega(nodoPaquete *paquete, nodoMotorizado *motorizado);
       void mostrarHistorial();
   };
   ```

3. **Versión 4.0 - Rutas Optimizadas:**
   - Algoritmo para calcular rutas óptimas
   - Agrupación de paquetes por zona geográfica
   - Estimación de tiempos de entrega

### **Recursos Utilizados:**

- **Documentación:** cplusplus.com, cppreference.com
- **Herramientas:** Visual Studio Code, g++ compiler, gdb debugger
- **Diagramas:** Draw.io para estructuras de datos
- **Control de versiones:** Git (repositorio local)

### **Tiempo de Desarrollo:**

| Fase | Tiempo Estimado |
|------|----------------|
| Análisis y diseño | 4 horas |
| Implementación de Motorizado | 6 horas |
| Implementación de Paquete | 4 horas |
| Integración y pruebas | 5 horas |
| Documentación | 6 horas |
| **TOTAL** | **25 horas** |

### **Agradecimientos:**

A mi profesor Msc. Walter León Chavarría por la guía durante el desarrollo del proyecto y a mis compañeros de clase por las discusiones técnicas que ayudaron a mejorar el diseño del sistema.

---

**Elaborado por:**  
Brayan Pérez Balladares  
Estudiante de Ingeniería en Sistemas de Información  
Universidad Nacional - Sede Regional Chorotega, Campus Nicoya

**Fecha:** 03 de octubre, 2025

---

## ANEXOS

### **Anexo A: Diagrama de Clases**

```
┌─────────────────────────┐
│      Motorizado         │
├─────────────────────────┤
│ - id: int               │
│ - nombre: string        │
│ - placa: string         │
│ - activo: bool          │
│ - inicioPaquetes: Paquete* │
│ - siguiente: Motorizado*│
│ - anterior: Motorizado* │
├─────────────────────────┤
│ + agregarMotorizado()   │
│ + mostrarMotorizados()  │
│ + modificarMotorizado() │
│ + eliminarMotorizado()  │
│ + agregarPaquete()      │
│ + entregarPaquetes()    │
└─────────────────────────┘
           │
           │ 1..*
           ▼
┌─────────────────────────┐
│       Paquete           │
├─────────────────────────┤
│ - codigo: int           │
│ - direccion: string     │
│ - fechaHora: string     │
│ - peso: double          │
│ - tipo: char            │
│ - siguiente: Paquete*   │
├─────────────────────────┤
│ + obtenerFechaHora()    │
│ + incrementarContador() │
└─────────────────────────┘
```

### **Anexo B: Ejemplo de Ejecución Completa**

```
# Sesión de ejemplo

1. Agregar Motorizado (ID: 101, Nombre: "Juan Pérez", Placa: "ABC-123")
2. Agregar Motorizado (ID: 102, Nombre: "María González", Placa: "XYZ-789")
3. Mostrar Motorizados
   → Muestra 2 motorizados, ambos con 0 paquetes
4. Agregar Paquete (Dir: "Hospital", Peso: 0.5, Tipo: U)
   → Asignado a Juan (menos paquetes)
5. Agregar Paquete (Dir: "Centro Comercial", Peso: 2.3, Tipo: N)
   → Asignado a María (menos paquetes)
6. Agregar Paquete (Dir: "Universidad", Peso: 1.2, Tipo: U)
   → Asignado a María (menos paquetes)
7. Mostrar Paquetes de Motorizado 102
   → [Urgente #1003: Universidad] → [Normal #1002: Centro Comercial]
8. Entregar Paquetes
   → Juan entrega #1001
   → María entrega #1003 (urgente primero)
9. Mostrar Motorizados
   → Juan: 0 paquetes
   → María: 1 paquete
```

### **Anexo C: Códigos de Error**

| Código | Mensaje | Causa |
|--------|---------|-------|
| E001 | ERROR: El nombre no puede estar vacío | Campo nombre vacío |
| E002 | ERROR: La placa no puede estar vacía | Campo placa vacío |
| E003 | ERROR: Ya existe un motorizado con ID X | ID duplicado |
| E004 | ERROR: Ya existe un motorizado con placa X | Placa duplicada |
| E005 | ERROR: Ya hay 6 motorizados activos | Límite alcanzado |
| E006 | ERROR: La dirección no puede estar vacía | Dirección vacía |
| E007 | ERROR: El peso debe ser positivo | Peso <= 0 |
| E008 | ERROR: Tipo debe ser U o N | Tipo inválido |
| E009 | ERROR: No hay motorizados activos | Sin motorizados |
| E010 | ERROR: Motorizado tiene paquetes pendientes | Intento de eliminar |

---

**FIN DEL DOCUMENTO**
