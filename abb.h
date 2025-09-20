#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED
#include <malloc.h>

typedef struct Nodo {
    Alumno dato;
    struct Nodo derecha;
    struct Nodo izquierda;
} Nodo;

typedef struct Arbol {
    Nodo *cursor;
    Nodo *raiz;
    Nodo *padre;
} Arbol;

void initABB(Arbol *abb) {
    abb->cursor = NULL;
    abb->padre = NULL;
    abb->raiz = NULL;
}

int LocalizarABB(Arbol *abb, char[] codigo, float *costo) {
    abb->padre = abb->raiz;
    abb->cursor = abb->raiz;

    if(abb->raiz == NULL) {
        abb->padre = abb->cursor;
        (*costo) = 0.0;    //No se encontro el elemento. El arbol esta vacio.
        return 0;
    }

    while(abb->cursor != NULL && stricmp(codigo, abb->cursor->dato.codigo) != 0) {
        (*costo) += 1;
        abb->padre = abb->cursor;

        if(stricmp(codigo, abb->cursor->dato.codigo) < 0) {
            abb->cursor = abb->cursor->izquierda;
        } else {
            abb->cursor = abb->cursor->derecha;
        }
        (*costo) += 1;
    }
    if(abb->cursor != NULL) {
        (*costo) += 1;
        return 1; // Exito
    } else {
        return 0; // Fracaso
    }
}

int AltaABB(Arbol *abb, Alumno alumno, float *costo) {
    float cost = 0.0;
    float costLoc = 0.0;

    Nodo *nodo = (Nodo*)malloc(sizeof(Nodo));

    if(nodo == NULL) {
        return 0; // Fracaso, no hay memoria suficiente
    } else {
        if(LocalizarABB(abb, alumno.codigo, &costLoc) == 1) {
            free(nodo);
            return 2; // Fracaso, el elemento ya existe
        }
        nodo->dato = alumno;
        nodo->izquierda = NULL;
        nodo->derecha = NULL;

        if(abb->raiz == NULL) { // El arbol esta vacio, se hace el alta en la raiz
            abb->raiz = nodo;
        } else {
            (stricmp(nodo->dato.codigo, abb->padre->dato.codigo) < 0) ? (abb->padre->izquierda = nodo) : (abb->padre->derecha = nodo);
        }
        cost += 0.5;
        (*costo) = cost;
        return 1; // Exito
    }
}

int BajaABB(Arbol *abb, Alumno alumno, float *costo) {
    float costoLoc = 0.0;
    float cost = 0.0;
    Nodo *padreAux, *cursorAux;

    if(abb->raiz == NULL){
        return 0;   //El arbol esta vacio, no se puede hacer la baja.
    }

    if(LocalizarABB(abb, alumno.codigo, &costoLoc) == 1){
        int nya = strcmp(alumno.nombape, abb->cursor->dato.nombape);
        int cor = strcmp(alumno.correo, abb->cursor->dato.correo);
        int cond = strcmp(alumno.condfinal, abb->cursor->dato.condfinal);

        if(nya == 0 && cor == 0 && alumno.nota == abb->cursor->dato.nota && cond == 0) {
            // Caso 1: nodo sin hijos
            if(abb->cursor->izquierda == NULL && abb->cursor->derecha == NULL){
                if(abb->cursor == abb->raiz){
                    abb->raiz = NULL;   // Se desea dar de baja un elemento que es raiz, el arbol queda vacio
                }else if(abb->padre->izquierda == abb->cursor){
                    abb->padre->izquierda = NULL;   // Eliminar nodo si es el hijo izquierdo
                } else {
                    abb->padre->derecha = NULL; // Eliminar nodo si es el hijo derecho
                }

                free(abb->cursor);
                cost += 0.5;
                (*costo) = cost;

                return 1;   // Exito

            // Caso 2: nodo con un hijo
            }else if(abb->cursor->izquierda == NULL || abb->cursor->derecha == NULL) {
                Nodo *hijo = (abb->cursor->izquierda != NULL) ? abb->cursor->izquierda : abb->cursor->derecha;
                if(abb->cursor == abb->raiz) {
                    abb->raiz = hijo;   // Si es la raiz, el hijo toma su lugar
                } else if(abb->padre->izquierda == abb->cursor) {
                    abb->padre->izquierda = hijo; // Si era el hijo izquierdo
                } else {
                    abb->padre->derecha = hijo; // Si era el hijo derecho
                }
                free(abb->cursor);
                cost += 0.5;
                (*costo) = cost;
                return 1; // Exito

            // Caso 3: nodo con dos hijos
            } else {
                cursorAux = abb->cursor->izquierda; // Se busca en el subarbol izquierdo
                padreAux = abb->cursor;

                while(cursorAux->derecha != NULL) {
                    padreAux = cursorAux;
                    cursorAux = cursorAux->derecha;
                }
                abb->cursor->dato = cursorAux->dato; // Valor del nodo actual con el del mayor de los menores
                cost += 1;

                if(padreAux->derecha == cursorAux) {
                    padreAux->derecha = cursorAux->izquierda;
                } else {
                    padreAux->izquierda = cursorAux->izquierda;
                }

                free(cursorAux);
                cost += 0.5;
                (*costo) = cost;
                return 1; // Exito
            }
        } else {
            return 3; // Code encontrado, pero distintos valores
        }
    }else{
        return 2; // Fracaso
    }
}

