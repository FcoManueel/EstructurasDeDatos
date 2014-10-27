#include <iostream>
#include "Monton_min.h"
using namespace std;

int main()
{
    Monton M;
    int num_op, aux;
    bool repetir = true;

    cout << "Monton minimo (min-heap) que maneja datos enteros.\n\n";

    M.agregar(10);
    M.agregar(9);
    M.agregar(11);

    M.agregar(100);
    M.agregar(50);
    M.agregar(150);
    M.agregar(30);
    M.agregar(70);
    M.agregar(130);
    M.agregar(170);
    M.agregar(200);

    M.agregar(25);
    M.agregar(75);
    M.agregar(125);
    M.agregar(175);
    M.agregar(40);
    M.agregar(50);
    M.agregar(55);
    M.agregar(60);
    M.agregar(150);
    M.agregar(145);

    while(repetir){
        cout << "\n\t";
        cout << char(201);
        for (int i = 0; i < 24 ; ++i) cout << char(205);
        cout << char(187);
        cout << "\n\t" << char(186) << "                        " << char(186);
        cout << "\n\t" << char(186) << "  1: Agregar elemento   " << char(186);
        cout << "\n\t" << char(186) << "  2: Sacar elemento     " << char(186);
        cout << "\n\t" << char(186) << "  3: Pintar como lista  " << char(186);
        cout << "\n\t" << char(186) << "  4: Pintar como arbol  " << char(186);
        cout << "\n\t" << char(186) << "  -1: Salir             " << char(186);
        cout << "\n\t" << char(186) << "                        " << char(186);
        cout << "\n\t";
        cout << char(200);
        for (int i = 0; i < 24 ; ++i) cout << char(205);
        cout << char(188);
        //cout << "\n\t--------------------------\n\n";

        cout << "\nElija una opcion: ";
        cin >> num_op;

        switch(num_op){
            case 1:
                cout << "Ingrese el elemento a agregar: ";
                cin >> aux;
                M.agregar(aux);
                cout << "\t~ El elemento fue agregado con exito! ~\n";
                break;
            case 2:
                aux = M.sacar();
                if( aux != M.ERROR_ ){
                    cout << "\t~ Se saco el elemento " << aux << " ~\n";
                }else{
                    cout << "\t~ El monton esta vacio, no se le puede sacar mas :( ~\n";
                }
                break;
            case 3:
                cout << "\n";
                M.pintar();
                break;
            case 4:
                cout << "\n";
                M.pintar_arbol();
                break;
            case -1:
                repetir = false;
                break;
            default:
                cout << "\t~ No mijo, que andas haciendo :( da una opcion valida, paro ~\n";
        }
        //cout << "\n------------------------------------------------------\n";
    }
    cout << "\t~ Gracias por todo :D! Vuelve pronto morro. ~\n";
    cin.ignore();
    cin.get();
}
