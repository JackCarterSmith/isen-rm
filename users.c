/*
 * users.c
 *
 *  Created on: 10 févr. 2018
 *      Author: are
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "users.h"
#include "logger.h"

void u_newSetup() {
	FILE *f = NULL;
	USER *admin = malloc(sizeof(USER));
	const unsigned int accts_default = 1;

	f = fopen("db.irm","rb");
	if (f != NULL) {
		fclose(f);
		addLogWarn("Suppression DB par mesure de sécurité.");
		remove("db.irm");
	}

	printf("Bienvenue dans la première installation du logiciel !\nMerci de spécifier l'identifiant administrateur (8 chiffres) : ");
	scanf("%s",admin->u_id);
	printf("Pour des raisons de sécurité, merci de spécifier un code à 4 chiffres : ");
	scanf("%s",admin->u_pin);
	admin->u_rank = 4;

	printf("Enregistrement de l'utilisateur...\n");
	f = fopen("users.crd","wb+");
	fwrite(&accts_default,sizeof(unsigned int),1,f);
	fwrite(admin, sizeof(USER),1,f);
	fclose(f);
	printf("Succès ! Merci de redémarrer l'application\n");
	addLogInfo("Création du fichier utilisateur avec succès !");
	free(admin);
}

int userLogin(USER *u) {
	FILE *u_db = NULL;
	unsigned int u_nbr = 0;

	u_db = fopen("users.crd","rb");
	if (u_db == NULL) {
		u_newSetup();
		return 1;		//Situation normalement impossible de reinit
	}

	fread(&u_nbr,sizeof(unsigned int),1,u_db);

	int i;
	USER *dump = malloc(sizeof(USER));
	char *logIDrecord = malloc(sizeof(char)*64);

	for (i = 1; i <= u_nbr; i++) {
		fread(dump,sizeof(USER),1,u_db);
		if (strcmp(u->u_id,dump->u_id) == 0) {
			if (strcmp(u->u_pin,dump->u_pin) == 0) {
				u->u_rank = dump->u_rank;
				sprintf(logIDrecord,"Connexion utilisateur [%s].",dump->u_id);
				addLogInfo(logIDrecord);
				fclose(u_db);
				free(dump);
				free(logIDrecord);
				return 0;
			} else {
				sprintf(logIDrecord,"Mauvais pin spécifié pour l'utilisateur [%s].",dump->u_id);
				addLogWarn(logIDrecord);
				fclose(u_db);
				free(dump);
				free(logIDrecord);
				return 2;	//Mauvais pin spécifié
			}
		}
	}
	fclose(u_db);

	sprintf(logIDrecord,"Utilisateur [%s] introuvable.",u->u_id);
	addLogWarn(logIDrecord);

	free(dump);
	free(logIDrecord);
	return 3;	//Utilisateur inconnu
}

int addUser(USER *u) {
	FILE *u_db = NULL;
	unsigned int u_nbr = 1;
	char *logIDrecord = malloc(sizeof(char)*64);

	u_db = fopen("users.crd","rb+");
	if (u_db != NULL) {
		fseek(u_db,0,SEEK_SET);
		fread(&u_nbr,sizeof(unsigned int),1,u_db);
		fseek(u_db, 0, SEEK_END);
		fwrite(u,sizeof(USER),1,u_db);
		fseek(u_db,0,SEEK_SET);
		u_nbr = u_nbr + 1;		//Incrementation du compteur
		fwrite(&u_nbr,sizeof(unsigned int),1,u_db);

		sprintf(logIDrecord,"AddUser: Ajout avec succès de l'utilisateur [%s].",u->u_id);
		addLogInfo(logIDrecord);

		free(logIDrecord);
		fclose(u_db);
		return 0;		//Utilisateur enregistré avec succès
	}

	sprintf(logIDrecord,"AddUser: Echec lors de l'ajout de l'utilisateur [%s].",u->u_id);
	addLogInfo(logIDrecord);
	free(logIDrecord);
	return 1; 		//Erreur fichier non existant
}

int delUser(char *u_id) {
	FILE *u_db = NULL;
	unsigned int u_nbr = 1;
	char *logIDrecord = malloc(sizeof(char)*64);
	int i;

	u_db = fopen("users.crd","rb+");
	if (u_db != NULL) {
		fseek(u_db,0,SEEK_SET);
		fread(&u_nbr,sizeof(unsigned int),1,u_db);

		USER dump[u_nbr];
		fread(dump,sizeof(USER),u_nbr,u_db);	//Function de copie mémoire des utilisateurs

		u_db = freopen("users.crd","wb",u_db);

		fseek(u_db, 0, SEEK_SET);
		u_nbr = u_nbr - 1;		//Decompte du compteur
		fwrite(&u_nbr,sizeof(unsigned int),1,u_db);

		for (i = 0; i < (u_nbr + 1); i++ ) {
			if ( strcmp(dump[i].u_id, u_id) != 0 ) {
				fwrite(&dump[i],sizeof(USER),1,u_db);
			}
		}

		sprintf(logIDrecord,"DelUser: Suppression avec succès de l'utilisateur [%s].",u_id);
		addLogInfo(logIDrecord);
		free(logIDrecord);
		fclose(u_db);
		return 0;		//Utilisateur supprimé avec succès
	}

	sprintf(logIDrecord,"DelUser: Echec lors de la suppression de l'utilisateur [%s].",u_id);
	addLogInfo(logIDrecord);
	free(logIDrecord);
	return 1; 		//Erreur fichier non existant
}
