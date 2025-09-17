#ifndef OPERACIONES_H_INCLUDED
#define OPERACIONES_H_INCLUDED
#include <string.h>
#define MAX 130

typedef struct {
    char codigo[8];
    char nombape[80];
    char correo[23];
    int nota;
    char condfinal[20];
} Alumno;

typedef struct {
    Alumno alumnos[MAX];
    int ultimo;
} LSO;

void init_LSO(LSO *lista) {
    (*lista).ultimo = 0;    // "ultimo" elemento en la posicion 0 (la estructura esta vacia)
}

int Localizar_LSO(LSO lista, char *codigo, int *pos, float *costo) {
    int i = 0;

    while(i < lista.ultimo && stricmp(lista.alumnos[i].codigo, codigo) < 0) {
        *costo = *costo + 1; // Se incrementa el costo por cada celda consultada.
        i++;
    }
    *pos = i;
    if (i < lista.ultimo) {
        *costo = *costo + 1; // La comparación final también suma al costo.
        if (stricmp(lista.alumnos[i].codigo, codigo) == 0) {
            return 1; // éxito
        } else {
            return 0; // Fracaso
        }
    } else {
        return 0; // fracaso
    }
}

int Alta_LSO(LSO *lista, Alumno alumno, float *costo) {
    int pos;
    *costo = 0;

    if(ult >= MAX) {
        return 2; // La estructura no tiene espacio
    }

    if(Localizar_LSO(*lista, alumno.codigo, &pos, costo) == 1) {    // El elemento ya existe en la estructura
            return 0; // Fracaso
    } else { // El elemento no existe en la estructura
        int ult = lista->ultimo;
        while(pos < ult) {
            lista->alumnos[ult] = lista->alumnos[ult - 1]; // Se desplaza la estructura
            *costo = *costo + 1;
            ult = ult - 1;
        }
    }
    lista->alumnos[pos] = alumno; // Ingresa nuevo elemento en pos
    lista->ultimo = lista->ultimo + 1;

    return 1; // Exito
}

int Evocacion_LSO(LSO lista, char *cod, float *costo) {
    int pos;
    *costo = 0;

    if(Localizar_LSO(lista, cod, &pos, costo) == 0) {
        return 0; // Fracaso, el elemento no existe
    } else {
        (*alumno) = lista.alumnos[pos];
        return 1; // Exito
    }
}

int Baja_LSO(LSO *lista, Alumno alumno, float *costo) {
    int pos;
    *costo = 0;

    if(Localizar_LSO(*lista, alumno.codigo, &pos, costo) == 0) {
        return 0; // Fracaso, el elemento no existe
    } else {
        Alumno en_lista = lista->alumnos[pos];
        if (strcmp(en_lista.nombape, alumno.nombape) == 0 &&
            strcmp(en_lista.correo, alumno.correo) == 0 &&
            en_lista.nota == alumno.nota) {

            // confirmación exitosa. todo s datos coinciden, procedemos a eliminar
            int i;
            for (i = pos; i < lista->ultimo - 1; i++) {
                lista->alumnos[i] = lista->alumnos[i + 1];
                *costo = *costo + 1;
            }
            lista->ultimo--;
            return 1;
        }
    }
}

#endif // OPERACIONES_H_INCLUDED
