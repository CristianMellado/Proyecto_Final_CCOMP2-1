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
		double entry, total, tictac_money, snake_money, rulette_money;
		MiniGames();
		double menu_minigames();
		double TicTacToe();
		double Snake();
		double Rulette();
		double hacker_mode();
};