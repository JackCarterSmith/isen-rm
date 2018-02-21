/*
 * backup.c
 *
 *  Created on: 2 févr. 2018
 *      Author: jackcartersmith
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "db.h"
#include "logger.h"

int backupDB() {
	time_t raw_time;
	struct tm *pdh;
	time(&raw_time);
	pdh = localtime(&raw_time);
	char name[32];
	int i;
	FILE *db = NULL;
	FILE *bck = NULL;
	HEAD *h = malloc(sizeof(HEAD));
	FICHE dump[h->nbr_fiches];

	if (getConfig(h) != 0) {
		addLogCritical("BackUP: Erreur de lecture de l'en-tête de la DB !");
		free(h);
		return 1;		//Problème dans la lecture du fichier
	}

	if (h->nbr_fiches <= 0) {
		printf("Cards missing, abort backup.\n");
		addLogInfo("BackUP: Aucune fiches, abandon.");
		free(h);
		return 0;
	}

	db = fopen("db.irm","rb");
	if (db != NULL){
		fseek(db, sizeof(HEAD), SEEK_SET);
		fread(dump, sizeof(FICHE), h->nbr_fiches, db);		//Le coeur de la function de dump des fiches en mémoire
		fclose(db);
		sprintf(name, "db_%04d-%02d-%02d.bck", pdh->tm_year+1900, pdh->tm_mon+1, pdh->tm_mday);
		bck = fopen(name,"rb");
		if (bck != NULL) {
			fclose(bck);
			char confirm = 'N';
			printf("ATTENTION ! Une sauvegarde est déjà présente, voulez-vous quand même l'écraser ? (N/O)");
			scanf(" %c", &confirm);
			if (confirm == 'N') {
				addLogWarn("BackUP: Bypass sauvegarde de démarrage.");
				free(h);
				return 2;
			} 			//Bypass backup procedure
		}

		bck = fopen(name,"wb+");
		if (bck == NULL) {
			addLogCritical("BackUP: Erreur création fichier backup.");
			free(h);
			return 3;
		}
		fseek(bck, 0, SEEK_SET);
		fwrite(h, sizeof(HEAD), 1, bck);
		for (i = 0; i < (h->nbr_fiches); i++ ) {
		//for (i = 0; i < sizeof(dump); i++ ) {
			fwrite(&dump[i], sizeof(FICHE), 1, bck);
		}
		fclose(bck);
	} else {
		addLogWarn("BackUP: DB absente, abandon.");
		free(h);
		return 4;
	}

	addLogInfo("BackUP: Création avec succès de la sauvegarde.");
	free(h);
	return 0;
}



int restoreDB(int day, int mounth, int year) {
	char name[32];
	int i;
	FILE *db = NULL;
	FILE *bck = NULL;
	HEAD *h = malloc(sizeof(HEAD));
	FICHE dump[h->nbr_fiches];

	sprintf(name, "db_%04d-%02d-%02d.bck", year, mounth, day);
	if (getConfigF(h,name) != 0) {
		addLogCritical("Recovery: Erreur de lecture de l'en-tête de la DB !");
		free(h);
		return 1;		//Problème dans la lecture du fichier
	}

	bck = fopen(name,"rb");
	if (bck != NULL){
		fseek(bck, sizeof(HEAD), SEEK_SET);
		fread(dump, sizeof(FICHE), h->nbr_fiches, bck);		//Le coeur de la function de dump des fiches en mémoire
		fclose(bck);

		char confirm = 'N';
		printf("ATTENTION ! Voulez-vous restaurer la sauvegarde ? (N/O)");
		scanf(" %c", &confirm);
		if (confirm == 'N') {
			addLogWarn("Recovery: Annulation procédure de restauration.");
			free(h);
			return 2;
		} 			//Cancel restoring

		db = fopen("db.irm","wb+");
		if (db == NULL) {
			addLogCritical("Recovery: Impossible d'ouvrir la DB.");
			free(h);
			return 3;
		}
		fseek(db, 0, SEEK_SET);
		fwrite(h, sizeof(HEAD), 1, db);
		for (i = 0; i < (h->nbr_fiches); i++ ) {
		//for (i = 0; i < sizeof(dump); i++ ) {
			fwrite(&dump[i], sizeof(FICHE), 1, db);
		}
		fclose(db);
	}

	addLogInfo("Recovery: Restauration avec succès de la DB.");
	free(h);
	return 0;
}
