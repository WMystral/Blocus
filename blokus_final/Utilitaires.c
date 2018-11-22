/* MAUMENE Juliette
   JORANDON Arnaud*/

#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include "Utilitaires.h"
#include "Ressources.h"
#include "Game.h"


struct bouton{
  int id;
  int x;
  int y;
  int width;
  int height;
};

struct bloc {
  int x;
  int y;
  int width;
  int height;
};

int check_button(struct bouton image){
    /*Regarde si la souris est au dessus de l'image*/
  if (_X > image.x && _X < image.x+image.width && _Y > image.y && _Y < image.y+image.height)
    return 1;
  else
    return 0;
}

int check_button2(struct bloc img){
    /*Regarde si la souris est au dessus de l'image*/
  if (_X > img.x && _X < img.x+img.width && _Y > img.y && _Y < img.y+img.height)
    return 1;
  else
    return 0;
}


void mouse_hover(struct bouton image, struct bouton hover){
  /*Affiche une version rouge de "Player 1" et "Player 2" au passage de la souris*/
  if(check_button(image))
    AfficherSprite(hover.id, hover.x, hover.y);
  else
    AfficherSprite(image.id,image.x, image.y);
}



void GameOver(int *player){
  int inEnd=1,x,y;
  if(*player==1){
    ChargerImageFond("GOM.png");
  }
  if(*player==2){
    ChargerImageFond("GOL.png");
  }
   SourisPosition();
   x=_X;
   y=_Y;
  struct bloc Menu = {34, 337,171,38};
  struct bloc Quit = {480,325,166,59};

  while(inEnd!=0){
  if(check_button2(Menu)) {
    if(SourisCliquee()){
      *player=0;
      menu(player);
    }
  }
  
  if (check_button2(Quit)) {
    if(SourisCliquee()) {
      inEnd=0;
      FermerGraphique();
    }
  }
  }
}


void grille (int *taille) { 
/*Fonction de création de la grille avec des cases de 75 de côté*/
  int i,j;
  int x=0,y=0,X=0,Y=0;
  int centre=(FNTR -(*taille)*CASE)/2; /*Cette variable nous permet
					 de centrer la grille au milieu
					 de la fenêtre*/

  for(i=0; i<*taille; i++){
    DessinerRectangle(centre,centre+(CASE*i),CASE,CASE);
    for(j=0; j<*taille; j++){
      DessinerRectangle(centre+(CASE*j),centre+(CASE*i),CASE,CASE);
    }
  }
}


void ini_verif(int *taille,int verif[11][11]){
  /*Pour notre tableau représentatif de la situation du jeu.
    On initialise une marge autour du tableau pour faciliter la
    vérification au fil du jeu, la marge vallant 4, et les cases
    vides 0, on initialise les cases jouables en fonction de la
    taille exigée*/
 
  int i,j;

  for(i=0;i<11;i++){
    for(j=0;j<11;j++){
      verif[i][j]=4;
    }
  }
  for(i=1;i<=*taille;i++){
    for(j=1;j<=*taille;j++){
      verif[i][j]=0;
    }
  }
}


