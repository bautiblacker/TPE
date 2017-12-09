#include "backCenso.h"


/* Si hay algun error, libera el espacio reservado para censo y tira mensaje de error */
void error(int rta, censusADT census);

/* Recorre el archivo y va validando si hay memoria, y de ser asi llama a completaCenso */
int leerArchivo(censusADT census);

/* Crea los archivos pedidos por el enunciado */
int creaArchivos(censusADT census);


void error(int rta, censusADT census)
{
  //freecensus(census);

  if(rta == ERROR)
  {
    printf("No se pudo crear el archivo por falta de memoria\n");
  }else
    printf("no se pudo crear el archivo\n");
}


int leerArchivo(censusADT census)
{
  int rta = 0;
  char linea[80];
  int condicion;
  long int id;
  char dpto[80];
  char provincia[80];

  while(fgets(linea, 80, stdin)!=NULL && rta == 0)
  {
    if(linea[0] != '\n')
    {
      sscanf(linea, "%d, %ld, %s, %s \n", &condicion, &id, dpto, provincia);
      //printf("%s, %s\n", dpto, provincia);
      rta = completeCensus(condicion, id, dpto, provincia, census);
    }
  }


  return rta;
}

int creaArchivos(censusADT census)
{
    int flag = 0; //flag indica si hubo error o no al crear los archivos
    flag += country(census);
    //flag += Provincia(census);
    flag += department(census);
    //freecensus(census);

    return flag;
}
