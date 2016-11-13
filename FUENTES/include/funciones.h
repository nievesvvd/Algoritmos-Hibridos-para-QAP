#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm> //para el mergesort
#include "data.h"
#include "random_ppio.h"

using namespace std;


int funcionCoste(vector<int> solucion);
vector <int> generarSolucion();
bool esta(int pos, vector<int> v);

vector<int> greedy();
vector<int> busquedaLocal(vector<int> &solucion);
int factorizaCoste(vector<int> &sol, int &r, int &s);
void ordenarPosiciones(vector<int> &salida, vector<int>origen);
void voltearVector(vector<int> &v);
//int intercambiarPos(vector<int> &v,vector<int> &vecino, int pos1, int pos2);
vector<int> intercambiar(vector<int> &v, int pos1, int pos2);
#endif