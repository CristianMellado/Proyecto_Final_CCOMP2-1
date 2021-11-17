/****************************************************************
Proyecto final

Departamento de Ciencia de la Computación
Prof: D.Sc. Manuel Eduardo Loaiza Fernández

Alumnos:
 - Cristian Mellado Baca
 - Marcelo Torres Acuña
 - Alexander Carpio Mamani
*****************************************************************/

#include "DataBase.h"

void DataBase::menu_start(){
	ifstream datos; 
	string info, world, name;
	char key; 
	int one_t = 19, one_b=26, two_t = 27, two_b = 34, i=1;
	bool one=true, two=false;

	while(1){
		//datos.open("inicio.txt", ios::in);  
			
		do{
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
			
			create_new_data(world, name);
		}
		else{
			cout<<"\n =======>>> WORLDS =======>>>\n\n";
			load_data();
		}
		
	}
}


void DataBase::create_new_data(string world, string name){
	ifstream read_file, w_r;
	ofstream write_file, w_a;
	
	read_file.open("database.txt", ios::in);
	w_r.open("worlds.txt", ios::in);
	
	if(read_file.fail() || w_r.fail()){
		read_file.close();
		w_r.close();
		write_file.open("database.txt", ios::out);
		w_a.open("worlds.txt", ios::out);
		
		if (write_file.fail() || w_a.fail()){
			write_file.close();
			w_a.close();
			exit(1);
		}
		else{
			write_file.close();
			w_a.close();
		}
	}
	else{
		read_file.close();
		w_r.close();
	}
	
	
	write_file.open("database.txt", ios::app);
	w_a.open("worlds.txt", ios::app);
	
	if(write_file.fail()){
		cout<<"\n Error, NO se pudo añadir elementos al archivo."<<endl;
		system("pause");
		//exit(1);
		write_file.close();
		w_a.close();
		cout<<"\n\n :: Cant create the data :: \n\n";
		getch();
		//exit(1);
	}
	else{
		cities = new City(world, name);
		cities->houses[0].money = 1000000.0;
		
		w_a<<world<<endl;
		w_a.close();
		
		cities->run_city();
		
		write_file<<cities->save_city()<<endl;
		write_file.close();
		
		delete cities;
	}
}

void DataBase::load_data(){
	ifstream read_file, world_file;

	read_file.open("database.txt", ios::in);
	world_file.open("worlds.txt", ios::in);
	if(read_file.fail() || world_file.fail()){
		read_file.close();
		world_file.close();
		cout<<"\n\n :: Data doesnt exist :: \n\n";
		getch();
		//exit(1);
	}
	else{
		int i=0, select;
		string info;
		while(!world_file.eof()){
			getline(world_file, info);
			if (info=="") break;
			cout<<i+1<<") "<<info<<endl;
			i++;
		}
		world_file.close();

		cout<<endl;
		
		do{
			cout<<" Enter world(1-"<<i<<"): ";cin>>select;
		}while(select<1 || select >i);
		
		i = 1;
		while(!read_file.eof()){
			getline(read_file, info);
			if (i==select) break;
			i++;
		}
		read_file.close();
		
		string arr[n_data];
		get_data(info, arr);
		
		cities = new City;
		cities->load_city(arr);
		cities->run_city();
		
		save_data(cities->save_city(), select);
		
		delete cities;
	}
}

void DataBase::save_data(string data, int index){
	ifstream read_file, copy_read;
	ofstream write_file, copy_file;

	read_file.open("database.txt", ios::in);
	copy_file.open("copy_database.txt", ios::out);
	
	if(read_file.fail() || copy_file.fail()){
		read_file.close();
		copy_file.close();
		exit(1);
	}
	else{
		string info;
		while(!read_file.eof()){
			getline(read_file, info);
			copy_file<<info<<endl;
		}
		read_file.close();
		copy_file.close();

		remove("database.txt");
		copy_read.open("copy_database.txt", ios::in);
		write_file.open("database.txt", ios::out);

		int i = 1;
		while(!copy_read.eof()){
			getline(copy_read, info);
			if (index == i){
				write_file<<data<<endl;
			}
			else{
				write_file<<info<<endl;
			}
			i++;
		}
		copy_read.close();
		write_file.close();

		remove("copy_database.txt");
	}	
}


void DataBase::get_data(string data, string arr[]){
	istringstream input(data);
    
	int i = 0;
	for (string element; input.getline(&element[0], 24, ';'); ) {
        	arr[i] = &element[0];
		i++;
    }
}
