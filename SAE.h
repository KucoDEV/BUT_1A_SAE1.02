#include "includes.h"

typedef struct {
    char *pseudo[20];
    int pv;
    int dmg;
    int score;
} Joueur;

typedef struct {
    char *pseudo[20];
    int meilleurScore;
    float moyenneScores;
    int nbParties
    int victoire;
    int defaite;
} Stats;

typedef struct {
    char nom;
    int pv;
    int dmg;
    int nbArme;
    int niveau;
} Monstres;

int menu(void);
void global(void);



void AffichageScore(int choixMenu);

void afficherTableau(Stats tab[], int tlog);




