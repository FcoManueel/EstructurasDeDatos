/********************************************
*											*
*	Nombre: Sistema "experto"         		*
*	Autor:	Francisco Manuel Valle Ruiz		*
*	Fecha:	Abril 2013						*
*											*
*********************************************/

#ifndef SISTEMA_EXPERTO_H
#define SISTEMA_EXPERTO_H

#define TOTAL_PREGUNTAS 20
#define TOTAL_CLAUSULAS 9
#define TOTAL_NODOS 35
#define OR 0
#define AND 1

#include <cstring>
using namespace std;

struct Arco;
struct Nodo;
struct NodoRuta;
class Lista_arcos;
class Lista_nodos;
class Lista_ruta;
class SistemaExperto;

struct Arco{
    int longitud;
    int afirmacion;
    Arco* siguiente;
    Nodo* nodo_apuntado;
};

struct Nodo{
    int num_nodo;
    Nodo* siguiente;
    Lista_arcos *salientes;
    int bandera;
    int ruta_corta;
    Nodo *antecesor;
    NodoRuta *direccion_en_lista_ruta;

    string cadena;
    int cuantos;
    int totales;
    int tipo_de_conexion; // -1: PREGUNTA, 0: OR, 1: AND
    int valor_verdad;// -1: NADA, 0: NO, 1: SI
};

struct NodoRuta{
    int ruta_corta;
    Nodo *direccion;
    NodoRuta *siguiente;
};


//////////////////////////////////////
//                                  //
//                                  //
//                                  //
//                                  //
//       Comienza Lista_arcos       //
//                                  //
//                                  //
//                                  //
//                                  //
//////////////////////////////////////

class Lista_arcos{
    Arco *principio; // Primer elemento de la lista
    Arco *anterior;  // Para la funcion buscar
    Arco *visitando; // Para la funcion dijkstra
    int cuantos;
    bool encontrado;
    enum donde_enum{VACIO, PRINCIPIO, ENMEDIO, FINAL};
    donde_enum donde;
public:
    Lista_arcos();
    ~Lista_arcos(); // ~: alt 126
    bool buscar(int a);
    bool agregar(Nodo* n, int l);
    bool borrar(int a);
    void pintar();
     int pop();         // Not needed
     int get_cuantos(); // Not needed

    void iniciar_recorrido();
    Arco* recorrer();
    void nuevo();
    void limpiar_arcos();

    friend Lista_nodos;
    friend SistemaExperto;
};

void Lista_arcos::nuevo(){
    principio = NULL;
    anterior = NULL;
    visitando = NULL;
    cuantos = 0;
    encontrado = false;
    donde = VACIO;
}

void Lista_arcos::limpiar_arcos(){
    Arco *p, *q;
    p = principio;
    while(p){
        q = p;
        p = p -> siguiente;
        delete q;
    }
    visitando = NULL;
    cuantos = 0;
}

Lista_arcos::Lista_arcos(){
    nuevo();
}

Lista_arcos::~Lista_arcos(){
    limpiar_arcos();
}


bool Lista_arcos::buscar(int a){
    Arco *p;
    p = principio;
    if (!p){
        donde = VACIO;
        return false;
    }

    while (p){
        if (p -> nodo_apuntado -> num_nodo == a){
            if(p == principio){
                donde = PRINCIPIO;
            }else{
                donde = ENMEDIO;
            }
            return true;
        }else if (p -> nodo_apuntado -> num_nodo > a){
            if(p == principio){
                donde = PRINCIPIO;
            }else{
                donde = ENMEDIO;
            }
            return false;
        }else{
            anterior = p;
            p = p -> siguiente;
        }
    }
    donde = FINAL;
    return false;
}

bool Lista_arcos::agregar(Nodo* n, int new_afirmacion){
    Arco *p;
    if (buscar(n -> num_nodo))
        return false;

    p = new Arco;
    p -> nodo_apuntado = n;
    p -> afirmacion = new_afirmacion;

    if (donde == VACIO){
        p -> siguiente = NULL;
        principio = p;
    }else if (donde == PRINCIPIO){
        p -> siguiente = principio;
        principio = p;
    }else{
        p -> siguiente = anterior -> siguiente;
        anterior -> siguiente = p;
    }
    cuantos++;
    return true;
}

void Lista_arcos::pintar(){
    Arco *p;
    p = principio;
    if(p){ // Imprimir primer elemento (sin coma antes)
        cout << "[" << p -> nodo_apuntado -> num_nodo << "]";
        p = (p -> siguiente);
    }
    while (p){ // Imprimir elementos restantes (con comas antes)
        cout << ", [" << p -> nodo_apuntado -> num_nodo << "]";
        p = (p -> siguiente);
    }
    cout<<"\n";
}

