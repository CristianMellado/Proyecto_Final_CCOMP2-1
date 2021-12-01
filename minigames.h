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
#include <string.h>
#include <unistd.h>
#include "Colors.cpp"
using namespace std;

class MiniGames{
	public:
		char directory_hacker[256];
		double entry, total, tictac_money, snake_money, rulette_money;
		
		MiniGames();
		~MiniGames();
		double menu_minigames();
		double TicTacToe();
		double Snake();
		double Rulette();
		double hacker_mode();
};