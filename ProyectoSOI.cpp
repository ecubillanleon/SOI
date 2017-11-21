#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


int hijos;

int *leerArchivo();

extern FILE *stdin;

int *leerArchivo()
{
   	if(stdin != NULL)
   	{
	   	fscanf(stdin, "%d", &hijos);
		int *nietos;
		nietos = new int[hijos];
        int validar = 0;
	
		int i = 0, n;
		
		while(!feof(stdin)) 
		{
			fscanf(stdin, "%d", &n);
			if(i < hijos) 
				nietos[i] = n;
			
			else if(n > 0 && !feof(stdin)) 
			{
				validar = 1;				
				break;
			}
			
			i++;
		}
		
		fclose(stdin);
			
		return (nietos);
	}
}

int main()
{
	int *nietos;
    nietos = leerArchivo();
        
	if(false) 
		printf("\nEl Arbol tiene mas de tres niveles");
	
	else
	{
			
		int pid;
		int hijo1, hijo2;

		for(int j = 0; j < hijos; j++)
		{
			hijo1 = j;
			
			pid = fork();
			
			if(pid == 0)break;
				
		}

		if(pid != 0)
		{
			int pid_hijos[hijos];
			
			for(int j = 0; j < hijos;j++)
				pid_hijos[j] = wait(0);

			int aux; 
			
			for(int i = 0; i < hijos; i++)
			{
				for(int j = 0; j < hijos-1-i; j++)
				{
					if(pid_hijos[j] >  pid_hijos[j+1])
					{
						aux = pid_hijos[j];
						pid_hijos[j] = pid_hijos[j+1];
						pid_hijos[j+1] = aux;
					}
				}
			}
				
			printf("\n\nRaiz: %d\n", getpid());

			char nombre[6];
			FILE* archivo;
			int n = 1;
			
			for(int i = 0; i < hijos; i++)
			{
				printf("\tHijo %d: %d\n", i+1, pid_hijos[i]);

				snprintf(nombre, 6,"%d",pid_hijos[i]);
				archivo = fopen(nombre, "r");
				
				if(archivo) 
				{
					int j = 0;	
					int pid_nieto;	
					
					while(!feof(archivo) && j < nietos[i])
					{
						fscanf(archivo, "%d", &pid_nieto);
						printf("\t\tNieto %d: %d\n", n, pid_nieto);
						n++;
						j++;
					}
					
					fclose(archivo);
				}
			}	
		}
		
		else 
		{		
			if(nietos[hijo1] > 0)
			{
				char nombre[6];
				snprintf(nombre, 6,"%d",getpid());
				FILE* archivo = fopen(nombre, "w");
				
				if(archivo)
				{
					for(int j = 0; j < nietos[hijo1]; j++)
					{
						hijo2 = j;
						
						pid = fork();
				
						if(pid == 0)
							break;
					}

					if(pid == 0){						
						
						printf("\nSoy una hoja del Arbol");
						sleep(2);
						
						_exit(0);		
					}
					
					else 
					{
						int pid_nietos[nietos[hijo1]];
						
						for(int j = 0; j < nietos[hijo1];j++)
							pid_nietos[j] = wait(0);
						
						int aux; 
						
						for(int i = 0; i < nietos[hijo1]; i++)
						{
							for(int j = 0; j < nietos[hijo1]-1-i; j++)
							{
								if(pid_nietos[j] >  pid_nietos[j+1])
								{
									aux = pid_nietos[j];
									pid_nietos[j] = pid_nietos[j+1];
									pid_nietos[j+1] = aux;
								}
							}
						}
						
						for(int i = 0; i < nietos[hijo1]; i++)
						{
							fprintf(archivo, "%d\n", pid_nietos[i]);						
						}
					}
					
					fclose(archivo);
				}
				
				else 
				{
					printf("El archivo para el hijo %d-%d no fue creado",hijo1+1,getpid());		
				}
				
			}	
			
			_exit(0);

		}
	}
			
	return 0;
}