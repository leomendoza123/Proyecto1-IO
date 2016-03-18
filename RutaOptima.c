#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <assert.h>




void floyds(int p[11][11], int r[11][11],int n);
char** str_split(char* a_str, const char a_delim); 
int min(int a,int b);
void print_matris (int p[11][11], int n, FILE* temp_result, char* descripcion); 

int main( int argc, char *argv[] )
{

// Abre archivo de grafo
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(argv[1], "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

//Abre archivo resultado latex temporal 

	FILE* temp_result= fopen( "resultado", "w" );


// abre archivo template de latex y llena el archivo resultado temp

    char const* const fileName = "latex-ruta-template.txt"; 
    FILE* template = fopen(fileName, "r"); 
    char line_template[1000];

	int x = 0; 
    while (fgets(line_template, sizeof(line_template), template) && x!=55) {
        printf("%s", line_template); 
	 fputs(line_template, temp_result);

	x+=1; 
    }



//Abre archivo resultado latex


// optiene el numero de nodos
    getline(&line, &len, fp); 
   
	int n = (int) strtol(line, (char **)NULL, 10);
	printf ("%d", n); 
// optiene el numero de edges
    getline(&line, &len, fp); 
   
	int e = (int) strtol(line, (char **)NULL, 10);
	printf ("%d", e); 

 int p[11][11],r[11][11], w,u,v,i,j;;



 for(i=1;i<=n;i++)
 {
   //Crea grafo en latex
	char * line; 
	if (i==1){
	    	line = " \\Vertex{1} \n"; 
	}
	else{

		char buffer[100];
		if (i<5){
			sprintf(buffer, "  \\SO(%d){%d} \n", i-1, i);
		}	
		else if (i<8 == 1){
			sprintf(buffer, "  \\WE(%d){%d} \n", i-1, i);
		}
		else{
			sprintf(buffer, "  \\NO(%d){%d} \n", i-1, i);
		}

		
		line = buffer; 
	}
	fputs(line, temp_result);

	// crea edges infinitos y tabla D
  for(j=1;j<=n;j++){
	
	r[i][j]= 0; 
	if (i==j){
		p[i][j] = 0;	
	}
	else{
	p[i][j]= 999;
	}
	}

 }


// agrega los edges del usuario
 for(i=1;i<=e;i++)
 {
	
	char buffer[100];
		
   getline(&line, &len, fp); 
   char** tokens; 
   tokens = str_split(line, ',');
   int salida = (int) strtol(tokens[0], (char **)NULL, 10);
   int llegada = (int) strtol(tokens[1], (char **)NULL, 10);
   int costo = (int) strtol(tokens[2], (char **)NULL, 10);
   p[salida][llegada]=costo;
	
	sprintf(buffer, "  \\Edge[label = %d](%d)(%d) \n", costo , salida, llegada);
	fputs(buffer, temp_result);

 }
   

// Agrega elemento de latex antes de tabla D0
 while (fgets(line_template, sizeof(line_template), template) && x!=61) {
	fputs(line_template, temp_result);
	x+=1; 

    }

char* descripcion = "Matris D(0)"; 
// Imprime tabla D(0)
 print_matris (p,n,temp_result, descripcion); 
// Imprime tabla D(n)
descripcion = "Matris D(n)"; 
 floyds(p,r, n);
  print_matris (p,n,temp_result, descripcion); 
// Imprime tabla P
descripcion = "Matris P(n)";
  print_matris (r,n,temp_result, descripcion); 
// Imprime lista de rutas más cortas

char buffer[100];

sprintf(buffer, "\n \\begin{table}[h!] \n \\centering \n \\begin{tabular}{|| c ||} \n  \\hline ");
fputs(buffer, temp_result);

 printf("\n The shortest paths are:\n");
 for(i=1;i<=n;i++)
  for(j=1;j<=n;j++)
  {
	if (r[i][j] != 0){
	
	
    	 sprintf(buffer, "\n De %d a %d ir por %d \\\\   \n ", i,j,r[i][j]);
	fputs(buffer, temp_result);
	}	
		
	
	}
   if (i==n && j== n){
		sprintf(buffer, "fin  \\\\[1ex]     \n ");
fputs(buffer, temp_result);
	}
	


  
sprintf(buffer, " \n \\hline \n \\end{tabular}\n  \\caption{%s} \n \\label{table:1} \n \\end{table} ", "Lista de atajos");
fputs(buffer, temp_result);


//-----------------------------------

// Termina de llenar el resultado con el archivo template

  


 while (fgets(line_template, sizeof(line_template), template) ) {
	fputs(line_template, temp_result);
	x+=1; 

    }

// Ciera archivo de grafo 
fclose(temp_result);
 fclose(template);
fclose(fp);
    if (line)
        free(line);

system("pdflatex resultado");
system("gnome-open resultado.pdf");

    exit(EXIT_SUCCESS); 

 
}

// Funciona para imprimir matrices en latex
void print_matris (int p[11][11], int n, FILE* temp_result, char* descripcion){


char buffer[100];





sprintf(buffer, "\n \\begin{table}[h!] \n \\centering \n \\begin{tabular}{|| ");
fputs(buffer, temp_result);

int x=1; 
for (x;x<=n;x+=1){
	fputs(" c " , temp_result);
}
sprintf(buffer, " ||} \n \\hline \n");
fputs(buffer, temp_result);


	int i,j; 
 for(i=1;i<=n;i++)
 {
  char buffer[100];
  for(j=1;j<=n;j++){
	   printf("%d \t",p[i][j]);
	   printf("\n");
	
		if (i == n && j == n){
			sprintf(buffer, " %d \\\\[1ex]   \n ", p[i][j]);
		}
	
		else if (j+1 > n){
			sprintf(buffer, " %d  \\\\  \n", p[i][j]);
		}

		
		else{
			sprintf(buffer, " %d &", p[i][j]);
		}
		fputs(buffer, temp_result);
	}
 }
sprintf(buffer, " \n \\hline \n \\end{tabular}\n  \\caption{%s} \n \\label{table:1} \n \\end{table} ", descripcion);
fputs(buffer, temp_result);



}


//Algorithmo floyd
void floyds(int p[11][11], int r[11][11],int n)
{
 int i,j,k;
	 for(k=1;k<=n;k++){
		  for(i=1;i<=n;i++){
			   for(j=1;j<=n;j++){
					if (p[i][j]> min(p[i][j],p[i][k]+p[k][j])){
						r[i][j]=k;
						}
				    if(i==j){
				     p[i][j]=0;
					}
					else{

				    
				    
					
				     p[i][j]=min(p[i][j],p[i][k]+p[k][j]);}
					
			}
		}
	}
}

int min(int a,int b)
{
 if(a<b )
  return(a);
 else
  return(b);
}



char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}
