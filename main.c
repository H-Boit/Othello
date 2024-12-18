#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "fonctions.h"

int main(){

    // Initialisation du plateau
    int plateau[Lenght_tab][Lenght_tab];

    // Initialisation du plateau et affichage
    Init_tab(plateau);
    Print_tab(plateau);

    // Boucle de jeux

    char tab_player[2] = {'B', 'W'};
    int Indice_tab_player = 0;

    int end_game = 0, nb_move = 0;

    bool boucle = true;
    while(boucle){
        time_t begin = time( NULL );
        printf("C'est au tour de %c\n", tab_player[Indice_tab_player]);

        int ligne;
        int column;

        int Possible_vect[8][2] = {{0,0}};
        bool played = false;

        int tmp;
        if (Indice_tab_player == 0) {
            tmp = appel_IA_max_pts_rec(plateau, Indice_tab_player, Indice_tab_player);
        }
        else {tmp = appel_IA_max_pts_rec_elag(plateau, Indice_tab_player, Indice_tab_player);}
        
        //tmp = appel_IA_max_pts_rec_var(plateau, Indice_tab_player, Indice_tab_player, nb_move);

        
        if (end_game == 2){
            int WW = Who_win(plateau);
            if (WW != -1) printf("Le joueur %c a gagné ! \n",tab_player[WW]);
            else printf("Egalité \n");
            boucle = false;
        }
        else if (tmp ==64 ){
            played = 1;
            end_game += 1;
        }
        else {  
            column = tmp % Lenght_tab;
            ligne = tmp / Lenght_tab;

            printf("ligne %d, colone %d\n",ligne,column);

            played = Is_possible(plateau, ligne, column, Indice_tab_player, Possible_vect);

            if (played){
                swap(plateau, ligne, column, Indice_tab_player, Possible_vect);
            }
            else printf("Coup invalide \n");

            Print_tab(plateau);
            end_game = 0;
        }
        if (played) Indice_tab_player = (Indice_tab_player + 1)%2;
        nb_move++;

        time_t end = time( NULL);
        unsigned long secondes = (unsigned long) difftime( end, begin );
        printf( "Finished in %ld sec\n", secondes ); 
    }
    return 0;
}
