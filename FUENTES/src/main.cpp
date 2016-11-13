#include <iostream>
#include <vector>
#include <utility>
#include <time.h>
#include <string>
#include "AGG.h"
#include "funciones.h"
#include "data.h"

using namespace std;

Data datos;

int main(int argc, char const *argv[]){

	vector<int> solucionAGGpos, solucionGreedy;
	clock_t start;
	double timeAGGpos, timeGreedy;
	int seed;


	//Set_random(seed);
	//cout << "La semilla usada es: " << Get_random() << endl;
	datos.leerFichero(argv[1]);
	if(argc==4){
		seed=atoi(argv[3]);
		Set_random(seed);
	}
	cout << "La semilla establecida es: " << Get_random() << endl;
	

	//////////////////////////AGG posicion//////////////////////////
	if(strcmp(argv[2],"t")==0){
		start=clock();
		solucionAGGpos = algoritmoGGeneracional('t');
		timeAGGpos=((double)clock() - start) / CLOCKS_PER_SEC;
		
	//////////////////////////AGG posicion//////////////////////////
		cout << "//////////////////////////AM-(10,1.0)//////////////////////////" <<endl;
		cout << "La solucion hibirda para el fichero " << argv[1] << " tiene un coste de: "<< funcionCoste(solucionAGGpos) << endl;
		/*for(unsigned int i=0; i<solucionAGGpos.size(); i++){
			cout << solucionAGGpos[i]+1 << " ";
		}*/
		//cout << endl;
		//cout << "Su coste es del: " << funcionCoste(solucionAGGpos) << endl;
		cout << "Y tarda: " << timeAGGpos << endl;
	}
	//////////////////////////AGG posicion//////////////////////////
	if(strcmp(argv[2],"s")==0){
		start=clock();
		solucionAGGpos = algoritmoGGeneracional('s');
		timeAGGpos=((double)clock() - start) / CLOCKS_PER_SEC;
			
		//////////////////////////AGG posicion//////////////////////////
		cout << "//////////////////////////AM-(10,0.1)//////////////////////////" <<endl;
		cout << "La solucion hibirda para el fichero " << argv[1] << " tiene un coste de: "<< funcionCoste(solucionAGGpos) << endl;
			/*for(unsigned int i=0; i<solucionAGGpos.size(); i++){
				cout << solucionAGGpos[i]+1 << " ";
			}
			cout << endl;
			cout << "Su coste es del: " << funcionCoste(solucionAGGpos) << endl;*/
		cout << "Y tarda: " << timeAGGpos << endl;
	}
	//////////////////////////AGG posicion//////////////////////////
	if(strcmp(argv[2],"m")==0){
		start=clock();
		solucionAGGpos = algoritmoGGeneracional('m');
		timeAGGpos=((double)clock() - start) / CLOCKS_PER_SEC;
			
		//////////////////////////AGG posicion//////////////////////////
		cout << "//////////////////////////AM-(10,0.1mej)//////////////////////////" <<endl;
		cout << "La solucion hibirda para el fichero " << argv[1] << " tiene un coste de: "<< funcionCoste(solucionAGGpos) << endl;
		/*for(unsigned int i=0; i<solucionAGGpos.size(); i++){
			cout << solucionAGGpos[i]+1 << " ";
		}
		cout << endl;
		cout << "Su coste es del: " << funcionCoste(solucionAGGpos) << endl;*/
		cout << "Y tarda: " << timeAGGpos << endl;
	}
	////////////////////////// Greedy //////////////////////////
	start=clock();
	solucionGreedy = greedy();
	timeGreedy=((double)clock() - start) / CLOCKS_PER_SEC;
		
	////////////////////////// Greedy //////////////////////////
	cout << "////////////////////////// Greedy //////////////////////////" <<endl;
	cout << "La solucion memetica para el fichero " << argv[1] << " tiene un coste de: "<< funcionCoste(solucionGreedy) << endl;
	/*for(unsigned int i=0; i<solucionGreedy.size(); i++){
		cout << solucionGreedy[i]+1 << " ";
	}
	cout << endl;
	cout << "Su coste es del: " << funcionCoste(solucionGreedy) << endl;*/
	cout << "Y tarda: " << timeGreedy << endl; 

	return 0;
}