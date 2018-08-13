#ifndef DICC_STRING_H_
#define DICC_STRING_H_

#include "Conj.hpp"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;


template<typename T>
class DiccString {
        public:
                /**
                CONSTRUCTOR
                * Construye un diccionario vacio.
                **/
                DiccString();

                /**
                CONSTRUCTOR POR COPIA
                * Construye un diccionario por copia.
                **/
                DiccString(const DiccString<T>&);


                /**
                DESTRUCTOR
                **/
                ~DiccString();

                /**
                DEFINIR
                * Recibe una clave con su significado de tipo T y la define.
                * Si ya estaba definida, la reescribe.
                **/
                void Definir(const string& clave, const T& significado);

                /**
                DEFINIDO?
                * Devuelve un bool, que es true si la clave pasada está definida en
                * el diccionario.
                **/
                bool Definido(const string& clave) const;

                /**
                OBTENER
                * Dada una clave, devuelve su significado.
                * PRE: La clave está definida.
                --PRODUCE ALIASING--
				-- Versión modificable y no modificable
                **/
				const T& Obtener(const string& clave) const;
                T& Obtener(const string& clave);

                /**
                OBTENER
                * Dada una clave, la borra del diccionario junto a su significado.
                * PRE: La clave está definida.
                --PRODUCE ALIASING--
                **/
                void Borrar(const string& clave);


                /**
                CLAVES
                * Devuelve las claves del diccionario.
                --NO PRODUCE ALIASING--
                **/
                const Conj<string>& Claves() const;

		

        private:

                struct Nodo{
                    Nodo** siguientes;
                    T* definicion;
                    Nodo(){
						siguientes = new Nodo*[256];
                        for (int i = 0; i < 256; i++){
                            siguientes[i] = NULL;
                        }
                        definicion = NULL;
                    }
                    ~Nodo(){
                        delete definicion;
						delete [] siguientes;
                    }
                    
                    int cantNodosSigs();
                    void BorradorNodo();
                    void CopiadorNodo(const Nodo* original);
                    
                };

               //void BuscarNodo(string key, Nodo* iterador, int n);
				void borrarUnaClave(const string& clave);
                Nodo* raiz;
                Conj<string> claves;
                int cantHijos(Nodo* iterador);
};


template <typename T>
DiccString<T>::DiccString()
    : raiz(NULL), claves(){

}


template <typename T>
DiccString<T>::DiccString(const DiccString& d) {
	Conj<string> nuevo = d.Claves();
    for (int i = 0; i < d.Claves().cardinal(); i++) {
        string min = nuevo.minimo();
        T signif = d.Obtener(min);
        this->Definir(min, signif);

        nuevo.remover(min);
    }
}

template <typename T>
DiccString<T>::~DiccString(){

	while(this->claves.cardinal() > 0) {
        this->Borrar(this->claves.minimo());
    }

    if (this->claves.cardinal() == 0) {
        delete this->raiz;
    }



}


template <typename T>
void DiccString<T>::Definir(const string& clave, const T& significado){
    
    //if(this->Definido(clave)){ this->Borrar(clave); }
	
	if(this->claves.cardinal() == 0 || this->raiz == NULL){
		
		this->raiz = new Nodo;

	}

	Nodo* iterador = this->raiz;
	
	
		
	for (int i = 0; i < clave.size(); i++) {
	    if (iterador->siguientes[int(clave[i])] == NULL) {
	        iterador->siguientes[int(clave[i])] = new Nodo;
	    }
	    iterador = iterador->siguientes[int(clave[i])];
	}
		
/*
	while(i < clave.size()){
		
	
		if(iterador->siguientes == NULL ){
	

			
			iterador->siguientes = new Nodo*[256];
            for (int j = 0; j < 256; j++){
                iterador->siguientes[j] = NULL;
            }
		}
		
		cout << "creo siguiente nodo" << endl;
		iterador->siguientes[int(clave.at(i))] = new Nodo();
		iterador = iterador->siguientes[int(clave.at(i))];
		i++;
	}
  */  
   
   
   	T* valor = iterador->definicion;
    iterador->definicion = NULL;
    delete valor;

    iterador->definicion = new T(significado);

	//T key = clave;
	claves.insertar(clave);
	    
}


template <typename T>
bool DiccString<T>::Definido(const string& clave) const{
    bool res;

    if(raiz != NULL){
    	Nodo* iterador = this->raiz;
		int i = 0;
		//menor o menor igual?
		while(i<clave.size() && iterador->siguientes[int(clave.at(i))] != NULL){
			iterador = iterador->siguientes[int(clave.at(i))];
			i++;
			
		}

    	res = ((i == clave.size()) && (iterador->definicion != NULL));
    
    
	}else{res = false;}

	return res;

}

