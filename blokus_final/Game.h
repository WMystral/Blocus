/* MAUMENE Juliette
   JORANDON Arnaud*/
#ifndef GAME_H
#define GAME_H

void JouerPlayer(int *Joueur,int *taille,int *inGame, int *tour, int *xMario, int *yMario, int *xLuigi, int *yLuigi,int verif[11][11]);


void JouerOrdi(int *taille, int *inGame,int *tour, int *xLuigi, int *yLuigi, int verif[11][11]);

int PartieJoueur(int *Joueur, int *taille,int *perdu, int *tour,int *OC, int *OL, int *oc, int *ol,int verif[11][11], int *inGame);


int PartieOrdi(int *Joueur, int *taille,int *perdu, int *tour,int *OC, int *OL, int *oc, int *ol,int verif[11][11], int *inGame);

#endif

