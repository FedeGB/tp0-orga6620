#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERSION 2

// Definicion de funcines

int procesarArchivo(FILE* fd);

// Funcion principal
int main(int argc, char** argv) {
	int status = 0;
	
	if(argc == 2) {
		if(strcmp(argv[1], "-V") == 0) {
			printf("Version: %d\n", VERSION);
			// No se si solo eso :P
			return 0;
		}
		if(strcmp(argv[1], "-h") == 0) {
			printf("Comandos y argumentos disponibles:\n");
			printf("-V Version del programa\n");
			printf("[File...] (Archivo/s de entrada)\n");
			// Y cualquier otra cosa que se quiera agregar
			return 0;
		}
	}
	if(argc == 1) {
		status = procesarArchivo(stdin);
	}
	else{
		int arch = 1;
		FILE* entrada;
		while(arch < argc) {
			entrada = fopen(argv[arch], "r");
			if(!entrada) {
				fprintf(stderr, "No se pudo abrir el archivo: %s\n", argv[arch]);
				return 1;
			}
			status = procesarArchivo(entrada);
			if(status)
				return status;
			fclose(entrada);
			entrada = NULL;
			arch++;
		}
	}
	return status;
	
}

// Procesa el archivo de entrada (puede ser stdin)
// Invierte las lineas del archivo y las imprime por stdout
// En caso satisfactorio devuelve 0, distinto de 0 en otros casos
int procesarArchivo(FILE* fd){
	int nextChar = fgetc(fd);
	size_t sizeOfChar = sizeof(unsigned char);
	unsigned char* line = malloc(sizeOfChar);
	int lineWidth = 0;
	int result = 0;
	while(nextChar != EOF) {
		if(nextChar != '\n') {
			lineWidth++;
			line = (unsigned char*) realloc(line,lineWidth*sizeOfChar);
			line[lineWidth - 1] = (unsigned char) nextChar;
		} else {
			unsigned char* inverseLine = (unsigned char*) malloc((lineWidth + 1)*sizeOfChar);
			for(int pos = 0; pos < lineWidth; pos++){
				inverseLine[pos] = line[(lineWidth - 1) - pos];
			}
			inverseLine[lineWidth] = '\n';
			int outStatus = fwrite ( inverseLine, sizeOfChar, lineWidth + 1, stdout);
			free(inverseLine);
			lineWidth = 0;
		}
		nextChar = fgetc(fd);
	}
	return result;
}

