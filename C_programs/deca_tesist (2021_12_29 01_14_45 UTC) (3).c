
/* 
9-07-2001
PROGRAMA QUE GENERA UN DECAEDRO TRUNCADO GEOMETRICAMENTE PERFECTO.
EL NIVEL DEL DECAEDRO ESTARA DADO POR EL PARAMETRO 1 DEL PROGRAMA
EL ELEMENTO DEL DECAEDRO ESTA DADO POR EL PARAMETRO 2 DEL PROGRAMA
PARAMETRO 3 CAPAS INTERMEDIAS
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

void Initial(void);
	/* Genera los puntos iniciales del decaedro y los vectores auxiliares para los atomos intermedios */


void WritePDB(unsigned int, unsigned int, unsigned int );
	/* Crea el archivo con formato PDB que almacena las coordenadas del decaedro */

int sfibo(int );    /*Funciones que calculan numero de atomos en las capas del decaedro */
int nitera(int );




/*
Variables Globales.
*/

double  atom[3][100000];   /* Arreglo que contiene las coordenadas del decaedro en un plano  X, Y   */
double  aux[2][5], penta[2][5];	/* auxiliares para puntos medios */

unsigned int no_atoms;     /* Numero de atomos en el arreglo. Este depende del nivel del decaedro */



void Initial()
{

	/* Coordenadas de los atomos Nivel 1 (pentagono) */

	penta[0][0] = 0.8506508083;	/* 0.5/cos(54) = h */
	penta[1][0] = 0.0;		/* 0.0 */

	penta[0][1] = 0.262865556;	/* h*cos(72) */
	penta[1][1] = 0.8090169943;	/* h*cos(18) */
	
	penta[0][2] = -0.6881909602;	/* -h*cos(36) */
	penta[1][2] = 0.5;		/* 0.5 */

	penta[0][3] = -0.6881909602;	/* -h*cos(36) */
	penta[1][3] = -0.5;		/* -0.5 */

	penta[0][4] = 0.262865556;	/* h*cos(72) */
	penta[1][4] = -0.8090169943;	/* -h*cos(18) */



	/*Coordenadas de los auxiliares para puntos medios */

	aux[0][0] = penta[0][1] - penta[0][0];		/* Atomo 2 menos Atomo 1 */
	aux[1][0] = penta[1][1] - penta[1][0];

	aux[0][1] = penta[0][2] - penta[0][1];		/* Atomo 3 menos Atomo 2 */
	aux[1][1] = penta[1][2] - penta[1][1];

	aux[0][2] = penta[0][3] - penta[0][2];		/* Atomo 4 menos Atomo 3 */
	aux[1][2] = penta[1][3] - penta[1][2];

	aux[0][3] = penta[0][4] - penta[0][3];		/* Atomo 5 menos Atomo 4 */
	aux[1][3] = penta[1][4] - penta[1][3];

	aux[0][4] = penta[0][0] - penta[0][4];		/* Atomo 1 menos Atomo 5 */
	aux[1][4] = penta[1][0] - penta[1][4];

	
}



/* PROCESO PRINCIPAL */


void main(int argc, char *argv[])
{
unsigned int Nivel = atoi(argv[1]);       /*Nivel del decaedro */
unsigned int Elemento = atoi(argv[2]); 	/*Elemento del decaedro */
unsigned int Inos = atoi(argv[3]);
unsigned int Trunc = atoi(argv[4]);

unsigned int n;		/*Variable que va formando los niveles del decaedro hasta el Nivel. */
unsigned int i,j,trunc,t;		/*variables subindices */

/* Inicia el proceso de creacion de pentagonos, 1 pentagono por nivel */


Initial();	/* en la funcion Initial se crearon los 2 primeros niveles */

/* Nivel 0 */
	atom[0][0] = 0.0;
	atom[1][0] = 0.0;

no_atoms = 1;
  if(Trunc > (Nivel/2)){ 
    Trunc =(Nivel/2);
     printf("\n Aplicando Truncamiento Maximo \n");
  }
  
 

/* Nivel 1 en adelante */

	n=1;
        trunc = Nivel-Trunc;
        t=0;
        while( n <= Nivel )
        {
             for(i=0;i<5;i++)
             {
               atom[0][no_atoms] = n*penta[0][i];	/*Atomos del pentagono */
	       atom[1][no_atoms] = n*penta[1][i];
	       atom[2][no_atoms] = 0.0;
               if(n > trunc){
                              atom[2][no_atoms] = -1.0;
                             }
	       no_atoms++;

               for(j=0;j<n-1;j++)
		{
	         atom[0][no_atoms]=atom[0][no_atoms-1] + aux[0][i];        /*Atomos intermedios */
	         atom[1][no_atoms]=atom[1][no_atoms-1] + aux[1][i];
		 atom[2][no_atoms] = 0.0;
	           if( n> (trunc+1) )
                   if( j<t || j>=(trunc)  )
			{
			atom[2][no_atoms] = -1.0;
			 
			}
		 no_atoms++;
	        }
	        
              }
            n++;
            if( n> (trunc+1) ) t++;
         }
   

    WritePDB(Nivel, Elemento,Inos);	/* Subrutina que escribe el pdb */

   


/* fin de main */

    

}




               
  

