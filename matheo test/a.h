
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
    int degatsParAttaque;
    int nombreArmes;
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

void global(void);
int menu(void);

// void initialiserJoueur(Joueur* joueur, const char* pseudo);
// void initialiserMonstre(Monstre* monstre, const char* nom, int niveau);

// void jouerPartie(Partie* partie);

// void sauvegarderPartie(const Partie* partie, const char* fichier);
// void chargerPartie(Partie* partie, const char* fichier);

// void afficherJoueurs(Joueur* joueurs, int nbJoueurs, bool triParNom);

// void trierJoueursParNom(Joueur* joueurs, int nbJoueurs);
// void trierJoueursParScore(Joueur* joueurs, int nbJoueurs);
// Joueur* rechercherJoueur(const Joueur* joueurs, int nbJoueurs, const char* pseudo);