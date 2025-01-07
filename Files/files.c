
#include "files.h"

File fileVide(void) {
    File f;
    f.tete = NULL;
    f.queue = NULL;
    return f;
}

File adjq(File f, int x) {
    Maillon *m;
    m = (Maillon *)malloc(sizeof(Maillon));
    if (m == NULL) {
        printf("Problème de malloc\n");
        exit(1);
    }
    m->valeur = x;
    m->suiv = NULL;
    if (estVide(f)) {
        f.tete = m;
        f.queue = m;
        return f;
    }
    f.queue->suiv = m;
    f.queue = m;
    return f;
}

// Supprimer en tête
File supt(File f) {
    if (estVide(f)) {
        printf("La file est vide\n");
        exit(1);
    }
    Maillon *m;
    m = f.tete;
    f.tete = f.tete->suiv;
    if (f.tete == NULL) {
        f.queue = NULL;
    }
    free(m);
    return f;
}

int tete(File f) {
    if (estVide(f)) {
        printf("La file est vide\n");
        exit(1);
    }
    return f.tete->valeur;
}

int longueur(File f) {
    int len = 0;
    Maillon *m = f.tete;
    while (m != NULL) {
        len++;
        m = m->suiv;
    }
    return len;
}

int estVide(File f) {
    return (f.tete == NULL);
}