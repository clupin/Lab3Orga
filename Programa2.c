#include <stdio.h>
#include <malloc.h>
#include <stdio.h>

#define N 1000000


int calcular(char *a);

int main(int argc, char *argv[])
{
    char a[N];

    // NO hago entrada ahora, solamente números sin significado
    for(size_t i = 0; i < N; i++){
        a[i] = i % 120 + 1;
    }

    printf("%d\n", calcular(a));
    
    return 0;
}

int calcular(char *a){
    int acc = 0;

    for(size_t i = 0; i < N - 1; i++)
    {
       char tmp = a[i] ^ a[i + 1];
       acc = acc + tmp;
    }

    return acc;
}
