#ifndef CONJUNTO_HPP_
#define CONJUNTO_HPP_

#include <iostream>
using namespace std;

template <class T>
class Conjunto
{
	public:

		// Constructor. Genera un conjunto vacío.
		Conjunto();

		// Destructor. Debe dejar limpia la memoria.
		~Conjunto();

		// Inserta un elemento en el conjunto. Si éste ya existe,
		// el conjunto no se modifica.
		void insertar(const T&);

		// Decide si un elemento pertenece al conjunto o no.
		bool pertenece(const T&) const;

		// borra un elemento del conjunto. Si éste no existe,
		// el conjunto no se modifica.
		void remover(const T&);

		// devuelve el mínimo elemento del conjunto según <.
		const T& minimo() const;

		// devuelve el máximo elemento del conjunto según <.
		const T& maximo() const;

		// devuelve la cantidad de elementos que tiene el conjunto.
		unsigned int cardinal() const;

		// muestra el conjunto.
		void mostrar(std::ostream&) const;

		friend ostream& operator<<(ostream& os, const Conjunto<T> &c) {
			c.mostrar(os);
			return os;
		}

		//borrar despues

		T raiz();


	private:

		// la representación de un nodo interno.
		struct Nodo
		{
			// el constructor, toma el elemento al que representa el nodo.
			Nodo(const T& v);
			// el elemento al que representa el nodo.
			T valor;
			// puntero a la raíz del subárbol izq.
			Nodo* izq;
			// puntero a la raíz del subárbol der.
			Nodo* der; 

			int cantHijos();
			void mostrarAux(std::ostream& os);
			void destNodo();
			
		};

		// puntero a la raíz de nuestro árbol.
		Nodo* raiz_;
		int cantidad;
		// funciones auxiliares
		void buscar(const T& clave, Nodo* padre, Nodo* aBuscar);
		int queHijoEs(const T& clave, Nodo* padre);
		T buscarPredInmediato(Nodo* referente);

		
		

};

template <class T>
Conjunto<T>::Nodo::Nodo(const T& v)
	 : valor(v), izq(NULL), der(NULL)
{}

template <class T>
Conjunto<T>::Conjunto() : raiz_(NULL)
{cantidad = 0;}


