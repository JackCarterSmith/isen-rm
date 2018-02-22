#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "logger.h"
#include "users.h"
#include "db.h"
#include "backup.h"




void sub_addCard() {

}

void sub_delCard() {

}

void sub_readCard() {

}

void sub_editCard() {

}

void sub_validCard() {

}

void sub_dispCptTot() {

}

void sub_dispCptRdy2Go() {

}

void sub_addUser() {
	USER *usr = malloc(sizeof(USER));

	printf("\n Ajout d'utilisateur\n -------------------\n\n");
	printf("Entrer l'ID du nouvel utilisateur (8 chiffres) : ");
	scanf("%s",usr->u_id);
	printf("Entrer le PIN pour cet utilisateur (4 chiffres) : ");
	scanf("%s",usr->u_pin);
	printf("Entrer le rang pour cet utilisateur\n(1 = Technicien, 2 = Responsable inventaire, 3 = Validateur) : ");
	scanf("%d",&usr->u_rank);

	if (addUser(usr) != 0) {
		printf("Une erreur s'est produite, consulter les logs pour plus de détails.");
	}

	free(usr);
}

void sub_delUser() {
	char id[9];

	printf("\n Suppression d'utilisateur\n -------------------------\n\n");
	printf("Entrer l'ID de l'utilisateur à supprimer (8 chiffres) : ");
	scanf("%s",id);

	if (delUser(id) != 0) {
		printf("Une erreur s'est produite, consulter les logs pour plus de détails.");
	}
}



