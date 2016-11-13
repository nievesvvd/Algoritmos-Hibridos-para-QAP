#ifndef AGG_H
#define AGG_H
#include <iostream>
#include <string>
#include <utility> //Para el pair
#include <vector> //Para el vector
#include <queue> //Para la PQ
#include "data.h" 
#include "random_ppio.h"

//**************************** Ayuda para PQ y pair ****************************//
typedef std::pair <std::vector <int>, int> Individuo;

class comparaCromosomas{ //Comparador de la PQ. Devuelve TRUE si coste de individuo1 es mayor que coste de individuo2
public:
  comparaCromosomas(){}
  bool operator()(const Individuo individuo1, const Individuo individuo2){
    return individuo1.second > individuo2.second;
  }
};

typedef std::priority_queue<Individuo , vector <Individuo> , comparaCromosomas > Generacion;

//**************************** Ayuda para PQ y pair ****************************//

vector<int> algoritmoGGeneracional(char tipo);
void poblacionInicial(vector<Individuo> &poblacion, int &contador);

void mutar(Individuo &v, int crom);
void crucePosicion(Individuo padre, Individuo madre, Individuo &hijo1, Individuo &hijo2);

#endif