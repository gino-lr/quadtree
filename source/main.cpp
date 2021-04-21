//Estructura Basica del QuadTree
#include <iostream>
#include <fstream>
#include <vector> 
#include <cmath>
#include <string>

using namespace std;

struct coord{
	int x, y;
	coord(int a, int b){
		x = a;
		y = b;
	}
	coord(){
		x = 0;
		y = 0;
	}
};

struct nodo{
	coord P;
	int X;
	nodo(coord _pos, int _data){
		P = _pos;
		X = _data;
	}
	nodo(){
		X = 0;
	}
};

class quadtree{	
public:
	coord esquina_arriba;
	coord esquina_abajo;	
	nodo* n;
	quadtree* noroeste;
	quadtree* noreste;
	quadtree* suroeste;
	quadtree* sureste;
	quadtree(){
		esquina_arriba = coord(0, 0);
		esquina_abajo = coord(0, 0);
		n = NULL;
		noroeste = NULL;
		noreste = NULL;
		suroeste = NULL;
		sureste = NULL;
	}
	quadtree(coord arribaIzq, coord abajoDer){
		n = NULL;
		noroeste = NULL;
		noreste = NULL;
		suroeste = NULL;
		sureste = NULL;
		esquina_arriba = arribaIzq;
		esquina_abajo = abajoDer;
	}
	void insertar(nodo*);
	nodo* buscar(coord);
	bool enQuad(coord);
};

void quadtree::insertar(nodo* node){
	if (node == NULL)
		return;	
	if (!enQuad(node->P))
		return;	
	if (abs(esquina_arriba.x - esquina_abajo.x) <= 1 &&	abs(esquina_arriba.y - esquina_abajo.y) <= 1){
		if (n == NULL)
			n = node;
		return;
	}
	if ((esquina_arriba.x + esquina_abajo.x) / 2 >= node->P.x){
		if ((esquina_arriba.y + esquina_abajo.y) / 2 >= node->P.y){
			if (noroeste == NULL)
				noroeste = new quadtree(coord(esquina_arriba.x, esquina_arriba.y), coord((esquina_arriba.x + esquina_abajo.x) / 2, (esquina_arriba.y + esquina_abajo.y) / 2));
			noroeste->insertar(node);
		}else{
			if (suroeste == NULL)
				suroeste = new quadtree(coord(esquina_arriba.x,	(esquina_arriba.y + esquina_abajo.y) / 2), coord((esquina_arriba.x + esquina_abajo.x) / 2, esquina_abajo.y));
			suroeste->insertar(node);
		}
	}else{		
		if ((esquina_arriba.y + esquina_abajo.y) / 2 >= node->P.y){
			if (noreste == NULL)
				noreste = new quadtree(coord((esquina_arriba.x + esquina_abajo.x) / 2, esquina_arriba.y), coord(esquina_abajo.x, (esquina_arriba.y + esquina_abajo.y) / 2));
			noreste->insertar(node);
		}else{
			if (sureste == NULL)
				sureste = new quadtree(coord((esquina_arriba.x + esquina_abajo.x) / 2, (esquina_arriba.y + esquina_abajo.y) / 2), coord(esquina_abajo.x, esquina_abajo.y));
			sureste->insertar(node);
		}
	}
}

nodo* quadtree::buscar(coord X){	
	if (!enQuad(X))
		return NULL;
	if (n != NULL)
		return n;
	if ((esquina_arriba.x + esquina_abajo.x) / 2 >= X.x){		
		if ((esquina_arriba.y + esquina_abajo.y) / 2 >= X.y){
			if (noroeste == NULL)
				return NULL;
			return noroeste->buscar(X);
		}		
		else{
			if (suroeste == NULL)
				return NULL;
			return suroeste->buscar(X);
		}
	}
	else{		
		if ((esquina_arriba.y + esquina_abajo.y) / 2 >= X.y){
			if (noreste == NULL)
				return NULL;
			return noreste->buscar(X);
		}else{
			if (sureste == NULL)
				return NULL;
			return sureste->buscar(X);
		}
	}
};

bool quadtree::enQuad(coord X){
	return (X.x >= esquina_arriba.x && X.x <= esquina_abajo.x && X.y >= esquina_arriba.y &&	X.y <= esquina_abajo.y);
}

int main(){
	//recibir profundidad(?) y cantidad de datos para obtener el color
	return 0;
}