int main()
{
	FILE *db = NULL;
	FILE *u_login = NULL;

	USER *u = malloc(sizeof(USER));
	FICHE *u_dump = NULL;

	char choice;
	int sub_choice = 0;
	int nbr_cardRdy = 0;


	if (initialise_logger() != 0) {			//Initialise le logger et vérifie qu'il a bien démarré
		printf("\n\nATTENTION ! Le fichier de log ne peut etre ecrit, aucune info ne sera enregistree !\n\n");
	}

	db = fopen("db.irm","rb");
	if (db == NULL) { regenDBFile(); }		//Vérifier si la base de donnée existe, sinon la reconstruire
	fclose(db);

	u_login = fopen("users.crd","rb");
	if (u_login == NULL) { u_newSetup(); }
	fclose(u_login);


	do {
		printf("\n\n\n\n\n #=================#\n |  ISEN RM v1.00  |\n #=================#\n\n");

		printf("Entrer votre ID utilisateur (ou 'guest' si vous êtes simple visiteur) : ");
		scanf("%s",u->u_id);
		if (strcmp(u->u_id,"guest") == 0) {
			u->u_rank = 0;
		} else {
			printf("Entrer votre PIN : ");
			scanf("%s",u->u_pin);

			if (userLogin(u) != 0) {
				printf("Un problème est survenu durant l'authentification, consulter les logs pour plus de détails.\n");
				free(u);
				return -1;	//Défaillance authentification
			}
		}

		backupDB();		//Backup de démarrage par mesure de précaution


		switch (u->u_rank) {
		case 1:		//Menu technicien
			printf("\n\n\nBienvenue Technicien [%s], vous pouvez accéder aux fiches PC pour les édités.\n", u->u_id);
			do {
				printf(" #=============================#\n |    Menu Technicien    |\n #=============================#\n\n");
				do {
					printf("   [1] - Edition fiche PC\n   [2] - Consulter une fiche PC\n   [3] - Consulter le nombre de PC en stock\n   [0] - Logout\n\n");
					printf(" Spécifier le numéro d'action à lancer : ");
					scanf("%d",&sub_choice);
				} while (sub_choice < 0 && sub_choice > 3);

				switch (sub_choice) {
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				}
			} while (sub_choice != 0);
		break;
		case 2:		//Menu responsable inventaire
			printf("\n\n\nBienvenue Responsable inventaire [%s], vous pouvez accéder aux ajouts et suppression des fiches PC.\n", u->u_id);
			do {
				printf(" #=============================#\n |    Menu Rep.Inv    |\n #=============================#\n\n");
				do {
					printf("   [1] - Ajouter une nouvelle fiche PC\n   [2] - Supprimer une fiche PC\n   [3] - Consulter une fiche PC\n   [4] - Consulter le nombre de PC en stock\n   [5] - Consulter le nombre de PC prêt à être utilisé\n   [0] - Logout\n\n");
					printf(" Spécifier le numéro d'action à lancer : ");
					scanf("%d",&sub_choice);
				} while (sub_choice < 0 && sub_choice > 5);

				switch (sub_choice) {
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				case 5:
					break;
				}
			} while (sub_choice != 0);
		break;
		case 3:		//Menu validateur
			printf("\n\n\nBienvenue Validateur [%s], vous pouvez accéder aux procédures de validation des PC.\n", u->u_id);
			do {
				printf(" #=============================#\n |    Menu Validateur   |\n #=============================#\n\n");
				do {
					printf("   [1] - Valider et verrouiller une fiche PC\n   [2] - Consulter une fiche PC\n   [3] - Consulter le nombre de PC en stock\n   [4] - Consulter le nombre de PC prêt à être utilisé\n   [0] - Logout\n\n");
					printf(" Spécifier le numéro d'action à lancer : ");
					scanf("%d",&sub_choice);
				} while (sub_choice < 0 && sub_choice > 4);

				switch (sub_choice) {
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				}
			} while (sub_choice != 0);
		break;
		case 4:		//Menu admin
			printf("\n\n\nBienvenue Administrateur, vous pouvez accéder à toutes les fonctions du programme.\n");
			do {
				printf(" #================================================================================#\n |                               Menu Administrateur                              |\n #================================================================================#\n\n");
				do {
					printf("   [1] - Ajouter une nouvelle fiche PC\n   [2] - Supprimer une fiche PC\n   [3] - Consulter une fiche PC\n   [4] - Edition fiche PC\n   [5] - Valider et verrouiller une fiche PC\n   [6] - Consulter le nombre de PC en stock\n   [7] - Consulter le nombre de PC prêt à être utilisé\n   [8] - Ajouter un utilisateur\n   [9] - Supprimer un utilisateur\n   [0] - Logout\n\n");
					printf(" Spécifier le numéro d'action à lancer : ");
					scanf("%d",&sub_choice);
				} while (sub_choice < 0 && sub_choice > 9);

				switch (sub_choice) {
				case 1:
					sub_addCard();
					break;
				case 2:
					sub_delCard();
					break;
				case 3:
					sub_readCard();
					break;
				case 4:
					sub_editCard();
					break;
				case 5:
					sub_validCard();
					break;
				case 6:
					sub_dispCptTot();
					break;
				case 7:
					sub_dispCptRdy2Go();
					break;
				case 8:
					sub_addUser();
					break;
				case 9:
					sub_delUser();
					break;
				}
			} while (sub_choice != 0);
		break;
		default:	//Menu visiteur
			nbr_cardRdy = sortReadyCard(u_dump);
			printf("\n\n\nBienvenue Visiteur, vous pouvez accéder aux derniers chiffres de l'association.\n");
			printf(" #=============================#\n |    PC total réparé : %d   |\n #=============================#\n\n",nbr_cardRdy);
		}

		printf("\n\nRetour écran de login ? (y/n)");
		scanf(" %c",&choice);
	} while (choice != 'n');

	printf("Exit program.");
	return 0;











    int taille;
    FICHE *tab = NULL;
    taille = sortReadyCard(tab);

    printf("Taille du tableau : %d\n",taille);

    FICHE *test = malloc(sizeof(FICHE));
	printf("ID to write: ");
	scanf("%s",test->ID);
	strcpy(test->CPU,"Core i3");
	strcpy(test->MEM,"2G");
	strcpy(test->HDD,"250G");
	strcpy(test->Nom,"TEST-bouzepc-db");
	strcpy(test->OS,"NUXNUX\0");
	test->etat.Hardware = 1;
	test->etat.OS = 1;
	test->etat.Drivers = 0;
	test->etat.Software = 0;

	addCard(test);

	char id[11];
	FICHE *ddump = malloc(sizeof(FICHE));
	printf("Enter an ID to be read : ");
	scanf("%s",id);

	readCard(id,ddump);

	printf("Nom : %s\nEtat : %d%d%d%d\nCPU : %s\nMEM : %s\nHDD : %s\nOS : %s\n",ddump->Nom,ddump->etat.Hardware,ddump->etat.OS,ddump->etat.Drivers,ddump->etat.Software,ddump->CPU,ddump->MEM,ddump->HDD,ddump->OS);

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
	test->etat.Hardware = 1;
	test->etat.OS = 1;
	test->etat.Drivers = 1;
	test->etat.Software = 1;

	editCard(test);

	if (tab != NULL) {free(tab);}
}
