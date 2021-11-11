/****************************************************************
Proyecto final

Departamento de Ciencia de la Computación
Prof: D.Sc. Manuel Eduardo Loaiza Fernández

Alumnos:
 - Cristian Mellado Baca
 - Marcelo Torres Acuña
 - Alexander Carpio Mamani
*****************************************************************/


#include "mylib.h"
using namespace std;

int models[4][6] = {{61,61,61,124,254,124},{94,94,94,91,4,93},
					{203,205,203,186,186,186},{242,242,242,197,197,197}};
double prices[4][2] = {{10000.0f,100.0}, {18000.0, 180.0}, {25000.0, 250.0},{40000.0, 400.0}};

House::House(int h, int x, string name){
	for (int i=0;i<6;i++){
		model[i] = char(models[h][i]);
	}
	house[0][0] = x;
	house[0][1] = 38;
	house[1][0] = x;
	house[1][1] = 37;	
	
	this->name = name;
	color = BLOCK_BLACK;
	
	money = 100.0;
	price = prices[h][0];
	pay = prices[h][1];
	
	for (int i=0;i<4;i++){
		money_month[i] = 0.0;
	}
	
	tax = 0.2;
	employees = 20.0;
	light_and_water = 0.0;
}

bool House::request_house(int x, int y){
	for (int i=0; i<n; i++){
		if(house[i][0]==x && house[i][1]==y) return true;
	}
	return false;
}

void House::add_house(){
	double sell_house_price = 0.25, total;
	if (n<limit){
		if (money > price*sell_house_price){
			int pisos;char op;
			do{
				cout <<"\n How many floors you want to buy ? ";cin>>pisos;
				total = double(pisos)*(price*sell_house_price);
			}while(pisos<0 || pisos > 30-n || total>money);
			
			do{
				cout<<" Do you sure of buy "<<pisos<<" floors by "<<total<<" $ ? (y/n): ";
				cin>>op;
			}while(op!='y' && op!='n');
			
			if (op=='y'){
				for(int i=0; i<pisos;i++){
					house[n][0] = house[0][0];
					house[n][1] = house[0][1]-n;
					n++;
				}
				money -= total;
				cout<<"\n :: Successful Purchase ::\n";
			}
		}
		else{
			cout <<"\n You dont have enough money.\n";
		}
	}
	else{
		cout <<"\n You reach the top of you house.\n";
	}
}
void House::draw_house(int row){
	cout<<color;
	if (color == BLOCK_WHITE || color == BLOCK_LIGHT_WHITE || color==BLOCK_LIGHT_CYAN || 
		color==BLOCK_LIGHT_YELLOW || color == BLOCK_LIGHT_RED || color == BLOCK_YELLOW) 
		cout<<BLACK;
	
	if (row==house[n-1][1]){
		
		cout<<model[0]<<model[1]<<model[2];
	}
	else{
		cout<<model[3]<<model[4]<<model[5];
	}
	cout<<RESET;
}

void House::rename_house(){
	fflush(stdin);
	cout<<"\n Enter new name: ";getline(cin,name);
	fflush(stdin);
	cout<<"\n :: Successful Rename ::\n";
}

void House::change_color(){
	int op;char confirm;
	double total = 100.0 * double(n);
	
	if (total<money){
		cout <<"\n :: Colors :: Colors :: Colors ::\n";
		cout<<" 1) Black \t\t 9) Light Black\n";
		cout<<" 2) Red Color \t\t 10) Light Red\n";
		cout<<" 3) Green \t\t 11) Light Green\n";
		cout<<" 4) Yellow \t\t 12) Light Yellow\n";
		cout<<" 5) Blue \t\t 13) Light Blue\n";
		cout<<" 6) Magenta \t\t 14) Light Magenta\n";
		cout<<" 7) Cyan \t\t 15) Light Cyan\n";
		cout<<" 8) White \t\t 16) Light White\n\n";
		do{
			cout <<" option: ";cin>>op;
		}while(op<1 || op >16);
		
		switch(op){
			case 1:color = BLOCK_BLACK;break;
			case 2:color = BLOCK_RED;break;
			case 3:color = BLOCK_GREEN;break;
			case 4:color = BLOCK_YELLOW;break;
			case 5:color = BLOCK_BLUE;break;
			case 6:color = BLOCK_MAGENTA;break;
			case 7:color = BLOCK_CYAN;break;
			case 8:color = BLOCK_WHITE;break;
			case 9:color = BLOCK_LIGHT_BLACK;break;
			case 10:color = BLOCK_LIGHT_RED;break;
			case 11:color = BLOCK_LIGHT_GREEN;break;
			case 12:color = BLOCK_LIGHT_YELLOW;break;
			case 13:color = BLOCK_LIGHT_BLUE;break;
			case 14:color = BLOCK_LIGHT_MAGENTA;break;
			case 15:color = BLOCK_LIGHT_CYAN;break;
			case 16:color = BLOCK_LIGHT_WHITE;break;
		}
		
		do{
			cout<<" Do you sure of change color by "<<total<<" $ ? (y/n): ";
			cin>>confirm;
		}while(confirm!='y' && confirm!='n');
			
		if (confirm=='y'){
			money -= total;
			cout<<"\n :: Successful Color ::\n";
		}
	}
	else{
		cout <<"\n You dont have enough money.\n";
	}
}


