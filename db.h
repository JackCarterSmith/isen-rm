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
    unsigned short int Etat; 	//Par défaut 0x0 soit 0000 en base 2
}FICHE;

extern FICHE Fiche;


int regenDBFile();  //Regénère la base de donnée, la remplace si elle existe déjà. Retourne 0 quand aucun problème.
int getConfig(HEAD *h);		//Récupère la config enregistrer dans le HEAD de la DB et l'enregistre dans le pointeur fourni

int addCard(FICHE *data);		//Ajouter une fiche
int delCard(char id[]);			//Supprimer une fiche
int readCard(char id[], FICHE *f);			//Récupérer les datas d'une fiche
int editCard(FICHE *data);	//Editer les datas d'une fiche

int backupDB();		//Créer une backup de la DB dans un sous dossier "backup"
int restoreDB();	//Restaure la DB à partir d'une backup --a réfléchir

#endif /* DB_H_ */
