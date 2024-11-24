#include <stdio.h> 
#include <stdlib.h> 
#include <stdint.h> 
#include <errno.h>
#include <stdbool.h>
#include "fonctions.h"

#define N 8 
#define BLACK 1 
#define WHITE 0 
#define EMPTY 2 

//#define CONVENTIONOK 

#ifdef CONVENTIONOK 
typedef int8_t monType ;
#else 
typedef int32_t monType;
#define MYBLACK 0
#define MYWHITE 1
#define MYEMPTY -1
#endif 


// Assume we have a function that modifies our board 
int faireCoupOthello(monType tableau[N][N],int8_t coup,int8_t couleur) {
	int ligne = coup /8;
	int column = coup %8;
	
	int Possible_vect[8][2]= {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};
	
	int played = Is_possible(tableau, ligne, column, couleur, Possible_vect);

	if (played > 0) {
		swap(tableau, ligne, column, couleur, Possible_vect);
	}
	for(int i =0; i< 8 ;i++){
		printf("(%d , %d)  ",Possible_vect[i][0],Possible_vect[i][1]);
	}
	return 0;
}


void afficheTableau(monType tableau[N][N]) 
{
	for (int i=0;i<N;i++) {
		for (int j=0;j<N;j++) {
			printf("%c ",tableau[i][j]==2?'.':'0'+tableau[i][j]); 
		} 
		printf("\n"); 
	}
	printf("\n\n\n"); 

}

int dansTableau(int i, int j) 
{
	return ((i>=0) && (i<N) && (j>=0) && (j<N)); 
}

/*
int faireCoupOthello(monType tableau[N][N],int8_t coup,int8_t couleur) 
{
	int dirs[8][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}}; 
	int retournes=0; 
	int i,j; 
	// on recupere la ligne et la colonne de coup dans i et j 
	i=coup/N; 
	j=coup%N; 

	if (dansTableau(i,j)) {
	// pour toutes les directions
		for (int d=0;d<8;d++) {
			int x,y,v=0; 
			x=i+dirs[d][0]; 
			y=j+dirs[d][1]; 
	// on avance tant qu'on est dans le tableau et que le pion est adverse 
			while (dansTableau(x,y) && (tableau[x][y]==(!couleur))) {
				x+=dirs[d][0]; 
				y+=dirs[d][1]; 
				v++; 
			}
	// si on est toujours dans le tableau et qu'on a avancé alors la piece doit ausi etre de notre couleur 
			if (dansTableau(x,y) && (v!=0) && (tableau[x][y]==couleur)) {
				retournes+=v; 
				for (int w=0;w<=v;w++) {
					tableau[i+w*dirs[d][0]][j+w*dirs[d][1]]=couleur; 
				}
			}
				
		}
	}
	return retournes; 
}
*/
int lireCoup(int8_t *coup,int8_t *couleur, FILE *savedGames) 
{
	int res=0; 
	res=fread(coup,sizeof(int8_t),1,savedGames); 
	if (res) res=fread(couleur,sizeof(int8_t),1,savedGames); 
#ifndef CONVENTIONOK 
	*couleur=(*couleur==BLACK)?MYBLACK:MYWHITE; 
#endif 
	return res; 
}

int lireTableau(monType tableau[N][N], FILE *savedGames) 
{
	int res; 
#ifdef CONVENTIONOK 
	res=fread(tableau,sizeof(int8_t),64,savedGames); 
#else 
	int8_t temp[N][N]; 
	res=fread(temp,sizeof(int8_t),64,savedGames); 
	for (int i=0;i<N*N;i++) {
		tableau[i/8][i%8]=((temp[i/8][i%8]==BLACK)?MYBLACK:(temp[i/8][i%8]==WHITE)?MYWHITE:MYEMPTY); 
	}
#endif 
	return res; 
}
int compareTableau(monType tableau[N][N],monType reference[N][N]) 
{
	int erreur=0; 
	for (int i=0;i<64;i++) { 
		erreur+=(tableau[i/8][i%8]!=reference[i/8][i%8]); 
	}
	return erreur; 
}


int main(int argc, char *argv[])
{
	// tableau before and after (ie. expected after) 
	monType monTableau[N][N]; // 1 Black, 0 white , 2 empty 
	monType after[N][N]; 
	int8_t  c,p; // coup de 0 à 63 pour un coup valide, 64 pour PASS. 
		     // p player (1 Black, 0 white) 
	int errors=0,nberrors=0; 
	int nbtest=0; 
	FILE *fi; 

	if (argc<2) { printf("%s <file>\n",argv[0]); exit (1); } 
	if ((fi=fopen(argv[1],"r"))!=NULL) {
		while (lireTableau(monTableau,fi)) {
			nbtest++; 
			printf("tableau initial\n"); 
			afficheTableau(monTableau); 
			lireCoup(&c,&p,fi); 
			lireTableau(after,fi); 
			faireCoupOthello(monTableau,c,p);
			printf("coup de %d en %d %d\n",p,c/8,c%8); 
			printf("tableau ref\n"); 
			afficheTableau(after); 
			afficheTableau(monTableau); 
			if ((errors=compareTableau(monTableau,after))) { 
				printf("%d error(s) in test %d\n",errors,nbtest);
		       		nberrors+=errors;
			}
		}
	fclose(fi); 
	} else {
		perror("cannot open file"); 
	}
	printf("J'ai détecté %d Erreur(s)\n",nberrors); 
}