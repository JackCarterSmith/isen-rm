#include "db.h"

#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

typedef struct stat_pc {  //Structure de booleens. Chaque variable prend 1 si le PC comporte le module correspondant.
    int Materiel;
    int Os;
    int Drivers;
    int Software;
}STAT;

typedef struct log { // Historique des actions de l'utilisateur depuis le menu.
    int Annee;
    int Mois;
    int Jour;
    int Heure;
    int Minute;
    int Seconde;
}LOG;

typedef struct login {
    char UserName[11];
    char PassWord[11];
}LOGIN;


// functions public

int CmptPcRep(LOG L[], int Rep); //La fonction renvoie le nombre de PC réparés depuis le début de l'annee

// functions privées ;

int compareLogin(char *fichierLogin);
int CmptPcExp(STAT A[], int taille, int Exp); //La fonction balaye la liste des PC et compte le nombre de pc répondant aux critères d'expédition grace à la struct STAT
void BackupDB();
int ajoutFichePC(FICHE *pp, STAT *A, int taille, int Exp);
int supprimePC(FICHE *F, char *ID); // suppression de fiche
int retrogradePC(); //fonction qui permet de retirer un pc de son etat expédiable


#endif // HEADER_H_INCLUDED

int CmptPcRep(LOG L[], int Rep); //La fonction renvoie le nombre de PC réparés depuis le début de l'annee

// functions privées ;

int CmptPcExp(STAT A[], int taille, int Exp); //La fonction balaye la liste des PC et compte le nombre de pc répondant aux critères d'expédition grace à la struct STAT
void BackupDB();
int ajoutFichePC(FICHE *pp, STAT *A, int taille, int Exp);
int supprimePC(FICHE *F, char *ID); // suppression de fiche
int retrogradePC(); //fonction qui permet de retirer un pc de son etat expédiable


#endif // HEADER_H_INCLUDED
