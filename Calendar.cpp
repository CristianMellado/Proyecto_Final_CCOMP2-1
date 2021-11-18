/****************************************************************
Proyecto final

Departamento de Ciencia de la Computación
Prof: D.Sc. Manuel Eduardo Loaiza Fernández

Alumnos:
 - Cristian Mellado Baca
 - Marcelo Torres Acuña
 - Alexander Carpio Mamani
*****************************************************************/

#include "Calendar.h"

Calendar::Calendar(){
	day=1;
	year=2021; 
	month=1;
	interval=7;
}

bool Calendar::update_calendar(){
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
		

bool Calendar::draw_calendar(double money){
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

void Calendar::load_calendar(string arr[], int index){
	day = atoi(arr[index].c_str());
	month = atoi(arr[index + 1].c_str());
	year = atoi(arr[index + 2].c_str());
}

string Calendar::save_calendar(){
	return to_string(day) + ";" + to_string(month) + ";" + to_string(year) + ";";
}


