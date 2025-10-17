#include <stdlib.h>
#include <stdio.h>

typedef struct _nodo {
    int dato;
    struct _nodo *ant;
} Nodo;

int vacia(Nodo *tope) {
    return (tope == NULL);
}

Nodo* crearNodo(int n) {
    Nodo *nuevo_nodo = (Nodo*)malloc(sizeof(Nodo));
    nuevo_nodo->dato = n;
    nuevo_nodo->ant = NULL;
    return nuevo_nodo;
}

Nodo* push(Nodo *tope, int n) {
    Nodo *aux = crearNodo(n);
    aux->ant = tope;
    return aux;
}

void mostrar(Nodo *tope) {
    if (vacia(tope)) {
        printf("La pila esta vacia\n");
        return;
    }
    Nodo *aux = tope;
    while (aux != NULL) {
        printf("%d ", aux->dato);
        aux = aux->ant;
    }
    printf("\n");
}

Nodo* pop(Nodo *tope) {
    Nodo *aux = tope;
    tope = tope->ant;
    free(aux);
    return tope;
}

int main(void) {
    Nodo *tope = NULL;
    int dato, op;

    do {
        printf("\nPROGRAMA QUE IMPLEMENTA PILAS CON LISTAS ENLAZADAS\n\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Mostrar\n");
        printf("4. Salir\n");
        printf("Opcion: ");
        scanf("%d", &op);

        switch(op) {
            case 1:
                printf("Introduce un numero: ");
                scanf("%d", &dato);
                tope = push(tope, dato);
                break;

            case 2:
                if (!vacia(tope)) {
                    printf("El dato eliminado es: %d\n", tope->dato);
                    tope = pop(tope);
                    if (tope != NULL)
                        printf("El nuevo dato en la cima es: %d\n", tope->dato);
                    else
                        printf("La pila ahora esta vacia\n");
                } else {
                    printf("Pila vacia\n");
                }
                break;

            case 3:
                mostrar(tope);
                break;

            case 4:
                printf("Saliendo del programa...\n");
                break;

            default:
                printf("Opcion invalida\n");
        }
    } while(op != 4);

    return 0;
}