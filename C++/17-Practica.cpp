// Estructura para representar una tarea individual

#include <iostream>
#include <string>
using namespace std;

struct NodoTarea
{
    string descripcion;      // Descripción de la tarea
    NodoTarea *sgte;         // Puntero al siguiente nodo en la pila de tareas
};

// Estructura para representar una lista de tareas de un tipo específico
struct ListaPorTipo
{
    NodoTarea *pilaDeTareas; // Puntero al tope de la pila de tareas de este tipo
    int codigoTipo;          // Código que identifica el tipo de tarea
    ListaPorTipo *sgte;      // Puntero al siguiente tipo en la lista principal
};

ListaPorTipo *lista; // Puntero a la lista principal de tipos de tareas

// 1. Agrega una nueva lista de tareas para un tipo específico
ListaPorTipo *agregarNuevaListaPorTipo(ListaPorTipo *&lista, int codigoTipo)
{
    ListaPorTipo *tipoActual = new ListaPorTipo; // Crea un nuevo nodo para el tipo
    tipoActual->codigoTipo = codigoTipo;         // Asigna el código de tipo
    tipoActual->pilaDeTareas = nullptr;          // Inicializa la pila de tareas vacía
    tipoActual->sgte = nullptr;                  // Inicializa el puntero siguiente como nulo

    // Busca el final de la lista principal para agregar el nuevo tipo
    ListaPorTipo *tipoAnterior = nullptr;
    ListaPorTipo *tipoAuxiliar = lista;
    while (tipoAuxiliar != nullptr)
    {
        tipoAnterior = tipoAuxiliar;             // Guarda el nodo anterior
        tipoAuxiliar = tipoAuxiliar->sgte;       // Avanza al siguiente nodo
    }
    if (tipoAnterior == nullptr)
    {
        lista = tipoActual;                      // Si la lista está vacía, el nuevo tipo es el primero
    }
    else
    {
        tipoAnterior->sgte = tipoActual;         // Si no, lo agrega al final
    }
    return tipoActual;                           // Devuelve el puntero al nuevo tipo
}

// 2. Agrega una tarea a la pila de un tipo específico
void agregarTarea(ListaPorTipo *&lista, int codigoTipo, string descripcion)
{
    ListaPorTipo *tipoActual = lista;            // Comienza desde el inicio de la lista
    ListaPorTipo *tipoAnterior = nullptr;
    // Busca la lista correspondiente al códigoTipo
    while (tipoActual != nullptr && tipoActual->codigoTipo != codigoTipo)
    {
        tipoAnterior = tipoActual;               // Guarda el nodo anterior
        tipoActual = tipoActual->sgte;           // Avanza al siguiente nodo
    }
    // Si no existe la lista para ese tipo, la crea
    if (tipoActual == nullptr)
    {
        tipoActual = agregarNuevaListaPorTipo(lista, codigoTipo); // Crea nueva lista de tipo
    }
    // Crea un nuevo nodo de tarea
    NodoTarea *nuevaTarea = new NodoTarea;
    nuevaTarea->descripcion = descripcion;       // Asigna la descripción
    nuevaTarea->sgte = tipoActual->pilaDeTareas; // Apunta al tope actual de la pila
    tipoActual->pilaDeTareas = nuevaTarea;       // El nuevo nodo es el nuevo tope de la pila
}

// 3. Devuelve y elimina la próxima tarea de un tipo específico
string dameProximaTarea(ListaPorTipo *lista, int codigoTipo)
{
    ListaPorTipo *tipoActual = lista;            // Comienza desde el inicio de la lista
    // Busca la lista correspondiente al códigoTipo
    while (tipoActual != nullptr && tipoActual->codigoTipo != codigoTipo)
    {
        tipoActual = tipoActual->sgte;           // Avanza al siguiente nodo
    }
    // Si no existe la lista o no hay tareas, retorna "No tengo"
    if (tipoActual == nullptr || tipoActual->pilaDeTareas == nullptr)
    {
        return "No tengo";
    }
    // Obtiene la descripción de la tarea en el tope de la pila
    string descripcion = tipoActual->pilaDeTareas->descripcion;
    NodoTarea *tareaAEliminar = tipoActual->pilaDeTareas; // Guarda el nodo a eliminar
    tipoActual->pilaDeTareas = tipoActual->pilaDeTareas->sgte; // Avanza el tope de la pila
    delete tareaAEliminar;                          // Libera la memoria de la tarea eliminada
    return descripcion;                             // Devuelve la descripción de la tarea
}

// 4. Cuenta cuántas pilas tienen tareas pendientes
int dameCantidadDePilasConTareasPendientes(ListaPorTipo *lista)
{
    int cantidad = 0;                              // Inicializa el contador
    ListaPorTipo *tipoActual = lista;              // Comienza desde el inicio de la lista
    while (tipoActual != nullptr)
    {
        if (tipoActual->pilaDeTareas != nullptr)   // Si la pila de tareas no está vacía
        {
            cantidad++;                            // Incrementa el contador
        }
        tipoActual = tipoActual->sgte;             // Avanza al siguiente tipo
    }
    return cantidad;                               // Devuelve la cantidad de pilas con tareas
}

int main(){
    lista = nullptr; // Inicializa la lista principal como vacía

    // Agrega tareas a diferentes tipos
    agregarTarea(lista, 1, "Tarea 1 de tipo 1");
    agregarTarea(lista, 1, "Tarea 2 de tipo 1");
    agregarTarea(lista, 2, "Tarea 1 de tipo 2");

    // Muestra la próxima tarea de cada tipo
    cout << "Próxima tarea de tipo 1: " << dameProximaTarea(lista, 1) << endl; // Espera "Tarea 2 de tipo 1"
    cout << "Próxima tarea de tipo 2: " << dameProximaTarea(lista, 2) << endl; // Espera "Tarea 1 de tipo 2"
    cout << "Próxima tarea de tipo 3: " << dameProximaTarea(lista, 3) << endl; // Espera "No tengo"

    // Cuenta cuántas pilas tienen tareas pendientes
    cout << "Cantidad de pilas con tareas pendientes: " << dameCantidadDePilasConTareasPendientes(lista) << endl; // Espera 1

    return 0;
}