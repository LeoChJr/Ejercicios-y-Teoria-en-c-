// //Enunciado:  1. Organización de libros en una biblioteca
//  En una biblioteca, tu tarea es organizar los libros que van llegando. Cada libro nuevo que llega debe colocarse 
//  encima de los libros anteriores. Si alguien solicita un libro, debes entregar el que se encuentra en la parte superior 
//  de la pila de libros. De cada libro se conoce su titulo y su escritor. Realiza un programa que permita:
//  -Agregar libros a la pila de libros.
//  -Mostrar el titulo del libro más reciente (el que está en la parte superior).
//  -Retirar el libro más reciente (el que está en la parte superior).
//  -Retirar todos los libros mostrando sus títulos y autores

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

struct Libro{
    string titulo;
    string escritor;
    Libro* siguiente;
};

//Agregar libros a la pila de libros
Libro* crear(string titulo, string escritor){
    Libro* nuevoLibro = new Libro;
    nuevoLibro->titulo = titulo;
    nuevoLibro->escritor = escritor;
    nuevoLibro->siguiente = NULL;
    return nuevoLibro;
}

//Mostrar el titulo del libro más reciente (el que está en la parte superior)
void mostrarPush(Libro*& pila, string titulo, string escritor){
    Libro* nuevoLibro = crear(titulo,escritor);
    nuevoLibro->siguiente=pila;
    pila=nuevoLibro;
    cout<<"Libro agregado: "<<titulo<<" de "<<escritor<<endl;
}

//Retirar el libro más reciente (el que está en la parte superior)
void retirarPop(Libro*& pila){
    if(pila == NULL){
        cout<<"La pila esta vacia"<<endl;
        return; //Valor que indica que la pila esta vacia
    }

    Libro* temp = pila;//Guardar el nodo superior en una variable temporal
    cout<<"Se retiro el libro: "<<temp->titulo<<" de "<<temp->escritor<<endl;
    pila = pila->siguiente;//Actualizar la pila al siguiente nodo
    delete temp; 
}

//Retirar todos los libros mostrando sus títulos y autores
void mostrarTodos(Libro*& pila){
    if(pila == NULL){
        cout<<"La pila esta vacia"<<endl;
        return; //Valor que indica que la pila esta vacia
    }

    cout<<"Retirando todos los libros: "<<endl;
    while(pila != NULL){
        Libro* temp = pila;//Guardar el nodo superior en una variable temporal
        cout<<"Libro: "<<temp->titulo<<" de "<<temp->escritor<<endl;//Obtener el valor del nodo superior
        pila = pila->siguiente;//Actualizar la pila al siguiente nodo
        delete temp; //Liberar memoria del nodo eliminado
    }
}

int main(){

    Libro* pila = NULL; //Inicializar la pila como vacia
    mostrarPush(pila, "Cien Años de Soledad", "Gabriel Garcia Marquez");
    mostrarPush(pila, "1984", "George Orwell");
    mostrarPush(pila, "Don Quijote de la Mancha", "Miguel de Cervantes");
    retirarPop(pila);
    mostrarTodos(pila);

    
    system("pause");
    return 0;

}