template <class T>
Conjunto<T>::~Conjunto(){ 
	if(raiz_ == NULL) {}else{
		
		Nodo* der = this->raiz_->der;
		Nodo* izq = this->raiz_->izq;

		delete raiz_;

		if(der != NULL) der->destNodo();
		
		if(izq != NULL) izq->destNodo();

		this->cantidad = 0;
	}
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const{
	Nodo* x = raiz_;
	while((x != NULL) && (x->valor != clave)){
		if (clave > x->valor){
			x = x->der;
		} else {
			x = x->izq;
		}
	}

	return x != NULL;
	
}

template <class T>
void Conjunto<T>::insertar(const T& clave){
	Nodo* insertado = new Nodo(clave);
	Nodo* x = this->raiz_;
	bool insert = false;
	if(this->raiz_ == NULL){
		this->raiz_ = insertado;
		this->cantidad ++;
	} else {
		if(!this->pertenece(clave)){

			while(!insert){
				if(x->cantHijos() == 2){
					if (x->valor < clave){
						x = x->der;
					} else {
						x = x-> izq;
					}
				}
				if(x->cantHijos() == 1){
					if(x->der != NULL){
						if(x->valor < clave){
							x = x->der;
						}else{
							x->izq = insertado;
							insert = true;
						}
					}else{
						if(x->valor < clave){
							x->der = insertado;
							insert = true;
						} else {
							x = x->izq;
						}
					}
				}
				if(x->cantHijos() == 0){
					if (x->valor < clave){
						x->der = insertado;
					} else {
						x-> izq = insertado;
					}
					insert = true;
				}
			}	

			
			this->cantidad ++;
		}else{}
	}

}

template <class T>
unsigned int Conjunto<T>::cardinal() const
{
	return this->cantidad;
}

template <class T>
void Conjunto<T>::remover(const T& clave){
	if(this->pertenece(clave) /*&& (raiz_ != NULL)*/){
		Nodo* padre = this->raiz_;
		Nodo* hijo = this->raiz_;
		bool encontrado = false;
		//buscar padre-hijo-------------
		while(!encontrado){
			if(hijo->valor == clave){
				encontrado = true;
			} else {
				padre = hijo;
				if(hijo->valor < clave){
					hijo = hijo->der;
				} else {
					hijo = hijo->izq;
				}
			}
		}
		//----------------------------

		if(hijo->cantHijos() == 0){
			
			if (padre == hijo){
				this->raiz_ = NULL;
				delete hijo;
			}else{


				if(padre->valor > clave){
					padre->izq = NULL;
				} else {
					padre->der = NULL;
				}

				delete hijo;
			}
			
			cantidad = cantidad - 1;
		}else{ 

			if(hijo->cantHijos() == 1){
				if (padre == hijo){
					if(hijo->der != NULL){
							this->raiz_ = hijo->der;
							
						} else {
							this->raiz_ = hijo->izq; 
						}
					delete hijo;

				}else{
					if(padre->valor > clave){
						if(hijo->der != NULL){
							padre->izq = hijo->der;
							
						} else {
							padre->izq = hijo->izq; 
						}
						delete hijo;
					} else {
						if(hijo->der != NULL){
							padre->der = hijo->der;
							
						} else {
							padre->der = hijo->izq; 
						}
						delete hijo;
					}
				}
				cantidad = cantidad - 1;
				
			}else{

				if(hijo->cantHijos() == 2) {
					T predInmediato = this->buscarPredInmediato(hijo->izq);
					//T valorPred = predInmediato->valor;
					this->remover(predInmediato);
					hijo->valor = predInmediato;


				}
			}
		}

		

	} else {}

}

template <class T>
const T&  Conjunto<T>::minimo() const{

//que pasa si el arbol está vacío?

	Nodo* buscador = raiz_;
	while(buscador->izq != NULL){
		buscador = buscador->izq;
	}	

	return buscador->valor;
}


template <class T>
const T&  Conjunto<T>::maximo() const{
	
//que pasa si el arbol está vacío?	
	
	Nodo* buscador = raiz_;
	while(buscador->der != NULL){	
		buscador = buscador->der;
	}	

	return buscador->valor;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream& os) const {
	

	Nodo* actual = raiz_;	
	os << "{";
	if (raiz_ != NULL){
		os << raiz_->valor;
	

		if((raiz_->der != NULL) || (raiz_->izq != NULL)) os << ", ";

		if(raiz_->der != NULL){
		
			raiz_->der->mostrarAux(os);
		}

		//if((raiz_->izq != NULL)os << ", ";

		if(raiz_->izq != NULL){
			os << ", ";
			raiz_->izq->mostrarAux(os);
		}
	}

	os << "}";
}



#endif // CONJUNTO_HPP_



//No debe recibir NULL
template <class T>
int Conjunto<T>::Nodo::cantHijos(){
	int hijos = 0;
	if (this->der != NULL) hijos++;
	if (this->izq != NULL) hijos++;
	return hijos;

}


//PRE: conjunto no vacío y clave pertece a conjunto
//POST: Si el buscado es la raíz, padre e hijo son raíz, etc

template <class T>
void Conjunto<T>::buscar(const T& clave, Nodo* padre, Nodo* aBuscar){
	aBuscar = this->raiz_;
	padre = this->raiz_;
	bool encontrado = false;
	while(!encontrado){
		if(aBuscar->valor == clave){
			encontrado = true;
		} else {
			padre = aBuscar;
			if(aBuscar->valor > clave){
				aBuscar = aBuscar->der;
			} else {
				aBuscar = aBuscar->izq;
			}
		}
	}

}


//0 es izq, 1 es derecho, 2 no está (no debería pasar)

template <class T>
int Conjunto<T>::queHijoEs(const T& clave, Nodo* padre){
	int res = 2;
	//chequear acceso a punteros inválidos
	if((padre->izq != NULL) && (padre->izq->valor = clave)) res = 0;
	if((padre->izq != NULL) && (padre->der->valor = clave)) res = 1;

}


template <class T>
T Conjunto<T>::buscarPredInmediato(Nodo* referente){
	//necesito encontrar el máximo de la izquierda
	Nodo* buscador = referente;
	while(buscador->der != NULL){	
		buscador = buscador->der;
	}	

	return buscador->valor;

}
		

template <class T>
void Conjunto<T>::Nodo::mostrarAux(std::ostream& os){
	os << this->valor;
	
	if(this->der != NULL) {
		os << ", ";
		this->der->mostrarAux(os);
	}

	
	if(this->izq != NULL) {
		os << ", ";
		this->izq->mostrarAux(os);
	}
}	


template <class T>
void Conjunto<T>::Nodo::destNodo(){
	Nodo* der = this->der;
	Nodo* izq = this->izq;
	//Nodo* este = this;
	delete this;
	
	if(der != NULL) {
		
		der->destNodo();
	}

	
	if(izq != NULL) {
		izq->destNodo();
	}
}



template <class T>
T Conjunto<T>::raiz(){

	return this->raiz_->valor;
}