void WritePDB(unsigned int Nivel,unsigned int Elemento, unsigned int Inos)
{




 FILE *ffwrite;	/* Nombre del archivo */
 
int i=0,j=1,k,s=1,ni,in,Z,inos;    /* Sub indices */
 double r1,r2;	/* Factor de reescalamiento */
 char El[2];	/* Nombre del elemento */

	switch(Elemento)
	{
	  case 1:
		strcpy(El,"AU");
		r1 = 2.884;
		break;
	  case 2:
		strcpy(El,"RH");
		r1 = 2.69;
		break;
	  case 3:
		strcpy(El,"PD");
		r1 = 2.751;
		break;
	  case 4:
		strcpy(El,"PT");
		r1 = 2.775;
		break;
	  case 5:
		strcpy(El,"PB");
		r1 = 3.5;
		break;
      case 6:
          strcopy(El, "AG");
          r1 = 2.36;
          break;
	}
	
	r2= 0.5257311122*r1;  /* constante (1-t) donde t = (1+raiz(5))/2   */
   
      if ((ffwrite = fopen("deca.pdb","w")) == NULL)
    {
     printf("Sorry, I can't open the file ~/temp/deca.pdb \n");
     exit(1);
    }



 i=0;
 k=0;
 in = 0;
 no_atoms=1;
 Z=Nivel;
 inos=Inos;
 while(i<Nivel)
 {
    s=i;
    k=sfibo(i);
    while(s>=0)
    {
      ni=nitera(s);
      for(j=0;j<ni;j++)
      {
       if(atom[2][k] > -0.5)
         {
          fprintf(ffwrite,"HETATM");
          fprintf(ffwrite,"%5d",no_atoms++);
          fprintf(ffwrite," %s1  UNK A   1    ",El);
          fprintf(ffwrite,"%8.3f",atom[0][k]*r1);
          fprintf(ffwrite,"%8.3f",atom[1][k]*r1);
          fprintf(ffwrite,"%8.3f",(in-Z)*r2);
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

i= Nivel;
inos = Inos * 2;
 while(inos>0)
 {
    s=i;
    k=sfibo(i);
    while(s>=0)
    {
      ni=nitera(s);
      for(j=0;j<ni;j++){
       if(atom[2][k] > -0.5)
        {
          fprintf(ffwrite,"HETATM");
          fprintf(ffwrite,"%5d",no_atoms++);
          fprintf(ffwrite," %s1  UNK A   1    ",El);
          fprintf(ffwrite,"%8.3f",atom[0][k]*r1);
          fprintf(ffwrite,"%8.3f",atom[1][k]*r1);
          fprintf(ffwrite,"%8.3f",(in-Z)*r2);
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
i=Nivel;

 while(i>=0)
 {
    s=i;
    k=sfibo(i);
    while(s>=0)
    {
      ni=nitera(s);
      for(j=0;j<ni;j++){
       if(atom[2][k] > -0.5)
      {
          fprintf(ffwrite,"HETATM");
          fprintf(ffwrite,"%5d",no_atoms++);
          fprintf(ffwrite," %s1  UNK A   1    ",El);
          fprintf(ffwrite,"%8.3f",atom[0][k]*r1);
          fprintf(ffwrite,"%8.3f",atom[1][k]*r1);		
          fprintf(ffwrite,"%8.3f",(in-Z)*r2);
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
   else return sfibo(i-1)+(i-1)*5;
}

int nitera(int s)
{
   if (s==0) return 1;
   else return (s*5);
}
