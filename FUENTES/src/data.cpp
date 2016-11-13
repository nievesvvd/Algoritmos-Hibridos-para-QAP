#include <iostream>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string>
#include "data.h"
#include "random_ppio.h"

using namespace std;

void Data::leerFichero(const char *nombre){
	std::fstream myfile(nombre, std::ios_base::in);
	string cadena,valores;
	Set_random(74695481);//asignamos una semilla

	getline (myfile,cadena);
	tam = atoi(cadena.c_str()); 
	setTam(tam);
	//creamos las dos matrices del tamaño establecido en el fichero
	flujo.resize(tam);
	distancia.resize(tam);
	for(int i=0; i<tam; i++){
		flujo[i].resize(tam);
		distancia[i].resize(tam);
	}
	
	while(!myfile.eof()){
		//procedemos a leer el fichero
		
		getline(myfile, cadena);	//leemos el salto de linea entre datos.

		//leemos datos de la matriz de flujo y los guardamos 
		for(int i=0; i<tam; i++){//filas
			//getline(myfile, valores, ' ');
			for(int j=0; j<tam; j++){
				myfile >> flujo[i][j];
			}
		}
		//getline(myfile, cadena); 	//leemos salto de linea entre matrices.

		//leemos datos de la matriz de distancia y los guardamos 
		for(int i=0; i<tam; i++){//filas
			//getline(myfile, valores, ' ');
			for(int j=0; j<tam; j++){
				myfile >> distancia[i][j];
			}

		}	
	}
}

Data::Data(){}

Data::~Data(){
	distancia.clear();	
	flujo.clear();	
	tam=0;
}