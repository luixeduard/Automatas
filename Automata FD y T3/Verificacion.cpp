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
	int nver[max];
}T_FIN;
T_FIN Tabla[max][max];

char aiuda[max][max];
ifstream verificar;
ifstream cargar;
ifstream lan;
int cont;
int tr;

int verificacion(){
	string nombreArchivo,texto;
	verificar.open("validar.txt",ios::in);
	if(verificar.fail()){
		cout<<"No hay elementos a evaluar"<<endl;
		exit(1);
	}
	verificar.close();
	verificar.open("lenguaje.txt",ios::in);
	if(verificar.fail()){
		cout<<"Error"<<endl;
		exit(1);
	}
	verificar.close();
}


int charge(){
	string texto;
	char aux[max];
	char cad[max];
	char aa[2];
	int i,tr,num,t=0;
	tr=0;
	while(!cargar.eof()){ //mientras no sea final del archivo
		getline(cargar,texto);
		std::string str = texto;
		const char *caaa = str.c_str();
		strcpy(aiuda[tr],caaa);
		tr+=1;
	}
	tr-=1;
	//for(int i=0;i<tr;i++){
	//	cout<<aiuda[i]<<endl;
	//}
	for(i=0;i<tr;i++){
		strcpy(cad,aiuda[i]);
		int c=0;
		int co=0;
		for(int j=0;j<=strlen(cad);j++){
			if(cad[j]!='|' && cad[j]!='\0'){
				aux[c]=cad[j];
				c+=1;
			}
			else{
				//printf("%d",co);
				//printf("|%s|\n",aux);
				num=atoi(aux);
				//cout<<num<<endl;
				Tabla[i][co].nver[0]=num;
				co+=1;
				if(t<c){
					t=c+1;	
				}
				c=0;
				strcpy(aux,"-");
		}
	}
	strcpy(aux,"-");
}
	/*printf("Tabla:\n");
	for(int i=0;i<tr;i++){
		for(int j=0;j<t;j++){
			printf("|%d|",Tabla[i][j].nver[0]);
		}
		printf("\n");
	}*/
cargar.close();
}

int char_index(char a[],char x){
	int i;
	i=0;
	while (a[i]!=x&&i<strlen(a)){
		i=i+1;
	}
	if(strlen(a)==i){
		return -1;
	}
	else{
		return i;
	}
}

validar(){
	string texto;
	int ini=1,acep=0;
	char cad[max];
	char alf[max];
	while(!lan.eof()){ //mientras no sea final del archivo
		getline(lan,texto);
		std::string str = texto;
		const char *caaa = str.c_str();
		strcpy(alf,caaa);
	}
	cout<<alf<<endl;
	cout<<"¿Cual es tu cadena a verificar?"<<endl;
	scanf("%s",cad);
	int i=0;	
	int b=strlen(alf)+2;
	while(acep!=1&&i!=strlen(cad)){
		int v=char_index(alf,cad[i]);
		if(v==-1){
			acep=0;
			break;
		}
		cout<<"Estado actual"<<endl;
		cout<<ini<<endl;
		ini=Tabla[ini][v+1].nver[0];
		acep=Tabla[ini][b].nver[0];
		if(ini==0){
			acep=0;
			break;
		}
		cout<<"Siguiente estado"<<endl;
		cout<<ini<<endl;
		i+=1;
	}
	if(acep==1){
		cout<<"Cadena valida"<<endl;
	}
	else{
		cout<<"Cadena no valida"<<endl;
	}
}

main(){
	int opc=1;
	verificacion();
	cargar.open("validar.txt",ios::in);
	lan.open("lenguaje.txt",ios::in);
	charge();
	while(opc!=2){
		validar();
		printf("¿Deseas verificar otra cadena?\n");
		printf("1.- Si\n");
		printf("2.- No\n");
		printf("Opcion: ");
		scanf("%d",&opc);
		if(opc==2){
			if(std::remove("validar.txt")!=0 ){
                cout<<"Error al removerlo: "<<strerror(errno)<<endl;
            }else{
                cout<<"Archivo removido"<<endl;
            }
            if(std::remove("lenguaje.txt")!=0 ){
                cout<<"Error al removerlo: "<<strerror(errno)<<endl;
            }else{
                cout<<"Archivo removido"<<endl;
            }
		}
	}
}
