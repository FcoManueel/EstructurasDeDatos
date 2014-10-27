#ifndef MONTON_MIN_H
#define MONTON_MIN_H
/************************************
*                                   *
*   Implementacion de un max-heap   *
*   Francisco Manuel Valle Ruiz     *
*   Mayo - 2013                     *
*                                   *
************************************/

#include <iostream>
using namespace std;

struct nodo{
    int valor;
    nodo *padre, *h_izq, *h_der; // Punteros de arbol
    nodo *anterior, *siguiente;  // Punteros de lista doble
};

class Monton{
    nodo *raiz;              // Variable de arbol
    nodo *principio, *final; // Variables de lista doble
    nodo *donde;             // Variables operativas (funciones)
    enum enum_como{VACIO, H_IZQ, H_DER};
    enum_como como;
  public:
    int ERROR_ = 31212012; // 3=E 12=R 12=R 0=O 12=R (ERROR)
    Monton();
    ~Monton();
    bool agregar(int a);
    int sacar();
    void subir(nodo* p);
    void bajar(nodo* p);
    void intercambiar(nodo *, nodo *);

    void pintar();
    void pintar_arbol();
};

Monton::Monton(){
    raiz = NULL;

    principio = NULL;
    final = NULL;

    donde = NULL;
    como = VACIO;
}

