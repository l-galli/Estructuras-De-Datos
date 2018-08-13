typedef unsigned long Nat;

#include <string>
#include <ostream>
#include <iostream>
using namespace std;


struct ElemPila {
  public:
      int id;
      string nombre;
      string descripcion;
  

  friend ostream& operator<<(ostream& os, const ElemPila& a) {
     os << "{Id:" << a.id << ", " << "Nombre:" << a.nombre << ", Descripción:" << a.descripcion <<"}";
     return os;
  }

};

class Pila {

  private:

    struct Nodo {
      ElemPila elem;
      Nodo* sig;
    };

    Nodo* prim;
    Nat tam;

  public:

  // Constructor y destructor
    Pila(); 
   ~Pila();
      
  // Generadores
    void vacia();
    void apilar(ElemPila& elem);
  
  // Observadores básicos
    bool esVacia();
    ElemPila& tope();
    //ElemPila& 
    void desapilar();



  // Otras operaciones
    Nat tamanio() const;

  // Asignacion
    Pila& operator=(const Pila & aCopiar);

  // Muestra la lista en un ostream
    void mostrar(ostream& os) const;

  friend ostream& operator<<(ostream& os, const Pila &p) {
    p.mostrar(os);
    return os;
  }

};

