/****************************************************************
Proyecto final

Departamento de Ciencia de la Computación
Prof: D.Sc. Manuel Eduardo Loaiza Fernández

Alumnos:
 - Cristian Mellado Baca
 - Marcelo Torres Acuña
 - Alexander Carpio Mamani
*****************************************************************/

#include "Menu.h"

Menu::Menu(){
	db = new DataBase();
	
	//getcwd(dir_menu, 256);
	//strcat(dir_menu, "inicio.txt");	
	//strcpy(dir_menu, "inicio.txt");
}

Menu::~Menu(){
	delete db;
}

void Menu::menu_start(){
	ifstream datos; 
	string info, world, name;
	char key;
	int one_t = 19, one_b=26, two_t = 27, two_b = 34, i=1;
	bool one=true, two=false;

	while(1){
		//datos.open("inicio.txt", ios::in); 
		do{
			//datos.open(dir_menu, ios::in); 
			datos.open("inicio.txt", ios::in); 
			i = 1;
			system("cls");
			if(datos.fail()){
				cout<<" Error. file didnt find of menu start."<<endl;
				system("pause");
				exit(1);
			}
			else{
				while(!datos.eof()){
					
					if ((one && i >=one_t && i<=one_b) || (two && i >=two_t && i<=two_b)){
						cout<<BLOCK_GREEN<<BLACK;
					}
					getline(datos, info);
					cout<<info<<RESET<<endl;	
					i++;
				}
				datos.close();
				//datos.clear();
				//datos.seekg(0, ios::beg);
			}
			
			key = 'a';
			if (kbhit()){
				key = getch();
				if (key=='w'){
					one = true;
					two = false;
				}
				else if (key=='s'){
					one = false;
					two = true;
				}
			}
			
		}while(key!=13);
		
		system("cls");
		//cities = nullptr;
		if (one){
			cout<<"\n =======>>> NEW WORLD =======>>>\n\n";
			fflush(stdin);
			cout<<" Enter world name: ";getline(cin,world);
			fflush(stdin);
			cout<<" Enter first local name: ";getline(cin,name);
			fflush(stdin);
			
			db->create_new_data(world, name);
		}
		else{
			cout<<"\n =======>>> WORLDS =======>>>\n\n";
			db->load_data();
		}
	}
}