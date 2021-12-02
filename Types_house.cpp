/****************************************************************
Proyecto final

Departamento de Ciencia de la Computación
Prof: D.Sc. Manuel Eduardo Loaiza Fernández

Alumnos:
 - Cristian Mellado Baca
 - Marcelo Torres Acuña
 - Alexander Carpio Mamani
*****************************************************************/

#include "Types_house.h"

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


// Casino
Casino::Casino(int house_type=0, int pos=5, string name="nothing"):House(house_type, pos, name){
	games = new MiniGames();
}

Casino::~Casino(){
	delete games;
}

void Casino::menu_house(City *city){
	char op;
	double total;
	do{
		cout<<"\n\n =========> "<<name<<"\n\n 1) Info house\n 2) Casino\n 3) Exit\n\n option: ";
		cin>>op;
		switch(op){
			case '1': 	house_info();
						break;
			case '2': 
						total = games->menu_minigames();
						if (total<0.0){
							city->pay_money(-1.0*total);
						}
						else{
							city->receive_money(total);
						}
						break;
		}
	}while(op!='3');
}


// Transactions
Transactions::Transactions(int house_type=0, int pos=5, string name="nothing"):House(house_type, pos, name){
	total = 0.0;
	from_money = 0.0;
}

Transactions::~Transactions(){
}

void Transactions::menu_house(City *city){
	char op, op2;
	bool exist;
	do{
		cout<<"\n\n =========> "<<name<<"\n\n 1) Info house\n 2) Trasfering money\n 3) Exit\n\n option: ";
		cin>>op;
		switch(op){
			case '1': 	house_info();
						break;
			case '2':
					//cout<<"\n You money: "<<money<<" $"<<endl;
					cout<<"\n\n =========> Transfering:\n";
					for (int i=0;i<city->limit;i++){
						if (city->positions[i][0]==1){
							cout<<" "<<i+1<<") ";
							switch(city->positions[i][2]){
								case 1: 
										cout<<city->restaurant->name;							
										break;
								case 2: 
										cout<<city->painters->name;						
										break;
								case 3: 
										cout<<city->constructors->name;	
										break;
								case 4: 
										cout<<city->properties->name;							
										break;
								case 5: 
										cout<<city->transactions->name;								
										break;
								case 6: 
										cout<<city->stonks->name;							
										break;
								case 7: 
										cout<<city->hotel->name;								
										break;
								case 8: 
										cout<<city->casino->name;								
										break;								
							}							
						}
					}
					cout<<endl<<endl;
					
					do{
						exist=false;
						cout<<" From: ";cin>>op;
						for (int i=0;i<city->limit;i++){
							if (city->positions[i][0]==0 && int(op)-49==i){
								exist = true;
							}
						}						
					}while(exist || int(op)-48<1 || int(op)-48>8);

					do{
						exist=false;
						cout<<" To: ";cin>>op2;
						for (int i=0;i<city->limit;i++){
							if (city->positions[i][0]==0 && int(op2)-49==i){
								exist = true;
							}
						}						
					}while(exist || int(op2)-48<1 || int(op2)-48>8);
					
					cout<<endl<<endl<<" Information account: \n ";
					
					switch(city->positions[int(op)-49][2]){
						case 1: 
								cout<<city->restaurant->name<<": "<<city->restaurant->get_money()<<"$";
								from_money = city->restaurant->get_money();
								break;
						case 2: 
								cout<<city->painters->name<<": "<<city->painters->get_money()<<"$";
								from_money = city->painters->get_money();								
								break;
						case 3: 
								cout<<city->constructors->name<<": "<<city->constructors->get_money()<<"$";	
								from_money = city->constructors->get_money();								
								break;
						case 4: 
								cout<<city->properties->name<<": "<<city->properties->get_money()<<"$";
								from_money = city->properties->get_money();																
								break;
						case 5: 
								cout<<city->transactions->name<<": "<<city->transactions->get_money()<<"$";
								from_money = city->transactions->get_money();																
								break;
						case 6: 
								cout<<city->stonks->name<<": "<<city->stonks->get_money()<<"$";
								from_money = city->stonks->get_money();																
								break;
						case 7: 
								cout<<city->hotel->name<<": "<<city->hotel->get_money()<<"$";
								from_money = city->hotel->get_money();																
								break;
						case 8: 
								cout<<city->casino->name<<": "<<city->casino->get_money()<<"$";
								from_money = city->casino->get_money();																
								break;								
					}					
					
					cout<<endl<<endl;
					
					do{
						cout<<" Enter money deposit to (";
						switch(city->positions[int(op2)-49][2]){
							case 1: 
									cout<<city->restaurant->name;							
									break;
							case 2: 
									cout<<city->painters->name;						
									break;
							case 3: 
									cout<<city->constructors->name;	
									break;
							case 4: 
									cout<<city->properties->name;							
									break;
							case 5: 
									cout<<city->transactions->name;								
									break;
							case 6: 
									cout<<city->stonks->name;							
									break;
							case 7: 
									cout<<city->hotel->name;								
									break;
							case 8: 
									cout<<city->casino->name;								
									break;								
						}						
						cout<<"):";
						cin>>total;
					}while(total<0.0 || from_money<total);
					
					switch(city->positions[int(op)-49][2]){
						case 1: 
								city->restaurant->pay_amount(total);							
								break;
						case 2: 
								city->painters->pay_amount(total);						
								break;
						case 3: 
								city->constructors->pay_amount(total);	
								break;
						case 4: 
								city->properties->pay_amount(total);							
								break;
						case 5: 
								city->transactions->pay_amount(total);								
								break;
						case 6: 
								city->stonks->pay_amount(total);							
								break;
						case 7: 
								city->hotel->pay_amount(total);								
								break;
						case 8: 
								city->casino->pay_amount(total);								
								break;								
					}	
					
					switch(city->positions[int(op2)-49][2]){
						case 1: 
								city->restaurant->receive(total);							
								break;
						case 2: 
								city->painters->receive(total);						
								break;
						case 3: 
								city->constructors->receive(total);	
								break;
						case 4: 
								city->properties->receive(total);							
								break;
						case 5: 
								city->transactions->receive(total);								
								break;
						case 6: 
								city->stonks->receive(total);							
								break;
						case 7: 
								city->hotel->receive(total);								
								break;
						case 8: 
								city->casino->receive(total);								
								break;								
					}	
					
					cout<<"\n :: Transferene Successful ::\n";
					getch();
					op = '2';
					break;
		}
	}while(op!='3');
}


