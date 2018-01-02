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
	 * Contenu de l'en-t�te :
	 * Version de la DB (float)
	 * Nombre d'entr�es (int)
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
		return -1;		//Probl�me dans la lecture du fichier
		//Ajouter d'une entr�e dans le log !
	}

	return 0;
}

int addCard(FICHE data){
	FILE *db = NULL;
	HEAD h;

	db = fopen("db.irm","rb+");
	if (db != NULL){
		fread(&h, sizeof(HEAD), 1, db);
		h.nbr_fiches += 1;
		fseek(db, 0, SEEK_SET);
		fwrite(&h, sizeof(HEAD), 1, db);

		fseek(db, 0, SEEK_END);
		fwrite(&data, sizeof(FICHE), 1, db);

		fclose(db);
	} else {
		return -1;		//Probl�me dans la lecture du fichier
		//Ajouter d'une entr�e dans le log !
	}

	return 0;
}

int delCard(int id){

}

FICHE readCard(int id){

}

int editCard(int id, FICHE data){

}

