#include <iostream>
#include <string>
#include <utility> //Para el pair
#include <vector> //Para el vector
#include <queue> //Para la PQ
#include <algorithm> //para el mergesort
#include "data.h"
#include "funciones.h"
#include "random_ppio.h"

using namespace std;

extern Data datos;

vector<int> busquedaLocal(vector<int> &solucion){
	vector<int> vecino;
	vector<int> bit;
	int contador=0;
	bool optimo=false,flag;
	int coste, costeVecino;

	bit.resize(datos.getTam(),0);
	vecino.resize(datos.getTam(),-1);
	coste=funcionCoste(solucion);

	while(!optimo && contador!=400){
		//cambiar semilla cada vez?
		optimo = true;
		for(int i=0; i<datos.getTam(); i++){
			if(bit[i]==0){
				flag=false;
				for(int j=0; j<datos.getTam(); j++){
					if(i!=j){
						//vecino = intercambiar(solucion,i,j);
						costeVecino=coste+factorizaCoste(vecino,i,j);
						contador++;
						if(costeVecino < coste){
							vecino = intercambiar(solucion,i,j);
							solucion=vecino;
							flag=true;
							optimo=false;
						}
					}
				}
				if(flag){
					bit[i]=1;
				}
			}
		}
	}
	return solucion;

}

//Funcion para calcular la factorizacion de coste
int factorizaCoste(vector<int> &sol, int &r, int &s){
	int coste = 0;

	for(int i = 0; i < datos.getTam(); i++){
			coste += (datos.getPosFlujo(r, i)*(datos.getPosDist(sol[s], sol[i]) - datos.getPosDist(sol[s], sol[i]) )) +
					 (datos.getPosFlujo(s, i)*(datos.getPosDist(sol[r], sol[i]) - datos.getPosDist(sol[s], sol[i]) )) +
					 (datos.getPosFlujo(i, r)*(datos.getPosDist(sol[i], sol[s]) - datos.getPosDist(sol[i], sol[r]) )) +
					 (datos.getPosFlujo(i, s)*(datos.getPosDist(sol[i], sol[r]) - datos.getPosDist(sol[i], sol[s]) ));
	}
	return coste;
}

vector <int> generarSolucion(){
	vector<int> salida;
	vector<int> apoyo;
	int valor;
	//inicializamos el vector
	salida.resize(datos.getTam(), -1);
	apoyo.resize(datos.getTam(), -1);

	for(int i=0; i<datos.getTam(); i++){
		valor=Randint(1, datos.getTam());
		if(apoyo[valor]==-1){
			salida[i]=valor;
			apoyo[valor]=0;
		}
	}
	//vemos si faltan valores por setear
	for(int j=0; j<datos.getTam();j++){
		if(apoyo[j]==-1){
			for(int k=0; k<datos.getTam(); k++){
				if(salida[k]==-1){
					salida[k]=j;
					apoyo[j]=0;
					break;
				}
			}
		}

	}
	return salida;
}

int funcionCoste(vector<int> solucion){
	int coste=0;
	for(int i=0; i<datos.getTam(); i++){
		for(int j=0; j<datos.getTam(); j++){
			if(i!=j){
				coste+=datos.getPosFlujo(i,j)*datos.getPosDist(solucion[i],solucion[j]);
			}
		}
	}
	return coste;
}

bool esta(int pos, vector<int> v){
	for(unsigned int i=0; i < v.size(); i++){
		if(pos == v[i]){	
			return true;
		}
	}
	return false;
}

vector<int> greedy(){
	vector<int> solucionGreedy(datos.getTam());
	vector<int> suma_fluj(datos.getTam());
	vector<int> suma_dist(datos.getTam());
	vector<int> aux_fluj(datos.getTam());
	vector<int> aux_dist(datos.getTam());
	int d=0, f=0;

	for(int i=0; i<datos.getTam(); i++){
		for(int j=0; j<datos.getTam(); j++){
			f += datos.getPosFlujo(i,j);
			d += datos.getPosDist(i,j);
		}

		suma_fluj[i] = f;
		suma_dist[i] = d;
		f = 0;
		d = 0;
	}
	aux_fluj = suma_fluj;
	aux_dist = suma_dist;

	std::sort(aux_fluj.begin(), aux_fluj.end());
	std::sort(aux_dist.begin(), aux_dist.end());

	ordenarPosiciones(suma_fluj, aux_fluj);
	ordenarPosiciones(suma_dist, aux_dist);
	
	voltearVector(suma_fluj);


	for(int i=0; i< datos.getTam(); i++){
		solucionGreedy[suma_fluj[i]] = suma_dist[i];
	}

	return solucionGreedy;
}

/**************************************************
*************** Ordenacion vectores ***************
**************************************************/
void ordenarPosiciones(vector<int> &salida, vector<int>origen){
	vector<int> auxS(datos.getTam());
	vector<int> mascara(datos.getTam());
	mascara=salida;

	for(int i=0; i<datos.getTam(); i++){//recorro el vector ordenado
		for(int j=0; j<datos.getTam(); j++){//recorro el original
			if(origen[i] == salida[j]){//si son iguales
				auxS[i] = j;//guardo en aux en la pos i la pos del valor que va ahi segun su orden
				salida[j]=-1;
				break;
			}
		}
	}
	salida = auxS;//guardo en salida los indices ya ordenados segun su contenido
}

void voltearVector(vector<int> &v){
	vector<int> salida;
	salida.resize(v.size(),-1);
	for(int i=0; i<datos.getTam(); i++){
		salida[i]=v[(datos.getTam()-1)-i];
	}
	v = salida;
}

vector<int> intercambiar(vector<int> &v, int pos1, int pos2){
	int aux,pos;
	vector<int> salida(v);
	pos = Randint(0,datos.getTam()-1);

	if(pos!=pos1 && pos!=pos2){
		aux=salida[pos1];
		salida[pos1]=salida[pos];
		salida[pos]=aux;
		return salida;
	}else{
		intercambiar(v, pos1, pos2);
	}
	return salida;
}