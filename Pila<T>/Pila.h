#include <ostream>
#include "TiposBasicos.h"

/**
 * Esta clase representa una Pila de objetos de tipo genérico T.
 * 
 * Sólo se pueden asumir sobre 'T' es que tiene
 * definido el constructor por copia, el operador '<< (std::ostream&)' y
 * el operador de comparación '=='.
 */
template <typename T>
class Pila
{
  public:

    // Constructor sin parámetros. Crea una pila vacía.
    Pila();

    // Constructor por copia. Crea una nueva instancia de una Pila
    // que debe ser igual a la pasada por parámetro.
    Pila(const Pila& otra);

    // Destructor. Limpia toda la memoria dinámica que aún esté en uso.
    ~Pila();

    // El constructor puede ser visto como un generador
    void apilar(const T& elem);

    // En este caso, a diferencia del TAD, desapilar cambia el estado interno de mi instancia de clase
    // PRE: la pila no es vacía
    void desapilar();
  
  // Observadores básicos

    // Devuelve true si la Pila es vacía, false en caso contrario.
    bool esVacia() const;

    // Devuelve una referencia al elemento en el tope de la Pila.
    // PRE: La Pila no está vacía.
    T& tope();

    // Devuelve una referencia al elemento en el tope de la Pila.
    // PRE: La Pila no está vacía.
    const T& tope() const;

  // Otras operaciones

    // Devuelve la cantidad de elementos que hay en la pila.
    aed2::Nat tamanio() const;

    // Modifica esta instancia de Pila de tal manera que termine
    // siendo una copia de la Pila pasada por parámetro.
    // Devuelve una referencia a si misma.
    Pila& operator = (const Pila& otra);

    // IMPLEMENTACION OPCIONAL (no va a ser evaluada).
    // Compara dos instancias de Pila. Devuelve true si son iguales
    // y false en caso contrario.
    bool operator == (const Pila& otra) const;

    /**
     * Muestra la lista en un ostream.
     * formato de salida:
     *   [e_0, e_1, e_2, ...]
     * donde e_i es el resultado del "mostrar" el elemento i.
     * PRE: está definido el operador '<<' para los elementos de tipo 'T'.
     *
     * Nota: imprimir sobre os, es decir: os << "[" << ...
     * 
     * ATENCION:
     * 
     *  - entre elemento y elemento de la pila debe haber una coma y un espacio.
     * 
     *  - El primer elemento que se muestra representa al tope de la pila, es
     *    decir, los elementos se muestran en orden inverso al que fueron apilados.
     */
    template<typename S>
    friend std::ostream& operator << (std::ostream& os, const Pila<S>& pila);

  private:

    struct Nodo {
      T elem_;
      Nodo* sig;

      Nodo(const T& e, Nodo* sig);

      //void mostrar_n(std::ostream& os) const;

    };

    Nodo* tope_;
    aed2::Nat tamanio_;
    void mostrar(std::ostream& os) const;

};

template <typename T>
Pila<T>::Nodo::Nodo(const T& e, Nodo* s)
: elem_(e)
{
  this->sig = s;

}

/*
template <typename T>
void Pila<T>::Nodo::mostrar_n(std::ostream& os) const{
  os << this->elem_ << std::endl;

}


*/

template <typename T>
Pila<T>::Pila(){
  this->tope_ = NULL;
  this->tamanio_ = 0;

}


