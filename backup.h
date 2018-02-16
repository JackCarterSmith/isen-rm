/*
 * backup.h
 *
 *  Created on: 16 févr. 2018
 *      Author: jackcartersmith
 */

#ifndef BACKUP_H_
#define BACKUP_H_

int backupDB();		//Créer une backup de la DB dans un sous dossier "backup"
int restoreDB();	//Restaure la DB à partir d'une backup --a réfléchir

#endif /* BACKUP_H_ */
