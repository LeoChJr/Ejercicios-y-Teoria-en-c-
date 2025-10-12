#include <iostream>
#include <cstdlib>
using namespace std;


//Estructura de tipo LISTA ENLAZADA SIMPLE
//Def:Cada elemento apunta al siguiente, formando una cadena
//Cuando conviene usarlo?
//Cuando no se conoce el numero de elementos a almacenar
//Cuando se requiere un uso eficiente de la memoria
//Cuando se necesita un acceso secuencial a los elementos

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

void imprimirListaSimple(Nodo* inicio){
    Nodo* actual = inicio; //Puntero temporal para recorrer la lista
    while(actual != NULL){ //Mientras no se llegue al final de la lista
        cout<<actual->dato<<" -> "; //Imprimir el dato del nodo actual
        actual = actual->siguiente; //Mover al siguiente nodo
    }
    cout<<"NULL"<<endl; //Indicar el final de la lista

}

//CARGA SIN RESTRICCIONES: Significa agregar nodos al final de la lista
Nodo* cargarLista(Nodo* inicio, int valor){
    Nodo* nuevoNodo = crearNodo(valor); //Crear un nuevo nodo
    if(inicio == NULL){ //Si la lista esta vacia
        return nuevoNodo; //El nuevo nodo es el inicio de la lista
    }else{
        Nodo* actual = inicio; //Puntero temporal para recorrer la lista
        while(actual->siguiente != NULL){ //Recorrer hasta el final de la lista
            actual = actual->siguiente; //Mover al siguiente nodo
        }
        actual->siguiente = nuevoNodo; //Enlazar el nuevo nodo al final de la lista
    }
    return inicio; //Retornar el inicio de la lista
}

//CARGA SIN REPETIR:Significa agregar nodos al final de la lista sin repetir valores
bool existeElemento(Nodo* inicio, int valor){
    Nodo* actual = inicio; //Puntero temporal para recorrer la lista
    while(actual != NULL){ //Mientras no se llegue al final de la lista
        if(actual->dato == valor){ //Si el valor ya existe en la lista
            return true; //Retornar true
        }
        actual = actual->siguiente; //Mover al siguiente nodo
    }   
    return false; //Retornar false si no se encontro el valor
}


Nodo* cargarSinRepetir(Nodo* inicio, int valor){
    if(!existeElemento(inicio, valor)){ //Si el valor no existe en la lista
        return cargarLista(inicio, valor); //Agregar el valor a la lista
    }
    return inicio; //Retornar el inicio de la lista sin cambios
}

//Busqueda: Significa buscar un elemento en una lista enlazada simple implica recorrer la lista para encontrar el valor deseado

Nodo* buscarElemento(Nodo* inicio, int valor){
    Nodo* actual = inicio; //Puntero temporal para recorrer la lista
    while(actual != NULL){ //Mientras no se llegue al final de la lista
        if(actual->dato == valor){ //Si se encontro el valor
            return actual; //Retornar el nodo que contiene el valor
        }
        actual = actual->siguiente; //Mover al siguiente nodo
    }
    return NULL; //Retornar NULL si no se encontro el valor
}

//Recorrido:Significa visitar cada elemento de la lista y realizar algun accion ,como mostar su valor
void recorrerLista(Nodo* inicio){
    Nodo* actual = inicio; //Puntero temporal para recorrer la lista
    while(actual != NULL){ //Mientras no se llegue al final de la lista
        cout<<actual->dato<<" "; //Imprimir el dato del nodo actual
        actual = actual->siguiente; //Mover al siguiente nodo
    }
    cout<<endl; //Nueva linea al finalizar el recorrido
}

