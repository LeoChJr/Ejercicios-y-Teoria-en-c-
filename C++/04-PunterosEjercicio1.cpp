#include <iostream>
#include <cstdlib>
using namespace std;

int intercambio(int* puntero1, int* puntero2){
    int aux;//Variable temporal
    aux = *puntero1;//Guardar el valor apuntado por puntero1
    *puntero1 = *puntero2;//Asignar a puntero1 el valor apuntado por puntero2
    *puntero2 = aux;//Asignar a puntero2 el valor guardado en aux
    return 0;

}

int main(){

    int p1=10;
    int p2=20;    

    cout<<"Antes del intercambio: "<<endl;
    cout<<"p1: "<<p1<<endl;
    cout<<"p2: "<<p2<<endl;
    intercambio(&p1,&p2);
    cout<<"Despues del intercambio: "<<endl;
    cout<<"p1: "<<p1<<endl;
    cout<<"p2: "<<p2<<endl;
    system("pause");
    return 0;

}