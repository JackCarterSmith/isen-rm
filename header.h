#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

struct fiche //En gros, la config du PC.
    {
    char Nom[256];
    char CPU[64];
    char HDD[64];
    char OS[64];
    char Etat;
    };

typedef struct fiche FICHE;

struct avancee  //Structure de booleens. Chaque variable prend 1 si le PC comporte le module correspondant.
    {
    int Materiel;
    int Os;
    int Drivers;
    int Software;
    };

typedef struct avancee AVANCEE;

struct log // Historique des actions de l'utilisateur depuis le menu.
    {
    int Annee;
    int Mois;
    int Jour;
    int Heure;
    int Minute;
    int Seconde;
    };

typedef struct log LOG;

//prototypes temporaires et à améliorer.

public ;

int CmptPcRep(LOG L[], int Rep); //La fonction renvoie le nombre de PC réparés depuis le début de l'annee

private ;

int CmptPcExp(AVANCEE A[], int Exp); //La fonction balaye la liste des PC et compte le nombre de pc répondant aux critères d'expédition grace à la struct avancee
int LogPc(LOG L[]);
void BackupDB();


#endif // HEADER_H_INCLUDED
