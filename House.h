/****************************************************************
Proyecto final

Departamento de Ciencia de la Computación
Prof: D.Sc. Manuel Eduardo Loaiza Fernández

Alumnos:
 - Cristian Mellado Baca
 - Marcelo Torres Acuña
 - Alexander Carpio Mamani
*****************************************************************/

#pragma once
#include <iostream>
#include <conio.h>
#include <time.h>
#include "Colors.cpp"
using namespace std;
				
class House{
	public:
		int limit, n, color, n_variables;
		int **house;
		int *model;
		string name;
		double price, pay, money, *money_month, tax, employees, light_and_water;
		
		House(int , int , string );
		virtual ~House();
		bool request_house(int,int);
		void add_house();
		void draw_house(int);
		void set_name_house(string);
		void set_color(int );
		void change_color();
		virtual void house_info();
		double get_money();
		virtual void collect();
		void pay_amount(double);
		void receive(double);
		void payments();
		virtual void load_house(string [], int &);
		virtual string save_house();
};