#include<ctype.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<stack>
#include<list>
#define max 100
using namespace std;

list<char> ext;//auxiliar en infija a posfija
char inf[max];//variable infija
char reinf[max];//resultado de la infija
char inft[max];//operacion de variables
bool aux=false;//Indica que la tabla está vacía
char let[max];//Todas las letras ocupadas
int estados_aceptacion[100];//Pues estos son los estados de aceptación xd
char alfabeto[100];
int ultimo_estado=1;//22/11/2017 6:25 pm
int primero,ultimo;
char thomson[max];
char expresion[100];
char esnew[500][max];
int d=0,est=0,reest=0;
int cont=0,lett=0;
int longitud_alfabeto,no_estados;
int exec,contesta=0;
char t2[max];
int ymt_senpai=0;
bool pegar_tabla=false;

typedef struct est{
	//int no_estado[100];//Es el número del estado actual, puede varíar según se una con otros estados
	int trans_estado[100];//Es la trancición a otro estado, si no tiene transición lo único que tendrá será -1
}T_estado;
T_estado tabla[500][100];//Tabla resultante
T_estado tabla_aux2[500][100];
T_estado t_a[3][3];//Tabla de una expresión a
T_estado t_b[3][3];//Tabla de una expresión b (Por si acaso xd)
T_estado t_kl[6][4];//Tabla de Kleene
T_estado t_or[4][7];//Tabla de or
T_estado t_nd[5][4];//Tabla de and
T_estado t_ps[7][4];//Tabla de a^+


int valS(stack<char> p, char inf[]){
	stack<char> aux;
	int i=0;
	while(inf[i]!='\0'){
		if(inf[i]=='|'||inf[i]=='*'||inf[i]=='.'||inf[i]=='+'||inf[i]=='('||inf[i]==')'||(inf[i]>=49&&inf[i]<=57)||(inf[i]>=65&&inf[i]<=90)||(inf[i]>=97&&inf[i]<=122)){
			if(inf[i]=='(')
				p.push(inf[i]);
			else if(inf[i]==')'){
				aux=p;
				if(!aux.empty()){
					if(inf[i]==')'){
						if(aux.top()=='(')
							p.pop();
					}
				}
				else
					p.push(inf[i]);
			}
			i++;
		}
		else{
			/*printf("NOTACION INCORRECTA\n");*/
			return 0;
			break;
		}
	}
	if(p.empty()){
		/*printf("\nNOTACION CORRECTA");*/
		return 1;
	}
	else{
		/*printf("\nNOTACION INCORRECTA");*/
		return 0;
	}
}

int valD(){
	int i,j,v;
	char aux[max];
	/*printf("%s\n",inf);*/
	for(i=0;i<=strlen(inf);i++){
		aux[i]=inf[i+1];
	}
	/*printf("%s\n",aux);*/
	for(i=0;i<=strlen(inf)-1;i++){
		if(inf[i]==aux[i]){	
			if(inf[i]=='|'){
				/*printf("aqui 1");*/
				return 1;
			}
			else if(inf[i]=='+'){
				/*printf("aqui 2");*/
				return 1;
			}
			else if(inf[i]=='*'){
				/*printf("aqui 3");*/
				return 1;
			}
			else if(inf[i]=='.'){
				/*printf("aqui 4");*/
				return 1;
			}
			else if((inf[i]>=48&&inf[i]<=57)||(inf[i]>=65&&inf[i]<=90)||(inf[i]>=97&&inf[i]<=122)){
				return 1;
				/*printf("aqui 5");*/
			}
		}
		else if(((inf[i]=='*')&&(aux[i]=='+'))||((inf[i]=='+')&&(aux[i]=='*'))){
			/*printf("aqui 6");*/
			return 1;
		}
		else if(((inf[i]=='|')&&(aux[i]=='+'))||((inf[i]=='|')&&(aux[i]=='*'))){
			/*printf("aqui 7");*/
			return 1;
		}
		else if(((inf[i]=='.')&&(aux[i]=='+'))||((inf[i]=='.')&&(aux[i]=='*'))){
			/*printf("aqui 8");*/
			return 1;
		}
		else if(((inf[i]=='|')&&(aux[i]=='.'))||((inf[i]=='.')&&(aux[i]=='|'))){
			/*printf("aqui 9");*/
			return 1;
		}
		else if(inf[i]=='*'&&((aux[i]>=48&&aux[i]<=57)||(aux[i]>=65&&aux[i]<=90)||(aux[i]>=97&&aux[i]<=122))){
			/*printf("aqui 10");*/
			return 1;
		}
		else if(inf[i]=='+'&&((aux[i]>=48&&aux[i]<=57)||(aux[i]>=65&&aux[i]<=90)||(aux[i]>=97&&aux[i]<=122))){
			/*printf("aqui 11");*/
			return 1;
		}
		else if(inf[i]==')'&&((aux[i]=='+')||(aux[i]=='|')||(aux[i]=='.')||(aux[i]=='*'))){
			v=0;
		}
		else if(v==0&&i==strlen(inf)-1){
			/*printf("aqui 12");*/
			return 0;
		}
	}	
}

int valG(){
	int i,j;
	for(i=0;i<=strlen(inf)-1;i++){
		if(inf[i]=='k'){
			return 1;
		}
	}
}

int valH(){
	int i;
	for(i=1;i<=strlen(inf)-1;i++){
		if((inf[i-1]>=48&&inf[i-1]<=57)&&((inf[i]>=65&&inf[i]<=90)||(inf[i]>=97&&inf[i]<=122))){
			return 1;
		}
	}
}

