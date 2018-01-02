/*
 * db.h
 *
 *  Created on: 2 janv. 2018
 *      Author: are
 *
 *      DB Core
 */

#ifndef DB_H_
#define DB_H_

typedef struct head_db{
	float version_db;		//Pour la compatibilité et la migration des données
	int nbr_fiches;
	int cpt1;
	int cpt2;
}HEAD;

int regenDBFile();  //Regénère la base de donnée, la remplace si elle existe déjà. Retourne 0 quand aucun problème.
int backupDB();		//Créer une backup de la DB dans un sous dossier "backup"
int restoreDB();	//Restaure la DB à partir d'une backup --a réfléchir

#endif /* DB_H_ */
