#include "SAE.h"

int menu(void) {
    int choix;
    printf("------------- Menu -------------\n");
    printf("\t1. Jouer une partie prédéfinie\n");
    printf("\t2. Créer une nouvelle partie\n");
    printf("\t3. Afficher le tableau des scores triée par nom\n");
    printf("\t4. Afficher le tableau des scores triée par meilleur score\n");
    printf("\t5. Afficher les statistiques d'un joueur\n");
    printf("\t9. Quitter\n");
    printf("--------------------------------\n");
    printf("> Choix: ");
    scanf("%d", &choix);
    return choix;
}


void global(void) {
    int choix;
    int score = 0;
    char pseudo[50];
    char fichier[50];

    choix = menu();

    while (choix != 9) {
        switch (choix) {
        case 1: // Jouer une partie prédéfinie
            printf("\nNom du fichier correspondant à la partie : ");
            scanf("%s", fichier);

            printf("Pseudo joueur : ");
            scanf("%s", pseudo);

            deroulerPartie(fichier, pseudo);
            break;

        case 2: // Créer une nouvelle partie
            {
                char nomFichier[50];
                printf("Donnez le nom du fichier: ");
                scanf("%s", nomFichier);
                creerNouvellePartie(nomFichier);
                break;
            }

        case 3: // Afficher le tableau des scores triés par nom
            {
                break;
            }

        case 4: // Afficher le tableau des scores triés par meilleur score
            {
                break;
            }

        case 5: // Afficher les statistiques d'un joueur
            {
                break;
            }

        default:
            printf("Choix non valide! Veuillez réessayer.\n");
            break;
        }

        choix = menu();
    }

    printf("Merci d'avoir joué, à bientôt!\n");
}

