#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;

//int escribir_vector(vector<char>& pvector);

/*************************************************/
void escribir_vector(const vector<char> & pvector)
{
	for(int i = 0;i<pvector.size();i++)
	{
		cout << pvector[i];
	}
	
	cout << "\n"; //agregamos un salto de linea
	
}

/*************************************************/
int main(int argc,char *argv[])
{
	//variables
	FILE* fichero = fopen(argv[1],"r");
	char letra;
	vector<char> vector_cabecera;
	vector_cabecera.resize(0);
	vector<char> vector_secuencia;
	vector_secuencia.resize(0);
	vector<char> vector_mas;
	vector<char> vector_puntuacion;
	
	
	//inicio = 0, 
	//seccion_cabecera = 1; 
	//seccion_secuencia = 2;
	//seccion_mas = 3;
	//seccion_puntuacion = 4;
	int seccion = 0; 
	
	
	//abriendo archivo
	if(fichero == NULL)
	{
		printf("\n NO ES POSIBLE ABRIR EL ARCHIVO: \n");
		exit(1);
	}
	else
	{
		printf("\n ARCHIVO ABIERTO \n");
	}

	//mostrando contenido
	printf("\n ----------------------------------");
	printf("\n CONTENIDO DE ARCHIVO FASTQ");
	printf("\n ----------------------------------\n");

	letra = getc(fichero);

	while(feof(fichero)==0)
	{
		//vector_cabecera.push_back(letra);	
		if(letra == '@')
		{
			
			if(seccion == 4)	
			{	
				//escribir_vector(vector_puntuacion);
				vector_puntuacion.clear();
				vector_puntuacion.resize(0);
			}
			
			seccion = 1;
			vector_cabecera.push_back(letra);
			
			
		}
		else
		{
			if(letra == '+')
			{
				if(seccion == 2)
				{
					printf("SECUENCIA : ");
					escribir_vector(vector_secuencia);
					vector_secuencia.clear();
					vector_secuencia.resize(0);
				}
				seccion = 3;
				vector_mas.push_back(letra);
			}
			else
			{
				if(letra == '\n')//salto de linea hacia cabecera o secuencia
				{
					if(seccion==1)// la anterior seccion era cabecera
					{
						seccion  = 2;

						//escribir anterior seccion
						printf("CABECERA : ");
						escribir_vector(vector_cabecera);
						vector_cabecera.clear();
						vector_cabecera.resize(0);

					}
					else
					{
						if(seccion == 3)
						{
							seccion = 4;
							
							//escribir seccion 3
							//escribir_vector(vector_mas);
							vector_mas.clear();
							vector_mas.resize(0);
						}
						else
						{
							
						}
					}
				}
				else //puede ser char de secuenca, cabecera, mas o puntuacion
				{


					if(seccion == 1)//char en cabecera
					{
						vector_cabecera.push_back(letra);
					}			
					else
					{
						if(seccion == 2)//char en secuencia
						{
							vector_secuencia.push_back(letra);
						}
						else
						{
							if(seccion == 3)
							{
								vector_mas.push_back(letra);
							}
							else
							{
								if(seccion == 4)
								{
									vector_puntuacion.push_back(letra);
								}
							}
						}
					}


				}
			}
		}
		
		//printf("%c",letra);ribir_verctor()
		letra = getc(fichero);
	}
	
	
	//escribir_vector(vector_puntuacion);
	
	if(fclose(fichero)!=0)
		printf("\n PROBLEMAS AL CERRAR EL FICHERO \n");
}
