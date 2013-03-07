#include <iostream>
#include "Lista_ord.h"
using namespace std;

int main()
{
    Lista_ord lista;
	int valor_elemento;
	int op;
	cout << "Lista\n";
	cout << "0: Agregar elemento\t";
	cout << "1: Sacar elemento\n";
	cout << "2: Cuantos?\t\t";
	cout << "3: Pintar\n";
	cout << "-1: Salir\n\n";

	while(op != -1){
	    cout << "Op: ";
        cin >> op;
        switch (op){
            case 0:
                cout << "Elemento a agregar: ";
                cin >> valor_elemento;
                if( ! lista.push(valor_elemento) ){
                    cout<<"El elemento ya se encontraba en la lista!\n";
                }
                break;
            case 1:
                if(lista.get_cuantos() != 0){
                    cout << "Se saco el elemento " << lista.pop() <<"\n";
                }else{
                    cout << "La lista esta vacia.\n";
                }
                break;
            case 2:
                cout << "La lista tiene "<< lista.get_cuantos() << " elementos\n";
                break;
            case 3:
                lista.pintar();
                break;
        }
	}

	return 0;
}
