#include <stdio.h>

void busqueda_lineal(int arr[], int len, int numero);
void busqueda_bin(int arr[], int len, int numero);

void insertion_sort(int arr[], int len);
void seleccion(int arr[], int len);
void bubble_sort(int arr[], int len);

int main(void) {
    // arreglo original
    int arr[7] = {12, 9, 3, 7, 14, 11, 8};
	///////////////////// BUSQUEDA LINEAL /////////////////////
    printf("\nBuscqueda lineal\n");
    busqueda_lineal(arr, 7, 111);

    ///////////////////// BUSQUEDA BINARIA /////////////////////
    
    printf("\nBuscqueda binaria\n");
    int arr2[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    busqueda_bin(arr, 6, 3);

    ///////////////////// SELECTION SORT /////////////////////
    printf("\nArreglo a ordenar con selection sort: \n");
	for(int i = 0 ; i < 7 ; i++)
		printf("[%d] = %d\n", i, arr[i]);

    seleccion(arr, 7);
    printf("\nArreglo ordenado por seleccion: \n");
	for(int i = 0 ; i < 7 ; i++)
		printf("[%d] = %d\n", i, arr[i]);

    int arr_reset[7] = {12, 9, 3, 7, 14, 11, 8};
    for(int i = 0; i < 7; i++) {
        arr[i] = arr_reset[i];
    }

    ///////////////////// INSERTION SORT /////////////////////

    printf("\nArreglo a ordenar con insertion sort: \n");
	for(int i = 0 ; i < 7 ; i++)
		printf("[%d] = %d\n", i, arr[i]);

    insertion_sort(arr, 7);
    printf("\nArreglo ordenado por insercion: \n");
	for(int i = 0 ; i < 7 ; i++)
		printf("[%d] = %d\n", i, arr[i]);
    
    for(int i = 0; i < 7; i++) {
        arr[i] = arr_reset[i];
    }
    
    ///////////////////// BUBBLE SORT /////////////////////

    printf("\nArreglo a usar en bubble sort: \n");
	for(int i = 0 ; i < 7 ; i++)
		printf("[%d] = %d\n", i, arr[i]);

    bubble_sort(arr, 7);
    printf("\nArreglo ordenado por bubble: \n");
	for(int i = 0 ; i < 7 ; i++)
		printf("[%d] = %d\n", i, arr[i]);
    return 0;
}

void busqueda_lineal(int arr[], int len, int numero) {
    int flag = 0;
    for(int i = 0 ; i < len ; i++) {
        if(numero == arr[i]) {
            flag = 1;
        }
    }
    
    if(flag) {
        printf("Numero encontrado en arreglo\n");
    } else {
        printf("El numero no se encuentra dentro del arreglo\n");
    }
}

void busqueda_bin(int arr[], int len, int numero) {
    int inicio = 0; 
    int fin = len - 1;
    int flag = 0;

    for(int i = 0 ; i < len ; i++) {
        int medio = inicio + (fin - inicio) / 2;

        if(arr[medio] == numero) {
            flag = 1;
            break;
        } else if(arr[medio] < numero) {
            inicio = medio + 1;
        } else {
            fin = medio - 1;
        }
    }

    if(flag) { // 1
        printf("Numero encontrado en el arreglo\n"); // 1
    } else { // 1 
        printf("El numero no se encuentra dentro del arreglo\n"); // 1
    }
}
    
void seleccion(int arr[], int len) {
    for (int i = 0; i < len; i++) {
        int menor = 1000;
        int pos = -1;

        // Buscar el menor valor en el subarreglo desde i hasta len
        for (int j = i; j < len; j++) {
            if (arr[j] < menor) {
                menor = arr[j];
                pos = j;
            }
            printf("i = %d, menor = %d, posicion = %d\n", j, menor, pos);
        }

        printf("\nINT\n");
        // Intercambiar el menor encontrado con el elemento en la posición i
        if (pos != -1) {
            int temp = arr[i];
            arr[i] = arr[pos];
            arr[pos] = temp;
        }
    }
}

// Ordena el arreglo usando Insertion Sort
// Insertion Sort toma cada elemento y lo inserta en la posición correcta dentro de la parte ordenada del arreglo.
// void insertion_sort(int arr[], int len) {
//     for (int i = 1; i < len; i++) {
//         int key = arr[i]; // Elemento a insertar
//         int j = i - 1;
//         // Mueve los elementos mayores que key una posición adelante
//         while (j >= 0 && arr[j] > key) {
//             arr[j + 1] = arr[j]; // Desplaza el elemento hacia la derecha
//             j--;
//         }
//         // Inserta el elemento en la posición correcta
//         arr[j + 1] = key;
//     }
// }

// Esta función ordena los números de menor a mayor usando el método "insertion sort"
void insertion_sort(int arr[], int len) {
    int j = 0;

    // Empezamos desde el segundo número (el primero ya está "ordenado")
    for (int i = 1; i < len; i++) {
        int temp = arr[i]; // Guardamos el número que queremos colocar en su lugar

        // Vamos a buscar dónde poner ese número, comparando hacia la izquierda
        for (j = i - 1; j >= 0; j--) {
            // Si encontramos un número más pequeño o igual, ya no hay que mover más
            if (arr[j] <= temp) {
                break; // Salimos del ciclo porque ya encontramos el lugar
            }

            // Si el número es más grande, lo movemos una posición a la derecha
            arr[j + 1] = arr[j];
        }

        // Finalmente colocamos el número guardado en el lugar correcto
        arr[j + 1] = temp;
    }
}

void bubble_sort(int arr[], int len) {
    // Vamos a repetir el proceso varias veces (una vez por cada número menos uno)
    for (int i = 0; i < len - 1; i++) {
        // En cada vuelta, comparamos pares de números uno por uno
        for (int j = 0; j < len - 1 - i; j++) {
            // Mostramos qué dos números estamos comparando
            printf("Comparando arr[%d] = %d con arr[%d] = %d\n", j, arr[j], j + 1, arr[j + 1]);

            // Si el número de la izquierda es más grande que el de la derecha...
            if (arr[j] > arr[j + 1]) {
                // ...los cambiamos de lugar (como si el grande "flotara" hacia la derecha)
                int temp = arr[j];        // Guardamos el número izquierdo en una caja temporal
                arr[j] = arr[j + 1];      // Ponemos el número derecho en el lugar izquierdo
                arr[j + 1] = temp;        // Ponemos el número de la caja en el lugar derecho

                printf("Intercambio realizado\n"); // Avisamos que hicimos un cambio
            }
        }

        // Después de cada vuelta, mostramos cómo va quedando el arreglo
        printf("Resultado parcial: ");
        for (int k = 0; k < len; k++) {
            printf("%d ", arr[k]);
        }
        printf("\n\n");
    }
}
