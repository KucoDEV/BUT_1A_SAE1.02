// File d'attente

#include "stdio.h"
#include "stdlib.h"

#include "../Booleen/booleen.h"

typedef struct Maillon {
    int valeur;
    struct Maillon *suiv;
} Maillon;

typedef struct {
    Maillon *tete;
    Maillon *queue;
} File;

File fileVide(void);
File adjq(File f, int x);
File supt(File f);
// int tete(File f);
// int longueur(File f);
// Booleen estVide(File f);
