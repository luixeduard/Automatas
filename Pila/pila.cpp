#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<windows.h>
#include<stack>
#define max 100
using namespace std;

typedef struct est{
	int npila[max];
	char cpila[max];
}T_FIN;
T_FIN Tabla[max][6];

stack <char> pila;

ofstream registro;
ifstream cargar;
int cont;
char aiuda[max][max];
int ini=999;
int tr;
int iniciarpila(){
    pila.empty();
    pila.push('#');
}

int verificacion_registro(){
	string nombreArchivo,texto;
	registro.open("registroP.txt",ios::app);
	if(registro.fail()){
		registro.open("registroP.txt",ios::out);
	}
}

int creacion(){
	ofstream arc;
	char aux[2];
	char aa[2];
	char cad[max];
	string texto=".txt";
	int i,num;
	std::string buff = "";
	buff = static_cast<std::ostringstream*>(&(std::ostringstream() << cont))->str();
	buff=buff+texto;
	strcpy(aux,"-");
	strcpy(aa,"-");
	printf("Hola usuario necesito tus transiciones\n");
	printf("Ejemplo:\n");
	printf("1,a,#=1,x#\n");
	printf("Primer elemento: el estado del que se parte\n");
	printf("Segundo elemento: la letra que habra que buscar\n");
	printf("Tercer elemento: lo que debe haber en la pila\n");
	printf("Cuarto elemento: el estado al cual cambiara\n");
	printf("Quinto elemento: la letra a la que se cambiara\n");
	printf("Quitar y vacio es igual a: &\n");
	printf("Favor de no utilizar el estado 0\n");
	printf("Dame tu numero de transiciones:");
	scanf("%i",&tr);
	arc.open(buff.c_str(),ios::out);
	for(i=1;i<=tr;i++){
		printf("%d.-",i);
		scanf("%s",&cad);
		arc<<cad<<endl;
		if(strlen(cad)==9){
			cad[9]=',';
			cad[10]='?';
			cad[11]='\0';
		}
		if(strlen(cad)==10){
			aa[0]=cad[9];
			cad[9]=',';
			cad[10]=aa[0];
			cad[11]='\0';
			strcpy(aa,"-");
		}
		int c=0;
		int co=0;
		for(int j=0;j<=strlen(cad);j++){
			if(cad[j]!=',' && cad[j]!='=' && cad[j]!='\0'){
				aux[0]=cad[j];
				c+=1;
				//printf("|%s|\n",aux);
			}
			else{
				//printf("%d",co);
				//printf("|%s|\n",aux);
				if(co==0 || co==3){
					num=atoi(aux);
					if(co==0){
						Tabla[i-1][co].npila[0]=num;
					}
					else if(co==3){
						Tabla[i-1][co-2].npila[0]=num;
					}
					//printf("||%d||\n",num);
				}
				else{
					if(co==1){
						Tabla[i-1][co-1].cpila[0]=aux[0];
					}
					else if(co==2){
						Tabla[i-1][co-1].cpila[0]=aux[0]; //1,0,#=1,#
					}
					else if(co==4){
						Tabla[i-1][co-2].cpila[0]=aux[0];
					}
					else if(co==5){
						Tabla[i-1][co-2].cpila[0]=aux[0];
					}
				}
				co+=1;
				c=0;
				strcpy(aux,"-");
			}
		}
	}
	arc.close();
/*	printf("Estados:\n");
	for(int i=0;i<tr;i++){
		for(int j=0;j<2;j++){
			printf("|%d|",Tabla[i][j].npila[0]);
		}
		printf("\n");
	}
	printf("Cosas:\n");
	for(int i=0;i<tr;i++){
		for(int j=0;j<4;j++){
			printf("|%c|",Tabla[i][j].cpila[0]);
		}
		printf("\n");
	}*/
}

int verificar(string c){
	ifstream archivo;
	string texto;
	archivo.open("registroP.txt",ios::in);
	cont=0;
	while(!archivo.eof()){
		getline(archivo,texto);
		if(texto==c){
			cont+=1;
			return 1;
		}
		else{
			cont+=1;
		}
	}
	archivo.close();
}

int estado_inicial(){
	int i=0;
	while(Tabla[i][0].npila[0]!=0){
		if(ini>Tabla[i][0].npila[0]){
			ini=Tabla[i][0].npila[0];
		}
		i+=1;
	}
}

