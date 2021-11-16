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
#include "Colors.cpp"
using namespace std;

class House{
	public:
		int limit = 30, n=2, color;
		int house[30][2];
		int model[6];
		string name;
		double price, pay, money, money_month[4], tax, employees, light_and_water;
		
		House(int , int , string );
		bool request_house(int,int);
		void add_house();
		void draw_house(int);
		void rename_house();
		void change_color();
		void house_info();
		void collect();
		void pay_amount(double);
		void payments();
		void load_house(string [], int);
		string save_house();
};