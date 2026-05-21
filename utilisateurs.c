#include "bibliotheque.h"

/* ================= CONNEXION/INSCRIPTION ================= */

int inscription(Utilisateur **users, int *nbUsers) {
    Utilisateur u;
    char confirmation[MAX_PASSWORD];

    lireChaine("Choisissez un login: ", u.login, MAX_LOGIN);
    if (chaineVide(u.login)) {
        printf("Login vide refuse.\n");
        return -1;
    }
    if (trouverUserParLogin(*users, *nbUsers, u.login) != -1) {
        printf("Ce login existe deja.\n");
        return -1;
    }
    lireChaine("Choisissez un mot de passe: ", u.password, MAX_PASSWORD);
    lireChaine("Confirmez le mot de passe: ", confirmation, MAX_PASSWORD);
    if (strcmp(u.password, confirmation) != 0) {
        printf("Les mots de passe ne correspondent pas.\n");
        return -1;
    }

    printf("Type de compte: 0=Etudiant, 1=Professeur\n");
    u.type = (lireEntier("Votre choix: ") == 1) ? PROFESSEUR : ETUDIANT;
    u.nbLivresEmpruntes = 0;
    u.statut = ACTIF;

    Utilisateur *tmp = realloc(*users, (*nbUsers + 1) * sizeof(Utilisateur));
    if (tmp == NULL) {
        printf("Erreur allocation pendant l'inscription.\n");
        return -1;
    }
    *users = tmp;
    (*users)[*nbUsers] = u;
    (*nbUsers)++;
    printf("Compte cree avec succes. Vous pouvez maintenant vous connecter.\n");
    return *nbUsers - 1;
}

int connexion(Utilisateur *users, int nbUsers) {
    char login[MAX_LOGIN], password[MAX_PASSWORD];
    int idx;
    lireChaine("Login: ", login, MAX_LOGIN);
    lireChaine("Mot de passe: ", password, MAX_PASSWORD);
    idx = trouverUserParLogin(users, nbUsers, login);
    if (idx == -1 || strcmp(users[idx].password, password) != 0) {
        printf("Login ou mot de passe incorrect.\n");
        return -1;
    }
    if (users[idx].statut == SUSPENDU) {
        printf("Compte suspendu. Contactez un bibliothecaire.\n");
        return -1;
    }
    printf("Connexion reussie. Bienvenue %s (%s).\n", users[idx].login, typeTexte(users[idx].type));
    return idx;
}
