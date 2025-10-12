#include <iostream>
#include <cstdlib>
using namespace std;

//Estructura de tipo COLA
//Def:El primer elemento en entrar es el primero en salir (FIFO - First In First Out)
//Cuando conviene usarlo?
//Cuando no se conoce el numero de elementos a almacenar
//Cuando se requiere un uso eficiente de la memoria
//Cuando se necesita un acceso rapido al primer elemento agregado

struct Nodo{
    int dato;
    Nodo* siguiente; //Puntero que apunta al siguiente nodo 
};

Nodo* crearNodo(int valor){
    Nodo* nuevoNodo = new Nodo; //Crear un nuevo nodo en memoria dinamica
    nuevoNodo->dato = valor; //Asignar el valor al nodo
    nuevoNodo->siguiente = NULL; //El siguiente nodo es NULL por defecto
    return nuevoNodo; //Retornar el nuevo nodo
}

void encolar(Nodo*& frente, Nodo*& final, int valor){//Agregar un elemento a la cola
    Nodo* nuevoNodo = crearNodo(valor); //Crear un nuevo nodo
    if(final == NULL){ //Si la cola esta vacia
        frente = final = nuevoNodo; //El frente es el nuevo nodo
    }else{
        final->siguiente = nuevoNodo; //El siguiente del final es el nuevo nodo
    }
    final -> siguiente = nuevoNodo; //El final ahora es el nuevo nodo
    final = nuevoNodo;
    cout<<"Elemento "<<valor<<" agregado a la cola"<<endl;

}

int desencolar(Nodo*& frente, Nodo*& final){//Eliminar un elemento de la cola
    if(frente == NULL){
        cout<<"La cola esta vacia"<<endl;
        return -1; //Valor que indica que la cola esta vacia
    }

    int valor = frente->dato; //Obtener el valor del nodo frontal
    Nodo* temp = frente; //Guardar el nodo frontal en una variable temporal
    frente = frente->siguiente; //Actualizar el frente al siguiente nodo

    if(frente == NULL){ //Si la cola queda vacia
        final = NULL; //El final tambien es NULL
    }

    delete temp; //Liberar memoria del nodo eliminado
    return valor;
}

bool isEmpty(Nodo* frente){
    return frente == NULL; //Retorna true si la cola esta vacia
}


int main(){
    Nodo* frente = NULL; //Inicializar el frente como NULL
    Nodo* final = NULL; //Inicializar el final como NULL

    encolar(frente, final, 10);
    encolar(frente, final, 20);
    encolar(frente, final, 30);

    cout<<"Elementos en la cola: "<<endl;
    while(!isEmpty(frente)){
        int valor = desencolar(frente, final);
        cout<<valor<<endl;
    }
    system("pause");
    return 0;
}
