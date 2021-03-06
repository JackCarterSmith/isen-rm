#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "logger.h"
#include "users.h"
#include "db.h"
#include "backup.h"




void sub_addCard() {
	FICHE *f = malloc(sizeof(FICHE));
	char c;

	printf("\n Ajout d'une fiche PC\n --------------------\n\n");
	initCard(f);
	do {
		printf("\nEntrer l'ID du PC (10 chiffres) : ");
		scanf("%s",f->ID);
	} while (strlen(f->ID) != 10);
	printf("\nEntrer un nom pour désigner le PC (127 chars max) : ");
	while((c = getchar()) != '\n' && c != EOF)
		/* discard */ ;
	gets(f->Nom);
	printf("\nPréciser le modèle du CPU si connu (N/A dans le cas contraire) : ");
	gets(f->CPU);
	printf("\nPréciser la quantité de RAM si connu (N/A dans le cas contraire) : ");
	gets(f->MEM);
	printf("\nPréciser la capacité du HDD si connu (N/A dans le cas contraire) : ");
	gets(f->HDD);
	printf("\nPréciser l'OS si connu (N/A dans le cas contraire) : ");
	gets(f->OS);
	f->etat.Hardware = 0;
	f->etat.OS = 0;
	f->etat.Drivers = 0;
	f->etat.Software = 0;
	f->locked = 0;

	if (addCard(f) != 0) {
		printf("Une erreur s'est produite, consulter les logs pour plus de détails.\n\n");
	}

	free(f);
}

void sub_delCard() {
	char id[11];

	printf("\n Suppression fiche PC\n --------------------\n\n");
	do {
		printf("Entrer l'ID du PC à supprimer (10 chiffres) : ");
		scanf("%s",id);
	} while (strlen(id) != 10);

	if (delCard(id) != 0) {
		printf("Une erreur s'est produite, consulter les logs pour plus de détails.\n\n");
	}
}

void sub_readCard() {
	char id[11];
	FICHE *ddump = malloc(sizeof(FICHE));

	printf("\n Consultation fiche PC\n ---------------------\n\n");
	do {
		printf("Entrer l'ID du PC à consulter (10 chiffres) : ");
		scanf("%s",id);
	} while (strlen(id) != 10);

	if (readCard(id,ddump) != 0) {
		printf("Une erreur s'est produite, consulter les logs pour plus de détails.\n\n");
	} else {
		printf("Nom : %s\nEtat (Hardware-OS-Drivers-Software) : (%d-%d-%d-%d)\nCPU : %s\nMEM : %s\nHDD : %s\nOS : %s\n\n",ddump->Nom,ddump->etat.Hardware,ddump->etat.OS,ddump->etat.Drivers,ddump->etat.Software,ddump->CPU,ddump->MEM,ddump->HDD,ddump->OS);
	}

	free(ddump);

	printf("Appuyer sur une touche pour continuer\n");
	getchar();
}

