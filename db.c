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

int getConfigF(HEAD *h, char db_file[]) {
	FILE *db = NULL;

	db = fopen(db_file,"rb");
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
	char *logIDrecord = malloc(sizeof(char)*64);

	if (getConfig(h) != 0) {
		addLogCritical("Add: Erreur de lecture de l'en-tête de la DB !");
		free(h);
		free(logIDrecord);
		return 1;		//Problème dans la lecture de l'entête du fichier
	}
	h->nbr_fiches += 1;

	db = fopen("db.irm","rb+");
	if (db != NULL){
		fseek(db, sizeof(float), SEEK_SET);
		fwrite(&h->nbr_fiches, sizeof(unsigned short int), 1, db);

		fseek(db, 0, SEEK_END);
		fwrite(data, sizeof(FICHE), 1, db);
		sprintf(logIDrecord,"Add: Fiche [%s] ajoutée avec succés dans la DB.",data->ID);
		addLogInfo(logIDrecord);
	} else {
		addLogCritical("Add: Erreur lors de l'ajout de la fiche dans la DB !");
		free(h);
		free(logIDrecord);
		return 2;		//Problème dans la lecture du fichier
	}

	free(h);
	free(logIDrecord);
	fclose(db);
	return 0;
}

int delCard(char id[]){
	FILE *db = NULL;
	HEAD *h = malloc(sizeof(HEAD));
	char *logIDrecord = malloc(sizeof(char)*64);
	int i;

	if (getConfig(h) != 0) {
		addLogCritical("Del: Erreur de lecture de l'en-tête de la DB !");
		free(h);
		free(logIDrecord);
		return 1;		//Problème dans la lecture du fichier
	}
	FICHE dump[h->nbr_fiches];

	db = fopen("db.irm","rb");
	if (db != NULL){
		if ( checkIDExist(id,h->nbr_fiches,db) == 0) {
			free(h);
			free(logIDrecord);
			fclose(db);
			addLogWarn("Del: L'id de la fiche spécifié n'est pas enregistré.");
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
		free(logIDrecord);
		addLogCritical("Del: Erreur lors de la suppression de la fiche dans la DB !");
		return 3;		//Problème dans la lecture du fichier
	}

	sprintf(logIDrecord,"Del: Fiche %s supprimée avec succés dans la DB.",id);
	addLogInfo(logIDrecord);
	free(h);
	free(logIDrecord);
	fclose(db);
	return 0;
}

int readCard(char id[], FICHE *f){
	FILE *db = NULL;
	HEAD *h = malloc(sizeof(HEAD));
	int i;

	if (getConfig(h) != 0) {
		addLogCritical("Read: Erreur de lecture de l'en-tête de la DB !");
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
			f->etat.Hardware = 0;
			f->etat.OS = 0;
			f->etat.Drivers = 0;
			f->etat.Software = 0;
			free(h);
			fclose(db);
			addLogWarn("Read: L'id de la fiche spécifié n'est pas enregistré.");
			return 2;			//Aucun fichier dans la DB correspond à l'ID spécifié
		}
		fseek(db, sizeof(HEAD), SEEK_SET);
		for (i = 0; i < ((h->nbr_fiches) + 1); i++ ) {
			fread(f, sizeof(FICHE), 1, db);

			if ( strcmp(f->ID, id) == 0 ) {
				free(h);
				fclose(db);
				addLogInfo("Read: Fiche récupérée avec succés dans la DB.");
				return 0;
			}
		}
	} else {
		addLogCritical("Read: Erreur lors de la lecture de la fiche dans la DB !");
		free(h);
		return 2;		//Problème dans la lecture du fichier
	}

	strcpy(f->CPU,"N/A");
	strcpy(f->MEM,"N/A");
	strcpy(f->HDD,"N/A");
	strcpy(f->Nom,"ERROR");
	strcpy(f->OS,"N/A");
	f->etat.Hardware = 0;
	f->etat.OS = 0;
	f->etat.Drivers = 0;
	f->etat.Software = 0;
	free(h);
	fclose(db);
	addLogCritical("Read: ID data value corrupted!");
	return 3;		//Erreur interne, id corrompu
}

