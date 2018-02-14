/*
 * db.c
 *
 *  Created on: 2 janv. 2018
 *      Author: are
 *
 *      DB Core
 */
#define VERSION 1.3
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "db.h"
#include "logger.h"

int regenDBFile(){
	/*
	 * Template DB :
	 * <HEAD>
	 * 	conf_opt(value)
	 * 	...
	 * </HEAD>
	 * <DATA>
	 * 	<FICHEx>
	 * 	</FICHEx>
	 * </DATA>
	 *
	 * Contenu de l'en-tête :
	 * Version de la DB (float)
	 * Nombre d'entrées (int)
	 * Compteur de pc réparé totaux (uint)
	 * Compteur de pc prêt à être expédié (uint)
	 */
	FILE *db = NULL;
	HEAD default_head_data;

	db = fopen("db.irm","wb+");
	if (db != NULL){
		default_head_data.version_db = VERSION;
		default_head_data.nbr_fiches = 0;
		default_head_data.cpt_rep_total = 0;
		default_head_data.cpt_ready2go = 0;
		fwrite(&default_head_data, sizeof(HEAD), 1, db);

		fclose(db);
	} else {
		addLogCritical("DB creation failure !");
		return 1;		//Problème dans la lecture du fichier
	}

	addLogInfo("DB regenerated !");
	return 0;
}

int getConfig(HEAD *h) {
	FILE *db = NULL;

	db = fopen("db.irm","rb");
	if (db != NULL) {
		fread(h, sizeof(HEAD), 1, db);
		fclose(db);
	} else {
		return 1;		//Problème dans la lecture du fichier
		//Ajouter d'une entrée dans le log !
	}

	return 0;
}

int checkIDExist(char id[], unsigned short int max_fiches, FILE *f) {
	int i;
	FICHE dump;

	fseek(f, sizeof(HEAD), SEEK_SET);
	for (i = 0; i < max_fiches; i++) {
		fread(&dump, sizeof(FICHE), 1, f);
		if ( strcmp(dump.ID, id) == 0 ) { return 1; }	//Retourne 1 si l'id est présent
	}
	return 0;	//0 dans le cas contraire
}

int addCard(FICHE *data){
	FILE *db = NULL;
	HEAD *h = malloc(sizeof(HEAD));

	if (getConfig(h) != 0) {
		addLogCritical("Erreur de lecture de l'en-tête de la DB !");
		free(h);
		return 1;		//Problème dans la lecture du fichier
	}
	h->nbr_fiches += 1;

	db = fopen("db.irm","rb+");
	if (db != NULL){
		fseek(db, sizeof(float), SEEK_SET);
		fwrite(&h->nbr_fiches, sizeof(unsigned short int), 1, db);

		fseek(db, 0, SEEK_END);
		fwrite(data, sizeof(FICHE), 1, db);
		//Ajouter l'ID dans le log
		addLogInfo("Fiche %s ajoutée avec succés dans la DB.");
	} else {
		addLogCritical("Erreur lors de l'ajout de la fiche dans la DB !");
		free(h);
		return 2;		//Problème dans la lecture du fichier
	}

	free(h);
	fclose(db);
	return 0;
}

int delCard(char id[]){
	FILE *db = NULL;
	HEAD *h = malloc(sizeof(HEAD));
	int i;

	if (getConfig(h) != 0) {
		addLogCritical("Erreur de lecture de l'en-tête de la DB !");
		free(h);
		return 1;		//Problème dans la lecture du fichier
	}
	FICHE dump[h->nbr_fiches];

	db = fopen("db.irm","rb");
	if (db != NULL){
		if ( checkIDExist(id,h->nbr_fiches,db) == 0) {
			free(h);
			fclose(db);
			addLogWarn("L'id de la fiche spécifié n'est pas enregistré.");
			return 2;			//Aucun fichier dans la DB correspond à l'ID spécifié
		}
		fseek(db, sizeof(HEAD), SEEK_SET);
		fread(dump, sizeof(FICHE), h->nbr_fiches, db);		//Le coeur de la function de dump des fiches en mémoire

		h->nbr_fiches -= 1;
		db = freopen("db.irm","wb",db);
		fseek(db, 0, SEEK_SET);
		fwrite(h, sizeof(HEAD), 1, db);

		for (i = 0; i < ((h->nbr_fiches) + 1); i++ ) {
			if ( strcmp(dump[i].ID, id) != 0 ) {
				fwrite(&dump[i], sizeof(FICHE), 1, db);
			}
		}
	} else {
		free(h);
		addLogCritical("Erreur lors de la suppression de la fiche dans la DB !");
		return 3;		//Problème dans la lecture du fichier
	}

	free(h);
	fclose(db);
	addLogInfo("Fiche supprimée avec succés dans la DB.");
	return 0;
}

