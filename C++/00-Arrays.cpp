#include <iostream>
#include <cstdlib>
using namespace std;
int main()
{
    int numeros[5];
    int suma = 0;
    for (int i = 0; i < 5; i++)
    {
        cout << "Ingrese el número " << i + 1 << ": ";
        cin >> numeros[i];
    }
    for (int i = 0; i < 5; i++)
    {
        suma += numeros[i];
    }
    cout << "La suma de los números ingresados es: " << suma << endl;
    system("pause");
    return 0;

}