#include <stdbool.h>
#define Lenght_tab 8

#define RESET "\x1b[0m"
#define BLACK_BG "\x1b[48;5;22m"  // Fond vert foncé
#define WHITE_BG "\x1b[48;5;28m"  // Fond vert clair

// Fonctions de fonctions_bases.c

void Init_tab(int plateau[Lenght_tab][Lenght_tab]);
void Print_tab(int plateau[Lenght_tab][Lenght_tab]); 
bool Is_empty(int plateau[Lenght_tab][Lenght_tab], int ligne, int column); 
bool Tab_is_empty(int plateau[Lenght_tab][Lenght_tab], int Indice_player, int Possible_vect[8][2]);
int Is_possible(int plateau[Lenght_tab][Lenght_tab], int i, int j, int Indice_player, int Possible_vect[8][2]);
int swap(int plateau[Lenght_tab][Lenght_tab], int i, int j, int Indice_player, int Possible_vect[8][2]);
int Who_win(int plateau[Lenght_tab][Lenght_tab]);

// Fonctions de IA.c

int IA(int plateau[Lenght_tab][Lenght_tab], int Indice_player);
int IA_max_pts(int plateau[Lenght_tab][Lenght_tab], int Indice_player);
int appel_IA_max_pts_rec(int plateau[Lenght_tab][Lenght_tab], int Indice_player, int MyColor);
int IA_max_pts_rec(int plateau[Lenght_tab][Lenght_tab], int Indice_player, int MyColor, int profondeur);
int IA_max_pts_rec_2(int plateau[Lenght_tab][Lenght_tab], int Indice_player, int MyColor, int profondeur);
int appel_IA_max_pts_rec_var(int plateau[Lenght_tab][Lenght_tab], int Indice_player, int MyColor, int nb_move);
int calcul_profondeur(int nb_move);
int appel_IA_max_pts_rec_elag(int plateau[Lenght_tab][Lenght_tab], int Indice_player, int MyColor, int nb_move);
int calcul_points(int plateau[Lenght_tab][Lenght_tab], int MyColor);

