/**
 * \file SAE.c
 * \brief Fichier contenant les déclarations des fonctions de la SAE
 * 
 * \authors CABARET Benjamin, MIOTTO Quentin, PICHOT-MOÏSE Mathéo
 * \date 5 décembre 2024 -> 10 janvier 2025
 */
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

void sauvegarde(char * pseudo, int score, int victoire);
void sauvegardeTableau(Stats ts[],int nbJoueurs, int newJ,char pseudo[],int score,int victoire);

// Fonctions liées à l'affiche
int ChargeTabAffichage(int choix);
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
int rechercheDichomatique(Stats tab[],int n,char cible[]);
void affichageJoueur(Stats ts[],int tlo, int trouve, char cible[]);
void affichageLettre(Stats tab[], int tlog, char Lettre);
void afficherDerniers(Stats tab[], int tlog, int x);