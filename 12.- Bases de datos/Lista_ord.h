#ifndef LISTA_ORD
#define LISTA_ORD
#include <string>

struct persona{
	int id; // Identificador unico (Expediente)
	std::string apellido;
	std::string nombre;
	persona* siguiente;
};

class Lista_ord{
	persona *principio, *anterior;
	persona *ultimo_agregado_;
	int cuantos;
	bool encontrado;
	enum donde_enum{VACIO, PRINCIPIO, ENMEDIO, FINAL};
	donde_enum donde;
public:
	Lista_ord();
	~Lista_ord();	// ~: alt 126
	bool buscar(int a);
	bool push(int, std::string, std::string);
	bool borrar(int a);
	void pintar();
	int pop();
	int get_cuantos();
	persona* ultimo_agregado();
};

Lista_ord::Lista_ord(){
    principio = NULL;
    anterior = NULL;
    cuantos = 0;
    encontrado = false;
    donde = VACIO;
}

Lista_ord::~Lista_ord(){
    persona *p, *q;
    p = principio;
    while(p){
        q = p;
        p = p -> siguiente;
        delete q;
    }
    cuantos = 0;
}


bool Lista_ord::buscar(int a){
    persona *p;
    p = principio;
    if (!p){
    	donde = VACIO;
    	return false;
    }

    while (p){
    	if (p -> id == a){
    		if(p == principio){
                donde = PRINCIPIO;
            }else{
                donde = ENMEDIO;
            }
    		return true;
        }else if (p -> id > a){
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

bool Lista_ord::push(int new_id, std::string new_apellido, std::string new_nombre){
	persona *p;
	if (buscar(new_id))
        return false;

	p = new persona;
	p -> id = new_id;
	p -> nombre = new_nombre;
	p -> apellido = new_apellido;
	ultimo_agregado_ = p;

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
    persona *p;
    p = principio;

    while (p){
        std::cout << " ->\t" << p->id << "\t" << p->apellido << "\t  " << p->nombre << "\n";
        p = p -> siguiente;
    }
    std::cout<<"\n";
}

bool Lista_ord::borrar(int a){
	persona *p;

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
	int id;
	id = principio -> id;

	principio = principio -> siguiente;
	cuantos --;
	return id;
}

int Lista_ord::get_cuantos(){
	return cuantos;
}

persona* Lista_ord::ultimo_agregado(){
    return ultimo_agregado_;
}
#endif
