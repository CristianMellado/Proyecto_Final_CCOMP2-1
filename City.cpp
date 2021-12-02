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
	limit = 8;
	size_house=18; // number of variables of house
	money=0.0;
	game = true;
	
	
	this->world = world;
	
	restaurant = new Restaurant(0,5,name);
	if(name!="nada") name = "nada";
	
	casino = new Casino(0,5,name);
	transactions = new Transactions(0,5,name);
	properties = new Properties(0,5,name);
	painters = new Painters(0,5,name);
	constructors = new Constructors(0,5,name);
	stonks = new Stonks(0,5,name);
	hotel = new Hotel(0,5,name);
	
	// separamos memoria para matriz positions:
	positions = new int *[limit];
	for (int i=0;i<limit;i++){
		positions[i] = new int[3];  // (ocupado, posicion en la ciudad, tipo de casa).
	}
	
	/*
	types of house for positions[i][2].
	1: Restaurant
	2: Painters
	3: Constructors
	4: Properties
	5: Transactions
	6: Stonks
	7: Hotel
	8: Casino
	*/
	
	int n=5;
	for (int i=0;i<limit;i++){
		positions[i][0] = 0;
		positions[i][1] = n;
		positions[i][2] = 0;  // 0: none house
		n+=5;
	}
	positions[0][0] = 1;
	positions[0][2] = 1;
}

City::~City(){
	for (int i=0;i<limit;i++){
		delete[] positions[i];  // liberamos la memoria para cada elemento del puntero de enteros.
	}
	delete[] positions;
	
	delete casino;
	delete restaurant;
	delete transactions;
	delete properties;
	delete painters;
	delete constructors;
	delete stonks;
	delete hotel;
}

void City::load_city(string arr[]){
	world = arr[0];
	
	int index = 1;
	
	for (int i=0;i<limit;i++){
		positions[i][0] = atoi(arr[index].c_str());
		index++;
	}
	for (int i=0;i<limit;i++){
		positions[i][2] = atoi(arr[index].c_str());
		index++;
	}
	
	restaurant->load_house(arr, index);
	index += size_house + 1;
	
	painters->load_house(arr, index);
	index += size_house;
	
	constructors->load_house(arr, index);
	index += size_house;
	
	properties->load_house(arr, index);
	index += size_house;
	
	transactions->load_house(arr, index);
	index += size_house;
	
	stonks->load_house(arr, index);
	index += size_house;
	
	hotel->load_house(arr, index);
	index += size_house;
	
	casino->load_house(arr, index);
	index += size_house;
	
	calendar.load_calendar(arr, index);
}

