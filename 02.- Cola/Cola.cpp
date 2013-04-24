#include <iostream>
#include "Cola.h
"using namespace std;

int main()
{
	Cola cola;
	int valor_elemento;
	int op;
	cout << "Cola\n";
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
                cola.push(valor_elemento);
                break;
            case 1:
                if(cola.get_cuantos() != 0){
                    cout << "Se saco el elemento " << cola.pop() <<"\n";
                }else{
                    cout << "La cola esta vacia.\n";
                }
                break;
            case 2:
                cout << "La lista tiene "<< cola.get_cuantos() << " elementos\n";
                break;
            case 3:
                cola.pintar();
                break;
        }
	}
	return 0;
}