void deroulerPartie(char* nomFichier, char* pseudo) {
    Joueur joueur;
    strcpy(joueur.pseudo, pseudo);
    joueur.pointsDeVie = 20;
    joueur.degatsParAttaque = 1;
    int score = 0;

    char chemin[50] = "Parties/";
    strcat(nomFichier, ".txt");
    strcat(chemin, nomFichier);

    FILE* fichier = fopen(chemin, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier de partie");
        return;
    }

    int tailleGroupe1, tailleGroupe2;
    char contexte[200];

    fgets(contexte, sizeof(contexte), fichier);
    printf("\nContexte : %s\n", contexte);

    fscanf(fichier, "%d", &tailleGroupe1);
    Monstre groupe1[tailleGroupe1];

    for (int i = 0; i < tailleGroupe1; i++) {
        fscanf(fichier, "%s %d %d %c %c %c %c %c", groupe1[i].nom, &groupe1[i].niveau, &groupe1[i].nombreArmes,
               &groupe1[i].armes[0], &groupe1[i].armes[1], &groupe1[i].armes[2], &groupe1[i].armes[3], &groupe1[i].armes[4]);

        groupe1[i].pointsDeVie = (groupe1[i].niveau == 1) ? 4 : (groupe1[i].niveau == 2) ? 6 : 4;
        groupe1[i].degatsParAttaque = (groupe1[i].niveau == 3) ? 2 : 1;

        printf("Le monstre %s (%dptV, %dAtt) accoure et se prépare à vous attaquer %s (%dptV, %dAtt)\n",
               groupe1[i].nom, groupe1[i].pointsDeVie, groupe1[i].degatsParAttaque,
               joueur.pseudo, joueur.pointsDeVie, joueur.degatsParAttaque);

        while (groupe1[i].pointsDeVie > 0 && joueur.pointsDeVie > 0) {
            printf("%s (%dpts), choisissez votre arme parmi P, F, C : ", joueur.pseudo, joueur.pointsDeVie);
            char choixJoueur = attaqueJoueur();

            printf("%s (%c) attaque %s (%dptV)\n", joueur.pseudo, choixJoueur, groupe1[i].nom, groupe1[i].pointsDeVie);
            int attaqueMonstreResult = attaqueMonstre(groupe1[i]);
            int resultat = victoireDuel(attaqueMonstreResult, choixJoueur, groupe1[i]);

            if (resultat == 1) {
                groupe1[i].pointsDeVie -= joueur.degatsParAttaque;
                score += 10;
                printf("\t%s gagne l'attaque contre %s. Score : %d\n", joueur.pseudo, groupe1[i].nom, score);
            } else if (resultat == 0) {
                joueur.pointsDeVie -= groupe1[i].degatsParAttaque;
                printf("\t%s perd l'attaque contre %s.\n", joueur.pseudo, groupe1[i].nom);
            } else {
                printf("\tAucun des deux n'a remporté l'attaque.\n");
            }
        }

        if (joueur.pointsDeVie <= 0) {
            printf("PERDU... Vous avez été vaincu par %s. Score final : %d\n\n", groupe1[i].nom, score);
            // miseAJourScore(joueur.pseudo, score, 0);
            fclose(fichier);
            return;
        } else {
            score += 50 * groupe1[i].niveau;
            printf("%s est vaincu ! Score actuel : %d\n\n", groupe1[i].nom, score);
        }
    }

    fgets(contexte, sizeof(contexte), fichier);
    printf("\nContexte : %s\n", contexte);

    fscanf(fichier, "%d", &tailleGroupe2);
    Monstre groupe2[tailleGroupe2];

    for (int i = 0; i < tailleGroupe2; i++) {
        fscanf(fichier, "%s %d %d %c %c %c %c %c", groupe2[i].nom, &groupe2[i].niveau, &groupe2[i].nombreArmes,
               &groupe2[i].armes[0], &groupe2[i].armes[1], &groupe2[i].armes[2], &groupe2[i].armes[3], &groupe2[i].armes[4]);

        groupe2[i].pointsDeVie = (groupe2[i].niveau == 1) ? 4 : (groupe2[i].niveau == 2) ? 6 : 4;
        groupe2[i].degatsParAttaque = (groupe2[i].niveau == 3) ? 2 : 1;
    }

    printf("Les monstres du groupe 2 attaquent tous en même temps !\n");
    while (joueur.pointsDeVie > 0) {
        printf("%s (%dpts), choisissez votre arme parmi P, F, C : ", joueur.pseudo, joueur.pointsDeVie);
        char choixJoueur = attaqueJoueur();

        for (int i = 0; i < tailleGroupe2; i++) {
            if (groupe2[i].pointsDeVie > 0) {
                printf("%s attaque %s\n", joueur.pseudo, groupe2[i].nom);
                int attaqueMonstreResult = attaqueMonstre(groupe2[i]);
                int resultat = victoireDuel(attaqueMonstreResult, choixJoueur, groupe2[i]);

                if (resultat == 1) {
                    groupe2[i].pointsDeVie -= joueur.degatsParAttaque;
                    score += 10;
                    printf("\t%s gagne l'attaque contre %s. Score : %d\n", joueur.pseudo, groupe2[i].nom, score);
                } else if (resultat == 0) {
                    joueur.pointsDeVie -= groupe2[i].degatsParAttaque;
                    printf("\t%s perd l'attaque contre %s.\n", joueur.pseudo, groupe2[i].nom);
                } else {
                    printf("\tAucun des deux n'a remporté l'attaque contre %s.\n", groupe2[i].nom);
                }
            }
        }

        int monstresRestants = 0;
        for (int i = 0; i < tailleGroupe2; i++) {
            if (groupe2[i].pointsDeVie > 0) {
                monstresRestants++;
            } else {
                score += 100 * groupe2[i].niveau;
                printf("%s est vaincu ! Score actuel : %d\n", groupe2[i].nom, score);
            }
        }

        if (monstresRestants == 0) {
            printf("Tous les monstres du groupe 2 ont été vaincus ! Score final : %d\n\n", score);
            break;
        }

        if (joueur.pointsDeVie <= 0) {
            printf("PERDU... Vous avez été vaincu par les monstres du groupe 2... Score final : %d\n\n", score);
            // miseAJourScore(joueur.pseudo, score, 0);
            fclose(fichier);
            return;
        }
    }

    printf("FÉLICITATIONS %s, vous avez terminé la partie avec %d PV restants ! Score final : %d\n", joueur.pseudo, joueur.pointsDeVie, score);
    // miseAJourScore(joueur.pseudo, score, 1);
    fclose(fichier);
}

