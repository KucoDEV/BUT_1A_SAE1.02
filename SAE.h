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

void global(void);
int menu(void);
void chargerJoueurs(char* nomFichier, Joueur** joueurs, int* nbJoueurs);
void creerNouvellePartie(char* nomFichier);
void afficherJoueurs(Joueur *joueur, int nbJoueurs);
int main(void);


//--------------------| Fonction d'affichage |--------------------//

int ChargeTabAffichage(void);
void tabParNom(Stats ts[],int tlog);
void tabParScore(Stats ts[],int tlog);
void rechercherJoueur(Stats ts[],int tlog);
int plusGrandNom(Stats tab[], int n);
int plusGrandScore(Stats tab[],int n);
void echanger(Stats tab[], int i, int j);
void triEchangeNom(Stats tab[], int n);
void triEchangeScore(Stats tab[], int n);
void afficherTableauScore(Stats tab[], int tlog);
void afficherTableauNom(Stats tab[], int tlog);
void afficherTableauLettre(Stats tab[], int tlog);
int rechercheDichomatique(Stats tab[],int n,char cible[]);
void affichageJoueur(Stats ts[],int tlo, int trouve, char cible[]);
void affichageLettre(Stats tab[], int tlog, char Lettre);
void afficherDerniers(Stats tab[], int tlog, int x);