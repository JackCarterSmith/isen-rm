/*
 * users.h
 *
 *  Created on: 10 févr. 2018
 *      Author: are
 */

#ifndef USERS_H_
#define USERS_H_

typedef struct user { 		//Struct utilisateur
	char u_id[9];
	char u_pin[5];
	unsigned int u_rank;
}USER;

void u_newSetup();	//Nouvelle installation
int userLogin(USER *u);		//login utilisateur
int addUser(USER *u);		//Ajouter utilisateur au fichier
int delUser(char *u_id);		//Supprimer utilisateur du fichier

#endif /* USERS_H_ */
