// Liste simplement chainée

#include "stdio.h"
#include "stdlib.h"

#include "../Booleen/booleen.h"

typedef struct maillons {
    int valeur;
    struct maillons *suiv;
} maillons, *Liste;


Liste listeVide(void);
Liste insererEnTete(Liste l, int x);
Liste inserer(Liste l, int x);
Liste supprimerEnTete(Liste l);
Liste supprimer(Liste l, int x);
Liste supprimerEnQueue(Liste l);
Liste insererEnQueue(Liste l, int x);
Booleen vide(Liste l);
int longueur(Liste l);
int tete(Liste l);
Booleen existe(Liste l, int x);
void afficherListe(Liste l);
