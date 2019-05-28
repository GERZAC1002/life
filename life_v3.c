#include <stdio.h>
#include <stdlib.h>

#define ZUFALL 5
#define AKTUALISIERE 50000

int reihe = 1;
int spalte = 1;

void linie(){
	for(int i = 0; i < spalte;i++){
		printf("=");
	}
	printf("\n");
}

int main(int argc, char *argv[]){
	if(argc < 2){
		printf("Eingabe Spalten(Terminalbreite):\n");
		scanf("%d",&spalte);
		printf("Eingabe Reihen(Terminallänge):\n");
		scanf("%d",&reihe);
	}else{
		spalte = atoi(argv[1]);
		reihe = atoi(argv[2]);
	}
	int anzahl = 0;
	int letzte_anzahl = 0;
	int ident = 0;
	int generation = 0;
	int ueber = 0;
	int c=0;
	char nachbarn = 0;
	char **feld;
	char **feld2;
	feld = malloc(spalte*sizeof(char *));
	feld2 = malloc(spalte*sizeof(char *));
	if(feld == NULL || feld2 == NULL){
		printf("Nicht genügend Speicher frei!\n");
	}
	for(int i=0; i<= spalte;i++){
		feld[i]=malloc(reihe*sizeof(char));
		feld2[i]=malloc(reihe*sizeof(char));
		if(feld[i] == NULL || feld2[i] == NULL){
			printf("Nicht genügend Speicher!\n");
			return EXIT_FAILURE;
		}
	}
	/*char feld[spalte][reihe];
	char feld2[spalte][reihe];*/
	char geburt_ueberleb[2][8] = {//Regeln für Geburt und Überleben Standard:3 und 2,3
		{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
		{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
	};

	FILE *regel;
	regel = fopen("rule.life", "r");
	if(regel){
		for(int i = 0; i <= 1; i++){
			int u =0;
			while((c=getc(regel))!='\n'){
				geburt_ueberleb[i][u] = c -48;
				printf("%c\n",c);
				u = u+1;
			}
		}
	}

	char zufall = 0;
	srand(time(NULL));

	for(int x = 0; x <= spalte; x++){
		for(int y = 0; y <= reihe; y++){
			zufall = rand()%ZUFALL;
			if(zufall == 1){
				feld[x][y] = 1;
			}else{
				feld[x][y]=0;
			}
		}
	}

	zufall = 0;
	srand(time(NULL));

	for(int x = 0; x <= spalte; x++){
		for(int y = 0; y <= reihe; y++){
				feld[x][y] = 0;
		}
	}

	while("Game of Life"){
		for(int x = 0; x <= spalte-1; x++){
			for(int y = 0; y <= reihe-1;y++){
				if(x != 0){
					if(feld[x-1][y] == 1){
						nachbarn = nachbarn +1;
					}
					if(feld[x-1][y-1] == 1 && y!=0){
						nachbarn = nachbarn +1;
					}
					if(feld[x-1][y+1] == 1 && y!=reihe-1){
						nachbarn = nachbarn +1;
					}
				}
				if(feld[x][y-1] == 1 && y!=0){
					nachbarn = nachbarn +1;
				}
				if(feld[x][y+1] == 1 && y != reihe-1){
					nachbarn = nachbarn +1;
				}
				if(x != spalte-1){
					if(feld[x+1][y-1] == 1 && y != 0){
						nachbarn = nachbarn +1;
					}
					if(feld[x+1][y] == 1){
						nachbarn = nachbarn +1;
					}
					if(feld[x+1][y+1] == 1 && y != reihe-1){
						nachbarn = nachbarn +1;
					}
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
		
		for(int x = 0; x <= spalte-1; x++){
			for(int y = 0; y <= reihe-1; y++){
				feld[x][y] = feld2[x][y];
			}
		}

		for(int x = 0; x <= spalte; x++){
			for(int y = 0; y <= reihe; y++){
					feld2[x][y] = 0;
			}
		}

		generation = generation +1;
		system("clear");

		for(int y = 0; y <= reihe-1;y++){
			for(int x = 0; x <= spalte-1; x++){
				if(feld[x][y] == 0){
					printf(" ");
				}else{
					printf("*");
					anzahl = anzahl +1;
				}
			}
			printf("\n");
		}
		printf("\nGeneration: %i\tAnzahl: %i\n",generation,anzahl);
		if(letzte_anzahl == anzahl){
			ident = ident +1;
		}else{
			ident = 0;
		}

		if(anzahl == 0 || ident == 10){
				for(int x = 0; x <= spalte; x++){
					for(int y = 0; y <= reihe; y++){
						zufall = rand()%ZUFALL;
						if(zufall == 1){
							feld[x][y] = 1;
						}else{	
							feld[x][y]=0;
						}
					}
				}
				for(int x = 0; x <= spalte; x++){
					for(int y = 0; y <= reihe; y++){
						feld2[x][y] = 0;
					}
				}
				generation = 0;
				ident = 0;
		}
		letzte_anzahl = anzahl;
		anzahl = 0;
		linie();
		usleep(AKTUALISIERE);
	}

	return 0;
}
