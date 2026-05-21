#include "bibliotheque.h"

/* ================= CHARGEMENT/SAVE ================= */

int chargerLivres(Livre **livres) {
    FILE *f = fopen(FICHIER_LIVRES, "r");
    char ligne[MAX_LIGNE];
    int nb = 0;
    *livres = NULL;
    if (f == NULL) return 0;

    while (fgets(ligne, sizeof(ligne), f)) {
        Livre l;
        char *token;
        retirerRetourLigne(ligne);
        if (chaineVide(ligne)) continue;

        token = strtok(ligne, "|"); if (!token) continue; l.id = atoi(token);
        token = strtok(NULL, "|"); if (!token) continue; snprintf(l.titre, sizeof(l.titre), "%s", token);
        token = strtok(NULL, "|"); if (!token) continue; snprintf(l.auteur, sizeof(l.auteur), "%s", token);
        token = strtok(NULL, "|"); if (!token) continue; snprintf(l.categorie, sizeof(l.categorie), "%s", token);
        token = strtok(NULL, "|"); if (!token) continue; l.statut = (StatutLivre)atoi(token);

        Livre *tmp = realloc(*livres, (nb + 1) * sizeof(Livre));
        if (tmp == NULL) {
            printf("Erreur allocation livres.\n");
            free(*livres);
            *livres = NULL;
            fclose(f);
            return 0;
        }
        *livres = tmp;
        (*livres)[nb++] = l;
    }
    fclose(f);
    return nb;
}

int chargerUtilisateurs(Utilisateur **users) {
    FILE *f = fopen(FICHIER_USERS, "r");
    char ligne[MAX_LIGNE];
    int nb = 0;
    *users = NULL;
    if (f == NULL) return 0;

    while (fgets(ligne, sizeof(ligne), f)) {
        Utilisateur u;
        char *token;
        retirerRetourLigne(ligne);
        if (chaineVide(ligne)) continue;

        token = strtok(ligne, "|"); if (!token) continue; snprintf(u.login, sizeof(u.login), "%s", token);
        token = strtok(NULL, "|"); if (!token) continue; snprintf(u.password, sizeof(u.password), "%s", token);
        token = strtok(NULL, "|"); if (!token) continue; u.type = (TypeUtilisateur)atoi(token);
        token = strtok(NULL, "|"); if (!token) continue; u.nbLivresEmpruntes = atoi(token);
        token = strtok(NULL, "|"); if (!token) u.statut = ACTIF; else u.statut = (StatutUtilisateur)atoi(token);

        Utilisateur *tmp = realloc(*users, (nb + 1) * sizeof(Utilisateur));
        if (tmp == NULL) {
            printf("Erreur allocation utilisateurs.\n");
            free(*users);
            *users = NULL;
            fclose(f);
            return 0;
        }
        *users = tmp;
        (*users)[nb++] = u;
    }
    fclose(f);
    return nb;
}

int chargerEmprunts(Emprunt **emprunts) {
    FILE *f = fopen(FICHIER_EMPRUNTS, "r");
    char ligne[MAX_LIGNE];
    int nb = 0;
    *emprunts = NULL;
    if (f == NULL) return 0;

    while (fgets(ligne, sizeof(ligne), f)) {
        Emprunt e;
        char *token;
        retirerRetourLigne(ligne);
        if (chaineVide(ligne)) continue;

        token = strtok(ligne, "|"); if (!token) continue; e.idLivre = atoi(token);
        token = strtok(NULL, "|"); if (!token) continue; snprintf(e.loginUser, sizeof(e.loginUser), "%s", token);
        token = strtok(NULL, "|"); if (!token) continue; e.dateEmprunt = (time_t)atoll(token);
        token = strtok(NULL, "|"); if (!token) continue; e.dateRenduPrevue = (time_t)atoll(token);

        Emprunt *tmp = realloc(*emprunts, (nb + 1) * sizeof(Emprunt));
        if (tmp == NULL) {
            printf("Erreur allocation emprunts.\n");
            free(*emprunts);
            *emprunts = NULL;
            fclose(f);
            return 0;
        }
        *emprunts = tmp;
        (*emprunts)[nb++] = e;
    }
    fclose(f);
    return nb;
}

