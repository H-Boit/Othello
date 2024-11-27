#include <stdio.h>
#include <stdbool.h>
#include "fonctions.h"

/*----------------------------------------------------------------------------------*/

int IA(int plateau[Lenght_tab][Lenght_tab], int Indice_player){
    int Possible_vect[8][2];
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            int play=Is_possible(plateau, i, j, Indice_player, Possible_vect);
			    if(play>0){
                    return i*8+j;
                }
        }
    }
    return 64;
}

/*----------------------------------------------------------------------------------*/

int IA_max_pts(int plateau[Lenght_tab][Lenght_tab], int Indice_player){
    int tab_max_pts[64]; // 
    int Possible_vect[8][2];
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            Is_possible(plateau, i, j, Indice_player, Possible_vect);
        }
    }

    return 64;
}
