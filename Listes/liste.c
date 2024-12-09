
#include "liste.h"

Liste listeVide(void) {
    return NULL;
}

Liste insererEnTete(Liste l, int x) {
    Maillon *m;
    m = (Maillon *)malloc(sizeof(Maillon));
    if (m == NULL) {
        printf("Erreur d'allocation de memoire\n");
        exit(1);
    }
    m->valeur=x;
    m->suiv=l;
    return m;
}

Liste inserer(Liste l, int x) {
    if (l == NULL) return insererEnTete(l, x);
    if (x < l->valeur) return insererEnTete(l, x);
    // if (x == l->valeur) return insererEnTete(l, x);
    if (x == l->valeur) return l;
    l->suiv = inserer(l->suiv, x);
    return l;
}

Liste supprimerEnTete(Liste l) {
    Maillon *aux;
    if (l == NULL) {
        printf("Opération interdite\n");
        exit(1);
    }
    aux = l->suiv;
    free(l);
    return aux;
}

Liste supprimer(Liste l, int x) {
    if (l == NULL) return l;
    if (x < l->valeur) return l;
    if (x == l->valeur) return supprimerEnTete(l);
    l->suiv = supprimer(l->suiv, x);
    return l;
}

Liste supprimerEnQueue(Liste l) {
    Maillon *aux;
    if (l == NULL) {
        printf("Operation interdite\n");
        exit(1);
    }
    if (l->suiv == NULL) return supprimerEnTete(l);
    l->suiv = supprimerEnQueue(l->suiv);
    return l;
}

Liste insererEnQueue(Liste l, int x) {
    if (l == NULL) return insererEnTete(l, x);
    l->suiv = insererEnQueue(l->suiv, x);
    return l;
}

Booleen vide(Liste l) {
    return l == NULL;
}

int longueur(Liste l) {
    int longueur=0;
    while (l != NULL) {
        longueur++;
        l = l->suiv;
    }
    return longueur;
}
// Longueur de manière récursive
// int longueur(Liste l) {
//     if (l == NULL) return 0;
//     return 1+longueur(l);
// }

int tete(Liste l) {
    if (vide(l)) {
        printf("Operation interdite\n");
        exit(1);
    }
    return l->valeur;
}

Booleen existe(Liste l, int x) {
    if (l == NULL) return faux;
    if (x < l->valeur) return faux;
    if (x == l->valeur) return vrai;
    return existe(l->suiv, x);
}

void afficherListe(Liste l) {
    while (l != NULL) {
        printf("%d ", l->valeur);
        l = l->suiv;
    }
    printf("\n");
}