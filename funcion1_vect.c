#include <xmmintrin.h>
#include <emmintrin.h>
#include <pmmintrin.h>
#include <time.h>  
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h> /* for getopt */

#include "cargarchivo.h"


#define N 100000


__m128 _mm_parteentera_ps(__m128 a);

int _mm_compare_ps(__m128 a, __m128 b);

__m128 _mm_pow_ps(__m128 a, __m128 b);

__m128 _mm_pow2_ps(__m128 a, __m128 b);

float sumar(float *a);

int main (int argc, char **argv)
{
    clock_t start = clock(); 
    int index;
    int c;
    
    opterr = 0;
    
    while ((c = getopt (argc, argv, "f:")) != -1)
        switch (c)
    {
        case 'f':
            printf("Leyendo archivo[%s]...\n", optarg);
            float *F=leerArchivo(optarg);
            
            
            printf("%f\n",sumar(F));
            break;
        case '?':
            if (optopt == 'f')
                fprintf (stderr, "Opcion -%c requiere la direccion del archivo.\n", optopt);
            else if (isprint (optopt))
                fprintf (stderr, "Unknown option `-%c'.\n", optopt);
            else
                fprintf (stderr,
                         "Unknown option character `\\x%x'.\n",
                         optopt);
            return 1;
        default:
            abort ();
    }
    
    for (index = optind; index < argc; index++)
        printf ("Non-option argument %s\n", argv[index]);
    

    printf("\nTiempo transcurrido: %f", ((double)clock() - start) / CLOCKS_PER_SEC);
    return 0;
}



float sumar(float *a){
    float sumaF[4] __attribute__((aligned(16)));
    __m128 sumas= _mm_set1_ps(0);//suma alineada 1313 iniciadas en 0
    __m128 calculo;
    int i;
    __m128 aux;
    for ( i = 0; i < 100000; i+=4){
        //   multip =1;
        aux = _mm_load_ps(&a[i]);
        if(_mm_compare_ps(aux,_mm_set1_ps(0)))break;//corta el ciclo cuando el arreglo no tiene mas valores validos;
        //   calculo = sqrt(a[i]);
        calculo = _mm_sqrt_ps(aux);//se calcula la raiz cuadrada de los 4 float en paralelo
        calculo = _mm_pow2_ps(calculo,aux);// se decidió que por precicion de calculo se utilizará la funcion pow2
        sumas = _mm_add_ps(sumas, calculo);
        
    }
    _mm_store_ps(sumaF, sumas);
    return sumaF[0]+sumaF[1]+sumaF[2]+sumaF[3];
}
__m128 _mm_pow2_ps(__m128 a, __m128 b){//eleva a[i]^b[i] sin excepciones, pero no de forma paralela
    float base[4] __attribute__((aligned(16)));
    _mm_store_ps(base, a);
    float exponente[4] __attribute__((aligned(16)));
    _mm_store_ps(exponente, b);
    return _mm_setr_ps(
                       (b[0]==0)?0:powf(base[0], exponente[0]),
                       (b[1]==0)?0:powf(base[1], exponente[1]),
                       (b[2]==0)?0:powf(base[2], exponente[2]),
                       (b[3]==0)?0:powf(base[3], exponente[3]));
}
__m128 _mm_pow_ps(__m128 a, __m128 b){//eleva a[i]^b[i] para todo a real, y b entero < 0
    __m128 cero = _mm_set1_ps(0);
    __m128 uno = _mm_set1_ps(1.0);//se declaran las constantes [0,0,0,0] y [1,1,1,1] para ser usadas luego
    
    b = _mm_parteentera_ps(b);// para evitar problemas con decimales.
    b = _mm_sub_ps(b, uno);//b[i]--
    b = _mm_max_ps(b, cero);// se busca el maximo con 0 para luego comparar y saber cuales deben o no deben ser
    
    __m128 activo= _mm_mul_ps(_mm_set1_ps(1.0), b);//elimina de los activos a los exponentes menores que 1
    activo= _mm_min_ps(activo , uno);//con esto se setean en numeros 1 o 0 declarando activos a quienes su exponente sea mayor que 0
   
    __m128 resul= a;//el resultado se iguala a la entrada a 
    __m128 act_x_a;//se declara variable para ser usarda en el bucle
   
    
    while (!_mm_compare_ps(b, cero)) {//luego lo explico
        act_x_a = _mm_mul_ps(a, activo);//se elimina los activos de las variables a multiplicar para poder ejecutar las multiplicaciones en paralelo
        act_x_a = _mm_max_ps(act_x_a, uno);//las variables eliminadas se setean en 1 para que el resultado quede como en el estado anterior
        resul= _mm_mul_ps(resul, act_x_a);// se multiplican en paralelo lo la base por si misma tantas veces como sea indicado por el exponente
        
        b = _mm_sub_ps(b, uno);//b[i]--
        b = _mm_max_ps(b, cero);// en caso de que la resta deje algun valor en negativo este se setea en 0
        
        activo= _mm_mul_ps(activo, b);// se realiza nuevamente la busqueda de los que ya no estan activos  que depende de los valores en los exponentes.
        activo= _mm_min_ps(activo , uno);
        
    }
    
    return resul;// se retorna un vector con los valores pedidos
    
}
int _mm_compare_ps(__m128 a, __m128 b){//funcion que compara uno a uno los elementos en un vector
    a=_mm_sub_ps(a, b);
    float f[4] __attribute__((aligned(16)));
    _mm_store_ps(f, a);
    int r=((f[0]+f[1]+f[2]+f[3])==0);
    return r;//la hicimos porque no encontramos una que hiciera esto exactamente
}
__m128 _mm_parteentera_ps(__m128 a){//calcula parte  para evtar problemas en la implementacion de la funcion _mm_pow_ps
    float f[4] __attribute__((aligned(16)));
    _mm_store_ps(f,a);
    
    f[0]=(int) f[0];
    f[1]=(int) f[1];
    f[2]=(int) f[2];
    f[3]=(int) f[3];

    return _mm_load_ps(&f[0]);
}
