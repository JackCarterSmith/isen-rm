#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "logger.h"
#include "db.h"
#include "backup.h"

int main()
{
    int taille = 0; //taille temporaire du tableau de fiches
    int *my_app=NULL;
    int choix;
    int choixValideur;
    //int choixTechnicien;
    //int choixRespInventaire;
    //int *my_app=NULL
    FILE *db = NULL;

    db = fopen("db.irm","rb");
    if (db == NULL) {regenDBFile();}		//V�rifier si la base de donn�e existe, sinon la reconstruire
    fclose(db);

    backupDB();

    my_app=malloc(sizeof(int)*taille);
    if(my_app==NULL){printf("Pb\n");return -1;}

	FICHE *test = malloc(sizeof(FICHE));
	printf("ID to write: ");
	scanf("%s",test->ID);
	strcpy(test->CPU,"Core i3");
	strcpy(test->MEM,"2G");
	strcpy(test->HDD,"250G");
	strcpy(test->Nom,"TEST-bouzepc-db");
	strcpy(test->OS,"NUXNUX\0");
	test->Etat = 0x0011;

	addCard(test);

	char id[11];
	FICHE *ddump = malloc(sizeof(FICHE));
	printf("Enter an ID to be read : ");
	scanf("%s",id);

	readCard(id,ddump);

	printf("Nom : %s\nEtat : %d\nCPU : %s\nMEM : %s\nHDD : %s\nOS : %s\n",ddump->Nom,ddump->Etat,ddump->CPU,ddump->MEM,ddump->HDD,ddump->OS);

	free(ddump);

	printf("Enter an ID to be deleted : ");
	scanf("%s",id);

	delCard(id);

	printf("ID to rewrite: ");
	scanf("%s",test->ID);
	strcpy(test->CPU,"Quad Core X15");
	strcpy(test->MEM,"8G");
	strcpy(test->HDD,"1T");
	strcpy(test->Nom,"TEST-ultimatesexemachine-db");
	strcpy(test->OS,"RECODED");
	test->Etat = 0x1111;

	editCard(test);

	return 0;







/*

    do {
            do {
                printf("\n**ISEN RM**\n\nMENU\n");
                printf("Type d'utilisateur ?\n");
                printf("1/ Technicien\n");
                printf("2/ Responsable Inventaire\n");
                printf("3/ Valideur\n");
                printf("4/ Quitter le programme");
                printf("Votre choix ?\n");
                scanf("%d", &choix);
                }

                while (choix < 1 || choix > 4);
                switch (choix)
                {
                    case 1 :    addLogInfo("Action Technicien");
                                printf("\n** Modifier les entr�es de la DB **\n");
                                //appel d'une fonction de sous menu technicien "modifier les entr�es de la DB"
                                break;

                    case 2 :    addLogInfo("Action Responsable inventaire");
                                printf("\n** Ajout de fiches PC a ID unique **\n");
                                //appel d'une fonction de sous menu resp inventaire "ajouter des fiches PC a ID unique"
                                //ajoutFichePC(FICHE *pp, AVANCEE *A, int taille, int Exp)
                                break;

                    case 3 :    addLogInfo("Action Valideur");
                                printf("\n** Supprimer ou retrograder une fiche PC **\n");
                                // appel d'une fonction de sous menu valideur soit "supprimer une fiche PC" soit "retourner la fiche pc en maintenance"
                                do {
                                    do {
											printf("\nMENU - Valideur\n");
											printf("1/ Supprimer une fiche pc\n");
											printf("2/ R�trograder une fiche pc en maintenance\n");
											printf("3/ Retour au menu principal\n");
											printf("choix ?\n");
											scanf("%d", &choixValideur);
                                        } while (choixValideur < 1 || choixValideur > 3);
										switch (choixValideur)
										{
											case 1 :    addLogInfo("Action Valideur - Supprimer une fiche pc");
														//int supprimePC(FICHE *F, char *ID);

											break;

											case 2 :    addLogInfo("Action Valideur - Retrograder une fiche pc");
														//int retrogradePC();

											break;

											case 3 :    addLogInfo("Action Valideur - Retour au menu principal");
														//voir comment retourner au niveau pr�c�dent

											default :   addLogWarn("Erreur saisie");
											break;
										}
                                    } while (choix != 3);
                                break;

                    case 4 :    addLogInfo("Quitter le programme");
                    			break;

                    default :   addLogWarn("Erreur saisie");
                    			break;

                }
    }
    while (choix != 4);
    stop_logger();		//Stop le logger
    free(my_app);
    return 0;
}

//prototypes temporaires et � am�liorer.

int CmptPcExp(STAT A[], int taille, int Exp)
{
    int i=0;

    for (i=0; i<taille; i++)
    {

    }
}

int ajoutFichePC(FICHE *pp, STAT *A, int taille, int Exp)
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

    //printf("Drivers install�s ?\n"); fprintf(f, "Drivers : %s", pp->Drivers);  //Drivers pr�sents mais optionnels
    //printf("Divers software ?\n"); fprintf(f, "Softwares : %s", pp->Softwares); //Logiciels pr�sents mais optionnels

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
	f=fopen(nomfic, "r+"); //En revanche j'ai �crit cette fonction de la m�me mani�re que pour un .txt donc m�thode � v�rifier.

	if(f==NULL) //Si le fichier n'existe pas, on retourne une erreur
	{
		return 0;
	}

	rewind(f); //On se place au d�but du fichier

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

	printf("fiche trouv�e\n");

	while(fscanf(f,"%s\n",F->Nom)!=EOF)
	{
		fseek(f,pos*52,SEEK_SET); //taille 52 arbitraire a v�rifier la taille en octet d'une ligne sachant que la DB sera en binaire
		fprintf(f,"%-20s%",F->Nom);
		pos++;
		fseek(f,(pos+1)*52,SEEK_SET);
	}

	fseek(f,pos*52,SEEK_SET);
	fprintf(f,"%c",26);
	fclose(f);

	return 1;
	
*/
}
