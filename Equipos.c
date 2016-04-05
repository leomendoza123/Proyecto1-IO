#define _GNU_SOURCE
#include "Equipo.h"
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <assert.h>

void imprimirResultado(int plazo, int ruta[plazo+1]){
	int cont = 0;
	printf("Ruta óptima = 0 -> ");
	while(cont != plazo){
		if(ruta[cont] == plazo){
			printf("%d\n", ruta[cont]);
			break;
		}
		else
		{
			printf("%d -> ",ruta[cont]);
			cont = ruta[cont];
		}
	}
}

int minimo(int a, int b, int plazo,int ruta[plazo+1],int x,int y){
	if(b<a){

		return(b);
	}
	else{
		ruta[x] = y;
		return(a);
	}

}

float interes(int anho,int valor, int inflacion){
	int cont = 0;
	float respuesta = (float)valor;
	while(cont != anho){
		respuesta = respuesta + (respuesta * (0.01 * inflacion));
		cont ++;
	}

	return respuesta;

}

int Cxy(int x, int y, int inflacion, int plazo, equipo_t* lista_equipo[plazo], int lista_g[plazo+1],int vidaUtil,int inicial){
	int cont = 0;
	//printf("C%d%d,%d=", x,y,plazo);
	int resultado = interes(x,inicial,inflacion);
	while(x != y){
		resultado = resultado + interes(x,lista_equipo[cont]->mantenimiento,inflacion) - interes(x,lista_equipo[cont]->ganancia,inflacion);
		x++;
		cont++;
	}
	resultado = resultado - interes(x,lista_equipo[cont-1]->valor,inflacion);
	//printf("%d\n", resultado);
	return resultado;

}


int CXY(int x, int y, int inflacion, int plazo, equipo_t* lista_equipo[plazo], int lista_g[plazo+1],int vidaUtil,int inicial,int ruta[plazo+1]){
	int cont = 0;
	int diferencia = y - x;
	int resultado = 32767;

	while(cont != diferencia){
		if(cont < vidaUtil){
			resultado = minimo(Cxy(x,x + cont + 1,inflacion,plazo,lista_equipo,lista_g, vidaUtil,inicial) + lista_g[x+cont+1],resultado,plazo,ruta,x,x+cont+1);
		}
		cont++;
	}
	printf("G(%d) = %d\n",x,resultado);

	return resultado;
}

void reemplazo(int inflacion, int plazo, equipo_t* lista_equipo[plazo], int lista_g[plazo+1],int vidaUtil,int inicial,int ruta[plazo+1]){
	lista_g[plazo] = 0;
	int cont = plazo-1;
	printf("G(%d) = %d\n",plazo,0);
	while(cont != -1){
		//printf("G(%d) = %d",cont+1,CXY(cont,plazo,inflacion,plazo,lista_equipo,lista_g,vidaUtil,inicial));
		lista_g[cont] = CXY(cont,plazo,inflacion,plazo,lista_equipo,lista_g,vidaUtil,inicial,ruta);
		cont--;
	}
	printf("Resultado óptimo= %d\n", lista_g[0]);
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


	//Plazo
	getline(&line, &len, fp);
	int plazo = (int) strtol(line, (char **)NULL, 10);
	//Vida útil del equipo
	getline(&line, &len, fp);
	int vidaUtil = (int) strtol(line, (char **)NULL, 10);
	//Inflación
	getline(&line, &len, fp);
	int inflacion = (int) strtol(line, (char **)NULL, 10);
	//Costo Inicial
	getline(&line, &len, fp);
	int inicial = (int) strtol(line, (char **)NULL, 10);


	equipo_t* lista_equipo[vidaUtil];
	int lista_g[vidaUtil+1];
	int ruta[vidaUtil+1];

	int cont = 0;
	//Crea un struct con la información del archivo de texto
	while(cont != vidaUtil)
	   {
		char buffer[100];

		   getline(&line, &len, fp);
		   char** tokens;
		   tokens = str_split(line, ',');
		   int valor = (int) strtol(tokens[0], (char **)NULL, 10);
		   int mantenimiento = (int) strtol(tokens[1], (char **)NULL, 10);
		   int ganancia = (int) strtol(tokens[2], (char **)NULL, 10);

		   lista_equipo[cont] = equipo_new(valor,mantenimiento,ganancia);
		   cont++;

	   }


	//
	//(int x, int y, int inflacion, int plazo, equipo_t* lista_equipo[plazo], int lista_g[plazo+1],int vidaUtil,int inicial)
	//printf("%d",CXY(3,5,inflacion,plazo,lista_equipo,lista_g,vidaUtil,inicial));
	reemplazo(inflacion,plazo,lista_equipo,lista_g,vidaUtil,inicial,ruta);
	imprimirResultado(plazo,ruta);

}


