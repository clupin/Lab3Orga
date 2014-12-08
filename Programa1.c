#include <stdio.h>
#include <malloc.h>
#include <stdio.h>
#include <math.h>

#define N 400


float calcular(float *a, float *b);

int main(int argc, char *argv[])
{
    float a[N];
    float b[N];

    // NO hago entrada ahora, solamente números sin significado, usted debe
    // hacer que el programa lea esto desde un archivo
    int i;
    for(i = 0; i < N; i++){
        a[i] = i + 1;
    }

    for(i = 0; i < N; i++){
        b[i] = i + 1;
    }

    printf("%f\n", calcular(a, b));
    
    return 0;
}

float calcular(float *a, float *b){

    float acc = 0;
    float acc2 = 0;
    int i;
    for( i = 0; i < N; i++){
        acc = acc + a[i] / 2 + sqrt(b[i]);
    }

    for(i = 0; i < N; i++){
        acc2 = acc2 + pow(a[i], 2) - acc;
    }

    return acc2;
}
