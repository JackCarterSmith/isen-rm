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
	float version_db;		//Pour la compatibilité et la migration des donn�es
	unsigned short int nbr_fiches;
	unsigned int cpt_ready2go;
	unsigned int cpt_rep_total;
}HEAD;

typedef struct stat_pc { 	 //Structure de booleens. Chaque variable prend 1 si le PC comporte le module correspondant.
    int Hardware;
    int OS;
    int Drivers;
    int Software;
}ETAT;

typedef struct fiche { //En gros, la config du PC.
	char ID[11];
    char Nom[128];
    char CPU[16];
    char HDD[8];
    char MEM[8];
    char OS[32];
    ETAT etat; 	//Par défaut 0x0 soit 0000 en base 2
    int locked;
}FICHE;

extern FICHE Fiche;


int regenDBFile();  //Regénère la base de donnée, la remplace si elle existe déjà. Retourne 0 quand aucun problème.
int getConfig(HEAD *h);		//Récupère la config enregistrer dans le HEAD de la DB et l'enregistre dans le pointeur fourni.
int getConfigF(HEAD *h, char db_file[]);		//Récupère la config enregistrer dans le HEAD dans le fichier DB spécifié et l'enregistre dans le pointeur fourni.

int sortReadyCard(FICHE *tab_f);		//Function de recherche pc prêt (ETAT = 1 partout), retourne le nombre de pc compté et rempli le tableau fourni
void updateRdyCpt(unsigned int c);		//Modifi le compteur dans le HEAD de la DB

void initCard(FICHE *f);		//Permet de purger les zones mémoire du tas afin d'éviter de 'salir' la DB avec des fausses données.
int checkCardStatus(char id[], unsigned short int max_fiches, FILE *f);			//Vérifie si la fiche est verrouillé ou non.
int addCard(FICHE *data);		//Ajouter une fiche
int delCard(char id[]);			//Supprimer une fiche
int readCard(char id[], FICHE *f);			//Récupèrer les datas d'une fiche
int editCard(FICHE *data);	//Editer les datas d'une fiche
int validCard(char id[]);	//Valide et rends la fiche non editable par la suite

#endif /* DB_H_ */
