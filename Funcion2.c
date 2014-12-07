#include <stdio.h>
#include <malloc.h>
#include <stdio.h>
#include <math.h>

#define N 30

float modulo(float *a){
    float suma = 0;
    float multip = 1;
    float elModulo;
    int i;

    for (/*size_t*/ i = 0; i < N; i++){
        multip =a[i]*a[i];
        suma = suma + multip;
    }

    elModulo = sqrt(suma);
    printf("el modulo es: %f\n", elModulo);
    return elModulo;
}

float sumar(float *a){
    float suma=0;
    float multip;
    float elModulo = modulo(a);
    int i;
    float cont=0;
    for (/*size_t*/ i = 0; i < N; i++){
        if(i<elModulo){
            multip = a[i]*a[i+1];
            suma = suma + multip;
            cont++;
        }
    }

    return suma;
}

int main(int argc, char *argv[])
{
	printf("el texto\n");
    float a[N];
    int i;
    //"inicializacion" del arreglo
    /*for(/*size_t i = 0; i < N; i++){
        a[i] = i + 1;
    }*/
    a[0]= 5; a[1]= 3; a[2]= 5; a[3]= 5; a[4]=1; a[5]= 2; a[6]= 1; a[7]= 1; a[8]= 1; a[9]= 5;
    a[10]= 3; a[11]= 1; a[12]= 3; a[13]= 4; a[14]=1; a[15]= 4; a[16]= 1; a[17]= 2; a[18]= 5; a[19]= 4;
    a[20]= 2; a[21]= 5; a[22]= 1; a[23]= 4; a[24]=4; a[25]= 4; a[26]= 5; a[27]= 2; a[28]= 2; a[29]= 3;

    printf("%f\n", sumar(a));
    
    return 0;
}