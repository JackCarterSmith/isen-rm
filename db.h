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

int regenDBFile();  //Reg�n�re la base de donn�e, la remplace si elle existe d�j�. Retourne 0 quand aucun probl�me.
int backupDB();		//Cr�er une backup de la DB dans un sous dossier "backup"
int restoreDB();	//Restaure la DB � partir d'une backup --a r�fl�chir

#endif /* DB_H_ */
