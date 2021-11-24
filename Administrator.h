/****************************************************************
Proyecto final

Departamento de Ciencia de la Computación
Prof: D.Sc. Manuel Eduardo Loaiza Fernández

Alumnos:
 - Cristian Mellado Baca
 - Marcelo Torres Acuña
 - Alexander Carpio Mamani
*****************************************************************/

#include "City.cpp"
#include "DataBase.h"

class Admi : public DataBase{
	public:
		int n_data;
		City *cities;
		FILE *file;
		
		Admi();
		void menu_start();
		void create_new_data(string, string);
		void load_data();
		void save_data(string, int);
		void get_data(string, string[]);
};