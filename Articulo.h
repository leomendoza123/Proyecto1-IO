/*
 * articulo.h
 *
 *  Created on: Mar 27, 2016
 *      Author: patrick
 */

#ifndef ARTICULO_H_
#define ARTICULO_H_
#include <stdio.h>
#include <stdlib.h>

typedef struct articulo {
   char nombre;
   int beneficio;
   int costo;
} articulo_t;

 struct articulo* articulo_new(char nombre, int beneficio, int costo) {
	  struct articulo* p = (articulo_t*)malloc(sizeof(articulo_t*));
	  p->nombre = nombre;
	  p->beneficio = beneficio;
	  p->costo = costo;
	  return p;
}



#endif
