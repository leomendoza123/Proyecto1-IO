#import "logica.h"


char colorArray[3][20] = {"black", "green", "red"};

void iniciaMatricesDeResultados (){

	int i = 0; 
	int j = 0; 
	resultado_instacia.valor = (int **)calloc(capacidadMochila+1,sizeof(double *));
	resultado_instacia.color = (int **)calloc(capacidadMochila+1,sizeof(double *));
	resultado_instacia.usados = (int **)calloc(capacidadMochila+1,sizeof(double *));

	for (i=0; i<capacidadMochila+1; i++){
    	 	resultado_instacia.valor[i] = (double *)calloc(itemsLen+1,sizeof(double));
		resultado_instacia.color[i] = (double *)calloc(itemsLen+1,sizeof(double));
		resultado_instacia.usados[i] = (double *)calloc(itemsLen+1,sizeof(double));
		for (j=0; j<itemsLen+1; j++){
			resultado_instacia.valor[i][j] = 0; 
			resultado_instacia.color[i][j] = 0; 
			resultado_instacia.usados[i][j] = 0; 
		}
   	 }
        


}

void knapsack(){

	int i,j; 
	// Recorrido por columnas
	for (j=0; j<itemsLen; j++){

	int costoYaUsado = 0;
	int maxValorActual = 0; 
	int cantidadUsada = 0;
	int usandoItemActual ; 
	
	for (i=0; i<capacidadMochila+1; i++){

		int campoDisponible = i; 
		
		int JsUsados = 0; 
		while (campoDisponible > JsUsados*items[j].costo &&  (JsUsados<=items[j].limite ||items[j].limite==0 )){
			
			int campoDisponibleSinJusados = campoDisponible-(JsUsados*items[j].costo);
			int valorEnJusados = JsUsados*items[j].valor; 
			if (j>0){
			if (resultado_instacia.valor[campoDisponibleSinJusados][j-1] + valorEnJusados >resultado_instacia.valor[i][j]  ){

				resultado_instacia.valor[i][j] = resultado_instacia.valor[campoDisponibleSinJusados][j-1]+valorEnJusados; 

				if (JsUsados>0){
					resultado_instacia.color[i][j] = 1; 
				}
				else{
					resultado_instacia.color[i][j] = 2; 

				}
				resultado_instacia.usados[i][j] = JsUsados;

			}
			else {
				resultado_instacia.color[i][j] = 2; 
				resultado_instacia.usados[i][j] = 0;	
			}
			
			
			}
			else{
				resultado_instacia.valor[i][j] = valorEnJusados; 
				resultado_instacia.color[i][j] = 1; 
				resultado_instacia.usados[i][j] = JsUsados;
				

			}
			 
			

			JsUsados++; 
		}
		


/*
		while (items[j].costo + items[j].costo*cantidadUsada <= i && (items[j].limite > cantidadUsada || items[j].limite == 0 )){
			
			printf ("%d - %d", items[j].costo + items[j].costo*cantidadUsada, i);
			++cantidadUsada; 
			resultado_instacia.valor[i][j] = items[j].valor*cantidadUsada; 
			resultado_instacia.color[i][j] = 1; 
			resultado_instacia.usados[i][j] =cantidadUsada; 

			if (j>0){
				if (resultado_instacia.valor[i-items[j].costo*cantidadUsada][j-1]+resultado_instacia.valor[i][j])

			}
					
		}

	*/
/*
		// Usa un item j actual más
		
		if (items[j].costo + costoYaUsado <= i && (items[j].limite > cantidadUsada || items[j].limite == 0 )){
			

			++cantidadUsada; 
			resultado_instacia.valor[i][j] = items[j].valor*cantidadUsada; 
			resultado_instacia.color[i][j] = 1; 
			 
			resultado_instacia.usados[i][j] =cantidadUsada; 
			costoYaUsado = items[j].costo * cantidadUsada; 
			maxValorActual =  resultado_instacia.valor[i][j];
					
		}

		// Se mantiene usando la misma cantidad de item j actuales
		else {

			resultado_instacia.valor[i][j] = maxValorActual; 
			resultado_instacia.usados[i][j] =cantidadUsada; 

			if (cantidadUsada>0){
			resultado_instacia.color[i][j] = 1; 
			}
			else {	
			resultado_instacia.color[i][j] = 0; 

			}


			}

		
		if (j>0){


			// Verifica si combinando el item actual con lo acumulado anteriormente es mejor 

			int x = 0; 
			while (i > items[j].costo * x ){
					// valor actual            <         valor del item actual + el valor acumulado anterior
				if (resultado_instacia.valor[i][j] < resultado_instacia.valor[i-items[j].costo*x][j-1] + items[j].valor * (cantidadUsada-x) ){
					
					resultado_instacia.valor[i][j] = resultado_instacia.valor[i-items[j].costo*x][j-1] + items[j].valor * (cantidadUsada-x);
					resultado_instacia.color[i][j] = 1;
					resultado_instacia.usados[i][j] = ++cantidadUsada; 
				}
				x++;
			}

			// Verifica si el valor anterior es mejor que el actual 
			if (resultado_instacia.valor[i][j] < resultado_instacia.valor[i][j-1]){
				maxValorActual = resultado_instacia.valor[i][j-1];
				resultado_instacia.valor[i][j] = maxValorActual; 
				resultado_instacia.color[i][j] = 2;
				cantidadUsada = 0; 
				resultado_instacia.usados[i][j] = cantidadUsada; 
			}

		}
*/
		
			
   	 }
	}


}

