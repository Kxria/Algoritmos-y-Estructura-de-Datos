#include <stdio.h>

void shell(int arreglo[], int longitud);
void radixSort(int arr[], int len);
void mergeSort(int arr[], int len);

int main(void) {
    printf("|||||||||||||||| RADIXSORT |||||||||||||||||||||\n");
    int arr[] = {5432, 150, 35, 302, 23, 451, 151, 806, 18};
    int len = sizeof(arr) / sizeof(arr[0]);

    printf("Arreglo original:\n");
    for (int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    radixSort(arr, len);

    printf("Arreglo ordenado con Radix Sort:\n");
    for (int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("\n|||||||||||||||| SHELLSORT |||||||||||||||||||||\n");
    
    int arr1[] = {5432, 150, 35, 302, 23, 451, 151, 806, 18};
    int arr2[] = {94, 14, 25, 33, 82, 25, 59, 13};
    int len2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("Arreglo 2 original:\n");
    for (int i = 0; i < len2; i++) {
        printf("%d ", arr2[i]);
    }
    printf("\n");

    shell(arr2, len2);

    printf("Arreglo ordenado con Shell Sort:\n");
    for (int i = 0; i < len2; i++) {
        printf("%d ", arr2[i]);
    }
    printf("\n");

    printf("\n|||||||||||||||| MERGESORT |||||||||||||||||||||\n");

    int arr_merge[] = {12, 9, 3, 7, 14, 11, 8};
    int len_merge = sizeof(arr_merge) / sizeof(arr_merge[0]);

    printf("Arreglo original:      LEN = %d\n", len_merge);
    for (int i = 0; i < len_merge; i++) {
        printf("%d ", arr_merge[i]);
    }
    printf("\n\n");

    mergeSort(arr_merge, len);

    printf("Arreglo ordenado con Merge Sort:\n");
    for (int i = 0; i < len_merge; i++) {
        printf("%d ", arr_merge[i]);
    }
    printf("\n");

    return 0;
}

void shell(int arr[], int len) {
    // Primer ciclo: define el salto (gap) entre elementos a comparar
    // Declaración: int k = len / 2 → empezamos con la mitad del arreglo
    // Comparación: k > 0 → seguimos reduciendo el gap hasta llegar a 1
    // Incremento: k = k / 2 → el gap se reduce a la mitad en cada iteración
    for (int k = len / 2; k > 0; k = k / 2) {

        // Segundo ciclo: recorre el arreglo desde el índice 'k' hasta el final
        // Declaración: int i = k → empezamos en el primer índice que permite comparación con salto 'k'
        // Comparación: i < len → procesamos hasta el final del arreglo
        // Incremento: i++ → avanzamos de uno en uno
        for (int i = k; i < len; i++) {
            int temp = arr[i]; // Guardamos el valor actual que queremos insertar en su posición correcta
            int j;

            // Tercer ciclo: retrocede desde 'i' en pasos de 'k' para comparar con elementos anteriores
            // Declaración: int j = i → empezamos desde el elemento actual
            // Comparación: j >= k → nos aseguramos de no salir del arreglo por la izquierda
            // Incremento: j = j - k → retrocedemos en pasos del tamaño del gap
            for (j = i; j >= k; j = j - k) {

                // Condición: comparamos el valor anterior (arr[j - k]) con el valor actual (temp)
                // Si arr[j - k] > temp → significa que el valor anterior está desordenado y debe moverse
                // arr[j - k]: elemento anterior en la secuencia con salto 'k'
                // temp: valor que estamos intentando insertar en su posición correcta
                if (arr[j - k] > temp) {
                    arr[j] = arr[j - k]; // Desplazamos el elemento hacia la derecha para hacer espacio
                } else {
                    break; // Si el orden es correcto, salimos del ciclo
                }
            }

            arr[j] = temp; // Insertamos el valor guardado en la posición correcta

            // Mostrar el arreglo después de cada inserción
            printf("k[%d] = %d: \n", i, k);
            for (int m = 0; m < len; m++) {
                printf("%d ", arr[m]);
            }
            printf("\n");
        }
    }
}

void mergeSort(int arr[], int len) {
    int temp[len];

    for (int p = 1; p < len; p *= 2) {
        for (int i = 0; i < len - p; i += 2 * p) {

            int L = i;
            int q = L + p - 1;
            int R = i + 2 * p - 1;

            if (R >= len) {
                R = len - 1;
            }
            
            // índices descriptivos para el merge
            int idx = L;
            int k = L;
            int mid = q + 1;

            // merge clásico
            while (idx <= q && mid <= R) {
                if (arr[idx] < arr[mid]) {
                    temp[k] = arr[idx];
                    idx++;
                    k++;
                } else {
                    temp[k] = arr[mid];
                    mid++;
                    k++;
                }
            }

            while (idx <= q) {
                temp[k] = arr[idx];
                idx++;
                k++;
            }

            while (mid <= R) {
                temp[k] = arr[mid];
                mid++;
                k++;
            }

            // copiar resultado al arreglo original
            for (int idx = L; idx <= R; idx++) {
                arr[idx] = temp[idx];
            }
        }
    }
}

void radixSort(int arr[], int len) {
    int j, k = 1;             // j: índice para retroceder en inserción
                              // k: base actual (1 = unidades, 10 = decenas, etc.)
    int max = arr[0];         // max: valor máximo del arreglo, usado para saber cuántos dígitos procesar
    int pivote, match, temp;  // pivote: dígito del número actual
                              // match: dígito del número anterior
                              // temp: valor temporal para insertar

    // Encontrar el número máximo del arreglo
    // Declaración: int i = 1 → empezamos desde el segundo elemento
    // Comparación: i < len → recorremos hasta el final
    // Incremento: i++ → avanzamos uno por uno
    for (int i = 1; i < len; i++) {
        if (arr[i] > max)     // Si encontramos un número mayor, actualizamos max
            max = arr[i];
    }
    // Bucle principal: se repite mientras haya dígitos que procesar
    // Condición: k <= max → mientras la base actual sea menor o igual al número más grande
    while (k <= max) {

        // Ordenamiento por inserción basado en el dígito actual
        // Declaración: int i = 1 → empezamos desde el segundo elemento
        // Comparación: i < len → recorremos hasta el final
        // Incremento: i++ → avanzamos uno por uno
        for (int i = 1; i < len; i++) {
            temp = arr[i];                  // Guardamos el valor actual
            pivote = (temp / k) % 10;       // Extraemos el dígito relevante según la base actual

            // Bucle interno: retrocede desde i-1 hasta 0
            // Declaración: j = i - 1 → empezamos justo antes del elemento actual
            // Comparación: j >= 0 → seguimos mientras no salgamos del arreglo por la izquierda
            // Incremento: j-- → retrocedemos uno por uno
            for (j = i - 1; j >= 0; j--) {

                // Comparación entre dígitos: ¿el dígito anterior es mayor que el actual?
                // (arr[j] / k) % 10 → extrae el dígito de arr[j] en la base actual
                // pivote → dígito del número que estamos insertando
                if (((arr[j] / k) % 10) > pivote) {
                    arr[j + 1] = arr[j];    // Si el dígito anterior es mayor, lo desplazamos a la derecha
                } else {
                    break;                  // Si no, ya encontramos la posición correcta
                }
            }
            arr[j + 1] = temp;              // Insertamos el valor en su posición ordenada
        }
        // Mostrar el arreglo después de ordenar por la base actual
        printf(" || Base %d:\n", k);
        for (int i = 0; i < len; i++) {
            printf("%d ", arr[i]);          // Imprime cada elemento del arreglo
        }
        printf("\n");

        k = k * 10;                          // Avanzamos a la siguiente base (unidades → decenas → centenas...)
    }
}

void quicksort(int arr[], int n) {
    int low = 0;           // inicio del arreglo
    int high = n - 1;      // fin del arreglo

    // Mientras todavía quede algo que ordenar
    while (low < high) {
        int i = low;                  // índice que va de izquierda a derecha
        int j = high;                 // índice que va de derecha a izquierda
        int pivot = arr[(low + high) / 2];  // escogemos el pivote al centro

        // Este ciclo acomoda los elementos menores a la izquierda
        // y los mayores a la derecha
        while (i <= j) {
            while (arr[i] < pivot) {
                i++;
            }
            while (arr[j] > pivot) {
                j--;
            }
            if (i <= j) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                i++;
                j--;
            }
        }

        // Ahora ya tenemos dos partes: [low..j] y [i..high]
        // Lo que hacemos es seguir con la parte más grande
        // y luego reducimos a la parte más pequeña sin usar pila

        if ((j - low) < (high - i)) {
            // La parte izquierda es más pequeña
            if (low < j) {
                high = j;   // seguimos ordenando la izquierda
                continue;   // volvemos al inicio del while
            }
            low = i;        // si no, avanzamos con la derecha
        } else {
            // La parte derecha es más pequeña
            if (i < high) {
                low = i;    // seguimos ordenando la derecha
                continue;
            }
            high = j;       // si no, reducimos por la izquierda
        }
    }
}