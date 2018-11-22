/* MAUMENE Juliette
   JORANDON Arnaud*/

#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <time.h>
#include <unistd.h>
#include "Game.h"
#include "Utilitaires.h"
#include "Ressources.h"

void JouerPlayer(int *Joueur,int *taille,int *inGame, int *tour, int *xMario, int *yMario, int *xLuigi, int *yLuigi,int verif[11][11]) {
/*Fonction d'un joueur réel, comprenant aussi bien le joueur 1 que le second*/
  int x,y,c,j,i,l,k, mv=0,phase=1;
  int middle[10];
  int id, oldx, oldy,ValeurCase;
  int centre=(FNTR -(*taille)*CASE)/2;
  

  for(k=0; k<*taille;k++){        /*Ce tableau est remplie des valeurs de la moitié des cases, une à une, afin de placer les images*/
  middle[k]=centre+(CASE/2)+CASE*k;
  }

  while(inGame!=0) { 
    SourisPosition();
    x=_X;
    y=_Y;
    grille(taille);

  if(*Joueur==1){
    id=1;
    oldx=*xMario;
    oldy=*yMario;
    ValeurCase=1;
  }
  if(*Joueur==2){
    id=4;
    oldx=*xLuigi;
    oldy=*yLuigi;
    ValeurCase=2;
  }


  Begin:
  if (SourisCliquee()) {
    for (i=0; i <*taille; i++) {                /*Calcul de la case cliquée: c pour colonne, l pour ligne*/
      if ((_X > (i*CASE+centre)) && ( _X < (i+1)*(CASE+centre))) {
        c=i+1;
      }
    }
    for (j=0; j <*taille; j++) {
      if ((_Y > (j*CASE+centre)) && (_Y < (j+1)*(CASE+centre))) {
        l=j+1;
      }
    }

    if(verif[c][l]!=0){
      goto Begin;
    }

    switch (phase){ 
      case(1):                              /*Déplacement du pion du joueur 1*/
      
      if(*tour!=1){
        if (c < (oldx+2) && c > (oldx-2) && l < (oldy+2) && l > (oldy-2)){
          AfficherSprite(id,middle[c-1]-35,middle[l-1]-35); /*Affichage de l'image de Mario (joueur 1), l'image faisant 70x70, pour qu'elle apparaîsse au milieu de la case, on réduit de 35 la place*/
          verif[c][l]=ValeurCase;
        }else{
          goto Begin;
        }

      AfficherSprite(2,middle[oldx-1]-35,middle[oldy-1]-35);  /* Cette image nous servira à "déplacer" le pion; la valeur 0 est ajoutée pour rendre cette case à nouveau disponible.*/
      verif[oldx][oldy]=0;
      phase=2;
      }else{
        AfficherSprite(id,middle[c-1]-35,middle[l-1]-35);
        verif[c][l]=ValeurCase;
        phase=3;
      }
      if(*Joueur==1){
        *xMario=c; /*oldx prend la valeur de la colonne du pion*/
        *yMario=l; /*oldy prend la valeur de la ligne du pion*/
      }
      if(*Joueur==2){
        *xLuigi=c;
        *yLuigi=l;
      }
       /* A la fin du déplacement, la phase 2 du tour peut commencer: placer le bloc*/
      break;

      case(2):                              /*Placement du bloc du joueur 1*/
        AfficherSprite(3,middle[c-1]-35,middle[l-1]-35);
        verif[c][l]=3;
        phase=3;
        break;
      }
    }
    if (phase==3) {
      inGame=0;
    }
  }
}
void JouerOrdi(int *taille, int *inGame,int *tour, int *xLuigi, int *yLuigi, int verif[11][11]){
  /*Fonction de déplacement*/
  int x,y,c,j,i,l,k, mv=0,phase=1;
  int middle[10];
  int id=4, oldx=*xLuigi, oldy=*yLuigi;
  int ChoixC, ChoixL;
  int centre=(FNTR -(*taille)*CASE)/2;

  for(k=0; k<*taille;k++){        /*Ce tableau est remplie des valeurs de la moitié des cases, une à une, afin de placer les images*/
  middle[k]=centre+(CASE/2)+CASE*k;
  }
   BeginOrdi:
  while(inGame!=0) { 

    grille(taille);

    switch (phase){ 
      case(1):                              /*Déplacement du pion de l'ordi*/
      
      usleep(500000);
      while(SourisCliquee()){
      }
      if(*tour!=1){
        do{
          ChoixC=(rand()%3)-1;
          ChoixL=(rand()%3)-1;
        }while(verif[oldx+ChoixC][oldy+ChoixL]!=0);
        c=oldx+ChoixC;
        l=oldy+ChoixL;

        AfficherSprite(id,middle[c-1]-35,middle[l-1]-35); /*Affichage de l'image de Luigi, l'image faisant 70x70, pour qu'elle apparaîsse au milieu de la case, on réduit de 35 la place*/
        verif[c][l]=2;

        AfficherSprite(2,middle[oldx-1]-35,middle[oldy-1]-35);  /* Cette image nous servira à "déplacer" le pion; la valeur 0 est ajoutée pour rendre cette case à nouveau disponible.*/
        verif[oldx][oldy]=0;
        phase=2;

        }
        else{
          do{
        c=1+rand()%*taille;
        l=1+rand()%*taille;
        }while(verif[c][l]!=0);
        AfficherSprite(id,middle[c-1]-35,middle[l-1]-35);
        verif[c][l]=2;
        phase=3;
      }

      *xLuigi=c;
      *yLuigi=l;

      /* A la fin du déplacement, la phase 2 du tour peut commencer: placer le bloc*/
      break;
      case(2):
                                    /*Placement du bloc de l'ordi*/
        usleep(500000);
        while(SourisCliquee()){
        }
        do{
        c=1+rand()%*taille;
        l=1+rand()%*taille;
        }while(verif[c][l]!=0);
        AfficherSprite(3,middle[c-1]-35,middle[l-1]-35);
        verif[c][l]=3;

        phase=3;
        break;
      }
    if (phase==3) {
      inGame=0;
    }
  }
  }