int trans1(){   //transformacion de kleene positivo
int cpc=0,cpa=0;
char aux[max];
int n,j,save,c,k;
strcpy(aux,inf);
for(int i=0;i<=strlen(inf);i++){
	if(inf[i]=='+'&&((inf[i-1]>=49&&inf[i-1]<=57)||(inf[i-1]>=65&&inf[i-1]<=90)||(inf[i-1]>=97&&inf[i-1]<=122))){
		n=i+5;
		inf[i]='.';
		inf[i+1]='(';
		inf[i+2]=inf[i-1];
		inf[i+3]='*';
		inf[i+4]=')';
		for(int j=n;j<=strlen(inf);j++){
			inf[j]=aux[j-4];
		}
		strcpy(aux,inf);
	}
	else if(inf[i]=='+'&&inf[i-1]==')'){
		/*printf("lol");*/
		cpc=1;
		n=i-2;
		for(j=n;j>=0;j--){
			if(inf[j]==')'){
				cpc+=1;
			}
			else if(inf[j]=='('){
				cpa+=1;
			}
			if(cpc==cpa&&(inf[j]=='(')){
				save=j;
				break;
			}
		}
		inf[i]='.';
		inf[i+1]='(';
		n=i+2;
		for(j=save;j<=i-1;j++){
			inf[n]=aux[j];
			n+=1;
		}
		inf[n]='*';
		inf[n+1]=')';
		n=n+2;
		for(k=i+1;k<=strlen(aux);k++){
			inf[n]=aux[k];
			n+=1;
		}
		strcpy(aux,inf);
	}
}
}

int trans2(){   //transformacion de * a ^k
int cpc=0,cpa=0;
char aux[max];
int n,j,save,c,k;
strcpy(aux,inf);
for(int i=0;i<=strlen(inf);i++){
	if(inf[i]=='*'){
		n=i;
		inf[i]='^';
		for(int j=n+1;j<=strlen(inf);j++){
			inf[j]=aux[j-1];
		}
		inf[i+1]='k';
		strcpy(aux,inf);
	}
}
}

int trans3(){    //transformacion de k^ a *
int i,j,n;
char aux[max];
	for(i=0;i<=strlen(inf);i++){
		n=i+1;
		if(inf[i]=='k'){
			for(j=0;j<i;j++){
				aux[j]=inf[j];
			}
			aux[j]='*';
			for(j=n;j<strlen(inf);j++){
				aux[j]=inf[n+1];
				n+=1;
			}
			strcpy(inf,aux);
		}
	}
}

int prioridad_infija(char a){
    if(a=='(')
        return 4;
	if(a=='^')
        return 3;
	if(a=='.')
        return 2;
    if(a=='|')
        return 2;
}

int prioridad_pila(char a){
	if(a=='^')
        return 3;
    if(a=='.')
        return 2;
    if(a=='|')
        return 2; /*necesitamos simbolo para multiplicacion*/
    if(a=='(')
        return 0;
}

int trans(char inf[]){  //transformacion de infija a posfija
	char out[max];
	char c;
	int i,p;
	int error=0;
	stack<char> pfin;	
	for(i=0;i<strlen(inf);i++){
	if((inf[i]>=49&&inf[i]<=57)||(inf[i]>=65&&inf[i]<=90)||(inf[i]>=97&&inf[i]<=122))
	ext.push_back(inf[i]);
	if(inf[i]=='|'||inf[i]=='.'||inf[i]=='('||inf[i]=='^'){
		if(pfin.empty())
			pfin.push(inf[i]);
		else{
			if(prioridad_infija(inf[i])>prioridad_pila(pfin.top()))
				pfin.push(inf[i]);
			else{
				if(prioridad_infija(inf[i])==prioridad_pila(pfin.top())){
					c=pfin.top();
					pfin.pop();
					ext.push_back(c);
					pfin.push(inf[i]);
				}
				else{
					c=pfin.top();
					pfin.pop();
					ext.push_back(c);
				}
			}
		}
	}
	if(inf[i]==')'){
		while(pfin.top()!='('&&!pfin.empty()){
			c=pfin.top();
			pfin.pop();
			ext.push_back(c);
		}
		if(pfin.top()=='(')
			c=pfin.top();
			pfin.pop();
	}
}
while(!pfin.empty()){
	c=pfin.top();
	pfin.pop();
	ext.push_back(c);
}
list<char>::iterator it=ext.begin();
printf("\n");
p=0;
while(it!=ext.end()){
	reinf[p]=*it++;
	p+=1;
}	
	strcpy(inf,reinf);
}

void qtrans(){    //conteo de letras y estados, abecedario
char Re[70];
char ord[70];
int i=0,j=0,k=0;
while(inf[i]){ 
    if(!strchr(Re,inf[i]))
        Re[j++]=inf[i];
    i++; 
} 
Re[j]='\0';
for(int i=0;i<=strlen(Re);i++){/*letras y filas*/
	if(((Re[i]>=48&&Re[i]<=57)||(Re[i]>=65&&Re[i]<=90)||(Re[i]>=97&&Re[i]<=106)||(Re[i]==108)||(Re[i]>=110&&Re[i]<=122))){
		lett=lett+1;
		cont=cont+1;
		let[k]=Re[i];
		k+=1;
		}
	}
for(int i = 1; i < strlen(let); i++)
    for(int j=0;j<strlen(let)-i;j++){
        if((tolower(let[j]))>(tolower(let[j+1]))){/*Para pasar la letra sea minuscula o mayuscula*/
			int x=let[j];
            let[j]=let[j+1];
            let[j+1]=x;
        }
    } 
for(int i=0;i<=strlen(inf);i++){/*solo estados y columnas*/
	if(((inf[i]>=48&&inf[i]<=57)||(inf[i]>=65&&inf[i]<=90)||(inf[i]>=97&&inf[i]<=106)||(inf[i]==108)||(inf[i]>=110&&inf[i]<=122))){
		est=est+2;
		d=d+2;
	}
	else if(inf[i]=='*'){
		est=est+2;
		d=d+2;
	}
	else if(inf[i]=='|'){
		est=est+2;
		d=d+2;
	}
	else if(i==strlen(inf)){
		cont=cont+3;
		d=d+1;
	}
}
/*printf("Filas: %i\n",cont);
printf("Columnas: %i\n",d);
printf("Numero de letras %i\n",lett);*/
reest=est;
printf("Numero de estados %i\n",est);
printf("Letras empleadas: %s\n",let); 
}

