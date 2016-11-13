#include <iostream>
#include <string>
#include <utility> //Para el pair
#include <vector> //Para el vector
#include <queue> //Para la PQ
#include "data.h"
#include "AGG.h"
#include "funciones.h"
#include "random_ppio.h"

using namespace std;

extern Data datos;

vector<int> algoritmoGGeneracional(char tipo){
	vector<Individuo> ganadores;	//vector de vector de los ganadores
	vector<Individuo> poblacionV;	//vector de vector de la poblacion
	vector<Individuo> poblacionNV;	//vector de vector de la poblacion nueva 
	Individuo hijo1;
	Individuo hijo2;
	Individuo mejorPopOld;
	Individuo mejorPopNew;
	Generacion poblacion;
	Generacion poblacionNueva;
	vector<int> mejorPadre;
	Individuo busquedaL;
	Individuo memetico;

	unsigned int nTorneos=0;
	int contador=0, cruzan, tamP=50, valor1,valor2, k; 
	int cont=0, mutan,cont2=0, contBL=0;
	double pCruce,probMut=0.001, probBL=0.0;

	mejorPadre.resize(datos.getTam(), -1);
	hijo1.first.resize(datos.getTam(),-1);
	hijo2.first.resize(datos.getTam(),-1);
	mejorPopOld.first.resize(datos.getTam(),-1);
	mejorPopNew.first.resize(datos.getTam(),-1);
	int tope = tamP*0.1;
	cruzan = 0.7*tamP;
	mutan = int(tamP*datos.getTam()*probMut);

	//generamos la poblacion inicial y la guardamos en un vector y en la pq
	poblacionInicial(poblacionV,contador);
	for(unsigned int i=0; i< poblacionV.size(); i++){
		poblacion.push(poblacionV[i]);
	}
	//el mejor padre inicialmente es el mejor de la primera poblacion
	mejorPadre = poblacionV[0].first;
	//cout << tamP*0.1 << endl;
	while(contador < 25000){
		while(nTorneos!=poblacionV.size()){
			valor1 = Randint(0,poblacionV.size()-1);
			valor2 = Randint(0,poblacionV.size()-1);

			if(valor1!=valor2){
				if(poblacionV[valor1].second < poblacionV[valor2].second){
					ganadores.push_back(poblacionV[valor1]);
					nTorneos++;
				}else{
					ganadores.push_back(poblacionV[valor2]);
					nTorneos++;
				}
			}
		}
		//cout << "cruzan " << endl;
		while(cont <= cruzan){
				k=0;
				while(k!=tamP){
					pCruce = Rand();
					if(pCruce >= 0.7){
						hijo1.first.clear();
						hijo2.first.clear();
						hijo1.first.resize(datos.getTam(),-1);
						hijo2.first.resize(datos.getTam(),-1);		
						crucePosicion(ganadores[k], ganadores[(k+1)%tamP], hijo1, hijo2);
						cont++;
						contador++;
						k+=2;
					}
					//añadimos los dos hijos creados
						poblacionNV.push_back(hijo1);
						poblacionNV.push_back(hijo2);
				}
			//cout << "cont: " << cont << endl;
		}
		cont = 0;
		//cout << "mutamos" << endl;
		//mutacion
		while(cont2 != mutan){
			valor1 = Randint(0, tamP-1);//valor con el que tomamos el cromosoma a mutar
			valor2 = Randint(0, datos.getTam()-1);//valor con el que establecemos el gen del cromosoma a curzar
			mutar(poblacionNV[valor1], valor2);
			cont2++;
			contador++;
		}
		cont2=0;
		//añadimos la poblacion nueva a su pq antes de buscar el mejor
		for(int i=0; i < tamP; i++){
			poblacionNueva.push(poblacionNV[i]);
		}
		//actualizamos el contador de numero de generaciones
		contBL++;

		// *************** memeticos ***************//
		//cout << "Aplicamos memeticos" << endl;
		if(contBL% 10== 0){
			switch(tipo){
				case 't':
					for(int i=0; i < tamP; i++){
						memetico=poblacionNueva.top();
						busquedaL.first = busquedaLocal(memetico.first);
						poblacionNueva.pop();
						busquedaL.second = funcionCoste(busquedaL.first);
						if(memetico.second < busquedaL.second){
							poblacionNueva.push(memetico);
						}else{
							poblacionNueva.push(busquedaL);
						}
					}
				 break;
				case 's':
					for(int i=0; i < tamP; i++){
						probBL=Rand();
						if(probBL == 0.1){
							memetico=poblacionNueva.top();
							busquedaL.first = busquedaLocal(memetico.first);
							poblacionNueva.pop();
							busquedaL.second = funcionCoste(busquedaL.first);
							if(memetico.second < busquedaL.second){
								poblacionNueva.push(memetico);
							}else{
								poblacionNueva.push(busquedaL);
							}
						}
					}
				 break;
				case 'm':
					for(int i=0; i < tope; i++){
						memetico=poblacionNueva.top();
						busquedaL.first = busquedaLocal(memetico.first);
						poblacionNueva.pop();
						busquedaL.second = funcionCoste(busquedaL.first);
						if(memetico.second < busquedaL.second){
							poblacionNueva.push(memetico);
						}else{
							poblacionNueva.push(busquedaL);
						}
					}
				 break;
			}
		}
		// *************** memeticos ***************//

		//vemos cual es la mejor solucion hasta ahora
		mejorPopOld = poblacion.top();
		mejorPopNew = poblacionNueva.top();
		if(mejorPopOld.second < mejorPopNew.second){
			if(mejorPopOld.second < funcionCoste(mejorPadre) ){
				//actualizamos al mejor padre
				mejorPadre = mejorPopOld.first;
				contador++;
			}
		}

		//actualizamos poblacion
		for(int i=0; i<tamP; i++){
			poblacion.top();
			poblacion.pop();
		}
		for(int i=0; i<tamP; i++){
			//vaciar poblacion antes de añadir lo nuevo
			poblacion.push(poblacionNueva.top());
			poblacionNueva.pop();
		}
		for(int i=0; i< tamP; i++){
			poblacionV[i] = poblacionNV[i];
		}

	}
	return mejorPadre;
}

