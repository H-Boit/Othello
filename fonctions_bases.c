#include <stdio.h>
#include <stdbool.h>
#include "fonctions.h"

/*-------------------------------------------------------------------------*/
/*  PARAMETRES :
        plateau : le plateau de jeux, 
    
    RETURN :
        Initialise le plateau
*/
void Init_tab(int plateau[Lenght_tab][Lenght_tab]) { 
    for(int i = 0; i < Lenght_tab; i++){
        for(int j = 0; j < Lenght_tab; j ++){
            plateau[i][j] = (-1);
        }
    }
    plateau[3][3] = 1;
    plateau[3][4] = 0;
    plateau[4][3] = 0;
    plateau[4][4] = 1;
}

/*-------------------------------------------------------------------------*/
/*  PARAMETRES :
        plateau : le plateau de jeux, 
    
    RETURN :
        Affiche le tableau en console
*/
void Print_tab(int plateau[Lenght_tab][Lenght_tab]) { 
    printf("     0  1  2  3  4  5  6  7\n");

    for (int i = 0; i < 8; i++) {
        printf(" %d  ", i);
        for (int j = 0; j < 8; j++) {

            if ((i + j) % 2 == 0) printf(BLACK_BG);
            else printf(WHITE_BG);

            if (plateau[i][j] == -1) printf("   ");  
            else if (plateau[i][j] == 0) printf(" B ");  
            else if (plateau[i][j] == 1) printf(" W "); 

            printf(RESET);
        }
        printf("\n");
    }
}

/*-------------------------------------------------------------------------*/
/*  PARAMETRES :
        plateau : le plateau de jeux, 
        ligne : l'indice de ligne du coup,
        column : l'indice de colonne du coup,
    
    RETURN :
        1 si la case est vide
        0 sinon
*/
bool Is_empty(int plateau[Lenght_tab][Lenght_tab], int ligne, int column){ 
    return (plateau[ligne][column] == (-1));
}

/*-------------------------------------------------------------------------*/
/*  PARAMETRES :
        plateau : le plateau de jeux, 
        Indice_player : le numéro correspondant à la couleur du joueur,
        Possible_vect : un tableau contenant les vecteurs possibles de déplacement,
    
    RETURN :
        1 si le tableau est plein
        0 sinon
*/
bool Tab_is_empty(int plateau[Lenght_tab][Lenght_tab], int Indice_player, int Possible_vect[8][2]){
    for (int init = 0; init < Lenght_tab ; init++){
        Possible_vect[init][0] = 0;
        Possible_vect[init][1] = 0;
    }
    for (int i = 0; i<Lenght_tab; i++){
        for (int j = 0; j<Lenght_tab; j++){
            if (Is_empty(plateau, i , j)){
                if (Is_possible(plateau, i, j, Indice_player, Possible_vect) > 0) return 0;
            }
        }
    }
    return 1;
}

/*-------------------------------------------------------------------------*/
/*
    PARAMETRES :
        plateau : le plateau de jeux, 
        i : l'indice de ligne du coup,
        j : l'indice de colonne du coup,
        Indice_player : le numéro correspondant à la couleur du joueur,
        Possible_vect : un tableau initialisé vide
    
    RETURN :
        nb_of_possible_vec : nombre de vecteurs de direction

    UPDATE :
        Possible_vect : remplit les nb_of_possible_vec premières cases avec les vecteurs possibles
*/
int Is_possible(int plateau[Lenght_tab][Lenght_tab], int i, int j, int Indice_player, int Possible_vect[8][2]){

    int nb_of_possible_vec=0;
    int Vect[8][2] = {{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1}};

    if (Is_empty(plateau,i,j)){
        for (int i_vect = 0; i_vect < Lenght_tab; i_vect++){
            int pos_ligne = Vect[i_vect][0]+i;
            int pos_column = Vect[i_vect][1]+j;

            bool in_boucle=false;

            while (plateau[pos_ligne][pos_column] == (!Indice_player) && (pos_ligne >= 0) && (pos_ligne < 8) && (pos_column >= 0) && (pos_column <= 7)){

                pos_ligne += Vect[i_vect][0];
                pos_column += Vect[i_vect][1];
                in_boucle = true;
            }
            if ((plateau[pos_ligne][pos_column] == Indice_player) && (in_boucle==true) && (pos_ligne >= 0) && (pos_ligne < 8) && (pos_column >= 0) && (pos_column <= 7)){
                Possible_vect[nb_of_possible_vec][0] = Vect[i_vect][0];
                Possible_vect[nb_of_possible_vec][1] = Vect[i_vect][1];
                nb_of_possible_vec += 1;
            }
        }
    }
    return nb_of_possible_vec;
}

/*-------------------------------------------------------------------------*/
/*  PARAMETRES :
        plateau : le plateau de jeux, 
        i : l'indice de ligne du coup,
        j : l'indice de colonne du coup,
        Indice_player : le numéro correspondant à la couleur du joueur,
        Possible_vect : un tableau contenant les vecteurs possibles de déplacement,
    
    RETURN :
        p_ret : nombre de pions retournés en tout
*/
int swap(int plateau[Lenght_tab][Lenght_tab], int i, int j, int Indice_player, int Possible_vect[8][2]){
    int p_ret = 0, cmpt = 0, temp_p_ret = 0;
    plateau[i][j]=  Indice_player ; 
    while((Possible_vect[cmpt][0]!=0 || Possible_vect[cmpt][1]!=0) && cmpt < 8){
        int di = Possible_vect[cmpt][0];
        int dj = Possible_vect[cmpt][1];
        int pos_ligne= i+ di;
        int pos_column = j + dj;
        while(plateau[pos_ligne][pos_column]!= Indice_player && (pos_ligne >= 0) && (pos_ligne <= 7) && (pos_column >= 0) && (pos_column <= 7)){
            plateau[pos_ligne][pos_column] =  Indice_player ; 
            pos_ligne += di;
            pos_column += dj;
            temp_p_ret++;
        }
        p_ret = temp_p_ret +1;
        temp_p_ret = 0;
        cmpt++;
    }
    return p_ret;
}

/*--------------------------------------------------------------------------*/
/*  PARAMETRES :
        plateau : le plateau de jeux,

    RETURN : 
        winner : 0 si les pions noirs ont gagné, 1 pour les blancs et -1 sinon
*/
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
