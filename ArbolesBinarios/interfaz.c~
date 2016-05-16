#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "guardarCargar.h"
#include "interfaz.h"

GtkBuilder *gtkBuilder;
GtkWidget *window;
int nodosLen = 0; 





void cargaDatosDeInterfaz (){
	int x= 0; 
	nodosLen = 0; 
	for (; x<14; x++){
		if 	(strlen (gtk_entry_get_text (tuplasDeInterfaz[x].txtNombre)) >0
			 && strlen(gtk_entry_get_text (tuplasDeInterfaz[x].txtProbabilidad)) >0 
			){

			nodos[x].nombre =  gtk_entry_get_text (tuplasDeInterfaz[x].txtNombre) ;
			nodos[x].probabilidad =  atoi (gtk_entry_get_text (tuplasDeInterfaz[x].txtProbabilidad));
			printf ("Natural: %s, %d \n", nodos[x].nombre , nodos[x].probabilidad); 
			nodosLen++; 
		}
		
	}
}



void ejecutarAlgorithmo (){

	 cargaDatosDeInterfaz(); 
	int x = 0; 
	for (; x<nodosLen; x++){

		printf ("Tpls: %s = %d \n",nodos[x].nombre, nodos[x].probabilidad); 
	}
	 ordenarPalabras(nodosLen); 
	normalizaProbabilidades (nodosLen); 

	x = 0; 
	 for (; x<nodosLen; x++){

		printf ("Tpls-Ord-Norm: %s = %f \n",nodos[x].nombre, nodos[x].normProbabilidad);
	}
	 arbolBinarioBusqueda(nodosLen); 

}





int main(int argc, char *argv[])
{
	
	

	// Crea venta
	gtk_init(&argc, &argv);    
	gtkBuilder = gtk_builder_new();
	gtk_builder_add_from_file(gtkBuilder, "interfaz.glade", NULL);
	window = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "window1"));


	//liga botones
	GtkWidget *button_algorithmo;
	GtkWidget *button_guardar;
	GtkWidget *button_cargar;
	button_algorithmo = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "button_algorithmo"));
	button_guardar = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "button_guardar"));
	button_cargar = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "button_cargar"));
	fileChooser = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "filechooserbutton1"));

	// conecta acciones

	g_signal_connect (button_algorithmo, "clicked",G_CALLBACK (ejecutarAlgorithmo),NULL);
	g_signal_connect (button_guardar, "clicked",G_CALLBACK (guardar),NULL);
	g_signal_connect (button_cargar, "clicked",G_CALLBACK (cargar),NULL);

	// Liga entradas de texto
	int x=0; 
	printf ("ok");
	for (; x<14; x++){
		char cated_string[6];
		sprintf(cated_string,"%s%d","entry",x*2 +1);
		tuplasDeInterfaz[x].txtNombre = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, cated_string));
		char cated_string2[6];
		sprintf(cated_string2,"%s%d","entry",x*2+2);
		tuplasDeInterfaz[x].txtProbabilidad = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, cated_string2));

	}

	

	//Muestra venta
	g_object_unref(G_OBJECT(gtkBuilder));
    	gtk_widget_show(window);
   	gtk_main();


}
