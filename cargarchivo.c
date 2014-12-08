
#include<stdlib.h>
#include "cargarchivo.h"

float* leerArchivo (char *direccion){
    
    FILE *archivo;
    char mensaje;
    float lista[100000];
    int n;
    int i=0;
    
    archivo = fopen(direccion,"r");
    
    if(archivo == NULL){
        printf("\nError al abrir el archivo");
    } else {
        n = fgetc(archivo);
        char arr[n];
        while (feof(archivo)==0){
            mensaje = fgetc(archivo);
            lista[i]= atoi(mensaje);
            i++;
        }
    }
    fclose(archivo);
    
    return lista;
}