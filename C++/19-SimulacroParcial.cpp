// #include <iostream>
// #include <string>
// using namespace std;

// struct Sorteo{
//     int codigo;
//     int cantidad_ganadores;
//     char descripcion[200];
// };

// struct SorteoConPersona{
//     Sorteo sorteo;
//     NodoPersona* personas;
// };

// struct Persona{
//     int dni;
//     string nombre;
// };

// struct NodoPersona{
//     Persona per;
//     NodoPersona* sgte;
// };

// struct NodoSorteo{
//     SorteoConPersona sorteo;
//     NodoSorteo* sgte;
// };

// NodoSorteo* CargarLista(){
//     NodoSorteo* lista = NULL;
//     Sorteo sor = dameSiguienteRegistroDelArchivo();
//     while(sor.codigo != 0){
//         SorteoConPersona sorteoPer;
//         sorteoPer.sorteo = sor,
//         sorteoPer.personas = NULL;
        
//         lista = addElementoLista(lista,sorteoPer);
//         sor = dameSiguienteRegistroDelArchivo();

//     }
//     return lista;
// }

// void CargarPersona(NodoSorteo* lista, Persona per, int codigo){
//     NodoSorteo* actual = lista;
//     while(actual != NULL){
//         if(actual->sorteo.sorteo.codigo == codigo){
//             actual-> sorteo.personas = addElementoLista(actual->sorteoPersona,per);
//             break;
//         }
//         actual = actual -> sgte;
//     }
// }

// void mostrarSorteos(NodoSorteo* lista, int dni){
//     NodoSorteo* actualSor = lista;
//     while(actualSor != NULL){
//         NodoPersona* actualPer = actualSor->sorteo.personas;
//         while(actualPer != NULL){
//             if(actualPer -> per.dni == dni){
//                 cout<<actualSor ->sorteo.sorteo.descripcion<<endl;
//                 break;
//             }
//             actualPer = actualPer->sgte;
//         }
//         actualSor = actualSor ->sgte;
//     }
// }
// struct Nodo{
//     int dato;
//     Nodo* sgte;
// };

// Nodo* addElementoLista(Nodo* lista, int valor){
//     Nodo* nuevo = new Nodo;
//     nuevo -> dato = valor;
//     nuevo -> sgte = NULL;

//     if(lista == NULL){
//         lista = nuevo;
//     }else{
//         Nodo* actual = lista;
//         while(actual -> sgte != NULL){
//             actual = actual -> sgte;
//         }
//         actual -> sgte = nuevo;
//     }
//     return lista;
// }

// Sorteo dameSiguienteRegistroDelArchivo(){
//     Sorteo sor;
//     // Implementación ficticia para el ejemplo
//     sor.codigo = 0; // Indica el fin de los registros
//     return sor;
// }

// int main(){

// }