int int_index(int a[],int x){
	int i;
	i=0;
	while (a[i]!=x && a[i]!=0){
		i=i+1;
	}
	return i;
}

void intv_printf_tb(int a[]){   //Impresion de tabla
	int i=0;
	printf("|");
	while (a[i]!=0){
		printf("%i",a[i]);
		if(a[i+1]!=0&&exec!=1){
			printf(",");
		}
		i=i+1;
	}
	printf("|");
}

int char_index(char a[],char x){
	int i;
	i=0;
	while (a[i]!=x&&i<strlen(a)){
		i=i+1;
	}
	return i;
}

void ll_t_ayb(){
	int i,j;
	i=1;
	while (i<=2){
		j=1;
		while (j<=2){
			if (i==1&&j==1){
				t_a[i][j].trans_estado[0]=2;
				t_b[i][j].trans_estado[0]=2;
			}
			/*if (t_a[i][j].trans_estado[0]!=-1&&t_b[i][j].trans_estado[0]!=-1){
				printf("%i",t_a[i][j].trans_estado[0]);
				printf("%i",t_b[i][j].trans_estado[0]);
			}
			else{
				printf("  ");
			}*/
			j=j+1;
		}
		//printf(" \n");
		i=i+1;
	}
}

void nuevo_estado_tabla(int x,T_estado tabla[500][100]){//Añadir x estados al principio de la tabla
	int i,j,k,longitud;
	i=1;//Le suma x estados a cada transición
	while (i<=99){
		j=1;
		while (j<=99){
			if (tabla[i][j].trans_estado[0]!=0){
				longitud=int_index(tabla[i][j].trans_estado,100);//El estado 100 no existe, eso saca la longitud de cada vector tabla[i][j].trans_estado
				k=0;
				while (k<longitud){
					tabla[i][j].trans_estado[k]=tabla[i][j].trans_estado[k]+x;
					k=k+1;
				}
			}
			j=j+1;
		}
		i=i+1;
	}
	i=99;//Recorre x estados cada transición
	while (i>=1){
		j=99;
		while (j>=1){
			if (tabla[i][j].trans_estado[0]!=0){
				longitud=int_index(tabla[i][j].trans_estado,100);//El estado 100 no existe, eso saca la longitud de cada vector tabla[i][j].trans_estado
				k=0;
				while (k<longitud){
					tabla[i+x][j].trans_estado[k]=tabla[i][j].trans_estado[k];
					tabla[i][j].trans_estado[k]=0;
					if(ultimo_estado<tabla[i+x][j].trans_estado[k]){
						ultimo_estado=tabla[i+x][j].trans_estado[k];
					}
					k=k+1;
				}
			}
			j=j-1;
		}
		i=i-1;
	}
}

void ll_t_kl(){
	int i,j,l;
	i=1;
	while (i<=3){
		j=1;
		while (j<=5){
			if (i==1&&j==3){
				t_kl[i][j].trans_estado[0]=2;
				t_kl[i][j].trans_estado[1]=4;
			}
			else if(i==2&&j==1){
				t_kl[i][j].trans_estado[0]=3;
			}
			else if(i==3&&j==3){
				t_kl[i][j].trans_estado[0]=2;
				t_kl[i][j].trans_estado[1]=4;
			}
			/*if (t_kl[i][j].trans_estado[0]!=0){
				//printf("%i",t_kl[i][j].trans_estado[0]);
				intv_printf(t_kl[i][j].trans_estado);
			}
			else{
				printf("  ");
			}*/
			j=j+1;
		}
		//printf(" \n");
		i=i+1;
	}
}

void ll_t_or(){
	int i,j;
	i=1;
	while (i<=3){
		j=1;
		while (j<=6){
			if (i==1&&j==3){
				t_or[i][j].trans_estado[0]=2;
				t_or[i][j].trans_estado[1]=4;
			}
			else if(i==2&&j==1){
				t_or[i][j].trans_estado[0]=3;
			}
			else if(i==3&&j==3){
				t_or[i][j].trans_estado[0]=6;
			}
			else if(i==4&&j==2){
				t_or[i][j].trans_estado[0]=5;
			}
			else if(i==5&&j==3){
				t_or[i][j].trans_estado[0]=6;
			}
			/*if (t_or[i][j].trans_estado[0]!=-1){
				printf("%i",t_or[i][j].trans_estado[0]);
			}
			else{
				printf("  ");
			}*/
			/*if (t_or[i][j].trans_estado[0]!=0){
				//printf("%i",t_or[i][j].trans_estado[0]);
				intv_printf(t_or[i][j].trans_estado);
			}
			else{
				printf("  ");
			}*/
			j=j+1;
		}
		//printf(" \n");
		i=i+1;
	}
}

void ll_t_nd(){
	int i,j;
	i=1;
	while (i<=4){
		j=1;
		while (j<=3){
			if (i==1&&j==1){
				t_nd[i][j].trans_estado[0]=2;
			}
			else if(i==2&&j==3){
				t_nd[i][j].trans_estado[0]=3;
			}
			else if(i==3&&j==2){
				t_nd[i][j].trans_estado[0]=4;
			}
			/*if (t_nd[i][j].trans_estado[0]!=-1){
				printf("%i",t_nd[i][j].trans_estado[0]);
			}
			else{
				printf("  ");
			}*/
			/*if (t_nd[i][j].trans_estado[0]!=0){
				//printf("%i",t_nd[i][j].trans_estado[0]);
				intv_printf(t_nd[i][j].trans_estado);
			}
			else{
				printf("  ");
			}*/
			j=j+1;
		}
		//printf(" \n");
		i=i+1;
	}
}

