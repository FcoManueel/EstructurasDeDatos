#ifndef LISTA_DOBLE
#define LISTA_DOBLE

struct caja{
	int valor;
	caja* siguiente;
	caja* anterior;
};

class Lista_doble{
	caja *principio, *final, *anterior;
	int cuantos;
	bool encontrado;
	enum donde_enum{VACIO, PRINCIPIO, ENMEDIO, FINAL};
	donde_enum donde;
public:
	Lista_doble();
	~Lista_doble();	// ~: alt 126
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

Lista_doble::Lista_doble(){
    principio = NULL;
    final = NULL;
    anterior = NULL;
    cuantos = 0;
    encontrado = false;
    donde = VACIO;
}

Lista_doble::~Lista_doble(){
    caja *p, *q;
    p = principio;
    while(p){
        q = p;
        p = p -> siguiente;
        delete q;
    }
    cuantos = 0;
}


bool Lista_doble::buscar(int a){
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

bool Lista_doble::push(int a){
	caja *p;
	if (buscar(a))
        return false;

	p = new caja;
	p -> valor = a;

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

	cuantos++;
	return true;
}

void Lista_doble::pintar(){
    caja *p;
    p = principio;

    while (p){
        std::cout << " " << p->valor << " ";
        p = p -> siguiente;
    }
    std::cout<<"\n";
}

void Lista_doble::pintar2(){
    caja *p;
    p = final;

    while (p){
        std::cout << " " << p->valor << " ";
        p = p -> anterior;
    }
    std::cout<<"\n";
}

bool Lista_doble::borrar(int a){
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

int Lista_doble::pop(){
    caja *ex;
    int valor;
    ex = principio;
    valor = ex -> valor;
    if (principio -> siguiente){    // Si la lista tiene mas de un elemento
        (ex -> siguiente) -> anterior = NULL;
        principio = ex -> siguiente;
    }else{
        principio = final = NULL;
    }

    delete ex;
    cuantos--;
    return valor;
}

int Lista_doble::popl(){
    pop();
}
int Lista_doble::popr(){
    caja *ex;
    int valor;
    ex = final;
    valor = ex -> valor;
    if (final -> anterior){    // Si la lista tiene mas de un elemento
        (ex -> anterior) -> siguiente = NULL;
        final = ex -> anterior;
    }else{
        principio = final = NULL;
    }

    delete ex;
    cuantos--;
    return valor;
}

void pintar2();
int Lista_doble::get_cuantos(){
	return cuantos;
}

#endif
