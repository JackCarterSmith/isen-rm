/*
 * logger.c
 *
 *  Created on: 4 janv. 2018
 *      Author: are
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "logger.h"

FILE *log_file=NULL;

int initialise_logger(){
	time_t raw_time;
	struct tm *pdh;
	time(&raw_time);
	pdh = localtime(&raw_time);
	char name[64];
	sprintf(name, "%04d-%02d-%02d.log", pdh->tm_year+1900, pdh->tm_mon+1, pdh->tm_mday);
	log_file=fopen(name, "a");

	if(log_file==NULL) //fichier innexistant
	{
		log_file=fopen(name,"w+");

		if(log_file==NULL) //Le prog n'a pas les droits en �criture
			return -1;
	}

	return 0;
}

void stop_logger() {fclose(log_file);}

void addLogInfo(char *mess){
	time_t now;
	struct tm* tm_info;
	char buffer[12];

	time(&now);
	tm_info = localtime(&now);
	strftime(buffer, 12, "%H:%M:%S", tm_info);
	fprintf(log_file,"[INFO][%s] %s\n", buffer, mess);
}

void addLogWarn(char *mess){
	time_t now;
	struct tm* tm_info;
	char buffer[12];

	time(&now);
	tm_info = localtime(&now);
	strftime(buffer, 12, "%H:%M:%S", tm_info);
	fprintf(log_file,"[WARN][%s] %s\n", buffer, mess);
}

void addLogCritical(char *mess){
	time_t now;
	struct tm* tm_info;
	char buffer[12];

	time(&now);
	tm_info = localtime(&now);
	strftime(buffer, 12, "%H:%M:%S", tm_info);
	fprintf(log_file,"[CRITICAL][%s] %s\n", buffer, mess);
}
