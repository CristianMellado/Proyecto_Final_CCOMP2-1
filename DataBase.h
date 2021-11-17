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
#include <sstream>

class DataBase{
	public:
		int n_data = 156;
		City *cities = nullptr;
		FILE *file;
		void menu_start();
		void load_data();
		void create_new_data(string, string);
		void save_data(string, int);
		void get_data(string, string[]);
};