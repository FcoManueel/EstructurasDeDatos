#ifndef CAJERAS
#define CAJERAS

struct cajera{
	bool ocupada;
	int h_disponible; // Hora a la que puede atender a otro cliente
	cajera* siguiente;
};

class Cajeras{
	cajera *principio, *anterior;
	int cuantos;
	bool encontrado;
	enum donde_enum{VACIO, PRINCIPIO, ENMEDIO, FINAL};
	donde_enum donde;
public:
	Cajeras();
	~Cajeras();	// ~: alt 126
	bool buscar(int);
	bool push(int, bool);
	bool borrar(int);
	void pintar();
	int pop();
	int get_cuantos();

	int recibir_cliente(int, int);
	int h_sig_disponible();
	bool despachar(int);
    bool agregar();
    bool disponible(int);
    bool buscar2(int);
};

Cajeras::Cajeras(){
    principio = NULL;
    anterior = NULL;
    cuantos = 0;
    encontrado = false;
    donde = VACIO;
}

Cajeras::~Cajeras(){
    cajera *p, *q;
    p = principio;
    while(p){
        q = p;
        p = p -> siguiente;
        delete q;
    }
    cuantos = 0;
}


bool Cajeras::buscar(int a){
    cajera *p;
    p = principio;
    if (!p){
    	donde = VACIO;
    	return false;
    }

    while (p){
    	if (p -> h_disponible == a){
    		if(p == principio){
                donde = PRINCIPIO;
            }else{
                donde = ENMEDIO;
            }
    		return true;
        }else if (p -> h_disponible > a){
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

bool Cajeras::push(int h_dis, bool ocupada){
	cajera *c;
	buscar(h_dis);

//    std::cout<<"La funcion buscar devolvio la posicion "<<donde<<"\n";
	c = new cajera;
	c -> h_disponible = h_dis;
	c -> ocupada = ocupada;

	if (donde == VACIO){
		c -> siguiente = NULL;
		principio = c;
	}else if (donde == PRINCIPIO){
		c -> siguiente = principio;
		principio = c;
	}else{
		c -> siguiente = anterior -> siguiente;
		anterior -> siguiente = c;
	}

	cuantos++;
	return true;
}

void Cajeras::pintar(){
    cajera *p;
    p = principio;

    while (p){
        std::cout << "  " << p->h_disponible << ":" << p->ocupada << "  ";
        p = p -> siguiente;
    }
    std::cout<<"\n";
}

bool Cajeras::borrar(int a){
	cajera *p;

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

int Cajeras::pop(){
	int h_disponible;
	h_disponible = principio -> h_disponible;

	principio = principio -> siguiente;
	cuantos --;
	return h_disponible;
}

int Cajeras::get_cuantos(){
	return cuantos;
}

int Cajeras::h_sig_disponible(){
	if (principio == NULL)
		return -31212012; //3 12 12 0 12 = E R R O R. Si, esta feo, pero no importa :)

	return principio -> h_disponible;
}

bool Cajeras::disponible(int h_actual){
	if (principio == NULL)
		return -31212012; //3 12 12 0 12 = E R R O R. Si, esta feo, pero no importa :)

	// return (principio -> h_disponible) <= h_actual;
	return !(principio -> ocupada); // True si la cajera esta desocupada, False si esta ocupada
}

int Cajeras::recibir_cliente(int h_actual, int t_cajera){
	cajera *c;
	c = principio;

	// Re asignar la cajera a otro cliente
	if ( (c -> ocupada) == false){
	    (c -> h_disponible) = h_actual + t_cajera;
		(c -> ocupada) = true;

        // Acomodarla en su lugar correspondiente en la lista ordenada
        buscar2(c -> h_disponible);

        if (donde == FINAL || donde == ENMEDIO){
            principio = c -> siguiente;
            (c -> siguiente) = anterior -> siguiente;
            anterior -> siguiente = c;
        }

        // Imprimir detalles, para debuggear
        #include <iostream>
        std::cout<<"La cajera se desocupara a las "<<c->h_disponible<<"\n";
        ////////// std::cout << "Se encontro cajera con "<<c->h_disponible<<"? " << buscar2(c -> h_disponible)<<"\n";
        ////////// std::cout << "Se acomodara en: " << donde << "\n";
        std::cout<<"Cajera re-acomodada en: " << donde << "\n\n";
	}
}

bool Cajeras::agregar(){
	this -> push(0, false);
}

bool Cajeras::despachar(int h_actual){
	cajera *c;
	c = principio;

	if (principio == NULL)
		return false; // Devuelve un indicador de que la operacion no se realizo bien
    while (c){
        if ( (c -> h_disponible == h_actual) && (c -> ocupada) ){
            (c -> ocupada) = false;
        }

        c = c -> siguiente;
    }
	return true;
}


/*
bool Cajeras::buscar2(int a){
    cajera *p;
    p = principio;
    if (!p){
    	donde = VACIO;
    	return false;
    }
    p = (p -> siguiente);
    while (p){
    	if (p -> h_disponible == a){
    		if(p == principio -> siguiente){
                donde = PRINCIPIO;
            }else{
                donde = ENMEDIO;
            }
    		return true;
        }else if (p -> h_disponible > a){
    		if(p == principio -> siguiente){
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
*/

bool Cajeras::buscar2(int h){
    cajera *p;
    p = principio;
    if (!p){
    	donde = VACIO;
    	return false;
    }

    p = (p -> siguiente);
    if (p -> h_disponible > h){
    	donde = PRINCIPIO;
    	return false;
    }else{
        anterior = p;
    	p = (p -> siguiente);
    }

    while (p){
    	if (p -> h_disponible > h){
    	    donde = ENMEDIO;
    		return false;
    	}else{
    		anterior = p;
    		p = p -> siguiente;
    	}
    }
    donde = FINAL;
    return false;
}

#endif