int validar(){
	char cadena[max];
	int esti,i,j,w;
	estado_inicial();
	iniciarpila();
	esti=ini;
	int fin=0,val=0;
	printf ("Ingrese la cadena\n");
	scanf("%s",&cadena);
	printf("¿Cuanto quieres que tarde en segundos que se tarde cada accion?");
	scanf("%d",&w);
	w=w*1000;
	strcat(cadena,"&");
	cout<<cadena<<endl;
	int con=0;
	j=0;
	while(fin!=1){
	    i=0;
        while(Tabla[i][0].npila[0]!=0){
            if(esti==Tabla[i][0].npila[0]){
            	if(cadena[j]==Tabla[i][0].cpila[0] &&cadena[j]=='&'&&Tabla[i][1].cpila[0]=='#'&& Tabla[i][2].cpila[0]=='#'){
                    printf("\nSimbolo de entrada %c\n",cadena[j]);
                    printf("Simbolo de pila %c\n",pila.top());
                    printf("Posicion en cadena  %d\n",j);
                    printf("Posicion en tabla  %d\n",i);
                    printf("Estado %d\n",esti);
                	fin=1;
                	con=0;
                	val=1;
          		}
             	else if(cadena[j]==Tabla[i][0].cpila[0]&&pila.top()==Tabla[i][1].cpila[0]){
                 	if(Tabla[i][3].cpila[0]!='?'&&Tabla[i][2].cpila[0]!='&'){
                    printf("\nSimbolo de entrada %c\n",cadena[j]);
                    printf("Simbolo de pila %c\n",pila.top());
                    printf("Posicion en cadena  %d\n",j);
                    printf("Posicion en tabla  %d\n",i);
                    printf("Estado %d\n",esti);
                    	cout << pila.top() <<endl ;
						char m=Tabla[i][2].cpila[0];
                    	pila.push(m);
                    	esti=Tabla[i][1].npila[0];
                    	j+=1;
                    	cout << pila.top() <<endl;
                 	}
                 	else if(Tabla[i][2].cpila[0]=='&'){
                    printf("\nSimbolo de entrada %c\n",cadena[j]);
                    printf("Simbolo de pila %c\n",pila.top());
                    printf("Posicion en cadena  %d\n",j);
                    printf("Posicion en tabla  %d\n",i);
                    printf("Estado %d\n",esti);
                 		cout << pila.top() << endl;
                 		pila.pop();
                 		esti=Tabla[i][1].npila[0];
                 		j=j+1;
                 		cout << pila.top() <<endl ;
					 }else if(Tabla[i][1].cpila[0]==Tabla[i][2].cpila[0]){
                    printf("\nSimbolo de entrada %c\n",cadena[j]);
                    printf("Simbolo de pila %c\n",pila.top());
                    printf("Posicion en cadena  %d\n",j);
                    printf("Posicion en tabla  %d\n",i);
                    printf("Estado %d\n",esti);
                        cout << pila.top() <<endl ;
					     esti=Tabla[i][1].npila[0];
					     j=j+1;
					     cout << pila.top() <<endl ;

					 }
					 Sleep(w);
            }
            else{
                con+=1;
                if(con>1000){
                val=0;
                fin=1;
                }

            }


        }
    i+=1;
	}
	}
	if(val==1){
		printf("Cadena valida\n");
	}
	else{
		printf("Cadena no valida\n");
	}


}

int charge(){
	string texto;
	char aux[max];
	char cad[max];
	char aa[2];
	int i,tr,num;
	tr=0;
	while(!cargar.eof()){ //mientras no sea final del archivo
		getline(cargar,texto);
		std::string str = texto;
		const char *caaa = str.c_str();
		strcpy(aiuda[tr],caaa);
		tr+=1;
	}
	tr-=1;
	printf("Transiciones del automata: \n");
	for(int i=0;i<tr;i++){
		cout<<aiuda[i]<<endl;
	}
	for(i=0;i<tr;i++){
		strcpy(cad,aiuda[i]);
		if(strlen(cad)==9){      //L(G)={a^nb^n|n>0}
			cad[9]=',';
			cad[10]='?';
			cad[11]='\0';
		}
		if(strlen(cad)==10){
			aa[0]=cad[9];
			cad[9]=',';
			cad[10]=aa[0];
			cad[11]='\0';
			strcpy(aa,"-");
		}
	int c=0;
	int co=0;
	for(int j=0;j<=strlen(cad);j++){
		if(cad[j]!=',' && cad[j]!='=' && cad[j]!='\0'){
			strcpy(aux,"-");
			aux[0]=cad[j];
			c+=1;
		}
		else{
			//printf("%d",co);
			//printf("|%s|\n",aux);
			if(co==0 || co==3){
					num=atoi(aux);
					if(co==0){
						Tabla[i][co].npila[0]=num;
					}
					else if(co==3){
						Tabla[i][co-2].npila[0]=num;
					}
					//printf("||%d||\n",num);
			}
			else{
				if(co==1){
					Tabla[i][co-1].cpila[0]=aux[0];
				}
				else if(co==2){
					Tabla[i][co-1].cpila[0]=aux[0];
				}
				else if(co==4){
					Tabla[i][co-2].cpila[0]=aux[0];
				}
				else if(co==5){
					Tabla[i][co-2].cpila[0]=aux[0];
				}
			}
			co+=1;
			c=0;
		}
	}

}
	/*printf("Estados:\n");
	for(int i=0;i<tr;i++){
		for(int j=0;j<2;j++){
			printf("|%d|",Tabla[i][j].npila[0]);
		}
		printf("\n");
	}
	printf("Cosas:\n");
	for(int i=0;i<tr;i++){
		for(int j=0;j<4;j++){
			printf("|%c|",Tabla[i][j].cpila[0]);
		}
		printf("\n");
	}*/
cargar.close();
}

main(){
	iniciarpila();
	string cadena;
	int v;
	char buff[max];
	int opc=1;
	string texto=".txt";
	verificacion_registro();
	printf("Dame tu expresion para el automata de pila: ");
	getline(cin,cadena);
	v=verificar(cadena);
	if(v==1){
		std::string buff = "";
		buff = static_cast<std::ostringstream*>(&(std::ostringstream() << cont))->str();
		buff=buff+texto;
		cargar.open(buff.c_str(),ios::in);
		charge();
		cargar.close();
		while(opc!=2){
			validar();
			printf("¿Deseas verificar otra cadena?\n");
			printf("1.- Si\n");
			printf("2.- No\n");
			printf("Opcion: ");
			scanf("%d",&opc);
		}
	}
	else{
		registro<<cadena<<endl;
		creacion();
		while(opc!=2){
			validar();
			printf("¿Deseas verificar otra cadena?\n");
			printf("1.- Si\n");
			printf("2.- No\n");
			printf("Opcion: ");
			scanf("%d",&opc);
		}
	}
	}

