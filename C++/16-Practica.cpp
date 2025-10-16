// Práctica: Sistema de Administración de Ventas de un Kiosko

#include <iostream>
#include <string>
using namespace std;

// Estructura que representa un producto vendido
struct Producto
{
    string nombre;   // Nombre del producto
    float precio;    // Precio unitario
    int cantidad;    // Cantidad vendida
};

// Nodo para la lista de productos vendidos en un día
struct NodoProducto
{
    Producto producto;         // Datos del producto vendido
    NodoProducto *sgte;        // Apunta al siguiente producto vendido
};

// Nodo para la lista de ventas de cada día
struct NodoVentasDelDia
{
    NodoProducto *productosVendidos; // Lista de productos vendidos ese día
    int dia;                         // Número de día (1 a 5)
    NodoVentasDelDia *sgte;          // Apunta al siguiente día
};

// Agrega un nodo vacío para un día a la lista de ventas semanales
NodoVentasDelDia *agregarNodoVentasVacio(NodoVentasDelDia *ventas, int dia)
{
    NodoVentasDelDia *nuevo = new NodoVentasDelDia;
    nuevo->dia = dia;                      // Asigna el número de día
    nuevo->sgte = nullptr;                 // Inicializa el siguiente nodo como nulo
    nuevo->productosVendidos = nullptr;    // Inicializa la lista de productos vendidos como vacía
    if (ventas == nullptr)
    {
        ventas = nuevo;                    // Si la lista está vacía, el nuevo nodo es el primero
    }
    else
    {
        NodoVentasDelDia *actual = ventas;
        while (actual->sgte != nullptr)    // Busca el último nodo de la lista
        {
            actual = actual->sgte;
        }
        actual->sgte = nuevo;              // Agrega el nuevo nodo al final
    }
    return ventas;
}

// Inicializa la lista de ventas semanales con 5 días (del 1 al 5)
NodoVentasDelDia *dameVentasSemanalInicializado()
{
    NodoVentasDelDia *ventas = nullptr;
    for (int i = 1; i <= 5; i++)
    {
        ventas = agregarNodoVentasVacio(ventas, i); // Agrega cada día vacío
    }
    return ventas;
}

// Agrega un producto vendido a la lista de productos de un día
NodoProducto *agregarNodoProductoVendido(NodoProducto *productos, string nombre, int cantidad, float precio)
{
    NodoProducto *nuevo = new NodoProducto;
    nuevo->producto.cantidad = cantidad;   // Asigna cantidad vendida
    nuevo->producto.nombre = nombre;       // Asigna nombre del producto
    nuevo->producto.precio = precio;       // Asigna precio unitario
    nuevo->sgte = nullptr;                 // Inicializa el siguiente nodo como nulo
    if (productos == nullptr)
    {
        productos = nuevo;                 // Si la lista está vacía, el nuevo nodo es el primero
    }
    else
    {
        NodoProducto *actual = productos;
        while (actual->sgte != nullptr)    // Busca el último nodo de la lista
        {
            actual = actual->sgte;
        }
        actual->sgte = nuevo;              // Agrega el nuevo nodo al final
    }
    return productos;
}

// Registra una venta en el día correspondiente
void registrarVenta(NodoVentasDelDia *ventasSemanal, int dia, string nombre, int cantidad, float precio)
{
    NodoVentasDelDia *aux = ventasSemanal;
    while (aux->dia != dia)                // Busca el nodo del día indicado
    {
        aux = aux->sgte;
    }
    // Agrega el producto vendido a la lista de ese día
    aux->productosVendidos = agregarNodoProductoVendido(aux->productosVendidos, nombre, cantidad, precio);
}

// Calcula el total de ingresos por ventas de un día
int dameVentasDelDia(NodoProducto *productos)
{
    int valor = 0;
    while (productos != nullptr)           // Recorre la lista de productos vendidos
    {
        valor += productos->producto.cantidad * productos->producto.precio; // Suma el ingreso de cada producto
        productos = productos->sgte;
    }
    return valor;                          // Retorna el total de ingresos del día
}

// Devuelve el día con más ingresos por ventas
int dameDiaMasExitoso(NodoVentasDelDia *ventasSemanal)
{
    int max = 0;                           // Máximo ingreso encontrado
    int dia = 0;                           // Día con máximo ingreso
    while (ventasSemanal != nullptr)       // Recorre la lista de días
    {
        int ventasDelDia = dameVentasDelDia(ventasSemanal->productosVendidos); // Calcula ingresos del día
        if (ventasDelDia > max)            // Si es mayor al máximo actual
        {
            max = ventasDelDia;            // Actualiza el máximo
            dia = ventasSemanal->dia;      // Actualiza el día más exitoso
        }
        ventasSemanal = ventasSemanal->sgte;
    }
    return dia;                            // Retorna el día más exitoso
}

// Función principal para probar el sistema
int main()
{
    NodoVentasDelDia *init = dameVentasSemanalInicializado(); // Inicializa la semana
    // Registra ventas en distintos días
    registrarVenta(init, 1, "Agua", 10, 10);
    registrarVenta(init, 2, "Agua", 20, 10);
    registrarVenta(init, 2, "Agua", 20, 10);
    registrarVenta(init, 3, "Agua", 20, 10);
    registrarVenta(init, 3, "Agua", 40, 10);
    registrarVenta(init, 4, "Agua", 10, 40);
    registrarVenta(init, 5, "Agua", 10, 10);
    // Muestra el día con más ingresos
    cout << "El día más exitoso es: " << dameDiaMasExitoso(init);
}