string City::save_city(){
	string all = "";
	
	all += world + ";";
	
	for (int i=0; i<limit; i++){
		all += to_string(positions[i][0]) + ";";
	}	
	
	for (int i=0; i<limit; i++){
		all += to_string(positions[i][2]) + ";";
	}	
	
	all += restaurant->save_house();
	all += painters->save_house();
	all += constructors->save_house();
	all += properties->save_house();
	all += transactions->save_house();
	all += stonks->save_house();
	all += hotel->save_house();
	all += casino->save_house();

	all += calendar.save_calendar();
	
	return all;
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
					switch(positions[k][2]){
						case 1: 
								if(restaurant->request_house(j,i)){
									house = true;
									restaurant->draw_house(i);
								}								
								break;
						case 2: 
								if(painters->request_house(j,i)){
									house = true;
									painters->draw_house(i);
								}								
								break;
						case 3: 
								if(constructors->request_house(j,i)){
									house = true;
									constructors->draw_house(i);
								}								
								break;
						case 4: 
								if(properties->request_house(j,i)){
									house = true;
									properties->draw_house(i);
								}								
								break;
						case 5: 
								if(transactions->request_house(j,i)){
									house = true;
									transactions->draw_house(i);
								}								
								break;
						case 6: 
								if(stonks->request_house(j,i)){
									house = true;
									stonks->draw_house(i);
								}								
								break;
						case 7: 
								if(hotel->request_house(j,i)){
									house = true;
									hotel->draw_house(i);
								}								
								break;
						case 8: 
								if(casino->request_house(j,i)){
									house = true;
									casino->draw_house(i);
								}								
								break;								
					}
				}
				if (house) break;
			}
     
			if (i==39){
				std::cout <<floor<<floor<<floor;
			}
			else if (!house){
				std::cout<<"   ";
			}
		}
		std::cout<<std::endl;
	}


	for (int i=0;i<limit;i++){
		if (positions[i][0]==1){
			cout<<" "<<i+1<<") ";
				switch(positions[i][2]){
					case 1: 
							cout<<restaurant->name;							
							break;
					case 2: 
							cout<<painters->name;						
							break;
					case 3: 
							cout<<constructors->name;	
							break;
					case 4: 
							cout<<properties->name;							
							break;
					case 5: 
							cout<<transactions->name;								
							break;
					case 6: 
							cout<<stonks->name;							
							break;
					case 7: 
							cout<<hotel->name;								
							break;
					case 8: 
							cout<<casino->name;								
							break;								
				}
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
	cout<<"\n\n 1) Tienda 2) Info Houses 5) Save and exit";
	char key=getch();
	double total=0.0;
	cout<<"\n\n";
	
	switch(key){
		case '1':
			if (positions[0][0]==0 || positions[1][0]==0 || positions[2][0]==0 || positions[3][0]==0 ||
				positions[4][0]==0 || positions[5][0]==0 || positions[6][0]==0 || positions[7][0]==0){
				string name_local;
				char pos, h, op;
				bool ex, type_exist;
				
				//begin
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
					cout<<"\t"<<description[i];
				}
				cout<<endl;
				
				for (int i=0;i<4;i++){
					cout<<"\tprice: "<<prices[i][0]<<" $";
				}
				cout<<endl;
				for (int i=0;i<4;i++){
					cout<<"\tmax pay: "<<prices[i][1]<<" $";
				}
				cout<<endl<<endl;
			
				// second row
				for (int i=4;i<8;i++){
					cout<<"\t\t"<<char(models[i][0])<<char(models[i][1])<<char(models[i][2]);
				}
				cout<<endl;
				for (int j=0;j<3;j++){
					for (int i=4;i<8;i++){
						cout<<"\t\t"<<char(models[i][3])<<char(models[i][4])<<char(models[i][5]);
					}
					cout<<endl;
				}
				for (int i=4;i<8;i++){
					cout<<"\t"<<description[i];
				}
				cout<<endl;
				
				for (int i=4;i<8;i++){
					cout<<"\tprice: "<<prices[i][0]<<" $";
				}
				cout<<endl;
				for (int i=4;i<8;i++){
					cout<<"\tmax pay: "<<prices[i][1]<<" $";
				}
				cout<<endl<<endl;
				//end
				
				do{
					type_exist = false;
					do{
						cout<<" Select type house(1-8): ";cin>>h;
					}while(int(h)-48<1 || int(h)-48 > 8);
					
					for(int i=0;i<limit;i++){
						if(positions[i][0]==1 && positions[i][2]==int(h)-48) type_exist = true;
					}
				}while(type_exist);
				
				
				if (money >= prices[int(h)-49][0]){
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
					
					cout<<"\n Do you sure to buy a house of "<<prices[int(h)-49][0]<<" $ ? (yes: y/ no: any key): ";
					cin>>op;
					
					if(op == 'y'){
						double total=0.0;
						switch(h){
							case '1':	
										if(restaurant){
											delete restaurant;
										}
										restaurant = new Restaurant(int(h)-49, positions[int(pos)-49][1], name_local);
										break;
							case '2':	
										if(painters){
											delete painters;
										}
										painters = new Painters(int(h)-49, positions[int(pos)-49][1], name_local);
										break;
							case '3':	
										if(constructors){
											delete constructors;
										}
										constructors = new Constructors(int(h)-49, positions[int(pos)-49][1], name_local);
										break;
							case '4':	
										if(properties){
											delete properties;
										}
										properties = new Properties(int(h)-49, positions[int(pos)-49][1], name_local);
										break;
							case '5':	
										if(transactions){
											delete transactions;
										}
										transactions = new Transactions(int(h)-49, positions[int(pos)-49][1], name_local);
										break;
							case '6':	
										if(stonks){
											delete stonks;
										}
										stonks = new Stonks(int(h)-49, positions[int(pos)-49][1], name_local);
										break;
							case '7':	
										if(hotel){
											delete hotel;
										}
										hotel = new Hotel(int(h)-49, positions[int(pos)-49][1], name_local);
										break;
							case '8':	
										if(casino){
											delete casino;
										}		
										casino = new Casino(int(h)-49, positions[int(pos)-49][1], name_local);
										break;										
						}
						
						pay_money(total);
						positions[int(pos)-49][0] = 1;
						positions[int(pos)-49][2] = int(h)-48;
						cout<<"\n :: Successful Purchase ::\n";
						getch();
					}
				}
				else{
					cout <<"\n You dont have enough money.\n";
					getch();
				}
			}
			break;
		case '2':
					cout <<"\n\n ===============>>> Houses Information:\n\n";
					for(int i=0; i<limit; i++){
						cout<<description[i]<<":"<<endl;
						cout<<"\t"<<char(4)<<description_text[i]<<endl<<endl;
					}
					getch();
					break;
		case '5': game=false; break;
		default : break;
	}
}