//Properties
Properties::Properties(int house_type=0, int pos=5, string name="nothing"):House(house_type, pos, name){
	total = 0.0;
	rename = "";
}

Properties::~Properties(){
}

void Properties::menu_house(City *city){
	char op, op2;
	bool exist;
	do{
		cout<<"\n\n =========> "<<name<<"\n\n 1) Info house\n 2) Change name\n 3) Sell house\n 4) Exit\n\n option: ";
		cin>>op;
		switch(op){
			case '1': 	house_info();
						break;
			case '2':
					cout<<"\n\n =========> Renameming:\n";
					for (int i=0;i<city->limit;i++){
						if (city->positions[i][0]==1){
							cout<<" "<<i+1<<") ";
							switch(city->positions[i][2]){
								case 1: 
										cout<<city->restaurant->name;							
										break;
								case 2: 
										cout<<city->painters->name;						
										break;
								case 3: 
										cout<<city->constructors->name;	
										break;
								case 4: 
										cout<<city->properties->name;							
										break;
								case 5: 
										cout<<city->transactions->name;								
										break;
								case 6: 
										cout<<city->stonks->name;							
										break;
								case 7: 
										cout<<city->hotel->name;								
										break;
								case 8: 
										cout<<city->casino->name;								
										break;								
							}							
						}
					}
					cout<<endl<<endl;
					
					do{
						exist=false;
						cout<<" Select house: ";cin>>op;
						for (int i=0;i<city->limit;i++){
							if (city->positions[i][0]==0 && int(op)-49==i){
								exist = true;
							}
						}						
					}while(exist || int(op)-48<1 || int(op)-48>8);
					
					fflush(stdin);
					cout<<"\n Enter new name: ";getline(cin,rename);
					fflush(stdin);
					
					switch(city->positions[int(op)-49][2]){
						case 1: 
								city->restaurant->set_name_house(rename);
								break;
						case 2: 
								city->painters->set_name_house(rename);								
								break;
						case 3:
								city->constructors->set_name_house(rename);								
								break;
						case 4: 
								city->properties->set_name_house(rename);															
								break;
						case 5: 
								city->transactions->set_name_house(rename);																
								break;
						case 6: 
								city->stonks->set_name_house(rename);															
								break;
						case 7: 
								city->hotel->set_name_house(rename);															
								break;
						case 8: 
								city->casino->set_name_house(rename);																
								break;								
					}			
					
					cout<<"\n :: Successful Rename ::\n";
	
					getch();
					op = '2';
					break;
			case '3':
					cout<<"\n\n =========> Selling house:\n";
					for (int i=1;i<city->limit;i++){
						if (city->positions[i][0]==1){
							cout<<" "<<i+1<<") ";
							switch(city->positions[i][2]){
								// case 1: 
										// cout<<city->restaurant->name<<": "<<city->restaurant->price<<"$\n";
										// break;
								case 2: 
										cout<<city->painters->name<<": "<<city->painters->price<<"$\n";							
										break;
								case 3: 
										cout<<city->constructors->name<<": "<<city->constructors->price<<"$\n";						
										break;
								case 4: 
										cout<<city->properties->name<<": "<<city->properties->price<<"$\n";															
										break;
								case 5: 
										cout<<city->transactions->name<<": "<<city->transactions->price<<"$\n";															
										break;
								case 6: 
										cout<<city->stonks->name<<": "<<city->stonks->price<<"$\n";														
										break;
								case 7: 
										cout<<city->hotel->name<<": "<<city->hotel->price<<"$\n";															
										break;
								case 8: 
										cout<<city->casino->name<<": "<<city->casino->price<<"$\n";															
										break;								
							}						
						}
					}
					
					cout<<endl<<endl;
					
					do{
						exist=false;
						cout<<" Select house: ";cin>>op;
						for (int i=0;i<city->limit;i++){
							if (city->positions[i][0]==0 && int(op)-49==i){
								exist = true;
							}
						}						
					}while(exist || int(op)-48<2 || int(op)-48>8);
					
					cout<<"\n\n Remind: if you sell you house, you will lose\n\t all money of this house(";
					switch(city->positions[int(op)-49][2]){
						// case 1: 
								// cout<<city->restaurant->get_money();
								// break;
						case 2: 
								cout<<city->painters->get_money();						
								break;
						case 3: 
								cout<<city->constructors->get_money();
								break;
						case 4: 
								cout<<city->properties->get_money();							
								break;
						case 5: 
								cout<<city->transactions->get_money();							
								break;
						case 6: 
								cout<<city->stonks->get_money();							
								break;
						case 7: 
								cout<<city->hotel->get_money();								
								break;
						case 8: 
								cout<<city->casino->get_money();								
								break;								
					}						
					cout<<"$).\n Recommended: Use House Transactions.\n\n";
					
					
					cout<<" You want sell the house(";
					switch(city->positions[int(op)-49][2]){
						// case 1: 
								// cout<<city->restaurant->name;							
								// break;
						case 2: 
								cout<<city->painters->name;						
								break;
						case 3: 
								cout<<city->constructors->name;	
								break;
						case 4: 
								cout<<city->properties->name;							
								break;
						case 5: 
								cout<<city->transactions->name;								
								break;
						case 6: 
								cout<<city->stonks->name;							
								break;
						case 7: 
								cout<<city->hotel->name;								
								break;
						case 8: 
								cout<<city->casino->name;								
								break;								
					}
					cout<<") ? (yes: y, no: any key):";cin>>op2;

					if(op2=='y'){
						switch(city->positions[int(op)-49][2]){
							// case 1: 
									// total = city->restaurant->price;
									// break;
							case 2: 
									total = city->painters->price;								
									break;
							case 3: 
									total = city->constructors->price;								
									break;
							case 4: 
									total = city->properties->price;													
									break;
							case 5: 
									total = city->transactions->price;								
									break;
							case 6: 
									total = city->stonks->price;								
									break;
							case 7: 
									total = city->hotel->price;								
									break;
							case 8: 
									total = city->casino->price;									
									break;								
						}
						city->positions[int(op)-49][0] = 0;
						city->receive_money(total);
						
						cout<<"\n :: Successful Selling ::\n";
						getch();
					}
					op = '3';
					break;			
		}
	}while(op!='4');
}


