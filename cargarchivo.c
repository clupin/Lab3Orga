
#include<stdlib.h>
#include "cargarchivo.h"

float* leerArchivo (char *direccion){
    
    FILE *archivo;
    char mensaje;
    float lista[100000]  __attribute__((aligned(16)));

    
    int n;
    int i=0;
    
    for(i=0;i<100000;i++)lista[i]=0.0;
    i=0;
	char *str;
    
    archivo = fopen(direccion,"r");
    
    if(archivo == NULL){
        printf("\nError al abrir el archivo");
    } else {
        while (feof(archivo) == 0)
        {
            
            str=(char *) malloc(99*sizeof(char));
            fgets(str,99,archivo);
            str= strtok(str, "\n");
            lista[i]=atof(str);
            i++;
            if(i==10000){//limitador
                break;
            }
        }
    }
    fclose(archivo);
    
    return lista;
}