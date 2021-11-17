/****************************************************************
Proyecto final

Departamento de Ciencia de la Computación
Prof: D.Sc. Manuel Eduardo Loaiza Fernández

Alumnos:
 - Cristian Mellado Baca
 - Marcelo Torres Acuña
 - Alexander Carpio Mamani
*****************************************************************/

#include "City.h"

City::City(string world="nada", string name="nada"){
	this->world = world;
	houses[0] = House(0,5,name);
	
	// for(int i=1; i<limit;i++){
		// houses[i] = NULL;
	// }
	
	int n=5;
	for (int i=0;i<limit;i++){
		positions[i][0] = 0;
		positions[i][1] = n;
		n+=5;
	}
	positions[0][0] = 1;
}

void City::load_city(string arr[]){
	int index = 1;
	world = arr[0];
	
	for (int i=0;i<limit;i++){
		positions[i][0] = atoi(arr[index].c_str());
		index++;
	}
	
	for(int i=0; i<limit;i++){
		houses[i].load_house(arr, index);
		index += size_house;
	}

	game = true;
	calendar.load_calendar(arr, index);
}

void City::draw_game(){
	int n;
	bool house;
	char floor = char(254);
	
	for (int i=0; i<40; i++){
		for (int j=0; j<50; j++){
			house = false;
			for (int k=0; k<limit; k++){
				if (positions[k][0]==1){
					if (houses[k].request_house(j,i)){
						house = true;
						n = k;
					}
				}
			} 
     
			if (house){
				houses[n].draw_house(i);
			}
			else if (i==39){
				std::cout <<floor<<floor<<floor;
			}
			else{
				std::cout<<"   ";
			}
		}
		std::cout<<std::endl;
	}


	for (int i=0;i<limit;i++){
		if (positions[i][0]==1){
			cout<<" "<<i+1<<") "<<houses[i].name;
		}
	}
	
	cout << " 9) More options ";
}

void City::option_selected(char key){
	
	for (int i=0;i<limit;i++){
		if (positions[i][0]==1 && key == 49+i){
			city_houses(i);
		}
	}
	if (key == '9') more_options();
}

void City::more_options(){
	cout<<"\n\n 1) Tienda 2) Apuestas 3) Inversiones 4) Hacker mode 5) Save and exit";
	char key=getch();
	double total=0.0;
	cout<<"\n\n";
	
	switch(key){
		case '1':
			if (positions[0][0]==0 || positions[1][0]==0 || positions[2][0]==0 || positions[3][0]==0 ||
				positions[4][0]==0 || positions[5][0]==0 || positions[6][0]==0 || positions[7][0]==0){
				string name_local;
				char pos, h;
				bool ex;
				
				cout <<" :: Show houses ::\n\n";
				for (int i=0;i<4;i++){
					cout<<"\t\t"<<char(models[i][0])<<char(models[i][1])<<char(models[i][2]);
				}
				cout<<endl;
				for (int j=0;j<3;j++){
					for (int i=0;i<4;i++){
						cout<<"\t\t"<<char(models[i][3])<<char(models[i][4])<<char(models[i][5]);
					}
					cout<<endl;
				}
				for (int i=0;i<4;i++){
					cout<<"\tprice: "<<prices[i][0]<<" $";
				}
				cout<<endl;
				for (int i=0;i<4;i++){
					cout<<"\tmax pay: "<<prices[i][1]<<" $";
				}
				cout<<endl<<endl;
				do{
					cout<<" Select type house(1-4): ";cin>>h;
				}while(int(h)-48<1 || int(h)-48 > 4);
				
				if (money>= prices[int(h)-49][0]){
					fflush(stdin);
					cout<<"\n Enter local name: ";getline(cin,name_local);
					fflush(stdin);
					
					do{
						ex = false;
						cout<<" Enter local position(1-8): ";cin>>pos;
						for (int i=0;i<8;i++){
							if (int(pos)-48==i+1 && positions[i][0]==1) ex = true;
						}
					}while(ex || int(pos)-48 < 1 || int(pos)-48 > 8);
					
					houses[int(pos)-49] = House(int(h)-49,positions[int(pos)-49][1], name_local);
					
					pay_money(houses[int(pos)-49].price);
					
					positions[int(pos)-49][0] = 1;
					
					cout<<"\n :: Successful Purchase ::\n";
				}
				else{
					cout <<"\n You dont have enough money.\n";
					getch();
				}
			}
			break;
		case '2':
					total = games.menu_minigames();
					if (total<0.0){
						pay_money(-1.0*total);
					}
					else{
						receive_money(total);
					}
					break;
		case '3':
					total = inver.activar_inversion();
					if (total<0.0){
						pay_money(-1.0*total);
					}
					else{
						receive_money(total);
					}
					getch();
					break;
		case '4':
					total = games.hacker_mode();
					if (total<0.0){
						pay_money(-1.0*total);
					}
					else{
						receive_money(total);
					}
					getch();
					system("color 0F");
					break;
		case '5': game=false; break;
		default : break;
	}
}

