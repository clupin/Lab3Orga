#include <stdio.h>
#include <malloc.h>
#include <stdio.h>
#include <math.h>

#define N 30

float sumar(float *a){

    float suma = 0;
    float calculo = 0;
    float multip = 1;
    int i,j;

    for (/*size_t*/ i = 0; i < N; i++){
    	multip =1;
    	calculo = sqrt(a[i]);
	    for(/*size_t*/ j = 0; j < a[i]; j++){
	    	multip = multip*calculo;
	    }
        suma = suma + multip;
    }

    return suma;
}

int main(int argc, char *argv[])
{
	printf("el texto\n");
    float a[N];
    int i;
    //"inicializacion" del arreglo
    for(/*size_t */i = 0; i < N; i++){
        a[i] = i + 1;
    }

    printf("%f\n", sumar(a));
    
    return 0;
}
