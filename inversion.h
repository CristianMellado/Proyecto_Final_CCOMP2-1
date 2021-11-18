/****************************************************************
Proyecto final

Departamento de Ciencia de la Computación
Prof: D.Sc. Manuel Eduardo Loaiza Fernández

Alumnos:
 - Cristian Mellado Baca
 - Marcelo Torres Acuña
 - Alexander Carpio Mamani
*****************************************************************/

#include <iostream>
#include <time.h>
#include <conio.h>
#include <fstream>
#include "Colors.cpp"
using namespace std;

class Inversion{
	public:
		int n_ask;
		double capital, monto;
		string *preguntas;
		int *correct;
	  
		Inversion();
		~Inversion();
		double activar_inversion();
		string gen_bar(int,int);
};