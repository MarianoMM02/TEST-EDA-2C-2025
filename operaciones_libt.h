#ifndef OPERACIONES_LIBT_H_INCLUDED
#define OPERACIONES_LIBT_H_INCLUDED
#define MAX 130

typedef struct {
    char codigo[8];
    char nombape[80];
    char correo[23];
    int nota;
    char condfinal[20];
} Alumno;

typedef struct {
    Alumno alumnos[MAX]; //arr de datos
    Alumno punteros[MAX]; //arr de punteros a los datos. Este se mantiene ordenado
    int ultimo_d;
    int ultimo_p;
} LIBT;

void init_LIBT(LIBT *libt) {
    libt->ultimo_d = 0;
    libt->ultimo_p = 0;
}

int Localizar_LIBT(LIBT libt, char *codigo, int *pos, float *costo) {
    int li = 0, ls = libt.ultimo_p - 1;
    *costo = 0;

    while (li <= ls) {
        int medio = (li + ls + 1) / 2; // segmento más grande a la izquierda
        (*costo)++;
        int comp = strcmp(libt.punteros[medio]->codigo, codigo);

        if (comp == 0) {
            *pos = medio;
            return 1; // Encontrado
        } else if (comp < 0) {
            li = medio + 1;
        } else {
            ls = medio - 1;
        }
    }
    *pos = li; // Posición donde debería insertarse
    return 0; // No encontrado
}

int Alta_LIBT(LIBT *libt, Alumno alumno, float *costo) {
    //Agrega el alumno, lo guarda en en arreglo de alumnos y luego inserta el puntero a ese dato en la pos correcta del arr punteros
    //el csoto ser�a el de localizar + 0.5 (0.5 por cada corrimiento de puntero)�?
    int pos;
    *costo = 0;

    if (libt->ultimo_p >= MAX) {
        return 2; // Estructura llena.
    }

    if (Localizar_LIBT(*libt, alumno.codigo, &pos, costo) == 1) {
        return 0; // Fracaso por duplicado.
    } else {
        //Se guarda al final, sin orden específico.
        libt->alumnos[libt->ultimo_d] = alumno;

        //Corrimiento de punteros para hacer espacio
        int i;
        for (i = libt->ultimo_p; i > pos; i--) {
            libt->punteros[i] = libt->punteros[i - 1];
            *costo = *costo + 0.5;
        }

        //Inserción del nuevo puntero en la posición correcta para mantener el orden
        libt->punteros[pos] = &libt->alumnos[libt->ultimo_d];
        libt->ultimo_d++;
        libt->ultimo_p++;

        return 1; // Éxito.
    }
}

int Evocacion_LIBT(LIBT libt, char *cod, float *costo) {
    //costo del localizar
    int pos;
    *costo = 0;

    return Localizar_LIBT(libt, cod, &pos, costo);
}

int Baja_LIBT(LIBT *libt, Alumno alumno, float *costo) {
    //Elimina al alumno. Busca el puntero en el arreglo punteros, lo elimina y desplaza los dem�s.
    //El dato en el arreglo no se borrar�a pero s� quedar�a inaccesible
    //costo de localizar m�s 0.5 por cada corrimiento de puntero
    int pos;
    *costo = 0;

    if (Localizar_LIBT(*libt, alumno.codigo, &pos, costo) == 1) {

        //se comparan los datos del alumno apuntado con los datos recibi
        if (strcmp(libt->punteros[pos]->nombape, alumno.nombape) == 0 &&
            strcmp(libt->punteros[pos]->correo, alumno.correo) == 0 &&
            libt->punteros[pos]->nota == alumno.nota &&
            strcmp(libt->punteros[pos]->condfinal, alumno.condfinal) == 0) {

            //Eliminación del puntero y corrimiento
            int i;
            for (i = pos; i < libt->ultimo_p - 1; i++) {
                libt->punteros[i] = libt->punteros[i + 1];
                *costo = *costo + 0.5; // Cada corrimiento de puntero suma 0.5 al costo.
            }

            libt->ultimo_p--; // Se reduce el contador de puntero   s.
            return 1; // Éxito
        }
    }
    return 0; //fracado
}


#endif // OPERACIONES_LIBT_H_INCLUDED
