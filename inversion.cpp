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

Inversion::Inversion(){
	n_ask = 14;
	capital=0.0;
	monto=0.0;
	
	string ask[n_ask] ={
		" Cual es el cerebro de una computadora?\n1) El procesador\n2) El disco duro\n3) La memoria ram",
		
		" Cómo se le llama a una colección de revistas, diarios y publicaciones periódicas?\n 1) hemeroteca\n 2) biblioteca\n 3) reviteca",
	
		" Cuál fue el primer metal que empleó el hombre?\n 1) Hierro\n 2) Cobre\n 3) Acero", 

		" Cuanto es el IGV?\n 1) 18% \n 2) 22%\n 3) 16%",

		" En que año el Perú logró su independencia?\n 1) 1821\n 2) 1848\n 3) 1813",

		" Cual es la capital del pais de Bogota?\n 1) Ninguna de las anteriores\n 2) Colombia\n 3) Medellin",

		" Cual es el pais mas pequeño?\n 1) El Vaticano\n 2) Monaco \n 3) Maldivas",

		" Cuanto duro la guerra de 100 años?\n 1) 116 años\n 2) 100 años\n 3) 99 años",

		" Cual es el sistema operativo para pc's mas usado?\n 1) Windows\n 2) Linux\n 3) Mac", 

		" Quien es el o la cantante mas famoso(a) peruano?\n 1) Yma Sumac\n 2) Eva Ayllon\n 3) Faraon Love Shady",

		" En qué año murió Steve Jobs?\n 1) 1999\n 2) 2010\n 3) 2011",

		" Cómo se llama la primera estación espacial rusa?\n 1) Sputnik I\n 2) Sputnik\n 3) Mir", 

		" Quien fue uno de los creadores de google?\n 1) Larry Page\n 2) Bill gates\n 3) Steve Jobs",
	
		" Quien escribio la novena sinfonia de Beethoven?\n 1) Beethoven y Chopin\n 2) Tu vieja\n 3) Tu viejo",
		
	};

	int answers[n_ask] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	
	preguntas = ask;
	correct = answers;
}

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