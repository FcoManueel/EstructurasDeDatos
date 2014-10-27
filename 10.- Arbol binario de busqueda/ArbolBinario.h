#ifndef ARBOL_BINARIO_H
#define ARBOL_BINARIO_H

#include <iostream>
using namespace std;

struct nodo{
    int valor;
    nodo *padre, *h_izq, *h_der; // Punteros de arbol
    nodo *anterior, *siguiente;  // Punteros de lista doble
};

class ArbolBinario{
    nodo *raiz;             // Variable de arbol
    nodo *principio, *final; // Variables de lista doble
    nodo *donde;            // Variables operativas (funciones)
    enum enum_como{VACIO, H_IZQ, H_DER};
    enum_como como;
  public:
    ArbolBinario();
    ~ArbolBinario();
    bool buscar(int a);
    bool agregar(int a);
    void intercambiar(nodo *, nodo *);
    void desconectar(nodo *);
    bool borrar(int a);

    void pintar();
    void pintar_arbol();
};

ArbolBinario::ArbolBinario(){
    raiz = NULL;

    principio = NULL;
    final = NULL;

    donde = NULL;
    como = VACIO;
}

ArbolBinario::~ArbolBinario(){
    nodo *p, *q;
    p = principio;

    while(p){
        q = p;
        p = (p -> siguiente);

        (q -> padre) = NULL; // Reiniciar miembros
        (q -> h_izq) = NULL;
        (q -> h_der) = NULL;
        
        delete q;
    }
}

void ArbolBinario::pintar(){
    nodo *p;
    p = principio;

    while(p){
        cout << (p -> valor) << " ";
        p = (p -> siguiente);
    }
    cout << "\n";
}

void pintar_arbol_rec(nodo* n, int indentacion){
    if(n){
        if(indentacion){
            for(int i = 1; i < indentacion; ++i) cout << "     " ;
            cout << char(192) << "--->";
        }

        cout << (n -> valor) << "\n";
        pintar_arbol_rec(n -> h_izq, indentacion + 1);
        pintar_arbol_rec(n -> h_der, indentacion + 1);
    }
}

void ArbolBinario::pintar_arbol(){
    pintar_arbol_rec(raiz, 0);
}

/*
*   Funcion buscar()
*   Busca si existe en el arbol un nodo con algun valor dado.
*   La funcion tambien recolecta los datos "donde" y "como".
*   "como" representa si el hijo cuelga como h_izq o h_der
*   y "donde" es el puntero al nodo que sería el padre.
*
*   Recibe:
*       int a       Numero a buscar en el arbol
*   Devuelve:
*       booleano, true si ya existe algun nodo con valor "a",
*       (i.e. se encontro el valor) false en caso contrario.
*/
bool ArbolBinario::buscar(int a){
    donde = raiz;

    if(!donde){
        como = VACIO;
        return false;
    }

    while(donde){
        if (donde -> valor == a){         // Revisar nodo
            donde = (donde -> padre);
            return true;
        }else if(a < donde -> valor){     // Revisar rama izquierda
            como = H_IZQ;
            if (donde -> h_izq){
                donde = (donde -> h_izq);
                continue;
            }else{
                return false;
            }
        }else{                            // Revisar rama derecha
            como = H_DER;
            if (donde -> h_der){
                donde = (donde -> h_der);
                continue;
            }else{
                return false;
            }
        }
    }
}

bool ArbolBinario::agregar(int a){
    if(buscar(a)) return false;

    nodo* nuevo;
    nuevo = new nodo;
    (nuevo -> valor) = a;
    (nuevo -> padre) = donde;
    (nuevo -> h_izq) = NULL;
    (nuevo -> h_der) = NULL;

    if(!donde){
        (nuevo -> anterior) = NULL;
        (nuevo -> siguiente) = NULL;

        raiz = nuevo;
        principio = nuevo;
        final = nuevo;
        return true;
    }
    if(como == H_IZQ){
        (nuevo -> anterior) = (donde -> anterior);
        (nuevo -> siguiente) = donde;

        (donde -> h_izq) = nuevo;
        (donde -> anterior) = nuevo;
        if(nuevo -> anterior == NULL){
            principio = nuevo;
        }else{
            (nuevo -> anterior -> siguiente) = nuevo;
        }
    }else{ //if (como == H_DER)
        (nuevo -> anterior) = donde;
        (nuevo -> siguiente) = (donde -> siguiente);

        (donde -> h_der) = nuevo;
        (donde -> siguiente) = nuevo;
        if(nuevo -> siguiente == NULL){
            final = nuevo;
        }else{
            (nuevo -> siguiente -> anterior) = nuevo;
        }
    }
}

