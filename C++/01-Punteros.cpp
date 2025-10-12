//Punteros en c++
//Trabajan directamente con la memoria
//Def: Almacena la direccion de memoria de otra variable
// y los declarammos con "*"
#include <iostream>
#include <cstdlib>
using namespace std;
int main(){
    // int* p_numero = new int;
    // *p_numero = 10;
    // int numero = 20;

    // cout << "Valor de p_numero: " << *p_numero << endl;//10
    // cout << "Direccion de memoria de p_numero: " << p_numero << endl;//depende de la ejecucion

    // cout << "Valor de numero: " << numero << endl;//20

    int numero = 10;
    int* p_numero = &numero; //El operador "&" obtiene la direccion de memoria de una variable

    cout << "Valor de numero: " << numero << endl; 
    cout <<"Direccion de numero wasa: " << &numero << endl;
    cout << "Valor de p_numero: " << p_numero << endl;
    cout <<"Valor apuntado por p_numero: " << *p_numero << endl;
    system("pause");
    return 0;
}
//Como poner en comentario todo un bloque de codigo
//Seleccionar el bloque y presionar "Ctrl + K + C" para comentar
//Seleccionar el bloque y presionar "Ctrl + K + U" para descomentar