bool Lista_arcos::borrar(int a){
    Arco *p;

    if (buscar(a))
        return false;

    if (donde == PRINCIPIO){
        p = principio;
        principio = p -> siguiente;
    }else if (donde == ENMEDIO){

        p = anterior -> siguiente;
        anterior -> siguiente = p -> siguiente;
    }else{
        p = anterior -> siguiente;
        anterior -> siguiente = NULL;
    }

    delete p;
    cuantos --;
    return true;
}

int Lista_arcos::pop(){
    int num_nodo;
    num_nodo = principio -> nodo_apuntado -> num_nodo;

    principio = principio -> siguiente;
    cuantos --;
    return num_nodo;
}

int Lista_arcos::get_cuantos(){
    return cuantos;
}

void Lista_arcos::iniciar_recorrido(){
    visitando = principio;
}

Arco* Lista_arcos::recorrer(){
    Arco *a = visitando;
    if(!a) return NULL;

    visitando = (visitando -> siguiente);
    return a;
}


//////////////////////////////////////
//                                  //
//                                  //
//                                  //
//                                  //
//      Comienza Lista_nodos        //
//                                  //
//                                  //
//                                  //
//                                  //
//////////////////////////////////////

class Lista_nodos{
    Nodo *principio, *anterior;
    bool encontrado;
    enum donde_enum{VACIO, PRINCIPIO, ENMEDIO, FINAL};
    donde_enum donde;
public:
    Lista_nodos();
    ~Lista_nodos(); // ~: alt 126
    Nodo* buscar(int a);
    bool agregar(int a, string s, int t);
    bool borrar(int a);
    int pop();

    void nuevo();
    void limpiar_nodos();
    void pintar_nodos();
    void pintar_arcos();
    void pintar_todo();
    friend SistemaExperto;
};

void Lista_nodos::nuevo(){
    principio = NULL;
    anterior = NULL;
    donde = VACIO;
}

void Lista_nodos::limpiar_nodos(){
    Nodo *p, *q;
    p = principio;
    while(p){
        q = p;
        p = p -> siguiente;
        delete q;
    }

}

Lista_nodos::Lista_nodos(){
    nuevo();
}

Lista_nodos::~Lista_nodos(){
    limpiar_nodos();
}


Nodo* Lista_nodos::buscar(int a){
    Nodo *p;
    p = principio;
    if (!p){
        donde = VACIO;
        return NULL;
    }

    while (p){
        if (p -> num_nodo == a){
            if(p == principio){
                donde = PRINCIPIO;
            }else{
                donde = ENMEDIO;
            }
            return p;
        }else if (p -> num_nodo > a){
            if(p == principio){
                donde = PRINCIPIO;
            }else{
                donde = ENMEDIO;
            }
            return NULL;
        }else{
            anterior = p;
            p = p -> siguiente;
        }
    }
    donde = FINAL;
    return NULL;
}

bool Lista_nodos::agregar(int a, string s, int t){
    Nodo *n;
    if (buscar(a))
        return false;

    n = new Nodo;
    n -> num_nodo = a;
    n -> cadena = s;
    n -> bandera = -1;
    n -> valor_verdad = -1;
    n -> cuantos = 0;
    n -> totales = 0;
    n -> tipo_de_conexion = t;


    if (donde == VACIO){
        n -> siguiente = NULL;
        principio = n;
    }else if (donde == PRINCIPIO){
        n -> siguiente = principio;
        principio = n;
    }else{
        n -> siguiente = anterior -> siguiente;
        anterior -> siguiente = n;
    }
    (n -> salientes) = new Lista_arcos;
    (n -> salientes) -> nuevo();

    return true;
}

void Lista_nodos::pintar_nodos(){
    Nodo *n;
    n = principio;
    if(n){ // Imprimir primer elemento (sin coma antes)
        cout << "[" << n -> num_nodo << "]";
        n = (n -> siguiente);
    }
    while (n){ // Imprimir elementos restantes (con comas antes)
        cout << ", [" << n -> num_nodo << "]";
        n = (n -> siguiente);
    }
    cout<<"\n";
}

void Lista_nodos::pintar_arcos(){
    Nodo *n;
    n = principio;

    if(!n){
        cout << "No hay ningun nodo!" ;
        return;
    }

    Arco *arco;
    while (n){
        arco = (n -> salientes) -> principio;

        while(arco){
            cout << "\t[" << (n -> num_nodo) << "]";
            cout << " ----" << (arco -> longitud) << "---->";
            cout << " [" << (arco -> nodo_apuntado -> num_nodo) << "]\n";
            arco = (arco -> siguiente);
        }
        n = n -> siguiente;
    }
}

