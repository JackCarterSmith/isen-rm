#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

struct fiche //En gros, la config du PC.
    {
    char Nom[256];
    char CPU[64];
    char HDD[64];
    char OS[64];
    char Etat;
    char Drivers[256];
    char Softwares[256];
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

//prototypes temporaires et � am�liorer.

public ;

int CmptPcRep(LOG L[], int Rep); //La fonction renvoie le nombre de PC r�par�s depuis le d�but de l'annee

private ;

int CmptPcExp(AVANCEE A[], int taille, int Exp); //La fonction balaye la liste des PC et compte le nombre de pc r�pondant aux crit�res d'exp�dition grace � la struct avancee
int LogPc(LOG L[]);
void BackupDB();
int ajoutFichePC(FICHE *pp, AVANCEE *A, int taille, int Exp);
int supprimePC(); // suppression de fiche
int retrogradePC(); //fonction qui permet de retirer un pc de son etat exp�diable

int CmptPcExp(AVANCEE A[], int taille, int Exp)
{
    int i=0;

    for (i=0; i<taille; i++)
    {

    }
}

int ajoutFichePC(FICHE *pp, AVANCEE *A, int taille, int Exp)
{
    FILE*f=NULL;  //A voir le format de la DB, pour l'instant je proc�de comme si la DB �tait un .txt
    char nomfic[32];
    char O;
    char N;
    printf("Nom du fichier DB ?\n");
    scanf("%s", nomfic);
    f=fopen(nomfic, "a");

    if(f==NULL) //fichier innexistant
    {
        printf("DB introuvable");

        if(f==NULL) //Le prog n'a pas les droits en �criture
            return -1;
    }

    printf("\nID du PC ?\n"); fprintf(f, "ID : %s", pp->Nom);
    printf("Son CPU ?\n"); fprintf(f, "CPU : %s", pp->CPU); A->Materiel=1; if (pp->CPU==NULL) {A->Materiel=0;}
    printf("HDD ?\n"); fprintf(f, "HDD : %s", pp->HDD); A->Materiel=1; if (pp->HDD==NULL) {A->Materiel=0;}
    printf("Son OS ?\n"); fprintf(f, "OS : %s", pp->OS); A->Os=1; if (pp->OS==NULL) {A->Os=0;}

    if (A->Materiel == 1 && A->Os == 1) //Si la partie materielle et l'os pr�sentes, l'etat est O pour oui.
    {
        fprintf(f, "Etat : O\n"); Exp=Exp+1;
    }

    else
    {
        fprintf(f, "Etat : N\n"); //Dans le cas contraire, l'etat est N pour non
    }

    printf("Drivers install�s ?\n"); fprintf(f, "Drivers : %s", pp->Drivers);  //Drivers pr�sents mais optionnels
    printf("Divers software ?\n"); fprintf(f, "Softwares : %s", pp->Softwares); //Logiciels pr�sents mais optionnels

    taille = taille+1;
    fclose(f);
    return taille;
}

#endif // HEADER_H_INCLUDED