int chargerHistorique(Historique **hist) {
    FILE *f = fopen(FICHIER_HISTORIQUE, "r");
    char ligne[MAX_LIGNE];
    int nb = 0;
    *hist = NULL;
    if (f == NULL) return 0;

    while (fgets(ligne, sizeof(ligne), f)) {
        Historique h;
        char *token;
        retirerRetourLigne(ligne);
        if (chaineVide(ligne)) continue;

        token = strtok(ligne, "|"); if (!token) continue; h.idLivre = atoi(token);
        token = strtok(NULL, "|"); if (!token) continue; snprintf(h.loginUser, sizeof(h.loginUser), "%s", token);
        token = strtok(NULL, "|"); if (!token) continue; h.dateEmprunt = (time_t)atoll(token);
        token = strtok(NULL, "|"); if (!token) continue; h.dateRenduPrevue = (time_t)atoll(token);
        token = strtok(NULL, "|"); if (!token) continue; h.dateRetourReelle = (time_t)atoll(token);

        Historique *tmp = realloc(*hist, (nb + 1) * sizeof(Historique));
        if (tmp == NULL) {
            printf("Erreur allocation historique.\n");
            free(*hist);
            *hist = NULL;
            fclose(f);
            return 0;
        }
        *hist = tmp;
        (*hist)[nb++] = h;
    }
    fclose(f);
    return nb;
}

int sauvegarderLivres(Livre *livres, int nbLivres) {
    FILE *f = fopen(FICHIER_LIVRES, "w");
    int i;
    if (f == NULL) return 0;
    for (i = 0; i < nbLivres; i++) {
        fprintf(f, "%d|%s|%s|%s|%d\n", livres[i].id, livres[i].titre, livres[i].auteur, livres[i].categorie, livres[i].statut);
    }
    fclose(f);
    return 1;
}

int sauvegarderUtilisateurs(Utilisateur *users, int nbUsers) {
    FILE *f = fopen(FICHIER_USERS, "w");
    int i;
    if (f == NULL) return 0;
    for (i = 0; i < nbUsers; i++) {
        fprintf(f, "%s|%s|%d|%d|%d\n", users[i].login, users[i].password, users[i].type, users[i].nbLivresEmpruntes, users[i].statut);
    }
    fclose(f);
    return 1;
}

int sauvegarderEmprunts(Emprunt *emprunts, int nbEmprunts) {
    FILE *f = fopen(FICHIER_EMPRUNTS, "w");
    int i;
    if (f == NULL) return 0;
    for (i = 0; i < nbEmprunts; i++) {
        fprintf(f, "%d|%s|%lld|%lld\n", emprunts[i].idLivre, emprunts[i].loginUser,
                (long long)emprunts[i].dateEmprunt, (long long)emprunts[i].dateRenduPrevue);
    }
    fclose(f);
    return 1;
}

int sauvegarderHistorique(Historique *hist, int nbHist) {
    FILE *f = fopen(FICHIER_HISTORIQUE, "w");
    int i;
    if (f == NULL) return 0;
    for (i = 0; i < nbHist; i++) {
        fprintf(f, "%d|%s|%lld|%lld|%lld\n", hist[i].idLivre, hist[i].loginUser,
                (long long)hist[i].dateEmprunt, (long long)hist[i].dateRenduPrevue,
                (long long)hist[i].dateRetourReelle);
    }
    fclose(f);
    return 1;
}

void sauvegarderTout(Livre *livres, int nbLivres, Utilisateur *users, int nbUsers,
                     Emprunt *emprunts, int nbEmprunts, Historique *hist, int nbHist) {
    int ok = 1;
    ok &= sauvegarderLivres(livres, nbLivres);
    ok &= sauvegarderUtilisateurs(users, nbUsers);
    ok &= sauvegarderEmprunts(emprunts, nbEmprunts);
    ok &= sauvegarderHistorique(hist, nbHist);
    if (!ok) printf("Attention: une sauvegarde a echoue.\n");
}

void creerCompteBibliothecaireSiAbsent(Utilisateur **users, int *nbUsers) {
    if (trouverUserParLogin(*users, *nbUsers, "admin") == -1) {
        Utilisateur *tmp = realloc(*users, (*nbUsers + 1) * sizeof(Utilisateur));
        if (tmp == NULL) return;
        *users = tmp;
        snprintf((*users)[*nbUsers].login, MAX_LOGIN, "admin");
        snprintf((*users)[*nbUsers].password, MAX_PASSWORD, "admin");
        (*users)[*nbUsers].type = BIBLIOTHECAIRE;
        (*users)[*nbUsers].nbLivresEmpruntes = 0;
        (*users)[*nbUsers].statut = ACTIF;
        (*nbUsers)++;
        printf("Compte bibliothecaire cree: login admin / mdp admin\n");
    }
}
