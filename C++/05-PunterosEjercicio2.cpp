#include <iostream>
#include <cstdlib>
using namespace std;


struct Libro{
    char titulo[20];
    int paginas;
};

void modificarLibro(Libro* libro){
    cout<<"Ingrese el nuevo titulo del libro: ";
    cin>>libro->titulo;
    cout<<"Ingrese el nuevo numero de paginas: ";
    cin>>libro->paginas;
}

int main(){
    Libro* miLibro = new Libro;

    cout<<"Ingrese el titulo del libro: ";
    cin>>miLibro->titulo;       
    cout<<"Ingrese el numero de paginas: ";
    cin>>miLibro->paginas;


    cout<<"Datos del libro antes de la modificacion: "<<endl;
    cout<<"Titulo: "<<miLibro->titulo<<endl;
    cout<<"Paginas: "<<miLibro->paginas<<endl;


    modificarLibro(miLibro);
    cout<<"Datos del libro despues de la modificacion: "<<endl;
    cout<<"Titulo: "<<miLibro->titulo<<endl;
    cout<<"Paginas: "<<miLibro->paginas<<endl;
    delete miLibro; //Liberar memoria
    system("pause");
    return 0;

}