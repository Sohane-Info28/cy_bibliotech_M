#include "bibliotheque.h"

/* ================= AFFICHAGES ================= */

void afficherEntete(void) {
    printf(CYAN);
    printf("\n╔════════════════════════════════════════════╗\n");
    printf("║                                            ║\n");
    printf("║      📚  CY-BIBLIOTEQUE  📚                ║\n");
    printf("║                                            ║\n");
    printf("╚════════════════════════════════════════════╝\n");
    printf(RESET);

    printf(JAUNE);
    printf("        Bienvenue dans votre espace lecture\n");
    printf("        Gestion des livres, emprunts et comptes\n\n");
    printf(RESET);
}

void afficherMenuPrincipal(void) {
    printf(VERT);
    printf("┌──────────────────────────────────────────────┐\n");
    printf("│                 MENU PRINCIPAL               │\n");
    printf("├──────────────────────────────────────────────┤\n");
    printf("│  1. 🔐 Se connecter                          │\n");
    printf("│  2. 📝 Créer un compte                       │\n");
    printf("│  3. 📖 Afficher les livres disponibles       │\n");
    printf("│  0. 🚪 Quitter                               │\n");
    printf("└──────────────────────────────────────────────┘\n");
    printf(RESET);
}

void afficherLivre(Livre l) {
    printf("ID: %d | %s | %s | %s | %s\n", l.id, l.titre, l.auteur, l.categorie, statutLivreTexte(l.statut));
}

void afficherLivres(Livre *livres, int nbLivres) {
    int i;
    if (nbLivres == 0) {
        printf("Aucun livre dans la bibliotheque.\n");
        return;
    }
    for (i = 0; i < nbLivres; i++) afficherLivre(livres[i]);
}

void afficherLivresDisponibles(Livre *livres, int nbLivres) {
    int i, trouve = 0;
    if (nbLivres == 0) {
        printf("Aucun livre dans la bibliotheque.\n");
        return;
    }
    for (i = 0; i < nbLivres; i++) {
        if (livres[i].statut == DISPONIBLE) {
            afficherLivre(livres[i]);
            trouve = 1;
        }
    }
    if (!trouve) printf("Aucun livre disponible pour le moment.\n");
}

void afficherUtilisateurs(Utilisateur *users, int nbUsers) {
    int i;
    if (nbUsers == 0) {
        printf("Aucun utilisateur.\n");
        return;
    }
    for (i = 0; i < nbUsers; i++) {
        printf("Login: %s | Type: %s | Emprunts: %d | Statut: %s\n",
               users[i].login, typeTexte(users[i].type), users[i].nbLivresEmpruntes,
               statutUserTexte(users[i].statut));
    }
}

void afficherMesEmprunts(Emprunt *emprunts, int nbEmprunts, Livre *livres, int nbLivres, const char *login) {
    int i, trouve = 0;
    time_t maintenant = time(NULL);
    for (i = 0; i < nbEmprunts; i++) {
        if (strcmp(emprunts[i].loginUser, login) == 0) {
            int idxLivre = trouverLivreParId(livres, nbLivres, emprunts[i].idLivre);
            trouve = 1;
            printf("Livre: %s | Emprunte le: ", idxLivre >= 0 ? livres[idxLivre].titre : "Livre supprime/inconnu");
            afficherDate(emprunts[i].dateEmprunt);
            printf(" | A rendre le: ");
            afficherDate(emprunts[i].dateRenduPrevue);
            if (maintenant > emprunts[i].dateRenduPrevue) {
                printf(" | RETARD: %d minute(s)", minutesEntre(emprunts[i].dateRenduPrevue, maintenant));
            }
            printf("\n");
        }
    }
    if (!trouve) printf("Vous n'avez aucun emprunt en cours.\n");
}

void afficherHistorique(Historique *hist, int nbHist, Livre *livres, int nbLivres) {
    int i;
    if (nbHist == 0) {
        printf("Aucun historique.\n");
        return;
    }
    for (i = 0; i < nbHist; i++) {
        int idx = trouverLivreParId(livres, nbLivres, hist[i].idLivre);
        printf("User: %s | Livre: %s | Emprunt: ", hist[i].loginUser, idx >= 0 ? livres[idx].titre : "Livre inconnu");
        afficherDate(hist[i].dateEmprunt);
        printf(" | Prevu: ");
        afficherDate(hist[i].dateRenduPrevue);
        printf(" | Retour: ");
        afficherDate(hist[i].dateRetourReelle);
        if (hist[i].dateRetourReelle > hist[i].dateRenduPrevue) {
            printf(" | Retard: %d minute(s)", minutesEntre(hist[i].dateRenduPrevue, hist[i].dateRetourReelle));
        }
        printf("\n");
    }
}
