#ifndef COLA
#define COLA
struct caja{
    int valor;
    caja *siguiente;
};

class Cola{
    caja *principio, *final;
    int cuantos;
public:
    Cola();
    ~Cola();
    void push(int a);
    int pop();
    void pintar();
    int get_cuantos();
};

Cola::Cola(){
    principio = NULL;
    final = NULL;
    cuantos = 0;
}

void Cola::push(int a){
    caja *p;

    p = new caja;
    p -> valor = a;
    p -> siguiente = NULL;
    
    if (principio == NULL){
        principio = p;
        final = p;
    }else{
        final -> siguiente = p;
        final = p;
    }
    cuantos++;
}

void Cola::pintar(){
    caja *p;
    p = principio;

    while(p){
        std::cout << " " << p->valor << " ";
        p = p -> siguiente;
    }
    std::cout<<"\n";
}

Cola:: ~Cola(){
    caja *p, *q;
    p = principio;
    while(p){
        q = p;
        p = p -> siguiente;
        delete q;
    }

    cuantos = 0;
}

int Cola::get_cuantos(){
    return cuantos;
}

int Cola::pop(){
    caja *p;
    int valor_caja;

    p = principio;
    if (p == NULL) return -31212012; //3 12 12 0 12 = E R R O R. Si, esta feo, pero no importa :)

    valor_caja = p -> valor;
    principio = principio -> siguiente;

    delete p;
    cuantos --;
    if (cuantos == 0) final == NULL;
    
    return valor_caja;
}
#endif