int editCard(FICHE *data){
	FILE *db = NULL;
	FICHE *card = malloc(sizeof(FICHE));
	HEAD *h = malloc(sizeof(HEAD));
	char *logIDrecord = malloc(sizeof(char)*64);
	int i;

	if (getConfig(h) != 0) {
		addLogCritical("Edit: Erreur de lecture de l'en-tête de la DB !");
		free(h);
		free(card);
		return 1;		//Problème dans la lecture du fichier
	}

	db = fopen("db.irm","rb+");
	if (db != NULL){
		if ( checkIDExist(data->ID,h->nbr_fiches,db) == 0) {
			free(h);
			free(logIDrecord);
			free(card);
			fclose(db);
			addLogWarn("Edit: L'id de la fiche spécifié n'est pas enregistré.");
			return 2;			//Aucun fichier dans la DB correspond à l'ID spécifié
		}
		fseek(db, sizeof(HEAD), SEEK_SET);
		for (i = 0; i < ((h->nbr_fiches) + 1); i++ ) {
			fread(card, sizeof(FICHE), 1, db);

			if ( strcmp(card->ID, data->ID) == 0 ) {
				fseek(db, sizeof(HEAD), SEEK_SET);
				fseek(db, sizeof(FICHE) * i, SEEK_CUR);
				fwrite(data, sizeof(FICHE), 1, db);

				sprintf(logIDrecord,"Edit: Fiche [%s] éditée avec succés dans la DB.",data->ID);
				addLogInfo(logIDrecord);

				fclose(db);
				free(h);
				free(logIDrecord);
				free(card);
				return 0;
			}
		}
	} else {
		addLogCritical("Edit: Erreur lors de l'édition de la fiche dans la DB !");
		free(h);
		free(logIDrecord);
		free(card);
		return 3;		//Problème dans la lecture du fichier
	}

	free(h);
	free(logIDrecord);
	free(card);
	fclose(db);
	addLogCritical("Edit: ID data value corrupted!");
	return 4;		//Erreur interne, id corrompu
}

int sortReadyCard(FICHE *tab_f){
	FILE *db = NULL;
	FICHE *buffer = malloc(sizeof(FICHE));
	HEAD *h = malloc(sizeof(HEAD));
	int i;
	int t = 0;

	if (getConfig(h) != 0) {
		addLogCritical("SrtRdyCard: Erreur de lecture de l'en-tête de la DB !");
		free(h);
		free(buffer);
		return -1;		//Problème dans la lecture du fichier
	}

	db = fopen("db.irm","rb");
	if (db != NULL){
		fseek(db, sizeof(HEAD), SEEK_SET);
		for (i = 0; i < ((h->nbr_fiches) + 1); i++ ) {
			fread(buffer, sizeof(FICHE), 1, db);
			if ( buffer->etat.Hardware == 1 && buffer->etat.OS == 1 && buffer->etat.Drivers == 1 && buffer->etat.Software == 1 ) {
				t = t + 1;
			}
		}
		buffer = realloc(buffer,sizeof(FICHE) * t);
		for (i = 0; i < ((h->nbr_fiches) + 1); i++ ) {
			fread(buffer+t, sizeof(FICHE), 1, db);
			if ( (buffer+t)->etat.Hardware == 1 && (buffer+t)->etat.OS == 1 && (buffer+t)->etat.Drivers == 1 && (buffer+t)->etat.Software == 1 ) {
				t = t + 1;
			}
		}
		fclose(db);
	}

	tab_f = buffer;
	free(h);
	updateRdyCpt(t);
	return t;		//Retourne le nombre de fiche
}

void updateRdyCpt(int c){
	FILE *db = NULL;

	db = fopen("db.irm","rb+");
	if (db != NULL) {
		fseek(db,sizeof(float) + sizeof(unsigned short int) + sizeof(unsigned int),SEEK_SET);
		fwrite(&c,sizeof(int),1,db);
		fclose(db);
	}
}