int EvocacionABB(Arbol abb, Alumno *alumno, float *costo) {
    float costoLoc = 0.0;

    if(LocalizarABB(&abb, alumno->codigo, &costoLoc) == 1) {
        strcpy(alumno->codigo, abb.cursor->dato.codigo);
        strcpy(alumno->nombape, abb.cursor->dato.nombape);
        alumno->nota = abb.cursor->dato.nota;
        strcpy(alumno.condfinal, abb.cursor->dato.condfinal);

        (*costo) = costoLoc;

        return 1; // Exito
    } else {
        (*costo) = costoLoc;
        return 0; // Fracaso
    }
}

void BarridoPreorden(Nodo *nodo) {
    int i = 0;
    int continuar;

    if (nodo != NULL) {
        printf("\n---------- Alumno ----------\n");
        printf("Codigo: %s\n", nodo->dato.codigo);
        printf("Nombre y Apellido: %s\n", nodo->dato.nombape);
        printf("Correo: %s\n", nodo->dato.correo);
        printf("Nota: %d\n", nodo->dato.nota);
        printf("Condicion final: %s\n", nodo->dato.condfinal);
        printf("\n");
        i++;

        // Recorrer el subarbol izquierdo
        if(nodo->izquierda != NULL) {
            printf("Hijo izquierdo: %s\n", nodo->izquierda->dato.codigo);
        } else {
            printf("Hijo izquierdo: No tiene.\n");
        }
        // Recorrer el subarbol derecho
        if(nodo->derecha != NULL) {
            printf("Hijo derecho: %s\n", nodo->derecha->dato.codigo);
        } else {
            printf("Hijo derecho: No tiene.\n");
        }

        if(i == 3) {
            i = 0;
            printf("-----------------------------------\n");
            printf("   (1) Continuar    (2) Salir     \n");
            printf("-----------------------------------\n");
            do{
                scanf("%d",&continuar);
                fflush(stdin);
                if(continuar == 2){
                    return;
                }
                system("cls");
            }while(continuar!=1);
        }
        barridoPreorden(nodo->izquierda);
        barridoPreorden(nodo->derecha);
    }
}

void ResetABB(Nodo *nodo){
    if (nodo != NULL){
        if (nodo->izquierda != NULL)
            resetABB(nodo->izquierda);
        if (nodo->derecha != NULL)
            resetABB(nodo->derecha);
    free((void*)nodo);
    }
}

#endif // ABB_H_INCLUDED
