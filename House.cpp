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

int models[4][6] = {{61,61,61,124,254,124},{94,94,94,91,4,93},
					{203,205,203,186,186,186},{242,242,242,197,197,197}};
double prices[4][2] = {{10000.0,100.0}, {18000.0, 180.0}, {25000.0, 250.0},{40000.0, 400.0}};

House::House(int h=0, int x=5, string name="nothing"){
	for (int i=0;i<6;i++){
		model[i] = models[h][i];
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
	
	for (int i=0;i<4;i++){
		money_month[i] = 0.0;
	}
	
	tax = 0.2;
	employees = 20.0;
	light_and_water = 0.0;
}

void House::load_house(string arr[], int index){
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
			cout <<" option: ";cin>>color;
		}while(color<1 || color >16);
		
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
	cout <<" Current Money: "<<money<<" $"<<endl;
	cout <<" Money per month: "<<1.0<<" $ - "<<pay<<" $"<<endl;
	cout<<" Price House: "<<price<<" $"<<endl<<endl;
	
	cout <<"\t:: Payments ::"<<endl;
	cout<< " Tax(impuesto): "<<tax*100.0<<"% of month"<<endl;
	cout<<" Employees: "<<employees<<" $"<<endl;
	cout<< " light and water: 10 $ - 30 $"<<endl<<endl;
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




