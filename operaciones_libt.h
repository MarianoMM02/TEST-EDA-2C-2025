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
    //l�mites inclusivos y segmento m�s grande a la derecha
    //a costo se le suma 1 por cada comparaci�n de clave en la trisecci�n en el arreglo de punteros

    int li = 0, ls = libt.ultimo_p - 1;
    *costo = 0;

    while (li <= ls) {
        int tercio = (ls - li + 1) / 3;
        int medio1 = li + tercio;
        int medio2 = ls - tercio;

        *costo = *costo + 1; //primera comparación (medio1)
        int comp1 = stricmp(codigo, libt.punteros[medio1]->codigo);

        if (comp1 < 0) { // El código está en el primer tercio.
            ls = medio1 - 1;
        } else if (comp1 == 0) { // Encontrado en medio1.
            *pos = medio1;
            return 1;
        } else { //el código es mayor que el de medio1.
            *costo = *costo + 1; // segunda comparación (medio2)
            int comp2 = stricmp(codigo, libt.punteros[medio2]->codigo);

            if (comp2 < 0) { // el cód está en el segundo tercio.
                li = medio1 + 1;
                ls = medio2 - 1;
            } else if (comp2 == 0) { //encontrado en medio2.
                *pos = medio2;
                return 1;
            } else { //cóf está en el tercer tercio.
                li = medio2 + 1;
            }
        }
    }

    *pos = li; // posición de inserción si no se encontró.
    return 0;
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
            libt->punteros[pos]->nota == alumno.nota) {

            //Eliminación del puntero y corrimiento
            int i;
            for (i = pos; i < libt->ultimo_p - 1; i++) {
                libt->punteros[i] = libt->punteros[i + 1];
                *costo = *costo + 0.5; // Cada corrimiento de puntero suma 0.5 al costo.
            }

            libt->ultimo_p--; // Se reduce el contador de punteros.
            return 1; // Éxito
        }
    }
    return 0; //fracado 
}


#endif // OPERACIONES_LIBT_H_INCLUDED
