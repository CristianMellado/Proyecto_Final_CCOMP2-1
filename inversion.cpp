/****************************************************************
Proyecto final

Departamento de Ciencia de la Computación
Prof: D.Sc. Manuel Eduardo Loaiza Fernández

Alumnos:
 - Cristian Mellado Baca
 - Marcelo Torres Acuña
 - Alexander Carpio Mamani
*****************************************************************/

#include "inversion.h"

string Inversion::gen_bar(int n, int t){
	string bar = "";

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