#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

    int end_game = 0;

    bool boucle = true;
    while(boucle){
        
        printf("C'est au tour de %c\n", tab_player[Indice_tab_player]);

        int ligne;
        int column;

        int Possible_vect[8][2];
        bool played = false;

        int tmp = appel_IA_max_pts_rec(plateau, Indice_tab_player, Indice_tab_player);
        //int tmp = IA_max_pts(plateau,Indice_tab_player);

        // 
        //printf("%d\n",tmp);
        //

        if (end_game == 2){
            int WW = Who_win(plateau);
            if (WW != -1) printf("Le joueur %c a gagné ! \n",tab_player[WW]);
            else printf("Egalié \n");
            boucle = false;
        }
        else if (tmp ==64 ){
            played = 1;
            end_game += 1;
        }
        else {
            /*
            printf("\n");
            printf("C'est au tour des pions %c\n", tab_player[Indice_tab_player]);
            printf("Rentrer ligne : ");
            scanf("%d", &ligne); // Rentrer ligne : 
            printf("Rentrer colone : ");
            scanf("%d", &column); // Rentrer colone : 
            printf("\n");
            */
            

            column = tmp % Lenght_tab;
            ligne = tmp / Lenght_tab;

            printf("ligne %d, colone %d\n",ligne,column);

            played = Is_possible(plateau, ligne, column, Indice_tab_player, Possible_vect);

            //
            printf("%d\n", played);
            //

            if (played){
                swap(plateau, ligne, column, Indice_tab_player, Possible_vect);
            }
            else printf("Coup invalide \n");

            Print_tab(plateau);
            end_game = 0;
        }
        if (played) Indice_tab_player = (Indice_tab_player + 1)%2;

    }
    return 0;
}
