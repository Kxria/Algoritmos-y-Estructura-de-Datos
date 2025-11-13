#include <stdio.h>
#include <stdlib.h>

typedef struct _nodo {
    int dato;
    struct _nodo *ant;
    struct _nodo *sig;
} Nodo;

Nodo* crearnodo(int dato) {
    Nodo *nuevo;
    nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->dato = dato;
    nuevo->sig = nuevo->ant = NULL;
    return nuevo;
}

Nodo* insertar(Nodo *inicio, int dato) {
    Nodo *nuevo = crearnodo(dato);

    if (inicio == NULL) { // primer nodo
        nuevo->sig = nuevo;
        nuevo->ant = nuevo;
        return nuevo;
    } else {
        Nodo *ultimo = inicio->ant;
        ultimo->sig = nuevo;
        nuevo->ant = ultimo;
        nuevo->sig = inicio;
        inicio->ant = nuevo;
        return inicio;
    }
}

Nodo* eliminar(Nodo *inicio) {
    Nodo *ultimo = inicio->ant;

    // Si solo hay un nodo
    if (inicio == ultimo) {
        printf("\nSe elimina: %d\n", inicio->dato);
        free(inicio);
        return NULL;
    }

    printf("\nSe elimina: %d\n", ultimo->dato);

    ultimo->ant->sig = inicio;
    inicio->ant = ultimo->ant;
    free(ultimo);

    return inicio;
}

void mostrar(Nodo *inicio) {
    if (inicio == NULL) {
        printf("\nEsta vacia\n");
        return;
    }

    Nodo *aux = inicio;
    do {
        printf("\n%d ", aux->dato);
        aux = aux->sig;
    } while (aux != inicio);
}

int main(void) {
    Nodo *inicio = NULL;
    int dato, op;

    do {
        printf("\n 1. Insertar en la lista");
        printf("\n 2. Eliminar un elemento");
        printf("\n 3. Imprimir la lista");
        printf("\n 4. Salir");
        printf("\n Opcion: [ ]\b\b");
        scanf("%d", &op);

        switch(op) {
            case 1:
                printf("\nDato: ");
                scanf("%d", &dato);
                inicio = insertar(inicio, dato);
                break;
            case 2:
                inicio = eliminar(inicio);
                break;
            case 3:
                mostrar(inicio);
                break;
        }
    } while(op != 4);

    return 0;
}
