// Enunciado: Sistema de tramitación de clientes
// En una oficina de trámites, los clientes se dividen en dos grupos según la rapidez con la que pueden resolver su 
// trámite. Los que tienen trámites rápidos deben ser atendidos antes de los que tienen trámites largos, pero estos 
// últimos ingresan antes en el sistema. Crea un programa que permita:
//  - Ingresar clientes que serán clasificados como de trámite rápido o lento.
//  - Atender a 5 clientes de cada grupo.
//  - Mostrar cuántos clientes quedan sin atender en cada grupo.



#include <iostream>
#include <cstdlib>
using namespace std;
struct Cliente{
    int id;
    string tipo; // "rapido" o "lento"
    Cliente* siguiente;
};
Cliente* crearCliente(int id, string tipo){
    Cliente* nuevoCliente = new Cliente;
    nuevoCliente->id = id;
    nuevoCliente->tipo = tipo;
    nuevoCliente->siguiente = NULL;
    return nuevoCliente;
}

// Función para agregar un cliente a la cola correspondiente
void encolarCliente(Cliente*& frente, Cliente*& final, int id, string tipo){
    Cliente* nuevoCliente = crearCliente(id, tipo);
    if(final == NULL){ // Si la cola está vacía
        frente = final = nuevoCliente;
    }else{
        final->siguiente = nuevoCliente; // Enlazar el nuevo cliente al final de la cola
        final = nuevoCliente; // Actualizar el final de la cola
    }
    cout<<"Cliente "<<id<<" de tipo "<<tipo<<" agregado a la cola."<<endl;
}
// Función para atender a un cliente de la cola
void atenderCliente(Cliente*& frente, Cliente*& final){
    if(frente == NULL){ // Si la cola está vacía
        cout<<"No hay clientes para atender."<<endl;
        return;
    }
    Cliente* temp = frente; // Guardar el cliente que será atendido
    cout<<"Atendiendo al cliente "<<temp->id<<" de tipo "<<temp->tipo<<endl;
    frente = frente->siguiente; // Actualizar el frente de la cola
    if(frente == NULL){ // Si la cola queda vacía después de atender
        final = NULL;
    }
    delete temp; // Liberar memoria del cliente atendido
}
// Función para contar cuántos clientes quedan en la cola
int contarClientes(Cliente* frente){
    int contador = 0;
    Cliente* actual = frente;
    while(actual != NULL){
        contador++;
        actual = actual->siguiente;
    }
    return contador;
}



int main(){
    Cliente* frenteRapido = NULL; // Frente de la cola de clientes rápidos
    Cliente* finalRapido = NULL; // Final de la cola de clientes rápidos
    Cliente* frenteLento = NULL; // Frente de la cola de clientes lentos
    Cliente* finalLento = NULL; // Final de la cola de clientes lentos

    // Ingresar clientes
    encolarCliente(frenteRapido, finalRapido, 1, "rapido");
    encolarCliente(frenteLento, finalLento, 2, "lento");
    encolarCliente(frenteRapido, finalRapido, 3, "rapido");
    encolarCliente(frenteLento, finalLento, 4, "lento");
    encolarCliente(frenteRapido, finalRapido, 5, "rapido");
    encolarCliente(frenteLento, finalLento, 6, "lento");
    encolarCliente(frenteRapido, finalRapido, 7, "rapido");
    encolarCliente(frenteLento, finalLento, 8, "lento");
    encolarCliente(frenteRapido, finalRapido, 9, "rapido");
    encolarCliente(frenteLento, finalLento, 10, "lento");
    encolarCliente(frenteRapido, finalRapido, 11, "rapido");
    encolarCliente(frenteLento, finalLento, 12, "lento");


    // Atender a 5 clientes de cada grupo
    cout<<"Atendiendo a clientes rapidos:"<<endl;
    for(int i=0; i<5; i++){
        atenderCliente(frenteRapido, finalRapido);
    }
    cout<<"Atendiendo a clientes lentos:"<<endl;
    for(int i=0; i<5; i++){
        atenderCliente(frenteLento, finalLento);
    }

    // Mostrar cuántos clientes quedan sin atender en cada grupo
    int restantesRapidos = contarClientes(frenteRapido);
    int restantesLentos = contarClientes(frenteLento);
    cout<<"Clientes rapidos restantes sin atender: "<<restantesRapidos<<endl;
    cout<<"Clientes lentos restantes sin atender: "<<restantesLentos<<endl;

    // Liberar memoria restante
    while(frenteRapido != NULL){
        atenderCliente(frenteRapido, finalRapido);
    }
    while(frenteLento != NULL){
        atenderCliente(frenteLento, finalLento);
    }  
    system("pause");
    return 0;
}