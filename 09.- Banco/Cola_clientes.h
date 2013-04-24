#ifndef COLA_CLIENTES
#define COLA_CLIENTES

/*
#ifndef STDLIB_H        // Revisar si ya se cuenta con las librerias necesarias para generar
#define STDLIB_H        // numeros aleatorios y agregarlas si es necesario.
    #include <stdlib.h>
    #ifndef TIME_H
    #define TIME_H
        #include <time.h>

    #endif
#endif
*/

struct cliente{
    int h_llegada;
    // int t_espera;
    int t_cajera;
    //int h_salida = h_llegada + t_espera + t_cajera;
    cliente *siguiente;
};

class Cola_clientes{
    cliente *principio, *final;
    int num_clientes;
public:
    Cola_clientes();
    ~Cola_clientes();
    void agregar(int h, int t);
    int avanzar_fila(int);
    void pintar();
    int cuantos();
    int t_sig_cliente();
};

int Cola_clientes::t_sig_cliente(){
    return principio -> t_cajera;
}

Cola_clientes::Cola_clientes(){
    principio = NULL;
    final = NULL;
    num_clientes = 0;
}

void Cola_clientes::agregar(int h, int t){
    cliente *c;

    c = new cliente;
    c -> h_llegada = h;
    c -> t_cajera = t; // rand() % 10 + 1; // Se calcula el tiempo de cajera que ocupa para resolver su problema
    //c -> t_espera = 0;

    c -> siguiente = NULL;

    if (principio == NULL){
        principio = c;
        final = c;
    }else{
        final -> siguiente = c;
        final = c;
    }
    num_clientes++;
}

void Cola_clientes::pintar(){
    cliente *p;
    p = principio;

    while(p){
        std::cout << " " << p->h_llegada << " ";
        p = p -> siguiente;
    }
    std::cout<<"\n";
}

Cola_clientes:: ~Cola_clientes(){
    cliente *p, *q;
    p = principio;
    while(p){
        q = p;
        p = p -> siguiente;
        delete q;
    }

    num_clientes = 0;
}

int Cola_clientes::cuantos(){
    return num_clientes;
}

int Cola_clientes::avanzar_fila(int h_actual){
    cliente *c;
    int t_espera;

    c = principio;
    if (c == NULL) return -31212012; //3 12 12 0 12 = E R R O R. Si, esta feo, pero no importa :)

    t_espera = h_actual - (c -> h_llegada);
    principio = principio -> siguiente;

    delete c;
    num_clientes --;
    if (num_clientes == 0) final == NULL;

    return t_espera;
}
#endif
