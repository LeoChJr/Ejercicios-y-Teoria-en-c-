// Práctica: Administración de equipos y sus jugadores en un torneo de fútbol
// Descripción general:
// Este programa usa estructuras enlazadas para representar jugadores dentro de equipos.
// Cada equipo tiene un código y una lista (enlazada) de jugadores. Se implementan funciones
// para inicializar equipos, agregar jugadores y obtener el capitán (jugador de mayor habilidad).

#include <iostream>
#include <string>
using namespace std;

// Estructura que representa un jugador: nombre y nivel de habilidad
struct Jugador
{
    string nombre; // Nombre del jugador
    int habilidad; // Puntuación de habilidad
};

// Nodo de la lista enlazada que contiene un Jugador y un puntero al siguiente nodo
struct NodoJugador
{
    Jugador jugador;     // Datos del jugador
    NodoJugador *sgte;    // Puntero al siguiente nodo en la lista 
};

// Estructura Equipo: código identificador y puntero a la lista de jugadores
struct Equipo
{
    int codigoEquipo;    // Código único del equipo (p. ej. 10..29)
    NodoJugador *jugadores; // Puntero al primer nodo de la lista de jugadores
};

// Inicializa los equipos: asigna códigos consecutivos desde 10 y deja la lista vacía
void inicializarEquipos(Equipo equipos[], int cantidad)
{
    for (int i = 0; i < cantidad; i++)
    {
        equipos[i].codigoEquipo = 10 + i; // Asigna código (10,11,12,...)
        equipos[i].jugadores = NULL;      // Inicializa la lista de jugadores como vacía
    }
}

// Crea y agrega un nuevo nodo al final de la lista de jugadores; devuelve el puntero (posible nueva cabeza)
NodoJugador *agregarNodo(NodoJugador *jugadores, string nombreJugador, int habilidad)// Agrega un nuevo jugador al final de la lista
{
    NodoJugador *nuevo = new NodoJugador;           // Reserva memoria para un nuevo nodo
    nuevo->jugador.nombre = nombreJugador;         // Asigna el nombre
    nuevo->jugador.habilidad = habilidad;           // Asigna la habilidad
    nuevo->sgte = nullptr;                          // Inicialmente no apunta a ningún siguiente

    if (jugadores == nullptr) // Si la lista estaba vacía
    {
        jugadores = nuevo;    // El nuevo nodo es ahora la cabeza de la lista
    }
    else
    {
        NodoJugador *actual = jugadores;            // Empezar desde la cabeza
        while (actual->sgte != nullptr)             // Avanzar hasta el último nodo
        {
            actual = actual->sgte;                 // Mover al siguiente
        }
        actual->sgte = nuevo;                      // Enlazar el nuevo nodo al final
    }
    return jugadores; // Retornar (posible) nueva cabeza de la lista
}

// Busca el equipo por código y agrega un jugador usando agregarNodo
void agregarJugador(Equipo equipos[], int codigoEquipo, string nombreJugador, int habilidad, int cantidad)// Agrega un jugador a un equipo específico (osea a la lista de equipos que le corresponde el codigo)
{
    // Recorre el arreglo de equipos para encontrar el código coincidente
    for (int i = 0; i < cantidad; i++)
    {
        if (equipos[i].codigoEquipo == codigoEquipo)
        {
            // Actualiza la lista de jugadores del equipo con el nuevo nodo
            equipos[i].jugadores = agregarNodo(equipos[i].jugadores, nombreJugador, habilidad);
            break; // Salir al encontrar el equipo
        }
    }
}

// Devuelve el jugador con mayor habilidad dentro del equipo indicado
Jugador obtenerCapitan(Equipo equipos[], int codigoEquipo, int cantidad)
{
    Jugador jugMax;         // Jugador con mayor habilidad encontrado

    for (int i = 0; i < cantidad; i++)
    {
        if (equipos[i].codigoEquipo == codigoEquipo) // Si encontramos el equipo
        {
            int max = 0;                              // Máxima habilidad encontrada hasta ahora
            NodoJugador *jug = equipos[i].jugadores;  // Puntero para recorrer la lista
            while (jug != nullptr)                    // Recorre todos los nodos
            {
                if (jug->jugador.habilidad > max)   // Si la habilidad actual es mayor
                {
                    jugMax = jug->jugador;          // Actualiza el capitán temporal
                    max = jug->jugador.habilidad;   // Actualiza el valor máximo
                }
                jug = jug->sgte;                    // Avanza al siguiente nodo
            }
            break; // Sale tras procesar el equipo encontrado
        }
    }
    return jugMax; // Retorna el jugador con mayor habilidad (o un Jugador vacío si no hay jugadores)
}

// Función principal: demuestra el uso de las funciones anteriores
int main()
{
    Equipo equipos[20];               // Array estático de 20 equipos
    inicializarEquipos(equipos, 20);  // Inicializa códigos y listas

    // Agrega jugadores al equipo con código 10
    agregarJugador(equipos, 10, "Juan Perez", 85, 20);
    agregarJugador(equipos, 10, "Pedro Gomez", 78, 20);

    // Agrega jugadores al equipo con código 11
    agregarJugador(equipos, 11, "Juan Perez", 85, 20);
    agregarJugador(equipos, 11, "Pedro Gomez", 199, 20);

    // Nota: la siguiente llamada tiene 'cantidad' = 100, pero el arreglo solo tiene 20 elementos.
    // Esto no causa efecto práctico en este caso porque la búsqueda por código encontrará el equipo
    // antes de que el bucle alcance índices fuera de rango. Sin embargo, pasar 100 es inconsistente
    // y debe corregirse a 20 para mayor seguridad.
    agregarJugador(equipos, 11, "Luis Martinez", 900, 100);

    // Muestra los nombres de los capitanes (mejores jugadores) de los equipos 10 y 11
    cout << obtenerCapitan(equipos, 10, 20).nombre << endl;
    cout << obtenerCapitan(equipos, 11, 20).nombre << endl;
    return 0;
}