//Eliminar de nodos: Significa eliminar un elemento especifico de la lista
Nodo* eliminarElemento(Nodo* inicio, int valor){
    if(inicio == NULL){ //Si la lista esta vacia
        return NULL; //Retornar NULL
    }
    if(inicio->dato == valor){ //Si el valor a eliminar es el primer nodo
        Nodo* temp = inicio; //Guardar el nodo a eliminar en una variable temporal
        inicio = inicio->siguiente; //Actualizar el inicio al siguiente nodo
        delete temp; //Liberar memoria del nodo eliminado
        return inicio; //Retornar el nuevo inicio de la lista
    }
    Nodo* actual = inicio; //Puntero temporal para recorrer la lista
    while(actual->siguiente != NULL ){ //Recorrer hasta encontrar el valor o llegar al final
        if(actual->siguiente->dato == valor){ //Si se encontro el valor
            Nodo* temp  = actual->siguiente; //Guardar el nodo a eliminar en una variable temporal
            actual->siguiente = actual->siguiente->siguiente; //Actualizar el enlace para saltar el nodo eliminado
            delete temp; //Liberar memoria del nodo eliminado
            return inicio; //Retornar el inicio de la lista
        }
        actual = actual->siguiente; //Mover al siguiente nodo
    }
    return inicio; //Retornar el inicio de la lista si no se encontro el valor
}

//Otra funcion:(Insertar ordenado)
Nodo* insertarOrdenado(Nodo* inicio, int valor){
    Nodo* nuevoNodo = crearNodo(valor); //Crear un nuevo nodo
    if(inicio == NULL || valor < inicio ->dato){ //Si la lista esta vacia o el nuevo valor es menor que el primer nodo
        nuevoNodo->siguiente = inicio; //El siguiente del nuevo nodo es el inicio actual
        inicio = nuevoNodo; //Actualizar el inicio al nuevo nodo
        return inicio; //El nuevo nodo es el nuevo inicio de la lista
    }
    Nodo* actual = inicio; //Puntero temporal para recorrer la lista
    while(actual->siguiente != NULL && actual->siguiente->dato < valor){ //Recorrer hasta encontrar la posicion correcta
        actual = actual->siguiente; //Mover al siguiente nodo
    }
    nuevoNodo->siguiente = actual->siguiente; //Enlazar el nuevo nodo al siguiente del nodo actual
    actual->siguiente = nuevoNodo; //Enlazar el nodo actual al nuevo nodo
    return inicio; //Retornar el inicio de la lista

}

