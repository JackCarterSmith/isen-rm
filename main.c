#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header.h"

int main()
{
    int taille = 0; //taille temporaire du tableau de fiches
    int choix;
    int choixValideur;
    int *my_app=NULL;

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
                    case 1 :    printf("\n** Modifier les entrées de la DB **\n");
                                //appel d'une fonction de sous menu technicien
                    break;

                    case 2 :    printf("\n** Ajout de fiches PC a ID unique **\n");
                                //appel d'une fonction de sous menu resp inventaire
                    break;

                    case 3 :    printf("\n** Supprimer ou retrograder une fiche PC **\n");
                                // appel d'une fonction de sous menu valideur
                    break;
                    default : break;

                }
    }
    while (choix != 4);
    free(my_app);
    return 0;
}