void City::city_houses(int selected){
	char op;
	bool exist;
	
	switch(positions[selected][2]){
		case 1: 
				restaurant->menu_house(this);							
				break;
		case 2: 
				painters->menu_house(this);							
				break;
		case 3: 
				constructors->menu_house(this);		
				break;
		case 4: 
				properties->menu_house(this);								
				break;
		case 5: 
				transactions->menu_house(this);									
				break;
		case 6: 
				stonks->menu_house(this);								
				break;
		case 7: 
				hotel->menu_house();									
				break;
		case 8: 
				casino->menu_house(this);									
				break;								
		}
}

void City::collect_money(){
	if(restaurant->get_state_food()){
		for (int i=0;i<limit;i++){
			if (positions[i][0]==1){
				switch(positions[i][2]){
					case 1: 
							restaurant->collect();							
							break;
					case 2: 
							painters->collect();					
							break;
					case 3: 
							constructors->collect();
							break;
					case 4: 
							properties->collect();							
							break;
					case 5: 
							transactions->collect();								
							break;
					case 6: 
							stonks->collect();							
							break;
					case 7: 
							hotel->collect();									
							break;
					case 8: 
							casino->collect();								
							break;								
				}
			}
		}
		restaurant->n_food--;
	}
}

void City::receive_money(double total){
	refresh_account();
	double percentage;
	
	for (int i=0;i<limit;i++){
		if (positions[i][0]==1){
			switch(positions[i][2]){
				case 1: 
						percentage = restaurant->get_money() / this->money;
						restaurant->receive(percentage * total);						
						break;
				case 2: 
						percentage = painters->get_money() / this->money;
						painters->receive(percentage * total);			
						break;
				case 3: 
						percentage = constructors->get_money() / this->money;
						constructors->receive(percentage * total);
						break;
				case 4: 
						percentage = properties->get_money() / this->money;
						properties->receive(percentage * total);				
						break;
				case 5: 
						percentage = transactions->get_money() / this->money;
						transactions->receive(percentage * total);											
						break;
				case 6: 
						percentage = stonks->get_money() / this->money;
						stonks->receive(percentage * total);										
						break;
				case 7: 
						percentage = hotel->get_money() / this->money;
						hotel->receive(percentage * total);												
						break;
				case 8: 
						percentage = casino->get_money() / this->money;
						casino->receive(percentage * total);							
						break;								
			}
		}
	}
}

void City::pay_money(double total){
	refresh_account();
	double percentage;
	
	for (int i=0;i<limit;i++){
		if (positions[i][0]==1){
			switch(positions[i][2]){
				case 1: 
						percentage = restaurant->get_money() / this->money;
						restaurant->pay_amount(percentage * total);						
						break;
				case 2: 
						percentage = painters->get_money() / this->money;
						painters->pay_amount(percentage * total);			
						break;
				case 3: 
						percentage = constructors->get_money() / this->money;
						constructors->pay_amount(percentage * total);
						break;
				case 4: 
						percentage = properties->get_money() / this->money;
						properties->pay_amount(percentage * total);				
						break;
				case 5: 
						percentage = transactions->get_money() / this->money;
						transactions->pay_amount(percentage * total);											
						break;
				case 6: 
						percentage = stonks->get_money() / this->money;
						stonks->pay_amount(percentage * total);										
						break;
				case 7: 
						percentage = hotel->get_money() / this->money;
						hotel->pay_amount(percentage * total);												
						break;
				case 8: 
						percentage = casino->get_money() / this->money;
						casino->pay_amount(percentage * total);							
						break;								
			}
		}
	}
}

void City::refresh_account(){
	this->money = 0.0;
	for (int i=0;i<limit;i++){
		if (positions[i][0]==1){
			switch(positions[i][2]){
				case 1: 
						money += restaurant->get_money();					
						break;
				case 2: 
						money += painters->get_money();
						break;
				case 3: 
						money += constructors->get_money();
						break;
				case 4: 
						money += properties->get_money();			
						break;
				case 5: 
						money += transactions->get_money();									
						break;
				case 6: 
						money += stonks->get_money();									
						break;
				case 7: 
						money += hotel->get_money();										
						break;
				case 8: 
						money += casino->get_money();					
						break;								
			}
		}
	}
}


void City::pay_money_month(){
	for (int i=0;i<limit;i++){
		if (positions[i][0]==1){
			switch(positions[i][2]){
				case 1: 
						restaurant->payments();							
						break;
				case 2: 
						painters->payments();					
						break;
				case 3: 
						constructors->payments();
						break;
				case 4: 
						properties->payments();							
						break;
				case 5: 
						transactions->payments();								
						break;
				case 6: 
						stonks->payments();							
						break;
				case 7: 
						hotel->payments();									
						break;
				case 8: 
						casino->payments();								
						break;								
			}			
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
		action = calendar.draw_calendar(money, restaurant->get_food());

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