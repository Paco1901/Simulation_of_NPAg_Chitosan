/* 
OCTAEDRO

PROGRAMA QUE GENERA OCTAEDROS truncados CON CAPAS INTERMEDIAS GEOMETRICAMENTE PERFECTOS 
EL NIVEL DEL OCTAEDRO ESA DADO POR EL PARAMETRO 1 DEL PROGRAMA
EL ELEMENTO DEL OCTAEDRO ESTA DADO POR EL PARAMETRO 2 DEL PROGRAMA
EL PARAMETRO 3 NOS DA EL NUMERO DE CAPAS INTERMEDIAS
PARAMETRO 4 NIVEL DE TRUNCAMIENTO

AU = 1
RH = 2
PD = 3
PT = 4
PB = 5 


Parte del sistema NanoSim

*/

# include <stdio.h>
# include <math.h>
# include <string.h>


/* Funciones */

void WritePDB(unsigned int, unsigned int, unsigned int, unsigned int);
	/* Crea el archivo con formato PDB que almacena las coordenadas del octaedro */

int sfibo(int);
int nitera(int); /*Funciones que calculan numero de atomos en las capas del octaedro */


/*
Variables Globales.
*/
float  atom[1000000][2]; 	/* Arreglo que contiene las coordenadas del octaedro en un plano  X, Y   */
unsigned int no_atoms=0; 	/* Numero de atomos en el arreglo. Este depende del nivel del octaedro */



/* PROCESO PRINCIPAL */
/*********************************************/
void main(int argc, char *argv[])
{
unsigned int N = atoi(argv[1]);       /*Nivel del octaedro */
unsigned int Elemento = atoi(argv[2]); 	/*Elemento del decaedro */
unsigned int Inos = atoi(argv[3]);	/*Numero de capas intermedias */
unsigned int Trunc = atoi(argv[4]);     /*Nivel de truncamiento */

int i,j;	/*variables subindices */

float k,l,s;
		/* auxiliares para puntos medios */

/* Coordenadas de los atomos Nivel 0 (centro) */
    atom[0][0] = 0.0; 
    atom[0][1] = 0.0; 

    no_atoms=1;

  if(Trunc > (N/2)){ 
    Trunc =(N/2);
     printf("\n Aplicando Truncamiento Maximo \n");
  }


/* Ciclo principal del algoritmo */
   i=0;
   while(i<=N){
     
      k=(i-1.0)*-1.0;
      l=1.0;s=1.0;
      for(j=0;j<2*i;j++)
      {
         atom[no_atoms][0] = k;
	 atom[no_atoms][1] = l;
	 no_atoms++;

         atom[no_atoms][0] = -k;
	 atom[no_atoms][1] = -l;
         no_atoms++; 
         k+=1.0;
         if(l >= i) s=-1.0;
         l+=s;
      }
      i++;
    }


WritePDB( N, Elemento, Inos, Trunc);

/* fin de main */
}  





/* Genera el Archivo PDB */

