#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define ERROR -1


typedef struct censusCDT * censusADT;

/* crea un nuevo census */
censusADT newCensus();

/*completa el census con la informacion recibida */
int completeCensus(int condicion, long int id, char * depto, char * provincia, censusADT census);

/* Crea un archivo con la informacion de las provincias */
int province(censusADT census);

/* Crea un archivo con la informacion del pais */
int country(censusADT census);

/* Crea un archivo con la informacion del departamento */
int department(censusADT census);

/* libera el espacio reservado */
void freeCensus(censusADT census);
