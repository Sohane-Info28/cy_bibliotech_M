#include "bibliotheque.h"

/* ================= RECHERCHES INTERNES ================= */

int trouverLivreParId(Livre *livres, int nbLivres, int id) {
    int i;
    for (i = 0; i < nbLivres; i++) {
        if (livres[i].id == id) return i;
    }
    return -1;
}

int trouverUserParLogin(Utilisateur *users, int nbUsers, const char *login) {
    int i;
    for (i = 0; i < nbUsers; i++) {
        if (strcmp(users[i].login, login) == 0) return i;
    }
    return -1;
}

int trouverEmprunt(Emprunt *emprunts, int nbEmprunts, int idLivre, const char *login) {
    int i;
    for (i = 0; i < nbEmprunts; i++) {
        if (emprunts[i].idLivre == idLivre && strcmp(emprunts[i].loginUser, login) == 0) return i;
    }
    return -1;
}

int prochainIdLivre(Livre *livres, int nbLivres) {
    int i, max = 0;
    for (i = 0; i < nbLivres; i++) if (livres[i].id > max) max = livres[i].id;
    return max + 1;
}
