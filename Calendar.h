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
using namespace std;

class Calendar{
	public:
		Calendar();
		int day, year, month, interval;
		bool update_calendar();
		bool draw_calendar(double );
		void load_calendar(string [], int);
		string save_calendar();
};