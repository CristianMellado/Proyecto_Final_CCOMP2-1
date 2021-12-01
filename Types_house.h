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
#define _GLIBCXX_USE_CXX11_ABI 0
#include "House.cpp"
#include "MiniGames.cpp"
#include "Inversion.cpp"
#include "City.h"

/*
casa Casino
casa Transactions
casa Properties(rename, vender)
casa Painters
casa Constructors
casa Stonks
casa Restaurant
casa Hotel
*/

class City;

class Casino : public House{
	public:
		MiniGames *games;
		Casino(int , int , std::string );
		~Casino();
		
		void menu_house(City *);
		void run_casino();
};


class Transactions : public House{
	public:
		Transactions(int , int , string );
		~Transactions();
		
		void menu_house(City *);
};


class Properties : public House{
	public:
		Properties(int , int , string );
		~Properties();
		
		void menu_house(City *);
};


class Painters : public House{
	public:
		Painters(int , int , string );
		~Painters();
		
		void menu_house(City *);
};


class Constructors : public House{
	public:
		Constructors(int , int , string );
		~Constructors();
		
		void menu_house(City *);
};


class Restaurant : public House{
	public:
		Restaurant(int , int , string );
		~Restaurant();
		
		void menu_house(City *);
};


class Stonks : public House{
	public:
		Inversion *inver;
		MiniGames *games;
		Stonks(int , int , string );
		~Stonks();
		
		void menu_house(City *);
};


class Hotel : public House{
	public:
		Hotel(int , int , string );
		~Hotel();
		
		void menu_house();
		void house_info();
		void collect();
};