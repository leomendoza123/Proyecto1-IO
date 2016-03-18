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
	
	openfile ();
	printf( "%s \n", filename);
	system(filename); 
	 
}

void  mochila_clicked( GtkButton *button,         gpointer   data )
{
    printf("Mochila clicked:\n");
}
G_MODULE_EXPORT void remplazo_clicked( GtkButton *button,  gpointer   data )
{
    printf("Remplazo clicked:\n");
}

void openfile (){
	GtkWidget *dialog;

	dialog = gtk_file_chooser_dialog_new ("Open File",
					      window,
					      GTK_FILE_CHOOSER_ACTION_OPEN,
					      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
					      GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
					      NULL);

	if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
	  {
	    filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
		char buffer[100];
		sprintf(buffer, "./Ruta %s", filename);

		
	    	system (buffer);
	   
	  }

	gtk_widget_destroy (dialog);
}
