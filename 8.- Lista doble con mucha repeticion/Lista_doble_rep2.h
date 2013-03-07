#ifndef LISTA_DOBLE_REP2
#define LISTA_DOBLE_REP2

struct caja{
	int valor;
	int repeticiones;
	caja* siguiente;
	caja* anterior;
};

class Lista_doble_rep2{
	caja *principio, *final, *anterior;
	int cuantos;
	bool encontrado;
	enum donde_enum{VACIO, PRINCIPIO, ENMEDIO, FINAL};
	donde_enum donde;
public:
	Lista_doble_rep2();
	~Lista_doble_rep2();	// ~: alt 126
	bool buscar(int a);
	bool push(int a);
	bool borrar(int a);
	void pintar();
	void pintar2();
	int pop();
	int popl();
	int popr();
	int get_cuantos();
};

Lista_doble_rep2::Lista_doble_rep2(){
    principio = NULL;
    final = NULL;
    anterior = NULL;
    cuantos = 0;
    encontrado = false;
    donde = VACIO;
}

Lista_doble_rep2::~Lista_doble_rep2(){
    caja *p, *q;
    p = principio;
    while(p){
        q = p;
        p = p -> siguiente;
        delete q;
    }
    cuantos = 0;
}


bool Lista_doble_rep2::buscar(int a){
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

bool Lista_doble_rep2::push(int a){
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
            p -> anterior = NULL;
            p -> siguiente = NULL;
            principio = p;
            final = p;
        }else if (donde == PRINCIPIO){
            p -> anterior = NULL;
            p -> siguiente = principio;
            principio -> anterior = p;
            principio = p;
        }else if (donde == ENMEDIO){
            p -> anterior = anterior;
            p -> siguiente = anterior -> siguiente;
            anterior -> siguiente = p;
            (p -> siguiente) -> anterior = p;
        }else{
            p -> anterior = anterior;
            p -> siguiente = anterior -> siguiente;
            anterior -> siguiente = p;
            final = p;
        }
    }
	cuantos++;
	return true;
}

void Lista_doble_rep2::pintar(){
    caja *p;
    p = principio;

    while (p){
        for (int i = 0; i < p->repeticiones+1; i++)
            std::cout << " " << p->valor << " ";
        p = p -> siguiente;
    }
    std::cout << "\n";
}

void Lista_doble_rep2::pintar2(){
    caja *p;
    p = final;

    while (p){
        for (int i = 0; i < p->repeticiones+1; i++)
            std::cout << " " << p->valor << " ";
        p = p -> anterior;
    }
    std::cout<<"\n";
}

bool Lista_doble_rep2::borrar(int a){
	caja *p;

	if (buscar(a))
        return false;

	if (donde == PRINCIPIO){
		p = principio;
		principio = p -> siguiente;
		principio -> anterior = NULL;
	}else if (donde == ENMEDIO){
		p = anterior -> siguiente;
		anterior -> siguiente = p -> siguiente;
		(p -> siguiente) -> anterior = anterior;
	}else{
		p = anterior -> siguiente;
		anterior -> siguiente = NULL;
		final = anterior;
	}

	delete p;
	cuantos --;
	return true;
}

int Lista_doble_rep2::pop(){
    int valor;
    valor = principio -> valor;
    if (principio -> repeticiones){
        (principio -> repeticiones) -= 1;
    }else{
        caja *ex;
        ex = principio;
        if (principio -> siguiente){    // Si la lista tiene mas de un elemento
            (ex -> siguiente) -> anterior = NULL;
            principio = ex -> siguiente;
        }else{
            principio = final = NULL;
        }
        delete ex;
    }
    cuantos--;
    return valor;
}

int Lista_doble_rep2::popl(){
    pop();
}
int Lista_doble_rep2::popr(){
    int valor;
    valor = final -> valor;

    if (principio -> repeticiones){
        (principio -> repeticiones) -= 1;
    }else{
        caja *ex;
        ex = final;
        if (final -> anterior){    // Si la lista tiene mas de un elemento
            (ex -> anterior) -> siguiente = NULL;
            final = ex -> anterior;
        }else{
            principio = final = NULL;
        }
        delete ex;
    }
    cuantos--;
    return valor;
}

void pintar2();
int Lista_doble_rep2::get_cuantos(){
	return cuantos;
}

#endif
