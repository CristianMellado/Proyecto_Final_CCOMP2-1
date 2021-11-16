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
		int day=1, year=2021, month=1, interval=7;
		bool update_calendar();
		bool draw_calendar(double );
		void load_calendar(string [], int);
		string save_calendar();
};