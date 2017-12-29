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

//prototypes temporaires et à améliorer.

public ;

int CmptPcRep(LOG L[], int Rep); //La fonction renvoie le nombre de PC réparés depuis le début de l'annee

private ;

int CmptPcExp(AVANCEE A[], int taille, int Exp); //La fonction balaye la liste des PC et compte le nombre de pc répondant aux critères d'expédition grace à la struct avancee
void BackupDB();
int ajoutFichePC(FICHE *pp, AVANCEE *A, int taille, int Exp);
int supprimePC(FICHE *F, char *ID); // suppression de fiche
int retrogradePC(); //fonction qui permet de retirer un pc de son etat expédiable

int CmptPcExp(AVANCEE A[], int taille, int Exp)
{
    int i=0;

    for (i=0; i<taille; i++)
    {

    }
}

int ajoutFichePC(FICHE *pp, AVANCEE *A, int taille, int Exp)
{
    FILE*f=NULL;  //A voir le format de la DB, pour l'instant je procède comme si la DB était un .txt
    char nomfic[32];
    char O;
    char N;
    printf("Nom du fichier DB ?\n");
    scanf("%s", nomfic);
    f=fopen(nomfic, "a");

    if(f==NULL) //fichier innexistant
    {
        printf("DB introuvable");

        if(f==NULL) //Le prog n'a pas les droits en écriture
            return -1;
    }

    printf("\nID du PC ?\n"); fprintf(f, "ID : %s", pp->Nom);
    printf("Son CPU ?\n"); fprintf(f, "CPU : %s", pp->CPU); A->Materiel=1; if (pp->CPU==NULL) {A->Materiel=0;}
    printf("HDD ?\n"); fprintf(f, "HDD : %s", pp->HDD); A->Materiel=1; if (pp->HDD==NULL) {A->Materiel=0;}
    printf("Son OS ?\n"); fprintf(f, "OS : %s", pp->OS); A->Os=1; if (pp->OS==NULL) {A->Os=0;}

    if (A->Materiel == 1 && A->Os == 1) //Si la partie materielle et l'os présentes, l'etat est O pour oui.
    {
        fprintf(f, "Etat : O\n"); Exp=Exp+1;
    }

    else
    {
        fprintf(f, "Etat : N\n"); //Dans le cas contraire, l'etat est N pour non
    }

    printf("Drivers installés ?\n"); fprintf(f, "Drivers : %s", pp->Drivers);  //Drivers présents mais optionnels
    printf("Divers software ?\n"); fprintf(f, "Softwares : %s", pp->Softwares); //Logiciels présents mais optionnels

    taille = taille+1;
    fclose(f);
    return taille;
}

int supprimePC(FICHE *F, char *ID)
{
FILE*f=NULL;
int pos=0;
int trouve=0;
char nomfic[32];

printf("Nom du fichier DB ?\n");
scanf("%s", nomfic); //exemple "DB.db"
f=fopen(nomfic, "r+"); //En revanche j'ai écrit cette fonction de la même manière que pour un .txt donc méthode à vérifier.

if(f==NULL) //Si le fichier n'existe pas, on retourne une erreur
{
return 0;
}

rewind(f); //On se place au début du fichier

while(fscanf(f,"%s\n",F->Nom)!=EOF)
{
if(strcmp(F->Nom, ID)==0)
{
trouve=1;
break;
}
pos++;
}
if (trouve == 0) return 0;

printf("fiche trouvée\n");

while(fscanf(f,"%s\n",F->Nom)!=EOF)
{
fseek(f,pos*52,SEEK_SET); //taille 52 arbitraire a vérifier la taille en octet d'une ligne sachant que la DB sera en binaire
fprintf(f,"%-20s%",F->Nom);
pos++;
fseek(f,(pos+1)*52,SEEK_SET);
}
fseek(f,pos*52,SEEK_SET);
fprintf(f,"%c",26);
fclose(f);
return 1;
}

#endif // HEADER_H_INCLUDED
