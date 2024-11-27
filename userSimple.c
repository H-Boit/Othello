#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include "userNetwork.h" 
#include "fonctions.h"
#define BLACK 1 

int main(int argc,char *argv[]) 
{
	game *g;
	int move; 

	if ((g=allocateGameOthello()) == NULL ) { return(EXIT_FAILURE); }

	if (argc > 3 ) { 
		g->userId=atoi(argv[3]); 
		g->address=argv[2]; 
	}
	else { fprintf(stderr,"usage : %s <userPasswd> <ip ad> <userId>\n",argv[0]); exit(-1); }

	g->port=8080; //par exemple

	if (registerGameOthello(g,argv[1]) < 0 ) { exit(-1); }	// test de l'authentification auprès du serveur 

	if (startGameOthello(g) < 0 ) { // cet appel est bloquant en attendant un adversaire 
		fprintf(stderr,"error Starting Game\n"); 
		return (EXIT_FAILURE); 
	}
	printf("I am player %s\n",(g->myColor==BLACK)?"Black":"White"); 
	// Initialisation du plateau
    int plateau[Lenght_tab][Lenght_tab];

    // Initialisation du plateau et affichage
    Init_tab(plateau);
    Print_tab(plateau);

	// debut de partie
	
	while (g->state == PLAYING && !feof(stdin)) {
	 	if (g->myColor != g->currentPlayer) { // attente du coup de l'adversaire 
			if ((move=waitMoveOthello(g)) == 0 ) {
				printf("Game status %d: \t",g->state); 
				if (g->state == PLAYING) { 
					printf("Received move from server %d (x=%d,y=%d)\n",g->move,g->move%8,g->move/8); 
					if(g->move==64){}
					else{
						
						int Possible_vect[8][2]= {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};
						
						Is_possible(plateau, g->move/8, g->move%8, !(g->currentPlayer), Possible_vect);
						swap(plateau, g->move/8, g->move%8, !(g->currentPlayer), Possible_vect);
						Print_tab(plateau);
					}
					
				}
			}
		}
	 	else { 		
			g->move=65; // si scanf correct cette valeur est modifiée, sinon cela terminera la partie. 
			// recuperation du coup sur stdin 
			printf("Enter your move:\n");
			int ligne, colonne;
			printf("Ligne : ");
			scanf("%d",&ligne);
			printf("Colonne : ");
			scanf("%d",&colonne);
			(g->move) = ligne*8 + colonne; 
			

			printf("playing move %d (x=%d,y=%d)\n",g->move,g->move%8,g->move/8);
			
			int Possible_vect[8][2]= {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};
			
			Is_possible(plateau, g->move/8, g->move%8, !(g->currentPlayer), Possible_vect);
			swap(plateau, g->move/8, g->move%8, !(g->currentPlayer), Possible_vect);


			doMoveOthello(g);	// envoie du coup à l'adversaire 
			Print_tab(plateau);
	   	}
		g->currentPlayer=!g->currentPlayer; 
	} 
	// fin de partie 
	printf("Final game status = %d\n",g->state); 
	freeGameOthello(g);
	return 0; 
}