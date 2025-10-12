#include <iostream>
#include <cstdlib>
using namespace std;

struct Alumno{
    string nombre;
    int edad;
};
//Recordar esto: 
//el operador "&" se utiliza para obtener la direccion de memoria de una variable
//Y el operador "*" se utiliza para acceder al valor almacenado en una direccion de memoria

// int main(){
//     Alumno* alumnoDinamico;
//     alumnoDinamico = new Alumno; 

//     alumnoDinamico->nombre = "Juan";//Acceder a los miembros de una estructura a traves de un puntero
//     alumnoDinamico->edad = 20;//Acceder a los miembros de una estructura a traves de un puntero

//     cout << "Nombre: " << alumnoDinamico->nombre << endl;//Acceder a los miembros de una estructura a traves de un puntero
//     cout << "Edad: " << alumnoDinamico->edad << endl;//Acceder a los miembros de una estructura a traves de un puntero

//     delete alumnoDinamico; //Liberar memoria
//     system("pause");
//     return 0;
// }


int main(){
    Alumno juan;
    juan.nombre = "Juan";
    juan.edad = 20;

    Alumno* punteroJuan = &juan; //El operador "&" obtiene la direccion de memoria de una variable

    cout <<"Direccion de memoria del objeto Alumno juan: " << punteroJuan << endl;
    cout << "Nombre: " << punteroJuan->nombre << endl;//Acceder a los miembros de una estructura a traves de un puntero
    cout << "Edad: " << punteroJuan->edad << endl;//Acceder a los miembros de una estructura a traves de un puntero
    
    delete punteroJuan; 
    system("pause");
    return 0;

}
