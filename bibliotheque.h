#ifndef BIBLIOTHEQUE_H
#define BIBLIOTHEQUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

/* ================= INTERFACE COULEURS ================= */
#define RESET   "\033[0m"
#define CYAN    "\033[1;36m"
#define VERT    "\033[1;32m"
#define JAUNE   "\033[1;33m"
#define ROUGE   "\033[1;31m"
#define BLEU    "\033[1;34m"
#define MAGENTA "\033[1;35m"



#define FICHIER_LIVRES "livres.txt"
#define FICHIER_USERS "users.txt"
#define FICHIER_EMPRUNTS "emprunts.txt"
#define FICHIER_HISTORIQUE "historique.txt"

#define MAX_TITRE 100
#define MAX_AUTEUR 100
#define MAX_CATEGORIE 50
#define MAX_LOGIN 50
#define MAX_PASSWORD 50
#define MAX_LIGNE 512

#define DUREE_EMPRUNT_ETUDIANT 2
#define DUREE_EMPRUNT_PROF 3
#define QUOTA_ETUDIANT 3
#define QUOTA_PROF 5
#define QUOTA_BIBLIOTHECAIRE 20

typedef enum { ETUDIANT = 0, PROFESSEUR = 1, BIBLIOTHECAIRE = 2 } TypeUtilisateur;
typedef enum { DISPONIBLE = 0, EMPRUNTE = 1 } StatutLivre;
typedef enum { ACTIF = 0, SUSPENDU = 1 } StatutUtilisateur;

typedef struct {
    int id;
    char titre[MAX_TITRE];
    char auteur[MAX_AUTEUR];
    char categorie[MAX_CATEGORIE];
    StatutLivre statut;
} Livre;

typedef struct {
    char login[MAX_LOGIN];
    char password[MAX_PASSWORD];
    TypeUtilisateur type;
    int nbLivresEmpruntes;
    StatutUtilisateur statut;
} Utilisateur;

typedef struct {
    int idLivre;
    char loginUser[MAX_LOGIN];
    time_t dateEmprunt;
    time_t dateRenduPrevue;
} Emprunt;

typedef struct {
    int idLivre;
    char loginUser[MAX_LOGIN];
    time_t dateEmprunt;
    time_t dateRenduPrevue;
    time_t dateRetourReelle;
} Historique;

void pauseVisuelle(void);
void viderBuffer(void);
void retirerRetourLigne(char *s);
void lireChaine(const char *message, char *chaine, int taille);
int lireEntier(const char *message);
int chaineVide(const char *s);
int comparerSansCasse(const char *a, const char *b);
int contientSansCasse(const char *texte, const char *mot);
void afficherDate(time_t date);
int minutesEntre(time_t debut, time_t fin);
const char* typeTexte(TypeUtilisateur type);
const char* statutUserTexte(StatutUtilisateur statut);
const char* statutLivreTexte(StatutLivre statut);
int quotaUtilisateur(TypeUtilisateur type);
int dureeEmprunt(TypeUtilisateur type);
int trouverLivreParId(Livre *livres, int nbLivres, int id);
int trouverUserParLogin(Utilisateur *users, int nbUsers, const char *login);
int trouverEmprunt(Emprunt *emprunts, int nbEmprunts, int idLivre, const char *login);
int prochainIdLivre(Livre *livres, int nbLivres);
void afficherEntete(void);
void afficherMenuPrincipal(void);
void afficherLivre(Livre l);
void afficherLivres(Livre *livres, int nbLivres);
void afficherLivresDisponibles(Livre *livres, int nbLivres);
void afficherUtilisateurs(Utilisateur *users, int nbUsers);
void afficherMesEmprunts(Emprunt *emprunts, int nbEmprunts, Livre *livres, int nbLivres, const char *login);
void afficherHistorique(Historique *hist, int nbHist, Livre *livres, int nbLivres);
int chargerLivres(Livre **livres);
int chargerUtilisateurs(Utilisateur **users);
int chargerEmprunts(Emprunt **emprunts);
int chargerHistorique(Historique **hist);
int sauvegarderLivres(Livre *livres, int nbLivres);
int sauvegarderUtilisateurs(Utilisateur *users, int nbUsers);
int sauvegarderEmprunts(Emprunt *emprunts, int nbEmprunts);
int sauvegarderHistorique(Historique *hist, int nbHist);
void sauvegarderTout(Livre *livres, int nbLivres, Utilisateur *users, int nbUsers, Emprunt *emprunts, int nbEmprunts, Historique *hist, int nbHist);
void creerCompteBibliothecaireSiAbsent(Utilisateur **users, int *nbUsers);
int inscription(Utilisateur **users, int *nbUsers);
int connexion(Utilisateur *users, int nbUsers);
int utilisateurEnRetard(Emprunt *emprunts, int nbEmprunts, const char *login);
void emprunterLivre(Livre *livres, int nbLivres, Utilisateur *user, Emprunt **emprunts, int *nbEmprunts);
void rendreLivre(Livre *livres, int nbLivres, Utilisateur *user, Emprunt **emprunts, int *nbEmprunts, Historique **hist, int *nbHist);
void rechercherParCategorie(Livre *livres, int nbLivres);
void rechercherParAuteur(Livre *livres, int nbLivres);
void rechercherParTitre(Livre *livres, int nbLivres);
void trierLivresParTitre(Livre *livres, int nbLivres);
void trierLivresParAuteur(Livre *livres, int nbLivres);
void afficherLivresDisponiblesTries(Livre *livres, int nbLivres, int parAuteur);
void menuRechercheTri(Livre *livres, int nbLivres);
void ajouterLivre(Livre **livres, int *nbLivres);
void supprimerLivre(Livre **livres, int *nbLivres, Emprunt *emprunts, int nbEmprunts);
void suspendreReactiverUser(Utilisateur *users, int nbUsers);
void changerTypeUser(Utilisateur *users, int nbUsers);
void menuBibliothecaire(Livre **livres, int *nbLivres, Utilisateur *users, int nbUsers, Emprunt *emprunts, int nbEmprunts, Historique *hist, int nbHist);
void menuUtilisateurConnecte(int idxUser, Livre **livres, int *nbLivres, Utilisateur *users, int nbUsers, Emprunt **emprunts, int *nbEmprunts, Historique **hist, int *nbHist);

#endif