void ll_t_ps(){
	int i,j;
	i=1;
	while (i<=6){
		j=1;
		while (j<=3){
			if (i==1&&j==1){
				t_ps[i][j].trans_estado[0]=2;
			}
			else if(i==2&&j==3){
				t_ps[i][j].trans_estado[0]=3;
			}
			else if(i==3&&j==3){
				t_ps[i][j].trans_estado[0]=4;
				t_ps[i][j].trans_estado[1]=6;
			}
			else if(i==4&&j==1){
				t_ps[i][j].trans_estado[0]=5;
			}
			else if(i==5&&j==3){
				t_ps[i][j].trans_estado[0]=4;
				t_ps[i][j].trans_estado[1]=6;
			}
			/*if (t_ps[i][j].trans_estado[0]!=-1){
				printf("%i",t_ps[i][j].trans_estado[0]);
			}
			else{
				printf("  ");
			}*/
			/*if (t_ps[i][j].trans_estado[0]!=0){
				//printf("%i",t_ps[i][j].trans_estado[0]);
				intv_printf(t_ps[i][j].trans_estado);
			}
			else{
				printf("  ");
			}*/
			j=j+1;
		}
		//printf(" \n");
		i=i+1;
	}
}

void ll_tablas(){
	//El código en comentario de cada módulo se puede "descomentar" para mostrar la tabla
	ll_t_ayb();
	ll_t_kl();
	ll_t_or();
	ll_t_nd();
	ll_t_ps();
}

void detalles(char exp[]){
	printf("Expresion: %s\n",exp);
	printf("Longitud de la expresion: %i\n",strlen(exp));
	//printf("Alfabeto generado: %s\n",alfabeto);
}

int buscar_operador(char exp[]){
	int i, indice;
	i=0;
	while(i<strlen(exp)){
		if(exp[i]=='*'||exp[i]=='+'||exp[i]=='|'||exp[i]=='.'){
			indice=i;
			i=strlen(exp);
		}
		i=i+1;
	}
	return indice;
}

 void thompson(char exp[],T_estado tabla[500][100]){//La tabla  thompson se llena aquíLa tabla  thompson se llena aquíLa tabla  thompson se llena aquíLa tabla  thompson se llena aquí
	int aux1;
	int tope=strlen(exp);
	int i=0;
	int operador;
	char exp_aux[100];
	operador=buscar_operador(exp);
	//printf("%c\n",exp[operador]);
	if (aux==false){
		switch (exp[operador]){
			case '*':
				aux1=char_index(alfabeto,exp[operador-1])+1;
				tabla[2][aux1].trans_estado[0]=3;
				aux1=char_index(alfabeto,'?')+1;
				tabla[1][aux1].trans_estado[0]=2;
				tabla[1][aux1].trans_estado[1]=4;
				tabla[3][aux1].trans_estado[0]=2;
				tabla[3][aux1].trans_estado[1]=4;
				ultimo_estado=4;
				ultimo=ultimo_estado;
			break;
			case '|':
				aux1=char_index(alfabeto,exp[operador-2])+1;
				tabla[2][aux1].trans_estado[0]=3;
				aux1=char_index(alfabeto,exp[operador-1])+1;
				tabla[4][aux1].trans_estado[0]=5;
				aux1=char_index(alfabeto,'?')+1;
				tabla[1][aux1].trans_estado[0]=2;
				tabla[1][aux1].trans_estado[1]=4;
				tabla[3][aux1].trans_estado[0]=6;
				tabla[5][aux1].trans_estado[0]=6;
				ultimo_estado=6;
				ultimo=ultimo_estado;
				/*Un estado más*/
			break;
			case '.':
				aux1=char_index(alfabeto,exp[operador-2])+1;
				tabla[1][aux1].trans_estado[0]=2;
				aux1=char_index(alfabeto,exp[operador-1])+1;
				tabla[3][aux1].trans_estado[0]=4;
				aux1=char_index(alfabeto,'?')+1;
				tabla[2][aux1].trans_estado[0]=3;
				ultimo_estado=4;
				ultimo=ultimo_estado;
			break;
		}
		aux=true;
	}
//Segúnda parte segúnda parte segúnda parte segúnda parte segúnda parte segúnda parte segúnda parte segúnda parte segúnda parte segúnda parte segúnda parte segúnda parte segúnda parte
	else{
		switch (exp[operador]){
			case '*':
				if(exp[operador-1]=='Ç'){
					nuevo_estado_tabla(1,tabla);
					aux1=char_index(alfabeto,'?')+1;
					tabla[1][aux1].trans_estado[0]=2;
					tabla[1][aux1].trans_estado[1]=ultimo_estado+1;
					tabla[ultimo_estado][aux1].trans_estado[0]=2;
					tabla[ultimo_estado][aux1].trans_estado[1]=ultimo_estado+1;
				}else if(exp[operador-1]==0){
					printf("%c\n",exp[operador-1]);
					exp_aux[0]='Ç';
					exp_aux[1]='*';
					thompson(exp_aux,tabla_aux2);
				}
			break;
			case '.':
				/*
				if(exp[operador-2]=='Ç'||exp[operador-1]=='Ç'){
					nuevo_estado_tabla(2);
					if(exp[operador-2]!='Ç'){
						aux1=char_index(alfabeto,exp[operador-2]);
					}
					else if(exp[operador-1]!='Ç'){
						aux1=char_index(alfabeto,exp[operador-1]);
					}
					tabla[1][aux1].trans_estado[0]=2;
				}
				aux1=char_index(alfabeto,'?');
				tabla[2][aux1].trans_estado[0]=3;*/
				/*if(exp[operador-2]=='Ç'||exp[operador-1]=='Ç'){
					if(exp[operador-2]!='Ç'){
						aux1=char_index(alfabeto,exp[operador-2])+1;
					}
					else if(exp[operador-1]!='Ç'){
						aux1=char_index(alfabeto,exp[operador-1])+1;
					}
					tabla[ultimo_estado+1][aux1].trans_estado[0]=ultimo_estado+2;
				}
				aux1=char_index(alfabeto,'?')+1;
				tabla[ultimo_estado][aux1].trans_estado[0]=ultimo_estado+1;
				ultimo_estado=ultimo_estado+2;*/
				aux1=char_index(alfabeto,'?')+1;//Actualización 22/11/2017 12:37 pm
				tabla[ultimo_estado][aux1].trans_estado[0]=ultimo_estado+1;
				ultimo_estado=ultimo_estado+1;
				if(exp[operador-2]=='Ç'||exp[operador-1]=='Ç'){
					if(exp[operador-2]!='Ç'){
						aux1=char_index(alfabeto,exp[operador-2])+1;
					}
					else if(exp[operador-1]!='Ç'){
						aux1=char_index(alfabeto,exp[operador-1])+1;
					}
					tabla[ultimo_estado][aux1].trans_estado[0]=ultimo_estado+1;
				}
			break;
			case '|':
				nuevo_estado_tabla(3,tabla);
				aux1=char_index(alfabeto,'?')+1;
				tabla[1][aux1].trans_estado[0]=2;
				tabla[1][aux1].trans_estado[1]=4;
				tabla[3][aux1].trans_estado[0]=ultimo_estado+1;
				tabla[ultimo_estado][aux1].trans_estado[0]=ultimo_estado+1;
				if(exp[operador-2]=='Ç'||exp[operador-1]=='Ç'){
					if(exp[operador-2]!='Ç'){
						aux1=char_index(alfabeto,exp[operador-2])+1;
					}
					else if(exp[operador-1]!='Ç'){
						aux1=char_index(alfabeto,exp[operador-1])+1;
					}
				}
				tabla[2][aux1].trans_estado[0]=3;
				/*
				nuevo_estado_tabla(4);
				if(exp[operador-2]=='Ç'||exp[operador-1]=='Ç'){
					if(exp[operador-2]!='Ç'){
						aux1=char_index(alfabeto,exp[operador-2])+1;
					}
					else if(exp[operador-1]!='Ç'){
						aux1=char_index(alfabeto,exp[operador-1])+1;
					}
					tabla[2][aux1].trans_estado[0]=3;
				}
				aux1=char_index(alfabeto,'?')+1;
				tabla[1][aux1].trans_estado[0]=2;
				tabla[1][aux1].trans_estado[1]=4;
				tabla[3][aux1].trans_estado[0]=ultimo_estado;//tabla[3][aux1].trans_estado[0]=ultimo_estado;
				tabla[4][aux1].trans_estado[0]=5;
				*/
			break;
		}
	}
}

