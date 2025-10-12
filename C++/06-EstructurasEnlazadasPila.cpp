// Implementacion de una pila usando estructuras enlazadas en C++
//Definicion de la estructura del nodo y funciones para operar la pila
//El ultimo elemento en entrar es el primero en salir (LIFO - Last In First Out)
//Cuando conviene usarlo?
//Cuando no se conoce el numero de elementos a almacenar
//Cuando se requiere un uso eficiente de la memoria
//Cuando se necesita un acceso rapido al ultimo elemento agregado


#include <iostream>
#include <cstdlib>
using namespace std;

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

void push(Nodo*& pila , int valor){//Agregar un elemento a la pila
    Nodo* nuevoNodo = crearNodo(valor); //Crear un nuevo nodo
    nuevoNodo->siguiente = pila; //El siguiente del nuevo nodo es la pila actual
    pila = nuevoNodo; //La pila ahora es el nuevo nodo
    cout<<"Elemento "<<valor<<" agregado a la pila"<<endl;
}

int pop(Nodo*& pila){
    if(pila == NULL){
        cout<<"La pila esta vacia"<<endl;
        return -1; //Valor que indica que la pila esta vacia
    }

    int valor = pila->dato;//Obtener el valor del nodo superior
    Nodo* temp = pila;//Guardar el nodo superior en una variable temporal
    pila = pila->siguiente;//Actualizar la pila al siguiente nodo
    delete temp; //Liberar memoria del nodo eliminado
    return valor;
}

bool isEmpty(Nodo* pila){
    return pila == NULL; //Retorna true si la pila esta vacia
}


int main(){
    Nodo* pila = NULL; //Inicializar la pila como vacia

    push(pila, 10);
    push(pila, 20);
    push(pila, 30);

    cout<<"Elementos en la pila: "<<endl;
    while(!isEmpty(pila)){
        int valor = pop(pila);
        cout<<valor<<endl;
    }
    system("pause");
    return 0;
}