void House::house_info(){
	cout <<"\n ============>>> "<<name<<endl<<endl;
	cout <<"\t:: House ::"<<endl;
	cout <<" Money: "<<money<<" $"<<endl;
	cout <<" Money per month: "<<1.0<<" $ - "<<pay<<" $"<<endl;
	cout<<" Price House: "<<price<<" $"<<endl<<endl;
	
	cout <<"\t:: Payments ::"<<endl;
	cout<< " Tax(impuesto): "<<tax<<"% of month"<<endl;
	cout<<" Employees: "<<employees<<" $"<<endl;
	cout<< "light and water: 10 $ - 30 $"<<endl<<endl;
}

void House::collect(){
	srand (time(NULL));
	double recollected = double(rand()%int(pay * double(n-1)) + 1);
	recollected += double(rand()%10)/10.0;
	
	money += recollected;
	
	double money_aux;
	for (int i=0;i<4;i++){
		money_aux = money_month[i];
		money_month[i] = recollected;
		recollected = money_aux;
	}
	
}

void House::pay_amount(double amount){
	money -= amount;
}

void House::payments(){
	double month=0.0;
	bool full_month = true;
	for (int i=0;i<4;i++){
		month += money_month[i];
		if (money_month[i] == 0.0) full_month = false;
	}
	if (full_month){
		money -= month*tax;
		money -= (n-1)*employees;
		
		srand (time(NULL));
		light_and_water = double(10 + rand()%31);
		money -= light_and_water;
	}
}

City::City(string world="nada", string name="nada", int index=0){
	this->world = world;
	index_memory = index;
	houses[0] = new House(0,5,name);
	
	for(int i=1; i<limit;i++){
		houses[i] = nullptr;
	}
	
	int n=5;
	for (int i=0;i<limit;i++){
		positions[i][0] = 0;
		positions[i][1] = n;
		n+=5;
	}
	positions[0][0] = 1;
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
					if (houses[k]->request_house(j,i)){
						house = true;
						n = k;
					}
				}
			} 
     
			if (house){
				houses[n]->draw_house(i);
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
			cout<<" "<<i+1<<") "<<houses[i]->name;
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
				int pos, h;
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
					cout<<" Select type house: ";cin>>h;
				}while(h<1 || h >4);
				
				if (money>= prices[h-1][0]){
					fflush(stdin);
					cout<<"\n Enter local name: ";getline(cin,name_local);
					fflush(stdin);
					
					do{
						ex = false;
						cout<<" Enter local position: ";cin>>pos;
						for (int i=0;i<8;i++){
							if (pos==i+1 && positions[i][0]==1) ex = true;
						}
					}while(ex || pos < 1 || pos > 8);
					
					houses[pos-1] = new House(h-1,positions[pos-1][1], name_local);
					
					pay_money(houses[pos-1]->price);
					
					positions[pos-1][0] = 1;
					
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
		cout<<"\n\n ===> "<<houses[selected]->name<<endl;
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
			case '1': 	houses[selected]->house_info();
						getch();break;

			case '2': 
						houses[selected]->add_house();
						getch();
						break;
			case '3':
					cout<<"\n You price house: "<<houses[selected]->price<<" $"<<endl;
					
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
						receive_money(houses[selected]->price);
						houses[selected] = nullptr;
						op = '7';
						cout<<"\n :: Successful Sale ::\n";
					}
					getch();break;
			case '4':
					cout<<"\n You money: "<<houses[selected]->money<<" $"<<endl;
					for (int i=0;i<limit;i++){
						if (positions[i][0]==1 && selected!=i){
							cout<<" "<<i+1<<") "<<houses[i]->name;
						}
					}
					cout<<endl;
					
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
						cout<<" Enter money deposit to ("<<houses[int(op)-49]->name<<"):";cin>>dinero;
					}while(dinero<0.0 || houses[selected]->money<dinero);
					
					houses[selected]->pay_amount(dinero);
					houses[int(op)-49]->money += dinero;
					
					cout<<"\n :: Transferene Successful ::\n";
					getch();
					break;
			  
			case '5':
					houses[selected]->rename_house();
					getch();
					break;
					
			case '6': 
						houses[selected]->change_color();getch();break;
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
			houses[i]->collect();
		}
	}
}