void ver_tabla(int long_alfabeto,T_estado tabla[500][100]){
	long_alfabeto=long_alfabeto+3;
	int i,j;
	i=1;
	printf("\n");
	while (i<=est){
		j=1;
		printf("%i",i);
		if(estados_aceptacion[i]==1){
			printf("%c%c",254,186);
		}
		else{
			printf(" %c",186);
		}
		while (j<=long_alfabeto){
		//while (j<=99){
			if (tabla[i][j].trans_estado[0]!=0){
				intv_printf_tb(tabla[i][j].trans_estado);
			}
			else{
				printf("  ");
			}
			//printf ("%i , %i\n",i,j);
			j=j+1;
		}
		printf(" \n");
		i=i+1;
	}
}
void ver_tabla_total(T_estado tabla[500][100]){
	int i,j;
	i=1;
	printf("\n");
	while (i<=99){
		j=1;
		printf("%i",i);
		if(estados_aceptacion[i]==1){
			printf("%c%c",254,186);
		}
		else{
			printf(" %c",186);
		}
		while (j<=99){
		//while (j<=99){
			if (tabla[i][j].trans_estado[0]!=0){
				intv_printf_tb(tabla[i][j].trans_estado);
			}
			else{
				printf("  ");
			}
			//printf ("%i , %i\n",i,j);
			j=j+1;
		}
		printf(" \n");
		i=i+1;
	}
}

int f_opa(char inft[]){
char ext[max];
char aux[max];
int opa=0,i=0,sav=0,j=0,asav=0;
	int p=0;
	while(opa!=1){
		if((inft[i]=='|')||(inft[i]=='.')){
			if(i>=2){
				sav=i;
				opa=1;/*si fue operado tendra valor 1*/
			}
		}
		else if((inft[i]=='+')||(inft[i]=='*')){
			if(i>=1){
				sav=i;
				opa=1;/*si fue operado tendra valor 1*/
			}
		}
		i+=1;
	}
	if(opa==1){
		if(sav!=strlen(inft)-1&&((inft[sav]=='.')||(inft[sav]=='|'))){
			int p=0;
			for(int e=0;e<=sav;e++){
				thomson[p]=inft[e];
				p+=1;
			}
			thomson[p]='\0';
			aux[sav-2]=199;
			j=0;
			for(i=0;i<sav-2;i++){
				aux[j]=inft[i];
				j++;
			}
			j=sav-1;
			for(i=sav+1;i<=strlen(inft);i++){
				aux[j]=inft[i];
				j++;
			}
			strcpy(inft,aux);
		}
		else if(sav!=strlen(inft)-1&&((inft[sav]=='+')||(inft[sav]=='*'))){
			//printf("bien");
			int p;
			for(int e=0;e<=sav;e++){
				thomson[p]=inft[e];
				p+=1;
			}
			thomson[p]='\0';
			aux[sav-1]=199;
			j=0;
			for(i=0;i<sav-1;i++){
				aux[j]=inft[i];
				j++;
			}
			j=sav;
			for(i=sav+1;i<=strlen(inft);i++){
				aux[j]=inft[i];
				j++;
			}
			strcpy(inft,aux);
			strcpy(aux,ext);
		}
		else if(sav==strlen(inft)-1){
			int p=0;
			for(int e=0;e<=sav;e++){
				thomson[p]=inft[e];
				p+=1;
			}
			thomson[p]='\0';
			ymt_senpai=1;
		}
	}
}

void acep_e(int a[],int b, int es){
	int i=0;
	while (a[i]!=0){
		if(a[i]==es){
			estados_aceptacion[b]=1;
		}
		i=i+1;
	}
}