// Painters
Painters::Painters(int house_type=0, int pos=5, string name="nothing"):House(house_type, pos, name){
	type_color = 'n';
}

Painters::~Painters(){
}

void Painters::menu_house(City *city){
	char op;
	bool exist;
	do{
		cout<<"\n\n =========> "<<name<<"\n\n 1) Info house\n 2) Change color\n 3) Exit\n\n option: ";
		cin>>op;
		switch(op){
			case '1': 	house_info();
						break;
			case '2':
					cout<<"\n\n =========> Color Changing:\n";
					for (int i=0;i<city->limit;i++){
						if (city->positions[i][0]==1){
							cout<<" "<<i+1<<") ";
							switch(city->positions[i][2]){
								case 1: 
										cout<<city->restaurant->name;							
										break;
								case 2: 
										cout<<city->painters->name;						
										break;
								case 3: 
										cout<<city->constructors->name;	
										break;
								case 4: 
										cout<<city->properties->name;							
										break;
								case 5: 
										cout<<city->transactions->name;								
										break;
								case 6: 
										cout<<city->stonks->name;							
										break;
								case 7: 
										cout<<city->hotel->name;								
										break;
								case 8: 
										cout<<city->casino->name;								
										break;								
							}							
						}
					}
					cout<<endl<<endl;
					
					do{
						exist=false;
						cout<<" Select house: ";cin>>type_color;
						for (int i=0;i<city->limit;i++){
							if (city->positions[i][0]==0 && int(type_color)-49==i){
								exist = true;
							}
						}						
					}while(exist || int(type_color)-48<1 || int(type_color)-48>8);
					
					
					switch(city->positions[int(type_color)-49][2]){
						case 1: 
								city->restaurant->change_color();
								break;
						case 2: 
								city->painters->change_color();							
								break;
						case 3:
								city->constructors->change_color();								
								break;
						case 4: 
								city->properties->change_color();															
								break;
						case 5: 
								city->transactions->change_color();															
								break;
						case 6: 
								city->stonks->change_color();															
								break;
						case 7: 
								city->hotel->change_color();															
								break;
						case 8: 
								city->casino->change_color();																
								break;								
					}
	
					getch();
					op = '2';
					break;
		}
	}while(op!='3');
}


