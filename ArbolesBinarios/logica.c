#include <stdio.h>
#include <stdlib.h>
#include "guardarCargar.h"


void arbolBinarioBusqueda(int nodosLen){

	
	int i,j;
	double **A = (double **)calloc(nodosLen+1,sizeof(double *));
    for (i=0; i<nodosLen+1; i++){
    	A[i] = (double *)calloc(nodosLen+1,sizeof(double));
    }
         
    int **R = (int **)calloc(nodosLen+1,sizeof(int *));
    for (i=0; i<nodosLen+1; i++){
    	R[i] = (int *)calloc(nodosLen+1,sizeof(int));
    }

	int imprimir = nodosLen;
	int k = 2;
	
	for (i = 0; i < nodosLen; ++i)
	{
		A[i][i+1] = nodos[i].normProbabilidad;
		R[i][i+1] = i+1;

	}
    nodosLen--;
    while (nodosLen != 0){
    	for (i = 0; i < nodosLen; ++i)
		{
			int pum = k-1;
			double* pumpumpum=(double*)calloc(k, sizeof(double));
			int* ks=(int*)calloc(k, sizeof(int));
			int cosa = i+k;
			int mover = i;
			double proba = 0.0;
			for (j = i; j < i+k; ++j)
			{
				proba = proba + nodos[j].normProbabilidad;
			}
			for (j = i; j < i+k; ++j)
			{
				pumpumpum[pum] = A[mover][j]+A[cosa-(imprimir-nodosLen)][i+k] + proba;
				ks[pum] = j+1;

				//printf("k = %d, %f\n",ks[pum],pumpumpum[pum] );

				cosa++;
				pum--;
			}
			double final = pumpumpum[0];
			int sub = ks[0];
			for (j = 0; j < k; ++j)
			{
				if (final > pumpumpum[j])
				{
					final = pumpumpum[j];
					sub = ks[j];
				}
			}
			A[i][i+k] = final;
			R[i][i+k] = sub;

		}
		nodosLen--;
		k++;
    }


	for (i = 0; i < imprimir+1; i++) {
        for (j = 0; j < imprimir+1; j++) {
            printf("%d ",R[i][j]);
        }
        printf("\n");
    }


    ArbolesBBeamer(imprimir,A,R);

    return 0;
}



void ArbolesBBeamer(int cantidad,double** A,int** R){
     FILE* fp;
    fp = fopen("temp.tex", "w");
    int i,j;
	
	printf (" Imprimiendo... \n" );

    fprintf(fp,"\\documentclass{article}\n\\usepackage{graphicx}\n\\usepackage[spanish]{babel}\n\\usepackage{float}\n\n\\begin{document}\n\n\\title{Optimización de Arboles de busqueda Binarios Investigación de Operaciones  (2 semestre - 2016)}\n\\author{Leonardo Mendoza - Patrick Maynard}\n\n\\maketitle\n\n\\begin{abstract}\nUn árbol binario de búsqueda también llamados BST (acrónimo del inglés Binary Search Tree) es un tipo particular de árbol binario que presenta una estructura de datos en forma de árbol usada en informática. Basado en la probabilidad de acceder que se desee localziar cada nodo, este algoritmo reordena el arbol de busqueda optimo para cada caso. \n\\end{abstract}\n\n\\section{Datos iniciales}\n\nEstos son los datos iniciales ordenados y normalizados: \n\n\\centering \n\\begin{figure}[H]\n\\label{my-label2}\n\\begin{tabular}{|l|l|} \n \\hline");


    for (i = 0; i < cantidad; ++i)
    {
    	fprintf(fp," %s & %.05f \\\\ \\hline\n",nodos[i].nombre,nodos[i].normProbabilidad);
    	printf(" %s & %f \\\\ \\hline\n",nodos[i].nombre,nodos[i].normProbabilidad);
    }
    fprintf(fp,"\\end{tabular}\n\\end{figure}\n    \n\\section{Tabla A}\nEsta es la table A completa.\n\n\n\\centering \n\\begin{figure}[H]\n\\label{my-label2}\n\\begin{tabular}{|");



    for (i = 0; i < cantidad+1; ++i)
    {
    	fprintf(fp,"l|");
    }
    fprintf(fp,"}\n");


    fprintf(fp,"\\hline\n");

    for (i = 0; i < cantidad+1; ++i)
    {
    	for (j = 0; j < cantidad+1; ++j)
    	{
    		if (j == 0)
    		{
    			fprintf(fp,"%.02f",A[i][j]);
    		}
    		else
    		{
    			fprintf(fp,"& %.02f",A[i][j]);
    		}
    	}
    	fprintf(fp,"\\\\ \\hline\n");
    }
    fprintf(fp,"\\end{tabular}\n\\end{figure}\n    \n\\section{Tabla R}\nEsta es la tabla que contiene el arbol optimo.\n\n\n\\centering \n\\begin{figure}[H]\n\\label{my-label2}\n\\begin{tabular}{|");


    for (i = 0; i < cantidad+1; ++i)
    {
    	fprintf(fp,"l|");
    }
    fprintf(fp,"}\n");


    fprintf(fp,"\\hline\n");

    for (i = 0; i < cantidad+1; ++i)
    {
    	for (j = 0; j < cantidad+1; ++j)
    	{
    		if (j == 0)
    		{
    			fprintf(fp,"%d",R[i][j]);
    		}
    		else
    		{
    			fprintf(fp,"& %d",R[i][j]);
    		}
    	}
    	fprintf(fp,"\\\\ \\hline\n");
    }


    fprintf(fp,"\\end{tabular}\n\\end{figure}\n    \n    \n\n\\section{Conclusion}\nFinalmente usando la tabla R se puede deducir el árbol de busca óptimo para este caso especifico.\n\n\\end{document}");
    fclose(fp);
    system("pdflatex temp.tex");
    system("evince --presentation temp.pdf ");
    return 0;
}


void ordenarPalabras(int cantidad){

	char temp[99];

	double tempP;

    int i, j, n;
	for (i = 0; i < cantidad - 1 ; i++)
    {
	
        for (j = i + 1; j < cantidad; j++)
        {
            if (strcmp(nodos[i].nombre, nodos[j].nombre) > 0)
            {
               	struct Nodo temp = nodos[i];

		
		nodos[i] = nodos[j]; 

		nodos[j] = temp;

            }
        }
    }
}

void normalizaProbabilidades (int cantidad){

	float total = 0; 
	int i; 
   	for (i = 0; i < cantidad  ; i++)
    	{
		total += nodos[i].probabilidad; 

        }

   	for (i = 0; i < cantidad  ; i++)
    	{
		nodos[i].normProbabilidad = nodos[i].probabilidad/total; 

        }


}

