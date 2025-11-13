#include<stdio.h>
#include<stdlib.h>

typedef struct Nodo{
    int dato;
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
    if(!raiz) { // si la raíz es NULL
        return crearNodo(dato); // crear y devolver el nuevo nodo como raíz
    }
    
    Nodo* nodo = raiz; // puntero para recorrer el árbol desde la raíz
    Nodo* aux = NULL; // puntero al padre del nodo donde se insertará
    
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
    nuevo->padre = aux; // enlazar su padre
    
    if(dato < aux->dato) { // si debe ir como hijo izquierdo
        aux->izq = nuevo; // asignar como hijo izquierdo
    } else {
        aux->der = nuevo; // asignar como hijo derecho
    }
    
    return raiz; // devolver la raíz
}

Nodo* eliminar(Nodo *raiz, int dato) {
    Nodo* eliminar = raiz; // puntero para buscar el nodo a eliminar
    
    while(eliminar != NULL && eliminar->dato != dato) { // buscar el nodo
        if(dato < eliminar->dato) { // si debe buscar a la izquierda
            eliminar = eliminar->izq; // mover a hijo izquierdo
        } else {
            eliminar = eliminar->der; // mover a hijo derecho
        }
    }

    if(eliminar == NULL) { // si no se encontró el dato
        printf("Dato inexistente\n"); // informar que no existe
        return raiz; // devolver raíz sin cambios
    }

    if(eliminar->izq != NULL && eliminar->der != NULL) { // si tiene dos hijos
        Nodo* sucesor = eliminar->der; // buscar el sucesor en el subárbol derecho
        while (sucesor->izq != NULL) { // ir al nodo más a la izquierda del subárbol derecho
            sucesor = sucesor->izq; // avanzar al hijo izquierdo
        }
        eliminar->dato = sucesor->dato; // copiar el valor del sucesor al nodo a eliminar
        eliminar = sucesor; // en realidad eliminaremos el sucesor (que tiene <=1 hijos)
    }
    
    Nodo* hijo = NULL; // puntero al hijo que reemplazará al nodo eliminado
    if(eliminar->izq != NULL) { // si tiene hijo izquierdo
        hijo = eliminar->izq; // hijo será el izquierdo
    } else {
        if (eliminar->der != NULL) { // si tiene hijo derecho
            hijo = eliminar->der; // hijo será el derecho
        }
    }

    if(hijo != NULL) { // si hay un hijo que reemplaza
        hijo->padre = eliminar->padre; // actualizar su puntero a padre
    }

    if(eliminar->padre == NULL) { // si el nodo a eliminar es la raíz
        raiz = hijo; // la nueva raíz es el hijo (puede ser NULL)
    } else {
        if(eliminar == eliminar->padre->izq) { // si era hijo izquierdo
            eliminar->padre->izq = hijo; // enlazar el hijo al padre
        } else {
            eliminar->padre->der = hijo; // enlazar el hijo al padre (derecho)
        }
    }

    free(eliminar); // liberar la memoria del nodo eliminado
    return raiz; // devolver la raíz del árbol actualizado
}

void imprimirPreorden(Nodo* nodo) {
    if (nodo == NULL) { // caso base: nodo nulo
        return; // no hacer nada
    }

    printf("%d ", nodo->dato); // visitar el nodo (raíz)
    imprimirPreorden(nodo->izq); // recorrer subárbol izquierdo
    imprimirPreorden(nodo->der); // recorrer subárbol derecho
}

void imprimirPreorden2(Nodo* raiz) {
    Nodo* aux = raiz; // puntero auxiliar para recorrer

    while(aux != NULL) { // mientras haya nodos
        printf("%d ", aux->dato); // imprimir el dato actual
        
        if(aux->izq != NULL) { // si hay hijo izquierdo
            aux = aux->izq; // bajar a la izquierda
        } else if(aux->der != NULL) { // si hay hijo derecho pero no izquierdo
            aux = aux->der; // bajar a la derecha
        } else { // si es hoja, subir hasta encontrar un nodo con hijo derecho no visitado
            while (aux->padre != NULL && (aux == aux->padre->der || !aux->padre->der)) { // subir mientras venga desde derecha o padre no tenga derecha
                aux = aux->padre; // subir al padre
            }
            
            if(aux->padre == NULL) { // si llegamos a la raíz sin encontrar derecha
                break; // terminar el recorrido
            }
            aux = aux->padre->der; // mover al subárbol derecho del padre
        }
    }
}

