
#include<stdlib.h>
#include "cargarchivo.h"

float* leerArchivo (char *direccion){
    
    FILE *archivo;
    char mensaje;
    float lista[100000]  __attribute__((aligned(16)));
    int n;
    int i=0;
    
    archivo = fopen(direccion,"r");
    
    if(archivo == NULL){
        printf("\nError al abrir el archivo");
    } else {
        while (feof(archivo)==0){
            mensaje = fgetc(archivo);
            lista[i]= atoi(&mensaje);
            mensaje = fgetc(archivo);
            i++;
        }
    }
    fclose(archivo);
    
    return lista;
}