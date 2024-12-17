#include "SAE.h"

int menu(void) {
    int choix;
    printf("------------- Menu -------------\n");
    printf("\t1. Jouer une partie prédéfinie\n");
    printf("\t2. Créer une nouvelle partie\n");
    printf("\t3. Afficher le tableau des scores triée par nom\n");
    printf("\t4. Afficher le tableau des scores triée par meilleur score\n");
    printf("\t5. Afficher les statistisques d'un joueur\n");
    printf("\t9. Quitter\n");
    printf("--------------------------------\n");
    printf("> Choix: ");
    scanf("%d", &choix);
    return choix;
}

void global(void) {
    int choix;
    int codeErreur;
    int score = 0;
    char pseudo[20];
    char fichier[20];

    choix = menu();

    while (choix != 9) {
        switch (choix) {
        case 1: // Jouer une partie prédéfinie
            printf("Nom du fichier correspondant à la partie : ");
            scanf("%s", fichier);

            printf("Pseudo joueur : ");
            scanf("%s", pseudo);

            jouerPartie(fichier, pseudo, &score);
            printf("Partie terminée. Votre score : %d\n", score);
            break;

        case 2: // Créer une nouvelle partie
            printf("Créer une nouvelle partie en ajoutant vos monstres.\n");
            creerNouvellePartie();
            break;

        case 3: // Afficher le tableau des scores triés par nom
        case 4: // Afficher le tableau des scores triés par meilleur score
        case 5: // Afficher les statistiques d'un joueur
            codeErreur = AffichageScore(choix);
            if (codeErreur == -1) {
                printf("Erreur : Impossible d'ouvrir le fichier des scores.\n");
            }
            break;

        default:
            printf("Choix non valide! Veuillez réessayer.\n");
            break;
        }

        choix = menu(); 
    }

    printf("Merci d'avoir joué, à bientôt!\n");
}


//
//         ________     ________
//   . - ~|        |-^-|        |~ - .
// {      |        |   |        |      }
//         `.____.'     `.____.'
//

void jouerPartie(char *fichier, char *pseudo, int *score) {
    int nosPv = 20;
    int monstrePv = 4; // Exemple à changer

    printf("Début de la partie pour %s avec 20 points de vie.\n", pseudo);

    while (nosPv > 0 && monstrePv > 0) {
        printf("Choisissez votre arme (P pour Pierre, F pour Feuille, C pour Ciseaux) : ");
        char choix;
        scanf(" %c", &choix);

        int attaque = attaqueMonstre();
        printf("Le monstre attaque avec %d.\n", attaque);

        if (victoireDuel(attaque, choix) == 1) {
            monstrePv--;
            *score += 10;
            printf("Vous avez gagné l'attaque ! Score : %d\n", *score);
        } else {
            nosPv--;
            printf("Vous avez perdu l'attaque ! PV restants : %d\n", nosPv);
        }

        if (monstrePv == 0) {
            printf("Le monstre est vaincu !\n");
            *score += 10;
        }
    }
}





//--------------------| generation aléatoire |------------------//

int attaqueMonstre(void){
    int attaque;
    int min = 1;
    int max = 3;

    srand(time(NULL));//initie le générateur de rnd
    attaque = (rand() % (max - min + 1)) + min;
    return attaque;
}


/**
 * \return 1 joueur gagne | 0 monstre gagne
 */
// int victoireDuel(int attaque, char choix){//comparer le chiffre généré aléatoirement avec la lettre que le joueur écrira
    
    
//     if(attaque == )

// }

// choix de l'arme dans la fonction "jouer"













//--------------------| comptage des points |------------------//



























//--------------------| Affichage |------------------//

// int AffichageScore(int choixMenu)
// {
//     FILE * tscore = fopen("/Fichier/scoreboard.txt", "r");
//     if (tscore == NULL)
//         return -1;
    
    
//     int nbJoueurs;
//     fscanf(tscore, "%d", &nbJoueurs);
    
//     int i=0;
//     Stats ts[nbJoueurs];