void imprimirInorden(Nodo* nodo) { // recorrido inorden recursivo
    if(nodo == NULL)  // caso base
        return; // no hacer nada

    imprimirInorden(nodo->izq); // recorrer izquierda
    printf("%d ", nodo->dato); // visitar nodo
    imprimirInorden(nodo->der); // recorrer derecha
}

void imprimirInorden2(Nodo* raiz) { // inorden iterativo (Morris traversal)
    Nodo* aux = raiz; // puntero auxiliar

    while(aux != NULL) { // mientras queden nodos
        if(aux->izq == NULL) { // si no hay hijo izquierdo
            printf("%d ", aux->dato); // visitar nodo
            aux = aux->der; // mover a la derecha
        } else {
            Nodo* aux2 = aux->izq; // encontrar predecesor

            while(aux2->der != NULL && aux2->der != aux) { // buscar el extremo derecho del subárbol izquierdo
                aux2 = aux2->der; // avanzar a la derecha
            }
            
            if(aux2->der == NULL) { // si enlace temporal no existe
                aux2->der = aux; // crear enlace temporal al nodo actual
                aux = aux->izq; // mover al subárbol izquierdo
            } else {
                aux2->der = NULL; // quitar el enlace temporal
                printf("%d ", aux->dato); // visitar el nodo
                aux = aux->der; // mover a la derecha
            }
        }
    }
}

void imprimirPostorden(Nodo* nodo) { // recorrido postorden recursivo
    if(nodo == NULL)  // caso base
        return; // no hacer nada

    imprimirPostorden(nodo->izq); // recorrer izquierda
    imprimirPostorden(nodo->der); // recorrer derecha
    printf("%d ", nodo->dato); // visitar nodo
}

void imprimirPostorden2(Nodo* raiz) { // postorden iterativo usando padres y auxiliar
    Nodo* aux = raiz; // puntero de recorrido
    Nodo* aux2 = NULL; // puntero al último nodo procesado
    
    while(aux) { // mientras haya nodos
        if(aux2 == aux->padre && (aux->izq || aux->der)) { // si venimos desde el padre y hay hijos
            aux2 = aux; // actualizar último procesado
            
            if(aux->izq)         // preferir ir a la izquierda
                aux = aux->izq;  // bajar a izquierda
            else
                aux = aux->der;  // bajar a derecha
            
        } else if(aux->izq == aux2 && aux->der) { // si venimos desde la izquierda y hay derecha
            aux2 = aux; // actualizar último procesado
            aux = aux->der; // explorar derecha
        } else { // si no hay hijos por explorar
            printf("%d ", aux->dato); // procesar nodo
            aux2 = aux; // marcar como último procesado
            aux = aux->padre; // subir al padre
        }
    }
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
                printf("Mostrar preorden\n");
                imprimirPreorden(raiz);
                printf("\n\n\n");

                printf("Mostrar preorden2\n");
                imprimirPreorden2(raiz);
                printf("\n\n\n");

                printf("Mostrar inorden\n");
                imprimirInorden(raiz);
                printf("\n\n\n");

                printf("Mostrar inorden2\n");
                imprimirInorden2(raiz);
                printf("\n\n\n");

                printf("Mostrar postorden\n");
                imprimirPostorden(raiz);
                printf("\n\n\n");

                printf("Mostrar postorden2\n");
                imprimirPostorden2(raiz);
                printf("\n\n");
                break;

            default:
                break;
        }
    } while(opcion != 0);
    
    return 0;
}