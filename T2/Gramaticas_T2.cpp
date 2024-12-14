#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Variables de control
int n_prod;
char cadena[100];
//Variables auxiliares
int caso;
int estado;
bool salir;
bool x1=false;
typedef struct prod{
	char nt;
	char p[100];
}T_prod;
T_prod producciones[100];
void leer_producciones(int n, int i){
	system("cls");
	while(i<n){
		printf("Para la produccion %i\n",i+1);
		printf("Ingrese el no terminal\n");
		scanf("%s",&producciones[i].nt);
		//strupr(producciones[i].nt);//No se si esto se puede hacer
		printf("Ingrese la produccion\n");
		scanf("%s",&producciones[i].p);
		i=i+1;
		system("cls");
	}
	printf("Producciones agregadas satisfactoriamente\n");
	system("pause");
	system("cls");
}
void producciones_por_default(){
	n_prod=2;
	producciones[0].nt='S';
	strcpy(producciones[0].p,"aSb");
	producciones[1].nt='S';
	strcpy(producciones[1].p,"ab");
}
void ver_producciones(){
	int i=0;
	printf("Tabla de producciones: \n");
	while (i<n_prod){
		printf("%c -> %s\n",producciones[i].nt,producciones[i].p);
		i=i+1;
	}
}
int n_terminales(char c[]){
	int i=0;
	int n=0;
	while (i<strlen(c)){
		if (c[i]>='a' && c[i]<='z'){
			n=n+1;
		}
		i=i+1;
	}
	return n;
}
int n_No_terminales(char c[]){
	int i=0;
	int n=0;
	while (i<strlen(c)){
		if (c[i]>='A' && c[i]<='Z'){
			n=n+1;
		}
		i=i+1;
	}
	return n;
}
int nt_search(char c[]){
	int i;
	int n;
	bool seguir_buscando=true;
	i=0;
	while (i<strlen(c) && seguir_buscando==true){
		if (c[i]>='A' && c[i]<='Z'){
			n=i;
			seguir_buscando=false;
		}
		i=i+1;
	}
	if (n==strlen(c)){
		n=-1;
	}
	return n;
}
int ssubstr(char a[],char b[]){
	char re[100];
	int i,j;
	if(strstr(a,b)!=0){
		strcpy(re,strstr(a,b));
		i=strlen(a)-strlen(re);
		return i;
	}
	else{
		i=-1;
		return i;
	}
}
int busc_prod(char c[],char nt){
	estado=0;
	int index;
	bool fin=false;
	while (estado<n_prod && fin==false){
		if (nt==producciones[estado].nt){
			index=ssubstr(c,producciones[estado].p);
		}
		if (index!=-1){
			fin=true;
		}
		estado=estado+1;
	}
	estado=estado-1;
	return index;
}
void replace_string(char c1[],int actual,int inicio){
	char aux[100];
	char aux3[100];
	bool caso_base=true;
	aux3[0]=producciones[actual].nt;
	int i;
	i=0;
	while (i<inicio){
		aux[i]=c1[i];
		i=i+1;
		caso_base=false;
	}
	strcat(aux,aux3);
	i=i+strlen(producciones[actual].p);
	while (i<strlen(c1)){
		aux[i-strlen(producciones[actual].p)+1]=c1[i];
		i=i+1;
	}
	strcpy(c1,aux);
}
validar_cadena(char c1[]){
	int max;
	int i=0;
	int x=0;
	int fijar,index;
	bool terminar=false;
	char c2[strlen(c1)];
	strcpy(c2,c1);
	if(x1==false){
		printf("Validacion de cadena: \n");
		x1=true;
	}
	while(terminar==false){
		printf("%s\n",c2);
		x=0;
		while (x<n_prod&&terminar==false){
			index=busc_prod(c2,producciones[x].nt);
			x=x+1;
		}
		if (index!=-1){
			replace_string(c2,estado,index);
			printf("La cadena actual es: ");
			if(strlen(c2)>1){
				validar_cadena(c2);
			}
		}
		terminar=true;
	}
}
void trabajar_cadena(){
	bool cadenas=true;
	bool valida;
	while (cadenas==true){
	ver_producciones();
		printf("Ingrese su cadena\n");
		scanf("%s",&cadena);
		validar_cadena(cadena);
		printf("La cadena es valida si aparece unicamente: %c\n",producciones[0].nt);
		system("pause");
		system("cls");
		printf("Desea validar otra cadena?\n");
		printf("1.- Si\n");
		printf("2.- Salir\n");
		scanf("%i",&caso);
		system("cls");
		switch(caso){
			case 1:
				cadenas=true;
			break;
			case 2:
				cadenas=false;
			break;
		}
	}
}
void llenar_producciones(){
	printf("Ingrese la cantidad de producciones\n");
	scanf("%i",&n_prod);
	leer_producciones(n_prod,0);
}
main(){
	llenar_producciones();
	//producciones_por_default();
	printf("Estas son sus producciones: \n");
	ver_producciones();
	printf("Desea ingresar una cadena?\n");
	printf("1.- Si\n");
	printf("2.- Salir\n");
	scanf("%i",&caso);
	system("cls");
	switch(caso){
		case 1:
			trabajar_cadena();
		break;
		case 2:
			salir=true;
		break;
	}
}
