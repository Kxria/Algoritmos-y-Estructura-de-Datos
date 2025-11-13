#include <stdio.h>
#include <stdlib.h>

typedef struct _nodo {
    int dato;
    struct _nodo *ant;
    struct _nodo *sig;
}Nodo;

Nodo* crearnodo(int dato) {
    Nodo *nuevo;
    nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->dato = dato;
    nuevo->sig = NULL;
    nuevo->ant = NULL;
    
    return nuevo;
}

void insertar(Nodo *inicio , int dato) {
    Nodo *aux, *nuevo;
    aux = inicio;
    nuevo = crearnodo(dato);
    
    while(aux->sig != NULL) {
        aux = aux->sig;
    }
    
    aux->sig = nuevo;
    nuevo->ant = aux;
}

void mostrar(Nodo *inicio) {
    Nodo *aux;
    if(!inicio)
        printf("\nEsta vacia\n");
    else {
        aux = inicio;
        
        do {
            printf("\n%d",aux->dato);
            aux = aux->sig;
        } while(aux != NULL);
    }
}

Nodo* eliminar(Nodo *inicio) {
    Nodo *aux = inicio;

    // Buscar el último nodo
    while (aux->sig != NULL) {
        aux = aux->sig;
    }

    printf("\nSe elimina: %d\n", aux->dato);

    // Caso 1: solo hay un nodo
    if (aux->ant == NULL) {
        free(aux);
        return NULL; // la lista queda vacía
    }

    // Caso 2: hay más de un nodo
    aux->ant->sig = NULL; // desconectar el ultimo nodo
    free(aux);

    return inicio;
}

// nodo* eliminar2(nodo *inicio) {
//     nodo *aux;
//     aux = inicio;
    
//     while (aux->sig != NULL) {
//         aux = aux->sig;
//     }

//     printf("\nSe elimina: %d\n", aux->dato);

//     // Si el nodo a eliminar no es el primero
//     if (aux->ant != NULL) {
//         aux->ant->sig = NULL;
//         free(aux);
//         return inicio; // el inicio no cambia
//     } else {
//         free(aux);
//         return NULL; // la lista queda vacía
//     }
// }

int main(void) {
    Nodo *inicio = NULL;
    int dato, op;
    do {
        printf("\n 1. Insertar en la lista");
        printf("\n 2. Eliminar un elemento ");
        printf("\n 3. Imprimir la lista");
        printf("\n 4. Salir");
        printf("\n Opcion: [ ]\b\b");
        scanf("%d", &op);
        
        switch(op) {
            case 1: 
                printf("\nDato: ");
                scanf("%d", &dato);
                if(inicio == NULL)
                    inicio = crearnodo(dato);
                else
                    insertar(inicio, dato);
                break;
            case 2: 
                if (inicio == NULL)
                    printf("\nEsta vacia\n");
                else
                    inicio = eliminar(inicio);
                break;
            case 3: 
                mostrar(inicio);
                break;
        }
    } while(op != 4);
    
    return 0;
}