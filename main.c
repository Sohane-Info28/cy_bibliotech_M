#include "bibliotheque.h"

int main(void) {
    Livre *livres = NULL;
    Utilisateur *users = NULL;
    Emprunt *emprunts = NULL;
    Historique *hist = NULL;
    int nbLivres, nbUsers, nbEmprunts, nbHist;
    int choix, idx;

    nbLivres = chargerLivres(&livres);
    nbUsers = chargerUtilisateurs(&users);
    nbEmprunts = chargerEmprunts(&emprunts);
    nbHist = chargerHistorique(&hist);
    creerCompteBibliothecaireSiAbsent(&users, &nbUsers);

    do {
        afficherEntete();
        afficherMenuPrincipal();
        choix = lireEntier("Votre choix: ");
        switch (choix) {
            case 1:
                idx = connexion(users, nbUsers);
                if (idx != -1) {
                    menuUtilisateurConnecte(idx, &livres, &nbLivres, users, nbUsers, &emprunts, &nbEmprunts, &hist, &nbHist);
                }
                break;
            case 2:
                inscription(&users, &nbUsers);
                sauvegarderTout(livres, nbLivres, users, nbUsers, emprunts, nbEmprunts, hist, nbHist);
                break;
            case 3:
                afficherLivresDisponibles(livres, nbLivres);
                break;
            case 0:
                sauvegarderTout(livres, nbLivres, users, nbUsers, emprunts, nbEmprunts, hist, nbHist);
                printf("Sauvegarde terminee. Au revoir.\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 0);

    free(livres);
    free(users);
    free(emprunts);
    free(hist);
    return 0;
}
