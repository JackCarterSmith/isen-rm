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
	unsigned short int nbr_fiches;
	unsigned int cpt_rep_total;
}HEAD;

typedef struct fiche { //En gros, la config du PC.
	char ID[11];
    char Nom[128];
    char CPU[16];
    char HDD[8];
    char MEM[8];
    char OS[32];
    unsigned short int Etat; 	//Par d�faut 0x0 soit 0000 en base 2
}FICHE;

extern FICHE Fiche;


int regenDBFile();  //Reg�n�re la base de donn�e, la remplace si elle existe d�j�. Retourne 0 quand aucun probl�me.
int getConfig(HEAD *h);		//R�cup�re la config enregistrer dans le HEAD de la DB et l'enregistre dans le pointeur fourni

int addCard(FICHE *data);		//Ajouter une fiche
int delCard(char id[]);			//Supprimer une fiche
int readCard(char id[], FICHE *f);			//R�cup�rer les datas d'une fiche
int editCard(FICHE *data);	//Editer les datas d'une fiche

int backupDB();		//Cr�er une backup de la DB dans un sous dossier "backup"
int restoreDB();	//Restaure la DB � partir d'une backup --a r�fl�chir

#endif /* DB_H_ */
