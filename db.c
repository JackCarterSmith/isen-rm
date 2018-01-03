/*
 * db.c
 *
 *  Created on: 2 janv. 2018
 *      Author: are
 *
 *      DB Core
 */
#define VERSION 1.0
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "db.h"

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
	 * Compteur 1 (int)
	 * Compteur 2 (int)
	 */
	FILE *db = NULL;
	HEAD default_head_data;

	db = fopen("db.irm","wb+");
	if (db != NULL){
		default_head_data.version_db = VERSION;
		default_head_data.nbr_fiches = 0;
		default_head_data.cpt1 = 0;
		default_head_data.cpt2 = 0;
		fwrite(&default_head_data, sizeof(HEAD), 1, db);

		fclose(db);
	} else {
		return -1;		//Problème dans la lecture du fichier
		//Ajouter d'une entrée dans le log !
	}

	return 0;
}

int getConfig(HEAD *h) {
	FILE *db = NULL;

	db = fopen("db.irm","rb");
	if (db != NULL) {
		fread(h, sizeof(HEAD), 1, db);
		fclose(db);
	} else {
		return -1;		//Problème dans la lecture du fichier
		//Ajouter d'une entrée dans le log !
	}

	return 0;
}

int addCard(FICHE data){
	FILE *db = NULL;
	HEAD *h = NULL;

	if (getConfig(h) != 0) {
		return -1;		//Problème dans la lecture du fichier
		//Ajouter d'une entrée dans le log !
	}
	h->nbr_fiches += 1;

	db = fopen("db.irm","rb+");
	if (db != NULL){
		fseek(db, 0, SEEK_SET);
		fwrite(h, sizeof(HEAD), 1, db);

		fseek(db, 0, SEEK_END);
		fwrite(&data, sizeof(FICHE), 1, db);

		fclose(db);
	} else {
		return -2;		//Problème dans la lecture du fichier
		//Ajouter d'une entrée dans le log !
	}

	return 0;
}

int delCard(char id[]){
	FILE *db = NULL;
	HEAD *h = NULL;
	int i;

	if (getConfig(h) != 0) {
		return -1;		//Problème dans la lecture du fichier
		//Ajouter d'une entrée dans le log !
	}
	FICHE dump[h->nbr_fiches];

	db = fopen("db.irm","rb+");
	if (db != NULL){
		fseek(db, sizeof(HEAD), SEEK_SET);
		fread(dump, sizeof(FICHE), h->nbr_fiches, db);		//Le coeur de la function de dump des fiches en mémoire

		h->nbr_fiches -= 1;
		fseek(db, 0, SEEK_SET);
		fwrite(h, sizeof(HEAD), 1, db);

		for (i = 0; i < ((h->nbr_fiches) + 1); i++ ) {
			if ( strcmp(dump[i].ID, id) != 0 ) {
				fwrite(&dump[i], sizeof(FICHE), 1, db);
			}
		}

		fclose(db);
	} else {
		return -2;		//Problème dans la lecture du fichier
		//Ajouter d'une entrée dans le log !
	}

	return 0;
}

int readCard(char id[], FICHE *f){
	FICHE *card = NULL;
	FILE *db = NULL;
	HEAD *h = NULL;
	int i;

	if (getConfig(h) != 0) {
		return -1;		//Problème dans la lecture du fichier
		//Ajouter d'une entrée dans le log !
	}

	db = fopen("db.irm","rb+");
	if (db != NULL){
		fseek(db, sizeof(HEAD), SEEK_SET);
		for (i = 0; i < ((h->nbr_fiches) + 1); i++ ) {
			fread(card, sizeof(FICHE), 1, db);

			if ( strcmp(card->ID, id) == 0 ) {
				return 0;
			}
		}

		fclose(db);
	} else {
		return -2;		//Problème dans la lecture du fichier
		//Ajouter d'une entrée dans le log !
	}

	return -1;			//Aucun fichier dans la DB correspond à l'ID spécifié
	//Ajouter d'une entrée dans le log !
}

int editCard(FICHE data){
	return 0;
}