int estados_acep(int long_alfabeto){;
	int i,j,p,aq;
	for(p=0;p<=est;p++){
		if(estados_aceptacion[p]==1){
			aq=p;
			}
	i=1;
	while (i<=est){
		j=long_alfabeto;
		while (j<=long_alfabeto){
			if (tabla[i][j].trans_estado[0]!=0){
				acep_e(tabla[i][j].trans_estado,i,aq);
			}
			else{
			}
			j=j+1;
		}
		i=i+1;
	}
		}
}
//Yisus comenzó a trbajar aquí xdYisus comenzó a trbajar aquí xdYisus comenzó a trbajar aquí xdYisus comenzó a trbajar aquí xdYisus comenzó a trbajar aquí xdYisus comenzó a trbajar aquí xdYisus comenzó a trbajar aquí xdYisus comenzó a trbajar aquí xd

void int_union(int a[], int b[]){
	int i=0;
	int j;
	bool accion=true;
	while (i<int_index(b,0)){
		j=0;
		while (j<=int_index(a,0)){
			if (a[j]==b[i]){
				accion=false;
			}
			j=j+1;
		}
		if (accion==true){
			a[int_index(a,0)]=b[i];
		}
		accion=true;
		i=i+1;
	}
}

void intv_printf(int a[]){
	int i=0;
	while (a[i]!=0){
		printf("%i",a[i]);
		if(a[i+1]!=0){
			printf(",");
		}
		i=i+1;
	}
}

void reiniciar_lambda(){
	int i=1;
	while (i<=ultimo_estado){
		if (tabla[i][char_index(alfabeto,'?')+1].trans_estado[0]!=0){
			tabla[i][char_index(alfabeto,'?')+1].trans_estado[0]=0;
			tabla[i][char_index(alfabeto,'?')+1].trans_estado[1]=0;
		}
		i=i+1;
	}
}

void union_de_lambdas(){
	printf("\n");
	printf("Union de lambdas iniciada\n");
	int aux1;
	int a;
	int i,j,k;
	int l,no_iteraciones;
	aux1=char_index(alfabeto,'?')+1;//Las lambda siempre se encuentran en esta colúmna
	//intv_printf(tabla[1][aux1].trans_estado);//EL comentario anterior es cierto
	printf("Filas: %i Columnas: %i\n",ultimo_estado,aux1);
	tabla[1][1].trans_estado[0]=3;
	no_iteraciones=0;
	while (no_iteraciones<=100){//Yo digo que la cosa esta haga unas 27,000 iteraciones (O las que sean) para evitarnos pedos xd
		i=1;//Estado actual
		while (i<=ultimo_estado){
			a=int_index(tabla[i][aux1].trans_estado,0);//Número de elementos en un vector de transición lambda
			if (a>0){
				j=0;//Índice de la transición lambda actual
				while (j<a){
					k=1;//Colúmna actual
					while(k<aux1-1){
						l=tabla[i][aux1].trans_estado[j];
						int_union(tabla[i][k].trans_estado,tabla[l][k].trans_estado);
						k=k+1;
					}
					j=j+1;
				}
			}
			i=i+1;
		}
		no_iteraciones=no_iteraciones+1;
	}
	reiniciar_lambda();//Hace que lambda valga cero
}



//Yisus terminó de trabajar aquí xdYisus terminó de trabajar aquí xdYisus terminó de trabajar aquí xdYisus terminó de trabajar aquí xdYisus terminó de trabajar aquí xdYisus terminó de trabajar aquí xdYisus terminó de trabajar aquí xdYisus terminó de trabajar aquí xd
//Ahora viene lo chido xDxdXdAhora viene lo chido xDxdXdAhora viene lo chido xDxdXdAhora viene lo chido xDxdXdAhora viene lo chido xDxdXdAhora viene lo chido xDxdXd


void union_de_newestate(int a, int b){
	for(int i=1;i<=lett;i++){
		int_union(tabla[a][i].trans_estado,tabla[b][i].trans_estado);
	}
}

void new_estate(int a[],int b){
	char aiuda[max];
	char aux[max];
	char ext[max];	
	int i=0;
	if(contesta>1){
		for(int w=0;w<contesta;w++){
			if(esnew[w]==esnew[contesta]){
				strcpy(esnew[contesta],ext);
				contesta=contesta-1;
			}
	}
	}
	while (a[i]!=0){;
		itoa (a[i],aiuda,10);
		strcat(aux,aiuda);
		if(a[i+1]!=0){
			strcat(aux,",");
		}
		i++;
	}
	if(i>1){
		for(int j=0;j<strlen(aux);j++){
			aux[j]=aux[j+1];
		}
		aux[strlen(aux)]='\0';
		//printf("%s",aux);
		strcpy(esnew[contesta],aux);
		contesta+=1;
	}
	strcpy(aux,ext);
	strcpy(aiuda,ext);
}

void est_nuevo(int long_alfabeto){
	long_alfabeto=long_alfabeto+3;
	int i,j;
	i=1;
	//contesta=0;
	while (i<=est+contesta){
		j=1;
		while (j<=long_alfabeto){
			if (tabla[i][j].trans_estado[0]!=0){
				new_estate(tabla[i][j].trans_estado,i);
			}
			else{
			}
			j=j+1;
		}
		i=i+1;
	}
}

int mo_est(int long_alfabeto){
	long_alfabeto=long_alfabeto+3;
	int i,j;
	i=est+1;
	printf("\n");
	while (i<=est+contesta){
		j=1;
		printf("%s",esnew[i-est-1]);
		if(estados_aceptacion[i]==1){
			printf("%c%c",254,186);
		}
		else{
			printf(" %c",186);
		}
		while (j<=long_alfabeto){
			if (tabla[i][j].trans_estado[0]!=0){
				intv_printf_tb(tabla[i][j].trans_estado);
			}
			else{
				printf("  ");
			}
			j=j+1;
		}
		printf(" \n");
		i=i+1;
	}
}

int estados_acep_recharged(int a, int b){
	if(estados_aceptacion[b]==1){
		estados_aceptacion[a]=1;	
	}
}