Monton::~Monton(){
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

void Monton::pintar(){
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

void Monton::pintar_arbol(){
    pintar_arbol_rec(raiz, 0);
}

bool Monton::agregar(int a){
    nodo* nuevo;
    nuevo = new nodo;
    nuevo -> valor = a;
    nuevo -> h_izq = NULL;
    nuevo -> h_der = NULL;

    if(raiz == NULL){
        raiz = nuevo;
        principio = nuevo;
        final = nuevo;

        (nuevo -> siguiente) = NULL;
        (nuevo -> anterior) = NULL;
        (nuevo -> padre) = NULL;
        donde = nuevo;
        como = H_IZQ;
    }else{ // if(raiz){
        (nuevo -> padre) = donde;
        if(como == H_IZQ){
            (donde -> h_izq) = nuevo;
            como = H_DER;
        }else{ // if(como == H_DER){
            (donde -> h_der) = nuevo;
            como = H_IZQ;
            donde = (donde -> siguiente);
        }
        (final -> siguiente) = nuevo;
        (nuevo -> anterior) = final;
        (nuevo -> siguiente) = NULL;
        final = nuevo;

        subir(nuevo);
    }

}

int Monton::sacar(){
    int valor;
    nodo *p;
    if (!raiz) return ERROR_;

    intercambiar(principio, final);
    p = final;
    valor = (p -> valor);

    // Acomodar como y donde
    if(como == H_IZQ){
        donde = (donde -> anterior);
        if(donde != NULL){
            (donde -> h_der) = NULL;
            como = H_DER;
        }
    }else{ // if(como == H_DER){
        como = H_IZQ;
        if(donde != NULL)
            donde->h_izq = NULL;
    }

    if(p -> anterior)
        (p -> anterior -> siguiente) = NULL;
    if(p == principio){
        principio = NULL;
        raiz = NULL;
    }
    final = (p -> anterior);
    delete p;
    p = principio;
    bajar(p);
    return valor;
}


void Monton::subir(nodo* p)
{
    while(p -> padre && (p -> padre -> valor) < (p -> valor)){
        intercambiar(p, p -> padre);
    }
}

void Monton::bajar(nodo* p)
{
    nodo* aux;
    while(p){
        if( !(p -> h_der) && !(p -> h_izq)){
            return;
        }else{
            if( p -> h_izq && !(p -> h_der)){
                aux = p -> h_izq;
            }else if( !(p -> h_izq) && p -> h_der){
                aux = p -> h_der;
            }else if( p -> h_izq && p -> h_der){
                if((p -> h_izq -> valor) > (p -> h_der -> valor)){
                   aux = p -> h_izq;
                }else{
                    aux = (p -> h_der);
                }
            }
            if((p -> valor) < (aux -> valor)){
                intercambiar(p,aux);
            }else{
                return;
            }
        }
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

    Intercambiar tiene tres casos:
        I)   el nodo q es padre de p
        II)  el nodo p es padre de q
        III) el nodo p y q no se encuentran juntos
*/
void Monton::intercambiar(nodo* p, nodo* q)
{
    nodo* aux;
    if(p == q) return;

    // Si p cuelga de q (Caso I), llamar a la funcion con
    // los parametros invertidos para estar en el caso II
    if(q == p -> padre){
        intercambiar(q,p);
        return;
    }

    // Caso II
    if(p == q -> padre){
        if(q == p -> h_der){ // Si q cuelga por la derecha de p
            aux = p -> padre;
            p -> padre = q;
            q -> padre = aux;

            intercambiar_punteros(p -> h_izq, q -> h_izq);

            aux = q -> h_der;
            q -> h_der = p;
            p -> h_der = aux;

            // Modificar los punteros de los vecinos al nodo
            if(q -> padre == NULL)
                raiz = q;
            else
                if(q -> padre -> h_der == p)
                    q -> padre -> h_der = q;
                else if(q -> padre -> h_izq == p)
                    q -> padre -> h_izq = q;
            if(q -> h_izq != NULL)
                q -> h_izq -> padre = q;
            if(p -> h_der != NULL)
                p -> h_der -> padre = p;
            if(p -> h_izq != NULL)
                p -> h_izq -> padre = p;
        }else{ // if(q == p -> h_izq){  Si q cuelga por la izquierda de p
            aux = p -> padre;
            p -> padre = q;
            q -> padre = aux;

            aux = q -> h_izq;
            q -> h_izq = p;
            p -> h_izq = aux;

            intercambiar_punteros(p -> h_der, q -> h_der);

            // Modificar los punteros de los vecinos
            if(q -> padre == NULL){
                raiz = q;
            }else{
                if(q -> padre -> h_der == p)
                    q -> padre -> h_der = q;
                else if(q -> padre -> h_izq == p)
                    q -> padre -> h_izq = q;
            }
            if(q -> h_der != NULL)
                q -> h_der -> padre = q;
            if(p -> h_der != NULL)
                p -> h_der -> padre = p;
            if(p -> h_izq != NULL)
                p -> h_izq -> padre = p;
        }
    }
    // Caso III
    else{
        intercambiar_punteros(p -> padre, q -> padre);
        intercambiar_punteros(p -> h_izq, q -> h_izq);
        intercambiar_punteros(p -> h_der, q -> h_der);

        // Modificar los punteros de los vecinos de p
        if(p -> padre == NULL){
            raiz = p;
        }else{
            if(p -> padre -> h_der == q){
                p -> padre -> h_der = p;
            }else if(p -> padre -> h_izq == q){
                p -> padre -> h_izq = p;
            }
        }
        if(p -> h_der != NULL)
            p -> h_der -> padre = p;
        if(p -> h_izq != NULL)
            p -> h_izq -> padre = p;

        // Modificar los punteros de los vecinos de q
        if(q -> padre == NULL){
            raiz = q;
        }else{
            if(q -> padre -> h_izq == p){
                q -> padre -> h_izq = q;
            }else if(q -> padre -> h_der == p){
                q -> padre -> h_der = q;
            }
        }
        if(q -> h_der != NULL)
            q -> h_der -> padre = q;
        if(q -> h_izq != NULL)
            q -> h_izq -> padre = q;
    }

    // Re-acomodar punteros de lista enlazada
    if(p -> siguiente == q){ // Si los nodos son vecinos en la lista enlazada
        aux = q -> siguiente;
        q -> siguiente = p;
        p -> siguiente = aux;

        aux = p -> anterior;
        p -> anterior = q;
        q -> anterior = aux;
    }else{ // Si los nodos NO son vecinos en la lista enlazada
        intercambiar_punteros(p -> siguiente, q -> siguiente);
        intercambiar_punteros(p -> anterior, q -> anterior);
        p -> anterior -> siguiente = p;
        q -> siguiente -> anterior = q;
    }
    if(principio == p){
        principio = q;
    }else{
        (q -> anterior -> siguiente) = q;
    }
    if(final == q){
        final = p;
    }else{
        (p -> siguiente -> anterior) = p;
    }

    // Actualizar 'donde'
    if(donde == p){
        donde = q;
    }else if(donde == q){
        donde = p;
    }
}
#endif
