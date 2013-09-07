#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERSION 0.1

// Definicion de funcines

int abrirArchivo(char* path, FILE* fd, char* mode);

// Funcion principal
int main(int argc, char** argv) {
	
	if(argc > 3) {
		fprintf(stderr, "Cantidad de argumentos invalidos\n");
		return 1;
	}
	FILE* entrada = NULL;
	FILE* salida = NULL;
	int status = 0;
	
	if(argc == 2) {
		if(strcmp(argv[1], "-V") == 0) {
			printf("Version: %d\n", VERSION);
			// No se si solo eso :P
			return 0;
		}
		if(strcmp(argv[1], "-h") == 0) {
			printf("Comandos disponibles:\n");
			printf("-V Version del programa\n");
			printf("<archivo entrada> <archivo salida>\n");
			printf("<archivo salida> (Toma entrada estandar\n");
			// Y cualquier otra cosa que se quiera agregar
			return 0;
		}
		else {
			status = abrirArchivo(argv[1], salida, "w");
			if(status)
				return status;		
		}
	}
	if(argc == 3) {
		status = abrirArchivo(argv[1], entrada, "r");
		status = abrirArchivo(argv[2], salida, "w");
		if(status)
			return status;
	}
	
	status = rev(entrada, salida);
	
	return status;
	
}

// Abre el archivo con el modo que se le pase por parametro
// Retorna 0 en caso satisfactorio, distinto de 0 en caso contrario
int abrirArchivo(char* path, FILE* fd, char* mode) {
	fd = fopen(path, mode);
	if(!fd) {
		fprintf(stderr, "No se pudo abrir el archivo: %s\n", path);
		return 1;
	}
	return 0;
}

int rev(FILE* entrada, FILE* salida) {
	if(!entrada){
		// Tomamos de la entrada estandar
	}
	// Sino procesamos del archivo de entrada
	
	return 0;
}
