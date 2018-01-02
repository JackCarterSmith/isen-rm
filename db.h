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
	float version_db;		//Pour la compatibilit� et la migration des donn�es
	int nbr_fiches;
	int cpt1;
	int cpt2;
}HEAD;


int regenDBFile();  //Reg�n�re la base de donn�e, la remplace si elle existe d�j�. Retourne 0 quand aucun probl�me.

int addCard(FICHE data);		//Ajouter une fiche
int delCard(int id);			//Supprimer une fiche
FICHE readCard(int id);			//R�cup�rer les datas d'une fiche
int editCard(int id, FICHE data);	//Editer les datas d'une fiche

int backupDB();		//Cr�er une backup de la DB dans un sous dossier "backup"
int restoreDB();	//Restaure la DB � partir d'une backup --a r�fl�chir

#endif /* DB_H_ */
