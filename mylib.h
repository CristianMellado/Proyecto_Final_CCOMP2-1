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
#include <conio.h>
#include <fstream>
#include <windows.h>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"   
#define GREEN   "\033[32m"    
#define YELLOW  "\033[33m"     
#define WHITE   "\033[37m"      

#define BLOCK_BLACK   "\033[40m"      
#define BLOCK_RED     "\033[41m"     
#define BLOCK_GREEN   "\033[42m"      
#define BLOCK_YELLOW  "\033[43m"     
#define BLOCK_BLUE    "\033[44m"    
#define BLOCK_MAGENTA "\033[45m"      
#define BLOCK_CYAN    "\033[46m"    
#define BLOCK_WHITE   "\033[47m"      

#define BLOCK_LIGHT_BLACK   "\033[100m"     
#define BLOCK_LIGHT_RED     "\033[101m"      
#define BLOCK_LIGHT_GREEN   "\033[102m"      
#define BLOCK_LIGHT_YELLOW  "\033[103m"      
#define BLOCK_LIGHT_BLUE    "\033[104m"     
#define BLOCK_LIGHT_MAGENTA "\033[105m"     
#define BLOCK_LIGHT_CYAN    "\033[106m"      
#define BLOCK_LIGHT_WHITE   "\033[107m"  

using namespace std;

class MiniGames{
	public:
		double entry=100.0, total=0.0, tictac_money = 200.0, snake_money=10.0, rulette_money = 200.0;
		
		double menu_minigames();
		double TicTacToe();
		double Snake();
		double Rulette();
		double hacker_mode();
};

class Inversion{
	public:
		int n_ask = 14;
		double capital=0.0, monto=0.0;
		string preguntas[14]={
			" Cual es el cerebro de una computadora?\n1) El procesador\n2) El disco duro\n3) La memoria ram",
		
			" Cómo se le llama a una colección de revistas, diarios y publicaciones periódicas?\n 1) hemeroteca\n 2) biblioteca\n 3) reviteca",
		
			" Cuál fue el primer metal que empleó el hombre?\n 1) Hierro\n 2) Cobre\n 3) Acero", 

			" Cuanto es el IGV?\n 1) 18% \n 2) 22%\n 3) 16%",

			" En que año el Perú logró su independencia?\n 1) 1821\n 2) 1848\n 3) 1813",

			" Cual es la capital del pais de Bogota?\n 1) Ninguna de las anteriores\n 2) Colombia\n 3) Medellin",

			" Cual es el pais mas pequeño?\n 1) El Vaticano\n 2) Monaco \n 3) Maldivas",

			" Cuanto duro la guerra de 100 años?\n 1) 116 años\n 2) 100 años\n 3) 99 años",

			" Cual es el sistema operativo para pc's mas usado?\n 1) Windows\n 2) Linux\n 3) Mac", 

			" Quien es el o la cantante mas famoso(a) peruano?\n 1) Yma Sumac\n 2) Eva Ayllon\n 3) Faraon Love Shady",

			" En qué año murió Steve Jobs?\n 1) 1999\n 2) 2010\n 3) 2011",

			" Cómo se llama la primera estación espacial rusa?\n 1) Sputnik I\n 2) Sputnik\n 3) Mir", 

			" Quien fue uno de los creadores de google?\n 1) Larry Page\n 2) Bill gates\n 3) Steve Jobs",
	
			" Quien escribio la novena sinfonia de Beethoven?\n 1) Beethoven y Chopin\n 2) Tu vieja\n 3) Tu viejo",
		
			};

		int correct[20] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	  
	  double activar_inversion();
	  string gen_bar(int,int);
};


class House{
	public:
		int limit = 30, n=2;
		int house[30][2];
		char model[6];
		string name, color;
		double price, pay, money, money_month[4], tax, employees, light_and_water;
		
		House(int h, int x, string name);
		bool request_house(int,int);
		void add_house();
		void draw_house(int);
		void rename_house();
		void change_color();
		void house_info();
		void collect();
		void pay_amount(double);
		void payments();
};

class Calendar{
	private:
		int day=1, year=2021, month=1, interval=7;
	
	public:
		bool update_calendar(){
			bool action = true;
			day += interval;
			if (month>12){
				month = 1;
				year++;
			}
			if (day > 30){
				day -= 30;
				month++;
				action = false;
			}
			return action;
		}
		bool draw_calendar(double money){
			cout<<"\n Money: "<<money<<" $\t Calendar: "<<year;
			switch (month){
				case 1: cout<<" January ";break;
				case 2: cout<<" February ";break;
				case 3: cout<<" March ";break;
				case 4: cout<<" April ";break;
				case 5: cout<<" May ";break;
				case 6: cout<<" June ";break;
				case 7: cout<<" July ";break;
				case 8: cout<<" August ";break;
				case 9: cout<<" September ";break;
				case 10: cout<<" October ";break;
				case 11: cout<<" November ";break;
				case 12: cout<<" December ";break;
			}
			
			cout <<day<<endl;
			
			return update_calendar();
		}
};


class City{
	public:
		string world;
		int limit = 8, n_houses=1, positions[8][2], index_memory;
		double money=0.0;
		House *houses[8];
		bool game = true;
		Calendar calendar;
		MiniGames games;
		Inversion inver;
	
		City(string, string, int);
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
};

class DataBase{
	public:
		City *cities;
		int n_city = 0;
		FILE *file;
		void menu_start();
		/*
		bool load_data();
		bool create_new_data(string, string);
		void save_data(int);
		*/
};