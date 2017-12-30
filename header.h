#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

typedef struct fiche //En gros, la config du PC.
    {
    char Nom[256];
    char CPU[64];
    char HDD[64];
    char OS[64];
    char Etat;
    char Drivers[256];
    char Softwares[256];
    }FICHE;

typedef struct stat_pc  //Structure de booleens. Chaque variable prend 1 si le PC comporte le module correspondant.
    {
    int Materiel;
    int Os;
    int Drivers;
    int Software;
    }STAT;

typedef struct log // Historique des actions de l'utilisateur depuis le menu.
    {
    int Annee;
    int Mois;
    int Jour;
    int Heure;
    int Minute;
    int Seconde;
    }LOG;


// functions public

int CmptPcRep(LOG L[], int Rep); //La fonction renvoie le nombre de PC r�par�s depuis le d�but de l'annee

// functions priv�es ;

int CmptPcExp(STAT A[], int taille, int Exp); //La fonction balaye la liste des PC et compte le nombre de pc r�pondant aux crit�res d'exp�dition grace � la struct STAT
void BackupDB();
int ajoutFichePC(FICHE *pp, STAT *A, int taille, int Exp);
int supprimePC(FICHE *F, char *ID); // suppression de fiche
int retrogradePC(); //fonction qui permet de retirer un pc de son etat exp�diable


#endif // HEADER_H_INCLUDED