void Lista_nodos::pintar_todo(){
Nodo *n;
    n = principio;
    if(!n){
        cout << "No hay ningun nodo!" ;
        return;
    }

    while (n){
        cout << "[" << (n -> num_nodo) << "]:\n ";
        cout << "   --> "; // Imprimir salientes
        if (n -> salientes -> principio){
            (n -> salientes) -> pintar();
            cout << "\n";
        }else{
            cout << "No tiene arcos salientes\n";
        }
        /*
        cout << "   <-- "; // Imprimir entrantes
        if (n -> entrantes -> principio){
            (n -> entrantes) -> pintar();
            cout << "\n";
        }else{
            cout << " No tiene arcos entrantes.\n";
        }
        */
        cout<<"\n";
        n = n -> siguiente;
    }
}

bool Lista_nodos::borrar(int a){
    Nodo *p;

    if (buscar(a))
        return false;

    if (donde == PRINCIPIO){
        p = principio;
        principio = p -> siguiente;
    }else if (donde == ENMEDIO){

        p = anterior -> siguiente;
        anterior -> siguiente = p -> siguiente;
    }else{
        p = anterior -> siguiente;
        anterior -> siguiente = NULL;
    }

    delete p;
    return true;
}

int Lista_nodos::pop(){
    int num_nodo;
    num_nodo = principio -> num_nodo;

    principio = principio -> siguiente;
    return num_nodo;
}



//////////////////////////////////////
//                                  //
//                                  //
//                                  //
//                                  //
//    Comienza clase Lista_ruta     //
//                                  //
//                                  //
//                                  //
//                                  //
//////////////////////////////////////

class Lista_ruta{
    NodoRuta *principio, *final;
  public:
    Lista_ruta();
    ~Lista_ruta();
    void ajustar(NodoRuta*, int);
    NodoRuta* agregar(Nodo*, int);
    Nodo* sacar();
    void pintar();

    void nuevo();
    void limpiar_ruta();
    friend class SistemaExperto;
};

void Lista_ruta::nuevo(){
    principio = NULL;
    final = NULL;
}

void Lista_ruta::limpiar_ruta(){
    NodoRuta *p, *q;
    p = principio;
    while(p){
        q = p;
        p = (p -> siguiente);
        delete q;
    }
    principio = final = NULL;
}

Lista_ruta::Lista_ruta(){
    nuevo();
}

Lista_ruta::~Lista_ruta(){
    limpiar_ruta();
}

Nodo* Lista_ruta::sacar(){
    Nodo *n;
    NodoRuta *p;
    p = principio;
    n = (p -> direccion);

    if (!principio)
        return NULL;
    if (principio == final)
        final = NULL;

    principio = (principio -> siguiente);

    delete p;
    return n;
}

void Lista_ruta::ajustar(NodoRuta* nodo_ruta, int nueva_longitud){
    NodoRuta* n = principio;
    while(n && n!= nodo_ruta){
        n = n->siguiente;
    }
    if(n)
    (n -> ruta_corta) = nueva_longitud;
}

NodoRuta* Lista_ruta::agregar(Nodo* nodo_apuntado, int longitud_ruta){
    NodoRuta* n;
    n = new NodoRuta;
    (n -> ruta_corta) = longitud_ruta;
    (n -> direccion) = nodo_apuntado;
    (n -> siguiente) = NULL;

    if (!principio){
        principio = n;
    }else{
        (final -> siguiente) = n;
    }
    final = n;
    return n;
}

/*
    Lista_ruta::pintar()
    Lista_ruta tiene los valores del camino mas corto de A a B, pero los tiene en orden inverso.
    La siguiente funcion los imprime en el orden correcto: primero ingresa los caracteres a un
    flujo en orden inverso, luego transforma ese flujo a cadena y finalmente voltea la cadena.

    There must be a better way.
    Perdon.
*/
#include <string.h>
#include <sstream>
void Lista_ruta::pintar(){
    string str_lista, str_aux;
    stringstream ss;

    NodoRuta *n = principio;
    while(n){
        ss << "  ]" << n -> direccion -> num_nodo << "[";
        n = (n -> siguiente);
    }

    str_lista = ss.str();
    str_aux = "";
    for (int i = str_lista.size(); i >= 0 ; i--)
         str_aux += str_lista[i];
    cout << str_aux;
    cout << endl;
}

//////////////////////////////////////
//                                  //
//                                  //
//                                  //
//                                  //
//  Comienza clase SistemaExperto   //
//                                  //
//                                  //
//                                  //
//                                  //
//////////////////////////////////////

