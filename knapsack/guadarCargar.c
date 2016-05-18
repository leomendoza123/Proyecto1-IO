
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logica.h"
#include "interfaz.h"



char* cutLastCharacters (char* string,  int amount); 

void guardar (){
	FILE *fp;
	fp = fopen("save" , "w"); 

	fprintf(fp, "%d\n", capacidadMochila);  
	int x = 0; 
	for (; x< 10; x++){
		fprintf(fp, "%d\n", items[x].costo);  
		fprintf(fp, "%d\n", items[x].limite);  
		fprintf(fp, "%d\n", items[x].valor);  

	}	
	fclose(fp);
}


void cargar (){
	char* filename;
    	filename =gtk_file_chooser_get_filename (fileChooser);
	printf ("%s \n", filename);
	FILE *fp;
   	fp = fopen(filename, "r");  

	const size_t line_size = 300;

	int x = -1; 
	for (; x< 10; x++){
		
		if (x == -1){
			char* line0 = malloc(line_size);
			char* lineCut0 = malloc(line_size);
			fgets(line0, line_size, fp);
			lineCut0 =  cutLastCharacters (line0, 1); 
			gtk_entry_set_text (txtCapacidadMochila, lineCut0) ;	
			printf ("%s \n", lineCut0); 

		}
		else{


			char* line = malloc(line_size);
			char* lineCut = malloc(line_size);
			fgets(line, line_size, fp);
			lineCut =  cutLastCharacters (line, 1); 
			if (strcmp (lineCut, "0") != 0){
				gtk_entry_set_text (entradasDeInterfaz[x].costo, lineCut) ;


		
				char* line2 = malloc(line_size);
				char* lineCut2 = malloc (line_size); 

				fgets(line2, line_size, fp);
				lineCut2 = cutLastCharacters (line2, 1);  
				gtk_entry_set_text (entradasDeInterfaz[x].limite, lineCut2) ;


				char* line3 = malloc(line_size);
				char* lineCut3 = malloc (line_size); 

				fgets(line3, line_size, fp);
				lineCut3 = cutLastCharacters (line3, 1);  
				gtk_entry_set_text (entradasDeInterfaz[x].valor, lineCut3) ;	

			}

			else{
				gtk_entry_set_text (entradasDeInterfaz[x].costo, "") ;
				gtk_entry_set_text (entradasDeInterfaz[x].limite, "") ;
				gtk_entry_set_text (entradasDeInterfaz[x].valor, "") ;

			}

		}
	
	}


	
}


char* cutLastCharacters (char* string,  int amount){
		printf (">%s\n", string); 
		int stringLen = strlen (string); 
		char* result = calloc(200, 4); 
		printf (":%s\n", result); 
		strncpy (result, string, stringLen-amount); 
		printf ("=%s\n", result); 
		return result; 
	
}
