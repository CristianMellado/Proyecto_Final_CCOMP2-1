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
#include "Types_house.cpp"
//#include <sstream>

class City;

class DataBase{
	public:
		int len_data;
		string *arr;
		City *cities;
		char dir_worlds[256], dir_database[256], dir_copy[256];
		
		DataBase();
		~DataBase();

		void load_data();
		void create_new_data(string, string);
		void save_data(string, int);
		void get_data(string);
		void data_len(string);
};