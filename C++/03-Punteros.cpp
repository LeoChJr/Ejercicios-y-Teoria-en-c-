#include <iostream>
#include <cstdlib>
using namespace std;

struct Alumno{
    string nombre;
    int edad;
};

int main(){
    Alumno juan;
    juan.nombre = "Juan";
    juan.edad = 20;
    int continuar;

    Alumno* punteroPersona = &juan; //El operador "&" obtiene la direccion de memoria de una variable

    cout <<"Direccion de memoria del objeto Alumno juan: " << punteroPersona << endl;
    cout << "Nombre: " << punteroPersona->nombre << endl;//Acceder a los miembros de una estructura a traves de un puntero
    cout << "Edad: " << punteroPersona->edad << endl;//Acceder a

    cout << "---------------------------------------------------------------------------------------------" << endl;
    cout<<"¿Que pasa si cambio el nombre de juan desde juan.nombre? Poner nuevo nombre:"<<endl;
    cin>>juan.nombre;
    cout<<"juan.nombre : "<<juan.nombre<<endl;//Acceder a los miembros de una estructura a traves de un puntero
    cout<<"punteroPersona->nombre :"<<punteroPersona->nombre<<endl;//Acceder a los miembros de una estructura a traves de un puntero
    //Ambos cambian porque punteroPersona apunta a la direccion de memoria de juan  
    
    cout << "---------------------------------------------------------------------------------------------" << endl;
    cout<<"¿Que pasa si cambio el nombre de juan desde punteroPersona->nombre? Poner nuevo nombre:"<<endl;
    cin>>punteroPersona->nombre;
    cout<<"juan.nombre : "<<juan.nombre<<endl;//Acceder a los miembros de una estructura a traves de un puntero
    cout<<"punteroPersona->nombre :"<<punteroPersona->nombre<<endl;//Acceder a los miembros de una estructura a traves de un puntero
    //Ambos cambian porque punteroPersona apunta a la direccion de memoria de juan
    
    cout << "---------------------------------------------------------------------------------------------" << endl;
    cout<<"Ahora llego un nuev amigo llamado carlos y tiene 30 años"<<endl;

    Alumno carlos;
    carlos.nombre = "Carlos";
    carlos.edad = 30;

    cout<<"¿Que oasa si cambio el puntero y le asigno la direccion de CARLOS?"<<endl;
    punteroPersona = &carlos; //El operador "&" obtiene la direccion de memoria de una variable         
    cout<<"punteroPersona = &carlos"<<endl;
    cout<<"Coloca un numero para continuar: ";
    cin>>continuar;
    
    cout<<"---------------------------------------------------------------------------------------------"<<endl;
    cout<<"juan.nombre :"<<juan.nombre<<endl;//Acceder a los miembros de una estructura a traves de un puntero
    cout<<"carlos.nombre :"<<carlos.nombre<<endl;//Acceder a los miembros de una estructura a traves de un puntero
    cout<<"punteroPersona->nombre :"<<punteroPersona->nombre<<endl;//Acc

    cout<<"-----------------------------------------------------------------------------"<<endl;
    cout<<"¿Como quedaron las direcciones? Coloca un numeor para continuar"<<endl;
    cin>>continuar;
    cout<<"&juan : "<<&juan<<endl;
    cout<<"&carlos : "<<&carlos<<endl;
    cout<<"punteroPersona : "<<punteroPersona<<endl;
    
    system("pause");
    return 0;
}