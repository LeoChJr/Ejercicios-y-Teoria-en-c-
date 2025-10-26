#include <iostream>
#include <string>
#include <cstring>
using namespace std;

// ==========================================
// 🔹 1️⃣ ESTRUCTURAS
// ==========================================

// Representa a una persona interesada en alquilar un departamento
struct Persona {
    string nombre;
    string telefono;
};

// NodoPersona es un elemento de la cola (cada persona en espera)
struct NodoPersona {
    Persona per;           // datos de la persona
    NodoPersona* sgte;     // puntero al siguiente en la cola
};

// Datos del departamento que administra la inmobiliaria
struct Departamento {
    int codigo;            // identificador único del depto
    char direccion[100];
    char tipo[30];
    char estado[10];       // puede ser "libre" o "alquilado"
};

// Cada departamento tiene su propia "cola" de personas (turnos de visita)
struct DepartamentoConPersonas {
    Departamento dep;      // datos del departamento
    NodoPersona* frente;   // apunta al primer turno (primera persona en la cola)
    NodoPersona* final;    // apunta al último turno (última persona en la cola)
};

// Lista enlazada de departamentos
struct NodoDepartamento {
    DepartamentoConPersonas datos;  // info del departamento + su cola
    NodoDepartamento* sgte;         // siguiente departamento en la lista
};



// ==========================================
// 🔹 2️⃣ FUNCIONES DE CARGA DESDE ARCHIVO
// ==========================================

// Función que simula leer un registro de un archivo
// Devuelve un departamento distinto cada vez que se la llama
Departamento dameSiguienteRegistroDelArchivo() {
    static int contador = 0; // se mantiene entre llamadas
    Departamento d;

    if (contador == 0) {
        d.codigo = 1023;
        strcpy(d.direccion, "Av.SiempreViva742");
        strcpy(d.tipo, "2ambientes");
        strcpy(d.estado, "libre");
    } else if (contador == 1) {
        d.codigo = 1024;
        strcpy(d.direccion, "CalleFalsa123");
        strcpy(d.tipo, "1ambiente");
        strcpy(d.estado, "alquilado");
    } else if (contador == 2) {
        d.codigo = 1025;
        strcpy(d.direccion, "Libertad50");
        strcpy(d.tipo, "2ambientes");
        strcpy(d.estado, "libre");
    } else {
        d.codigo = 0; // Indica que no hay más registros
    }

    contador++;
    return d;
}

// Agrega un departamento al final de la lista enlazada
NodoDepartamento* addElementoLista(NodoDepartamento* lista, DepartamentoConPersonas dep) {
    NodoDepartamento* nuevo = new NodoDepartamento;
    nuevo->datos = dep;
    nuevo->sgte = NULL;

    if (lista == NULL) {
        // si la lista está vacía, el nuevo es el primero
        lista = nuevo;
    } else {
        // si ya hay elementos, recorremos hasta el final
        NodoDepartamento* actual = lista;
        while (actual->sgte != NULL)
            actual = actual->sgte;
        actual->sgte = nuevo;
    }
    return lista;
}

// Carga todos los departamentos en la lista principal desde el "archivo"
NodoDepartamento* CargarLista() {
    NodoDepartamento* lista = NULL;
    Departamento dep = dameSiguienteRegistroDelArchivo();

    // mientras haya registros válidos
    while (dep.codigo != 0) {
        DepartamentoConPersonas depConCola;
        depConCola.dep = dep;
        depConCola.frente = NULL; // cola vacía
        depConCola.final = NULL;

        lista = addElementoLista(lista, depConCola);
        dep = dameSiguienteRegistroDelArchivo();
    }

    return lista; // devuelve el inicio de la lista
}



// ==========================================
// 🔹 3️⃣ ENCOLAR PERSONAS (ASIGNAR TURNOS)
// ==========================================

// Inserta una persona al final de la cola (orden FIFO)
void encolar(NodoPersona*& frente, NodoPersona*& final, Persona p) {
    NodoPersona* nuevo = new NodoPersona;
    nuevo->per = p;
    nuevo->sgte = NULL;

    if (frente == NULL) {
        // Si la cola está vacía, el nuevo nodo es el frente y final
        frente = final = nuevo;
    } else {
        // Si ya hay elementos, lo agregamos después del último
        final->sgte = nuevo;
        final = nuevo;
    }
}

// Asigna una persona a un departamento libre.
// Si está alquilado, muestra un mensaje de error.
void asignarTurno(NodoDepartamento* lista, Persona p, int codigo) {
    NodoDepartamento* actual = lista;

    // Buscamos el departamento por su código
    while (actual != NULL) {
        if (actual->datos.dep.codigo == codigo) {

            // Si el depto está alquilado → no se puede asignar turno
            if (strcmp(actual->datos.dep.estado, "alquilado") == 0) {
                cout << "El departamento " << codigo << " está alquilado. No se puede asignar turno." << endl;
                return;
            }

            // Si está libre → encolamos a la persona en su cola
            encolar(actual->datos.frente, actual->datos.final, p);
            cout << "Turno asignado a " << p.nombre
                 << " para el departamento " << codigo << endl;
            return;
        }
        actual = actual->sgte;
    }

    cout << "No se encontró el departamento con código " << codigo << endl;
}



// ==========================================
// 🔹 4️⃣ VACIAR TODAS LAS COLAS
// ==========================================

