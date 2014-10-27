#ifndef LISTA_DOBLE_MITAD_H
#define LISTA_DOBLE_MITAD_H

struct caja{
	int valor;
	caja* siguiente;
	caja* anterior;
};

class Lista_doble_mitad{
    caja *principio, *final, *anterior, *mitad;
	int cuantos;
	int menores,mayores; //Cantidad de elementos [menores | mayores] que el elemento en *mitad
	bool encontrado;
	enum donde_enum{VACIO, PRINCIPIO, ENMEDIO, FINAL};
	donde_enum donde;
public:
	Lista_doble_mitad();
	~Lista_doble_mitad();	// ~: alt 126
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

Lista_doble_mitad::Lista_doble_mitad(){
    principio = NULL;
    final = NULL;
    anterior = NULL;
    mitad = NULL;
    cuantos = 0;
    mayores = 0;
    menores = 0;
    encontrado = false;
    donde = VACIO;
}

Lista_doble_mitad::~Lista_doble_mitad(){
    caja *p, *q;
    p = principio;
    while(p){
        q = p;
        p = p -> siguiente;
        delete q;
    }
    cuantos = 0;
}


bool Lista_doble_mitad::buscar(int a){
    caja *p;

    if (!principio){
    	donde = VACIO;
    	return false;
    }

    if ((mitad -> valor) < a){
        p = mitad;
    }else{
        p = principio;
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

bool Lista_doble_mitad::push(int a){
	caja *p;
	if (buscar(a))
        return false;
    std::cout << "Metiendo en " << donde << std::endl ;
	p = new caja;
	p -> valor = a;

	if (donde == VACIO){
		p -> anterior = NULL;
		p -> siguiente = NULL;
		principio = p;
		final = p;
		mitad = p;
	}else if (donde == PRINCIPIO){
		p -> anterior = NULL;
		p -> siguiente = principio;
		principio -> anterior = p;
		principio = p;

		if (mayores == menores){
            ++menores;
        }else{
            ++mayores;
            mitad = mitad -> anterior;
        }
	}else if (donde == ENMEDIO){
		p -> anterior = anterior;
		p -> siguiente = anterior -> siguiente;
		anterior -> siguiente = p;
		(p -> siguiente) -> anterior = p;
		if ( (p -> valor) > (mitad -> valor) ){
            if (mayores == menores){
                mitad = mitad -> siguiente;
                ++menores;
            }else{
                ++mayores;
            }
		}else{
            if (mayores == menores){
                ++menores;
            }else{
                ++mayores;
                mitad = mitad -> anterior;
            }
		}
	}else{
	    p -> anterior = anterior;
		p -> siguiente = anterior -> siguiente;
		anterior -> siguiente = p;
		final = p;

		if (mayores == menores){
            menores += 1;
            mitad = mitad -> siguiente;
        }else{
            mayores += 1;
        }
	}
    std::cout << "Mitad en: " << mitad -> valor << std::endl ;
    std::cout << "Mayores: " << mayores << "\tMenores: " << menores << std::endl;
    std::cout << "-------------------" << std::endl;
	cuantos++;
	return true;
}

void Lista_doble_mitad::pintar(){
    caja *p;
    p = principio;

    while (p){
        std::cout << " " << p->valor << " ";
        p = p -> siguiente;
    }
    std::cout<<"\n";
}

void Lista_doble_mitad::pintar2(){
    caja *p;
    p = final;

    while (p){
        std::cout << " " << p->valor << " ";
        p = p -> anterior;
    }
    std::cout<<"\n";
}

bool Lista_doble_mitad::borrar(int a){
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

int Lista_doble_mitad::pop(){
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

int Lista_doble_mitad::popl(){
    pop();
}
int Lista_doble_mitad::popr(){
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
int Lista_doble_mitad::get_cuantos(){
	return cuantos;
}

#endif
