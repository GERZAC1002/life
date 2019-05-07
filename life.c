#include <stdio.h>
#include <stdlib.h>

#define SPALTE 80
#define REIHE 25

int main(int argc, char *argv[]){
	int generation = 0;
	int anzahl = 0;
	int ueber = 0;
	char ch;
	char nachbarn = 0;
	char zufall;
	char feld[SPALTE][REIHE];
	char feld2[SPALTE][REIHE];
	char feld3[SPALTE][REIHE];
	char geburt_ueberleb[2][8] = {
		{3,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
		{2,3,NULL,NULL,NULL,NULL,NULL,NULL}
	};
	char anfang[5][5] = {
		{0,0,0,0,0},
		{0,0,1,1,1},
		{0,0,1,0,1},
		{0,0,1,0,1},
		{0,0,0,0,0}
	};

	srand(time(NULL));

	for(int x = 0; x <= SPALTE; x++){
		for(int y = 0; y <= REIHE; y++){
			zufall = rand()%10;
			if(zufall == 1){
				feld[x][y] = 1;
			}else{	
				feld[x][y]=0;
			}
			feld2[x][y]=0;
		}
	}

	while(ch != 'q'){
		for(int x = 0; x <= SPALTE-1; x++){
			for(int y = 0; y <= REIHE-1;y++){
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

		for(int x = 0; x <= SPALTE-1; x++){
			for(int y = 0; y <= REIHE-1; y++){
				feld[x][y] = feld2[x][y];
				feld2[x][y] = feld3[x][y];
			}
		}

		generation = generation +1;

		for(int y = 0; y <= REIHE;y++){
                	for(int x = 0; x <= SPALTE; x++){
                	        if(feld[x][y] == 0){
        	                        printf(" ");
	                        }else{
                	                printf("*");
        	                }
	                }
                	printf("\n");
        	}
		printf("\nGeneration: %i\n============================================================================================\n",generation);
		ch = getchar();
	}

	return 0;
}
