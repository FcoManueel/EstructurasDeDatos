/********************************************
*                                           *
*   Nombre: Pseudo base de datos            *
*   Autor:  Francisco Manuel Valle Ruiz     *
*   Fecha:  Marzo 2013                      *
*                                           *
*********************************************/

#include <iostream>
#include <string>
#include <vector>

#include "Lista_ord.h"
using namespace std;

void pintar_apellido(vector<persona*>);
void pintar_nombre(vector<persona*>);
void actualizar_indices(persona*, vector<persona*> &, vector<persona*> &);
void actualizar_indice_1(vector<persona*> &, persona*);
void actualizar_indice_2(vector<persona*> &, persona*);

int main()
{
    Lista_ord l_personas;
    vector<persona*> indice_1;
    vector<persona*> indice_2;
    //cout << "\t          Simulador de bases de datos - Manuel Valle 2013 \n";
    cout << "\t ----------------------------------------------------------------" << endl;
    cout << "\t|                                                                |" << endl;
    cout << "\t|                            Acciones                            |" << endl;
    cout << "\t|  ------------------------------------------------------------  |" << endl;
    cout << "\t| | 1. Agregar una nueva persona a la base de datos            | |" << endl;
    cout << "\t| | 2. Imprimir personas ordenadas por Id                      | |" << endl;
    cout << "\t| | 3. Imprimir personas ordenadas por Apellido                | |" << endl;
    cout << "\t| | 4. Imprimir personas ordenadas por Nombre                  | |" << endl;
    cout << "\t| | -1. Salir del sistema.                                     | |" << endl;
    cout << "\t|  ------------------------------------------------------------  |" << endl;
    cout << "\t ----------------------------------------------------------------" << endl;

    ///////////////////
    ///////////////////
    /* Set de prueba */
    l_personas.push(0, "Kirk", "Lucia");
    actualizar_indices(l_personas.ultimo_agregado() , indice_1, indice_2);

    l_personas.push(1, "Valle", "Manuel");
    actualizar_indices(l_personas.ultimo_agregado() , indice_1, indice_2);

    l_personas.push(2, "Nefasto", "Arlequin");
    actualizar_indices(l_personas.ultimo_agregado() , indice_1, indice_2);

    l_personas.push(3, "Gallina", "Arlequin");
    actualizar_indices(l_personas.ultimo_agregado() , indice_1, indice_2);

    l_personas.push(4, "Nefasto", "Artimagna");
    actualizar_indices(l_personas.ultimo_agregado() , indice_1, indice_2);
    ///////////////////
    ///////////////////
    while(true){
        int num_op;
        cout << "\nQue accion desea ejecutar?: ";
        cin >> num_op;

        switch(num_op){
            case 1: {// Agregar una nueva persona a la base de datos
                int new_id;
                bool agregado;
                string new_apellido;
                string new_nombre;

                cout << "Ingrese el id de la nueva persona: ";
                cin >> new_id;

                cout << "Ingrese el apellido: ";
                cin >> new_apellido;

                cout << "Ingrese el nombre: ";
                cin >> new_nombre;

                agregado = l_personas.push(new_id, new_apellido, new_nombre);

                if (agregado){
                    actualizar_indices(l_personas.ultimo_agregado() , indice_1, indice_2);
                }else{
                    cout<<"\n\t! No se permiten ID's repetidos. Sorry bato :(\n";
                }

                break;
            }
            case 2: // Imprimir personas ordenadas por Id
                l_personas.pintar();
                break;
            case 3: // Imprimir personas ordenadas por Apellido
                pintar_apellido(indice_1);
                break;
            case 4: // Imprimir personas ordenadas por Nombre
                pintar_nombre(indice_2);
                break;
            case -1: // Salir
                return 0;
                break;
        }
        cout << "\n\n---------------------------------\n";
    }
}

/*
*   Imprime la lista de personas en el orden especificado en el vector indice.
*   Imprime con el siguiente formato:    ->  Id    Apellido    Nombre
*/
void pintar_apellido(vector<persona*> indice){
    vector<persona*>::iterator it;
    for (it=indice.begin(); it<indice.end(); it++)
        std::cout << " ->\t" << (*it)->id << "\t" << (*it)->apellido << "\t  " << (*it)->nombre << "\n";
    cout << '\n';
}

/*
*   Imprime la lista de personas en el orden especificado en el vector indice.
*   Imprime con el siguiente formato:    ->  Id    Nombre    Apellido
*/
void pintar_nombre(vector<persona*> indice){
    vector<persona*>::iterator it;
    for (it=indice.begin(); it<indice.end(); it++)
        std::cout << " ->\t" << (*it)->id << "\t" << (*it)->nombre << "\t  " << (*it)->apellido << "\n";
    cout << '\n';
}

void actualizar_indices(persona *nueva_persona, vector<persona*> &indice_1, vector<persona*> &indice_2){
    actualizar_indice_1( indice_1, nueva_persona );
    actualizar_indice_2( indice_2, nueva_persona );
}

void actualizar_indice_1(vector<persona*> &indice, persona* p){ // Ordenado por apellido
    vector<persona*>::iterator it, end;
    bool cond;  // Condicion que se debe satisfacer si una persona es alfabeticamente mayor que otra segun su apellido
    for (it = indice.begin(), end = indice.end() ; it != end ; ++it){
        cond = ( ((*it) -> apellido) > (p -> apellido) ) ||
              ( (((*it) -> apellido) == (p -> apellido)) && (((*it) -> nombre) > (p -> nombre)) );
        if ( cond ){
            indice.insert(it, p);
            return;
        }
    }
    indice.insert(indice.end(), p); //Si se llega aqui significa que la persona es la que ultima en el indice (no se encontro ninguna con apellido mayor)
}

void actualizar_indice_2(vector<persona*> &indice, persona* p){ // Ordenado por apellido
    vector<persona*>::iterator it, end;
    bool cond;  // Condicion que se debe satisfacer si una persona es alfabeticamente mayor que otra segun su nombre
    for (it = indice.begin(), end = indice.end() ; it != end ; ++it){
        cond = ( ((*it) -> nombre) > (p -> nombre) ) ||
              ( (((*it) -> nombre) == (p -> nombre)) && (((*it) -> apellido) > (p -> apellido)) );
        if ( cond ){
            indice.insert(it, p);
            return;
        }
    }
    indice.insert(indice.end(), p);
}