void ecran2(int *mode) {
  
  /*Fonction permettant d'afficher l'écran pour 
    choisir la taille de sa grille*/
  int inGrid=1;
  int taille;
  int x,y;

ChargerImageFond("gridsize.png");
 struct bloc trois = {104, 250, 60, 60};
 struct bloc quatre = {253, 250, 60, 60};
 struct bloc cinq  = {388, 250, 60, 60};
 struct bloc six = {523, 250, 60, 60};
 struct bloc sept = {172, 395, 60, 60};
 struct bloc huit = {326, 395, 60, 60};
 struct bloc neuf = {467, 395, 60, 60};

 SourisPosition();
 x=_X;
 y=_Y;
if(check_button2(trois)) {
   if(SourisCliquee()) {
     taille=3;
     while(inGrid) {
      Jouer(mode,&taille);
    }
}
 }
if(check_button2(quatre)) {
   if(SourisCliquee()) {
     taille=4;
     while(inGrid) {
      Jouer(mode,&taille);
    }
}
 }
if(check_button2(cinq)) {
   if(SourisCliquee()) {
     taille=5;
     while(inGrid) {
      Jouer(mode,&taille);
    }
}
 }
 if(check_button2(six)) {
   if(SourisCliquee()) {
     taille=6;
     while(inGrid) {
      Jouer(mode,&taille);
    }
}
 }
 if(check_button2(sept)) {
   if(SourisCliquee()) {
     taille=7;
     while(inGrid) {
      Jouer(mode,&taille);
    }
}
 }
if(check_button2(huit)) {
   if(SourisCliquee()) {
     taille=3;
     while(inGrid) {
      Jouer(mode,&taille);
    }
}
 }
    if(check_button2(neuf)) {
   if(SourisCliquee()) {
     taille=9;
     while(inGrid) {
      Jouer(mode,&taille);
    }
}
    }
   printf("%s%d","Taille= ", taille);
}


int VerifierPosition(int verif[11][11],int *xMario, int *yMario, int *xLuigi, int *yLuigi, int *perdu){
  /*Cette fonction sert à tester si un joueur peut encore bouger, le cas
    échéant, il a donc perdu*/
  int i, xtest=*xMario, ytest=*yMario;

  for(i=1;i<3;i++){
    *perdu=0;
    if(xtest==0&&ytest==0){ 
    }else{
    if(verif[xtest-1][ytest-1]!=0 && verif[xtest][ytest-1]!=0 && verif[xtest+1][ytest-1]!=0 && verif[xtest-1][ytest]!=0 && 
     verif[xtest+1][ytest]!=0 && verif[xtest-1][ytest+1]!=0 &&  verif[xtest][ytest+1]!=0 && verif[xtest+1][ytest+1]!=0){
      *perdu=i;
    }
    else{
      *perdu=0;
    }
    if(*perdu>0){
      return 0;
    }
  }
  xtest=*xLuigi;
  ytest=*yLuigi;
}
}


int menu(int *mode) {
  /*Fonction permettant d'afficher le premier écran du jeu*/
  int x, y;
  int inMenu = 1;

  InitialiserGraphique();
  CreerFenetre(150,50,675,675);

  struct bouton player1 = {5, 227, 150, 221, 30};
  struct bouton player1R = {6, 22, 150, 221, 30};
  struct bouton player2 = {7, 227, 200, 221, 30};
  struct bouton player2R = {8, 227, 200, 221, 30};
  struct bouton quit = {9, 274, 250, 126, 30};
  struct bouton quitR = {10, 274, 250, 126, 30};

  LoadImages();
  

  /*Affichage de l'image 1 Joueur, 2 Joueur, Quitter et BLOCUS*/
  ChargerImageFond("menu.png");
  AfficherSprite(player1.id, player1.x, player1.y);
  AfficherSprite(player2.id, player2.x, player2.y);
  AfficherSprite(quit.id, quit.x, quit.y);
  AfficherSprite(11,379,50);

  

   while(inMenu) {

    SourisPosition();
    mouse_hover(player1, player1R);
    mouse_hover(player2, player2R);
    mouse_hover(quit, quitR);
    
    SourisPosition();
    x=_X;
    y=_Y;
    
    if (check_button(player1)) {

      if(SourisCliquee()) {
        while(inMenu){
        ecran2(mode);    
        }
      }
    }


    if (check_button(player2)) {
      if(SourisCliquee()) {
        while(inMenu) {
          ecran2(mode);
        }
      }
    }

    if (check_button(quit)) {
      if(SourisCliquee()) {
      inMenu=0;
      FermerGraphique();
        
      }
    }
    
  }
  return EXIT_SUCCESS;
}




