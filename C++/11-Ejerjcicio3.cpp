// //Enunciado: Gestión de empleados de una empresa
// Una empresa almacena la información de sus empleados en un archivo, donde cada empleado tiene un número 
// de identificación único. El programa debe leer la información del archivo y realizar lo siguiente:
//  - Insertar los empleados en una lista ordenada por número de identificación.
//  - Mostrar la lista de empleados.
//  - Eliminar un empleado cuyo número de identificación es ingresado por el usuario.
//  - Mostrar nuevamente la lista con los empleados restantes

#include <iostream>
#include <cstdlib>
using namespace std;

struct Empleado{
    int id;
    Empleado* siguiente;
};


Empleado* crearEmpleado(int id){
    Empleado* nuevoEmpleado = new Empleado;
    nuevoEmpleado->id = id;
    nuevoEmpleado->siguiente = NULL;
    return nuevoEmpleado;
}

//Insertar ordenado
Empleado* insertarEmpleadoOrdenado(Empleado* inicio,int id){
    Empleado* nuevoEmpleado = crearEmpleado(id);
    if(inicio == NULL || id < inicio->id){
        nuevoEmpleado->siguiente = inicio;
        inicio = nuevoEmpleado;
        return inicio;
    }
    Empleado* actual = inicio;
    while(actual->siguiente != NULL && actual->siguiente->id < id){
        actual = actual->siguiente;
    }
    nuevoEmpleado->siguiente = actual->siguiente;
    actual->siguiente = nuevoEmpleado;
    return inicio;
}

//Mostrar la lista de empleados
void mostrarEmpleados(Empleado* inicio){
    Empleado* actual = inicio;
    while(actual != NULL){
        cout<<actual->id<<" -> ";
        actual = actual->siguiente;
    }
    cout<<"NULL"<<endl;
}

//Eliminar un empleado por id
Empleado* eliminarEmpleado(Empleado* inicio, int id){
    if(inicio == NULL){
        return NULL;
    }
    if(inicio->id == id){
        Empleado* temp = inicio;
        inicio = inicio->siguiente;
        delete temp;
        return inicio;
    }
    Empleado* actual = inicio;
    while(actual->siguiente != NULL){
        if(actual->siguiente->id == id){
            Empleado* temp = actual->siguiente;
            actual->siguiente = actual->siguiente->siguiente;
            delete temp;
            return inicio;
        }
        actual = actual->siguiente;
    }
    return inicio;
}

//Mostrar nuevamente la lista con los empleados restantes
void mostrarEmpleadosRestantes(Empleado* inicio){
    mostrarEmpleados(inicio);
}


int main(){
    Empleado* listaEmpleados = NULL; //Inicializar la lista como vacia
    listaEmpleados = insertarEmpleadoOrdenado(listaEmpleados, 103);
    listaEmpleados = insertarEmpleadoOrdenado(listaEmpleados, 101);
    listaEmpleados = insertarEmpleadoOrdenado(listaEmpleados, 105);
    listaEmpleados = insertarEmpleadoOrdenado(listaEmpleados, 102);
    listaEmpleados = insertarEmpleadoOrdenado(listaEmpleados, 104);

    cout<<"Lista de empleados: "<<endl;
    mostrarEmpleados(listaEmpleados);

    int idAEliminar;
    cout<<"Ingrese el ID del empleado a eliminar: ";
    cin>>idAEliminar;
    listaEmpleados = eliminarEmpleado(listaEmpleados, idAEliminar);

    cout<<"Lista de empleados restantes: "<<endl;
    mostrarEmpleadosRestantes(listaEmpleados);

    //Liberar memoria de la lista de empleados
    while(listaEmpleados != NULL){
        Empleado* temp = listaEmpleados;
        listaEmpleados = listaEmpleados->siguiente;
        delete temp;
    }
    system("pause");

    return 0;
}