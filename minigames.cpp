/****************************************************************
Proyecto final

Departamento de Ciencia de la Computación
Prof: D.Sc. Manuel Eduardo Loaiza Fernández

Alumnos:
 - Cristian Mellado Baca
 - Marcelo Torres Acuña
 - Alexander Carpio Mamani
*****************************************************************/

#include "minigames.h"

MiniGames::MiniGames(){
	entry=100.0;
	total=0.0; 
	tictac_money = 200.0;
	snake_money=10.0;
	rulette_money = 200.0;
	
	getcwd(directory_hacker, 256);   // save the current directory in the arr var directory_hacker.
	strcat(directory_hacker, "\\hacker_text.txt");  //concatenate with filename of hacker text.
	//strcpy(directory_hacker, "hacker_text.txt");
}

MiniGames::~MiniGames(){
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
	string number_s;
	bool c_t = true, c_b = true, c_l=true, c_r=true, ball=true, con;
	
	cout<<"\n  ======= Ruleta =====>>> :b"<<endl<<endl;
	//cout<<num<<endl;
	do{
		cout <<" 1) color(green: x3, red and black: x1)\n 2) number(x7)\n option: ";cin>>op;
	}while(op!='1' && op!='2');
	cout<<endl;
	if(op=='2'){
		do{
			cout<<" Enter your number(0-19): ";
			fflush(stdin);
			getline(cin, number_s);
			fflush(stdin);
			number = atoi(number_s.c_str());
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
	else if (selected == 'g' && win == 'g'){
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
	string op_s;
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
		
		do{
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
				fflush(stdin);
				getline(cin, op_s);
				fflush(stdin);
				op = atoi(op_s.c_str());
			}
			else{
				srand(time(NULL));
				op = 1 + rand()%9;
			}
		
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
	string info, amount_s;
	
	datos.open(directory_hacker, ios::in);  
	//datos.open("hacker_text.txt", ios::in);
		
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
		cout<<"\n\n\t ENTER AMOUNT TO HACKING(1-infinite)$: ";
		fflush(stdin);
		getline(cin, amount_s);
		fflush(stdin);
		amount = atoi(amount_s.c_str());
	}while(amount<1);
	
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