// Constructors
Constructors::Constructors(int house_type=0, int pos=5, string name="nothing"):House(house_type, pos, name){
	house_selected = 'n';
	
	getcwd(dir_constructors, 256);
	strcat(dir_constructors, "\\constructors_vista.txt"); 
}

Constructors::~Constructors(){
}

void Constructors::menu_house(City *city){
	char op;
	bool exist;
	do{
		cout<<"\n\n =========> "<<name<<"\n\n 1) Info house\n 2) Level Up House\n 3) Vision of city * . *\n 4) Exit\n\n option: ";
		cin>>op;
		switch(op){
			case '1': 	house_info();
						break;
			case '2':
					cout<<"\n\n =========> Leveling House:\n";
					for (int i=0;i<city->limit;i++){
						if (city->positions[i][0]==1){
							cout<<" "<<i+1<<") ";
							switch(city->positions[i][2]){
								case 1: 
										cout<<city->restaurant->name;							
										break;
								case 2: 
										cout<<city->painters->name;						
										break;
								case 3: 
										cout<<city->constructors->name;	
										break;
								case 4: 
										cout<<city->properties->name;							
										break;
								case 5: 
										cout<<city->transactions->name;								
										break;
								case 6: 
										cout<<city->stonks->name;							
										break;
								case 7: 
										cout<<city->hotel->name;								
										break;
								case 8: 
										cout<<city->casino->name;								
										break;								
							}							
						}
					}
					cout<<endl<<endl;
					
					do{
						exist=false;
						cout<<" Select house: ";cin>>house_selected;
						for (int i=0;i<city->limit;i++){
							if (city->positions[i][0]==0 && int(house_selected)-49==i){
								exist = true;
							}
						}						
					}while(exist || int(house_selected)-48<1 || int(house_selected)-48>8);
					
					
					switch(city->positions[int(house_selected)-49][2]){
						case 1: 
								city->restaurant->add_house();
								break;
						case 2: 
								city->painters->add_house();						
								break;
						case 3:
								city->constructors->add_house();						
								break;
						case 4: 
								city->properties->add_house();															
								break;
						case 5: 
								city->transactions->add_house();													
								break;
						case 6: 
								city->stonks->add_house();															
								break;
						case 7: 
								city->hotel->add_house();														
								break;
						case 8: 
								city->casino->add_house();																
								break;								
					}
	
					getch();
					op = '2';
					break;
			case '3':
						system("cls");
						ifstream datos;
						datos.open(dir_constructors, ios::in);  
						
						if(datos.fail()){
							cout<<" Error. file didnt find of constructors_vista text."<<endl;
							system("pause");
							exit(1);
						}
						else{
							string info;
							while(!datos.eof()){			
								getline(datos, info); 
								cout<<info<<endl;
							}
						}
						datos.close();
						cout<<"\n Presione cualquier tecla para volver a la realidad ...";
						getch();
						break;			
		}
	}while(op!='4');
}