void creerNouvellePartie(char* nomFichier) {
    char chemin[20] = "Parties/";
    strcat(nomFichier, ".txt");
    strcat(chemin, nomFichier);

    FILE *fichier = fopen(chemin, "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier pour écrire la partie");
        exit(1);
    }

    char contexteGroupe1[100], contexteGroupe2[100];
    int tailleGroupe1, tailleGroupe2;

    printf("Contexte du groupe 1 : ");
    getchar(); // /!\ NE PAS DELETE -> Consommer le saut de ligne laissé par scanf dans le menu
    fgets(contexteGroupe1, sizeof(contexteGroupe1), stdin);
    contexteGroupe1[strlen(contexteGroupe1) - 1] = '\0';
    fprintf(fichier, "%s\n", contexteGroupe1);

    printf("Nombre de monstres dans le groupe 1 : ");
    scanf("%d", &tailleGroupe1);
    fprintf(fichier, "%d\n", tailleGroupe1);

    for (int i = 0; i < tailleGroupe1; i++) {
        Monstre monstre;

        printf("\nMonstre %d - Nom : ", i + 1);
        scanf("%s", monstre.nom);
        printf("Niveau (1, 2, 3) : ");
        scanf("%d", &monstre.niveau);

        monstre.pointsDeVie = (monstre.niveau == 1 ? 4 : (monstre.niveau == 2 ? 6 : 4));
        monstre.degatsParAttaque = (monstre.niveau == 3 ? 2 : 1);
        monstre.nombreArmes = (monstre.niveau == 1 ? 4 : (monstre.niveau == 2 ? 3 : 5));
        monstre.armes[0] = PIERRE;
        monstre.armes[1] = FEUILLE;
        monstre.armes[2] = CISEAUX;

        if (monstre.niveau == 1) {
            monstre.armes[3] = ARME_BONNE_A_RIEN;
        } else if (monstre.niveau == 3) {
            monstre.armes[3] = ARME_BONNE_A_RIEN;
            monstre.armes[4] = SUPER_ARME;
        }

        fprintf(fichier, "%s %d %d ", monstre.nom, monstre.niveau, monstre.nombreArmes);
        for (int j = 0; j < monstre.nombreArmes; j++) {
            fprintf(fichier, "%c ", monstre.armes[j]);
        }
        fprintf(fichier, "\n");
    }

    printf("\nContexte du groupe 2 : ");
    getchar(); // /!\ NE PAS DELETE
    fgets(contexteGroupe2, sizeof(contexteGroupe2), stdin);
    contexteGroupe2[strcspn(contexteGroupe2, "\n")] = 0;
    fprintf(fichier, "%s\n", contexteGroupe2);

    printf("Nombre de monstres dans le groupe 2 : ");
    scanf("%d", &tailleGroupe2);
    fprintf(fichier, "%d\n", tailleGroupe2);

    for (int i = 0; i < tailleGroupe2; i++) {
        Monstre monstre;

        printf("\nMonstre %d - Nom : ", i + 1);
        scanf("%s", monstre.nom);
        printf("Niveau (1, 2, 3) : ");
        scanf("%d", &monstre.niveau);

        monstre.pointsDeVie = (monstre.niveau == 1 ? 4 : (monstre.niveau == 2 ? 6 : 4));
        monstre.degatsParAttaque = (monstre.niveau == 3 ? 2 : 1);
        monstre.nombreArmes = (monstre.niveau == 1 ? 4 : (monstre.niveau == 2 ? 3 : 5));
        monstre.armes[0] = PIERRE;
        monstre.armes[1] = FEUILLE;
        monstre.armes[2] = CISEAUX;

        if (monstre.niveau == 1) {
            monstre.armes[3] = ARME_BONNE_A_RIEN;
        } else if (monstre.niveau == 3) {
            monstre.armes[3] = ARME_BONNE_A_RIEN;
            monstre.armes[4] = SUPER_ARME;
        }

        fprintf(fichier, "%s %d %d ", monstre.nom, monstre.niveau, monstre.nombreArmes);
        for (int j = 0; j < monstre.nombreArmes; j++) {
            fprintf(fichier, "%c ", monstre.armes[j]);
        }
        fprintf(fichier, "\n");
    }

    fclose(fichier);
    printf("Nouvelle partie créée avec succès dans le fichier %s.\n", nomFichier);
}

int victoireDuel(int attaque, char choix, Monstre m) {
    if ((attaque == 1 && choix == 'F') || (attaque == 2 && choix == 'C') || (attaque == 3 && choix == 'P') || (attaque == 5)) {
        return 1;
    }
    if ((attaque == 1 && choix == 'C') || (attaque == 2 && choix == 'P') || (attaque == 3 && choix == 'F') || (attaque == 4)) {
        return 0;
    }
    return -1;
}

char attaqueJoueur(void) {
    char choix;
    scanf(" %c", &choix);

    while (choix != 'P' && choix != 'C' && choix != 'F') {
        printf("Entrée invalide ! Veuillez entrer P, C ou F : ");
        scanf(" %c", &choix);
    }

    return choix;
}

int attaqueMonstre(Monstre m) {
    int min = 1, max = (m.niveau == 1 ? 4 : (m.niveau == 2 ? 3 : 5));
    return (rand() % (max - min + 1)) + min;
}