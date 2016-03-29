#define _GNU_SOURCE
#include "Articulo.h"
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <assert.h>


int mayor(int a, int b){
	if(a<b){
		return(b);
	}
	else
		return(a*-1);
}

void imprimirRuta(int tareas, int tope, int x, int y, int lista_acumulado[tareas][tope], articulo_t* lista_articulos[tareas]){
	int contX = x;
	int contY = y;
	if(y != 0){
		if(lista_acumulado[contX][contY] < 0){
				printf("%c, ", lista_articulos[contX]->nombre);
				imprimirRuta(tareas,tope,x-1,y-lista_articulos[contX]->costo, lista_acumulado, lista_articulos);
			}
			else
				imprimirRuta(tareas,tope,x-1,y,lista_acumulado,lista_articulos);
	}
	else
		printf("\n");


}

void imprimirResultado(int x, int y, int lista_acumulado[x][y], articulo_t* lista_articulos[x]){
	int contX = 0;
	int contY = 0;
	while(contY != y){
		while(contX != x){
			if(contY == 0 && contX == 0){
				while(contX != x){
					printf("%c ", lista_articulos[contX]->nombre);
					contX++;
				}
				printf("\n");
				printf("%d ", lista_acumulado[contX][contY]);
				contX = 1;
			}
			printf("%d ", lista_acumulado[contX][contY]);
			contX++;

		}
		printf("\n");
		contX = 0;
		contY++;
	}
}

void imprimirTarea(int x, int y,int lista_acumulado[x][y], int tarea){
	int cont = 0;
	while(cont != y){
		printf("%d\n", lista_acumulado[tarea][cont]);
		cont++;
	}
}

void mochila(int tope,int tareas, articulo_t* lista_articulos[tareas]){
	int contTareas = 0;
	int contTope = 0;
	int lista_acumulado[tareas][tope];
	//printf("Beneficio:%d\n", lista_articulos[1]->beneficio);
	while(contTareas != tareas){
		while(contTope != tope){
			//printf("%s\n", "Por aquí anda la cosa");
			//Caso de inicio; no existe acumulado del anterior todavía
			if(contTareas == 0){
				if(contTope < lista_articulos[0]->costo){
					lista_acumulado[contTareas][contTope] = 0;
				}
				else
					lista_acumulado[contTareas][contTope] = (int) lista_articulos[0]->beneficio * -1;
			}
			else{
				//Si el costo es mayor al límite se usa el valor a la izquierda
				if(contTope < lista_articulos[contTareas]->costo){
					lista_acumulado[contTareas][contTope] = abs(lista_acumulado[contTareas-1][contTope]);
				}
				else{
					//Se escoje el mayor entre usar la tarea + lo que sobre de costo en la tabla de la izquierda, o el valor de la tabla de la izquierda
					lista_acumulado[contTareas][contTope] = mayor(lista_articulos[contTareas]->beneficio + abs(lista_acumulado[contTareas-1][contTope - lista_articulos[contTareas]->costo]), abs(lista_acumulado[contTareas-1][contTope]));
				}
			}
			contTope++;
		}
		contTope = 0;
		contTareas++;
	}
	//imprimirTarea(tareas,tope,lista_acumulado, 3);
	printf("Matriz: \n");
	imprimirResultado(tareas,tope,lista_acumulado,lista_articulos);
	printf("\n");
	printf("Ruta Optima: \n");
	imprimirRuta(tareas,tope,tareas-1,tope-1,lista_acumulado,lista_articulos);

}


char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}


int main( int argc, char *argv[] )
{

	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	fp = fopen(argv[1], "r");
	if (fp == NULL)
		exit(EXIT_FAILURE);


	//Número de artículos
	getline(&line, &len, fp);
	int numArticulos = (int) strtol(line, (char **)NULL, 10);
	//Número de artículos
	getline(&line, &len, fp);
	int tope = (int) strtol(line, (char **)NULL, 10);


	articulo_t* lista_articulos[numArticulos];

	int cont = 0;
	//Crea un struct con la información del archivo de texto
	while(cont != numArticulos)
	   {
		char buffer[100];

		   getline(&line, &len, fp);
		   char** tokens;
		   tokens = str_split(line, ',');
		   char nombre = tokens[0][0];
		   int beneficio = (int) strtol(tokens[1], (char **)NULL, 10);
		   int costo = (int) strtol(tokens[2], (char **)NULL, 10);

		   lista_articulos[cont] = articulo_new(nombre,beneficio,costo);
		   cont++;

	   }

	mochila(tope+1, numArticulos, lista_articulos);


}









