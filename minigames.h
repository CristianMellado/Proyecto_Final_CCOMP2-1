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
#include "Colors.cpp"
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
