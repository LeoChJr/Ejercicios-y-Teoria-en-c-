#include <iostream> // entrada/salida
#include <string>   // std::string
#include <cstring>  // funciones de cadena C (strcpy, strcmp)
using namespace std; // evita std:: en cada nombre

// --- ESTRUCTURAS ---

// Persona: datos de quien pide turno
struct Persona {
    string nombre;   // nombre de la persona
    string telefono; // teléfono de contacto
};

// NodoPersona: elemento de la cola de turnos
struct NodoPersona {
    Persona per;        // datos de la persona
    NodoPersona* sgte;  // puntero al siguiente nodo en la cola
};

// Departamento: datos básicos del departamento
struct Departamento {
    int codigo;             // identificador único
    char direccion[100];    // dirección (cadena C)
    char tipo[30];          // tipo (ej. "2ambientes")
    char estado[10];        // "libre" o "alquilado"
};

// DepartamentoConPersonas: combina el depto con su cola de turnos
struct DepartamentoConPersonas {
    Departamento dep;     // datos del departamento
    NodoPersona* frente;   // cabeza de la cola (primer turno)
    NodoPersona* final;    // cola final (último turno)
};

// NodoDepartamento: nodo de la lista enlazada de departamentos
struct NodoDepartamento {
    DepartamentoConPersonas datos; // depto + cola
    NodoDepartamento* sgte;        // siguiente departamento
};

// --- FUNCIONES DE CARGA ---

// Simula la lectura de registros desde un archivo: devuelve uno por cada llamada
Departamento dameSiguienteRegistroDelArchivo() {
    static int contador = 0; // conserva su valor entre llamadas
    Departamento d;          // registro a devolver

    if (contador == 0) {
        d.codigo = 1023;                          // asigna código
        strcpy(d.direccion, "Av.SiempreViva742"); // copia dirección
        strcpy(d.tipo, "2ambientes");           // copia tipo
        strcpy(d.estado, "libre");              // copia estado
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
        d.codigo = 0; // marcador: no hay más registros
    }

    contador++; // prepara la próxima llamada
    return d;   // devuelve el registro
}

// Añade un nodo Departamento al final de la lista enlazada
NodoDepartamento* addElementoLista(NodoDepartamento* lista, DepartamentoConPersonas dep) {
    NodoDepartamento* nuevo = new NodoDepartamento; // crea nodo dinámico
    nuevo->datos = dep;      // copia datos
    nuevo->sgte = NULL;      // inicialmente no hay siguiente

    if (lista == NULL) {
        lista = nuevo; // lista vacía → nuevo es cabeza
    } else {
        NodoDepartamento* actual = lista; // recorrer hasta final
        while (actual->sgte != NULL) actual = actual->sgte; // avanza
        actual->sgte = nuevo; // enlaza al final
    }
    return lista; // retorna la cabeza (posible nueva)
}

// Lee todos los departamentos disponibles y arma la lista enlazada
NodoDepartamento* CargarLista() {
    NodoDepartamento* lista = NULL;                     // inicio vacío
    Departamento dep = dameSiguienteRegistroDelArchivo(); // leer primer registro

    while (dep.codigo != 0) {                           // mientras haya registros
        DepartamentoConPersonas depConCola;             // estructura compuesta
        depConCola.dep = dep;                           // copiar datos
        depConCola.frente = NULL;                       // cola vacía al inicio
        depConCola.final = NULL;

        lista = addElementoLista(lista, depConCola);   // agregar a la lista
        dep = dameSiguienteRegistroDelArchivo();       // leer siguiente registro
    }

    return lista; // retorna la lista completa
}

// --- COLA: ENCOLAR / DESENCOLAR ---

// Encola una persona al final de la cola (FIFO)
void encolar(NodoPersona*& frente, NodoPersona*& final, Persona p) {
    NodoPersona* nuevo = new NodoPersona; // crear nodo
    nuevo->per = p;                       // almacenar datos
    nuevo->sgte = NULL;                   // será el último

    if (frente == NULL) {                 // cola vacía
        frente = final = nuevo;           // frente y final apuntan al nuevo
    } else {
        final->sgte = nuevo;              // enlazar al último
        final = nuevo;                    // actualizar final
    }
}

// Desencola el primer elemento y lo devuelve en p; retorna true si hubo elemento
bool desencolar(NodoPersona*& frente, NodoPersona*& final, Persona &p) {
    if (frente == NULL) return false;    // cola vacía → nada que desencolar

    NodoPersona* borrar = frente;         // nodo a eliminar
    p = borrar->per;                      // copiar datos a p
    frente = borrar->sgte;                // avanzar frente

    if (frente == NULL) final = NULL;    // si quedó vacía, final también debe ser NULL

    delete borrar;                        // liberar memoria del nodo
    return true;                          // éxito
}

// --- ASIGNAR TURNOS ---

// Asigna turno a una persona en el departamento indicado si está libre
void asignarTurno(NodoDepartamento* lista, Persona p, int codigo) {
    NodoDepartamento* actual = lista; // iterador

    while (actual != NULL) {          // recorrer lista
        if (actual->datos.dep.codigo == codigo) { // si coincide el código

            if (strcmp(actual->datos.dep.estado, "alquilado") == 0) {
                // si está alquilado no se puede asignar turno
                cout << "El departamento " << codigo << " está alquilado. No se puede asignar turno." << endl;
                return;
            }

            // si está libre, encolar la persona en su cola
            encolar(actual->datos.frente, actual->datos.final, p);
            cout << "Turno asignado a " << p.nombre
                 << " para el departamento " << codigo << endl;
            return;
        }
        actual = actual->sgte; // avanzar al siguiente departamento
    }

    cout << "No se encontró el departamento con código " << codigo << endl; // no existe
}

