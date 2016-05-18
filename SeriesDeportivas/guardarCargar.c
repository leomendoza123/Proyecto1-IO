
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logica.h"
#include "interfaz.h"

char* cutLastCharacters (char* string,  int amount); 
char *getLine (FILE *fp); 

void guardar (){

	cargarDatosDeInterfaz();
	FILE *fp;
	fp = fopen("save" , "w"); 
	int x = 0; 

		fprintf(fp, "%s\n", textInputs_instance.txtcantidadDePartidos);  
		fprintf(fp, "%s\n", textInputs_instance.txtprobabilidadEnCasa);  
		fprintf(fp, "%s\n", textInputs_instance.txtprobabilidadDeVisita);  
		fprintf(fp, "%s\n", textInputs_instance.txtserie);  
	
	fclose(fp);
}


void cargar (){
	char* filename;
    	filename =gtk_file_chooser_get_filename (fileChooser);
	printf ("%s \n", filename);
	FILE *fp;
   	fp = fopen(filename, "r");  

	gtk_entry_set_text (textInputs_instance.cantidadDePartidos, getLine (fp)) ;
	gtk_entry_set_text (textInputs_instance.probabilidadEnCasa, getLine (fp)) ;
	gtk_entry_set_text (textInputs_instance.probabilidadDeVisita, getLine (fp)) ;
	gtk_entry_set_text (textInputs_instance.serie, getLine (fp)) ;
}


char *getLine (FILE *fp){
		const size_t line_size = 300;
		char* line = malloc(line_size);
		fgets(line, line_size, fp);
		char* lineCut = malloc(line_size);
		lineCut =  cutLastCharacters (line, 1); 
		//printf ("%s\n", lineCut); 
		return lineCut; 

}

char* cutLastCharacters (char* string,  int amount){
		//printf (">%s\n", string); 
		int stringLen = strlen (string); 
		char* result = calloc(200, 4); 
		//printf (":%s\n", result); 
		strncpy (result, string, stringLen-amount); 
		//printf ("=%s\n", result); 
		return result; 
	
}
