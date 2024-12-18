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
/*  PARAMETRES :
        plateau : le plateau de jeux, 
        Indice_player : le numéro correspondant à la couleur du joueur,
    
    RETURN :
        valeur entre 0 et 63 : le premier coup possible
        64 : aucun coup possible
*/
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
/*  PARAMETRES :
        plateau : le plateau de jeux, 
        Indice_player : le numéro correspondant à la couleur du joueur,
    
    RETURN :
        imax : indice du coup rapportant le plus de points
*/
int IA_max_pts(int plateau[Lenght_tab][Lenght_tab], int Indice_player){
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
/*  PARAMETRES :
        plateau : le plateau de jeux, 
        Indice_player : le numéro correspondant à la couleur du joueur,
        MyColor : Indice correspondant à notre couleur,
    
    RETURN :
        imax : coup le plus interessant, calculé grâce au tableau des meilleurs positions,
*/
int appel_IA_max_pts_rec(int plateau[Lenght_tab][Lenght_tab], int Indice_player, int MyColor){

    int profondeur = 6, coup_score[Lenght_tab*Lenght_tab][2] = {{0,0}};

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
                coup_score[i*Lenght_tab+j][1] = 1;
                coup_score[i*Lenght_tab+j][0] = IA_max_pts_rec(copie_tableau, !Indice_player, MyColor, profondeur);
            }
        }
    }
    long max = -100000000000000000000000; 
    int imax = 64;
    for (int i = 0; i<  Lenght_tab* Lenght_tab; i++){
        if (coup_score[i][0] > max && coup_score[i][1] == 1){
            max = coup_score[i][0];
            imax = i;
        }
    }
    return imax;

}


/*----------------------------------------------------------------------------------*/
/*  PARAMETRES :
        plateau : le plateau de jeux, 
        Indice_player : le numéro correspondant à la couleur du joueur,
        MyColor : Indice correspondant à notre couleur,
        profondeur : nombre de coup joués à l'avance pour calculer l'avancement de la partie,
    
    RETURN :
        res : point calculés sur le tableau de position,
*/
int IA_max_pts_rec(int plateau[Lenght_tab][Lenght_tab], int Indice_player, int MyColor, int profondeur){
    int res = 0;
    if (profondeur > 0){
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
        res += calcul_points(plateau, MyColor);
    }
    return res;
}

/*----------------------------------------------------------------------------------*/
/*  PARAMETRES :
        plateau : le plateau de jeux, 
        Indice_player : le numéro correspondant à la couleur du joueur,
        MyColor : Indice correspondant à notre couleur,
        profondeur : nombre de coup joués à l'avance pour calculer l'avancement de la partie,
    
    RETURN :
        res : point calculés sur le tableau de position
*/
int IA_max_pts_rec_2(int plateau[Lenght_tab][Lenght_tab], int Indice_player, int MyColor, int profondeur){
    int res = 0, somme = 0, nb = 0, moy = 0;
    if (profondeur > 0){
        for(int i=0;i<Lenght_tab;i++){
            for(int j=0;j<Lenght_tab;j++){

                int Possible_vect[8][2] = {{0,0}}, tmp = 0;
                tmp = Is_possible(plateau, i, j, Indice_player, Possible_vect);
                if (tmp != 0){
                    nb ++;
                    int copie_tableau[Lenght_tab][Lenght_tab];
                    for (int i = 0; i < Lenght_tab; i++){
                        for (int j = 0; j < Lenght_tab; j++){
                            copie_tableau[i][j] = plateau[i][j];
                        }
                    }
                    swap(copie_tableau, i, j, Indice_player, Possible_vect);
                    int cp = calcul_points(copie_tableau,MyColor);
                    somme += cp;
                    moy = somme/nb;
                    if (cp >= moy+(nb-1)) {
                        res += IA_max_pts_rec(copie_tableau, !Indice_player, MyColor, profondeur - 1);
                    }
                }
            }
        }
    }
    else {
        res += calcul_points(plateau, MyColor);
    }
    return res;
}

