#include <stdbool.h>
#define Lenght_tab 8


// Fonctions de fonctions_bases.c

void Init_tab(int plateau[Lenght_tab][Lenght_tab]);
void Print_tab(int plateau[Lenght_tab][Lenght_tab]); 
bool Is_empty(int plateau[Lenght_tab][Lenght_tab], int ligne, int column); 
bool Tab_is_empty(int plateau[Lenght_tab][Lenght_tab], int Indice_player, int Possible_vect[8][2]);
bool Is_possible(int plateau[Lenght_tab][Lenght_tab], int i, int j, int Indice_player, int Possible_vect[8][2]);
void swap(int plateau[Lenght_tab][Lenght_tab], int i, int j, int Indice_player, int Possible_vect[8][2]);
int Who_win(int plateau[Lenght_tab][Lenght_tab]);

// Fonctions de IA.c


// Fonctions de test.c
bool test(int plateau_entre[8][8],int plateau_sortie[8][8],int ligne, int colonne, int Indice_player,int Possible_vect[8][2]);
