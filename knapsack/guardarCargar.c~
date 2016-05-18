
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logica.h"
#include "interfaz.h"
char* cutLastCharacters (char* string,  int amount); 

void guardar (){
	FILE *fp;
	fp = fopen("save" , "w"); 
	int x = 0; 
	for (; x< 14; x++){
		fprintf(fp, "%s\n", nodos[x].nombre);  
		fprintf(fp, "%d\n", nodos[x].probabilidad);  
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

	int x = 0; 
	for (; x< 14; x++){
		char* line = malloc(line_size);
		
		
		fgets(line, line_size, fp);
		char* lineCut =  cutLastCharacters (line, 1); 
		if (strcmp (lineCut, "(null)") != 0){
			gtk_entry_set_text (tuplasDeInterfaz[x].txtNombre, lineCut) ;
		}


		char* line2 = malloc(line_size);
		char* lineCut2 = malloc (line_size); 

		fgets(line2, line_size, fp);
		
		lineCut2 = cutLastCharacters (line2, 1);  
		//printf("%s\n", line2); 
		//printf("%s\n", lineCut2); 
		gtk_entry_set_text (tuplasDeInterfaz[x].txtProbabilidad, lineCut2) ;
			

	
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
