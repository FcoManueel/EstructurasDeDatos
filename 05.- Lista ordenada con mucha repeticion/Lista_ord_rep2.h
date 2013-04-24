#ifndef LISTA_ORD_REP2
#define LISTA_ORD_REP2
#ifndef IOSTREAM
#include <iostream>
#endif

struct caja{
	int valor;
	unsigned int repeticiones;
	caja* siguiente;
};

class Lista_ord_rep2{
	caja *principio, *anterior;
	int cuantos;
	bool encontrado;
	enum donde_enum{VACIO, PRINCIPIO, ENMEDIO, FINAL};
	donde_enum donde;
public:
	Lista_ord_rep2();
	~Lista_ord_rep2();	// ~: alt 126
	bool buscar(int a);
	bool push(int a);
	bool borrar(int a);
	void pintar();
	int pop();
	int get_cuantos();
};

Lista_ord_rep2::Lista_ord_rep2(){
    principio = NULL;
    anterior = NULL;
    cuantos = 0;
    encontrado = false;
    donde = VACIO;
}

Lista_ord_rep2::~Lista_ord_rep2(){
    caja *p, *q;
    p = principio;
    while(p){
        q = p;
        p = p -> siguiente;
        delete q;
    }
    cuantos = 0;
}


bool Lista_ord_rep2::buscar(int a){
    caja *p;
    p = principio;

    if (!p){
    	donde = VACIO;
    	return false;
    }

    while (p){
    	if (p -> valor == a){
    		if(p == principio){
                donde = PRINCIPIO;
            }else{
                donde = ENMEDIO;
            }
    		return true;
        }else if (p -> valor > a){
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

bool Lista_ord_rep2::push(int a){
	caja *p;
	bool repetido;
	repetido = buscar(a);
	if (repetido){
	    if (donde == PRINCIPIO){
	        principio -> repeticiones += 1;
	    }else{
            (anterior -> siguiente) -> repeticiones += 1;
	    }
	}else{
        p = new caja;
        p -> valor = a;
        p -> repeticiones = 0;


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
	}
        cuantos++;
        return true;
}

void Lista_ord_rep2::pintar(){
    caja *p;
    p = principio;

    while (p){
        for (int i = 0; i < p->repeticiones+1; i++){
            std::cout << " " << p->valor << " ";
        }
        p = p -> siguiente;
    }
    std::cout << "\n";
}

bool Lista_ord_rep2::borrar(int a){
	caja *p;

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

int Lista_ord_rep2::pop(){
	int valor;
	valor = principio -> valor;

	if(principio -> repeticiones){
        principio -> repeticiones -= 1;
	}else{
        principio = principio -> siguiente;
	}
	cuantos --;
	return valor;
}

int Lista_ord_rep2::get_cuantos(){
	return cuantos;
}

#endif
