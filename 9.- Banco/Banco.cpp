#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

#include "Cola_clientes.h"
#include "Cajeras.h"

int main()
{
	int h_actual;
	int h_maxima;
	int h_sig_cliente;
	int long_cola;
	int long_cola_max;
	int t_espera_cliente;
	int t_espera_max;
	int total_cajeras;
	int total_clientes;
	int intervalo_llegadas;
	int intervalo_esperas;

	srand(time(NULL));
	h_actual = 0;
	h_maxima = 420;
	long_cola  = 0;
	long_cola_max = 0;
	t_espera_cliente = 0;
	t_espera_max = 0;
	total_cajeras = 4;
	total_clientes = 0;
	intervalo_llegadas = 10;
	intervalo_esperas = 10;

	Cola_clientes clientes;
	Cajeras cajeras;

	cout << "Los valores por default son:\n\t"<< total_cajeras << " cajer"<<char(64)<<"s, \t" << h_maxima << "minutos\n";
	cout << "Desea cambiar los valores por default? [0: no, 1: si]: ";
	int cambiar_default = 0;
	cin >> cambiar_default;
	if (cambiar_default){
	    do{
            cout << "Cuantas cajer"<<char(64)<<"s desea tener?: ";
            cin >> total_cajeras;
            cout << "Cuantos minutos desea dejar abierto el banco?: ";
            cin >> h_maxima;
            cout << "Cuantos desea que sea el maximo de minutos entre clientes?: ";
            cin >> intervalo_llegadas;
            cout << "Cuantos desea que sea el maximo de tiempo de cajera por cliente?: ";
            cin >> intervalo_esperas;

            if(total_cajeras < 1 || h_maxima < 1 || intervalo_llegadas < 1 || intervalo_esperas < 1)
                cout << "Porfavor ingrese solo valores mayores a uno.\n";
		}while(total_cajeras < 1 || h_maxima < 1 || intervalo_llegadas < 1 || intervalo_esperas < 1);
	}

	h_sig_cliente = rand() % intervalo_llegadas + 1;
	for (int i = 0; i < total_cajeras; i++){
		cajeras.agregar();
	}

	//////////////
	//////////////
    cout << "\nPrimer cliente: "<<h_sig_cliente<<"\n";
    //////////////
    //////////////

	while ( (h_actual <= h_maxima) || (clientes.cuantos() != 0) ) { // Atender el banco mientras este "abierto" O queden clientes haciendo cola
		//////////////
		//////////////
		cout << "\t-------Info cajeras---"<<h_actual<<"------\n";
        //cout << "\nCuantas:\t\t"<<cajeras.get_cuantos();
        cout << "\tDisponible:\t\t" << cajeras.disponible(h_actual)<<"\n";
        cout << "\tH_ sig_disp:\t\t" << cajeras.h_sig_disponible()<<"\n";
        cout << "\tCajeras:\n\t";
        cajeras.pintar();
        cout << "\n\tH_ sig_cliente:\t\t" << h_sig_cliente<<"\n";
        cout << "\tCola de clientes:\n\t";
        clientes.pintar();
        cout << "\t----------------------------\n";
        //////////////
		//////////////

		// Agregar cliente
		if (h_actual == h_sig_cliente){					    // Se revisa si acaba de "llegar" un cliente al banco
			if (h_sig_cliente <= h_maxima){				    // Si el cliente llega mientras el banco esta abierto
				clientes.agregar(h_sig_cliente, rand() % intervalo_esperas + 1);		    // Agregarlo a la cola
				total_clientes++;
				long_cola++;
				if (long_cola > long_cola_max)
					long_cola_max = long_cola;

				h_sig_cliente = h_actual + rand() % intervalo_llegadas + 1; // Se calcula la hora del siguiente cliente
			}
		}

		// Despachar clientes
		cajeras.despachar(h_actual); // Las cajeras que ya completaron su tiempo con el cliente cambian su estado a desocupado

		// Avanzar fila
		while (cajeras.disponible(h_actual) && (clientes.cuantos() != 0)){	 // Si hay clientes por avanzar
		    //////////////
		    //////////////
		    cout<<"\nAtendiendo cliente \n";
		    //////////////
		    //////////////

			cajeras.recibir_cliente(h_actual, clientes.t_sig_cliente()); // El cliente va a la cajera y ocupa su tiempo,
			t_espera_cliente = clientes.avanzar_fila(h_actual);	    	 // lo que hace que la cola avance. Se almacena el tiempo que el cliente espero en la fila
			if (t_espera_cliente > t_espera_max)			// Si el cliente es el que mas ha esperado, guardar tiempo
				t_espera_max = t_espera_cliente;
			long_cola--;
		}

		h_actual++;
	}

	cout << "\n\n---------------------------------------------------------------\n\n";
	cout << "Resultados con " << total_cajeras << " cajer" <<char(64)<<"s durante " << h_maxima << "minutos:\n";
	cout << "\tCola mas larga: " << long_cola_max;
	cout << "\n\tTiempo de espera maximo: " << t_espera_max<<endl;

}// Fin main();
