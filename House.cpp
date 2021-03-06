/****************************************************************
Proyecto final

Departamento de Ciencia de la Computación
Prof: D.Sc. Manuel Eduardo Loaiza Fernández

Alumnos:
 - Cristian Mellado Baca
 - Marcelo Torres Acuña
 - Alexander Carpio Mamani
*****************************************************************/

#include "House.h"

int models[8][6] = {{61,61,61,124,254,124},{30,30,30,91,4,93},
					{220,223,220,219,254,219},{241,241,241,177,35,177},
					{194,79,194,180,12,195},{105,105,105,221,207,221},
					{203,205,203,186,186,186},{242,242,242,197,197,197}};
					
double prices[8][2] = {{10000.0,100.0}, {12000.0, 120.0}, {15000.0, 150.0},{15000.0, 150.0},
				{20000.0, 200.0}, {25000.0, 250.0}, {35000.0, 350.0}, {40000.0, 400.0}};
				
string description[8] = {"1) Restaurant", "2) Painters", "3) Constructor", "4) Properties",
				"5) Transactions", "6) Stonks", "7) Hotel", "8) Casino"};
				
string description_text[8] = {" This house permit food to the user for not dying.",
	 " This house allow to the house paint to others houses.", 
	 " This house allow update or built floors to every house. ", 
	 " This allow change name of to every house and sell these.", 
	 " This house allow translate money between houses.", 
	 " This house allow hack and invert in any bussines.", 
	 " This house ears 350 $.",
	 " This house serves for playing games and earn money."};
 
 
House::House(int h=0, int x=5, string name="nothing"){
	limit = 30;
	n = 2;
	n_variables = 18;  // number of variables of house
	
	model = new int [6];   // separamos memoria pra un arreglo
	for (int i=0;i<6;i++){
		model[i] = models[h][i];
	}
	
	house = new int *[30];  // separamos memoria para un arreglo de punteros
	for(int i=0; i<30;i++){
		house[i] = new int [2]; // separamos memoria para un arreglo
	}
	
	house[0][0] = x;
	house[0][1] = 38;
	house[1][0] = x;
	house[1][1] = 37;	
	
	this->name = name;
	color = 1;
	
	money = 100.0;
	price = prices[h][0];
	pay = prices[h][1];
	
	money_month = new double [4]; // separamos memoria para un arreglo
	for (int i=0;i<4;i++){
		money_month[i] = 0.0;
	}
	
	tax = 0.2;
	employees = 20.0;
	light_and_water = 0.0;
}

House::~House(){   // liberamos memoria reservada.
	delete[] model;
	
	for(int i=0; i<30;i++){
		delete[] house[i];
	}
	delete[] house;
	delete[] money_month;
}

void House::load_house(string arr[], int &index){
	this->name = arr[index];
	
	for (int i=0;i<6;i++){
		model[i] = atoi(arr[index + 1 + i].c_str());
	}
	
	n = atoi(arr[index+7].c_str());
	
	house[0][0] = atoi(arr[index + 8].c_str());
	house[0][1] = atoi(arr[index + 9].c_str());
	
	for(int i=1; i<n;i++){
		house[i][0] = house[0][0];
		house[i][1] = house[0][1] - i;
	}
	
	color = atoi(arr[index+10].c_str());
	
	money = atof(arr[index+11].c_str());
	price = atof(arr[index+12].c_str());
	pay = atof(arr[index+13].c_str());
	
	for (int i=0;i<4;i++){
		money_month[i] = atof(arr[index+14+i].c_str());
	}
	
	index += n_variables;
}

string House::save_house(){
	string all = "";
	
	all += name + ";";
	
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

bool House::request_house(int x, int y){
	for (int i=0; i<n; i++){
		if(house[i][0]==x && house[i][1]==y) return true;
	}
	return false;
}

void House::add_house(){
	double sell_house_price = 0.25, total;
	string pisos_s;
	
	if (n<limit){
		if (money > price*sell_house_price){
			int pisos=28;char op;
			
			for(int i=1.0; i<limit-2; i++){
				if(double(i)*price*sell_house_price > money){
					pisos = i - 1;
					break;
				}
			}
			
			cout<<"\n Max number of floors with you buget "<<pisos<<endl;
			do{
				cout <<"\n How many floors you want to buy ? ";
				fflush(stdin);
				getline(cin, pisos_s);
				fflush(stdin);
				pisos = atoi(pisos_s.c_str());
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
	
	switch(color){
		case 1:cout<<BLOCK_BLACK;break;
		case 2:cout<<BLOCK_RED;break;
		case 3:cout<<BLOCK_GREEN;break;
		case 4:cout<<BLOCK_YELLOW;break;
		case 5:cout<<BLOCK_BLUE;break;
		case 6:cout<<BLOCK_MAGENTA;break;
		case 7:cout<<BLOCK_CYAN;break;
		case 8:cout<<BLOCK_WHITE;break;
		case 9:cout<<BLOCK_LIGHT_BLACK;break;
		case 10:cout<<BLOCK_LIGHT_RED;break;
		case 11:cout<<BLOCK_LIGHT_GREEN;break;
		case 12:cout<<BLOCK_LIGHT_YELLOW;break;
		case 13:cout<<BLOCK_LIGHT_BLUE;break;
		case 14:cout<<BLOCK_LIGHT_MAGENTA;break;
		case 15:cout<<BLOCK_LIGHT_CYAN;break;
		case 16:cout<<BLOCK_LIGHT_WHITE;break;
	}
		
	if (color == 8 || color == 16 || color== 15 || color==12 || color == 10 || color == 4) 
		cout<<BLACK;
	
	if (row==house[n-1][1]){
		
		cout<<char(model[0])<<char(model[1])<<char(model[2]);
	}
	else{
		cout<<char(model[3])<<char(model[4])<<char(model[5]);
	}
	cout<<RESET;
}

void House::set_name_house(string rename){
	name = rename;
}

void House::set_color(int c){
	color = c;
}

void House::change_color(){
	int op;
	string op_s;
	char confirm;
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
			cout <<" option: ";
			fflush(stdin);
			getline(cin, op_s);
			fflush(stdin);
			op = atoi(op_s.c_str());
		}while(op<1 || op>16);
		
		do{
			cout<<" Do you sure of change color by "<<total<<" $ ? (y/n): ";
			cin>>confirm;
		}while(confirm!='y' && confirm!='n');
			
		if (confirm=='y'){
			money -= total;
			color = op;
			cout<<"\n :: Successful Color ::\n";
		}
	}
	else{
		cout <<"\n You dont have enough money.\n";
	}
}


void House::house_info(){
	cout <<"\n\n ============>>> "<<name<<endl<<endl;
	cout <<"\t:: House ::"<<endl;
	cout <<" Current Money: "<<money<<" $"<<endl;
	cout <<" Money per month: "<<1.0<<" $ - "<<pay<<" $"<<endl;
	cout<<" Price House: "<<price<<" $"<<endl<<endl;
	
	cout <<"\t:: Payments ::"<<endl;
	cout<< " Tax(impuesto): "<<tax*100.0<<"% of month"<<endl;
	cout<<" Employees: "<<employees<<" $"<<endl;
	cout<< " light and water: 10 $ - 30 $"<<endl<<endl;
	getch();
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

void House::receive(double amount){
	money += amount;
}

double House::get_money(){
	return money;
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