template <typename T>
Pila<T>::Pila(const Pila& otra)
{

  /*
  //this->tope_ = new Nodo (otra.tope_->elem_, this->tope_->sig);
  this->tamanio_ = otra.tamanio_;
  
  Nodo* iterador = otra.tope_->sig;
  tope_ = new Nodo (otra.tope_->elem_, NULL);
  while (iterador != NULL){
  	Nodo* siguiente;
  	this->tope_->sig = siguiente;
  	siguiente = new Nodo (iterador->elem_, iterador->sig);
  	iterador = iterador->sig;

  }

 
  int tam = otra.tamanio_ - 2;
  //Nodo* siguiente = tope_->sig;
  //Nodo* anterior = tope_;
  Nodo* anterior = tope_;
  Nodo* actual = tope_->sig;
  tope_->sig = NULL;

  while(tam != 0){
  	Nodo* siguiente = actual->sig;
  	actual->sig = anterior;
  	anterior = actual;
  	actual = siguiente;
  	tam--;
  	
  }

///////////
  if (otra.tamanio_ == 0) {
    tamanio_ = 0;
    tope_ = NULL;
  }else{
    
    Nodo* pnodo = new Nodo (otra.tope_->elem_, NULL);
    tope_ = pnodo;  
    Nodo* p_otra = otra.tope_->sig;
    for(unsigned int i = 1; i < otra.tamanio_ ;i++){
      Nodo* pactual = pnodo;
      if(p_otra != NULL){ 
      pnodo = new Nodo (p_otra->elem_, NULL);
      p_otra = p_otra->sig;
      pactual->sig = pnodo;
      }else{
        pactual->sig = NULL;
      }
    }
  }
*/  
  this-> tamanio_ = 0;
  this->tope_ = NULL;
  Nodo* nod = otra.tope_;
  Pila nueva;
  while(nod != NULL){
    nueva.apilar(nod->elem_);
    nod = nod->sig;

  }

Nodo* nod2 = nueva.tope_;
while(nod2 != NULL){
  this-> apilar(nod2 -> elem_);
  nod2 = nod2 -> sig;
}


}


template <typename T>
Pila<T>::~Pila(){
/*
  Nodo* pnodo = this->tope_;

  while(pnodo != NULL){
    Nodo* signodo = pnodo->sig;
    delete pnodo;
    pnodo = signodo;
  }
*/
  
  while(!this->esVacia()){
    this->desapilar();
  }



}

template <typename T>
void Pila<T>::apilar(const T& elem){
 Nodo* top = this->tope_;
 Nodo* nuevo = new Nodo (elem, top);
 this->tope_ = nuevo;
 tamanio_++;



  /*Nodo* nuevo = new Nodo;
  nuevo->elem_ = elem;
  nuevo->sig = this->tope_;
  this->tope_ = nuevo;
  tamanio_++;
*/

}

template <typename T>
void Pila<T>::desapilar(){
  Nodo* newprim = this->tope_;
  this->tope_ = newprim->sig;
  delete newprim;
  tamanio_--;
}

template <typename T>
bool Pila<T>::esVacia() const{
  return this->tope_ == NULL;


}

template <typename T>
T& Pila<T>::tope(){
  return this->tope_->elem_;
}

template <typename T>
const T& Pila<T>::tope() const{
  return this->tope_->elem_;
}

template <typename T>
aed2::Nat Pila<T>::tamanio() const{
  return this-> tamanio_;
}

template <typename T>
Pila<T>& Pila<T>::operator = (const Pila& otra){
  

   while(!this->esVacia()){
    this->desapilar();
  }


  Pila pila_nueva;
  Nodo* primero = otra.tope_;

  while (primero != NULL){
    pila_nueva.apilar(primero->elem_);
    primero = primero -> sig;
  }
  Nodo* primero2 = pila_nueva.tope_;
  while(primero2 != NULL){
    this->apilar(primero2->elem_);
    primero2 = primero2 -> sig;
  }
  this->tamanio_ = otra.tamanio_;
  

}


template <typename T>
std::ostream& operator << (std::ostream& os, const Pila<T>& pila){
  pila.mostrar(os);    
  return os;
}

template <typename T>
void Pila<T>::mostrar(std::ostream& os) const{
  Nodo* actual = tope_;
  
  os << "[";
  while(actual != NULL){
    os << actual->elem_;
    actual = actual->sig;
    if(actual != NULL){
      os << ", ";
    }
  }
  os << "]";


}


template <typename T>
bool Pila<T>::operator == (const Pila& otra) const{
  
  Nodo* actual = this->tope_;
  Nodo* actual_otra = otra.tope_;
  
  
  if(this->tamanio_ != otra.tamanio_){
    return false;
  }
  
  while((actual != NULL) && (actual_otra != NULL)){
    if(actual->elem_ != actual_otra->elem_){
      
      return false;
    }

    actual = actual->sig;
    actual_otra = actual_otra->sig;

  }

  return true;
}