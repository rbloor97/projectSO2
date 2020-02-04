/***************************************************************************//**

  @file         main.c

  @author       Renzo Loor

  @date         sunday,  2 january 2020

  @brief	
*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#define LIMITE 100

void split(char arreglo[]){ //Separador para obtener los valores de las variables

	strtok(arreglo,"\n"); //Eliminamos el salto de línea
	
	char delimitador[] = "=";
	char *variable; //aqui guardaremos el dato que nos interesa
        char *token = strtok(arreglo, delimitador); //Divimos por el delimitador '='
        if(token != NULL){
            	token = strtok(NULL, delimitador);//Seguimos llamando a la función para acceder al segundo token que es el valor que nos interesa
		variable =token;
          	printf("Token: %s\n", token);
         }
	int tamano = strlen(variable);
	for(int i=0;i < tamano;i++){
		arreglo[i]= *variable;
		variable++;
		
	}
	

	
	
}// end of split

 

int calcularBits(int bits,char sufijo[]){
	int exp = 0;
	exp = log2(bits);
  if(strncmp(sufijo,"GB",strlen(sufijo)) == 0){
    bits = exp + 30;   
  }else if(strncmp(sufijo,"MB",strlen(sufijo)) == 0){
    bits = exp + 20;
  }else if(strncmp(sufijo,"KB",strlen(sufijo)) == 0){
    bits = exp + 10;
  }else {
    bits =  exp;
  }

  return bits;
}// end of calcular Bits

void obtenerValor(char numero[], char sufijo[], char fuente[]){
  int tamano = strlen(fuente);
  for(int i = 0; i < tamano; i++ ){
    if(isdigit(fuente[i]) != 0 ){
      numero[i] = fuente[i];
    }
    else {   
      strcat(sufijo, &fuente[i] );
      break;
    }

  }

}//end of obtenerValor

void referenceString(char reference[], int offset,char rString[]){
  char delimitador[] = ",";
  int number; //variable auxiliar
  char *token = strtok(reference,delimitador);
  int i = 0;
  while(token != NULL){
    number = atoi(token);
    char n[10] = "";
    int div = number/offset;//division referencia/offset
    token = strtok(NULL,delimitador);
    snprintf(n, 10,"%d",div); //conbierte la division en String
    rString[i] = n[0]; //Almacenamos la cadena
    i+=1;
    
  }
  
}//end of referenceString

void FIFO(int nEntradas, char rString[], int nFrames){
int i,j,frame[10],k,avail,count=0;
int a[1024];
a[0]=0;
for(int m = 0; m<strlen(rString);m++){
  a[m+1] = (rString[m]);
}

for(i=0;i<nFrames;i++){
  frame[i]= -1;
}
  j=0;
  printf("ref string\t page frames\n");
for(i=1;i<=nEntradas;i++){
  printf("\t%c\t\t",a[i]);
  avail=0;
  for(k=0;k<nFrames;k++){
    if(frame[k]==a[i])
      avail=1;
  }
    if (avail==0){
      frame[j]=a[i];
      j=(j+1)%nFrames;
      count++;
      for(k=0;k<nFrames;k++){
      printf("%c\t",frame[k]);
      }
}
      printf("\n");
}

int hits = (nEntradas-count);
printf("\n\nNúmero de Page Faults = %d\n", count);
printf("Número Hits = %d\n ",hits);
printf("Hit ratio = %.2f porciento \n",((float)hits/(float)nEntradas));
                       
}//end of FIFO

int findLRU(int time[], int n){
	int i, minimum = time[0], pos = 0;
 
	for(i = 1; i < n; ++i){
		if(time[i] < minimum){
			minimum = time[i];
			pos = i;
		}
	}
	
	return pos;
}//end of findLRU

void LRU(int nEntradas, char rString[], int nFrames){
int  frames[10], pages[1024], counter = 0, time[10], flag1, flag2, i, j, pos, faults = 0;

for(int m = 0; m<strlen(rString);m++){
  pages[m] = (rString[m]);
}
printf("ref string\t page frames\n");
for(i = 0; i < nFrames; ++i){
    frames[i] = -1;
  }
  
  for(i = 0; i < nEntradas; ++i){
    flag1 = flag2 = 0;
    
    for(j = 0; j < nFrames; ++j){
      if(frames[j] == pages[i]){
        counter++;
        time[j] = counter;
        flag1 = flag2 = 1;
        break;
      }
    }
    
    if(flag1 == 0){
    for(j = 0; j < nFrames; ++j){
        if(frames[j] == -1){
          counter++;
          faults++;
          frames[j] = pages[i];
          time[j] = counter;
          flag2 = 1;
          break;
        }
      }	
    }
    
    if(flag2 == 0){
      pos = findLRU(time, nFrames);
      counter++;
      faults++;
      frames[pos] = pages[i];
      time[pos] = counter;
    }
    
    printf("\n");
    printf("\t %c\t\t",pages[i]);
    for(j = 0; j < nFrames; ++j){
      printf("%c\t", frames[j]);
    }
}
int hits = (nEntradas-faults);
printf("\n\nNúmero de Page Faults = %d\n", faults);
printf("Número Hits = %d\n ",hits);
printf("Hit ratio =  %.2f porciento \n",((float)hits/(float)nEntradas));
}//end of LRU

void OPTIMAL(int nEntradas, char rString[], int nFrames){
int  frames[10], pages[30], temp[10], flag1, flag2, flag3, i, j, k, pos, max, faults = 0;

for(int m = 0; m<strlen(rString);m++){
  pages[m] = (rString[m]);
}

for(i = 0; i < nFrames; ++i){
    frames[i] = -1;
}


printf("ref string\t page frames\n");

for(i = 0; i < nEntradas; ++i){
    flag1 = flag2 = 0;
    
    for(j = 0; j < nFrames; ++j){
        if(frames[j] == pages[i]){
                flag1 = flag2 = 1;
                break;
            }
    }
    
    if(flag1 == 0){
        for(j = 0; j < nFrames; ++j){
            if(frames[j] == -1){
                faults++;
                frames[j] = pages[i];
                flag2 = 1;
                break;
            }
        }    
    }
    
    if(flag2 == 0){
      flag3 =0;
      
        for(j = 0; j < nFrames; ++j){
          temp[j] = -1;
          
          for(k = i + 1; k < nEntradas; ++k){
            if(frames[j] == pages[k]){
              temp[j] = k;
              break;
            }
          }
        }
        
        for(j = 0; j < nFrames; ++j){
          if(temp[j] == -1){
            pos = j;
            flag3 = 1;
            break;
          }
        }
        
        if(flag3 ==0){
          max = temp[0];
          pos = 0;
          
          for(j = 1; j < nFrames; ++j){
            if(temp[j] > max){
              max = temp[j];
              pos = j;
            }
          }            	
        }
  
  frames[pos] = pages[i];
  faults++;
    }
    
    printf("\n");
    printf("\t %c\t\t",pages[i]);
    for(j = 0; j < nFrames; ++j){
        printf("%c\t", frames[j]);
    }
}
int hits = (nEntradas-faults);
printf("\n\n Número de Page Faults = %d\n", faults);
printf("Número de Hits = %d\n ",hits);
printf("Hit ratio = %.2f porciento \n",((float)hits/(float)nEntradas));

}//end of optimal
void calculoDirecciones(char las[],char pas[],char Loffset[],char pname[], char Lpsize[],char pref[],char algoritmo[], char pageframe[]){ //Función para calcular el Logical Address Structure, Physical Address, Offset and size page table

	char numero[100] ="" ;
  char sufijo[100] = "";

  obtenerValor(numero,sufijo,las);

  char numOffset[100] = "";
  char sufijoOffset[100] = "";

  obtenerValor(numOffset,sufijoOffset,Loffset);

  char numPAS[100] = "";
  char sufijoPAS[100] = "";

  obtenerValor(numPAS,sufijoPAS,pas);
 
  char psize[100] = "";
  char sufProccess[100] = "";

  obtenerValor(psize,sufProccess,Lpsize);


  int bits = calcularBits(atoi(numero),sufijo);
  int offset = calcularBits(atoi(numOffset),sufijoOffset);
  int bPAS = calcularBits(atoi(numPAS),sufijoPAS);  
  printf("\n\n!PAGE REPLACEMENT FOT THE PROCCESS: %s--------------!\n\n",pname);
  printf("\n\n!--------------DIRECCIÓN LÓGICA DE MEMORIA--------------!\n\n");
  printf("El tamaño de la dirección virtual es de %s --> %d bits \n",las, bits);
  printf("El tamaño del offset es: %d\n", offset);
  printf("LAS: [    p: %d bits    |     o: %d bits     ]\n",(bits-offset),offset);


  printf("\n\n!--------------DIRECCIÓN FÍSICA DE MEMORIA--------------!\n\n");
  printf("El tamaño de la dirección física es de %s --> %d bits \n",pas, bPAS);
  printf("PAS: [    f: %d bits    |     o: %d bits     ]\n",(bPAS-offset),offset);

  printf("\n\n!--------------MÁXIMO NÚMERO DE ENTRADAS--------------!\n\n");
  
  long pte = pow(2,(bits - offset));
  printf("Máximo número de entradas en la tabla de páginas 2x10^%d = %ld páginas \n",(bits - offset),pte);

  printf("\n\n!--------------MÁXIMO NÚMERO DE FRAMES--------------!\n\n");
  
  long nof = pow(2,(bPAS - offset));
  printf("Máximo número de frames en la memoria física 2x10^%d = %ld frames \n",(bPAS - offset),nof);
  int frames = 4;
  
  printf("\n\n!--------------TAMAÑO DE LA TABLA DE PÁGINA--------------!\n\n");
  
  float entradas = atoi(psize)/atoi(numOffset);
  if(atoi(psize)%atoi(numOffset) != 0){
    entradas +=1;
  }
  printf("entradas del proceso: %.1f páginas\n",entradas);
  printf("\n\n!--------------PÁGINAS DEL PROCESO VÁLIDAS--------------!\n\n");

  int n = 0;
  int total = 0;
  while(total<entradas){
    total = pow(2,n);
    n +=1;
  }

  printf("Entradas totales: %d\nEntradas válidas del proceso: %.2f \n", total,entradas);
  printf("Entradas inválidas: %.1f\n",(total - entradas));

  printf("\n\n!--------------REFERENCE STRING--------------!\n\n");
  printf("Referencia de memoria: [ %s ]\n",pref);
  char rString[] = "";
  referenceString(pref,atoi(numOffset),rString);
  printf("Reference String: [ %s ]\n",rString);

  printf("\n\n!--------------PAGE TABLE OUTPUT --------------!\n\n");
  

  FIFO(strlen(rString),rString,frames);
  LRU(strlen(rString),rString,frames);
  OPTIMAL(strlen(rString),rString,frames);


}//End of calculoDirecciones




int main(int argc, char** argv){
	
	if (argc != 2){
	 printf ("usage: main FileDirectory [./FILE...]\n");
	 return 0;
	}

 	  printf("\n \n \n*******************************************************");
  printf(" \n \t***Main & Virtual Memory**");
  printf("\n \n \t***Autor:    Renzo Loor***");
  printf("\n*******************************************************\n");

 	char comentario1[LIMITE]; char LAS[LIMITE];
	char PAS[LIMITE]; char pagesize[LIMITE];
	char comentario2[LIMITE]; char pname[LIMITE];
	char psize[LIMITE]; char pref[LIMITE];
	char algoritmo[LIMITE]; char pageframes[LIMITE];

	FILE *fp;
	fp = fopen (argv[1],"rt");  
	printf("arg: %s",argv[1]);
      
      
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

	

	split(LAS);
	split(PAS);
	split(pagesize);
	split(pname);
	split(psize);
	split(pref);
	split(algoritmo);
	split(pageframes);
	
	
	calculoDirecciones(LAS,PAS,pagesize,pname,psize,pref,algoritmo,pageframes);

	return 0;

}





