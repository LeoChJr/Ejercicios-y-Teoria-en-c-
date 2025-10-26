//___________EL MISMO PERO CON PILA—-------------------------------
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

// NodoPersona es un elemento de la pila (cada persona en espera)
struct NodoPersona {
    Persona per;           // datos de la persona
    NodoPersona* sgte;     // puntero al siguiente (debajo en la pila)
};

// Datos del departamento
struct Departamento {
    int codigo;
    char direccion[100];
    char tipo[30];
    char estado[10];       // "libre" o "alquilado"
};

// Cada departamento tiene su propia pila de turnos
struct DepartamentoConPersonas {
    Departamento dep;
    NodoPersona* pila; // tope de la pila (último en llegar)
};

// Lista de departamentos
struct NodoDepartamento {
    DepartamentoConPersonas datos;
    NodoDepartamento* sgte;
};

// ==========================================
// 🔹 2️⃣ CARGA DE DEPARTAMENTOS
// ==========================================

Departamento dameSiguienteRegistroDelArchivo() {
    static int contador = 0;
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
        d.codigo = 0;
    }

    contador++;
    return d;
}

// Agrega un departamento a la lista
NodoDepartamento* addElementoLista(NodoDepartamento* lista, DepartamentoConPersonas dep) {
    NodoDepartamento* nuevo = new NodoDepartamento;
    nuevo->datos = dep;
    nuevo->sgte = NULL;

    if (lista == NULL)
        lista = nuevo;
    else {
        NodoDepartamento* actual = lista;
        while (actual->sgte != NULL)
            actual = actual->sgte;
        actual->sgte = nuevo;
    }
    return lista;
}

// Cargar departamentos en una lista enlazada
NodoDepartamento* CargarLista() {
    NodoDepartamento* lista = NULL;
    Departamento dep = dameSiguienteRegistroDelArchivo();

    while (dep.codigo != 0) {
        DepartamentoConPersonas depConPila;
        depConPila.dep = dep;
        depConPila.pila = NULL; // pila vacía
        lista = addElementoLista(lista, depConPila);
        dep = dameSiguienteRegistroDelArchivo();
    }
    return lista;
}

// ==========================================
// 🔹 3️⃣ PUSH Y POP (operaciones de PILA)
// ==========================================

// Agrega una persona arriba de la pila (último en llegar)
void push(NodoPersona*& pila, Persona p) {
    NodoPersona* nuevo = new NodoPersona;
    nuevo->per = p;
    nuevo->sgte = pila; // apunta al anterior tope
    pila = nuevo;       // nuevo tope
}

// Saca la persona de arriba de la pila (último en entrar)
bool pop(NodoPersona*& pila, Persona &p) {
    if (pila == NULL) return false;
    NodoPersona* borrar = pila;
    p = borrar->per;
    pila = borrar->sgte;
    delete borrar;
    return true;
}

// ==========================================
// 🔹 4️⃣ ASIGNAR TURNOS (PUSH)
// ==========================================

void asignarTurno(NodoDepartamento* lista, Persona p, int codigo) {
    NodoDepartamento* actual = lista;
    while (actual != NULL) {
        if (actual->datos.dep.codigo == codigo) {
            if (strcmp(actual->datos.dep.estado, "alquilado") == 0) {
                cout << "El departamento " << codigo << " está alquilado. No se puede asignar turno." << endl;
                return;
            }

            // Agregamos persona a la pila (último en entrar, primero en atender)
            push(actual->datos.pila, p);
            cout << "Turno asignado (en pila) a " << p.nombre
                 << " para el departamento " << codigo << endl;
            return;
        }
        actual = actual->sgte;
    }
    cout << "No se encontró el departamento con código " << codigo << endl;
}

// ==========================================
// 🔹 5️⃣ VACIAR TODAS LAS PILAS
// ==========================================

void vaciarPila(NodoPersona*& pila) {
    Persona aux;
    while (pop(pila, aux)) { /* libera cada nodo */ }
}

void vaciarTodosLosTurnos(NodoDepartamento* lista) {
    NodoDepartamento* actual = lista;
    while (actual != NULL) {
        vaciarPila(actual->datos.pila);
        actual = actual->sgte;
    }
    cout << "Se vaciaron todos los turnos (pilas) de todos los departamentos." << endl;
}

// ==========================================
// 🔹 6️⃣ ATENDER TURNOS (POP - LIFO)
// ==========================================

void atenderTurnos(NodoDepartamento* lista, int codigo) {
    NodoDepartamento* actual = lista;

    while (actual != NULL) {
        if (actual->datos.dep.codigo == codigo) {
            if (actual->datos.pila == NULL) {
                cout << "No hay turnos en la pila del departamento " << codigo << ".\n";
                return;
            }

            cout << "Atendiendo turnos (PILA) del departamento " << codigo
                 << " (" << actual->datos.dep.tipo << ")\n";

            Persona p;
            while (pop(actual->datos.pila, p)) {
                cout << "Cliente: " << p.nombre << " - Tel: " << p.telefono << endl;
                cout << "¿Desea alquilar este departamento? (s/n): ";
                char resp;
                cin >> resp;

                if (resp == 's' || resp == 'S') {
                    strcpy(actual->datos.dep.estado, "alquilado");
                    cout << "El departamento " << codigo
                         << " fue alquilado por " << p.nombre << ".\n";
                    vaciarPila(actual->datos.pila);
                    return;
                } else {
                    cout << "No aceptó, pasando al siguiente turno (abajo en la pila)...\n";
                }
            }

            cout << "Se atendieron todos los turnos de la pila y nadie aceptó.\n";
            return;
        }
        actual = actual->sgte;
    }
    cout << "No se encontró el departamento con código " << codigo << endl;
}

// ==========================================
// 🔹 MAIN DE PRUEBA
// ==========================================
int main() {
    NodoDepartamento* lista = CargarLista();

    Persona p1 = {"Juan Perez", "123456789"};
    Persona p2 = {"Maria Lopez", "987654321"};
    Persona p3 = {"Carlos Diaz", "555555555"};

    // Apilar turnos
    asignarTurno(lista, p1, 1023);
    asignarTurno(lista, p2, 1023);
    asignarTurno(lista, p3, 1023);

    // Atender turnos (se atiende primero el último que llegó)
    atenderTurnos(lista, 1023);

    // Vaciar todas las pilas
    vaciarTodosLosTurnos(lista);

    return 0;
}

