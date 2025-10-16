// Práctica: Sistema de Administración de Estacionamiento
// Explicación general: este archivo define estructuras y funciones para gestionar secciones
// del estacionamiento y listas enlazadas de vehículos en cada sección.

#include <iostream> // Cabecera para entrada/salida (cout, endl)
#include <string>   // Cabecera para el tipo std::string
using namespace std; // Usar el espacio de nombres std para evitar escribir std:: en cada uso

// Estructura que representa un vehículo: tiene una patente y un tipo
struct Vehiculo
{
    string patente;      // Patente / matrícula del vehículo
    int tipoVehiculo;    // Código del tipo de vehículo (ejemplo: 10, 11, ...)
};

// Nodo de la lista enlazada que contiene un Vehiculo y un puntero al siguiente nodo
struct NodoVehiculo
{
    Vehiculo vehiculo;   // Datos del vehículo almacenado en este nodo
    NodoVehiculo *sgte;   // Puntero al siguiente nodo en la lista
};

// Una sección del estacionamiento contiene la lista de vehículos y el tipo que maneja
struct Seccion
{
    NodoVehiculo *vehiculos; // Puntero a la cabeza de la lista de vehículos en esta sección
    int tipoVehiculo;        // Código que identifica el tipo de vehículos de la sección
};

Seccion secciones[5]; // Arreglo global de 5 secciones (cada una para un tipo diferente)

// Inicializa todas las secciones del estacionamiento asegurando que estén sin vehículos.
void inicializarEstacionamiento(Seccion secciones[], int cantidad)
{
    for (int i = 0; i < cantidad; ++i) // Recorre 'cantidad' secciones
    {
        secciones[i].vehiculos = nullptr; // Marca la lista como vacía (sin nodos)
        secciones[i].tipoVehiculo = 10 + i; // Asigna códigos 10,11,12,13,14 a las secciones
    }
}

// Crea un nuevo nodo con los datos del vehículo y lo añade al final de la lista dada
NodoVehiculo *agregarNodo(NodoVehiculo *vehiculos, string patente, int tipoVehiculo)
{
    NodoVehiculo *nuevoVehiculo = new NodoVehiculo; // Reserva memoria para un nuevo nodo
    nuevoVehiculo->vehiculo.patente = patente;      // Asigna la patente al campo correspondiente
    nuevoVehiculo->vehiculo.tipoVehiculo = tipoVehiculo; // Asigna el tipo al vehículo
    nuevoVehiculo->sgte = nullptr;                  // Nuevo nodo no apunta a ningún siguiente

    if (vehiculos == nullptr) // Si la lista está vacía (no hay cabeza)
    {
        vehiculos = nuevoVehiculo; // El nuevo nodo se convierte en la cabeza de la lista
    }
    else
    {
        NodoVehiculo *actual = vehiculos; // Empezar desde la cabeza
        while (actual->sgte != nullptr)   // Avanzar hasta el último nodo
        {
            actual = actual->sgte;        // Mover al siguiente nodo
        }
        actual->sgte = nuevoVehiculo;    // Enlazar el nuevo nodo al final de la lista
    }
    return vehiculos; // Devolver la (posible) nueva cabeza de la lista
}

// Registra un vehículo en la sección correspondiente según su tipo
void registrarVehiculo(Seccion secciones[], string patente, int tipoVehiculo)
{
    // Itera por las secciones locales (aquí se usa 5 como número fijo)
    for (int i = 0; i < 5; ++i)
    {
        if (secciones[i].tipoVehiculo == tipoVehiculo) // Si la sección maneja este tipo
        {
            // Añade el vehículo a la lista de esa sección
            secciones[i].vehiculos = agregarNodo(secciones[i].vehiculos, patente, tipoVehiculo);
            return; // Termina la función después de registrar
        }
    }
    // Si no se encontró la sección adecuada, informamos por consola
    cout << "No se encontró la sección para el tipo de vehículo proporcionado." << endl;
}

// Devuelve la cantidad de vehículos almacenados en la sección correspondiente
int cantidadVehiculos(Seccion secciones[], int tipoVehiculo, int cantidadSecciones)
{
    int contador = 0; // Contador de nodos encontrados
    for (int i = 0; i < cantidadSecciones; ++i) // Recorre las secciones proporcionadas
    {
        if (secciones[i].tipoVehiculo == tipoVehiculo) // Si encontramos la sección correcta
        {
            NodoVehiculo *actual = secciones[i].vehiculos; // Apuntador para recorrer la lista
            while (actual != nullptr) // Recorre hasta el final de la lista
            {
                contador++;            // Incrementa el contador por cada vehículo
                actual = actual->sgte; // Avanza al siguiente nodo
            }
            break; // Rompe después de contar la sección encontrada
        }
    }
    return contador; // Retorna la cantidad de vehículos contados
}

int main()
{
    // Ejemplo de uso:
    inicializarEstacionamiento(secciones, 5);                    // Inicializa las 5 secciones
    registrarVehiculo(secciones, "AAA111", 10); // Registro: patente "AAA111" en tipo 10
    registrarVehiculo(secciones, "AAA111", 11); // Registro: misma patente en tipo 11 (posible duplicado)
    registrarVehiculo(secciones, "BBB222", 11); // Registro: nueva patente en tipo 11
    cout << "Cantidad de autos: " << cantidadVehiculos(secciones, 10, 5) << endl; // Muestra cantidad para tipo 10
    cout << "Cantidad de motos: " << cantidadVehiculos(secciones, 11, 5) << endl; // Muestra cantidad para tipo 11
    return 0; // Fin del programa
}