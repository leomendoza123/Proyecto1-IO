#ifndef ARTICULO_H_
#define ARTICULO_H_
#include <stdio.h>
#include <stdlib.h>

typedef struct equipo {
   int valor;
   int mantenimiento;
   int ganancia;
} equipo_t;

 struct equipo* equipo_new(int valor, int mantenimiento, int ganancia) {
	  struct equipo* p = (equipo_t*)malloc(sizeof(equipo_t*));
	  p->valor = valor;
	  p->mantenimiento = mantenimiento;
	  p->ganancia = ganancia;
	  return p;
}



#endif