int estados(){
	char cadena[max];
	char aux[max];
	char ext[max];
	int num,pcon;
	for(int i=0;i<=20;i++){
	}
	//printf("Estados a concatenar:");
	for(int w=est+1;w<=est+contesta;w++){
		pcon=w;
		//printf("%d",pcon);//--------------------------->pcon estado a concatenar
		//printf(" Concatenar con: ");
		for(int i=0;i<contesta;i++){
			int k=0;
			for(int j=0;j<strlen(esnew[i]);j++){
				if(esnew[i][j]!=','&&esnew[i][j]!='\0'){
					aux[k]=esnew[i][j];
					num = atoi(aux);//-------------------------->num estados a concatenar te sugiero llamarlo si num es mayor a 0 en el if de abajo
					k+=1;
				}
				else if(esnew[i][j]==','||esnew[i][j]=='\0'){
					k=0;
				}
				if(num>0){
					estados_acep_recharged(pcon,num);
					union_de_newestate(pcon,num);
					num=0;
				}
			}
		}
	}
}

void sumar_estados(int x,T_estado tabla[500][100]){//Añadir x estados al principio de la tabla
	int i,j,k,longitud;
	i=1;//Le suma x estados a cada transición
	while (i<=99){
		j=1;
		while (j<=99){
			if (tabla[i][j].trans_estado[0]!=0){
				longitud=int_index(tabla[i][j].trans_estado,100);//El estado 100 no existe, eso saca la longitud de cada vector tabla[i][j].trans_estado
				k=0;
				while (k<longitud){
					tabla[i][j].trans_estado[k]=tabla[i][j].trans_estado[k]+x;
					k=k+1;
				}
			}
			j=j+1;
		}
		i=i+1;
	}
}

int ultimo_estado_ocupado(T_estado tabla[500][100]){
	int aux1,i,j,k;
	aux1=char_index(alfabeto,'?')+1;
	bool seguir=true;
	i=1;
	while (seguir==true){
		j=1;
		while(seguir==true){
			k=0;
			while(seguir==true){
				if (tabla[i][j].trans_estado[k]!=0){
					seguir=true;
				}
				k=k+1;
			}
		}
		i=i+1;
	}
}

void pegar_matrices(int inicio,int final,T_estado tabla[500][100],T_estado tabla_aux2[500][100]){
	int i,j,k,aux1;
	i=inicio+1;
	aux1=char_index(alfabeto,'?')+1;
	while (i<=final){
		j=1;
		while (j<=aux1){
			k=0;
			while (tabla_aux2[i][j].trans_estado[k]!=0){
				tabla[i][j].trans_estado[k]=tabla_aux2[i][j].trans_estado[k];
				k=k+1;
			}
			j=j+1;
		}
		i=i+1;
	}
}

void reiniciar(int i,int ultimo_estado,T_estado tabla[500][100]){
	int j,k,aux1;
	aux1=char_index(alfabeto,'?')+1;
	while (i<=ultimo_estado){
		j=1;
		while (j<=aux1){
			k=0;
			while (tabla[i][j].trans_estado[k]!=0){
				tabla[i][j].trans_estado[k]=0;
				k=k+1;
			}
			j=j+1;
		}
		i=i+1;
	}
}