void City::receive_money(double total){
	refresh_account();
	double percentage;
	for (int i=0;i<limit;i++){
		if (positions[i][0]==1){
			percentage = houses[i]->money / money;
			houses[i]->money += total * percentage;
		}
	}
}

void City::pay_money(double p){
	refresh_account();
	double percentage;
	for (int i=0;i<limit;i++){
		if (positions[i][0]==1){
			percentage = houses[i]->money / money;
			houses[i]->pay_amount(p * percentage);
		}
	}
}

void City::refresh_account(){
	money = 0.0;
	for (int i=0;i<limit;i++){
		if (positions[i][0]==1){
			money += houses[i]->money;
		}
	}
}


void City::pay_money_month(){
	for (int i=0;i<limit;i++){
		if (positions[i][0]==1){
			houses[i]->payments();
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


double MiniGames::menu_minigames(){
	char op;
	total  = 0.0;

	do{
		cout << "\n\n ===> Casino"<<endl;
		cout <<" 1) TicTacToe"<<endl;
		cout <<" 2) Snake"<<endl;
		cout <<" 3) Rulette"<<endl;
		cout <<" 4) Exit"<<endl;
		cout<<" opcion: ";cin>>op;
		
		switch(op){
			case '1': 	
						total -= entry;
						total += TicTacToe();
						getch();
						break;
			case '2': 
						total -= entry;
						total += Snake();
						getch();
						break;
						
			case '3': 	total -= entry;
						total += Rulette();
						getch();
						break;
						
			case '4': break;
			default: cout<<"\n No existe esa opcion.";break;
		}
	}while(op!='4');
	
	return total;
}

double MiniGames::Rulette(){
	char op, mark = char(254), win, selected='n';
	srand(time(NULL));
	int num = rand()%20, t, b, l, r, pos[2]={0,0}, cl, number;
	bool c_t = true, c_b = true, c_l=true, c_r=true, ball=true, con;
	
	cout<<"\n  ======= Ruleta =====>>> :b"<<endl<<endl;
	cout<<num<<endl;
	do{
		cout <<" 1) color(green: x3, red and black: x1)\n 2) number(x7)\n option: ";cin>>op;
	}while(op!='1' && op!='2');
	cout<<endl;
	if(op=='2'){
		do{
			cout<<" Enter your number(0-19): ";cin>>number;
		}while(number<0 || number>19);
	}
	else{
		do{
			cout<<" 1) Red"<<endl;
			cout<<" 2) Black"<<endl;
			cout<<" 3) Green"<<endl;
			cin>>op;
			switch(op){
				case '1': selected='r'; break;
				case '2': selected='b'; break;
				case '3': selected='g'; break;
				default : cout<<"\n Option incorrect.\n";break;
			}
		}while(op!='3' && op!='2' && op!='1');
	}
	
	
	for(int a =0; a<21+num;a++){
		system("cls");
		system(" ");
		cout<<"\n  ======= Ruleta =====>>> :b"<<endl<<endl;
		t=0; b=15; l=19; r=6;
		ball=true; c_t = true; c_b = true; c_l=true; c_r=false;
		for (int i=0;i<6;i++){
			for (int j=0;j<6;j++){
				if (i==0 || j == 0 || i == 5 || j == 5){
					con = true;
					if (pos[0]==j && pos[1]==i && ball){
						if (i==0 && j<5) pos[0]++;
						else if (j==5 && i<5) pos[1]++;
						else if (i==5 && j>0) pos[0]--;
						else if (j==0 && i>0) pos[1]--;
						cout<<"\033[43m\t O \033[m";
						ball = false;
						con = false;
					}
					if (i==0){
						if (i==0 && j==0){
							if (num==0) win='g';
							if (con) cout<<"\033[42m\t "<<t<<" \033[m";
						}
						else{
							if (c_t){
								if (num==t) win='r';
								if (con) cout<<"\033[41m\t "<<t<<" \033[m";
								c_t = false;
							}
							else {
								if (num==t) win='b';
								if (con) cout<<"\033[100m\t "<<t<<" \033[m";
								c_t = true;
							}						
						}
						t++;
					}
					else if (i==5){
						if (c_b){
							if (num==b) win='r';
							if (con) cout<<"\033[41m\t "<<b<<" \033[m";
							c_b = false;
						}
						else {
							if (num==b) win='b';
							if (con) cout<<"\033[100m\t "<<b<<" \033[m";
							c_b = true;
						}
						b--;
					}
					else if (j==0){
						if (c_l){
							if (num==l) win='r';
							if (con) cout<<"\033[41m\t "<<l<<" \033[m";
							c_l = false;
						}
						else {
							if (num==l) win='b';
							if (con) cout<<"\033[100m\t "<<l<<" \033[m";
							c_l = true;
						}
						l--;
					}
					else if (j==5){
						if (c_r){
							if (num==r) win='r';
							if (con) cout<<"\033[41m\t "<<r<<" \033[m";
							c_r = false;
						}
						else {
							if (num==r) win='b';
							if (con) cout<<"\033[100m\t "<<r<<" \033[m";
							c_r = true;
						}
						r++;
					}
				}
				else{
					cout <<"\t";
				}
			}
			cout<<endl<<endl;	
		}
		//Beep(329,100);
		cl = clock() + 100;
		while (cl > clock()){
			continue;
		}
	}
	cout << " Number win: "<<num<<endl;
	cout << " Color win: ";
	if (win=='g') cout<<"Green";
	else if (win=='r') cout<<"Red";
	else cout<<"Black";
	cout<<endl<<endl;
	
	double pay = 0.0;
	if (num==number){
		pay = rulette_money*5;
		cout <<" YOU WIN "<<pay<<" $ !!!"<<endl;
	}
	else if (selected == 'g'){
		pay = rulette_money*3;
		cout <<" YOU WIN "<<pay<<" $ !!!"<<endl;
	}
	else if (selected == win){
		pay = rulette_money;
		cout <<" YOU WIN "<<pay<<" $ !!!"<<endl;
	}

	return pay;
}

double MiniGames::TicTacToe(){
	int width = 5, op;
	char mark = 254, side= '#', turn, x='X', o='O';
	bool x1=0,x2=0,x3=0,x4=0,x5=0,x6=0,x7=0,x8=0,x9=0,
	c1=0,c2=0,c3=0,c4=0,c5=0,c6=0,c7=0,c8=0,c9=0, validate=false;
	turn = x;
	
	while (1){
		system("cls");
		std::cout << "\n\n==================================================\n";
		std::cout << "================== Tres en raya ==================\n";
		std::cout << "==================================================\n\n";
		
		for (int i=1; i < 18; i++){
			for(int j=1; j < 18; j++){
				if (i%6==0){
					std::cout <<" "<< side <<" ";	
				}
				else if (j%6==0 && j!=0)
			std::cout << WHITE<<side<<RESET;
				
				else if (i==j && i < 6 && j < 6 && x1){
					std::cout <<" "<< RED<<mark<<RESET <<" ";
				}
				else if (i+j==6 && i < 6 && j < 6 && x1){
					std::cout <<" "<< RED<<mark<<RESET <<" ";
				}
				else if (i+6==j && i < 6 && j < 12 && x2){
					std::cout <<" "<< RED<<mark<<RESET <<" ";
				}
				else if (i+j==12 && i < 6 && j < 12 && x2){
					std::cout <<" "<< RED<<mark<<RESET <<" ";
				}
				else if (i+12==j && i < 6 && j < 18 && x3){
					std::cout <<" "<< RED<<mark<<RESET <<" ";
				}
				else if (i+j==18 && i < 6 && j < 18 && x3){
					std::cout <<" "<< RED<<mark<<RESET <<" ";
				}
				else if (i-6==j && i < 12  && i > 6 && j < 6 && x4){
					std::cout <<" "<< RED<<mark<<RESET <<" ";
				}
				else if (i+j==12 && i < 12 && i > 6 && j < 6 && x4){
					std::cout <<" "<< RED<<mark<<RESET <<" ";
				}
				else if (i==j && i < 12 && i>6 && j < 12 && x5){
					std::cout <<" "<< RED<<mark<<RESET <<" ";
				}
				else if (i+j==18 && i < 12 && i > 6 && j < 12 && x5){
					std::cout <<" "<< RED<<mark<<RESET <<" ";
				}
				else if (i+6==j && i < 12 && i > 6 && j < 18 && x6){
					std::cout <<" "<< RED<<mark<<RESET <<" ";
				}
				else if (i+j==24 && i < 12 && i > 6 && j < 18 && x6){
					std::cout <<" "<< RED<<mark<<RESET <<" ";
				}
				else if (i-12==j && i < 18 && i > 12 && j < 6 && x7){
					std::cout <<" "<< RED<<mark<<RESET <<" ";
				}
				else if (i+j==18 && i < 18 && i > 12 && j < 6 && x7){
					std::cout <<" "<< RED<<mark<<RESET <<" ";
				}
				else if (i-6==j && i < 18 && i > 12 && j < 12 && x8){
					std::cout <<" "<< RED<<mark<<RESET <<" ";
				}
				else if (i+j==24 && i < 18 && j < 12 && x8){
					std::cout <<" "<< RED<<mark<<RESET <<" ";
				}
				else if (i==j && i < 18 && i>12 && j < 18 && x9){
					std::cout <<" "<< RED<<mark<<RESET <<" ";
				}
				else if (i+j==30 && i < 18 && i > 12 && j < 18 && x9){
					std::cout <<" "<< RED<<mark<<RESET <<" ";
				}
				else if ((i==1 || j==1 || i==5 || j==5) && i < 6 && j < 6 && c1){
					std::cout <<" "<< GREEN<<mark<<RESET <<" ";
				}
				else if ((i==1 || j==7 || i==5 || j==11) && i < 6 && j < 12 && j > 6 && c2){
					std::cout <<" "<< GREEN<<mark<<RESET <<" ";
				}
				else if ((i==1 || j==13 || i==5 || j==17) && i < 6 && j < 18 && j > 12 && c3){
					std::cout <<" "<< GREEN<<mark<<RESET <<" ";
				}
				else if ((i==7 || j==1 || i==11 || j==5) && i < 12 && i >6 && j < 6 && c4){
					std::cout <<" "<< GREEN<<mark<<RESET <<" ";
				}
				else if ((i==7 || j==7 || i==11 || j==11) && i < 12 && i >6 && j < 12 && j > 6 && c5){
					std::cout <<" "<< GREEN<<mark<<RESET <<" ";
				}
				else if ((i==7 || j==13 || i==11 || j==17) && i < 12 && i >6 && j > 12 && c6){
					std::cout <<" "<< GREEN<<mark<<RESET <<" ";
				}
				else if ((i==13 || j==1 || i==17 || j==5) && i > 12 && j < 6 && c7){
					std::cout <<" "<< GREEN<<mark<<RESET <<" ";
				}
				else if ((i==13 || j==7 || i==17 || j==11) && i > 12 && j < 12 && j > 6 && c8){
					std::cout <<" "<< GREEN<<mark<<RESET <<" ";
				}
				else if ((i==13 || j==13 || i==17 || j==17) && i > 12 && j > 12 && c9){
					std::cout <<" "<< GREEN<<mark<<RESET <<" ";
				}
				else
					std::cout << "   ";
			}
			std::cout<<std::endl;
		}
		
		std::cout<<std::endl;
		std::cout<<std::endl;
		
		if ((x1 && x2 && x3) || (x4 && x5 && x6) || (x7 && x8 && x9) || (x1 && x4 && x7) || (x2 && x5 && x8) || 
		(x3 && x6 && x9) || (x1 && x5 && x9) || (x7 && x5 && x3)){
			std::cout << "==================================================\n";
			std::cout << "==================================================\n";
			std::cout << "==================== YOU WIN =====================\n";
			std::cout << "==================================================\n";
			std::cout << "==================================================\n\n";
			return tictac_money;
		}
		if ((c1 && c2 && c3) || (c4 && c5 && c6) || (c7 && c8 && c9) || (c1 && c4 && c7) || (c2 && c5 && c8) || 
		(c3 && c6 && c9) || (c1 && c5 && c9) || (c7 && c5 && c3)){
			std::cout << "==================================================\n";
			std::cout << "==================================================\n";
			std::cout << "==================== BOT WIN =====================\n";
			std::cout << "==================================================\n";
			std::cout << "==================================================\n\n";
			return 0.0;
		}
		
		if ((x1 || c1) && (x2 || c2) && (x3 || c3) && (x4 || c4) && (x5 || c5) && (x6 || c6) &&
		(x7 || c7) && (x8 || c8) && (x9 || c9)){
			std::cout << "==================================================\n";
			std::cout << "==================================================\n";
			std::cout << "===================== EMPATE =====================\n";
			std::cout << "==================================================\n";
			std::cout << "==================================================\n\n";
			return 0.0;
		}
		
		if (turn == x){
			std::cout<<" you turn (";
			if (!x1 && !c1) std::cout<<1<<",";
			if (!x2 && !c2) std::cout<<2<<",";
			if (!x3 && !c3) std::cout<<3<<",";
			if (!x4 && !c4) std::cout<<4<<",";
			if (!x5 && !c5) std::cout<<5<<",";
			if (!x6 && !c6) std::cout<<6<<",";
			if (!x7 && !c7) std::cout<<7<<",";
			if (!x8 && !c8) std::cout<<8<<",";
			if (!x9 && !c9) std::cout<<9;
			std::cout<<") :";
			std::cin>>op;
		}
		else{
			srand(time(NULL));
			op = 1 + rand()%9;
		}
		
		
		do{
			validate = false;
			if (op == 1 && !x1 && !c1){
				if (turn==x) x1=1;
				else c1=1;
			}
			else if (op == 2 && !x2 && !c2){
				if (turn==x) x2=1;
				else c2=1;
			}
			else if (op == 3 && !x3 && !c3){
				if (turn==x) x3=1;
				else c3=1;
			}
			else if (op == 4 && !x4 && !c4){
				if (turn==x) x4=1;
				else c4=1;
			}
			else if (op == 5 && !x5 && !c5){
				if (turn==x) x5=1;
				else c5=1;
			}
			else if (op == 6 && !x6 && !c6){
				if (turn==x) x6=1;
				else c6=1;
			}
			else if (op == 7 && !x7 && !c7){
				if (turn==x) x7=1;
				else c7=1;
			}
			else if (op == 8 && !x8 && !c8){
				if (turn==x) x8=1;
				else c8=1;
			}
			else if (op == 9 && !x9 && !c9){
				if (turn==x) x9=1;
				else c9=1;
			}
			else{
				if (turn==x){
					std::cout<<"\n Error, pls try again.\n\n";
					std::cout<<"\a";
					std::cout<<"turn \" "<<turn<<" \" (";
					if (!x1 && !c1) std::cout<<1<<",";
					if (!x2 && !c2) std::cout<<2<<",";
					if (!x3 && !c3) std::cout<<3<<",";
					if (!x4 && !c4) std::cout<<4<<",";
					if (!x5 && !c5) std::cout<<5<<",";
					if (!x6 && !c6) std::cout<<6<<",";
					if (!x7 && !c7) std::cout<<7<<",";
					if (!x8 && !c8) std::cout<<8<<",";
					if (!x9 && !c9) std::cout<<9;
					std::cout<<") :";
					std::cin>>op;
				}
				else{
					srand(time(NULL));
					op = 1 + rand()%9;
				}
				validate = true;
			}
		}while(validate);
		
		if (turn == x) turn = o;
		else turn = x;
		
		std::cout<<std::endl;

	}
}


double MiniGames::Snake(){
	double eat_money = 0.0;
	
	int x=10, y=10, score, snake[50][2], apple[2]={-1,-1};
	char state='w', head_snake= char(254), apple_img=char(254), vertical_side=char(186), horizontal_side='=';
	bool tail, apple_show, collide;
	
	
	score = 0;
	snake[0][0] = 10;
	snake[0][1] = 10;
	
	apple_show = false;
	
	while(1){
		system("cls");
		system(" ");
		std::cout<<"\n==================================================================\n";
		std::cout<<" Money: "<<eat_money<< " $"<<std::endl;
		
		for (int i=0; i<22; i++){
			for (int j=0; j<22; j++){
				tail = false;
				for (int k=0; k<score+1; k++){
					if (snake[k][0]==j && snake[k][1]==i) tail = true;
				}
				
				
				if (tail){
					//std::cout << GREEN<<head_snake<<head_snake<<head_snake<<RESET;
					cout<<BLOCK_GREEN<<"   "<<RESET;
				}
				else if (apple[0] == j && apple[1]==i && apple_show){
					//std::cout << RED<<apple_img<<apple_img<<apple_img<<RESET;
					cout<<BLOCK_RED<<"   "<<RESET;
				}
				else if (i==0 || i == 21 || j==0 || j==21){
					//std::cout <<YELLOW<<horizontal_side<<horizontal_side<<horizontal_side<<RESET;
					cout<<BLOCK_CYAN<<"   "<<RESET;
				}
				// else if (j==0 || j == 21) {
					// std::cout <<YELLOW<<vertical_side<<vertical_side<<vertical_side<<RESET;
				// }
				else{
					//std::cout << "   ";
					cout<<BLOCK_YELLOW<<"   "<<RESET;
				}
			}
			std::cout<<std::endl;
		}
		
		
		x = snake[0][0];
		y = snake[0][1];
		collide = false;
		for (int i=1; i<score+1;i++){
			if (x == snake[i][0] && y == snake[i][1]) collide = true;
		}
		
		if (x == 0 || x == 21 || y == 0 || y == 21 || collide){
			std::cout<<"\n============================ YOU LOSE ============================";
			std::cout<<"\n MONEY: "<< eat_money <<" $ ";
			break;
		}

		if (kbhit()){
			char key = getch();
			if (key == 'a' || key == 'd' || key == 'w' || key == 's')
				state = key;
		}

		switch(state){
			case 'a': x--;break;
			case 'd': x++;break;
			case 'w': y--;break;
			case 's': y++;break;
		}
			
		int ago_x=snake[0][0], ago_y=snake[0][1], copy_x, copy_y;
		for (int i=0; i<score+1; i++){
			copy_x = snake[i][0];
			copy_y = snake[i][1];
			snake[i][0] = ago_x;
			snake[i][1] = ago_y;
			ago_x = copy_x;
			ago_y = copy_y;
		}
		snake[0][0] = x; snake[0][1] = y;

		if (apple_show){
			if (snake[0][0]==apple[0] && snake[0][1]==apple[1]){
				apple_show = false;
				score++;
				eat_money += snake_money;
			}
		}
		else{
			apple_show = true;
			srand(time(NULL));
			apple[0] = 1 + rand()%(20); 
			apple[1] = 1 + rand()%(20); 
		}
	}
	
	return eat_money;
}

double MiniGames::hacker_mode(){
	srand(time(NULL));
	int hacking = rand()%2, cl;
	double amount=0.0;
	
	system("color 0A");
	cout<<"\n\t ::::::::::::::: HACKER MODE ::::::::::::::: HACKER MODE ::::::::::::::: HACKER MODE :::::::::::::::\n\n";

	ifstream datos; 
	string info;
	
	datos.open("hacker_text.txt", ios::in);  
		
	if(datos.fail()){
		cout<<" Error. file didnt find of hacker text."<<endl;
		system("pause");
		exit(1);
	}
	else{
		while(!datos.eof()){			
			getline(datos, info);          
			cout<<info<<endl;
			cl = clock() + 100;
			while (cl > clock()){
				continue;
			}		
		}
		datos.close();
	}

	do{
		cout<<"\n\n\t ENTER AMOUNT TO HACKING: ";cin>>amount;
	}while(amount<0);
	
	if (hacking==1){
		cout <<"\n YOU HACKED THE MONEY !!! "<<amount<<" $ SUCCESSFUL !!!"<<endl;
	}
	else{
		amount = -1.0*(amount*0.5);
		cout <<"\n YOU DONT HACKED THE MONEY !!! "<<amount<<" $ :( !!!"<<endl;
		for (int i=0;i<3;i++){
			system("start cmd");
		}
	}
	return amount;
}

string Inversion::gen_bar(int n, int t){
	string bar = "";
	//if (n<)
	n /= (t/100);
	for (int i=0;i<n;i++){
		bar += " ";
	}
	return bar;
}

double Inversion::activar_inversion(){
	char op, ask;
	int select, cl, timer=3000;
	bool next;
	srand(time(NULL));
	monto = double(1 + rand() % 5) * -1000.0;
	capital = 0.0;
	
	do{
		cout<<"\n ¿Deseas invertir "<<-1*monto <<" $ ? (y/n): ";cin>>op;
	}while(op!='y' && op!='n');
	
	if(op=='y'){
		for(int i=0;i<5;i++){
			system("cls");
			select = rand()%n_ask;
			next = true;
			
			cl = clock() + timer;
			while (cl > clock() && next){
				system("cls");
				cout<<"\n =======> :: INVERSIONES :: =======> \n";
				cout<<endl<<preguntas[select]<<endl<<endl;
				cout<<BLOCK_GREEN<<gen_bar(cl-clock(), timer)<<RESET;

				if(kbhit()){
					ask = getch();
					if (int(ask)-48==correct[select]){
						capital += (-1*monto) * 0.4;
					}
					next=false;
				}
			}
		}
		monto += capital;
		cout<<"\n Ganancia: "<<monto<<" $\n"<<endl;
		getch();
		return monto;
	}
	return 0.0;
}


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
		cities = nullptr;
		if (one){
			cout<<"\n =======>>> NEW WORLD =======>>>\n\n";
			fflush(stdin);
			cout<<" Enter world name: ";getline(cin,world);
			fflush(stdin);
			cout<<" Enter first local name: ";getline(cin,name);
			fflush(stdin);
			
			cities = new City(world, name, n_city);
			cout<<"\n :: Successful Creation ::\n";
			getch();
			cities->houses[0]->money = 1000000.0;
			cities->run_city();
			delete cities;
			
			/*
			if(create_new_data(world, name)){
				cout<<"\n :: Successful Creation ::\n";
				getch();
				cities->houses[0]->money = 1000000.0;
				cities->run_city();
			}
			*/
		}
		else{
			cout<<"\n =======>>> WORLDS =======>>>\n\n";
			/*
			if(load_data()){
				cities->run_city();
			}
			*/
			cout<<"\n :: Successful Load ::\n";
			getch();
		}
	}
}

/*
bool DataBase::load_data(){
	City *dato;

	file = fopen("database.dat","rb"); 

	if(file==0){          
		cout<<"\n Error, file didnt find.\n"<<endl;
		system("pause");
		//exit(1);
		return false;
	}
	else{
		int i=0, select;
		while(fread(dato, sizeof(City), 1, file)){
			cout<<"\n "<<i+1<<") "<<dato->world<<endl;
			i++;
		}
		//fclose(file);
		cout<<endl;
		
		do{
			cout<<" Enter world(1-"<<i<<"): ";cin>>select;
		}while(select<1 || select >i);
		
		fseek(file, (long)(select-1) * sizeof(City), 0);
		fread(cities, sizeof(City), 1, file);
		
		fclose(file);
	}
	return true;
}


bool DataBase::create_new_data(string w, string n){
	file = fopen("database.dat","rb");
	if(file == 0){
		fclose(file);
		file = fopen("database.dat","wb");
		if(file == 0){
			cout<<"\n Error, no se pudo CREAR el archivo."<<endl;
			system("pause");
			//exit(1);
			return false;
		}
		else{
			cout<<"\n Se pudo CREAR el archivo correctamente."<<endl;
			//system("pause");
			fclose(file);
		}
	}
		
	file = fopen("database.dat","ab");
	
	if(file == 0){
		cout<<"\n Error, NO se pudo añadir elementos al archivo."<<endl;
		system("pause");
		//exit(1);
		return false;
	}
	else{
		cities = new City(w, n, n_city);
		fwrite(cities, sizeof(City), 1, file);
		fclose(file);
		n_city++;
	}
	return true;
}

void DataBase::save_data(int index){
	FILE *file_2;
	City dato;
	
	file = fopen("database.dat","rb"); 
	file_2 = fopen("data_save.dat","wb+");

	if(!file){          
		cout<<" Error, file didnt find."<<endl;
		system("pause");
		exit(1);
	}
	else{
		int con = 0;
		while(fread(&dato, sizeof(City), 1, file)){
			if(index == con){
				fwrite(cities, sizeof(City), 1, file_2);
			}
			else{
				fwrite(&dato, sizeof(City), 1, file_2);
			}
			con++;
		}
		fclose(file);
		
		file = fopen("database.dat","wb+");
		fseek(file_2, (long)(0)*sizeof(City), 0);
		while(fread(&dato, sizeof(City), 1, file_2)){
			fwrite(&dato, sizeof(City), 1, file);
		}
		fclose(file_2);
		remove("data_save.dat");
		fclose(file);
	}
}
*/