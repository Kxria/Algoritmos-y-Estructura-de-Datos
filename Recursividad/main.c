#include <stdio.h>

int* repetidos(int arreglo[], int *len, int indice);
void invertirCadena(char cadena[], int inicio, int fin);

int main(void) {
    // 🔁 Prueba de repetidos
    int arreglo[] = {4, 7, 4, 2, 9, 2, 7, 5};
    int len = 8; // Longitud fija

    printf("Arreglo original:\n");
    for(int i = 0; i < len; i++) {
        printf("%d ", arreglo[i]);
    }
    printf("\n");

    repetidos(arreglo, &len, 0);

    printf("Arreglo sin repetidos:\n");
    for(int i = 0; i < len; i++) {
        printf("%d ", arreglo[i]);
    }
    printf("\n");

    // 🔄 Prueba de invertirCadena
    char cadena[] = "Recursivo";
    int inicio = 0;
    int fin = 8; // Longitud fija de "Recursivo"

    printf("Cadena original: %s\n", cadena);

    invertirCadena(cadena, inicio, fin);

    printf("Cadena invertida: %s\n", cadena);

    return 0;
}


int* repetidos(int arreglo[], int *len, int indice) {
    // CASO BASE
    // Si el índice actual es mayor o igual a la longitud, termina la recursión y retorna el arreglo.
    if(indice >= *len) {
        return arreglo; 
    }

    // CASO ITERATIVO
    // Recorre los elementos siguientes al índice actual para buscar duplicados.
    for(int i = indice + 1 ; i < *len ; i++) {
        // Si encuentra un elemento igual al actual, procede a eliminarlo.
        if(arreglo[indice] == arreglo[i]) {
            // Desplaza los elementos a la izquierda para sobrescribir el duplicado.
            for(int j = i ; j < *len - 1 ; j++) {
                arreglo[j] = arreglo[j + 1];
            }

            // Disminuye la longitud del arreglo porque se eliminó un elemento.
            (*len)--;
            // Decrementa 'i' para revisar la nueva posición después del desplazamiento.
            i--;
        }
    }

    // Llama recursivamente para procesar el siguiente índice.
    return repetidos(arreglo, len, indice + 1);
}

void invertirCadena(char cadena[], int inicio, int fin) {
    char temp;

    // CASO BASE:
    // Si el índice de inicio es mayor o igual al índice de fin, la recursión termina.
    if(inicio >= fin) {
        return;
    }

    // CASO ITERATIVO:
    // Intercambia el carácter en la posición 'inicio' con el de la posición 'fin'.
    temp = cadena[inicio];
    cadena[inicio] = cadena[fin];
    cadena[fin] = temp;

    // Llama recursivamente para invertir los caracteres internos.
    invertirCadena(cadena, inicio + 1, fin - 1);
}