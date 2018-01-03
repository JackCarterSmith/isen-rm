#define VERSION 1.0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header.h"
#include "db.h"

int main()
{
    int taille = 0; //taille temporaire du tableau de fiches
    int *my_app=NULL;
    int choix;
    int choixValideur;
    //int choixTechnicien;
    //int choixRespInventaire;
    //int *my_app=NULL;
    time_t now;
    FILE *db = NULL;

    db = fopen("db.irm","r");
    if (db == NULL) {regenDBFile();}		//Vérifier si la base de donnée existe, sinon la reconstruire
    fclose(db);

    FILE *lg=NULL;
    lg=fopen("historiqueActions.log", "a");
    if(lg==NULL) return -1;

    my_app=malloc(sizeof(int)*taille);
    if(my_app==NULL){printf("Pb\n");return -1;}

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
                    case 1 :    time(&now);
                                fprintf(lg,"%s-Action Technicien\n", asctime(localtime(&now)));
                                printf("\n** Modifier les entrées de la DB **\n");
                                //appel d'une fonction de sous menu technicien "modifier les entrées de la DB"
                    break;

                    case 2 :    time(&now);
                                fprintf(lg,"%s-Action Responsable inventaire\n", asctime(localtime(&now)));
                                printf("\n** Ajout de fiches PC a ID unique **\n");
                                //appel d'une fonction de sous menu resp inventaire "ajouter des fiches PC a ID unique"
                                //ajoutFichePC(FICHE *pp, AVANCEE *A, int taille, int Exp)
                    break;

                    case 3 :    time(&now);
                                fprintf(lg,"%s-Action Valideur\n", asctime(localtime(&now)));
                                printf("\n** Supprimer ou retrograder une fiche PC **\n");
                                // appel d'une fonction de sous menu valideur soit "supprimer une fiche PC" soit "retourner la fiche pc en maintenance"
                                do {
                                    do  {
                                            printf("\nMENU - Valideur\n");
                                            printf("1/ Supprimer une fiche pc\n");
                                            printf("2/ Rétrograder une fiche pc en maintenance\n");
                                            printf("3/ Retour au menu principal\n");
                                            printf("choix ?\n");
                                            scanf("%d", &choixValideur);
                                         }
                                            while (choixValideur < 1 || choixValideur > 3);
                                            switch (choixValideur)
                                            {
                                                case 1 :    time(&now);
                                                            fprintf(lg,"%s-Action Valideur - Supprimer une fiche pc\n", asctime(localtime(&now)));
                                                            //int supprimePC(FICHE *F, char *ID);

                                                break;

                                                case 2 :    time(&now);
                                                            fprintf(lg,"%s-Action Valideur - Retrograder une fiche pc\n", asctime(localtime(&now)));
                                                            //int retrogradePC();

                                                break;

                                                case 3 :    time(&now);
                                                            fprintf(lg,"%s-Action Valideur - Retour au menu principal\n", asctime(localtime(&now)));
                                                            //voir comment retourner au niveau précédent

                                                default :   time(&now);
                                                            fprintf(lg,"%s Erreur saisie\n", asctime(localtime(&now)));
                                                break;
                                            }
                                    }
                                    while (choix != 3);

                    break;

                    case 4 :    time(&now);
                                fprintf(lg,"%s-Quitter le programme\n", asctime(localtime(&now)));

                    default :   time(&now);
                                fprintf(lg,"%s Erreur saisie\n", asctime(localtime(&now)));
                    break;

                }
    }
    while (choix != 4);
    fclose(lg);
    free(my_app);
    return 0;
}

//prototypes temporaires et à améliorer.

int CmptPcExp(STAT A[], int taille, int Exp)
{
    int i=0;

    for (i=0; i<taille; i++)
    {

    }
}

int ajoutFichePC(FICHE *pp, STAT *A, int taille, int Exp)
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

    //printf("Drivers installés ?\n"); fprintf(f, "Drivers : %s", pp->Drivers);  //Drivers présents mais optionnels
    //printf("Divers software ?\n"); fprintf(f, "Softwares : %s", pp->Softwares); //Logiciels présents mais optionnels

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
