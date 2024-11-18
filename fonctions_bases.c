#include <stdio.h>
#include <stdbool.h>
#include "fonctions.h"

/*-------------------------------------------------------------------------*/

void Init_tab(int plateau[Lenght_tab][Lenght_tab]) { 
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j ++){
            plateau[i][j] = (-1);
        }
    }
    plateau[3][3] = 1;
    plateau[3][4] = 0;
    plateau[4][3] = 0;
    plateau[4][4] = 1;
}

/*-------------------------------------------------------------------------*/

void Print_tab(int plateau[Lenght_tab][Lenght_tab]){ 
    printf("  0 1 2 3 4 5 6 7");
    printf("\n");
    for(int i = 0; i < 8; i++){
        printf("%d ",i);
        for(int j = 0; j < 8; j ++){
            if (plateau[i][j] == 0) printf("N ");
            else if (plateau[i][j] == 1) printf("B ");
            else printf("+ ");
        }
        printf("\n");
    }
}

/*-------------------------------------------------------------------------*/

bool Is_empty(int plateau[Lenght_tab][Lenght_tab], int ligne, int column){ 
    return (plateau[ligne][column] == (-1));
}

/*-------------------------------------------------------------------------*/

bool Tab_is_empty(int plateau[Lenght_tab][Lenght_tab], int Indice_player, int Possible_vect[8][2]){
    for (int init = 0; init < 8 ; init++){
        Possible_vect[init][0] = 0;
        Possible_vect[init][1] = 0;
    }
    for (int i = 0; i<8; i++){
        for (int j = 0; j<8; j++){
            if (Is_empty(plateau, i , j)){
                if (Is_possible(plateau, i, j, Indice_player, Possible_vect)) return 0;
            }
        }
    }
    return 1;
}

/*-------------------------------------------------------------------------*/

bool Is_possible(int plateau[Lenght_tab][Lenght_tab], int i, int j, int Indice_player, int Possible_vect[8][2]){

    bool possible = false;
    int nb_of_possible_vec=0;
    int Vect[8][2] = {{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1}};

    if (Is_empty(plateau,i,j)){
        for (int i_vect = 0; i_vect < 8; i_vect++){
            int pos_ligne = Vect[i_vect][0]+i;
            int pos_column = Vect[i_vect][1]+j;

            bool end = true;
            bool in_boucle=false;

            if(pos_ligne >= 0 && pos_ligne <= 7 && pos_column >= 0 && pos_column <= 7){
                end = false;
            }
            while (plateau[pos_ligne][pos_column] != Indice_player && plateau[pos_ligne][pos_column] != (-1) && end == false){
                in_boucle=true;
                if(!(pos_ligne >= 0 && pos_ligne <= 7 && pos_column >= 0 && pos_column <= 7)){
                    end = true;
                } else {
                    pos_ligne += Vect[i_vect][0];
                    pos_column += Vect[i_vect][1];
                }
            }
            if ((plateau[pos_ligne][pos_column] == Indice_player) && (in_boucle==true) && end!=true){
                Possible_vect[nb_of_possible_vec][0] = Vect[i_vect][0];
                Possible_vect[nb_of_possible_vec][1] = Vect[i_vect][1];
                nb_of_possible_vec++;
                possible = true;
            }
        }
    }
    return possible;
}

/*-------------------------------------------------------------------------*/

void swap(int plateau[Lenght_tab][Lenght_tab], int i, int j, int Indice_player, int Possible_vect[8][2]){
    int cmpt=0;
    plateau[i][j]=  Indice_player ; 
    while((Possible_vect[cmpt][0]!=0 || Possible_vect[cmpt][1]!=0) && cmpt < 8){
        cmpt++;
    }
    for(int nb_ligne_retourne=0 ; nb_ligne_retourne < cmpt ; nb_ligne_retourne++){
        int di = Possible_vect[nb_ligne_retourne][0];
        int dj = Possible_vect[nb_ligne_retourne][1];
        int pos_ligne= i+ di;
        int pos_column = j + dj;
        while(plateau[pos_ligne][pos_column]!= Indice_player){
            plateau[pos_ligne][pos_column] =  Indice_player ; 
            pos_ligne += di;
            pos_column += dj;
        }
    }

}

/*--------------------------------------------------------------------------*/

/*Retourne 0 si les pions noirs ont gagné, 1 pour les blancs et -1 sinon*/
int Who_win(int plateau[Lenght_tab][Lenght_tab]){
    int N = 0;
    int B = 0;
    int winner = -1;
    for (int i = 0; i<Lenght_tab; i++){
        for (int j = 0; j<Lenght_tab; j++){
            if (plateau[i][j] == 0) N++;
            else if (plateau[i][j] == 1) B++;
        }
    }
    if (N>B) winner = 0;
    else if (B>N) winner = 1;
    return winner;
}
