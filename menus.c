#include "bibliotheque.h"

/* ================= MENUS ================= */

void menuUtilisateurConnecte(int idxUser, Livre **livres, int *nbLivres, Utilisateur *users, int nbUsers,
                             Emprunt **emprunts, int *nbEmprunts, Historique **hist, int *nbHist) {
    int choix;
    Utilisateur *user = &users[idxUser];
    do {
        printf(CYAN);
        printf("\n┌──────────────────────────────────────────────┐\n");
        printf("│              👤 ESPACE UTILISATEUR           │\n");
        printf("├──────────────────────────────────────────────┤\n");
        printf("│  Connecté : %-15s | %-14s │\n", user->login, typeTexte(user->type));
        printf("├──────────────────────────────────────────────┤\n");
        printf("│  1. 📚 Afficher les livres                   │\n");
        printf("│  2. 🔎 Recherche et tri                      │\n");
        printf("│  3. 📖 Emprunter un livre                    │\n");
        printf("│  4. ✅ Rendre un livre                       │\n");
        printf("│  5. 🧾 Mes emprunts                          │\n");
        if (user->type == PROFESSEUR) printf("│  6. ➕ Ajouter un livre (professeur)         │\n");
        if (user->type == BIBLIOTHECAIRE) printf("│  6. 🛠️  Menu bibliothécaire                   │\n");
        printf("│  9. 💾 Sauvegarder                           │\n");
        printf("│  0. 🚪 Déconnexion                           │\n");
        printf("└──────────────────────────────────────────────┘\n");
        printf(RESET);
        choix = lireEntier("Votre choix: ");
        switch (choix) {
            case 1: afficherLivres(*livres, *nbLivres); break;
            case 2: menuRechercheTri(*livres, *nbLivres); break;
            case 3: emprunterLivre(*livres, *nbLivres, user, emprunts, nbEmprunts); break;
            case 4: rendreLivre(*livres, *nbLivres, user, emprunts, nbEmprunts, hist, nbHist); break;
            case 5: afficherMesEmprunts(*emprunts, *nbEmprunts, *livres, *nbLivres, user->login); break;
            case 6:
                if (user->type == PROFESSEUR) {
                    ajouterLivre(livres, nbLivres);
                    printf("Livre ajoute par un professeur. Pensez a sauvegarder.\n");
                } else if (user->type == BIBLIOTHECAIRE) {
                    menuBibliothecaire(livres, nbLivres, users, nbUsers, *emprunts, *nbEmprunts, *hist, *nbHist);
                } else {
                    printf("Acces refuse: reserve au professeur ou au bibliothecaire.\n");
                }
                break;
            case 9:
                sauvegarderTout(*livres, *nbLivres, users, nbUsers, *emprunts, *nbEmprunts, *hist, *nbHist);
                printf("Sauvegarde effectuee.\n");
                break;
            case 0: break;
            default: printf("Choix invalide.\n");
        }
    } while (choix != 0);
}
