#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;


class Data{
    private:
        int tam;
        vector<vector<int> > flujo;
        vector<vector<int> > distancia;
    
    public:
    	Data();
		~Data();
    	
    	void leerFichero(const char *nombre);

        void setTam(int t){tam=t;}

    	int getTam(){return tam;}
    	
    	int getPosDist(int x, int y){
    		return distancia[x][y];
    	}

    	int getPosFlujo(int x, int y){
    		return flujo[x][y];
    	}

};

#endif