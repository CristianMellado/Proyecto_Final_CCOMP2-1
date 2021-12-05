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
#include "Types_house.h"
#include "Calendar.cpp"

class City{
	public:
		string world;
		int limit, **positions;
		double money;
		
		Casino *casino;
		Transactions *transactions;
		Properties *properties;
		Painters *painters;
		Constructors *constructors;
		Stonks *stonks;
		Restaurant *restaurant;
		Hotel *hotel;
		
		bool game;
		Calendar calendar;
	
		City(string, string);
		~City();
		void draw_game();
		void option_selected(char );
		void more_options();
		void collect_money();
		void pay_money_month();
		void pay_money(double);
		void refresh_account();
		void city_houses(int );
		void run_city();
		void receive_money(double);
		void load_city(string []);
		string save_city();
};