void imprime (){

	     FILE* fp;
    fp = fopen("temp.tex", "w");
    int i,j;
	
	printf (" Imprimiendo... \n" );

    fprintf(fp,"\\documentclass{article}\n\\usepackage{graphicx}\n\\usepackage[spanish]{babel}\n\\usepackage{float}\n\\usepackage{color}\n\n\n\\begin{document}\n\n\\title{Agloritmo de knapsack - Investigación De Operaciones  (2 semestre - 2016)}\n\\author{Leonardo Mendoza - Patrick Maynard}\n\n\\maketitle\n\n\\begin{abstract}\nEn algoritmia, el problema de la mochila, comúnmente abreviado por KP (del inglés Knapsack problem) es un problema de optimización combinatoria, es decir, que busca la mejor solución entre un conjunto de posibles soluciones a un problema. Modela una situación análoga al llenar una mochila, incapaz de soportar más de un peso determinado, con todo o parte de un conjunto de objetos, cada uno con un peso y valor específicos. Los objetos colocados en la mochila deben maximizar el valor total sin exceder el peso máximo.\n\\end{abstract}\n\n\\section{Datos iniciales}\n\n\nCapacidad de mochila: %d\n\n\\centering \n\\begin{figure}[H]\n\\label{my-label2}\n\\begin{tabular}{|l|l|l|} \n\\hline\nValor & Costo  & Limite\\\\ \\hline\n ",capacidadMochila );
	int x =0; 
	for (; x< 10; x++){
		fprintf(fp, "%d& ", items[x].valor);  
		fprintf(fp, "%d& ", items[x].costo);  
		fprintf(fp, "%d \\\\ \\hline\n", items[x].limite);
		printf ("ok con x= %d \n",x ); 

	}	

   fprintf(fp,"\n\\end{tabular}\n\\end{figure}\n\n    \n\\section{Tabla de resultados}\n\n\n\\centering \n\\begin{figure}[H]\n\\label{my-label2}\n\\begin{tabular}{|"); 

    for (i = 0; i < itemsLen+1; ++i)
    {
    	fprintf(fp,"l|");
	printf ("ok con i %d \n",i ); 
    }
    fprintf(fp,"}\n");
    fprintf(fp,"\\hline\n");


    for (i = 0; i < capacidadMochila+1; ++i)
    {
    	for (j = 0; j < itemsLen; ++j)
    	{

		printf ("ok color id = %d, color  =%s \n",resultado_instacia.color[i][j], colorArray[resultado_instacia.color[i][j]]); 
		fprintf(fp,"\\textcolor{%s}{%d} (%d)",  colorArray[resultado_instacia.color[i][j]], resultado_instacia.valor[i][j], resultado_instacia.usados[i][j] );
    		if (j != itemsLen)
    		{
    			fprintf(fp,"&");
    		}
		printf ("ok con i, j= %d, %d \n",i, j ); 
    	}
    	fprintf(fp,"\\\\ \\hline\n");
    }

fprintf(fp,
"\\end{tabular}\n\\end{figure}\n\n\n\\section{Conclusion}\nUsando la tabla se puede deducir cuales son los items que se deberían cargar\n\\end{document}");

    fclose(fp);
    system("pdflatex temp.tex");
    system("evince --presentation temp.pdf ");
    return 0;
}

