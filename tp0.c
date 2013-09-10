#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERSION 3

// Definicion de funcines

int procesarArchivo(FILE* fd);

// Funcion principal
int main(int argc, char** argv) {
	int status = 0;

	if (argc == 2) {
		if (strcmp(argv[1], "-V") == 0) {
			printf("Version: %d\n", VERSION);
			return 0;
		}
		if (strcmp(argv[1], "-h") == 0) {
			printf("Comandos y argumentos disponibles:\n");
			printf("-V Version del programa\n");
			printf("[File...] (Archivo/s de entrada)\n");
			printf(
					"En caso de no pasar archivos se toma la entrada estandar\n");
			printf("Cada linea se cuenta hasta un enter\n");
			printf(
					"Para finalizar el programa estando con la entrada estandar");
			printf(" pulsar 'ctrl+d' para un correcto cierre del mismo");
			// Y cualquier otra cosa que se quiera agregar
			return 0;
		}
	}
	if (argc == 1) {
		status = procesarArchivo(stdin);
	} else {
		int arch = 1;
		FILE* entrada;
		while (arch < argc) {
			entrada = fopen(argv[arch], "r");
			if (!entrada) {
				fprintf(stderr, "No se pudo abrir el archivo: %s\n",
						argv[arch]);
				return 1;
			}
			status = procesarArchivo(entrada);
			if (status)
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
int procesarArchivo(FILE* fd) {
	int nextChar = fgetc(fd);
	size_t sizeOfChar = sizeof(unsigned char);
	unsigned char* line = malloc(sizeOfChar);
	if (!line) {
		fprintf(stderr, "Problema al querer alocar memoria\n");
		return -1;
	}
	int lineWidth = 0;
	int result = 0;
	int aux_special;
	while (nextChar != EOF) {
		if (nextChar > 127) { // Para solucionar tema de caracteres especiales
			lineWidth += 2;
			line = (unsigned char*) realloc(line, lineWidth * sizeOfChar);
			if (!line) {
				fprintf(stderr, "Problema al querer alocar memoria\n");
				return -1;
			}
			aux_special = nextChar;
			nextChar = fgetc(fd);
			line[lineWidth - 2] = (unsigned char) nextChar;
			line[lineWidth - 1] = (unsigned char) aux_special;
			nextChar = fgetc(fd);
			continue;
		}
		if (nextChar != '\n') {
			lineWidth++;
			line = (unsigned char*) realloc(line, lineWidth * sizeOfChar);
			if (!line) {
				fprintf(stderr, "Problema al querer alocar memoria\n");
				return -1;
			}
			line[lineWidth - 1] = (unsigned char) nextChar;
		} else {
			unsigned char* inverseLine = (unsigned char*) malloc(
					(lineWidth + 1) * sizeOfChar);
			for (int pos = 0; pos < lineWidth; pos++) {
				inverseLine[pos] = line[(lineWidth - 1) - pos];
			}
			inverseLine[lineWidth] = '\n';
			int outStatus = fwrite(inverseLine, sizeOfChar, lineWidth + 1,
					stdout);
			if (outStatus != lineWidth + 1) {
				fprintf(stderr, "Error al escribir en salida\n");
				result = 2;
			}
			free(inverseLine);
			lineWidth = 0;
		}
		nextChar = fgetc(fd);
	}
	free(line);
	return result;
}
