#include <stdio.h>

int main(void) {
    int *direccion;
    int edad = 0;

    printf("Cuantos anios tienes: ");
    scanf("%d", &edad);

    direccion = &edad;

    printf("La edad esta guardada en la posicion de memoria: %p\n", direccion);
    printf("La edad esta guardada en la posicion de memoria: %p\n", &edad);
    printf("Tu edad es: %d\n", *direccion);
    printf("El apuntador de la edad esta guardada en la posicion de memoria: %p\n", &direccion);

////////////////////////////////////////// ARREGLOS ////////////////////////////////////////////
    /*
    int *dir;
    int x;

    dir = &v[0]; // == dir = v
    x = *dir; // == x = v[0] = 5
    */
    printf("\n////////////////////////////////////////// ARREGLOS ////////////////////////////////////////////\n");
    int arr[5] = {3, 0, 2, 2, 4};
    
    for(int i = 0; i < 5 ; i++) {
        printf("%d\n", /* *(arr+i) == */arr[i]);
    }
    
    return 0;
}