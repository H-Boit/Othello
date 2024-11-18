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

    bool boucle = true;
    while(boucle){
        
        int ligne;
        int column;

        printf("\n");
        printf("C'est au tour des pions %c\n", tab_player[Indice_tab_player]);
        printf("Rentrer ligne : ");
        scanf("%d", &ligne); // Rentrer ligne : 
        printf("Rentrer colone : ");
        scanf("%d", &column); // Rentrer colone : 

        int Possible_vect[8][2];
        bool played = Is_possible(plateau, ligne, column, Indice_tab_player, Possible_vect);

        printf("\n");
        for (int i =0;i<8; i++){
            for (int j =0; j<2;j++){
                printf("%d ", Possible_vect[i][j]);
            }
            printf(" , ");
        }
        printf("\n");

        Print_tab(plateau);
        Indice_tab_player = (Indice_tab_player + 1)%2;

        if (!played || Tab_is_empty(plateau)){
            printf("Le joueur %c a gagné ! \n",tab_player[Indice_tab_player]);
            boucle = false;
        }

    }
    return 0;
}