int readCard(char id[], FICHE *f){
	FILE *db = NULL;
	HEAD *h = malloc(sizeof(HEAD));
	int i;

	if (getConfig(h) != 0) {
		addLogCritical("Erreur de lecture de l'en-tête de la DB !");
		free(h);
		return 1;		//Problème dans la lecture du fichier
	}

	db = fopen("db.irm","rb");
	if (db != NULL){
		if ( checkIDExist(id,h->nbr_fiches,db) == 0) {
			strcpy(f->CPU,"N/A");
			strcpy(f->MEM,"N/A");
			strcpy(f->HDD,"N/A");
			strcpy(f->Nom,"ERROR");
			strcpy(f->OS,"N/A");
			f->Etat = 0;
			free(h);
			fclose(db);
			addLogWarn("L'id de la fiche spécifié n'est pas enregistré.");
			return 2;			//Aucun fichier dans la DB correspond à l'ID spécifié
		}
		fseek(db, sizeof(HEAD), SEEK_SET);
		for (i = 0; i < ((h->nbr_fiches) + 1); i++ ) {
			fread(f, sizeof(FICHE), 1, db);

			if ( strcmp(f->ID, id) == 0 ) {
				free(h);
				fclose(db);
				addLogInfo("Fiche récupérée avec succés dans la DB.");
				return 0;
			}
		}
	} else {
		addLogCritical("Erreur lors de la lecture de la fiche dans la DB !");
		free(h);
		return 2;		//Problème dans la lecture du fichier
	}

	strcpy(f->CPU,"N/A");
	strcpy(f->MEM,"N/A");
	strcpy(f->HDD,"N/A");
	strcpy(f->Nom,"ERROR");
	strcpy(f->OS,"N/A");
	f->Etat = 0;
	free(h);
	fclose(db);
	addLogCritical("ID data value corrupted!");
	return 3;		//Erreur interne, id corrompu
}

int editCard(FICHE *data){
	FILE *db = NULL;
	FICHE *card = malloc(sizeof(FICHE));
	HEAD *h = malloc(sizeof(HEAD));
	int i;

	if (getConfig(h) != 0) {
		addLogCritical("Erreur de lecture de l'en-tête de la DB !");
		free(h);
		free(card);
		return 1;		//Problème dans la lecture du fichier
	}

	db = fopen("db.irm","rb+");
	if (db != NULL){
		if ( checkIDExist(data->ID,h->nbr_fiches,db) == 0) {
			free(h);
			free(card);
			fclose(db);
			addLogWarn("L'id de la fiche spécifié n'est pas enregistré.");
			return 2;			//Aucun fichier dans la DB correspond à l'ID spécifié
		}
		fseek(db, sizeof(HEAD), SEEK_SET);
		for (i = 0; i < ((h->nbr_fiches) + 1); i++ ) {
			fread(card, sizeof(FICHE), 1, db);

			if ( strcmp(card->ID, data->ID) == 0 ) {
				fseek(db, sizeof(HEAD), SEEK_SET);
				fseek(db, sizeof(FICHE) * i, SEEK_CUR);
				fwrite(data, sizeof(FICHE), 1, db);

				fclose(db);
				free(h);
				free(card);
				addLogInfo("Fiche éditée avec succés dans la DB.");
				return 0;
			}
		}
	} else {
		addLogCritical("Erreur lors de l'édition de la fiche dans la DB !");
		free(h);
		free(card);
		return 3;		//Problème dans la lecture du fichier
	}

	free(h);
	free(card);
	fclose(db);
	addLogCritical("ID data value corrupted!");
	return 4;		//Erreur interne, id corrompu
}

