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
            char nomFichier[20];
            printf("Donnez le nom du fichier: ");
            scanf("%s", nomFichier);
            creerNouvellePartie(nomFichier);
            break;

        case 3: // Afficher le tableau des scores triés par nom
            break;
            
        case 4: // Afficher le tableau des scores triés par meilleur score
            break;

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

void jouerPartiePredifinie(char* nomFichier) { 
    pvJ = j.pointsDeVie;

    while(pvJ > 0)
        return ;
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

        // Écrire les détails du monstre
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


//--------------------| generation aléatoire & attaques |------------------//

int attaqueMonstre(Monstre m){
    int attaque;
    int min, max;
    
    if(m.niveau == 1) {
        min = 1;
        max = 4;
    }
    if(m.niveau == 2) {
        min = 1;
        max = 3;
    }
    if(m.niveau == 3) {
        min = 1;
        max = 5;
    }

    srand(time(NULL));//initie le générateur de rnd
    attaque = (rand() % (max - min + 1)) + min;
    return attaque;
}

char attaqueJoueur(void){
    char choix;

    printf("Avec quelle arme voulez vous vous battre ?\t P.pierre, F.feuille, C.ciseaux\n");
    scanf("%c%*c", &choix);
    
    while(choix != 'P' || choix != 'C' || choix != 'F')
    {
        printf("Vous seriez prié d'entrer une valeur valide : P, C ou F\n");
        scanf("%c%*c" , choix);
    }
    return choix;
}


//--------------------| condition de victoire |------------------//

//return 1 joueur gagne | 0 monstre gagne | -1 égalité
int victoireDuel(int attaque , char choix , Monstre m){//comparer le chiffre généré aléatoirement avec la lettre que le joueur écrira
    /*1 = Pierre
    2 = Feuille
    3 = Ciseaux
    4 = # = Bonne
    5 = O = Mauvaise
    les numeros sont générés alétoirement pour donner l'attaque du monstre*/

    if(m.niveau == 1)
    {
        //victoire du joueur
        if( ( attaque == 1 && choix == 'F' ) || ( attaque == 2 && choix == 'C') || ( attaque == 3 && choix == 'P' ) || attaque == '5')
            return 1;

        //victoire du monstre
        if( ( attaque == 1 && choix == 'C' ) || ( attaque == 2 && choix == 'P' ) || ( attaque == 3 && choix == 'F' ) )
            return 0;

        //égalité
        if( ( attaque == 1 && choix == 'P' ) || ( attaque == 2 && choix == 'F' ) || ( attaque == 3 && choix == 'C' ) )
            return;
    }
    else if (m.niveau == 2)
    {
        //victoire du joueur
        if( ( attaque == 1 && choix == 'F' ) || ( attaque == 2 && choix == 'C') || ( attaque == 3 && choix == 'P' ) )
            return 1;

        //victoire du monstre
        if( ( attaque == 1 && choix == 'C' ) || ( attaque == 2 && choix == 'P' ) || ( attaque == 3 && choix == 'F' ) )
            return 0;

        //égalité
        if( ( attaque == 1 && choix == 'P' ) || ( attaque == 2 && choix == 'F' ) || ( attaque == 3 && choix == 'C' ) )
            return;
    }
    else if (m.niveau == 3)
    {
        //victoire du joueur
        if( ( attaque == 1 && choix == 'F' ) || ( attaque == 2 && choix == 'C') || ( attaque == 3 && choix == 'P' ) || ( attaque == '5' ))
            return 1;

        //victoire du monstre
        if( ( attaque == 1 && choix == 'C' ) || ( attaque == 2 && choix == 'P' ) || ( attaque == 3 && choix == 'F' ) || ( attaque == '4' ) )
            return 0;

        //égalité
        if( ( attaque == 1 && choix == 'P' ) || ( attaque == 2 && choix == 'F' ) || ( attaque == 3 && choix == 'C' ) )
            return;  
    }
}

void retraitPV(Joueur j , Monstre m){
    int var;
    int attaque;
    char choix;
    var = victoireDuel(attaque, choix, m);

    if(var == 1)//le joueur a gagné le duel
    {
        m.pointsDeVie = m.pointsDeVie - j.degatsParAttaque;
        return m.pointsDeVie;
    }
    if(var == 0)//le monstre a gagné le duel
    {
        j.pointsDeVie = j.pointsDeVie - m.degatsParAttaque;
        return j.pointsDeVie;
    }
}

// int estMort(Joueur j , Monstre m){
//     //-1 monstre mort , -2 joueur mort
//     int pvM = m.pointsDeVie;
//     int pvJ = j.pointsDeVie;

//     if (pvM == 0)
//     {
//         printf("monstre mort.\n");
//         return -1;
//     }
//     if (pvJ == 0)
//     {
//         printf("Vous êtes mort, peut être une prochaine fois...\n");
//         return -2;
//     }
// }

int points(Monstre m){
    int scoreActuel = 0;
    int attaque;
    char choix;
    int gagne;//recupère la valeur a l'issue d'un duel
    gagne = victoireDuel(attaque , choix, m);

    if(gagne == 1)
        scoreActuel = scoreActuel + 10;

    if (m.groupe == 1 && m.pointsDeVie >= 0)
    {
        m.pointsDeVie = 0;
        scoreActuel = scoreActuel + 50 * m.niveau;
    }

    if (m.groupe == 2 && m.pointsDeVie >= 0)
    {
        m.pointsDeVie = 0;
        scoreActuel = scoreActuel + 100 * m.niveau;
    }
    return scoreActuel;
}




//cette partie contient les fonctions "code de triche"

void konami(void){
    //uuddlrlrba + "\0" -> 11 caractères
    char tab[11];
    char code[11] = "uuddlrlrba";

    scanf("%s" , tab);
    if ( strcomp(tab , code) == 0)
    {
        printf('You found glasses, it increase you accuracy, you can now deal critical damage !\n');
        printf("         ________     ________\n   . - ~|        |-^-|        |~ - .\n {      |        |   |        |      }\n         `.____.'     `.____.'\n");
        //appliquer le pouvoir
    }
    return;
}

int critique(Joueur j){//a 15% de faire degat *2
    int nombre;
    int min = 1;
    int max = 100;

    srand(time(NULL));//initie le générateur de rnd
    nombre = (rand() % (max - min + 1)) + min;
    if(nombre > 0 || nombre <= 15)
        j.degatsParAttaque = j.degatsParAttaque * 2;
    return j.degatsParAttaque;
}

void soin(void){
    //heal + "\0" -> 5 caractères
    char tab[5];
    char code[5] = "heal";

    scanf("%s" , tab);
    if ( strcmp(tab , code) == 0)
        printf('You found a potion and healed yourself ! <3\n');
    return;
}

void degat(void){
    //damage + "\0" -> 7 caractères
    char tab[7];
    char code[7] = "damage";

    scanf("%s" , tab);
    if ( strcmp(tab , code) == 0)
    {
        //appliquer un buff
        printf("You are now stronger ! \n");
    }
    return;
}




//--------------------| Affichage |------------------//

