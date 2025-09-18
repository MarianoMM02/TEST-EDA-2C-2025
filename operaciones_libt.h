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
    libt->ultimo_p = 0;
    libt->ultimo_p = 0;
}

int Localizar_LIBT(LIBT libt, char *codigo, int *pos, float *costo) {
    //l�mites inclusivos y segmento m�s grande a la derecha
    //a costo se le suma 1 por cada comparaci�n de clave en la trisecci�n en el arreglo de punteros

    int li = 0, ls = libt.ultimo_p - 1;
    int tercio, medio1, medio2;
    *costo = 0;

    while (li <= ls) {
        if (ls - li + 1 < 3) { // Si el segmento es muy chico, se usa b�squeda secuencial
            int i = li;
            while (i <= ls && stricmp(libt.punteros[i]->codigo, codigo) < 0) {
                *costo = *costo + 1;
                i++;
            }
            *pos = i;
            if (i <= ls) {
                *costo = *costo + 1;
                return (stricmp(libt.punteros[i]->codigo, codigo) == 0);
            }
            return 0;
        }
        tercio = (ls - li + 1) / 3;
        medio1 = li + tercio;
        medio2 = ls - tercio;

        *costo = *costo + 1; // Primera comparaci�n (medio1)
        if (strcmp(codigo, libt.punteros[medio1]->codigo) >= 0) {
            //el c�digo est� en el primer o seg tercio
            ls = medio2 - 1;
            if (strcmp(codigo, libt.punteros[medio1]->codigo) == 0) {
                *pos = medio1;
                return 1;
            }
        } else { //est� en el tercer tercio
            *costo = *costo + 1; // segunda comp (medio2)
            if (stricmp(codigo, libt.punteros[medio2]->codigo) <= 0) {
                //el c�d est� en el seg tercio
                li = medio1 + 1;
                ls = medio2;
                 if (stricmp(codigo, libt.punteros[medio2]->codigo) == 0) {
                    *pos = medio2;
                    return 1;
                }
            } else { // est� en el tercer tercio
                li = medio2 + 1;
            }

            *pos = li;
            return 0; //no est�
        }
    }
}

int Alta_LIBT(LIBT *libt, Alumno alumno, float *costo) {
    //Agrega el alumno, lo guarda en en arreglo de alumnos y luego inserta el puntero a ese dato en la pos correcta del arr punteros
    //el csoto ser�a el de localizar + 0.5 (0.5 por cada corrimiento de puntero)�?

    int pos;
    *costo = 0;

    if (libt->ultimo_p >= MAX_LIBT) {
        return 2; // Estructura llena.
    }

    if (Localizar_LIBT(*libt, alumno.codigo, &pos, costo) == 1) {
        return 0 //fracaso (dupli)
    } else {
        libt->alumnos[libt->ultimo.d] = alumno;
    }
}

int Evocacion_LIBT(LIBT libt, char *cod, float *costo) {
    //costo del localizar
}

int Baja_LIBT(LIBT *libt, Alumno alumno, float *costo) {
    //Elimina al alumno. Busca el puntero en el arreglo punteros, lo elimina y desplaza los dem�s.
    //El dato en el arreglo no se borrar�a pero s� quedar�a inaccesible
    //costo de localizar m�s 0.5 por cada corrimiento de puntero
}


#endif // OPERACIONES_LIBT_H_INCLUDED
