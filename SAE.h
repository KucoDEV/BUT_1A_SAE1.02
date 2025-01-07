
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Files/files.h"

#define MAX_ARMES 5

typedef struct {
    char pseudo[50]; 
    int pointsDeVie;
    int degatsParAttaque;
    int scores[100];
    int partiesJouees;
    int partiesGagnees;
    int partiesPerdues;
} Joueur;

typedef struct {
    char nom[50];
    int pointsDeVie;
    int niveau;
    int degatsParAttaque;
    int nombreArmes;
    int groupe;
    char armes[MAX_ARMES];
} Monstre;

typedef struct {
    Joueur joueur;
    Monstre* groupe1;
    int tailleGroupe1;
    Monstre* groupe2;
    int tailleGroupe2;
    int scoreActuel;
} Partie;

typedef enum {
    PIERRE = 'P',
    FEUILLE = 'F',
    CISEAUX = 'C',
    ARME_BONNE_A_RIEN = 'O',
    SUPER_ARME = '#'
} ArmeType;

typedef struct {
    char pseudo[50];
    int meilleurScore;
    float moyenneScores;
    int nbParties;
    int victoire;
    int defaite;
} Stats;

// Fonctions principales du programme
void global(void);
int menu(void);
void deroulerPartie(char* nomFichier, char* pseudo);
void creerNouvellePartie(char* nomFichier);

// Fonctions liées au duel et au jeu
int victoireDuel(int attaque, char choix, Monstre m);
char attaqueJoueur(void);
int attaqueMonstre(Monstre m);