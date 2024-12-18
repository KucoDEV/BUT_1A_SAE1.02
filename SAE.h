#include "includes.h"


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARMES 5

// Structure  joueur
typedef struct {
    char pseudo[50];
    int pointsDeVie;
    int degatsParAttaque;
    int* scores;
    int partiesJouees;
    int partiesGagnees;
    int partiesPerdues;
} Joueur;

// Structure  monstre
typedef struct {
    char nom[50];
    int pointsDeVie;
    int niveau;
    int degatsParAttaque;
    int nombreArmes;
    int groupe;
    char* armes; // armes disponibles: P, F, C, O, #
} Monstre;

// Structure partie
typedef struct {
    Joueur joueur;
    Monstre* groupe1;
    int tailleGroupe1;
    Monstre* groupe2;
    int tailleGroupe2;
    int scoreActuel;
} Partie;

// Types d'armes
typedef enum {
    PIERRE = 'P',
    FEUILLE = 'F',
    CISEAUX = 'C',
    ARME_BONNE_A_RIEN = 'O',
    SUPER_ARME = '#'
} ArmeType;

// A CHANGER CAR J'AI TOUT MIS DANS LA STRUCTURE JOUEUR
typedef struct {
    char *pseudo[20];
    int meilleurScore;
    float moyenneScores;
    int nbParties;
    int victoire;
    int defaite;
} Stats;

int menu(void);
void global(void);



int AffichageScore(int choixMenu);

void afficherTableau(Stats tab[], int tlog);