class SistemaExperto{
    Lista_nodos N;
    Lista_ruta R;
public:
    SistemaExperto();
    ~SistemaExperto();
    void agregar_nodo(int a, string s, int t);
    void agregar_arco(int a,int b,int l);

    void pintar();
    void pintar_nodos();
    void pintar_arcos();
    void pintar_ruta();

    void comenzar();
};

SistemaExperto::SistemaExperto(){
    N.nuevo();
    R.nuevo();
}

SistemaExperto::~SistemaExperto(){
//    N.limpiar_nodos(); // No se ocupa. Averiguar por que.
    R.limpiar_ruta();
}

void SistemaExperto::agregar_nodo(int a, string s, int tipo_de_conexion){
    N.agregar(a,s,tipo_de_conexion);
}

void SistemaExperto::agregar_arco(int a,int b,int afirmacion){
    Nodo *arc_ini, *arc_fin;
    arc_ini = N.buscar(a);
    arc_fin = N.buscar(b);
    if( !arc_ini || !arc_fin ){
        cout << "El arco no fue agregado :)";
        return;
    }
    (arc_ini -> salientes) -> agregar(arc_fin, afirmacion);
}

void SistemaExperto::pintar(){
    N.pintar_todo();
}
void SistemaExperto::pintar_nodos(){
    N.pintar_nodos();
}

void SistemaExperto::pintar_arcos(){
    N.pintar_arcos();
}

void SistemaExperto::pintar_ruta(){
    R.pintar();
}

void SistemaExperto::comenzar(){
    Nodo *pregunta;
    Nodo *clausula;
    Nodo *n;
    Arco *a;
    int ans;
    bool preguntar;
    bool terminado = false;

    pregunta = N.principio;
    // Obtener informacion
    for(int i = 1; i <= TOTAL_PREGUNTAS; ++i){
        preguntar = false;
        a = ((pregunta -> salientes) -> principio);
        while(a){
            n = (a -> nodo_apuntado);
            if(n -> valor_verdad == -1){ // Si no se ha tocado algun nodo, preguntar
                preguntar = true;
                break;
            }
            a = a -> siguiente;
        }

        if(preguntar){
            do{
                cout << char(168) << pregunta -> cadena << ": ";
                cin >> ans;
                if((ans != 0) && (ans != 1))
                    cout << "Porfavor ingrese solo 1 [si] o 0 [no]\n";
            }while((ans != 0) && (ans != 1));

            a = ((pregunta -> salientes) -> principio);
            while(a){
                n = (a -> nodo_apuntado);
                (n -> cuantos)++;
                if(n -> valor_verdad == -1){ // Aun no tiene valor
                    ans = ( a -> afirmacion ? ans : !ans); // Si es negativa, se cambia su valor de verdad

                    bool valor_decisivo;
                    valor_decisivo = ( (n -> tipo_de_conexion) == OR ? true : false);
                    if(ans == valor_decisivo || (n -> cuantos == n -> totales)){
                        n -> valor_verdad = ans; // Asignar ans si es un valor decisivo o si es el ultimo en llegar
                    }
                }
                a = (a -> siguiente);
            }
        }
        pregunta = pregunta -> siguiente;
    }

    clausula = pregunta;
    // Procesar informacion
    for(int i = 1; i <= TOTAL_CLAUSULAS; ++i){
        a = ((clausula -> salientes) -> principio);
        while(a){
            n = a -> nodo_apuntado;
            n -> cuantos += 1;
            if(clausula -> valor_verdad == -1){
                break;
            }else{ // Derramar el valor de la clausula intermedia
                bool valor_clausula = (clausula -> valor_verdad); // Para disminuir longitud de codigo
                (clausula -> valor_verdad) = (a -> afirmacion ? valor_clausula : !valor_clausula);

                bool valor_decisivo;
                valor_decisivo = ((n -> tipo_de_conexion) == OR ? true : false);

                if(valor_clausula == valor_decisivo || (n -> cuantos == n -> totales)){
                    n -> valor_verdad = valor_clausula; // Asignar valor_clausula si es un valor decisivo o si es el ultimo en llegar
                }
            }
            a = a -> siguiente;
        }
        clausula = clausula -> siguiente;
    }
    while(clausula && clausula -> num_nodo != TOTAL_NODOS){
        if(clausula -> valor_verdad){
            cout << "Yo se de que animal hablas... ";
            cout << clausula -> cadena << "!";
            return;
        }

        clausula = clausula -> siguiente;
    }
    cout << "Lo siento, no se de que animal raro hablas\n";
}

#endif