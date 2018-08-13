#include <iostream>
#include "Pila.h"

using namespace std;

//Implementacion del TAD Pila


// Constructor y destructor

Pila::Pila(){
	this -> prim = NULL;
	this -> tam = 0;
}


Pila::~Pila(){
	Nodo* pnodo = this->prim;
	while(pnodo != NULL){
		Nodo* signodo = pnodo->sig;
		delete pnodo;
		pnodo = signodo;
	}

}

 
 // Generadores


void Pila::vacia(){
	this->prim = NULL;
	this->tam = 0;
}



void Pila::apilar(ElemPila& elem){
	Nodo* nuevo = new Nodo;
	nuevo->elem = elem;
	nuevo->sig = this->prim;
	this->prim = nuevo;
	tam++;
	
}


// Observadores básicos


bool Pila::esVacia(){
	return this->prim == NULL;
}


ElemPila& Pila::tope(){
	ElemPila& tope = this -> prim -> elem;
	return tope;
	
}


void Pila::desapilar(){
	Nodo* newprim = this->prim;
	this->prim = newprim->sig;
	delete newprim;
	tam--;
}



// Otras operaciones

Nat Pila::tamanio() const{
	return this -> tam;
}


 // Asignacion


Pila& Pila::operator=(const Pila & aCopiar){
	
	Pila pila_nueva;
	Nodo* primero = aCopiar.prim;

	this->~Pila();
	this->vacia();

	while(primero != NULL){
		ElemPila nuevo_elem;
		nuevo_elem = primero->elem;
		pila_nueva.apilar(nuevo_elem);
		//apilar(nuevo_elem);
		primero = primero->sig;

	}
	Nodo* primero2 = pila_nueva.prim;
	while(primero2 != NULL){
		ElemPila nuevo_elem2;
		nuevo_elem2 = primero2 -> elem;
		this->apilar(nuevo_elem2);
		primero2 = primero2 -> sig;
	}
		
	this->tam = aCopiar.tam;

}



void Pila::mostrar(ostream& os) const{
	Nodo* actual = prim;
	
	os << "[";
	while(actual != NULL){
		os << actual->elem;
		actual = actual->sig;
		if(actual != NULL){
			os << ", ";
		}
	}
	os << "]"<<endl;

	delete actual;

}