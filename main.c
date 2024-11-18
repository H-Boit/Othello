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

    char tab_player[2] = {'N', 'B'};
    int Indice_tab_player = 0;

    int end_game = 0;

    bool boucle = true;
    while(boucle){
        
        int ligne;
        int column;

        int Possible_vect[8][2];
        bool played = false;

        if (end_game == 2){
            int WW = Who_win(plateau);
            if (WW != -1) printf("Le joueur %c a gagné ! \n",tab_player[WW]);
            else printf("Egalié \n");
            boucle = false;
        }
        else if (Tab_is_empty(plateau, Indice_tab_player, Possible_vect)){
            played = true;
            end_game += 1;
        }
        else {
            
            printf("\n");
            printf("C'est au tour des pions %c\n", tab_player[Indice_tab_player]);
            printf("Rentrer ligne : ");
            scanf("%d", &ligne); // Rentrer ligne : 
            printf("Rentrer colone : ");
            scanf("%d", &column); // Rentrer colone : 
            printf("\n");


            played = Is_possible(plateau, ligne, column, Indice_tab_player, Possible_vect);

            if (played) {
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
