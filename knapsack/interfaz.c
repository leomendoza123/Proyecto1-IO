
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "guardarCargar.h"
#include "interfaz.h"
#include "logica.h"


GtkBuilder *gtkBuilder;
GtkWidget *window;



void cargaDatosDeInterfaz (){
	int x= 0; 
	itemsLen = 0; 

	capacidadMochila= atoi( gtk_entry_get_text ( txtCapacidadMochila)); 
	
	for (; x<10; x++){



		if 	(strlen (gtk_entry_get_text (entradasDeInterfaz[x].costo)) >0
			 && strlen(gtk_entry_get_text (entradasDeInterfaz[x].valor)) >0 
			){

			 
			items[itemsLen].costo =  atoi (gtk_entry_get_text (entradasDeInterfaz[x].costo));
			items[itemsLen].valor =  atoi (gtk_entry_get_text (entradasDeInterfaz[x].valor));

			

			if (strlen (gtk_entry_get_text (entradasDeInterfaz[x].limite))== 0){		
				items[itemsLen].limite = -1; 
			}
			else{
				items[itemsLen].limite =  atoi (gtk_entry_get_text (entradasDeInterfaz[x].limite));
			}
			
			

			printf ("%d / Natural: %d, %d , %d\n", itemsLen, items[itemsLen].valor , items[itemsLen].costo, items[itemsLen].limite); 
			itemsLen++; 
		}
		
	}
}



void ejecutarAlgorithmo (){
	cargaDatosDeInterfaz(); 
	iniciaMatricesDeResultados(); 
	knapsack(); 
	imprime (); 

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
	for (; x<10; x++){
		char cated_string[6];
		sprintf(cated_string,"%s%d","entry",x*3 +2 );
		entradasDeInterfaz[x].valor = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, cated_string));
		char cated_string2[6];
		sprintf(cated_string2,"%s%d","entry",x*3+3 );
		entradasDeInterfaz[x].costo = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, cated_string2));
		char cated_string3[6];
		sprintf(cated_string3,"%s%d","entry",x*3+4 );
		entradasDeInterfaz[x].limite = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, cated_string3));

	}


	txtCapacidadMochila = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "entry1"));

	

	//Muestra venta
	g_object_unref(G_OBJECT(gtkBuilder));
    	gtk_widget_show(window);
   	gtk_main();


}