// Stonks
Stonks::Stonks(int house_type=0, int pos=5, string name="nothing"):House(house_type, pos, name){
	games = new MiniGames();
	inver = new Inversion();
}

Stonks::~Stonks(){
	delete games;
	delete inver;
}

void Stonks::menu_house(City *city){
	char op;
	double total;
	do{
		cout<<"\n\n =========> "<<name<<"\n\n 1) Info house\n 2) Inversion\n 3) Hacker mode\n 4) Exit\n\n option: ";
		cin>>op;
		switch(op){
			case '1': 	house_info();
						break;
			case '2': 
						total = inver->activar_inversion();
						if (total<0.0){
							city->pay_money(-1.0*total);
						}
						else{
							city->receive_money(total);
						}
						break;
			case '3': 
						total = games->hacker_mode();
						if (total<0.0){
							city->pay_money(-1.0*total);
						}
						else{
							city->receive_money(total);
						}
						break;					
		}
	}while(op!='4');
}


//Restaurant
Restaurant::Restaurant(int house_type=0, int pos=5, string name="nothing"):House(house_type, pos, name){
	n_hearts = 0;
	limit_food = 31;
	n_food = limit_food;
	total = 0.0;
}

Restaurant::~Restaurant(){
}

void Restaurant::menu_house(City *city){
	char op, op2; 
	do{
		cout<<"\n\n =========> "<<name<<"\n\n 1) Info house\n 2) Buy food\n 3) Exit\n\n option: ";
		cin>>op;
		switch(op){
			case '1': 	house_info();
						break;
			case '2': 
						cout<<" =========>>> Shop Food:\n\n";
						cout<<" 1) Water (1 point)(1.00 $).\n 2) Vegetables (2 points)(8.00 $).\n 3) Meat (3 points)(15.00 $)\n\n";
						
						cout<<endl;
						
						do{
							cout<<" Option: ";cin>>op2;
						}while(int(op2)-48 < 1 || int(op2)-48 > 3);
						
						cout<<endl;
						
						do{
							cout<<" Number of amount(1: 1-30)(2: 1-15)(3: 1-10): ";cin>>n_hearts;
						}while(n_hearts < 1 || n_hearts > 30);
						
						switch(op2){
							case '1': total = n_hearts * 1.0;break;
							case '2': total = n_hearts * 8.0;break;
							case '3': total = n_hearts * 15.0;break;
						}
						
						if (city->money > total ){
							city->pay_money(total);
							
							if(limit_food - n_food - ((int(op2)-48)*n_hearts) - 1 <= 0){
								n_food = limit_food;
							}
							else{
								n_food += (int(op2)-48)*n_hearts + 1;
							}
							cout<<"\n\n  :: Successful Buy ::\n\n";
						}
						else{
							cout<<"\n\n You dont have enough money.\n\n";
						}
						getch();
						break;				
		}
	}while(op!='3');
}

