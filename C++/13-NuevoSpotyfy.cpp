// Nuevo Spotify
// 1. **Crear una Playlist**: Define una estructura para representar una pila. Los elementos de la pila serán las canciones en tu playlist. Implementa funciones para añadir una canción (push), remover la última canción agregada (pop), y ver cuál es la última canción agregada (top).
//     - El sistema debe poder mediante un menu:
//         - Agregar canciones a la pila de reproducción (debe quedar primera)
//         - Tomar la próxima canción para escucharla (removiendola de la pila)
//         - Mostrar cual es la próxima canción (sin removerla)


#include <iostream>
#include <cstdlib>
using namespace std;


struct Cancion{
    string titulo;
    string artista;
    Cancion* siguiente;
};

Cancion* crearCancion(string titulo, string artista){
    Cancion* nuevaCancion = new Cancion;
    nuevaCancion->titulo = titulo;
    nuevaCancion->artista = artista;
    nuevaCancion->siguiente = NULL;
    return nuevaCancion;
}

void cancionPush(Cancion*& pila , string titulo, string artista){//Agregar un elemento a la pila
    Cancion* nuevaCancion = crearCancion(titulo, artista); //Crear un nuevo nodo
    nuevaCancion->siguiente = pila; //El siguiente del nuevo nodo es la pila actual
    pila = nuevaCancion; //La pila ahora es el nuevo nodo
    cout<<"Cancion "<<titulo<<" de "<<artista<<" agregada a la pila"<<endl;
}

//Tomar la próxima canción para escucharla (removiendola de la pila)
void cancionPop(Cancion*& pila){
    if(pila == NULL){
        cout<<"La pila esta vacia"<<endl;
        return; //Valor que indica que la pila esta vacia
    }

    Cancion* temp = pila;//Guardar el nodo superior en una variable temporal
    cout<<"Escuchando la cancion: "<<temp->titulo<<" de "<<temp->artista<<endl;
    pila = pila->siguiente;//Actualizar la pila al siguiente nodo
    delete temp; //Liberar memoria del nodo eliminado
}


// Función para ver la próxima canción sin removerla
void cancionTop(Cancion* pila){
    if(pila == NULL){
        cout<<"La pila esta vacia"<<endl;
        return; //Valor que indica que la pila esta vacia
    }
    cout<<"La proxima cancion es: "<<pila->titulo<<" de "<<pila->artista<<endl;
}

// 2. **Revertir Playlist**: Agrega al sistema la posibilidad de revertir el orden de las canciones. Te recomendamos usar una pila auxiliar para implementarlo.
//     - **Input**: ["Bohemian Rhapsody", "Hotel California", "Stairway to Heaven"]
//     - **Output**: ["Stairway to Heaven", "Hotel California", "Bohemian Rhapsody"]
void revertirPlaylist(Cancion*& pila){
    Cancion* pilaAuxiliar = NULL; // Pila auxiliar para almacenar las canciones en orden inverso
    while(pila != NULL){
        cancionPush(pilaAuxiliar, pila->titulo, pila->artista); // Mover la canción a la pila auxiliar
        cancionPop(pila); // Remover la canción de la pila original
    }
    pila = pilaAuxiliar; // La pila original ahora es la pila auxiliar (invertida)
    cout<<"Playlist revertida."<<endl;
}

// 3. **Historial de Reproducción:** El proyecto es todo un exito, por lo cual te piden una nueva funcionalidad. Quieren tener el historial de las canciones que se escucharon ordenadas por artista.
//     1. Por cada registro del historial quiero saber:
//         1. Titulo de la canción
//         2. Artista
//         3. El usuario debe calificar el tema luego de escucharlo, y esa calificación debe mostrarse en el historial (1 a 5 estrellas)
//     2. Quiero decirle que me muestre filtrando por cantidad de estrellas.
//         1. **Input**: 3 
//         2. **Output:** Todos los títulos de temas calificados con 3 estrella
//     3. Quiero que me de la cantidad de estrellas promedio asignadas al historial de reproducción
//     4. Quiero poder eliminar canciones del historial.

//muy complicado para hacer en el momento


int main(){
    //Menu de opciones
    Cancion* pila = NULL; //Pila de canciones inicializada como vacia
    int opcion;
    do{
        cout<<"Menu de opciones:"<<endl;
        cout<<"1. Agregar canción a la pila de reproducción"<<endl;
        cout<<"2. Tomar la próxima canción para escucharla"<<endl;
        cout<<"3. Mostrar cual es la próxima canción"<<endl;
        cout<<"4. Revertir Playlist"<<endl;
        cout<<"5. Salir"<<endl;
        cout<<"Ingrese una opción: ";
        cin>>opcion;

        switch(opcion){
            case 1:{
                string titulo, artista;
                cout<<"Ingrese el título de la canción: ";
                cin.ignore(); // Limpiar el buffer de entrada
                getline(cin, titulo);
                cout<<"Ingrese el artista de la canción: ";
                getline(cin, artista);
                cancionPush(pila, titulo, artista);
                break;
                
            }
            case 2:{
                cancionPop(pila);
                break;
            }
            case 3:{
                cancionTop(pila);
                break;
            }
            case 4:{
                revertirPlaylist(pila);
                break;
            }
            case 5:{
                cout<<"Saliendo del programa..."<<endl;
                break;
            }
            default:{
                cout<<"Opción inválida, por favor intente nuevamente."<<endl;
            }
        }
        cout<<endl; // Salto de línea para mejor legibilidad
    }while(opcion != 4);
}