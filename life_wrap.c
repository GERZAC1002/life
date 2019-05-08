#include <stdio.h>
#include <stdlib.h>

#define ZUFALL 10
#define AKTUALISIERE 50000

int reihe = 30;
int spalte = 120;

void linie(){
	for(int i = 0; i < spalte;i++){
		printf("=");
	}
	printf("\n");
}

void fuellFeld(char feld[spalte][reihe], char zufall_an){
	char zufall = 0;
	srand(time(NULL));

	for(int x = 0; x <= spalte; x++){
		for(int y = 0; y <= reihe; y++){
			if(zufall_an == 1){
				zufall = rand()%ZUFALL;
				if(zufall == 1){
					feld[x][y] = 1;
				}else{	
					feld[x][y]=0;
				}
			}else{
				feld[x][y] = 0;
			}
		}
	}
}

void kopiereFeld(char feld1[spalte][reihe], char feld2[spalte][reihe]){
	for(int x = 0; x <= spalte-1; x++){
		for(int y = 0; y <= reihe-1; y++){
			feld1[x][y] = feld2[x][y];
		}
	}
}

int main(int argc, char *argv[]){
	printf("Eingabe Spalten(Terminalbreite):\n");
	scanf("%d",&spalte);
	printf("Eingabe Reihen(Terminallänge):\n");
	scanf("%d",&reihe);
	int generation = 0;
	int ueber = 0;
	char nachbarn = 0;
	char feld[spalte][reihe];
	char feld2[spalte][reihe];
	char geburt_ueberleb[2][8] = {//Regeln für Geburt und Überleben Standard:3 und 2,3
		{3,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
		{2,3,NULL,NULL,NULL,NULL,NULL,NULL}
	};

	fuellFeld(&feld,1);
	fuellFeld(&feld2,0);

	while("Game of Life"){
		for(int x = 0; x <= spalte-1; x++){
			for(int y = 0; y <= reihe-1;y++){
				if(feld[x-1][y] == 1){
					nachbarn = nachbarn +1;
				}
				if(feld[x-1][y-1] == 1){
					nachbarn = nachbarn +1;
				}
				if(feld[x-1][y+1] == 1){
					nachbarn = nachbarn +1;
				}
				if(feld[x][y-1] == 1){
					nachbarn = nachbarn +1;
				}
				if(feld[x][y+1] == 1){
					nachbarn = nachbarn +1;
				}
				if(feld[x+1][y-1] == 1){
					nachbarn = nachbarn +1;
				}
				if(feld[x+1][y] == 1){
					nachbarn = nachbarn +1;
				}
				if(feld[x+1][y+1] == 1){
					nachbarn = nachbarn +1;
				}
				if(feld[x][y] == 0){
					for(int i=0;geburt_ueberleb[0][i]!=NULL;i++){
						if(nachbarn == geburt_ueberleb[0][i]){
							ueber = ueber +1;
						}
					}
				}else{
					for(int i = 0;geburt_ueberleb[1][i]!=NULL;i++){
						if(nachbarn == geburt_ueberleb[1][i]){
							ueber = ueber +1;
						}
					}
				}
				if(ueber > 0){
					feld2[x][y] = 1;
				}else{
					feld2[x][y] = 0;
				}

				ueber = 0;
				nachbarn = 0;
			}
		}
		printf("\n");

		kopiereFeld(&feld,&feld2);
		fuellFeld(&feld2,0);

		generation = generation +1;
		system("clear");

		for(int y = 0; y <= reihe-1;y++){
			for(int x = 0; x <= spalte-1; x++){
				if(feld[x][y] == 0){
					printf(" ");
				}else{
					printf("*");
				}
			}
			printf("\n");
		}
		printf("\nGeneration: %i\n",generation);
		linie();
		usleep(AKTUALISIERE);
	}

	return 0;
}