// Libera todos los nodos de una cola
void vaciarCola(NodoPersona*& frente, NodoPersona*& final) {
    NodoPersona* actual = frente;
    while (actual != NULL) {
        NodoPersona* borrar = actual;
        actual = actual->sgte;
        delete borrar; // liberamos memoria
    }
    frente = final = NULL; // cola vacía
}

// Aplica el vaciado a todos los departamentos
void vaciarTodosLosTurnos(NodoDepartamento* lista) {
    NodoDepartamento* actual = lista;
    while (actual != NULL) {
        vaciarCola(actual->datos.frente, actual->datos.final);
        actual = actual->sgte;
    }
    cout << "Se vaciaron todos los turnos de todos los departamentos." << endl;
}



// ==========================================
// 🔹 5️⃣ ASIGNAR TURNO AVANZADO
// ==========================================
// Si el departamento está alquilado, busca otro libre del mismo tipo
void asignarTurnoAvanzado(NodoDepartamento* lista, Persona p, int codigo) {
    NodoDepartamento* actual = lista;
    NodoDepartamento* libreMismoTipo = NULL;

    while (actual != NULL) {
        if (actual->datos.dep.codigo == codigo) {

            // Si está libre, encolamos normalmente
            if (strcmp(actual->datos.dep.estado, "libre") == 0) {
                encolar(actual->datos.frente, actual->datos.final, p);
                cout << "Turno asignado a " << p.nombre
                     << " en el departamento " << codigo << endl;
                return;
            }

            // Si está alquilado → buscamos otro libre del mismo tipo
            NodoDepartamento* aux = lista;
            while (aux != NULL) {
                if (strcmp(aux->datos.dep.tipo, actual->datos.dep.tipo) == 0 &&
                    strcmp(aux->datos.dep.estado, "libre") == 0) {
                    libreMismoTipo = aux;
                    break;
                }
                aux = aux->sgte;
            }

            // Si encontramos uno → encolamos allí
            if (libreMismoTipo != NULL) {
                encolar(libreMismoTipo->datos.frente, libreMismoTipo->datos.final, p);
                cout << "El departamento " << codigo << " está alquilado.\n";
                cout << "Se asignó turno en otro libre del mismo tipo: "
                     << libreMismoTipo->datos.dep.codigo << endl;
                return;
            } else {
                // No hay otro libre → mensaje de error
                cout << "El departamento " << codigo << " está alquilado y no hay otro libre del mismo tipo.\n";
                cout << "No se pudo asignar turno a " << p.nombre << ".\n";
                return;
            }
        }

        actual = actual->sgte;
    }

    cout << "No se encontró el departamento con código " << codigo << endl;
}



// ==========================================
// 🔹 6️⃣ ATENDER TURNOS EN ORDEN FIFO
// ==========================================

// Saca el primer elemento de la cola y lo devuelve por referencia
bool desencolar(NodoPersona*& frente, NodoPersona*& final, Persona &p) {
    if (frente == NULL) return false;

    NodoPersona* borrar = frente;
    p = borrar->per;
    frente = borrar->sgte;

    if (frente == NULL)
        final = NULL; // si la cola quedó vacía

    delete borrar;
    return true;
}

// Atiende los turnos de un departamento hasta que alguien acepte o se vacíen
void atenderTurnos(NodoDepartamento* lista, int codigo) {
    NodoDepartamento* actual = lista;

    while (actual != NULL) {
        if (actual->datos.dep.codigo == codigo) {
            NodoPersona*& frente = actual->datos.frente;
            NodoPersona*& final = actual->datos.final;

            if (frente == NULL) {
                cout << "No hay turnos para el departamento " << codigo << ".\n";
                return;
            }

            cout << "Atendiendo turnos del departamento " << codigo
                 << " (" << actual->datos.dep.tipo << ")\n";

            Persona p;
            while (desencolar(frente, final, p)) {
                cout << "Cliente: " << p.nombre
                     << " - Tel: " << p.telefono << endl;
                cout << "¿Desea alquilar este departamento? (s/n): ";
                char resp;
                cin >> resp;

                if (resp == 's' || resp == 'S') {
                    strcpy(actual->datos.dep.estado, "alquilado");
                    cout << "El departamento " << codigo
                         << " fue alquilado por " << p.nombre << ".\n";

                    vaciarCola(frente, final);
                    return;
                } else {
                    cout << "No aceptó, pasando al siguiente turno...\n";
                }
            }

            cout << "Se atendieron todos los turnos y nadie aceptó.\n";
            return;
        }
        actual = actual->sgte;
    }

    cout << "No se encontró el departamento con código " << codigo << endl;
}



// ==========================================
// 🔹 MAIN (PRUEBA)
// ==========================================
int main() {
    // Cargamos departamentos (lista enlazada)
    NodoDepartamento* lista = CargarLista();

    // Creamos algunas personas
    Persona p1 = {"Juan Perez", "123456789"};
    Persona p2 = {"Maria Lopez", "987654321"};
    Persona p3 = {"Carlos Diaz", "555555555"};

    // Asignamos turnos (una en libre, otra en alquilado)
    asignarTurnoAvanzado(lista, p1, 1023);
    asignarTurnoAvanzado(lista, p2, 1024);
    asignarTurnoAvanzado(lista, p3, 1025);

    // Atendemos turnos del departamento 1023
    atenderTurnos(lista, 1023);

    // Vaciamos todos los turnos
    vaciarTodosLosTurnos(lista);

    return 0;
}