void WritePDB(unsigned int N,unsigned int Elemento, unsigned int Inos, unsigned int Trunc)
{



 FILE *ffwrite;
 int i=0,j=1,k,s=1,ni,in,Z,inos;	/* Sub indices */
 int trunc = Trunc;
 float r=0.7071067812;		/* Factor de reescalamiento */
 char El[2];	/* Nombre del elemento */

	switch(Elemento)
	{
	  case 1:
		strcpy(El,"AU");
		r *= 2.884;
		break;
	  case 2:
		strcpy(El,"RH");
		r *= 2.69;
		break;
	  case 3:
		strcpy(El,"PD");
		r *= 2.751;
		break;
	  case 4:
		strcpy(El,"PT");
		r *= 2.775;
		break;
	  case 5:
		strcpy(El,"PB");
		r *= 3.5;
		break;
      case 6:
          strcpy(El, "AG");
          r *= 2.36;
          break;
	}
 
 
      if ((ffwrite = fopen("octat.pdb","w")) == NULL)
    {
     printf("Sorry, I can't open the file octa.pdb \n");
     exit(1);
    }

 i=trunc;
 k=0;
 in = 0;
 no_atoms=1;
 Z=N;
 inos=Inos;


 while(i<N)
 {
    s=i;
    k=sfibo(i);
    while(s>=0)
    {
      ni=nitera(s);
      for(j=0;j<ni;j++)
      {
	  if(atom[k][0] <= (N-trunc+0.5) &&  atom[k][1]<=(N-trunc+0.5) && atom[k][0] >= -(N-trunc+0.5) && atom[k][1] >= -(N-trunc+0.5))
 	  {
	
            fprintf(ffwrite,"HETATM");
            fprintf(ffwrite,"%5d",no_atoms++);
            fprintf(ffwrite," %s1  UNK A   1    ",El);
            fprintf(ffwrite,"%8.3f",atom[k][0]*r);
            fprintf(ffwrite,"%8.3f",atom[k][1]*r);
            fprintf(ffwrite,"%8.3f",(in-Z)*r);
            fprintf(ffwrite," %s%s\n"," 1.00  0.00          ",El);
          }
           k++;
      }
      
      s-=2;
      if(s>=0) k=sfibo(s);
    
    }
    i++;
    in++;
 }

 i= N;
 inos = Inos * 2;
 while(inos>0)
 {
    s=i;
    k=sfibo(i);
    while(s>=0)
    {
      ni=nitera(s);
      for(j=0;j<ni;j++)
      {
          
	  if(atom[k][0]<=(N-trunc+0.5)   &&  atom[k][1]<=(N-trunc+0.5) && atom[k][0] >= -(N-trunc+0.5) && atom[k][1] >= -(N-trunc+0.5))
 	  {
            fprintf(ffwrite,"HETATM");
            fprintf(ffwrite,"%5d",no_atoms++);
            fprintf(ffwrite," %s1  UNK A   1    ",El);
            fprintf(ffwrite,"%8.3f",atom[k][0]*r);
            fprintf(ffwrite,"%8.3f",atom[k][1]*r);
            fprintf(ffwrite,"%8.3f",(in-Z)*r);
            fprintf(ffwrite," %s%s\n"," 1.00  0.00          ",El);
	  }
           k++;
      }

      s-=2;
      if(s>=0) k=sfibo(s);

    }
    if( (inos %2 )==0 )
       i--;
    else i++;
    inos--;
    in++;
 }
i=N;

 while( i >= trunc)
 {
    s=i;
    k=sfibo(i);
    while(s>=0)
    {
      ni=nitera(s);
      for(j=0;j<ni;j++)
      {
          if(atom[k][0]<=(N-trunc+0.5) &&  atom[k][1]<=(N-trunc+0.5)  && atom[k][0] >= -(N-trunc+0.5) && atom[k][1] >= -(N-trunc+0.5))
	  {
            fprintf(ffwrite,"HETATM");
            fprintf(ffwrite,"%5d",no_atoms++);
            fprintf(ffwrite," %s1  UNK A   1    ",El);
            fprintf(ffwrite,"%8.3f",atom[k][0]*r);
            fprintf(ffwrite,"%8.3f",atom[k][1]*r);
            fprintf(ffwrite,"%8.3f",(in-Z)*r);
            fprintf(ffwrite," %s%s\n"," 1.00  0.00          ",El);
	  }
           k++;
      }
      
      s-=2;
      if(s>=0) k=sfibo(s);
    
    }
    i--;
    in++;
 }




     fclose(ffwrite);
    
return;
}

int sfibo(int i)
{
   if(i<=1) return i;
   else return sfibo(i-1)+(i-1)*4;
}

int nitera(int s)
{ 
   if (s==0) return 1;
   else return (s*4);
}