void sub_editCard() {
	FICHE *f = malloc(sizeof(FICHE));
	FICHE *edt_f = malloc(sizeof(FICHE));
	char c;

	printf("\n Edition d'une fiche PC\n ----------------------\n\n");
	initCard(f);
	initCard(edt_f);
	do {
		printf("\nEntrer l'ID du PC (10 chiffres) : ");
		scanf("%s",edt_f->ID);
	} while (strlen(edt_f->ID) != 10);

	if (readCard(edt_f->ID,f) != 0) {
		printf("Une erreur s'est produite, consulter les logs pour plus de détails.\n\n");
	} else {
		printf("Nom : %s\nEtat (Hardware-OS-Drivers-Software) : (%d-%d-%d-%d)\nCPU : %s\nMEM : %s\nHDD : %s\nOS : %s\n\n",f->Nom,f->etat.Hardware,f->etat.OS,f->etat.Drivers,f->etat.Software,f->CPU,f->MEM,f->HDD,f->OS);
		printf("\nPréciser le modèle du CPU : ");
		while((c = getchar()) != '\n' && c != EOF)
			/* discard */ ;
		gets(edt_f->CPU);
		printf("\nPréciser la quantité de RAM : ");
		gets(edt_f->MEM);
		printf("\nPréciser la capacité du HDD : ");
		gets(edt_f->HDD);
		printf("\nPréciser l'OS : ");
		gets(edt_f->OS);
		printf("\nEtat - Hardware (0 = NOK / 1 = OK) : ");
		scanf("%d",&(edt_f->etat.Hardware));
		printf("\nEtat - OS (0 = NOK / 1 = OK) : ");
		scanf("%d",&(edt_f->etat.OS));
		printf("\nEtat - Drivers (0 = NOK / 1 = OK) : ");
		scanf("%d",&(edt_f->etat.Drivers));
		printf("\nEtat - Software (0 = NOK / 1 = OK) : ");
		scanf("%d",&(edt_f->etat.Software));

		if (editCard(edt_f) != 0) {
			printf("Une erreur s'est produite, consulter les logs pour plus de détails.\n\n");
		}
	}

	free(f);
	free(edt_f);
}

void sub_validCard() {
	char id[11];

	printf("\n Validation fiche PC\n -------------------\n\n");
	do {
		printf("Entrer l'ID du PC à valider (10 chiffres) : ");
		scanf("%s",id);
	} while (strlen(id) != 10);

	if (validCard(id) != 0) {
		printf("Une erreur s'est produite, consulter les logs pour plus de détails.\n\n");
	}
}

void sub_dispCptTot() {
	HEAD *h = malloc(sizeof(HEAD));

	printf("\n Compteur de fiches réparés total\n --------------------------------\n\n");
	if (getConfig(h) != 0) {
		printf("Une erreur s'est produite, consulter les logs pour plus de détails.\n\n");
		h->cpt_rep_total = 0;
		h->nbr_fiches = 0;
	}

	printf(" Nombre de fiches dans la DB : %d\n\n Nombre de PC au total réparé : %d",h->nbr_fiches,h->cpt_rep_total);

	free(h);
}

void sub_dispRdy2Go() {
	FICHE **f = NULL;
	int i,nbr = 0;

	printf("\n Compteur de PC prêt à l'utilisation\n -----------------------------------\n\n");
	nbr = sortReadyCard(f);
	if (nbr >= 0) {
		printf(" Nombre de PC prêt à l'utilisation : %d\n\nIDs correspondant :\n",nbr);
		/*
		for (i = 0; i < nbr; i++) {
			printf(" - [%s]",(*f)[i].ID);
		}
		*/
	} else {
		printf("Une erreur s'est produite, consulter les logs pour plus de détails.\n\n");
	}

	if (f != NULL) { free(f); }
}

void sub_addUser() {
	USER *usr = malloc(sizeof(USER));

	printf("\n Ajout d'utilisateur\n -------------------\n\n");
	do {
		printf("Entrer l'ID du nouvel utilisateur (8 chiffres) : ");
		scanf("%s",usr->u_id);
	} while (strlen(usr->u_id) != 8);
	do {
		printf("Entrer le PIN pour cet utilisateur (4 chiffres) : ");
		scanf("%s",usr->u_pin);
	} while (strlen(usr->u_pin) != 4);
	do {
		printf("Entrer le rang pour cet utilisateur\n(1 = Technicien, 2 = Responsable inventaire, 3 = Validateur) : ");
		scanf("%d",&usr->u_rank);
	} while (usr->u_rank < 1 && usr->u_rank > 3);

	if (addUser(usr) != 0) {
		printf("Une erreur s'est produite, consulter les logs pour plus de détails.\n\n");
	}

	free(usr);
}

void sub_delUser() {
	char id[9];

	printf("\n Suppression d'utilisateur\n -------------------------\n\n");
	do {
		printf("Entrer l'ID de l'utilisateur à supprimer (8 chiffres) : ");
		scanf("%s",id);
	} while (strlen(id) != 8);

	if (delUser(id) != 0) {
		printf("Une erreur s'est produite, consulter les logs pour plus de détails.\n\n");
	}
}



