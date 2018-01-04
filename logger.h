/*
 * logger.h
 *
 *  Created on: 4 janv. 2018
 *      Author: are
 */

#ifndef LOGGER_H_
#define LOGGER_H_

int initialise_logger();		//Prépare le logger à écrire dans les fichiers de logs
void stop_logger();

void addLogInfo(char *mess);		//Ajoute une entrée dans le fichier de log de type INFO
void addLogWarn(char *mess);
void addLogCritical(char *mess);	//Ajoute une entrée dans le fichier de log de type CRITICAL

#endif /* LOGGER_H_ */
