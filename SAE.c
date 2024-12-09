
#include "SAE.h"

int menu(void) {
    int choix;
    printf("------------- Menu -------------\n");
    printf("\t1. Jouer une partie prédéfinie\n");
    printf("\t2. Créer une nouvelle partie\n");
    printf("\t3. Afficher la liste des joueurs triée par nom\n");
    printf("\t4. Afficher la liste des joueurs triée par meilleur score\n");
    printf("\t5. Afficher les statistisques d'un joueur\n");
    printf("\t9. Quitter\n");
    printf("--------------------------------\n");
    printf("> Choix: ");
    scanf("%d", &choix);
    return choix;
}

void global(void) {
    int choix = menu();
    while (choix != 9) {
        switch (choix) {
        case 1:
            // Jouer
            break;
        
        case 2:
            // Fonction créer une partie
            break;
        
        case 3:
            // Affichage
            break;
        
        case 4:
            // Affichage
            break;
        
        case 5:
            // Affichage
            break;
        
        default:
            printf("Choix non valide!\n");
            break;
        }
        choix = menu();
    }
}

//
//         ________     ________
//   . - ~|        |-^-|        |~ - .
// {      |        |   |        |      }
//         `.____.'     `.____.'
//

void tour(void) {}

void jouer(void) {
    char *pseudo[20];
    char *fichier[20];

    printf("Nom du fichier correspondant à la partie: ");
    scanf("%s", fichier);

    printf("Pseudo joueur: ");
    scanf("%s", pseudo);

    while (nosPv > 0 || monstrePv > 0) {
        tour();
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
int victoireDuel(int attaque, char choix){//comparer le chiffre généré aléatoirement avec la lettre que le joueur écrira
    
    
    if(attaque == )

}

// choix de l'arme dans la fonction "jouer"













//--------------------| comptage des points |------------------//



























//--------------------| Tableau |------------------//

int ChargerTabSc(Stats* stats)
{
    FILE * tscore = fopen("/Fichier/scoreboard.txt", "r");
    if (tscore == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier\n");
        return -1;
    }
    
    int nbJoueurs;
    fscanf(tscore, "%d", &nbJoueurs);
    int i=0;

    stats[i] = malloc(sizeof(Stats)); // premier malloc pour le premier fscanf avant le while
    if (stats[i] == NULL) 
    {
        printf("Erreur d'allocation de mémoire\n");
        fclose(tscore);
        return -2; // Erreur d'allocation
    }

    for (i = 0; i < nbJoueurs; i++) 
    {
        fscanf(tscore,"%s %d %d %d %d %d",stats[i]->pseudo, stats[i]->&meilleurScores, stats[i]->&moyenneScores, stats[i]->&nbParties, stats[i]->&victoire, stats[i]->&défaite);
        
        stats[i] = malloc(sizeof(Stats));
        if (stats[i] == NULL) 
        {
            printf("Erreur d'allocation de mémoire\n");
            fclose(tscore);
            return -2; // Erreur d'allocation 
        }
    }
}