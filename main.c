#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

int system(const char *command);
void openfile ();

GtkWindow * window;
char *filename;

int main(int argc, char *argv[])
{
	
    GtkBuilder      *builder; 
    GtkWidget       *window;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "UI.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));
    gtk_builder_connect_signals(builder, NULL);


    g_object_unref(builder);


    gtk_widget_show(window);    
	           
    gtk_main();

    return 0;
}

// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}

void ruta_clicked (GtkWidget *widget){
   	printf("Ruta clicked:\n");
	
	openfile (0);
	printf( "%s \n", filename);
	system(filename); 
	 
}

void  mochila_clicked( GtkButton *button,         gpointer   data )
{
    printf("Mochila clicked:\n");
    openfile (1);
    //printf( "%s \n", filename);
    system(filename);
}
G_MODULE_EXPORT void remplazo_clicked( GtkButton *button,  gpointer   data )
{
    printf("Remplazo clicked:\n");
    openfile (2);
    printf( "%s \n", filename);
    system(filename);
}

G_MODULE_EXPORT void series_clicked( GtkButton *button,  gpointer   data )
{
	system("make -C SeriesDeportivas");
    
}


G_MODULE_EXPORT void arboles_clicked( GtkButton *button,  gpointer   data )
{
	system("make -C ArbolesBinarios");
    
}

G_MODULE_EXPORT void knapsack_clicked( GtkButton *button,  gpointer   data )
{
	system("make -C knapsack");
    
}



void openfile (int tarea){
	GtkWidget *dialog;

	dialog = gtk_file_chooser_dialog_new ("Open File",
					      window,
					      GTK_FILE_CHOOSER_ACTION_OPEN,
					      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
					      GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
					      NULL);
	if(tarea == 0){
		if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
			  {
			    filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
				char buffer[100];
				sprintf(buffer, "./Ruta %s", filename);


			    	system (buffer);

			  }
	}
	else
		if(tarea == 1){
			if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
						  {
						    filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
							char buffer[100];
							sprintf(buffer, "./Mochila %s", filename);


						    	system (buffer);

						  }
		}



	gtk_widget_destroy (dialog);
}
