#include <iostream>
#include <string>
#include <cstring>
using namespace std;

// ======================
// ESTRUCTURAS PRINCIPALES
// ======================

// Representa a una persona participante de un sorteo
struct Persona {
    int dni;          // Documento de identidad
    string nombre;    // Nombre del participante
};

// Nodo de una lista enlazada de personas (participantes)
struct NodoPersona {
    Persona per;          // Datos de la persona
    NodoPersona* sgte;    // Puntero al siguiente nodo en la lista
};

// Representa un sorteo
struct Sorteo {
    int codigo;                 // Código identificador del sorteo
    int cantidad_ganadores;     // Cuántos ganadores habrá
    char descripcion[200];      // Descripción del sorteo (por ejemplo, "Sorteo de verano")
};

// Representa un sorteo con su lista de participantes
struct SorteoConPersona {
    Sorteo sorteo;              // Datos del sorteo
    NodoPersona* personas;      // Lista enlazada de personas que participan
};

// Nodo de una lista de sorteos (lista principal)
struct NodoSorteo {
    SorteoConPersona sorteo;    // Sorteo con sus personas
    NodoSorteo* sgte;           // Puntero al siguiente sorteo en la lista
};

// ======================
// PROTOTIPOS DE FUNCIONES
// ======================
Sorteo dameSiguienteRegistroDelArchivo();            // Simula lectura del archivo
NodoPersona* addElementoLista(NodoPersona* lista, Persona p); // Agrega persona a lista


// ======================
// AGREGA PERSONA A LA LISTA ENLAZADA
// ======================
NodoPersona* addElementoLista(NodoPersona* lista, Persona p) {
    // Crea un nuevo nodo de persona
    NodoPersona* nuevo = new NodoPersona;
    nuevo->per = p;        // Asigna los datos de la persona
    nuevo->sgte = NULL;    // Inicializa el puntero siguiente en NULL

    if (lista == NULL)
        // Si la lista está vacía, el nuevo nodo será el primero
        lista = nuevo;
    else {
        // Si ya hay nodos, recorre hasta el final
        NodoPersona* actual = lista;
        while (actual->sgte != NULL)
            actual = actual->sgte;
        // Conecta el nuevo nodo al final
        actual->sgte = nuevo;
    }
    return lista; // Devuelve el inicio de la lista
}

// ======================
// SIMULA LECTURA DE ARCHIVO DE SORTEOS
// ======================
Sorteo dameSiguienteRegistroDelArchivo() {
    Sorteo sor;
    static int i = 0; // Variable estática: conserva su valor entre llamadas

    // Devuelve diferentes sorteos en cada llamada
    if (i == 0) {
        sor.codigo = 101;
        sor.cantidad_ganadores = 3;
        strcpy(sor.descripcion, "Sorteo de verano");
    } else if (i == 1) {
        sor.codigo = 102;
        sor.cantidad_ganadores = 2;
        strcpy(sor.descripcion, "Sorteo de invierno");
    } else {
        // Cuando no hay más sorteos, devuelve código 0
        sor.codigo = 0;
    }
    i++;
    return sor;
}

// ======================
// AGREGA UN SORTEO A LA LISTA DE SORTEOS
// ======================
NodoSorteo* addElementoLista(NodoSorteo* lista, SorteoConPersona s) {
    // Crea un nuevo nodo de sorteo
    NodoSorteo* nuevo = new NodoSorteo;
    nuevo->sorteo = s;     // Copia los datos del sorteo (con lista vacía de personas)
    nuevo->sgte = NULL;    // Lo inicializa sin siguiente

    if (lista == NULL)
        // Si la lista está vacía, este es el primer sorteo
        lista = nuevo;
    else {
        // Si ya hay sorteos, recorre hasta el final y lo agrega
        NodoSorteo* actual = lista;
        while (actual->sgte != NULL)
            actual = actual->sgte;
        actual->sgte = nuevo;
    }
    return lista; // Devuelve el inicio de la lista
}

// ======================
// CARGA LISTA DE SORTEOS DESDE ARCHIVO
// ======================
NodoSorteo* CargarLista() {
    NodoSorteo* lista = NULL; // Lista principal vacía
    Sorteo sor = dameSiguienteRegistroDelArchivo(); // Lee el primer sorteo

    // Repite mientras haya sorteos válidos (código != 0)
    while (sor.codigo != 0) {
        SorteoConPersona sorteoPer;
        sorteoPer.sorteo = sor;     // Guarda los datos del sorteo
        sorteoPer.personas = NULL;  // Inicializa lista de personas vacía

        // Agrega este sorteo a la lista principal
        lista = addElementoLista(lista, sorteoPer);

        // Lee el siguiente sorteo del archivo
        sor = dameSiguienteRegistroDelArchivo();
    }

    return lista; // Devuelve la lista completa de sorteos
}

// ======================
// AGREGA UNA PERSONA A UN SORTEO ESPECÍFICO
// ======================
void CargarPersona(NodoSorteo* lista, Persona per, int codigo) {
    NodoSorteo* actual = lista; // Empieza desde el primer sorteo

    while (actual != NULL) {
        // Busca el sorteo con el código indicado
        if (actual->sorteo.sorteo.codigo == codigo) {
            // Cuando lo encuentra, agrega la persona a su lista de participantes
            actual->sorteo.personas = addElementoLista(actual->sorteo.personas, per);
            break; // Termina la búsqueda
        }
        actual = actual->sgte; // Pasa al siguiente sorteo
    }
}

// ======================
// MUESTRA LOS SORTEOS DONDE PARTICIPA UNA PERSONA
// ======================
void mostrarSorteos(NodoSorteo* lista, int dni) {
    NodoSorteo* actualSor = lista; // Recorre los sorteos uno por uno

    while (actualSor != NULL) {
        NodoPersona* actualPer = actualSor->sorteo.personas; // Lista de personas de ese sorteo

        // Recorre la lista de personas del sorteo actual
        while (actualPer != NULL) {
            if (actualPer->per.dni == dni) {
                // Si el DNI coincide, muestra la descripción del sorteo
                cout << actualSor->sorteo.sorteo.descripcion << endl;
                break; // Ya no hace falta seguir buscando en este sorteo
            }
            actualPer = actualPer->sgte; // Avanza al siguiente participante
        }
        actualSor = actualSor->sgte; // Pasa al siguiente sorteo
    }
}

// ======================
// FUNCIÓN PRINCIPAL (MAIN)
// ======================
int main(){
    // Crea la lista de sorteos leyendo desde el archivo simulado
    NodoSorteo* lista = CargarLista();

    // Crea dos personas (participantes)
    Persona p1 = {123, "Juan"};
    Persona p2 = {456, "Maria"};

    // Asigna a Juan al sorteo con código 101 (verano)
    CargarPersona(lista, p1, 101);

    // Asigna a María al sorteo con código 102 (invierno)
    CargarPersona(lista, p2, 102);

    // Muestra los sorteos donde participa Juan
    cout << "\nSorteos de Juan:\n";
    mostrarSorteos(lista, 123);

    return 0;
}
