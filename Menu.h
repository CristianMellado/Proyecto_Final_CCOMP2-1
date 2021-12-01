/****************************************************************
Proyecto final

Departamento de Ciencia de la Computación
Prof: D.Sc. Manuel Eduardo Loaiza Fernández

Alumnos:
 - Cristian Mellado Baca
 - Marcelo Torres Acuña
 - Alexander Carpio Mamani
*****************************************************************/

#include "DataBase.cpp"

class Menu{
	public:
		DataBase *db;
		//char dir_menu[256];
		
		Menu();
		~Menu();
		
		void menu_start();
};