int main(){

    Nodo* listaSimple = crearNodo(10); //Crear el primer nodo
    listaSimple->siguiente = crearNodo(20); //Crear el segundo nodo y enlazarlo al primero
    listaSimple->siguiente->siguiente = crearNodo(30); //Crear el tercer nodo y enlazarlo al segundo
    cout<<"Lista Simple: "<<endl;
    imprimirListaSimple(listaSimple); //Imprimir la lista simple
    delete listaSimple->siguiente->siguiente; //Liberar memoria del tercer nodo
    delete listaSimple->siguiente; //Liberar memoria del segundo nodo
    delete listaSimple; //Liberar memoria del primer nodo


    cout<<"----------------------------------------------------------------------"<<endl;

    cout<<"Cargando lista sin restricciones: "<<endl;
    Nodo* listaCarga = NULL; //Inicializar la lista como vacia
    listaCarga = cargarLista(listaCarga, 10);
    listaCarga = cargarLista(listaCarga, 20);
    listaCarga = cargarLista(listaCarga, 30);
    listaCarga = cargarLista(listaCarga, 20); //Intento de agregar un valor repetido
    imprimirListaSimple(listaCarga); //Imprimir la lista cargada
    //Liberar memoria de la lista cargada
    while(listaCarga != NULL){
        Nodo* temp = listaCarga;
        listaCarga = listaCarga->siguiente;
        delete temp;
    }
    cout<<"----------------------------------------------------------------------"<<endl;
    cout<<"Cargando lista sin repetir: "<<endl;
    Nodo* listaSinRepetir = NULL; //Inicializar la lista como vacia
    listaSinRepetir = cargarSinRepetir(listaSinRepetir, 10);
    listaSinRepetir = cargarSinRepetir(listaSinRepetir, 20);
    listaSinRepetir = cargarSinRepetir(listaSinRepetir, 30);
    listaSinRepetir = cargarSinRepetir(listaSinRepetir, 20); //Intento de agregar un valor repetido
    imprimirListaSimple(listaSinRepetir); //Imprimir la lista cargada sin repetir
    //Liberar memoria de la lista cargada sin repetir
    while(listaSinRepetir != NULL){
        Nodo* temp = listaSinRepetir;
        listaSinRepetir = listaSinRepetir->siguiente;
        delete temp;
    }

    cout<<"----------------------------------------------------------------------"<<endl;
    cout<<"Busqueda de un elemento en la lista: "<<endl;
    Nodo* listaBusqueda = NULL; //Inicializar la lista como vacia
    listaBusqueda = cargarLista(listaBusqueda, 10);
    listaBusqueda = cargarLista(listaBusqueda, 20);
    listaBusqueda = cargarLista(listaBusqueda, 30);
    int valorBuscado = 20;
    Nodo* resultado = buscarElemento(listaBusqueda, valorBuscado); //Buscar el elemento en la lista
    if(resultado != NULL){
        cout<<"Elemento "<<valorBuscado<<" encontrado en la lista."<<endl;
    }else{
        cout<<"Elemento "<<valorBuscado<<" no encontrado en la lista."<<endl;
    }
    //Liberar memoria de la lista de busqueda
    while(listaBusqueda != NULL){
        Nodo* temp = listaBusqueda;
        listaBusqueda = listaBusqueda->siguiente;
        delete temp;
    }
    cout<<"----------------------------------------------------------------------"<<endl;
    cout<<"Recorrido de la lista: "<<endl;
    Nodo* listaRecorrido = NULL; //Inicializar la lista como vacia
    listaRecorrido = cargarLista(listaRecorrido, 10);
    listaRecorrido = cargarLista(listaRecorrido, 20);
    listaRecorrido = cargarLista(listaRecorrido, 30);
    recorrerLista(listaRecorrido); //Recorrer e imprimir la lista
    //Liberar memoria de la lista de recorrido
    while(listaRecorrido != NULL){
        Nodo* temp = listaRecorrido;
        listaRecorrido = listaRecorrido->siguiente;
        delete temp;
    }
    cout<<"----------------------------------------------------------------------"<<endl;
    cout<<"Eliminacion de un elemento en la lista: "<<endl;
    Nodo* listaEliminacion = NULL; //Inicializar la lista como vacia
    listaEliminacion = cargarLista(listaEliminacion, 10);
    listaEliminacion = cargarLista(listaEliminacion, 20);
    listaEliminacion = cargarLista(listaEliminacion, 30);
    cout<<"Lista antes de la eliminacion: "<<endl;
    imprimirListaSimple(listaEliminacion); //Imprimir la lista antes de la eliminacion
    listaEliminacion = eliminarElemento(listaEliminacion, 20); //Eliminar el
    cout<<"Lista despues de eliminar el elemento 20: "<<endl;
    imprimirListaSimple(listaEliminacion); //Imprimir la lista despues de la eliminacion
    //Liberar memoria de la lista de eliminacion
    while(listaEliminacion != NULL){
        Nodo* temp = listaEliminacion;
        listaEliminacion = listaEliminacion->siguiente;
        delete temp;
    }
    cout<<"----------------------------------------------------------------------"<<endl;
    cout<<"Insercion ordenada en la lista: "<<endl;
    Nodo* listaOrdenada = NULL; //Inicializar la lista como vacia
    listaOrdenada = insertarOrdenado(listaOrdenada, 30);
    listaOrdenada = insertarOrdenado(listaOrdenada, 10);
    listaOrdenada = insertarOrdenado(listaOrdenada, 20);
    listaOrdenada = insertarOrdenado(listaOrdenada, 25);
    cout<<"Lista despues de inserciones ordenadas: "<<endl;
    imprimirListaSimple(listaOrdenada); //Imprimir la lista despues de las inserciones orden
    //Liberar memoria de la lista ordenada
    while(listaOrdenada != NULL){
        Nodo* temp = listaOrdenada;
        listaOrdenada = listaOrdenada->siguiente;
        delete temp;
    }
    cout<<"----------------------------------------------------------------------"<<endl;
    


    system("pause");
    return 0;
}