/*
 * db.h
 *
 *  Created on: 2 janv. 2018
 *      Author: are
 *
 *      DB Core - v1
 */

#ifndef DB_H_
#define DB_H_

int regenDBFile();  //Regénère la base de donnée, la remplace si elle existe déjà. Retourne 0 quand aucun problème.
int backupDB();		//Créer une backup de la DB dans un sous dossier "backup"
int restoreDB();	//Restaure la DB à partir d'une backup --a réfléchir

#endif /* DB_H_ */