/*----------------------------------------------------------------------------------*/
/*  PARAMETRES :
        plateau : le plateau de jeux, 
        Indice_player : le numéro correspondant à la couleur du joueur,
        MyColor : Indice correspondant à notre couleur,
        nb_move : nombre de pions placés sur le plateau,
    
    RETURN :
        imax : coup le plus interessant, calculé grâce au tableau des meilleurs positions,
*/
int appel_IA_max_pts_rec_var(int plateau[Lenght_tab][Lenght_tab], int Indice_player, int MyColor, int nb_move){
    
    int profondeur = calcul_profondeur(nb_move), coup_score[Lenght_tab*Lenght_tab][2] = {{0,0}};

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
                coup_score[i*Lenght_tab+j][1] = 1;
                coup_score[i*Lenght_tab+j][0] = IA_max_pts_rec(copie_tableau, !Indice_player, MyColor, profondeur);
            }
        }
    }
    
    long max = -100000000000000000000000; 
    int imax = 64;
    for (int i = 0; i<  Lenght_tab* Lenght_tab; i++){
        if (coup_score[i][0] > max && coup_score[i][1] == 1){
            max = coup_score[i][0];
            imax = i;
        }
    }
    return imax;

}

/*----------------------------------------------------------------------------------*/
/*  PARAMETRES :
        nb_move : nombre de pions placés sur le plateau,
    
    RETURN :
        nombre représantant la profondeur selon nb_move,
*/
int calcul_profondeur(int nb_move){
    int num = 6;
    if(nb_move<5){return num+1;}
    if(nb_move>4 && nb_move<10){return num-1;}
    if(nb_move>9 && nb_move<40){return num;}
    if(nb_move>39 && nb_move<49){return num+2;}
    if(nb_move>48 && nb_move<51){
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                tab_ref_pontos[i][j]=1;}}
    }
    if(nb_move>48 && nb_move<55){
        return num+11;}
    else{return 10;}
}
 
/*----------------------------------------------------------------------------------*/
/*  PARAMETRES :
        plateau : le plateau de jeux, 
        Indice_player : le numéro correspondant à la couleur du joueur,
        MyColor : Indice correspondant à notre couleur,
        nb_move : nombre de pions placés sur le plateau,
    
    RETURN :
        imax : coup le plus interessant, calculé grâce au tableau des meilleurs positions,
*/
int appel_IA_max_pts_rec_elag(int plateau[Lenght_tab][Lenght_tab], int Indice_player, int MyColor, int nb_move){
    
    int profondeur = calcul_profondeur(nb_move), coup_score[Lenght_tab*Lenght_tab][2] = {{0,0}}, somme = 0, nb = 0, moy = 0;

    for(int i=0;i<Lenght_tab;i++){
        for(int j=0;j<Lenght_tab;j++){

            int Possible_vect[8][2] = {{0,0}}, tmp = 0;
            tmp = Is_possible(plateau, i, j, Indice_player, Possible_vect);
            if (tmp != 0){
                nb ++;
                int copie_tableau[Lenght_tab][Lenght_tab];
                for (int i = 0; i < Lenght_tab; i++){
                    for (int j = 0; j < Lenght_tab; j++){
                        copie_tableau[i][j] = plateau[i][j];
                    }
                }
                swap(copie_tableau, i, j, Indice_player, Possible_vect);
                int cp = calcul_points(copie_tableau,MyColor);
                somme += cp;
                moy = somme/nb;
                if (cp >= moy) {
                    coup_score[i*Lenght_tab+j][1] = 1;
                    coup_score[i*Lenght_tab+j][0] = IA_max_pts_rec_2(copie_tableau, !Indice_player, MyColor, profondeur);
                }
            }
        }
    }
    
    long max = -100000000000000000000000; 
    int imax = 64;
    for (int i = 0; i<  Lenght_tab* Lenght_tab; i++){
        if (coup_score[i][0] > max && coup_score[i][1] == 1){
            max = coup_score[i][0];
            imax = i;
        }
    }
    return imax;

}

/*----------------------------------------------------------------------------------*/
/*  PARAMETRES :
        plateau : le plateau de jeux, 
        MyColor : Indice correspondant à notre couleur,
    
    RETURN :
        res : points selon le tableau de position,
*/
int calcul_points(int plateau[Lenght_tab][Lenght_tab], int MyColor){
    int res = 0;
    for(int i=0;i<Lenght_tab;i++){
            for(int j=0;j<Lenght_tab;j++){
                if (plateau[i][j] == MyColor){
                    res += tab_ref_pontos[i][j];
                }
            }
        }
    return res;
}
