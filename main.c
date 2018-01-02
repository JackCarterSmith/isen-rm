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

    my_app=(int*)malloc(sizeof(int)*taille);
    //(int*) = operation de casting pas nécessaire pour du C 99//
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