// Intenta asignar un turno avanzado: si el depto está alquilado, busca otro libre del mismo tipo
void asignarTurnoAvanzado(NodoDepartamento* lista, Persona p, int codigo) {
    NodoDepartamento* actual = lista;           // iterador para encontrar el depto pedido
    NodoDepartamento* libreMismoTipo = NULL;    // posible alternativa

    while (actual != NULL) {
        if (actual->datos.dep.codigo == codigo) {

            if (strcmp(actual->datos.dep.estado, "libre") == 0) {
                // si está libre, encolar normalmente
                encolar(actual->datos.frente, actual->datos.final, p);
                cout << "Turno asignado a " << p.nombre
                     << " en el departamento " << codigo << endl;
                return;
            }

            // si está alquilado, buscar otra sección del mismo tipo que esté libre
            NodoDepartamento* aux = lista; // recorrer desde el inicio
            while (aux != NULL) {
                if (strcmp(aux->datos.dep.tipo, actual->datos.dep.tipo) == 0 &&
                    strcmp(aux->datos.dep.estado, "libre") == 0) {
                    libreMismoTipo = aux; // encontramos alternativa
                    break;
                }
                aux = aux->sgte; // avanzar
            }

            if (libreMismoTipo != NULL) {
                // se encontró alternativa: encolar allí
                encolar(libreMismoTipo->datos.frente, libreMismoTipo->datos.final, p);
                cout << "El departamento " << codigo << " está alquilado.\n";
                cout << "Se asignó turno en otro libre del mismo tipo: "
                     << libreMismoTipo->datos.dep.codigo << endl;
                return;
            } else {
                // no hay alternativa → informar
                cout << "El departamento " << codigo << " está alquilado y no hay otro libre del mismo tipo.\n";
                cout << "No se pudo asignar turno a " << p.nombre << ".\n";
                return;
            }
        }
        actual = actual->sgte; // avanzar
    }

    cout << "No se encontró el departamento con código " << codigo << endl; // no existe
}

// --- VACIAR COLAS ---

// Libera todos los nodos de una cola
void vaciarCola(NodoPersona*& frente, NodoPersona*& final) {
    NodoPersona* actual = frente; // empezar por el frente
    while (actual != NULL) {
        NodoPersona* borrar = actual; // guardar nodo a borrar
        actual = actual->sgte;       // avanzar
        delete borrar;               // liberar memoria
    }
    frente = final = NULL;         // indicar cola vacía
}

// Vacía las colas de todos los departamentos en la lista
void vaciarTodosLosTurnos(NodoDepartamento* lista) {
    NodoDepartamento* actual = lista;       // iterador sobre departamentos
    while (actual != NULL) {
        vaciarCola(actual->datos.frente, actual->datos.final); // vacía la cola del depto
        actual = actual->sgte; // siguiente depto
    }
    cout << "Se vaciaron todos los turnos de todos los departamentos." << endl; // mensaje final
}

// --- ATENDER TURNOS ---

// Atiende los turnos en orden FIFO para un departamento
void atenderTurnos(NodoDepartamento* lista, int codigo) {
    NodoDepartamento* actual = lista; // buscar departamento

    while (actual != NULL) {
        if (actual->datos.dep.codigo == codigo) { // si coincide el código
            NodoPersona*& frente = actual->datos.frente; // referencia al frente de la cola
            NodoPersona*& final = actual->datos.final;   // referencia al final

            if (frente == NULL) { // si no hay turnos
                cout << "No hay turnos para el departamento " << codigo << ".\n";
                return; // terminar
            }

            cout << "Atendiendo turnos del departamento " << codigo
                 << " (" << actual->datos.dep.tipo << ")\n"; // información

            Persona p; // variable temporal para desencolar
            while (desencolar(frente, final, p)) { // desencolar uno por uno
                cout << "Cliente: " << p.nombre
                     << " - Tel: " << p.telefono << endl; // mostrar datos cliente
                cout << "¿Desea alquilar este departamento? (s/n): ";
                char resp;
                cin >> resp; // leer respuesta

                if (resp == 's' || resp == 'S') {
                    strcpy(actual->datos.dep.estado, "alquilado"); // marcar como alquilado
                    cout << "El departamento " << codigo
                         << " fue alquilado por " << p.nombre << ".\n";

                    vaciarCola(frente, final); // eliminar el resto de la cola
                    return; // terminar atención
                } else {
                    cout << "No aceptó, pasando al siguiente turno...\n"; // continuar
                }
            }

            cout << "Se atendieron todos los turnos y nadie aceptó.\n"; // si nadie aceptó
            return; // terminar
        }
        actual = actual->sgte; // avanzar al siguiente departamento
    }

    cout << "No se encontró el departamento con código " << codigo << endl; // si no existe
}

// --- MAIN de prueba ---
int main() {
    NodoDepartamento* lista = CargarLista(); // carga la lista simulada de departamentos

    // crear personas de ejemplo
    Persona p1 = {"Juan Perez", "123456789"};
    Persona p2 = {"Maria Lopez", "987654321"};
    Persona p3 = {"Carlos Diaz", "555555555"};

    // asignar turnos (usa la función avanzada que busca alternativas si el solicitado está alquilado)
    asignarTurnoAvanzado(lista, p1, 1023);
    asignarTurnoAvanzado(lista, p2, 1024);
    asignarTurnoAvanzado(lista, p3, 1025);

    // atender turnos del depto 1023 (simulación de diálogo con el usuario)
    atenderTurnos(lista, 1023);

    // al final, vaciar todas las colas para liberar la memoria
    vaciarTodosLosTurnos(lista);

    return 0; // fin del programa
}
