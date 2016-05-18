
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "guardarCargar.h"
#include "logica.h"
#include "interfaz.h"



void cargarDatosDeInterfaz(); 
void ejecutarAlgorithmo(); 



GtkBuilder *gtkBuilder;
GtkWidget *window;


void cargarDatosDeInterfaz(){

	textInputs_instance.txtcantidadDePartidos = gtk_entry_get_text (textInputs_instance.cantidadDePartidos);
	textInputs_instance.txtprobabilidadEnCasa = gtk_entry_get_text (textInputs_instance.probabilidadEnCasa);
	textInputs_instance.txtprobabilidadDeVisita = gtk_entry_get_text (textInputs_instance.probabilidadDeVisita);
	textInputs_instance.txtserie = gtk_entry_get_text(textInputs_instance.serie);
	
}

void ejecutarAlgorithmo(){
	cargarDatosDeInterfaz(); 
	cargaDatosALogica();
	if (serie_instance.partidosTotales%2 == 1){
		recalculaSerie (); 	
		serie(); 
	}
	

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


	textInputs_instance.cantidadDePartidos = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "txtcantidad"));
	textInputs_instance.probabilidadEnCasa = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "txtCasa"));
	textInputs_instance.probabilidadDeVisita = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "txtVisita"));
	textInputs_instance.serie = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "txtSerie"));


	

	//Muestra venta
	g_object_unref(G_OBJECT(gtkBuilder));
    	gtk_widget_show(window);
   	gtk_main();


}
