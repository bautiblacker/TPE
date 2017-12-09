#include "FrontCenso.c"

int main()
{
  censusADT censo=newCensus();

  int rta = leerArchivo(censo);
  rta = creaArchivos(censo);
  printf("%d\n", rta);
  return 0;
}
