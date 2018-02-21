/*
 * backup.h
 *
 *  Created on: 2 févr. 2018
 *      Author: jackcartersmith
 */

#ifndef BACKUP_H_
#define BACKUP_H_

int backupDB();		//Créer une backup de la DB dans un sous dossier "backup"
int restoreDB(int day, int mounth, int year);	//Restaure la DB à partir d'une backup

#endif /* BACKUP_H_ */
