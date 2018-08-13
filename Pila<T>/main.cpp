#include "Pila.h"
#include "TiposBasicos.h"

main(){
	Pila<int>* p1 = new Pila<int>();
	Pila<int>* p2 = new Pila<int>();

	p1->apilar(1);
	p1->apilar(2);
	p1->apilar(3);
	p1->apilar(4);
	p1->apilar(5);
	p1->apilar(5);

	p2->apilar(1);
	p2->apilar(2);
	p2->apilar(3);
	p2->apilar(4);
	p2->apilar(5);

	int a = 0;
	
	if(*(p1)==*(p2)){
		a = 1;
	}
	std::cout << a << "\n";

}