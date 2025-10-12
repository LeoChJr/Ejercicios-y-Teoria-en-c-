//Enunciado :  2. Sistema de atención de clientes en un supermercado
// En el supermercado "SuperCode", los clientes deben esperar su turno en una fila para ser atendidos. En esta fila 
// virtual, los clientes solo registran su nombre y se sientan a esperar ser atendidos. El cliente que llega primero 
// debe ser atendido antes que los demás. Escribe un programa que:
//  - Permita registrar clientes.
//  - Muestre el nombre del próximo cliente a ser atendido.
//  - Atienda clientes, mostrando su nombre y eliminándolo.

#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

struct Cliente{
    string nombre;
    Cliente* siguiente;
};

//Crear un nuevo cliente
Cliente* crearCliente(string nombre){
    Cliente* nuevoCliente = new Cliente;
    nuevoCliente->nombre = nombre;
    nuevoCliente->siguiente = NULL;
    return nuevoCliente;
}

//Registar al cliente en la fila
void encolarCliente(Cliente*& frente, Cliente*& final, string nombre){
    Cliente* nuevoCliente = crearCliente(nombre);
    if(final == NULL){ //Si la cola esta vacia
        frente = final = nuevoCliente; //El frente es el nuevo nodo
    }else{
        final->siguiente = nuevoCliente; //El siguiente del final es el nuevo nodo
    }
    final -> siguiente = nuevoCliente; //El final ahora es el nuevo nodo
    final = nuevoCliente;
    cout<<"Cliente "<<nombre<<" registrado en la fila"<<endl;
}

//Muestre el nombre del próximo cliente a ser atendido
void mostrarProximo(Cliente* frente){
    if(frente == NULL){
        cout<<"No hay clientes en la fila"<<endl;
        return;
    }
    cout<<"El proximo cliente a ser atendido es: "<<frente->nombre<<endl;
}   


//Atienda clientes, mostrando su nombre y eliminándolo
void atenderCliente(Cliente*& frente, Cliente*& final){
    if(frente == NULL){
        cout<<"No hay clientes en la fila"<<endl;
        return; //Valor que indica que la cola esta vacia
    }

    string nombre = frente->nombre; //Obtener el nombre del cliente frontal
    Cliente* temp = frente; //Guardar el nodo frontal en una variable temporal
    frente = frente->siguiente; //Actualizar el frente al siguiente nodo

    if(frente == NULL){ //Si la cola queda vacia
        final = NULL; //El final tambien es NULL
    }

    delete temp; //Liberar memoria del nodo eliminado
    cout<<"Atendiendo al cliente: "<<nombre<<endl;

}


int main(){
    Cliente* frente = NULL; //Inicializar el frente como NULL
    Cliente* final = NULL; //Inicializar el final como NULL

    encolarCliente(frente, final, "Juan");
    encolarCliente(frente, final, "Maria");
    encolarCliente(frente, final, "Pedro");
    mostrarProximo(frente);
    atenderCliente(frente, final);
    mostrarProximo(frente);
    atenderCliente(frente, final);
    mostrarProximo(frente);
    atenderCliente(frente, final);
    mostrarProximo(frente);
    atenderCliente(frente, final);
    
    system("pause");
    return 0;
}

