// Práctica: Sistema de Administración de Ventas de un Kiosko
// Se requiere un sistema para gestionar las ventas de productos de un kiosko de la semana. El kiosko
// vende distintos tipos de productos como golosinas, bebidas y artículos de librería. Se debe poder
// registrar ventas y conocer los ingresos de dichas ventas de cada día.
// Estructura de datos que debes utilizar:
// struct Producto {
// string nombre;
// float precio;
// int cantidad;
// };
// struct NodoProducto {
// Producto producto;
// NodoProducto* sgte;
// };
// struct NodoVentasDelDia {
// NodoProducto* productosVendidos;
// int dia; // 1..5
// NodoVentasDelDia* sgte;
// };
// NodoVentasDelDia* ventasSemanal;
// Operaciones a implementar:
// 1. NodoVentasDelDia* dameVentasSemanalInicializado();
// Devuelve la lista de ventas semanales con 5 nodos, uno para cada día. Donde cada día es
// representado por un número del 1 al 5 y asegurandose que todos los días arranquen sin productos
// vendidos.
// 2. void registrarVenta(NodoVentasDelDia* ventasSemanal, int dia, string nombre, int cantidad, float precio);
// Registra una venta de un producto en el día correspondiente. Da por hecho que ya está validado
// previamente si el día esta entre 1 y 5.

// 2do parcial (TA) Resuelto 3

// 3. int dameDiaMasExitoso(NodoVentasDelDia* ventasSemanal);
// Devuelve el día en el que se generó más ingresos por ventas.

#include <iostream>
#include <string>
using namespace std;
struct Producto
{
    string nombre;
    float precio;
    int cantidad;
};
struct NodoProducto
{
    Producto producto;
    NodoProducto *sgte;
};
struct NodoVentasDelDia
{
    NodoProducto *productosVendidos;
    int dia; // 1..5
    NodoVentasDelDia *sgte;
};
NodoVentasDelDia *agregarNodoVentasVacio(NodoVentasDelDia *ventas, int dia)
{
    NodoVentasDelDia *nuevo = new NodoVentasDelDia;
    nuevo->dia = dia;
    nuevo->sgte = nullptr;
    nuevo->productosVendidos = nullptr;
    if (ventas == nullptr)
    {
        ventas = nuevo;
    }
    else
    {
        NodoVentasDelDia *actual = ventas;
        while (actual->sgte != nullptr)
        {
            actual = actual->sgte;
        }
        actual->sgte = nuevo;
    }
    return ventas;
}
NodoVentasDelDia *dameVentasSemanalInicializado()
{
    NodoVentasDelDia *ventas = nullptr;
    for (int i = 1; i <= 5; i++)
    {
        ventas = agregarNodoVentasVacio(ventas, i);
    }
    return ventas;
}
NodoProducto *agregarNodoProductoVendido(NodoProducto *productos, string nombre, int cantidad, float precio)
{
    NodoProducto *nuevo = new NodoProducto;
    nuevo->producto.cantidad = cantidad;
    nuevo->producto.nombre = nombre;
    nuevo->producto.precio = precio;
    nuevo->sgte = nullptr;
    if (productos == nullptr)
    {
        productos = nuevo;
    }
    else
    {
        NodoProducto *actual = productos;
        while (actual->sgte != nullptr)
        {
            actual = actual->sgte;
        }
        actual->sgte = nuevo;
    }
    return productos;
}
void registrarVenta(NodoVentasDelDia *ventasSemanal, int dia, string nombre, int cantidad, float precio)
{
    NodoVentasDelDia *aux = ventasSemanal;
    while (aux->dia != dia)
    {
        aux = aux->sgte;
    }
    aux->productosVendidos = agregarNodoProductoVendido(aux->productosVendidos, nombre, cantidad, precio);
}
int dameVentasDelDia(NodoProducto *productos)
{
    int valor = 0;
    while (productos != nullptr)
    {
        valor += productos->producto.cantidad * productos->producto.precio;
        productos = productos->sgte;
    }
    return valor;
}
int dameDiaMasExitoso(NodoVentasDelDia *ventasSemanal)
{
    int max = 0;
    int dia = 0;
    while (ventasSemanal != nullptr)
    {
        int ventasDelDia = dameVentasDelDia(ventasSemanal->productosVendidos);
        if (ventasDelDia > max)
        {
            max = ventasDelDia;
            dia = ventasSemanal->dia;
        }
        ventasSemanal = ventasSemanal->sgte;
    }
    return dia;
}
int main()
{
    NodoVentasDelDia *init = dameVentasSemanalInicializado();
    registrarVenta(init, 1, "Agua", 10, 10);
    registrarVenta(init, 2, "Agua", 20, 10);
    registrarVenta(init, 2, "Agua", 20, 10);
    registrarVenta(init, 3, "Agua", 20, 10);
    registrarVenta(init, 3, "Agua", 40, 10);
    registrarVenta(init, 4, "Agua", 10, 40);
    registrarVenta(init, 5, "Agua", 10, 10);
    cout << "El día más exitoso es: " << dameDiaMasExitoso(init);
}