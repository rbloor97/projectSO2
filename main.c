/***************************************************************************//**

  @file         main.c

  @author       Renzo Loor

  @date         sunday,  2 january 2020

  @brief	
*******************************************************************************/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LIMITE 100

char* split(char arreglo[]){ //Separador para obtener los valores de las variables

	strtok(arreglo,"\n"); //Eliminamos el salto de línea
	
	char delimitador[] = "=";
	char *variable;
        char *token = strtok(arreglo, delimitador); //Divimos por el delimitador '='
        if(token != NULL){
		
            	token = strtok(NULL, delimitador);//Seguimos llamando a la función para acceder al segundo token que es el valor
		 
		variable = token;
          	printf("Token: %s\n", token);
		
         }
	return variable;

}// end of split


int main(int argc, char** argv){
	
	FILE *fp;

	char caracteres[100];
 		
 	char comentario1[LIMITE]; char LAS[LIMITE];
	char PAS[LIMITE]; char pagesize[LIMITE];
	char comentario2[LIMITE]; char pname[LIMITE];
	char psize[LIMITE]; char pref[LIMITE];
	char algoritmo[LIMITE]; char pageframes[LIMITE];


	fp = fopen ( "archivo.txt", "rt" );  
      
	if (fp == NULL)
        {
            printf("\nError de apertura del archivo. \n\n");
        }
        else
        {
            printf("\nEl contenido del archivo de prueba es \n\n");
            	fgets (comentario1, LIMITE, fp);
    	    	fgets (LAS, LIMITE, fp);
    	    	fgets (PAS, LIMITE, fp);
		fgets (pagesize, LIMITE, fp);
    	    	fgets (comentario2, LIMITE, fp);
    	    	fgets (pname, LIMITE, fp);
		fgets (psize, LIMITE, fp);
    	    	fgets (pref, LIMITE, fp);
    	    	fgets (algoritmo, LIMITE, fp);
	    	fgets (pageframes, LIMITE, fp);
		
		

        }

        fclose(fp);

/** Variables necesarias para el cálculo**/
	char *LASvalor;//el valor de la variable LAS
	char *PASvalor;
	char *pagesizeValor;
	char *pnameValor;
	char *psizeValor;
	char *prefValor;
	char *algoritmoValor;
	char *pageframesValor;
	
	LASvalor = split(LAS);
	PASvalor = split(PAS);
	pagesizeValor = split(pagesize);
	pnameValor = split(pname);
	psizeValor = split(psize);
	prefValor = split(pref);
	algoritmoValor = split(algoritmo);
	pageframesValor = split(pageframes);
	


	printf("valor: %s\n",LASvalor);
	printf("valor: %s\n",PASvalor);
	printf("valor: %s\n",pagesizeValor);
	printf("valor: %s\n",pnameValor);
	printf("valor: %s\n",psizeValor);
	printf("valor: %s\n",algoritmoValor);
	printf("valor: %s\n",pageframesValor);

	return 0;

}





