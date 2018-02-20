/*
 * db_debug.c
 *
 *  Created on: 10 janv. 2018
 *      Author: are
 */
#include <stdio.h>
#include <stdlib.h>
#include "users.h"

int main(){
	FILE *u_login = NULL;
    USER *u = malloc(sizeof(USER));
	int process;
	
	u_login = fopen("users.crd","rb");
    if (u_login == NULL) { u_newSetup(); }
    fclose(u_login);
	
	printf("u_ID to write: ");
	scanf("%s",u->u_id);
	printf("u_PIN to write: ");
	scanf("%s",u->u_pin);
	printf("u_rank to write (0-4): ");
	scanf("%d",&(u->u_rank));
	
	process = addUser(u);
	printf("Result : %d", process);

	return 0;
}
