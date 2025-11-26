#include<stdio.h>
#include<stdlib.h>

typedef struct Nodo {
    int dato; // dato del nodo
    struct Nodo *izq; // puntero al hijo izquierdo
    struct Nodo *der; // puntero al hijo derecho
    struct Nodo *padre; // puntero al padre del nodo
} Nodo;

Nodo* crearNodo(int dato) {
    Nodo* aux; // puntero auxiliar para el nuevo nodo
    aux = malloc(sizeof(Nodo)); // reservar memoria para el nodo
    
    aux->dato = dato; // asignar el valor al campo dato
    aux->izq = NULL; // inicializar hijo izquierdo a NULL
    aux->der = NULL; // inicializar hijo derecho a NULL
    aux->padre = NULL; // inicializar padre a NULL
    
    return aux; // devolver el nodo creado
}

Nodo* insertarDato(Nodo* raiz, int dato) {
    if(!raiz) { // si es el primer dato insertado
        return crearNodo(dato); // crear y devolver el nuevo nodo como raíz
    }
    
    Nodo* nodo = raiz; // puntero para recorrer el árbol desde la raíz
    Nodo* aux = NULL; // puntero al padre
    
    while(nodo != NULL) { // recorrer hasta encontrar posición NULL
        aux = nodo; // guardar el padre actual
        
        if(dato < nodo->dato) { // si dato es menor que el nodo actual
            nodo = nodo->izq; // ir al subárbol izquierdo
        } else if(dato > nodo->dato) { // si dato es mayor
            nodo = nodo->der; // ir al subárbol derecho
        } else if(dato == nodo->dato) { // si dato ya existe
            printf("Dato existente.\n"); // notificar dato duplicado
            return raiz; // no insertar y devolver raíz original
        }
    }
    
    Nodo* nuevo = crearNodo(dato); // crear el nuevo nodo
    nuevo->padre = aux; // se apunta su padre
    
    // se identifica si sera hijo derecho o izquierdo
    if(dato < aux->dato) {
        aux->izq = nuevo; // asignar como hijo izquierdo
    } else {
        aux->der = nuevo; // asignar como hijo derecho
    }
    
    return raiz;
}

Nodo* eliminar(Nodo *raiz, int dato) {
    Nodo* eliminar = raiz; // puntero auxiliar
    
    // buscar nodo
    while(eliminar != NULL && eliminar->dato != dato) {
        if(dato < eliminar->dato) { // si el dato es menor al nodo actual
            eliminar = eliminar->izq; // irse a la izquierda
        } else {
            eliminar = eliminar->der; // irse a la derecha
        }
    }

    // si el dato a eliminar no existe
    if(eliminar == NULL) {
        printf("Dato inexistente\n");
        return raiz;
    }

    // CASO: NODO CON DOS HIJOS
    if(eliminar->izq != NULL && eliminar->der != NULL) { // si el nodo a eliminar tiene dos hijos
        Nodo* predecesor = eliminar->izq; // dirigirse al subarbol izquierdo
        while (predecesor->der != NULL) { // buscar nodo mas derecho del arbol izquierdo
            predecesor = predecesor->der; // obtener precedecesor
        }
        eliminar->dato = predecesor->dato; // cambiar dato de la raiz por el precedesor
        eliminar = predecesor; // actualizar para eliminar el predecesor
    }
    
    // se verifica si tiene hijos
    Nodo* hijo = NULL;
    if(eliminar->izq != NULL) { // si tiene hijo izquierdo
        hijo = eliminar->izq; // su hijo es el nodo izquierdo
    } else if(eliminar->der != NULL) { // si tiene hijo derecho
        hijo = eliminar->der; // su hijo es el nodo derecho
    }

    // si el nodo tuvo un hijo
    if(hijo != NULL) {
        hijo->padre = eliminar->padre; // conectar el hijo con el nuevo padre
    }
    
    // eliminacion del nodo
    if(eliminar->padre == NULL) { // si el padre fue NULL, significa que era la raiz
        raiz = hijo; // si el nodo era la raiz, su hijo se convierte en la raiz
    } else { // si no, se elimina la hoja en base a su padre 
        if(eliminar == eliminar->padre->izq) { // encontramos el nodo a eliminar
            eliminar->padre->izq = hijo; // se elimina el hijo izquierdo
        } else {
            eliminar->padre->der = hijo; // se elimina el hijo derecho
        }
    }

    free(eliminar); // se elimina el nodo
    return raiz;
}

void imprimirInorden(Nodo* nodo) {
    if(nodo == NULL) // caso base
        return;

    imprimirInorden(nodo->izq); // recorrer izquierda
    printf("%d ", nodo->dato);
    imprimirInorden(nodo->der); // recorrer derecha
}

int main(void) {
    Nodo* raiz = NULL;
    int dato, opcion;
    
    do {
        printf("1) Insertar\n");
        printf("2) Eliminar\n");
        printf("3) Mostrar\n");
        printf("0) Salir\n");
        printf("Ingrese la opcion a elegir: ");
        scanf("%d", &opcion);
        
        switch(opcion) {
            case 1:
                printf("Ingrese el dato: ");
                scanf("%d",&dato);
                raiz = insertarDato(raiz, dato);
                printf("\n");
                break;
            
            case 2:
                printf("Ingrese el dato a eliminar: ");
                scanf("%d", &dato);
                raiz = eliminar(raiz, dato);
                printf("\n");
                break;

            case 3:
                printf("Mostrar inorden\n");
                imprimirInorden(raiz);
                printf("\n\n");
                break;

            default:
                break;
        }
    } while(opcion != 0);
    
    return 0;
}