/*
 * backup.c
 *
 *  Created on: 16 févr. 2018
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
	char name[64];
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
			printf("ATTENTION ! Une sauvegarde est déjà présente, voulez-vous quand même l'écraser ? (N/o)");
			scanf(" %c", &confirm);
			if (confirm == 'N') {
				addLogWarn("BackUP: Override sauvegarde de démarrage.");
				free(h);
				return 1;
			} 			//Override backup procedure
		}
		fopen(name,"wb+");
		fseek(db, 0, SEEK_SET);
		fwrite(h, sizeof(HEAD), 1, db);
		for (i = 0; i < (h->nbr_fiches); i++ ) {
		//for (i = 0; i < sizeof(dump); i++ ) {
			fwrite(&dump[i], sizeof(FICHE), 1, db);
		}
		fclose(bck);
	}

	addLogInfo("BackUP: Création avec succès de la DB.");
	free(h);
	return 0;
}

int restoreDB() {
	return 0;
}
