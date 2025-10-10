#include <stdlib.h>
#include <stdio.h>

struct Nodo {
    int dato;
    struct Nodo *ant;   
};

int vacia(struct Nodo *tope)
{
    return (!tope)? 1:0;
}

struct Nodo* crearNodo(int n)
{
    //PASO 1: Creamos el nuevo nodo
    struct Nodo *nuevo_nodo;
    nuevo_nodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    
    //PASO 2: Asignar el dato al nuevo nodo
    nuevo_nodo ->dato = n;
    nuevo_nodo ->ant = NULL;
    return(nuevo_nodo);
}

struct Nodo* push(struct Nodo *tope, int n)
{
    struct Nodo *aux;
    aux = crearNodo(n);
    aux->ant = tope;
    tope = aux;
    return(tope);
}

void mostrar(struct Nodo *tope)
{
    struct Nodo *aux;
    if(!tope)
        printf("La pila esta vacia");
    else
    {
        aux = tope;
        do{
            printf("%d ", aux->dato);
            aux = aux->ant;
        }while(aux != NULL);
    }
}

struct Nodo* pop(struct Nodo *tope)
{
    struct Nodo *aux;
    int dato;
    aux = tope;
    tope = tope->ant;
    free(aux);
    return(tope);
}

void main()
{
    struct Nodo *tope = NULL;
    int dato, op;
    do{
        printf("\nPROGRAMA QUE IMPLEMENTA PILAS CON LISTAS ENLAZADAS\n\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Mostrar\n");
        printf("4. Salir\n");
        printf("Opcion: ");
        scanf("%d", &op);
        switch(op)
        {
            case 1: 
                printf("Introduce un numero: ");
                scanf("%d", &dato);
                if(tope == NULL)
                    tope = crearNodo(dato);
                else
                    tope = push(tope,dato);
                break;
                
            case 2: 
                if(!vacia(tope))
                {
                    printf("El dato eliminado es: %d\n", tope->dato);
                    tope = pop(tope);
                    printf("El nuevo dato en la cima es: %d\n", tope->dato);
                }
                else
                    printf("Pila vacia\n");
                break;
                
            case 3: if(!vacia(tope))
                mostrar(tope);
                else printf("Pila vacia\n");
                break;
            case 4: break;
        }
    }while(op != 4);
}