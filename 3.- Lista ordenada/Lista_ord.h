#ifndef LISTA_ORD
#define LISTA_ORD

struct caja{
	int valor;
	caja* siguiente;
};

class Lista_ord{
	caja *principio, *anterior;
	int cuantos;
	bool encontrado;
	enum donde_enum{VACIO, PRINCIPIO, ENMEDIO, FINAL};
	donde_enum donde;
public:
	Lista_ord();
	~Lista_ord();	// ~: alt 126
	bool buscar(int a);
	bool push(int a);
	bool borrar(int a);
	void pintar();
	int pop();
	int get_cuantos();
};

Lista_ord::Lista_ord(){
    principio = NULL;
    anterior = NULL;
    cuantos = 0;
    encontrado = false;
    donde = VACIO;
}

Lista_ord::~Lista_ord(){
    caja *p, *q;
    p = principio;
    while(p){
        q = p;
        p = p -> siguiente;
        delete q;
    }
    cuantos = 0;
}


bool Lista_ord::buscar(int a){
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

bool Lista_ord::push(int a){
	caja *p;
	if (buscar(a))
        return false;

	p = new caja;
	p -> valor = a;

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

void Lista_ord::pintar(){
    caja *p;
    p = principio;

    while (p){
        std::cout << " " << p->valor << " ";
        p = p -> siguiente;
    }
    std::cout<<"\n";
}

bool Lista_ord::borrar(int a){
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

int Lista_ord::pop(){
	int valor;
	valor = principio -> valor;

	principio = principio -> siguiente;
	cuantos --;
	return valor;
}

int Lista_ord::get_cuantos(){
	return cuantos;
}

#endif
