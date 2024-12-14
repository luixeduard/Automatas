#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>

int turing(){
	system("turing.lnk");
}

int pilas(){
	system("pila.lnk");
}

int Validar(){
	system("Verificacion.lnk");
}

int Automatas(){
	system("Automata_FD.lnk");
}

int GramaticasT3(){
	system("Gramaticas_T3.lnk");
}

int GramaticasT2(){
	system("Gramaticas_T2.lnk");
}

int acerca(){
	system("cls");
	printf("Programa creado por:\nLuis Eduardo Salas Hernandez\n");
	printf("Creado desde el 29/11/2017");
}

main(){
	char comando;
	bool salir=false;
	bool s=false;
	while(!salir){
	printf("*|Ayuda (F1)|Acerca de(F2)|Salir (Esc)|\n");
	printf("\t\t\t\tBienvenido Usuario\n");
	printf("%cQu%c desea hacer?\n",168,130);
	printf("1. Automatas Finitos Deterministas\n");
	printf("2. Gramaticas\n");
	printf("3. Automatas de Pila\n");
	printf("4. Maquinas de turing\n");
	comando=getch();
	switch(comando){
		case 49:
			while(!salir){
				printf("Salir (Esc)\n");
				printf("1. Automatas\n");
				printf("2. Verificar\n");
				char cc=getch();
				switch(cc){
					case 49:
						Automatas();
						break;
					case 50:
						Validar();
						break;
					case 27:
    					salir=true;
						break;
					default:	
    					if(salir!=0){
							printf("Opci%cn no valida\n",162);
							system("pause");
							system("cls");
						}
								system("cls");
							break;
					}
				}
			system("cls");
			break;
		case 50:
			while(!salir){
				printf("Salir (Esc)\n");
				printf("1. Gramaticas Tipo 3\n");
				printf("2. Gramaticas Tipo 2\n");
				printf("3. Verificar\n");
				char cc=getch();
				switch(cc){
					case 49:
						GramaticasT3();
						break;
					case 50:
						GramaticasT2();
						break;
					case 51:
						Validar();
						break;
					case 27:
    					salir=true;
						break;
					default:	
    					if(cc!=0){
							printf("Opci%cn no valida\n",162);
							system("pause");
							system("cls");
						}
								system("cls");
							break;
					}
				}
		    system("cls");
		    break;
		case 51:
			pilas();
    		system("cls");
    		break;
    	case 52:
    		turing();
    		system("cls");
    		break;
    	case 59:
    		//aiuda();
    		system("cls");
    		break;
    	case 60:
    		acerca();
    		system("cls");
    		break;
    	case 27:
    		salir=true;
			break;
    	default:
    		if(comando!=0){
				printf("Opci%cn no valida\n",162);
				system("pause");
				system("cls");
			}
			system("cls");
			break;
	}
}
}
