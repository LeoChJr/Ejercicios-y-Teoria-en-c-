//  Práctica 7 puntos)
//  Una empresa de gimnasios quiere desarrollar un 
// sistema para gestionar las actividades de sus clientes 
// y entrenadores. El sistema deberá asignar a cada 
// cliente una serie de rutinas de ejercicio. Por cada 
// rutina, se conoce el nivel de intensidad 1..100, el tipo 
// de ejercicio (string), y el tiempo estimado en minutos 
// (int).
//  La empresa te proporciona un archivo donde está la 
// información de cada cliente. La información de los 
// clientes tiene el siguiente formato:
//  ID Cliente (int)
//  DNI (int)
//  Nombre (char[200])
//  Nuestro sistema debe poder asignarle una nueva 
// rutina a un cliente. Cada cliente debe ejecutar siempre 
// primero la última rutina asignada. Y luego la anteúltima 
// y así sucesivamente. 
// Debes encargarte de desarrollar las siguientes 
// funcionalidades:
//   Declarar las estructuras necesarias para el 
// sistema 1 punto)
//   Leer el archivo de clientes y almacenar su 
// información en la estructura elegida 2 puntos)
//   Registrar una nueva rutina a un cliente. Crea una 
// función que reciba por parámetro una rutina 
// armada y un id de cliente al cual se asignará la 
// rutina. El sistema debe registrar la rutina al cliente 
// correspondiente en la estructura creada en el 
// punto 2.  2 puntos)
//   Mostrar el DNI del cliente cuya próxima rutina 
// tenga el nivel de intensidad más alto entre todas 
// las pendientes. 2 puntos)
//  //Pueden dar por hecho que existen las siguientes funciones: El Nodo es a modo ilustrativo, puede ser de los 
// struct que cada uno genere)
//  void push(Nodo*& pila, int valor);
//  int pop(Nodo*& pila);
//  void encolar(Nodo*& frente, Nodo*& final, int valor);
//  int desencolar(Nodo*& frente, Nodo*& final);
//  Nodo* addElementoLista(Nodo* inicio, int valor);
//  Cliente dameSiguienteRegistroDelArchivo(); // Devuelve un cliente del archivo mientras el mismo exista, sino 
// devuelve un Cliente que tiene id igual a 0. 
// bool archivoIsEmpty(); // Devuelve si el archivo tiene más registros pendientes o no.


#include <iostream>
#include <string>
using namespace std;

//1. Declarar las estructuras necesarias para el sistema
struct Cliente{
    int id;
    int dni;
    char nombre[200];
};

struct Rutina{
    int intensidad; // 1..100
    string tipoEjercicio;
    int tiempoEstimado; // en minutos
};

struct NodoRutina{
    Rutina rutina;
    NodoRutina* siguiente;
};

struct NodoCliente{
    ClienteConRutinas clienteConRutinas;
    NodoCliente* siguiente;
};

struct ClienteConRutinas{   
    Cliente cliente;
    NodoRutina* pilaRutinas; // Puntero al tope de la pila de rutinas
};


//2. Leer el archivo de clientes y almacenar su información en la estructura elegida

NodoCliente* leerArchivoDeClientes(){
    NodoCliente* listaClientes = nullptr; // Inicializa la lista de clientes como vacía
    while(!archivoIsEmpty()){
        Cliente cliente = dameSiguienteRegistroDelArchivo();
        NodoCliente* nuevoNodo = new NodoCliente;
        nuevoNodo->clienteConRutinas.cliente = cliente;
        nuevoNodo->clienteConRutinas.pilaRutinas = nullptr; // Inicializa la pila de rutinas como vacía
        nuevoNodo->siguiente = listaClientes; // Inserta al inicio de la lista
        listaClientes = nuevoNodo; // Actualiza la cabeza de la lista
    }
    return listaClientes; // Retorna la lista completa de clientes
}

bool archivoIsEmpty(){
    // Implementación ficticia para ilustrar
    return true; // Cambiar según la lógica real de lectura de archivo
}

Cliente dameSiguienteRegistroDelArchivo(){
    // Implementación ficticia para ilustrar
    Cliente cliente;
    cliente.id = 0; // Cambiar según la lógica real de lectura de archivo
    return cliente;
}

//3. Registrar una nueva rutina a un cliente
void registrarNuevaRutina(NodoCliente* listaClientes, int idCliente, Rutina nuevaRutina){
    NodoCliente* actual = listaClientes;
    while(actual != nullptr){
        if(actual->clienteConRutinas.cliente.id == idCliente){
            // Encontró el cliente, agregar la nueva rutina a su pila
            NodoRutina* nuevoNodoRutina = new NodoRutina;
            nuevoNodoRutina->rutina = nuevaRutina;
            nuevoNodoRutina->siguiente = actual->clienteConRutinas.pilaRutinas; // Apunta al tope actual
            actual->clienteConRutinas.pilaRutinas = nuevoNodoRutina; // Nuevo nodo es el nuevo tope
            return; // Rutina registrada, salir de la función
        }
        actual = actual->siguiente; // Avanza al siguiente cliente
    }
    // Si llega aquí, el cliente con idCliente no fue encontrado
}

//4. Mostrar el DNI del cliente cuya próxima rutina tenga el nivel de intensidad más alto entre todas las pendientes
int mostrarDNIClienteConRutinaMasIntensa(NodoCliente* listaClientes) {
    NodoCliente* clienteMax = nullptr;
    NodoCliente* actual = listaClientes;
    while (actual != nullptr) {
        if (actual->clienteConRutinas.pilaRutinas != nullptr) {
            if (clienteMax == nullptr ||
                actual->clienteConRutinas.pilaRutinas->rutina.intensidad > 
                clienteMax->clienteConRutinas.pilaRutinas->rutina.intensidad) {
                clienteMax = actual;
            }
        }
        actual = actual->siguiente;
    }
    if (clienteMax != nullptr) {
        return clienteMax->clienteConRutinas.cliente.dni;
    }
    // Si ningún cliente tiene rutinas, podrías lanzar una excepción, retornar 0, o manejarlo según tu lógica
    return 0;
}

int main(){
}