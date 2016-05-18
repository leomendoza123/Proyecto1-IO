
#include <gtk/gtk.h>



struct EntradaDeInterfaz {
	GtkWidget *costo;
	GtkWidget *limite;
	GtkWidget *valor;
};

GtkWidget *txtCapacidadMochila;

struct EntradaDeInterfaz entradasDeInterfaz [10]; 


struct Item {
	int costo; 
	int valor; 
	int limite; 
	
};

struct Resultado {
	int ** valor; 
	int ** color; 
	int ** usados; 

};



struct Resultado resultado_instacia; 

struct Item items [10]; 
int capacidadMochila; 
int itemsLen; 

void iniciaMatricesDeResultados (); 
void knapsack(); 
void imprime (); 