int PartieJoueur(int *Joueur, int *taille,int *perdu, int *tour,int *OC, int *OL, int *oc, int *ol,int verif[11][11], int *inGame){
  int i,j;
  while(*perdu==0){
    switch(*Joueur){
      case 1:
      JouerPlayer(Joueur,taille,inGame,tour, OC, OL, oc, ol, verif);
      VerifierPosition(verif,OC, OL, oc, ol, perdu);
      *Joueur=2;
      break;
      case 2:
      *inGame=1;
      JouerPlayer(Joueur,taille,inGame,tour, OC, OL, oc, ol, verif);
      VerifierPosition(verif,OC, OL, oc, ol, perdu);
      *Joueur=1;
      (*tour)++;
      break;
    }
  }
}
int PartieOrdi(int *Joueur, int *taille,int *perdu, int *tour,int *OC, int *OL, int *oc, int *ol,int verif[11][11], int *inGame){
  while(*perdu==0){
    switch(*Joueur){
      case 1:
      JouerPlayer(Joueur,taille,inGame,tour, OC, OL, oc, ol, verif);
      VerifierPosition(verif,OC, OL, oc, ol, perdu);
      *Joueur=2;
      break;
      case 2:
      *inGame=1;
      JouerOrdi(taille,inGame,tour,oc, ol, verif);
      VerifierPosition(verif,OC, OL, oc, ol, perdu);
      *Joueur=1;
      (*tour)++;
      break;
    }
  }
}

int Jouer(void){
  int x, y, t,taille=6, Joueur=1, perdu=0,inGame=1, tour=1;
  int player=2;
  int verif[11][11], i, j;
  int OL=0, OC=0, ol=0, oc=0; /* coordonnée des pions Mario et Luigi, utilisée dans leur fonction réciproque.*/
  srand(time(NULL));
  InitialiserGraphique();
  CreerFenetre(500,50,675,675);
  ini_verif(&taille, verif);

  if(player==1){
    PartieOrdi(&Joueur, &taille, &perdu, &tour, &OC, &OL, &oc, &ol, verif, &inGame);
  }
  if(player==2){
    PartieJoueur(&Joueur, &taille, &perdu, &tour, &OC, &OL, &oc, &ol, verif, &inGame);
  }
  /*if(perdu==1){

}
if(perdu==2){
}*/

}

