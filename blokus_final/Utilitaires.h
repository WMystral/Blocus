/* MAUMENE Juliette
   JORANDON Arnaud*/

#ifndef UTILITAIRES_H
#define UTILITAIRES_H

struct bouton;

int check_button(struct bouton image);

void mouse_hover(struct bouton image, struct bouton hover);


void grille (int *taille);


void ini_verif(int *taille,int verif[11][11]);

int VerifierPosition(int verif[11][11],int *xMario, int *yMario, int *xLuigi, int *yLuigi, int *perdu);

int menu(int *mode);

struct bloc;


void ecran2(int *mode);

#endif