//////////////////////////// generacion de poblacion ////////////////////////////
void poblacionInicial(vector<Individuo> &ind, int &cont){
	Individuo miembro;
	vector<int> solucion;
	int coste=0, tamP=50;
	solucion.resize(0,datos.getTam());

	for(int i=0; i<tamP; i++){
		solucion = generarSolucion();
		coste = funcionCoste(solucion);
		cont++;

		miembro.first = solucion;
		miembro.second = coste;

		ind.push_back(miembro);		
	}
}

//////////////////////////// operadores de cruce ////////////////////////////
/**Cruce posicion: operador de cruce en el que para los hijos mantenemos las posiciones comunes
*de los dos padres y el resto de posiciones las establecemos de forma aleatoria
**/
void crucePosicion(Individuo padre, Individuo madre, Individuo &hijo1, Individuo &hijo2){
	vector <int> mascara1;
	vector <int> mascara2;
	int valor1,valor2/*,pos1=0,pos2=0*/;
	//bool terminado=false;
	
	mascara1.resize(datos.getTam(),-1);
	mascara2.resize(datos.getTam(),-1);

	//colocamos las posiciones comunes
	for(int i=0; i<datos.getTam(); i++){
		if(padre.first[i] == madre.first[i]){
			hijo1.first[i] = madre.first[i];
			hijo2.first[i] = madre.first[i];
			mascara1[padre.first[i]] = 0;//indicamos que hemos usado dicha pos
			mascara2[padre.first[i]] = 0;//indicamos que hemos usado dicha pos
		}
	}

	bool posEncontrada = false;
	for (unsigned i = 0; i < hijo1.first.size(); i++){
		if (hijo1.first[i] == -1){
			posEncontrada = false;
			while(!posEncontrada){
				valor1 =  Randint(0,datos.getTam()-1);
				if (mascara1[valor1] == -1){
					posEncontrada = true;
				}
			}
			hijo1.first[i] = valor1;
			mascara1[valor1]=0;
		}
	}

	for (unsigned i = 0; i < hijo2.first.size(); i++){
		if (hijo2.first[i] == -1){
			posEncontrada = false;
			while(!posEncontrada){
				valor2 =  Randint(0,datos.getTam()-1);
				if (mascara2[valor2] == -1){
					posEncontrada = true;
				}
			}
			hijo2.first[i] = valor2;
			mascara2[valor2]=0;
		}
	}

	hijo1.second = funcionCoste(hijo1.first);
	hijo2.second = funcionCoste(hijo2.first);
}

void mutar(Individuo &v, int crom){
	int valor = Randint(0, (v.first.size())-1);
	int aux;

	if(valor != crom){
		aux = v.first[crom];
		v.first[crom] = v.first[valor];
		v.first[valor] = aux;
	}
	v.second = funcionCoste(v.first);
}