//     for (i=0; i<nbJoueurs; i++)
//     {
//         fscanf(tscore, "%s %d %f %d %d %d", 
//                         ts[i].pseudo,
//                         &ts[i].meilleurScore,
//                         &ts[i].moyenneScore,
//                         &ts[i].nbParties,
//                         &ts[i].victoire,
//                         &ts[i].défaite);
//     }
    
//     switch (choixMenu)
//     {
//     case 3:
//         tabParNom(ts,nbJoueurs);
//         break;
//     case 4:
//         tabParScore(ts,nbJoueurs);
//         break;
//     case 5:
//         tabParScore(ts,nbJoueurs);
//         break;
//     default:
//         printf("\nComment êtes vous rentrér dans le chargement du tableau sans avoir sélectionné un choix d'affichage dans le menu ??? \n");
//         break;
//     }
// }
//--------------------| Tableau trié par nom |------------------//

void tabParNom(Stats ts[],int tlog)
{
    triEchangeNom(ts,tlog);
    afficherTableau(ts,tlog);
}

//--------------------| Tableau trié par Score |------------------//

void tabParScore(Stats ts[],int tlog)
{
    triEchangeScore(ts,tlog);
    afficherTableau(ts,tlog);
}

//--------------------| Rechercher un Joueur |------------------//

void rechercherJoueur(Stats ts[],int tlog)
{
    char cible[20];
    int trouve;
    int i;

    printf("\nJoueur à afficher : ");
    scanf("%s",cible);
    trouve = rechercheDichomatique(ts,tlog,cible);

    if (trouve != -1)
    {
        printf("\nStatistique du joueur %s : \n\n",cible);
        printf("\nMeilleur Score : %d \n",ts[trouve].meilleurScore);
        printf("\nMoyenne : %.2f \n",ts[trouve].moyenneScores);
        printf("\nNb Parties : %d", ts[trouve].nbParties);
        printf("\nVictoire : %d", ts[trouve].victoire);
        printf("\nDéfaite : %d", ts[trouve].defaite);
    }
}

//--------------------| tri |--------------------//

int plusGrandNom(Stats tab[], int n) {
    int pge = 0;
    int i;
    for ( i = 0; i < n; i++) 
    {
        if (strlen(tab[i].pseudo) > strlen(tab[pge].pseudo)) 
        {
            pge = i;
        }
    }
    return pge;
}

int plusGrandScore(Stats tab[],int n)
{
    int pge=0;
    int i;
    for (i=0;i<n;i++)
    {
        if (tab[i].meilleurScore>tab[pge].meilleurScore)
        {
            pge = i;
        }
    }
    return pge;
}

void echanger(Stats tab[], int i, int j)
{
    Stats tmp = tab[j];
    tab[j] = tab[i];
    tab[i] = tmp;
}

void triEchangeNom(Stats tab[], int n)
{
    int max;
    while (n > 1)
    {
        max = plusGrandNom(tab, n);
        echanger(tab, max, n - 1); 
        n = n - 1;
    }
}

void triEchangeScore(Stats tab[], int n)
{
    int max;
    while (n > 1)
    {
        max = plusGrandScore(tab, n);
        echanger(tab, max, n - 1); 
        n = n - 1;
    }
}

//--------------------| Affichage Tab [Pseudo : BestScore] |--------------------//

void afficherTableau(Stats tab[], int tlog)
{
    int i;
    printf("\nTableau des Scores :\n\n");
    for (i = 0; i < tlog; i++)
    {
        printf("%20s | %10d\n", tab[i].pseudo, tab[i].meilleurScore);
    }
}

//--------------------| Recherche Dicho d'un Joueur |--------------------//

int rechercheDichomatique(Stats tab[],int n,char cible[])
{
    int inf = 0;
    int sup = n-1;
    int mid;
    while (inf <= sup)
    {
        mid = (inf + sup)/2;

        if (strcmp(tab[mid].pseudo,cible) == 0)
            return mid;

        if (strcmp(cible,tab[mid].pseudo) > 0)
            inf = mid+1;

        else sup = mid+1;
    }
    return -1;
}