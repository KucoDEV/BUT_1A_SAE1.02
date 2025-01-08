/**
 * \file SAE.c
 * \brief Fichier contenant les fonctions de la SAE
 * 
 * \authors CABARET Benjamin, MIOTTO Quentin, PICHOT-MOÏSE Mathéo
 * \date 5 décembre 2024 -> 10 janvier 2025
 */
#include "SAE.h"

/**
 * \brief Fonction qui affiche le menu principal du jeu et demande ce que l'utilisateur veut faire
 * \author CABARET Benjamin
 * 
 * \return Le choix de l'utilisateur
 */
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

/**
 * \brief Fonction qui redirige l'utilisateur en fonction de son choix dans le menu
 * \author CABARET Benjamin
 */
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
                ChargeTabAffichage(choix);
                break;
            }

        case 4: // Afficher le tableau des scores triés par meilleur score
            {   
                ChargeTabAffichage(choix);
                break;
            }

        case 5: // Afficher les statistiques d'un joueur
            {
                ChargeTabAffichage(choix);
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

/**
 * \brief Fonction qui gère entièrement la partie
 * \authors CABARET Benjamin, PICHOT-MOÏSE Mathéo
 * 
 * \param nomFichier Nom du fichier de la partie prédéfinie
 * \param pseudo Pseudo du joueur
 */
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
        printf("Erreur lors de l'ouverture du fichier de partie!\n");
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

/**
 * \brief Fonction qui permet de créer une partie prédéfinie qui sera stocker dans un fichier
 * \author PICHOT-MOÏSE Mathéo
 * 
 * \param nomFichier Nom du fichier dans lequel la partie sera stocker
 */
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

/**
 * \brief Fonction qui permet de gérer les duels
 * \author CABARET Benjamin
 * 
 * \param attaque L'attaque du monstre
 * \param choix Le choix du joueur
 * \param m Structure du monstre correspondant au duel
 */
int victoireDuel(int attaque, char choix, Monstre m) {
    if ((attaque == 1 && choix == 'F') || (attaque == 2 && choix == 'C') || (attaque == 3 && choix == 'P') || (attaque == 5)) {
        return 1;
    }
    if ((attaque == 1 && choix == 'C') || (attaque == 2 && choix == 'P') || (attaque == 3 && choix == 'F') || (attaque == 4)) {
        return 0;
    }
    return -1;
}

/**
 * \brief Fonction qui permet de récuprer le choix du joueur
 * \author CABARET Benjamin
 */
char attaqueJoueur(void) {
    char choix;
    scanf(" %c", &choix);

    while (choix != 'P' && choix != 'C' && choix != 'F') {
        printf("Entrée invalide ! Veuillez entrer P, C ou F : ");
        scanf(" %c", &choix);
    }

    return choix;
}

/**
 * \brief Fonction qui génére aléatoirement une arme pour le monstre
 * \author CABARET Benjamin
 * 
 * \param m Structure du monstre correspondant
 */
int attaqueMonstre(Monstre m) {
    int min = 1, max = (m.niveau == 1 ? 4 : (m.niveau == 2 ? 3 : 5));
    return (rand() % (max - min + 1)) + min;
}

/**
 * \brief Fonction qui permet de charger les joueurs dans le scoreboard
 * \author MIOTTO Quentin
 * 
 * \param choix Le choix du joueur
 */
int ChargeTabAffichage(int choix) {
    FILE * tscore = fopen("Parties/scoreboard.txt", "r");
    if (tscore == NULL)
    {
        printf("pb ouverture de fichier\n");
        return -1;
    }
    
    int nbJoueurs;
    fscanf(tscore, "%d", &nbJoueurs);
    
    int i=0;
    Stats ts[nbJoueurs];

    for (i=0; i<nbJoueurs; i++)
    {
        fscanf(tscore, "%s %d %f %d %d %d", 
                        ts[i].pseudo,
                        &ts[i].meilleurScore,
                        &ts[i].moyenneScores,
                        &ts[i].nbParties,
                        &ts[i].victoire,
                        &ts[i].defaite);
    }

    switch (choix)
    {
    case 3:
        tabParNom(ts,nbJoueurs);
        break;
    case 4:
        tabParScore(ts,nbJoueurs);
        break;
    case 5:
        rechercherJoueur(ts,nbJoueurs);
        break;
    default:
        break;
    }
}

/**
 * \brief Fonction qui permet d'afficher le tableau des scores par nom
 * \author MIOTTO Quentin
 * 
 * \param ts Tableau des stats
 * \param tlog Nombre de joueur dans le tableau
 */
void tabParNom(Stats ts[],int tlog) {
    int choix = 0;
    char lettreCible;
    printf("--------------------------------\n");
    printf("Voulez vous :\n\t1 : Afficher tout le tableau (%d Joueurs)\n\t2 : Afficher ceux commençant par une certaine lettre\n\t3 : Annuler\n",tlog);
    printf("> Choix: ");
    scanf("%d%*c",&choix);
    
    switch (choix)
    {
    case 1:
        triEchangeNom(ts,tlog);
        afficherTableauNom(ts,tlog); // affiche le tableau entier trié par nom
        break;
    case 2:
        printf("> Quelle lettre: ");
        scanf("%c",&lettreCible);
        printf("\n");

        triEchangeNom(ts,tlog);
        affichageLettre(ts,tlog,lettreCible);
        break;
    case 3:
        return;
        break;
    default:
        printf("Choix invalide\n");
        break;
    }
}

/**
 * \brief Fonction qui permet d'afficher le tableau des scores par score
 * \author MIOTTO Quentin
 * 
 * \param ts Tableau des stats
 * \param tlog Nombre de joueur dans le tableau
 */
void tabParScore(Stats ts[],int tlog) {
    int choix = 0;

    if (tlog > 25) // proposer toutes les options si le tableau est plus grand que 25
    {
        printf("--------------------------------\n");
        printf("Voulez vous :\n\t1 : Afficher tout le tableau (%d Joueurs)\n\t2 : Afficher les 10 premiers joueurs\n\t3 : Afficher les 25 premiers joueurs\n\t4 : Afficher les 10 derniers joueurs\n\t5 : Afficher les 25 derniers joueurs\n\t6 : Annuler\n",tlog);
        printf("> Choix: ");
        scanf("%d%*c",&choix);

        switch (choix)
        {
        case 1:
            triEchangeScore(ts,tlog);
            afficherTableauScore(ts,tlog);
            break;
        case 2:
            triEchangeScore(ts,tlog);
            afficherTableauScore(ts,10);
            break;
        case 3:
            triEchangeScore(ts,tlog);
            afficherTableauScore(ts,25);
            break;
        case 4:
            triEchangeScore(ts,tlog);
            afficherDerniers(ts,tlog,10);
            break;
        case 5:
            triEchangeScore(ts,tlog);
            afficherDerniers(ts,tlog,25);
            break;
        case 6:
            break;
        default:
            printf("Choix invalide\n");
            break;
        }
    }
    else if (tlog > 10) // proposer les options pour limiter l'affichage à 10 si le tableau est plus grand que 10
    {
        printf("--------------------------------\n");
        printf("\nVoulez vous :\n\t1 : Afficher tout le tableau (%d Joueurs)\n\t2 : Afficher les 10 premiers joueurs\n\t3 : Afficher les 10 derniers joueurs\n\t4 : Annuler\n",tlog);
        printf("> Choix: ");
        scanf("%d%*c",&choix);

        switch (choix)
        {
        case 1:
            triEchangeScore(ts,tlog);
            afficherTableauScore(ts,tlog);
            break;
        case 2:
            triEchangeScore(ts,tlog);
            afficherTableauScore(ts,10);
            break;
        case 3:
            triEchangeScore(ts,tlog);
            afficherDerniers(ts,tlog,10);
            break;
        case 4:
            break;
        default:
            printf("Choix invalide\n");
            break;
        }
    }
    else
    {                    // proposer seulement l'option afficher tout le tableau puisqu'il est plus petit ou égal à 10
        printf("--------------------------------\n");
        printf("Voulez vous :\n\t1 : Afficher tout le tableau (%d Joueurs)\n\t2 : Annuler\n",tlog);
        printf("> Choix: ");
        scanf("%d%*c",&choix);

        switch (choix)
        {
        case 1:
            triEchangeScore(ts,tlog);
            afficherTableauScore(ts,tlog);
            break;
        case 2:
            break;
        default:
            printf("Choix invalide\n");
            break;
        }
    }
} 

/**
 * \brief Fonction qui permet de rechercher un joueur dans le tableau des scores
 * \author MIOTTO Quentin
 * 
 * \param ts Tableau des stats
 * \param tlog Nombre de joueur dans le tableau
 */
void rechercherJoueur(Stats ts[],int tlog) {
    char cible[20];
    int trouve;
    int i;

    triEchangeNom(ts,tlog);

    printf("> Joueur à afficher : ");
    scanf("%19s",cible);
    trouve = rechercheDichomatique(ts,tlog,cible);

    if (trouve != -1)
        affichageJoueur(ts,tlog,trouve,cible);
    else
        printf("Le Joueur '%s' n'existe pas\n",cible);
}

/**
 * \brief Fonction qui permet d'afficher les statistiques d'un joueur
 * \author MIOTTO Quentin
 * 
 * \param ts Tableau des stats
 * \param tlo Nombre de joueur dans le tableau
 * \param trouve La place du joueur
 * \param cible Le pseudo du joueur
 */
void affichageJoueur(Stats ts[],int tlo, int trouve, char cible[]) {
    printf("--------------------------------\n");
    printf("Statistique du joueur %s : \n\n",cible);
    printf("\tMeilleur Score : %d \n",ts[trouve].meilleurScore);
    printf("\tMoyenne : %.2f \n",ts[trouve].moyenneScores);
    printf("\tNb Parties : %d\n", ts[trouve].nbParties);
    printf("\tVictoire : %d\n", ts[trouve].victoire);
    printf("\tDéfaite : %d\n\n", ts[trouve].defaite);
}

/**
 * \brief Fonction qui permet de renvoyer l'indice (place dans le tableau) du pseudo d'un joueur le plus petit (dans l'ordre alphabetique)
 * \author MIOTTO Quentin
 * 
 * \param tab Tableau des stats
 * \param n Nombre de joueur dans le tableau
 * 
 * \return l'indice du plus petit pseudo d'un joueur
 */
int plusGrandNom(Stats tab[], int n) {
    int pge = 0;
    int i;
    for (i = 0; i < n; i++) 
    {
        if (strcasecmp(tab[i].pseudo, tab[pge].pseudo) > 0) 
        {
            pge = i;
        }
    }
    return pge;
}

/**
 * \brief Fonction qui permet de renvoyer l'indice (place dans le tableau) du Joueur ayant le grand Score
 * \author MIOTTO Quentin
 * 
 * \param ts Tableau des stats
 * \param tlog Nombre de joueur dans le tableau
 * 
 * \return l'indice du Joueur ayant le plus grand Score
 */
int plusGrandScore(Stats tab[],int n) {
    int pge=0;
    int i;
    for (i=0;i<n;i++)
    {
        if (tab[i].meilleurScore<tab[pge].meilleurScore)
        {
            pge = i;
        }
    }
    return pge;
}

/**
 * \brief Fonction qui permet d'échanger 2 éléments dans le tableau des scores
 * \author MIOTTO Quentin
 * 
 * \param tab Tableau des stats
 * \param i Le premier élément à échanger
 * \param j Le second élément à échanger
 */
void echanger(Stats tab[], int i, int j) {
    Stats tmp = tab[j];
    tab[j] = tab[i];
    tab[i] = tmp;
}

/**
 * \brief Fonction qui permet de trier le tableau des stats par nom
 * \author MIOTTO Quentin
 * 
 * \param tab Tableau des stats
 * \param n Nombre de joueur dans le tableau
 */
void triEchangeNom(Stats tab[], int n) {
    int max;
    while (n > 1)
    {
        max = plusGrandNom(tab, n);
        echanger(tab, max, n - 1); 
        n = n - 1;
    }
}

/**
 * \brief Fonction qui permet de trier le tableau des stats par score
 * \author MIOTTO Quentin
 * 
 * \param tab Tableau des stats
 * \param n Nombre de joueur dans le tableau
 */
void triEchangeScore(Stats tab[], int n) {
    int max;
    while (n > 1)
    {
        max = plusGrandScore(tab, n);
        echanger(tab, max, n - 1); 
        n = n - 1;
    }
}

/**
 * \brief Fonction qui permet d'afficher le tableau des scores par score
 * \author MIOTTO Quentin
 * 
 * \param tab Tableau des stats
 * \param tlog Nombre de joueur dans le tableau
 */
void afficherTableauScore(Stats tab[], int tlog) {
    int i;
    printf("--------------------------------\n");
    printf("Tableau des Scores :\n\n");
    for (i = 0; i < tlog; i++)
    {
        if (i==0)
            printf("%4der  | %20s | %10d\n",i+1, tab[i].pseudo, tab[i].meilleurScore);
        else
            printf("%4deme | %20s | %10d\n",i+1, tab[i].pseudo, tab[i].meilleurScore);
    }
    printf("\n");
}

/**
 * \brief Fonction qui permet d'afficher le tableau des scores par nom
 * \author MIOTTO Quentin
 * 
 * \param tab Tableau des stats
 * \param tlog Nombre de joueur dans le tableau
 */
void afficherTableauNom(Stats tab[], int tlog) {
    int i;
    printf("--------------------------------\n");
    printf("Tableau des Scores :\n\n");
    for (i = 0; i < tlog; i++)
    {
        if (i==0)
            printf("%20s | %10d\n", tab[i].pseudo, tab[i].meilleurScore);
        else
            printf("%20s | %10d\n", tab[i].pseudo, tab[i].meilleurScore);
    }
    printf("\n");
}

/**
 * \brief Fonction qui permet d'effectuer une recherche dichomatique dans le tableau des scores
 * \author MIOTTO Quentin
 * 
 * \param tab Tableau des stats
 * \param n Nombre de joueur dans le tableau
 * \param cible Le joueur voulu
 */
int rechercheDichomatique(Stats tab[], int n, char cible[]) {
    int inf = 0;
    int sup = n - 1;
    int mid;
    while (inf <= sup)
    {
        mid = (inf + sup) / 2;

        if (strcmp(tab[mid].pseudo, cible) == 0)
            return mid;

        if (strcmp(cible, tab[mid].pseudo) > 0)
            inf = mid + 1;
        else
            sup = mid - 1;
    }
    return -1;
}

/**
 * \brief Fonction qui permet d'afficher tout les pseudo en fonction d'une lettre
 * \author MIOTTO Quentin
 * 
 * \param tab Tableau des stats
 * \param tlog Nombre de joueur dans le tableau
 * \param Lettre La lettre que l'on souhaite chercher
 */
void affichageLettre(Stats tab[], int tlog, char Lettre) {
    int i;
    printf("--------------------------------\n");
    printf("Tableau des Scores :\n\n");
    for (i = 0; i < tlog; i++)
    {
        if (Lettre >= 97) // si minuscule
            if (tab[i].pseudo[0] == Lettre || tab[i].pseudo[0] == Lettre - 32)
            {
                printf("%20s | %10d\n", tab[i].pseudo, tab[i].meilleurScore);
            }
        if (Lettre >= 65 && Lettre <= 90) // si majuscule
            if (tab[i].pseudo[0] == Lettre || tab[i].pseudo[0] == Lettre + 32)
            {
                printf("%20s | %10d\n", tab[i].pseudo, tab[i].meilleurScore);
            }
    }
    printf("\n");
}

/**
 * \brief Fonction qui permet d'afficher le tableau des scores à partir du bas et limiter la taille du tableau afficher en fonction de x
 * \author MIOTTO Quentin
 * 
 * \param ts Tableau des stats
 * \param tlog Nombre de joueur dans le tableau
 * \param x taille du tableau afficher choisis dans le menu par l'utilisateur (10 ou 25)
 */
void afficherDerniers(Stats tab[], int tlog, int x) {
    int i;
    printf("--------------------------------\n");
    printf("Tableau des Scores :\n\n");
    for (i = tlog-x ; i < tlog; i++)
    {
        if (i==0)
            printf("%4der  | %20s | %10d\n",i+1, tab[i].pseudo, tab[i].meilleurScore);
        else
            printf("%4deme | %20s | %10d\n",i+1, tab[i].pseudo, tab[i].meilleurScore);
    }
    printf("\n");
}