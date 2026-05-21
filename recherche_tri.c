#include "bibliotheque.h"

/* ================= RECHERCHE ET TRI ================= */

void rechercherParCategorie(Livre *livres, int nbLivres) {
    char categorie[MAX_CATEGORIE];
    int i, trouve = 0;
    lireChaine("Categorie recherchee: ", categorie, MAX_CATEGORIE);
    for (i = 0; i < nbLivres; i++) {
        if (contientSansCasse(livres[i].categorie, categorie)) {
            afficherLivre(livres[i]);
            trouve = 1;
        }
    }
    if (!trouve) printf("Aucun livre trouve pour cette categorie.\n");
}

void rechercherParAuteur(Livre *livres, int nbLivres) {
    char auteur[MAX_AUTEUR];
    int i, trouve = 0;
    lireChaine("Auteur recherche: ", auteur, MAX_AUTEUR);
    for (i = 0; i < nbLivres; i++) {
        if (contientSansCasse(livres[i].auteur, auteur)) {
            afficherLivre(livres[i]);
            trouve = 1;
        }
    }
    if (!trouve) printf("Aucun livre trouve pour cet auteur.\n");
}

void rechercherParTitre(Livre *livres, int nbLivres) {
    char titre[MAX_TITRE];
    int i, trouve = 0;
    lireChaine("Titre recherche: ", titre, MAX_TITRE);
    for (i = 0; i < nbLivres; i++) {
        if (contientSansCasse(livres[i].titre, titre)) {
            afficherLivre(livres[i]);
            trouve = 1;
        }
    }
    if (!trouve) printf("Aucun livre trouve pour ce titre.\n");
}

void trierLivresParTitre(Livre *livres, int nbLivres) {
    int i, j;
    for (i = 0; i < nbLivres - 1; i++) {
        for (j = 0; j < nbLivres - i - 1; j++) {
            if (comparerSansCasse(livres[j].titre, livres[j + 1].titre) > 0) {
                Livre temp = livres[j];
                livres[j] = livres[j + 1];
                livres[j + 1] = temp;
            }
        }
    }
    printf("Tous les livres tries par titre.\n");
    afficherLivres(livres, nbLivres);
}

void trierLivresParAuteur(Livre *livres, int nbLivres) {
    int i, j;
    for (i = 0; i < nbLivres - 1; i++) {
        for (j = 0; j < nbLivres - i - 1; j++) {
            int cmpAuteur = comparerSansCasse(livres[j].auteur, livres[j + 1].auteur);
            if (cmpAuteur > 0 || (cmpAuteur == 0 && comparerSansCasse(livres[j].titre, livres[j + 1].titre) > 0)) {
                Livre temp = livres[j];
                livres[j] = livres[j + 1];
                livres[j + 1] = temp;
            }
        }
    }
    printf("Tous les livres tries par auteur.\n");
    afficherLivres(livres, nbLivres);
}

void afficherLivresDisponiblesTries(Livre *livres, int nbLivres, int parAuteur) {
    int i, j, nbDispo = 0;
    Livre *disponibles = NULL;

    for (i = 0; i < nbLivres; i++) {
        if (livres[i].statut == DISPONIBLE) nbDispo++;
    }

    if (nbDispo == 0) {
        printf("Aucun livre disponible pour le moment.\n");
        return;
    }

    disponibles = malloc(nbDispo * sizeof(Livre));
    if (disponibles == NULL) {
        printf("Erreur allocation pendant le tri.\n");
        return;
    }

    j = 0;
    for (i = 0; i < nbLivres; i++) {
        if (livres[i].statut == DISPONIBLE) disponibles[j++] = livres[i];
    }

    for (i = 0; i < nbDispo - 1; i++) {
        for (j = 0; j < nbDispo - i - 1; j++) {
            int doitEchanger;
            if (parAuteur) {
                int cmpAuteur = comparerSansCasse(disponibles[j].auteur, disponibles[j + 1].auteur);
                doitEchanger = (cmpAuteur > 0 || (cmpAuteur == 0 && comparerSansCasse(disponibles[j].titre, disponibles[j + 1].titre) > 0));
            } else {
                doitEchanger = (comparerSansCasse(disponibles[j].titre, disponibles[j + 1].titre) > 0);
            }
            if (doitEchanger) {
                Livre temp = disponibles[j];
                disponibles[j] = disponibles[j + 1];
                disponibles[j + 1] = temp;
            }
        }
    }

    printf("Livres disponibles tries par %s.\n", parAuteur ? "auteur" : "titre");
    afficherLivres(disponibles, nbDispo);
    free(disponibles);
}

void menuRechercheTri(Livre *livres, int nbLivres) {
    int choix;
    do {
        printf(BLEU);
        printf("\n┌──────────────────────────────────────────────┐\n");
        printf("│              🔎 RECHERCHE ET TRI             │\n");
        printf("├──────────────────────────────────────────────┤\n");
        printf("│  1. Rechercher par catégorie                 │\n");
        printf("│  2. Rechercher par auteur                    │\n");
        printf("│  3. Rechercher par titre                     │\n");
        printf("│  4. Afficher tous les livres par titre       │\n");
        printf("│  5. Afficher tous les livres par auteur      │\n");
        printf("│  6. Livres disponibles par titre             │\n");
        printf("│  7. Livres disponibles par auteur            │\n");
        printf("│  0. Retour                                   │\n");
        printf("└──────────────────────────────────────────────┘\n");
        printf(RESET);
        choix = lireEntier("Votre choix: ");
        switch (choix) {
            case 1: rechercherParCategorie(livres, nbLivres); break;
            case 2: rechercherParAuteur(livres, nbLivres); break;
            case 3: rechercherParTitre(livres, nbLivres); break;
            case 4: trierLivresParTitre(livres, nbLivres); break;
            case 5: trierLivresParAuteur(livres, nbLivres); break;
            case 6: afficherLivresDisponiblesTries(livres, nbLivres, 0); break;
            case 7: afficherLivresDisponiblesTries(livres, nbLivres, 1); break;
            case 0: break;
            default: printf("Choix invalide.\n");
        }
    } while (choix != 0);
}