template <typename T>
T& DiccString<T>::Obtener(const string& clave) {
	
	Nodo* iterador = this->raiz;

	int i = 0;
	
	while(i<clave.size()){
		iterador = iterador->siguientes[int(clave.at(i))];
		i++;

	}

	return *iterador->definicion;
    
}


template <typename T>
const T& DiccString<T>::Obtener(const string& clave) const {
		
    Nodo* iterador = this->raiz;

	int i = 0; 
	
	while(i<clave.size()){

		iterador = iterador->siguientes[int(clave.at(i))];
		i++;

	}

	return *iterador->definicion;
    
}


template <typename T>
const Conj<string>& DiccString<T>::Claves() const{
    return claves;
}


template <typename T>
void DiccString<T>::Borrar(const string& clave) {
	
	
	
	if(this->Claves().cardinal() == 1) {
		
		//caso 1 palabra
		this->borrarUnaClave(clave);
	}else{
		
		
		Nodo* otro = this->raiz; 
	    Nodo* iterador = this->raiz; 
        int indice = 0;


        for (int i = 0; i < clave.size(); i++) {
            iterador = iterador->siguientes[int(clave[i])];

            if (this->cantHijos(iterador) > 1 || (i != clave.size()-1 && iterador->definicion != NULL)) {
                otro = iterador;
                indice = i+1;
            }
        }

        
        if (this->cantHijos(iterador) > 0) {

           
            T* valor = iterador->definicion;
            iterador->definicion = NULL;
            delete valor;


       
        } else {
            Nodo* paraBorrar[clave.size()];

            
            iterador = otro;
            for (int i = indice; i < clave.size(); i++) {
                iterador = iterador->siguientes[int(clave[i])];
                paraBorrar[i] = iterador;
            }


            T* valor = iterador->definicion;
            iterador->definicion = NULL;
            delete valor;


            for (int i = indice; i < clave.size(); i++) {
                Nodo* nodoABorrar = paraBorrar[i];
                paraBorrar[i] = NULL;
                delete nodoABorrar;
            }

            otro->siguientes[int(clave[indice])] = NULL;
        }

        this->claves.remover(clave);
    }
}




#endif

/*
template <typename T>
void DiccString<T>::BuscarNodo(string key, Nodo* iterador, int n){

	iterador = this->raiz;

	//int i = 0;

	cout << "key length: " << key.length() << endl;  
	while(n<key.length()){
		iterador = iterador->siguientes[int(key.at(n))];
		cout << "key at: " << key.at(n) << endl;  
		n++;
		//cout << "n ya: " << n << endl;
	}
	cout << "n: " << n << endl;
	
}
*/

template <typename T>
int DiccString<T>::Nodo::cantNodosSigs(){

	int i = 0;
	int j = 0;

	while(i < 256){
		if (this->siguientes[i] != NULL) j++;
		i++;
	


	}
	
	return j ;

}


template <typename T>
void DiccString<T>::Nodo::BorradorNodo(){


	int i = 0;

	while(i < 256){
		if(this->siguientes != NULL && this->siguientes[i] != NULL){	
			this->siguientes[i]->BorradorNodo();

			delete this->siguientes[i];
			this->siguientes[i] = NULL;
			
		}

		i++;
	}

	delete this->definicion;
	this->definicion = NULL;
	//delete [] this->siguientes;


	delete *(this->siguientes);

	/*
	int j = 0;
	while(j < 256){

		delete this->siguientes[i];
		j++;
	}
	*/


	//delete this->siguientes;
	//delete this;

}



template <typename T>
void DiccString<T>::Nodo::CopiadorNodo(const Nodo* original){


	this->definicion = original->definicion;

	int i = 0;

	while(i < 256){
		if ((original->siguientes != NULL) && (original->siguientes[i] != NULL)){

			this->siguientes[i] = new Nodo();

			this->siguientes[i]->CopiadorNodo(original->siguientes[i]);
	
			
		}

		i++;
	} 

}

template <typename T>
int DiccString<T>::cantHijos(Nodo* iterador) {
    int j = 0;
    for (int i = 0; i < 256; i++) {
        if (iterador->siguientes[i] != NULL) {
            j++;
        }
    }
    return j;
}

template <typename T>
void DiccString<T>::borrarUnaClave(const string& clave){

	Nodo* iterador = this->raiz;

	Nodo* paraBorrar[clave.size()];

    
    for (int i = 0; i < clave.size(); i++) {
        iterador = iterador->siguientes[int(clave[i])];
        paraBorrar[i] = iterador;
    }

    
    T* valor = iterador->definicion;
    iterador->definicion = NULL;
    delete valor;

   
    for (int i = 0; i < clave.size(); i++) {
        Nodo* aBorrar = paraBorrar[i];
        paraBorrar[i] = NULL;
        delete aBorrar;
    }

  
    Nodo* raizABorrar = this->raiz;
    
    this->raiz = NULL;
    delete raizABorrar;

    this->claves.remover(clave);


}