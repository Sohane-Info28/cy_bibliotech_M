#include "bibliotheque.h"

void pauseVisuelle(void) {
    printf("\n");
}

/* ================= OUTILS ================= */

void viderBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void retirerRetourLigne(char *s) {
    if (s == NULL) return;
    s[strcspn(s, "\n")] = '\0';
}

void lireChaine(const char *message, char *chaine, int taille) {
    printf("%s", message);
    if (fgets(chaine, taille, stdin) == NULL) {
        chaine[0] = '\0';
        return;
    }
    retirerRetourLigne(chaine);
}

int lireEntier(const char *message) {
    char ligne[64];
    int valeur;
    while (1) {
        printf("%s", message);
        if (fgets(ligne, sizeof(ligne), stdin) == NULL) return 0;
        if (sscanf(ligne, "%d", &valeur) == 1) return valeur;
        printf("Saisie invalide. Reessayez.\n");
    }
}

int chaineVide(const char *s) {
    return s == NULL || s[0] == '\0';
}

int comparerSansCasse(const char *a, const char *b) {
    while (*a && *b) {
        int ca = tolower((unsigned char)*a);
        int cb = tolower((unsigned char)*b);
        if (ca != cb) return ca - cb;
        a++;
        b++;
    }
    return tolower((unsigned char)*a) - tolower((unsigned char)*b);
}

int contientSansCasse(const char *texte, const char *mot) {
    char t[MAX_LIGNE], m[MAX_LIGNE];
    size_t i;
    if (texte == NULL || mot == NULL) return 0;
    snprintf(t, sizeof(t), "%s", texte);
    snprintf(m, sizeof(m), "%s", mot);
    for (i = 0; t[i]; i++) t[i] = (char)tolower((unsigned char)t[i]);
    for (i = 0; m[i]; i++) m[i] = (char)tolower((unsigned char)m[i]);
    return strstr(t, m) != NULL;
}

void afficherDate(time_t date) {
    char buffer[32];
    struct tm *tmInfo = localtime(&date);
    if (tmInfo == NULL) {
        printf("Date inconnue");
        return;
    }
    strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", tmInfo);
    printf("%s", buffer);
}

int minutesEntre(time_t debut, time_t fin) {
    return (int)(difftime(fin, debut) / 60);
}

const char* typeTexte(TypeUtilisateur type) {
    switch (type) {
        case ETUDIANT: return "Etudiant";
        case PROFESSEUR: return "Professeur";
        case BIBLIOTHECAIRE: return "Bibliothecaire";
        default: return "Inconnu";
    }
}

const char* statutUserTexte(StatutUtilisateur statut) {
    return statut == ACTIF ? "Actif" : "Suspendu";
}

const char* statutLivreTexte(StatutLivre statut) {
    return statut == DISPONIBLE ? "Disponible" : "Emprunte";
}

int quotaUtilisateur(TypeUtilisateur type) {
    if (type == ETUDIANT) return QUOTA_ETUDIANT;
    if (type == PROFESSEUR) return QUOTA_PROF;
    return QUOTA_BIBLIOTHECAIRE;
}

int dureeEmprunt(TypeUtilisateur type) {
    if (type == PROFESSEUR || type == BIBLIOTHECAIRE) return DUREE_EMPRUNT_PROF;
    return DUREE_EMPRUNT_ETUDIANT;
}
