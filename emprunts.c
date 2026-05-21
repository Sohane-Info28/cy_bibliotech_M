#include "bibliotheque.h"

/* ================= EMPRUNTS ================= */

int utilisateurEnRetard(Emprunt *emprunts, int nbEmprunts, const char *login) {
    int i;
    time_t maintenant = time(NULL);
    for (i = 0; i < nbEmprunts; i++) {
        if (strcmp(emprunts[i].loginUser, login) == 0 && maintenant > emprunts[i].dateRenduPrevue) return 1;
    }
    return 0;
}

void emprunterLivre(Livre *livres, int nbLivres, Utilisateur *user,
                    Emprunt **emprunts, int *nbEmprunts) {
    int id, idxLivre;
    time_t maintenant;
    Emprunt *tmp;

    if (user->statut == SUSPENDU) {
        printf("Votre compte est suspendu. Emprunt impossible.\n");
        return;
    }
    if (utilisateurEnRetard(*emprunts, *nbEmprunts, user->login)) {
        printf("Emprunt refuse: vous avez au moins un retard.\n");
        return;
    }
    if (user->nbLivresEmpruntes >= quotaUtilisateur(user->type)) {
        printf("Quota atteint (%d livre(s)).\n", quotaUtilisateur(user->type));
        return;
    }

    afficherLivresDisponibles(livres, nbLivres);
    id = lireEntier("ID du livre a emprunter: ");
    idxLivre = trouverLivreParId(livres, nbLivres, id);
    if (idxLivre == -1) {
        printf("Livre introuvable.\n");
        return;
    }
    if (livres[idxLivre].statut == EMPRUNTE) {
        printf("Ce livre est deja emprunte.\n");
        return;
    }

    tmp = realloc(*emprunts, (*nbEmprunts + 1) * sizeof(Emprunt));
    if (tmp == NULL) {
        printf("Erreur allocation emprunts.\n");
        return;
    }
    *emprunts = tmp;

    maintenant = time(NULL);
    (*emprunts)[*nbEmprunts].idLivre = id;
    snprintf((*emprunts)[*nbEmprunts].loginUser, MAX_LOGIN, "%s", user->login);
    (*emprunts)[*nbEmprunts].dateEmprunt = maintenant;
    (*emprunts)[*nbEmprunts].dateRenduPrevue = maintenant + (time_t)dureeEmprunt(user->type) * 60;
    (*nbEmprunts)++;

    livres[idxLivre].statut = EMPRUNTE;
    user->nbLivresEmpruntes++;

    printf("Emprunt valide. Date limite: ");
    afficherDate(maintenant + (time_t)dureeEmprunt(user->type) * 60);
    printf("\n");
}

void rendreLivre(Livre *livres, int nbLivres, Utilisateur *user,
                 Emprunt **emprunts, int *nbEmprunts,
                 Historique **hist, int *nbHist) {
    int id, idxEmp, idxLivre, i;
    Historique *tmpHist;

    afficherMesEmprunts(*emprunts, *nbEmprunts, livres, nbLivres, user->login);
    id = lireEntier("ID du livre a rendre: ");
    idxEmp = trouverEmprunt(*emprunts, *nbEmprunts, id, user->login);
    if (idxEmp == -1) {
        printf("Vous n'avez pas emprunte ce livre.\n");
        return;
    }
    idxLivre = trouverLivreParId(livres, nbLivres, id);
    if (idxLivre != -1) livres[idxLivre].statut = DISPONIBLE;
    if (user->nbLivresEmpruntes > 0) user->nbLivresEmpruntes--;

    tmpHist = realloc(*hist, (*nbHist + 1) * sizeof(Historique));
    if (tmpHist != NULL) {
        *hist = tmpHist;
        (*hist)[*nbHist].idLivre = (*emprunts)[idxEmp].idLivre;
        snprintf((*hist)[*nbHist].loginUser, MAX_LOGIN, "%s", (*emprunts)[idxEmp].loginUser);
        (*hist)[*nbHist].dateEmprunt = (*emprunts)[idxEmp].dateEmprunt;
        (*hist)[*nbHist].dateRenduPrevue = (*emprunts)[idxEmp].dateRenduPrevue;
        (*hist)[*nbHist].dateRetourReelle = time(NULL);
        (*nbHist)++;
    } else {
        printf("Attention: historique non enregistre faute de memoire.\n");
    }

    for (i = idxEmp; i < *nbEmprunts - 1; i++) {
        (*emprunts)[i] = (*emprunts)[i + 1];
    }
    (*nbEmprunts)--;
    if (*nbEmprunts == 0) {
        free(*emprunts);
        *emprunts = NULL;
    } else {
        Emprunt *tmp = realloc(*emprunts, (*nbEmprunts) * sizeof(Emprunt));
        if (tmp != NULL) *emprunts = tmp;
    }
    printf("Livre rendu avec succes.\n");
}
