#include "bibliotheque.h"

/* ================= BIBLIOTHECAIRE ================= */

void ajouterLivre(Livre **livres, int *nbLivres) {
    Livre l;
    Livre *tmp;
    l.id = prochainIdLivre(*livres, *nbLivres);
    lireChaine("Titre: ", l.titre, MAX_TITRE);
    lireChaine("Auteur: ", l.auteur, MAX_AUTEUR);
    lireChaine("Categorie: ", l.categorie, MAX_CATEGORIE);
    l.statut = DISPONIBLE;
    if (chaineVide(l.titre) || chaineVide(l.auteur) || chaineVide(l.categorie)) {
        printf("Ajout refuse: champs obligatoires.\n");
        return;
    }
    tmp = realloc(*livres, (*nbLivres + 1) * sizeof(Livre));
    if (tmp == NULL) {
        printf("Erreur allocation livre.\n");
        return;
    }
    *livres = tmp;
    (*livres)[*nbLivres] = l;
    (*nbLivres)++;
    printf("Livre ajoute avec l'ID %d.\n", l.id);
}

void supprimerLivre(Livre **livres, int *nbLivres, Emprunt *emprunts, int nbEmprunts) {
    int id, idx, i;
    id = lireEntier("ID du livre a supprimer: ");
    idx = trouverLivreParId(*livres, *nbLivres, id);
    if (idx == -1) {
        printf("Livre introuvable.\n");
        return;
    }
    for (i = 0; i < nbEmprunts; i++) {
        if (emprunts[i].idLivre == id) {
            printf("Suppression refusee: ce livre est encore emprunte.\n");
            return;
        }
    }
    for (i = idx; i < *nbLivres - 1; i++) (*livres)[i] = (*livres)[i + 1];
    (*nbLivres)--;
    if (*nbLivres == 0) {
        free(*livres);
        *livres = NULL;
    } else {
        Livre *tmp = realloc(*livres, (*nbLivres) * sizeof(Livre));
        if (tmp != NULL) *livres = tmp;
    }
    printf("Livre supprime.\n");
}

void suspendreReactiverUser(Utilisateur *users, int nbUsers) {
    char login[MAX_LOGIN];
    int idx;
    lireChaine("Login utilisateur: ", login, MAX_LOGIN);
    idx = trouverUserParLogin(users, nbUsers, login);
    if (idx == -1) {
        printf("Utilisateur introuvable.\n");
        return;
    }
    if (users[idx].type == BIBLIOTHECAIRE) {
        printf("Operation refusee sur un bibliothecaire.\n");
        return;
    }
    users[idx].statut = (users[idx].statut == ACTIF) ? SUSPENDU : ACTIF;
    printf("Nouveau statut: %s.\n", statutUserTexte(users[idx].statut));
}

void changerTypeUser(Utilisateur *users, int nbUsers) {
    char login[MAX_LOGIN];
    int idx, type;
    lireChaine("Login utilisateur: ", login, MAX_LOGIN);
    idx = trouverUserParLogin(users, nbUsers, login);
    if (idx == -1) {
        printf("Utilisateur introuvable.\n");
        return;
    }
    printf("0=Etudiant, 1=Professeur, 2=Bibliothecaire\n");
    type = lireEntier("Nouveau type: ");
    if (type < 0 || type > 2) {
        printf("Type invalide.\n");
        return;
    }
    users[idx].type = (TypeUtilisateur)type;
    printf("Type modifie: %s.\n", typeTexte(users[idx].type));
}

void menuBibliothecaire(Livre **livres, int *nbLivres, Utilisateur *users, int nbUsers,
                        Emprunt *emprunts, int nbEmprunts, Historique *hist, int nbHist) {
    int choix;
    do {
        printf(MAGENTA);
        printf("\n┌──────────────────────────────────────────────┐\n");
        printf("│            🛠️  MENU BIBLIOTHÉCAIRE            │\n");
        printf("├──────────────────────────────────────────────┤\n");
        printf("│  1. ➕ Ajouter un livre                      │\n");
        printf("│  2. 🗑️  Supprimer un livre                    │\n");
        printf("│  3. 👥 Afficher les utilisateurs             │\n");
        printf("│  4. 🚫 Suspendre/réactiver un utilisateur    │\n");
        printf("│  5. 🔁 Changer le type d'un utilisateur      │\n");
        printf("│  6. 📚 Afficher les emprunts en cours        │\n");
        printf("│  7. 🕘 Afficher l'historique                 │\n");
        printf("│  0. Retour                                   │\n");
        printf("└──────────────────────────────────────────────┘\n");
        printf(RESET);
        choix = lireEntier("Votre choix: ");
        switch (choix) {
            case 1: ajouterLivre(livres, nbLivres); break;
            case 2: supprimerLivre(livres, nbLivres, emprunts, nbEmprunts); break;
            case 3: afficherUtilisateurs(users, nbUsers); break;
            case 4: suspendreReactiverUser(users, nbUsers); break;
            case 5: changerTypeUser(users, nbUsers); break;
            case 6: {
                int i;
                if (nbEmprunts == 0) printf("Aucun emprunt en cours.\n");
                for (i = 0; i < nbEmprunts; i++) {
                    int idx = trouverLivreParId(*livres, *nbLivres, emprunts[i].idLivre);
                    printf("User: %s | Livre: %s | Rendu prevu: ", emprunts[i].loginUser, idx >= 0 ? (*livres)[idx].titre : "Livre inconnu");
                    afficherDate(emprunts[i].dateRenduPrevue);
                    printf("\n");
                }
                break;
            }
            case 7: afficherHistorique(hist, nbHist, *livres, *nbLivres); break;
            case 0: break;
            default: printf("Choix invalide.\n");
        }
    } while (choix != 0);
}
