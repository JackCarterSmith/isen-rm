/*
 * db_debug.c
 *
 *  Created on: 10 janv. 2018
 *      Author: are
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct head_db{
	float version_db;
	unsigned short int nbr_fiches;
	unsigned int cpt_rep_total;
}HEAD;

int getConfig(HEAD *h) {
	FILE *db = NULL;

	db = fopen("db.irm","rb");
	if (db != NULL) {
		fread(h, sizeof(HEAD), 1, db);
	} else {
		return -1;		//Problème dans la lecture du fichier
		//Ajouter d'une entrée dans le log !
	}
	
	fclose(db);
	return 0;
}

int main(){
	HEAD *dumped_data = NULL; 
	
	dumped_data = malloc(sizeof(HEAD));
	if (getConfig(dumped_data) != 0) {
		return -1;		//Problème dans la lecture du fichier
	}
	
	printf("int : %d\nfloat : %d\n",sizeof(int),sizeof(float));
	printf("Version : %f\nNbr de pc : %d\nCpt total rep : %d",dumped_data->version_db,dumped_data->nbr_fiches,dumped_data->cpt_rep_total);

	free(dumped_data);
	return 0;
}
