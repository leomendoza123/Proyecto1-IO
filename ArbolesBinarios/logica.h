#include <gtk/gtk.h>

struct tuplaDeInterfaz {
	GtkWidget *txtNombre;
	GtkWidget *txtProbabilidad;
};
struct tuplaDeInterfaz tuplasDeInterfaz [14]; 

struct Nodo {
	char * nombre;
	int   probabilidad;
	float   normProbabilidad;
};

struct Nodo nodos [14]; 

void arbolBinarioBusqueda(int cantidad); 
void ArbolesBBeamer(int cantidad,double** A,int** R); 
void ordenarPalabras(int cantidad); 
void normalizaProbabilidades (int cantidad); 