/*
    La funcion borrar tiene tres casos:
        I)   el nodo es hoja
        II)  el nodo tiene un hijo
        III) el nodo tiene dos hijos
    La funcion desconectar solo "desconecta" los punteros del arbol
    y se aplica solo a nodos que se encuentran en los casos I o II.

    Si el nodo se encuentra en el caso III se aplica la funcion intercambiar,
    la cual lo deja en alguno de los primeros dos casos.
*/

bool ArbolBinario::borrar(int a){
    nodo *p;
    if (!buscar(a)) return false;

    if (raiz -> valor == a){ // Asignar a 'p' el puntero del nodo a borrar
        p = raiz;
    }else{
        p = ((como == H_IZQ) ? (donde -> h_izq) : (donde -> h_der));
    }

    // Si el nodo tiene dos hijos (caso III) intercambiarlo con el elemento anterior a el
    if ( p -> h_izq && p -> h_der){
        intercambiar (p, p -> anterior);
    }

    // Desconectar del arbol
    desconectar(p);
    // Desconectar de la lista doble
    if(p -> anterior){
        (p -> anterior -> siguiente) = (p -> siguiente);
    }else{
        principio = (p -> siguiente);
    }
    if(p -> siguiente){
        (p -> siguiente -> anterior) = (p -> anterior);
    }else{
        final = (p -> anterior);
    }
    delete p;
    return true;
}

void ArbolBinario::desconectar(nodo *p){
    if ( !(p -> h_der)  &&  !(p -> h_izq) ) { // Caso I
        if (raiz == p){
            raiz = NULL;
        }else{
            (como == H_IZQ ? donde -> h_izq : donde -> h_der) = NULL;
        }
    }else{                                    // Caso II
        if (raiz == p){
            raiz = ((p -> h_izq) ? (p -> h_izq) : (p -> h_der));
        }else{
            ( como == H_IZQ ? donde -> h_izq : donde -> h_der) = ((p -> h_izq) ? (p -> h_izq) : (p -> h_der));
        }
        pintar_arbol();
    }
}

// Funcion auxiliar para la funcion intercambiar
void intercambiar_punteros(nodo *&p, nodo *&q){
    nodo *aux;

    aux = p;
    p = q;
    q = aux;
}

/*
    Intercambiar cambia la posicion en el arbol y en la
    lista de dos nodos. Los punteros a los nodos por
    intercambiar se llaman 'p' y 'q'.

    Intercambiar tambien tiene tres casos:
        I)   el nodo q es padre de p
        II)  el nodo p es padre de q
        III) los nodos no estan juntos
*/
void ArbolBinario::intercambiar(nodo *p, nodo *q)
{
    nodo *aux;
    if(q == p -> padre){   // En caso de que q sea padre de p (caso I)
        intercambiar(q,p); // Se llama a la funcion de modo que se este en el caso II
        return;
    }

    (q -> padre -> h_izq == q) ? (como = H_IZQ) : (como = H_DER); // Actualizar los valores de como y donde
    donde = (q -> padre);

    // Intercambiar los punteros que salen de los nodos
    intercambiar_punteros(p -> padre, q -> padre);
    intercambiar_punteros(p -> h_izq, q -> h_izq);
    intercambiar_punteros(p -> h_der, q -> h_der);

    if(q -> h_izq == q || q -> h_der == q){ // En caso II, hacer correcciones correspondientes
        p -> padre = q;
        donde = q;
        if(q -> h_izq == q){       // Cuando q colgaba de p por la izq
            q -> h_izq = p;
        }else if(q -> h_der == q){ // Cuando q colgaba de p por la der
            q -> h_der = p;
        }
    }else{ // En caso III, p NO era padre de q, por lo que q pudo haber sido la raiz(antes del intercambio)
        if(!(q -> padre)){
            raiz = p;
        }else{
            ((p -> padre -> h_izq == q) ? (p -> padre -> h_izq) : (p -> padre -> h_der)) = p;
        }
    }

    if( !(q -> padre) ){ // Actualizar puntero del padre al nodo q
        raiz = q;
    }else{
        ((q -> padre -> h_izq == p) ? (q -> padre -> h_izq) : (q -> padre -> h_der)) = q;
    }

    // Cambiar puntero de los hijos al nodo.
    if(p -> h_izq){
        (p -> h_izq -> padre) = p;
    }
    if(p -> h_der){
        (p -> h_der -> padre) = p;
    }
    if(q -> h_izq){
        (q -> h_izq -> padre) = q;
    }
    if(q -> h_der){
        (q -> h_der -> padre) = q;
    }
}

#endif