void City::city_houses(int selected){
	char op;
	double dinero;
	bool exist;
	do{
		cout<<"\n\n ===> "<<houses[selected].name<<endl;
		cout<<" 1) Informacion acerca de la casa"<<endl;
		cout<<" 2) Agregar un piso"<<endl;
		cout<<" 3) Vender la casa"<<endl;
		cout<<" 4) Transferir dinero hacia otra casa"<<endl;
		cout<<" 5) Renombrar casa"<<endl;
		cout<<" 6) Change color"<<endl;
		cout<<" 7) Exit "<<endl;
		cout<<" opcion: ";cin>>op;
		cout<<endl;
		switch(op){
			case '1': 	houses[selected].house_info();
						getch();break;

			case '2': 
						houses[selected].add_house();
						getch();
						break;
			case '3':
					cout<<"\n You price house: "<<houses[selected].price<<" $"<<endl;
					
					do{
						exist=false;
						cout<<" Do you sell your house? (y/n): ";cin>>op;
						for (int i=0;i<limit;i++){
							if (positions[i][0]==0 && int(op)-49==i){
								exist = true;
							}
						}						
					}while(op!='y' && op!='n');
					
					if (op=='y'){
						positions[selected][0] = 0;
						receive_money(houses[selected].price);
		
						//houses[selected] = NULL;
						op = '7';
						cout<<"\n :: Successful Sale ::\n";
					}
					getch();break;
			case '4':
					cout<<"\n You money: "<<houses[selected].money<<" $"<<endl;
					for (int i=0;i<limit;i++){
						if (positions[i][0]==1 && selected!=i){
							cout<<" "<<i+1<<") "<<houses[i].name;
						}
					}
					cout<<endl<<endl;
					
					do{
						exist=false;
						cout<<" Enter house: ";cin>>op;
						for (int i=0;i<limit;i++){
							if (positions[i][0]==0 && int(op)-49==i){
								exist = true;
							}
						}						
					}while(exist || int(op)-49==selected || int(op)-48<1 || int(op)-48>8);
					
					do{
						cout<<" Enter money deposit to ("<<houses[int(op)-49].name<<"):";cin>>dinero;
					}while(dinero<0.0 || houses[selected].money<dinero);
					
					houses[selected].pay_amount(dinero);
					houses[int(op)-49].money += dinero;
					
					cout<<"\n :: Transferene Successful ::\n";
					getch();
					break;
			  
			case '5':
					houses[selected].rename_house();
					getch();
					break;
					
			case '6': 
						houses[selected].change_color();getch();break;
			case '7': break;
			
			default: 
					cout<<" No existe esa opcion."<<endl;
					break;
		}
	}while(op!='7');
}

void City::collect_money(){
	for (int i=0;i<limit;i++){
		if (positions[i][0]==1){
			houses[i].collect();
		}
	}
}

void City::receive_money(double total){
	refresh_account();
	double percentage;
	for (int i=0;i<limit;i++){
		if (positions[i][0]==1){
			percentage = houses[i].money / money;
			houses[i].money += total * percentage;
		}
	}
}

void City::pay_money(double p){
	refresh_account();
	double percentage;
	for (int i=0;i<limit;i++){
		if (positions[i][0]==1){
			percentage = houses[i].money / money;
			houses[i].pay_amount(p * percentage);
		}
	}
}

void City::refresh_account(){
	money = 0.0;
	for (int i=0;i<limit;i++){
		if (positions[i][0]==1){
			money += houses[i].money;
		}
	}
}


void City::pay_money_month(){
	for (int i=0;i<limit;i++){
		if (positions[i][0]==1){
			houses[i].payments();
		}
	}
}

void City::run_city() {
	char key;
	bool action;
	
	//system("color 0A");
	
	while(game){
		system(" ");
		system("cls");
		//std::cout<<"\033[H\033[2J\033[3J";
		
		refresh_account();
		action = calendar.draw_calendar(money);

		draw_game();
		
		key=getch();
		option_selected(key);
		
		if (action){
			collect_money();
		}
		else{
			pay_money_month();
		}
	}
	system("pause");
}

string City::save_city(){
	string all = "";
	all += world + ";";
	
	for (int i=0; i<limit; i++){
		all += to_string(positions[i][0]) + ";";
	}	
	
	for (int i=0; i<limit; i++){
		all += houses[i].save_house();
	}
	
	all += calendar.save_calendar();
	
	return all;
}