#include <iostream>
#include "ArbolBinario.h"
using namespace std;

int main()
{
    ArbolBinario AB;
    int num_op, aux;
    bool repetir = true;

    cout << "Arbol Binario de Busqueda que maneja datos enteros.\n\n";

    AB.agregar(10);
    AB.agregar(9);
    AB.agregar(11);

    AB.agregar(100);
    AB.agregar(50);
    AB.agregar(150);
    AB.agregar(30);
    AB.agregar(70);
    AB.agregar(130);
    AB.agregar(170);
    AB.agregar(200);

    AB.agregar(25);
    AB.agregar(75);
    AB.agregar(125);
    AB.agregar(175);
    AB.agregar(40);
    AB.agregar(50);
    AB.agregar(55);
    AB.agregar(60);
    AB.agregar(150);
    AB.agregar(145);


    while(repetir){
        cout << "\n\t";
        cout << char(201);
        for (int i = 0; i < 24 ; ++i) cout << char(205);
        cout << char(187);
        cout << "\n\t" << char(186) << "                        " << char(186);
        cout << "\n\t" << char(186) << "  1: Agregar elemento   " << char(186);
        cout << "\n\t" << char(186) << "  2: Borrar elemento    " << char(186);
        cout << "\n\t" << char(186) << "  3: Buscar             " << char(186);
        cout << "\n\t" << char(186) << "  4: Pintar como lista  " << char(186);
        cout << "\n\t" << char(186) << "  5: Pintar como arbol  " << char(186);
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
                if( AB.agregar(aux) ){
                    cout << "\t~ El elemento fue agregado con exito! ~\n";
                }else{
                    cout << "\t~ El elemento no pudo ser agregado :( ~\n";
                }
                break;
            case 2:
                cout << "Ingrese el elemento a borrar: ";
                cin >> aux;
                if( AB.borrar(aux) ){
                    cout << "\t~ El elemento fue borrado con exito! ~\n";
                }else{
                    cout << "\t~ El elemento no pudo ser borrado :( ~\n";
                }
                break;
            case 3:
                cout << "Ingrese el elemento a buscar: ";
                cin >> aux;
                if( AB.buscar(aux) ){
                    cout << "\t~ El elemento ya se encuentra en el arbol! ~\n";
                }else{
                    cout << "\t~ El elemento no se encuentra en el arbol :( ~\n";
                }
                break;
            case 4:
                cout << "\n";
                AB.pintar();
                break;
            case 5:
                cout << "\n";
                AB.pintar_arbol();
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