bool Restaurant::get_state_food(){
	return n_food > 0;
}

void Restaurant::load_house(string arr[], int index){
	this->name = arr[index];
	
	n_food = atoi(arr[index + 1].c_str());
	
	for (int i=0;i<6;i++){
		model[i] = atoi(arr[index + 2 + i].c_str());
	}
	
	n = atoi(arr[index+8].c_str());
	
	house[0][0] = atoi(arr[index + 9].c_str());
	house[0][1] = atoi(arr[index + 10].c_str());
	
	for(int i=1; i<n;i++){
		house[i][0] = house[0][0];
		house[i][1] = house[0][1] - i;
	}
	
	color = atoi(arr[index+11].c_str());
	
	money = atof(arr[index+12].c_str());
	price = atof(arr[index+13].c_str());
	pay = atof(arr[index+14].c_str());
	
	for (int i=0;i<4;i++){
		money_month[i] = atof(arr[index+15+i].c_str());
	}
}

string Restaurant::save_house(){
	string all = "";
	
	all += name + ";";
	
	all += to_string(n_food) + ";";
	
	for (int i=0;i<6;i++){
		all += to_string(model[i]) + ";";
	}
	
	all += to_string(n) + ";";
	
	all+= to_string(house[0][0]) + ";" + to_string(house[0][1]) + ";";

	all += to_string(color) + ";";
	
	all += to_string(money) + ";";
	all += to_string(price) + ";";
	all += to_string(pay) + ";";
	
	for (int i=0;i<4;i++){
		all += to_string(money_month[i]) + ";";
	}
	
	return all;
}

int Restaurant::get_food(){
	return this->n_food;
}


//Hotel
Hotel::Hotel(int house_type=0, int pos=5, string name="nothing"):House(house_type, pos, name){
	getcwd(dir_hotel, 256);
	strcat(dir_hotel, "\\hotel_vista.txt"); 
}

Hotel::~Hotel(){
}

void Hotel::menu_house(){
	srand(time(NULL));
	char op;
	int vista;
	ifstream datos;
	string info;
	do{
		cout<<"\n\n =========> "<<name<<"\n\n 1) Info house\n 2) Watch Beach\n 3) Exit\n\n option: ";
		cin>>op;
		switch(op){
			case '1': 	house_info();
						break;
			case '2': 
						system("cls");
						datos.open(dir_hotel, ios::in);  
					
						if(datos.fail()){
							cout<<" Error. file didnt find of hotel_vista text."<<endl;
							system("pause");
							exit(1);
						}
						else{
							vista = rand()%3;
							int i=1;
							while(!datos.eof()){			
								getline(datos, info); 
								switch(vista){
									case 0:
										if(i < 40)
											cout<<info<<endl;
										break;
									case 1:
										if(i == 40) cout<<"\n\n\n\n\n\n";
										if(i > 39 && i < 58)
											cout<<info<<endl;
										if(i == 57) cout<<"\n\n\n\n\n\n";
										break;
									case 2:
										if(i > 57)
											cout<<info<<endl;
										break;
								}
								i++;
							}
						}
						datos.close();
						cout<<"\n Presione cualquier tecla para voltear o girar la cabeza ...";
						getch();
						break;
		}						
	}while(op!='3');
}

void Hotel::collect(){
	double recollected = double(pay * double(n-1));
	money += recollected;
	
	double money_aux;
	for (int i=0;i<4;i++){
		money_aux = money_month[i];
		money_month[i] = recollected;
		recollected = money_aux;
	}	
}

void Hotel::house_info(){
	cout <<"\n\n ============>>> "<<name<<endl<<endl;
	cout <<"\t:: House ::"<<endl;
	cout <<" Current Money: "<<money<<" $"<<endl;
	cout <<" Money per month: "<<pay<<" $"<<endl;
	cout<<" Price House: "<<price<<" $"<<endl<<endl;
	
	cout <<"\t:: Payments ::"<<endl;
	cout<< " Tax(impuesto): "<<tax*100.0<<"% of month"<<endl;
	cout<<" Employees: "<<employees<<" $"<<endl;
	cout<< " light and water: 10 $ - 30 $"<<endl<<endl;
	getch();
}