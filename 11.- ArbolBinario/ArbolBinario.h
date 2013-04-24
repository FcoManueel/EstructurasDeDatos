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
    cout << "\n\n";
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
            if (donde -> h_izq){
                donde = (donde -> h_izq);
                continue;
            }else{
                como = H_IZQ;

                return false;
            }
        }else{                            // Revisar rama derecha
            if (donde -> h_der){
                donde = (donde -> h_der);
                continue;
            }else{
                como = H_DER;
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
            (donde -> anterior -> siguiente) = nuevo;
        }

    }else{ //if (como == H_DER)
        //if(donde -> siguiente == NULL) final = nuevo;
        (nuevo -> anterior) = donde;
        (nuevo -> siguiente) = (donde -> siguiente);

        (donde -> h_der) = nuevo;
        (donde -> siguiente) = nuevo;
        if(nuevo -> siguiente == NULL){
            final = nuevo;
        }else{
            (donde -> siguiente -> anterior) = nuevo;
        }
    }

    return true;
}



/*
    De aqui en adelante es el codigo versión piter flowers
    (de las notas de eduardo acye). 
    Ya jala en algunos casos, pero falta acompletar cosillas.
    Esta pendiente de revisar flow y ver que se puede 
    simplificar.
    23 / Abril / 2013
*/


/*
    La funcion borrar tiene tres casos:
        I)  el nodo es hoja
        II) el nodo tiene un hijo
        III)el nodo tiene dos hijos
    La funcion desconectar solo "desconecta" los punteros del arbol.
    Supongamos que p contiene el valor del puntero del nodo
    que se quiere borrar y que el nodo *p entra en el caso I o II
*/
void ArbolBinario::desconectar(nodo *p){
    if ((p -> h_der) == NULL && (p -> h_izq) == NULL) { // Caso I
        if (raiz == p){
            raiz = NULL;
            return;
        }else{
            //aux = (como == H_DER ? (donde -> h_der) : donde -> h_izq);
            //aux = NULL;
            if (como == H_DER){
                (donde -> h_der) = NULL;
            }else{
                (donde -> h_izq) = NULL;
            }
            return;
        }
    }else{ // Caso II
        if (raiz == p){
            if (p -> h_der){
                raiz = (p -> h_der);
            }else{
                raiz = (p -> h_izq);
            }
            return;
        }else{
            if (como == H_DER){
                if (p -> h_der){
                    (donde -> h_der) = p -> h_der;
                }else{
                    (donde -> h_der) = p -> h_izq;
                }
                return;
            }else{
                if (p -> h_der){
                    (donde -> h_izq) = p -> h_der;
                }else{
                    (donde -> h_izq) = p -> h_izq;
                }
                return;

            }
        }
    }
}

bool ArbolBinario::borrar(int a){
    nodo *p;
    if (!buscar(a)) return false;

    if (raiz -> valor = 0){
        p = raiz;
    }else{
        //p = ( como == H_DER ? (donde -> h_der) : (donde -> h_izq));
        if (como == H_DER){
            p = (donde -> h_der);
        }else{
            p = (donde -> h_izq);
        }

    }
    if ( p -> h_der && p -> h_izq){ // Si tiene dos hijos
        intercambiar (p, p -> anterior);
    }

    desconectar(p); // Desconectar del arbol

    // Desconectar de la lista doble
    if(p -> anterior){
        (p -> anterior -> siguiente) = (p -> siguiente);
    }
    if(p -> siguiente){
        (p -> siguiente -> anterior) = (p -> anterior);
    }

    delete p;
    return true;
}

void ArbolBinario::intercambiar(nodo *p, nodo *q)
{
    nodo *r, *r1;
    //CASO 1 P PADRE DE Q
    if(q->padre == p){
        if(p->h_der == q){
            // meneo de los nodos
            r = p->h_izq;
            p->h_izq = q->h_izq;
            q->h_izq = r;

            r = p->padre;
            p->padre = q;
            q->padre = r;

            r = q->h_der;
            q->h_der = p;
            p->h_der = r;

            //meneo de los vecinos
            if(!(q->padre)){
                raiz = q;
            }else{
                if(q->padre->h_der == p){
                    q->padre->h_der = q;
                }else{
                    q->padre->h_izq = q;
                }
            }
            if(q->h_izq){
                q->h_izq->padre = q;
            }
            if(p->h_der){
                p->h_der->padre = p;
            }
            if(p->h_izq){
                p->h_izq->padre = p;
            }
        }else{
        // Cuando q cuelga de p por la izquierda.
        }
    }else if(p->padre == q){
        // Cuando q es padre de p.
    }else{// NO ESTAN JUNTOS p y q
        r = p->padre;
        p->padre = q->padre;
        q->padre = r;

        r = p->h_der;
        p->h_der = q->h_der;
        q->h_der = r;

        r = p->h_izq;
        p->h_izq = q->h_izq;
        q->h_izq = r;

        if(!(p->padre)){
            raiz = p;
        }else{
            if(p->padre->h_der == q){
        p->padre->h_der = p;
            }else{
        p->padre->h_izq = p;
            }
        }
        if(p->h_der){
            p->h_der->padre = p;
        }
        if(p->h_izq){
            p->h_izq->padre = p;
        }
        // Hacer esto con q...
    }
}

#endif
