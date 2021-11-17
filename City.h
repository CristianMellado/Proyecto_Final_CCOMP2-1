/****************************************************************
Proyecto final

Departamento de Ciencia de la Computación
Prof: D.Sc. Manuel Eduardo Loaiza Fernández

Alumnos:
 - Cristian Mellado Baca
 - Marcelo Torres Acuña
 - Alexander Carpio Mamani
*****************************************************************/

#include "House.cpp"
#include "Calendar.cpp"
#include "minigames.cpp"
#include "inversion.cpp"

class City{
	public:
		string world;
		int limit = 8, positions[8][2], size_house=18;
		double money=0.0;
		House houses[8];
		bool game = true;
		Calendar calendar;
		MiniGames games;
		Inversion inver;
	
		City(string, string);
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