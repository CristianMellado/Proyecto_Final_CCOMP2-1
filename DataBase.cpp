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

DataBase::DataBase(){
	cities = nullptr;
	
	getcwd(dir_worlds, 256);
	strcat(dir_worlds, "\\worlds.txt");
	//strcpy(dir_worlds, "worlds.txt");
	
	getcwd(dir_database, 256);
	strcat(dir_database, "\\database.txt");
	//strcpy(dir_database, "database.txt");
	
	getcwd(dir_copy, 256);
	strcat(dir_copy, "\\copy_database.txt");
	//strcpy(dir_copy, "copy_database.txt");
}

DataBase::~DataBase(){
	if (cities){ //  if cities is diff to nullptr.
		delete cities;
	}
	if(arr){
		delete[] arr;
	}
}


void DataBase::create_new_data(string world, string name){
	ifstream read_file, w_r;
	ofstream write_file, w_a;
	
	read_file.open(dir_database, ios::in);
	w_r.open(dir_worlds, ios::in);
	
	// read_file.open("database.txt", ios::in);
	// w_r.open("worlds.txt", ios::in);
	
	if(read_file.fail() || w_r.fail()){
		read_file.close();
		w_r.close();
		write_file.open(dir_database, ios::out);
		w_a.open(dir_worlds, ios::out);
		
		// write_file.open("database.txt", ios::out);
		// w_a.open("worlds.txt", ios::out);
		
		if (write_file.fail() || w_a.fail()){
			write_file.close();
			w_a.close();
			cout<<"\n\n Error con algun archivo, cierre el programa y compile de nuevo.\n\n";
			getch();
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
	
	write_file.open(dir_database, ios::app);
	w_a.open(dir_worlds, ios::app);
	
	// write_file.open("database.txt", ios::app);
	// w_a.open("worlds.txt", ios::app);
	
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
		cities->receive_money(1000000.0);
		
		w_a<<world<<endl;
		w_a.close();
		
		cities->run_city();
		
		write_file<<cities->save_city()<<endl;
		write_file.close();
		
		delete cities;
		cities = nullptr;
	}
}

void DataBase::load_data(){
	ifstream read_file, world_file;

	read_file.open(dir_database, ios::in);
	world_file.open(dir_worlds, ios::in);
	
	// read_file.open("database.txt", ios::in);
	// world_file.open("worlds.txt", ios::in);
	
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
			cout<<" "<<i+1<<") "<<info<<endl;
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
			//cout<<"==> "<<i <<" : "<<info<<endl;
			if(info.length() > 2){
				if (i==select) break;
				i++;
			}
		}
		read_file.close();
		
		
		get_data(info); // separate the data in an array.
		
		cities = new City;
		cities->load_city(this->arr);
		cities->run_city();	
		
		save_data(cities->save_city(), select);
		
		delete cities;
		cities = nullptr;
	}
}

void DataBase::data_len(string data){
	// stringstream input(data);
	// int n = 0;
	// for (string element; input.getline(&element[0], sizeof(string), ';'); ) {
		// n++;
    // }	
	// return n;
	len_data = 0;
	for (int i=0; i<data.length(); i++){
		if(data[i] == ';')
			len_data++;
    }	
}

void DataBase::get_data(string data){
	// stringstream input(data);
    
	// int i = 0;
	// for (string element; input.getline(&element[0], 24, ';'); ) {
        // arr[i] = &element[0];
		// i++;
    // }
	
	data_len(data);  // calculate the number of variables.
	
	string word = "";
	arr = new string [len_data];
	
	int n = 0;
	for (int i=0; i<data.length(); i++){
		if(data[i] == ';'){
			arr[n] = word;
			word = "";
			n++;
		}
		else{
			word += data[i];
		}
    }
}

void DataBase::save_data(string data, int index){
	ifstream read_file, copy_read;
	ofstream write_file, copy_file;

	read_file.open(dir_database, ios::in);
	copy_file.open(dir_copy, ios::out);

	// read_file.open("database.txt", ios::in);
	// copy_file.open("copy_database.txt", ios::out);
	
	if(read_file.fail() || copy_file.fail()){
		read_file.close();
		copy_file.close();
		cout<<"\n\n Error con algun archivo, cierre el programa y compile de nuevo.\n\n";
		getch();
		//exit(1);
	}
	else{
		string info;
		while(!read_file.eof()){
			getline(read_file, info);
			if(info.length() > 2) copy_file<<info<<endl;
		}
		read_file.close();
		copy_file.close();

		remove(dir_database);
		copy_read.open(dir_copy, ios::in);
		write_file.open(dir_database, ios::out);

		// remove("database.txt");
		// copy_read.open("copy_database.txt", ios::in);
		// write_file.open("database.txt", ios::out);
		
		if(copy_read.fail() || write_file.fail()){
			cout<<"\n\n Error con algun archivo, cierre el programa y compile de nuevo.\n\n";
			getch();
			//exit(1);
		}

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

		remove(dir_copy);
		// remove("copy_database.txt");
	}	
}