int main()
{
	FILE *db = NULL;
	FILE *u_login = NULL;

	USER *u = malloc(sizeof(USER));
	FICHE **u_dump = NULL;

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

		do {
			printf("Entrer votre ID utilisateur (ou 'guest' si vous êtes simple visiteur) : ");
			scanf("%s",u->u_id);
		} while ((strlen(u->u_id) != 8) && (strcmp(u->u_id,"guest") != 0));
		if (strcmp(u->u_id,"guest") == 0) {
			u->u_rank = 0;
		} else {
			do {
				printf("Entrer votre PIN : ");
				scanf("%s",u->u_pin);
			} while (strlen(u->u_pin) != 4);

			if (userLogin(u) != 0) {
				printf("Un problème est survenu durant l'authentification, consulter les logs pour plus de détails.\n");
				free(u);
				return -1;	//Défaillance authentification
			}
		}

		if (u->u_rank != 0) {
			backupDB();		//Backup de démarrage par mesure de précaution
		}


		switch (u->u_rank) {
		case 1:		//Menu technicien
			printf("\n\n\nBienvenue Technicien [%s], vous pouvez accéder aux fiches PC pour les édités.\n", u->u_id);
			do {
				printf(" #=============================================================================#\n |                             Menu Technicien                              |\n #============================================================================#\n\n");
				do {
					printf("   [1] - Edition fiche PC\n   [2] - Consulter une fiche PC\n   [3] - Consulter le nombre de PC en stock\n   [0] - Logout\n\n");
					printf(" Spécifier le numéro d'action à lancer : ");
					scanf("%d",&sub_choice);
				} while (sub_choice < 0 && sub_choice > 3);

				switch (sub_choice) {
				case 1:
					sub_editCard();
					break;
				case 2:
					sub_readCard();
					break;
				case 3:
					sub_dispCptTot();
					break;
				}
			} while (sub_choice != 0);
		break;
		case 2:		//Menu responsable inventaire
			printf("\n\n\nBienvenue Responsable inventaire [%s], vous pouvez accéder aux ajouts et suppression des fiches PC.\n", u->u_id);
			do {
				printf(" #==========================================================================#\n |                            Menu Resp.Inv                              |\n #==========================================================================#\n\n");
				do {
					printf("   [1] - Ajouter une nouvelle fiche PC\n   [2] - Supprimer une fiche PC\n   [3] - Consulter une fiche PC\n   [4] - Consulter le nombre de PC en stock\n   [5] - Consulter le nombre de PC prêt à être utilisé\n   [0] - Logout\n\n");
					printf(" Spécifier le numéro d'action à lancer : ");
					scanf("%d",&sub_choice);
				} while (sub_choice < 0 && sub_choice > 5);

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
					sub_dispCptTot();
					break;
				case 5:
					sub_dispRdy2Go();
					break;
				}
			} while (sub_choice != 0);
		break;
		case 3:		//Menu validateur
			printf("\n\n\nBienvenue Validateur [%s], vous pouvez accéder aux procédures de validation des PC.\n", u->u_id);
			do {
				printf(" #============================================================================#\n |                             Menu Validateur                              |\n #=============================================================================#\n\n");
				do {
					printf("   [1] - Valider et verrouiller une fiche PC\n   [2] - Consulter une fiche PC\n   [3] - Consulter le nombre de PC en stock\n   [4] - Consulter le nombre de PC prêt à être utilisé\n   [0] - Logout\n\n");
					printf(" Spécifier le numéro d'action à lancer : ");
					scanf("%d",&sub_choice);
				} while (sub_choice < 0 && sub_choice > 4);

				switch (sub_choice) {
				case 1:
					sub_validCard();
					break;
				case 2:
					sub_readCard();
					break;
				case 3:
					sub_dispCptTot();
					break;
				case 4:
					sub_dispRdy2Go();
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
					sub_dispRdy2Go();
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
}
