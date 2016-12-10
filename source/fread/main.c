#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	
	printf("Hello World!\n");
	
	char *aux = malloc(21);	
	printf("aux: %lu\n", sizeof(aux));
	
	strcpy(aux, "dddddhhhhhdddddhhhhh");
	free(aux);
	
	char aux1[11];	
	printf("aux1: %lu\n", sizeof(aux1));
	
	/* --- */
	
	FILE *file;
	file = fopen("holaMundo.txt", "r");
	
	char *buffer;	

	if (file) {

		fseek(file, 0, SEEK_END);
		long fsize = ftell(file);
		fseek(file, 0, SEEK_SET);
		
		buffer = malloc(fsize + 1);	
		printf("fsize: %lu\n", fsize);
		printf("sizeof(buffer): %lu\n", sizeof(buffer));

		fread(buffer, fsize, 1, file);
		buffer[fsize] = '\0';

		printf("buffer: %s\n", buffer);
		printf("sizeof(buffer): %lu\n", sizeof(buffer));
		printf("strlen(buffer): %lu\n", strlen(buffer));

	}

	free(buffer);
	fclose(file);	
	

	/* --- */

	return 0;  
} 
