
#include "a.h"

void chargerJoueurs(char* nomFichier, Joueur** joueurs, int* nbJoueurs) {
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }
    fscanf(fichier, "%d", nbJoueurs);

    *joueurs = (Joueur*)malloc(*nbJoueurs * sizeof(Joueur));
    if (*joueurs == NULL) {
        perror("Erreur d'allocation mémoire pour les joueurs");
        fclose(fichier);
        return;
    }

    for (int i = 0; i < *nbJoueurs; i++) {
        Joueur* joueurActuel = &(*joueurs)[i];

        fscanf(fichier, "%s %d %d %d", joueurActuel->pseudo, &joueurActuel->partiesJouees, &joueurActuel->partiesGagnees, &joueurActuel->partiesPerdues);

        joueurActuel->scores = (int*)malloc(joueurActuel->partiesJouees * sizeof(int));
        if (joueurActuel->scores == NULL) {
            perror("Erreur d'allocation mémoire pour les scores");
            fclose(fichier);
            return;
        }

        for (int j = 0; j < joueurActuel->partiesJouees; j++) {
            fscanf(fichier, "%d", &joueurActuel->scores[j]);
        }
    }

    fclose(fichier);
    printf("Fichier %s chargé avec succès !\n", nomFichier);
}

void creerNouvellePartie(char* nomFichier) {
    char chemin[20] = "Parties/";
    strcat(chemin, nomFichier);

    FILE* fichier = fopen(chemin, "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier pour écrire la partie");
        exit(1);
    }

    char contexteGroupe1[100], contexteGroupe2[100];
    int tailleGroupe1, tailleGroupe2;

    printf("Contexte du groupe 1 : ");
    getchar(); // Consommer le saut de ligne laissé par scanf dans le menu -> http://ressources.unit.eu/cours/Cfacile/co/ch4_p5_4.html
    fgets(contexteGroupe1, sizeof(contexteGroupe1), stdin);
    contexteGroupe1[strlen(contexteGroupe1) - 1] = '\0';
    fprintf(fichier, "%s\n", contexteGroupe1);

    printf("Nombre de monstres dans le groupe 1 : ");
    scanf("%d", &tailleGroupe1);
    fprintf(fichier, "%d\n", tailleGroupe1);

    for (int i = 0; i < tailleGroupe1; i++) {
        char nom[50];
        int pv, degats;
        int inclureBonneArme = 0, inclureSuperArme = 0;

        printf("\nMonstre %d - Nom : ", i + 1);
        scanf("%s", nom);
        printf("Points de vie : ");
        scanf("%d", &pv);
        printf("Dégâts par attaque : ");
        scanf("%d", &degats);

        printf("Ajouter l'arme bonne à rien (1 pour oui, 0 pour non) : ");
        scanf("%d", &inclureBonneArme);
        printf("Ajouter l'arme surpuissante (1 pour oui, 0 pour non) : ");
        scanf("%d", &inclureSuperArme);

        fprintf(fichier, "%s %d %d %d ", nom, pv, degats, 3 + inclureBonneArme + inclureSuperArme);
        fprintf(fichier, "%c %c %c ", PIERRE, FEUILLE, CISEAUX); // Armes de base
        if (inclureBonneArme) {
            fprintf(fichier, "%c ", ARME_BONNE_A_RIEN);
        }
        if (inclureSuperArme) {
            fprintf(fichier, "%c ", SUPER_ARME);
        }
        fprintf(fichier, "\n");
    }

    printf("\nContexte du groupe 2 : ");
    getchar(); // Consommer le caractère de saut de ligne précédent -> http://ressources.unit.eu/cours/Cfacile/co/ch4_p5_4.html
    fgets(contexteGroupe2, sizeof(contexteGroupe2), stdin);
    contexteGroupe2[strcspn(contexteGroupe2, "\n")] = 0;
    fprintf(fichier, "%s\n", contexteGroupe2);

    printf("Nombre de monstres dans le groupe 2 : ");
    scanf("%d", &tailleGroupe2);
    fprintf(fichier, "%d\n", tailleGroupe2);

    for (int i = 0; i < tailleGroupe2; i++) {
        char nom[50];
        int pv, degats;
        int inclureBonneArme = 0, inclureSuperArme = 0;

        printf("\nMonstre %d - Nom : ", i + 1);
        scanf("%s", nom);
        printf("Points de vie : ");
        scanf("%d", &pv);
        printf("Dégâts par attaque : ");
        scanf("%d", &degats);

        printf("Ajouter l'arme bonne à rien (1 pour oui, 0 pour non) : ");
        scanf("%d", &inclureBonneArme);
        printf("Ajouter l'arme surpuissante (1 pour oui, 0 pour non) : ");
        scanf("%d", &inclureSuperArme);

        fprintf(fichier, "%s %d %d %d ", nom, pv, degats, 3 + inclureBonneArme + inclureSuperArme);
        fprintf(fichier, "%c %c %c ", PIERRE, FEUILLE, CISEAUX); // Armes de base
        if (inclureBonneArme) {
            fprintf(fichier, "%c ", ARME_BONNE_A_RIEN);
        }
        if (inclureSuperArme) {
            fprintf(fichier, "%c ", SUPER_ARME);
        }
        fprintf(fichier, "\n");
    }

    fclose(fichier);
    printf("Nouvelle partie créée avec succès dans le fichier %s.\n", nomFichier);
}

int menu(void) {
    int choix;
    printf("------------- Menu -------------\n");
    printf("\t1. Jouer une partie prédéfinie\n");
    printf("\t2. Créer une nouvelle partie\n");
    printf("\t3. Afficher la liste des joueurs triée par nom\n");
    printf("\t4. Afficher la liste des joueurs triée par meilleur score\n");
    printf("\t5. Afficher les statistiques d'un joueur\n");
    printf("\t9. Quitter\n");
    printf("--------------------------------\n");
    printf("Choix : ");
    scanf("%d", &choix);
    return choix;
}

void global(void) {
    int choix;
    choix = menu();

    Joueur* joueurs = NULL;
    int nbJoueurs = 0;

    chargerJoueurs("scores.txt", &joueurs, &nbJoueurs);

    char nomFichier[30];
    while (choix != 9) {
        switch (choix) {
            case 1:
                printf("Option 1 sélectionnée : Jouer une partie prédéfinie.\n");
                // Appeler la fonction pour jouer une partie prédéfinie
                break;
            case 2:
                printf("Donnez le nom du fichier: ");
                scanf("%s", nomFichier);
                creerNouvellePartie(nomFichier);
                break;
            case 3:
                printf("Option 3 sélectionnée : Afficher la liste des joueurs triée par nom.\n");
                // Appeler la fonction pour afficher les joueurs triés par nom
                break;
            case 4:
                printf("Option 4 sélectionnée : Afficher la liste des joueurs triée par meilleur score.\n");
                // Appeler la fonction pour afficher les joueurs triés par score
                break;
            case 5:
                printf("Option 5 sélectionnée : Afficher les statistiques d'un joueur.\n");
                // Appeler la fonction pour afficher les statistiques d'un joueur
                break;
            case 9:
                printf("Au revoir...\n");
                break;
            default:
                printf("Choix invalide, veuillez réessayer.\n");
        }
        choix = menu();
    }
}

int main(void) {
    global();
    return 0;
}