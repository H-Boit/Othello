#include <stdio.h>
#include <stdbool.h>
#include "fonctions.h"


int tab_ref_pontos[8][8]={
{500 ,-150,30,10,10,30,-150,500 },
{-150,-250,0 ,0 ,0 ,0 ,-250,-150},
{30  ,0   ,1 ,2 ,2 ,1 ,0   ,30  },
{10  ,0   ,2 ,16,16,2 ,0   ,10  },
{10  ,0   ,2 ,16,16,2 ,0   ,10  },
{30  ,0   ,1 ,2 ,2 ,1 ,0   ,30  },
{-150,-250,0 ,0 ,0 ,0 ,-250,-150},
{500 ,-150,30,10,10,30,-150,500 }
};

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
    // int tab_max_pts[Lenght_tab*Lenght_tab]
    int Possible_vect[8][2], tmp = 0, max = 0, imax = 64;
    for(int i=0;i<Lenght_tab;i++){
        for(int j=0;j<Lenght_tab;j++){
            tmp = Is_possible(plateau, i, j, Indice_player, Possible_vect);
            if (tmp>max){
                max = tmp;
                imax = i*Lenght_tab + j;
            }
        }
    }

    return imax;
}

/*----------------------------------------------------------------------------------*/

int appel_IA_max_pts_rec(int plateau[Lenght_tab][Lenght_tab], int Indice_player, int MyColor){
    // Copie des paramètres et plateau pour les itérations futurs
    // Itère sur les cases possibles et appelle la fonctions récursive
    // pour chaque coup possible
    
    int profondeur = 1, coup_score[Lenght_tab*Lenght_tab][2] = {{0,0}};

    for(int i=0;i<Lenght_tab;i++){
        for(int j=0;j<Lenght_tab;j++){

            int Possible_vect[8][2] = {{0,0}}, tmp = 0;
            tmp = Is_possible(plateau, i, j, Indice_player, Possible_vect);
            if (tmp != 0){
                //
                //printf("%d OK\n", i*Lenght_tab+j);
                //
                int copie_tableau[Lenght_tab][Lenght_tab];
                for (int i = 0; i < Lenght_tab; i++){
                    for (int j = 0; j < Lenght_tab; j++){
                        copie_tableau[i][j] = plateau[i][j];
                    }
                }

                swap(copie_tableau, i, j, Indice_player, Possible_vect);
                coup_score[i*Lenght_tab+j][1] = 1;
                coup_score[i*Lenght_tab+j][0] = IA_max_pts_rec(copie_tableau, Indice_player, MyColor, profondeur);
                //
                //printf("res = %d\n",IA_max_pts_rec(copie_tableau, Indice_player, MyColor, profondeur));
                //


            }
        }
    }
    
    int max = -100000, imax = 64;
    for (int i = 0; i<  Lenght_tab* Lenght_tab; i++){
        if (coup_score[i][0] > max && coup_score[i][1] == 1){
            max = coup_score[i][0];
            imax = i;
        }
    }
    //
    /*
    for (int i = 0; i< 64; i++){
        printf("{%d, %d}\n",coup_score[i][0],coup_score[i][1]);
    }
    printf("\n");
    */
    //printf("%d\n",imax);
    //

    return imax;

}

/*----------------------------------------------------------------------------------*/

int IA_max_pts_rec(int plateau[Lenght_tab][Lenght_tab], int Indice_player, int MyColor, int profondeur){
    int res = 0;
    if (profondeur > 0){
        //
        //printf("Prof : %d\n", profondeur);
        //
        for(int i=0;i<Lenght_tab;i++){
            for(int j=0;j<Lenght_tab;j++){

                int Possible_vect[8][2] = {{0,0}}, tmp = 0;
                tmp = Is_possible(plateau, i, j, Indice_player, Possible_vect);
                if (tmp != 0){
                    int copie_tableau[Lenght_tab][Lenght_tab];
                    for (int i = 0; i < Lenght_tab; i++){
                        for (int j = 0; j < Lenght_tab; j++){
                            copie_tableau[i][j] = plateau[i][j];
                        }
                    }

                    swap(copie_tableau, i, j, Indice_player, Possible_vect);
                    res += IA_max_pts_rec(copie_tableau, !Indice_player, MyColor, profondeur - 1);
                }
            }
        }
    }
    else {
        // Calcul des points
        //
        //printf("FINIE\n");
        //
        for(int i=0;i<Lenght_tab;i++){
            for(int j=0;j<Lenght_tab;j++){
                if (plateau[i][j] == MyColor){
                    res += tab_ref_pontos[i][j];
                }
            }
        }
    }
    return res;
}