void unir_matrices(int i,T_estado tabla[500][100],T_estado tabla_aux2[500][100],char op){
	int j,k,aux1;
	/*printf("El primer estado que se va a pegar es:  %i \n",i);
	printf("La operación sera: %c\n",op);*/
	aux1=char_index(alfabeto,'?')+1;
	if (op='.'){
		tabla[i][aux1].trans_estado[0]=5;
		nuevo_estado_tabla(i,tabla_aux2);
		/*printf("Tabla sumada \n");
		ver_tabla(longitud_alfabeto,tabla_aux2);
		printf("Tabla sumada \n");*/
		pegar_matrices(i,ultimo_estado,tabla,tabla_aux2);
		reiniciar(1,ultimo_estado,tabla_aux2);
	}
	if (op='|'){
		nuevo_estado_tabla(1,tabla);
		nuevo_estado_tabla(i,tabla_aux2);
		tabla[1][aux1].trans_estado[0]=2;
		tabla[1][aux1].trans_estado[1]=i+1;
		tabla[i+1][aux1].trans_estado[0]=ultimo_estado+1;
		tabla[ultimo_estado][aux1].trans_estado[0]=ultimo_estado+1;
		reiniciar(1,ultimo_estado,tabla_aux2);
	}
//Este ha sido el último proceso... Ya no quiero we! Dx
}
//La tabla de thompson se inicia con esta funciónLa tabla de thompson se inicia con esta funciónLa tabla de thompson se inicia con esta funciónLa tabla de thompson se inicia con esta función
int tabla_thomson(){
	int tam,ultimo_estado_2,pos_operador,op,deja_pasar_una_iteracion;
	char auxiliar[max];
	char aiuda=199;
	char exp_aux[100];
	ll_tablas();
	tam=strlen(let);
	let[tam]=' ';
	tam=strlen(let);
	let[tam]='?';
	strcpy(alfabeto,let);//Supongo que tienes una función para sacar el alfabeto automáticamente xd
	longitud_alfabeto=char_index(alfabeto,'?')+1;
	detalles(inf);//dara detalles como ancho y la expresion en si
	strcpy(inft,inf);//copiara la expresion infija a otra para no destruir nada
	while(ymt_senpai!=1){
		f_opa(inf);//va operando de 2 en 2
		if(strlen(thomson)<=3){	
			for(int i=0;i<=strlen(thomson);i++){
				auxiliar[i]=thomson[i+1];
			}
			for(int i=0;i<=strlen(thomson)-1;i++){
				if(thomson[i]==auxiliar[i]&&thomson[i]==aiuda){
					thomson[i+1]=200;
				}
			}
			//printf("Buena %s\n",thomson);
			op=2;
			if (thomson[2]=='*'){
				op=3;
				exp_aux[0]='Ç';
				exp_aux[1]='*';
				thompson(exp_aux,tabla_aux2);
				/*printf("Tabla auxiliar aparece con kleene\n");
				ver_tabla(longitud_alfabeto,tabla_aux2);
				printf("Tabla auxiliar se va con kleene\n");*/
				deja_pasar_una_iteracion=1;
			}
			if (pegar_tabla==false){
				thompson(thomson,tabla);
			}
			if (deja_pasar_una_iteracion==0){
				if(pegar_tabla==true){
					unir_matrices(ultimo_estado_2,tabla,tabla_aux2,thomson[op]);
					pegar_tabla=false;
				}
			}
			else{
				deja_pasar_una_iteracion=deja_pasar_una_iteracion-1;
			}
		}
		else if(strlen(thomson)==4){
			//printf("CON QUE SI CABRON! >:v: ");
			printf("Dentro del ciclo:\n");
			for(int i=1;i<=strlen(thomson);i++){
				t2[i-1]=thomson[i];
			}
			//printf("Mala %s\n",t2);
			aux=false;
			thompson(t2,tabla_aux2);
			pegar_tabla=true;
			//sumar_estados(ultimo_estado,tabla_aux2);
			ultimo_estado_2=ultimo_estado-1;//ultimo_estado_2=ultimo_estado;//22/11/2017 12:22 pm
			/*printf("Comienza tabla auxiliar\n");
			ver_tabla(longitud_alfabeto,tabla_aux2);
			printf("Termina_tabla_auxiliar\n");*/
			//unir_matrices(ultimo_estado_2,tabla,tabla_aux2);
//Termina la ejecucion de la tabla de thompsonTermina la ejecucion de la tabla de thompsonTermina la ejecucion de la tabla de thompsonTermina la ejecucion de la tabla de thompson

		}
	}
	exec=0;
	for(int i=0;i<=est;i++){
		estados_acep(longitud_alfabeto);
	}
	union_de_lambdas();//.................................................................................................................. Tenga cuidado
	exec=1;
	for(int w=0;w<=700;w++){
		if(contesta>=1){
			estados();
		}
	}
	if(est<est+contesta){
		printf("NUEVOS ESTADOS");
		mo_est(longitud_alfabeto);
	}
}
void gt3(T_estado tabla[500][100],char alfabeto[],int estados_aceptacion[]){
	int i,j;
	i=0;
	while(i<=est){
		j=0;
		while(j<strlen(alfabeto)){
			if(tabla[i][j+1].trans_estado[0]!=0){
				printf("S%i->%cS%i\n",i,alfabeto[j],tabla[i][j+1].trans_estado[0]);
				if(int_index(estados_aceptacion,i)!=int_index(estados_aceptacion,-1)){
					printf("S%i->%c\n",i,alfabeto[j]);
				}
			}
			j=j+1;
		}
		i=i+1;
	}
}
void analizador_lexico(T_estado tabla[500][100],char alfabeto[],int estados_aceptacion[]){
	int estado;
	int i=0;
	int caso;
	char cadena[100];
	printf("Ingrese su cadena\n");
	scanf("%s",&cadena);
	strcat(cadena,"$");
	estado=1;
	while(i<strlen(cadena)-1){
		estado=tabla[estado][char_index(alfabeto,cadena[i])+1].trans_estado[0];
		i=i+1;
	}
	if(estado!=0&&estado==estados_aceptacion[int_index(estados_aceptacion,estado)]){
		printf("Cadena aceptada\n");
	}
	else{
		printf("Cadena rechazada\n");
	}
	system("Pause");
	system("cls");
	printf("Desea ingresar otra cadena?\n");
	printf("1 Si\n");
	printf("2 Salir\n");
	scanf("%i",&caso);
	if(caso==1){
		system("cls");
		gt3(tabla,alfabeto,estados_aceptacion);
		analizador_lexico(tabla,alfabeto,estados_aceptacion);
	}
}
main(){
	int b,v,vv,vvv;
	stack<char> pinf;
	printf("Hola usuario\n");
	printf("REGLAS:\n1: NO UTILIZAR k \n2: SIMBOLOS: KLEENE: * CONCATENACION: . KLEENE CON POSITIVOS: + O: | \n");
	printf("#3:POR AHORA CADA VEZ AL QUERER APLICAR KLEENE A UN ELEMENTO(S)\nCERRAR CON PARENDENTESIS DESDE DONDE EMPIEZA LOS ELEMENTO(S) DESEADO(S) \n");
	printf("#4:IGUAL QUE LA 3 PERO CON | CON VARIOS ELEMENTOS 5: IGUAL QUE LA 3 PERO CON . CON VARIOS ELEMENTOS");
	printf("\nDame tu expresion:\t");
	gets(inf);
	do{
		if(!pinf.empty()){
			while(!pinf.empty()){
				pinf.pop();
			}
		}
	}while(!pinf.empty());
	vv=valH();
	vvv=valG();
	v=valD();
	b=valS(pinf,inf);
	if(b==1&&v!=1&&vvv!=1&&vv!=1){
		printf("VALIDA\n");
		trans1();/*Cambia todos los + por una concatenacion de la expresion con otra a la kleene*/
		qtrans();/*Devuelve las columnas y filas a ocupar de la tabla de thomson printf Filas:cont, Columnas: d, Numero de letras: lett, Numero de estados: est, Letras empleadas: let*/
		/*printf("Conversion:");*/
		trans2();/*Convierte cada * a ^k*/
		/*printf("%s",inf);*/
		printf("Infija a Posfija:");
		trans(inf);/*Devuelve la posfija sin modificar*/
		/*printf("%s",inf);*/
		trans3();/*Reconvierte cada k^ a **/
		/*printf("\nULTIMA CONVERSION:\n");*/
		//printf("%s",inf);
		estados_aceptacion[est]=1;
		tabla_thomson();
	}
	else{
		printf("INVALIDA");
	}
	/*
	printf("Esta es la verdadera tabla\n");
	ver_tabla(longitud_alfabeto,tabla);
	*/
	gt3(tabla,alfabeto,estados_aceptacion);
	analizador_lexico(tabla,alfabeto,estados_aceptacion);
}
