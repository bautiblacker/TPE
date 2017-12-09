#include "backCenso.h"


typedef struct dep{
  char * name;
  int cant_personas;
  long int id;
  int employed;
  int unemployed;
  struct dep * next;
}tDep;

typedef struct prov{
  tDep * dptos;
  char * name;
  int cant;
  int employed;
  int unemployed;
  struct prov * nextProv;
}tProv;

struct censusCDT{
  tProv * firstProv;
  int cant_citizens;
  int employed;
  int unemployed;
};

censusADT newCensus()
{
  censusADT census;
  census = (censusADT)calloc(1, sizeof(struct censusCDT));
  return census;
}

static tDep * createDep(tDep * d, char * dpto, int condition, long int id)
{
  if(d == NULL || strcmp(dpto, d->name) < 0)
  {
    tDep * new = malloc(sizeof(tDep));
    if(new != NULL)
    {
      new->next = d;
      new->name = malloc(strlen(dpto) + 1);
      strcpy(new->name, dpto);
      new->id = id;
      new->cant_personas = 1;
      new->employed = 0;
      new->unemployed = 0;

      if(condition == 1)
        new->employed++;
      if(condition == 2)
        new->unemployed++;
    }

    return new;
  }

  if(strcmp(dpto, d->name) > 0)
  {
    d->next = createDep(d->next, dpto, condition, id);
    return d;
  }

  d->cant_personas++;
  if(condition == 1)
    d->employed++;
  else if(condition == 2)
    d->unemployed++;

  return d;
}

static tProv * createProv(tProv * n, char * province, char * dpto, int condition, long int id)
{
  if(n == NULL || strcmp(province, n->name) < 0)
  {
    tProv * new = malloc(sizeof(tProv));
    if(new != NULL)
    {
      new->name = malloc(strlen(province) + 1);
      strcpy(new->name, province);
      new->cant=1;
      new->nextProv = n;
      if(condition == 1)
      {
        new->employed++;
      }else if(condition == 2)
        new->unemployed++;

      new->dptos = createDep(n->dptos, dpto, condition, id);
    }

    return new;
  }

  if(strcmp(province, n->name) > 0)
  {
    n->nextProv = createProv(n->nextProv, province, dpto, condition, id);
    return n;
  }
  n->dptos = createDep(n->dptos, dpto, condition, id);
  return n;
}


int completeCensus(int condition, long int id, char * dpto, char * province, censusADT census)
{
  tProv * aux = createProv(census->firstProv, province, dpto, condition, id);
  if(aux != NULL)
  {
    if(census->firstProv == NULL)
      census-> firstProv = aux;

  census->cant_citizens++;
  if(condition == 1)
    census->employed++;
  else if(condition == 2)
    census->unemployed++;

    return 0;
  }


  return ERROR;
}

/*int province(censusADT census)
{
  FILE* province
}*/

int country(censusADT census)
{
  float indx = 0;
  FILE * country = fopen("Pais.csv", "wt");
  if(country == NULL)
    return ERROR;
  if(census->unemployed + census->employed != 0)
    indx = census->unemployed/(census->unemployed + census->employed);
  fprintf(country, "%d, %.2f\n", census->cant_citizens, indx);
  return fclose(country);
}

static void departmentR(FILE * department, tProv * n)
{
  float indx;
  while(n!=NULL)
  {
    while(n->dptos!=NULL)
    {
      indx = 0;
      if(n->dptos->unemployed + n->dptos->employed != 0)
        indx = (n->dptos->unemployed)/(n->dptos->unemployed + n->dptos->employed);
      fprintf(department, "%s, %s, %d, %.2f\n", n->name, n->dptos->name, n->dptos->cant_personas, indx);
      n->dptos=n->dptos->next;
    }
    n=n->nextProv;
  }
}

int department(censusADT census)
{
  FILE * department = fopen("Departamento.csv", "wt");
  if(department != NULL)
  {
    while(census->firstProv != NULL)
    {
      departmentR(department, census->firstProv);
      census->firstProv = census->firstProv->nextProv;
    }


    return fclose(department);
  }

  return ERROR;
}

/*void freeCensus(censusADT census)
{

}*/
