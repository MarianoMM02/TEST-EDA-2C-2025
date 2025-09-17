#include <stdio.h>
#include <stdlib.h>
#include "operaciones.h"

/*
-----GRUPO 12------
 Gialluca Trinidad
 Mariano Meza
-------------------
*/

void Precarga(LSO *lista, int *cant);
void MostrarEstructura(LSO lista, int cant);

int main()
{
    LSO lista;
    Alumno alum;
    int opcion, cant = 0;

    init_LSO(&lista);

    //test
    Precarga(&lista, &cant);
    //----
    do {
        system("cls");
        printf("-----------------------------------\n");
        printf("        BIENVENIDO AL MENU\n");
        printf("-----------------------------------\n");
        printf("(1) Comparar Estructuras.\n");
        printf("(2) Mostrar LSO.\n");
        printf("(3) Mostrar LIBT.\n");
        printf("(4) Mostrar ABB.\n");
        printf("(5) Salir.\n");
        printf("-----------------------------------\n");
        printf("-----------------------------------\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        if(opcion < 1 || opcion > 5){
            printf("\nOpcion no valida. Por favor, ingrese un numero entre 1 y 7.\n");
            system("pause");
            continue;
        }

        switch(opcion) {
        case 1:
            //Comparar Estructuras
            break;
        case 2:
            //test
            MostrarEstructura(lista, cant);
            //----
            break;
        case 3:
            //Mostrar LSO
            break;
        case 4:
            //Mostrar ABB
            break;
    } while(opcion != 5);
    system("cls");
    printf("Cerrando programa...\n");
}

void Precarga(LSO *lista, int *cant) {
    Alumno alum;
    int val_alta, not;
    char cod[8], nya[80], cor[80], cfin[80];
    FILE *fp;

    fp = fopen("Alumnos.txt", "r");

    if(fp == NULL) {
        printf("No se pudo realizar la memorizacion previa, el archivo no se pudo abrir o esta vacio.\n");
        return;
    }

    while(!feof(fp)) {
        fscanf(fp, "%[^\n]\n", cod);
        strcpy(alum.codigo, cod);

        fscanf(fp, "%[^\n]\n", nya);
        strcpy(alum.nombape, nya);

        fscanf(fp, "%[^\n]\n", cor);
        strcpy(alum.correo, cor);

        fscanf(fp, "%d\n", &not);
        alum.nota = not;

        fscanf(fp, "%[^\n]\n", cfin);
        strcpy(alum.condfinal, cfin);

        val_alta = Alta(lista, alum);

        if(val_alta == 1) {
            (*cant) = (*cant) + 1;
        } else if (val_alta == 2) { // La lista esta llena
            system("cls");
            printf("La lista esta llena.");
            system("pause");
            break;
        }
    }
    system("cls");
    printf("Cantidad de elementos cargados: %d\n\n", *cant);
    system("pause");
    fclose(fp);     //Se realizo la precarga con exito
}

void MostrarEstructura(LSO lista, int cant) {
    int i, contador = 0, continuar;

    system("cls");

    if(cant == 0) { // La lista esta vacia
        system("cls");
        printf("No se pueden mostrar datos. La lista esta vacia.\n\n");
        system("pause");
    } else {    // Mostrar elementos en bloques de 3
        for(i = 0; i < lista.ultimo; i++) {
            printf("----------Alumno %d----------\n",i+1);
            printf("Codigo: %s \n"
                "Nombre y Apellido: %s \n"
                "Correo: %s \n"
                "Nota: %d \n"
                "Condicion final: %s \n", lista.alumnos[i].codigo, lista.alumnos[i].nombape, lista.alumnos[i].correo, lista.alumnos[i].nota, lista.alumnos[i].condfinal);
            contador++;

            if (contador == 3 || i == lista.ultimo - 1) {
                contador = 0;
                printf("\n-----------------------------------\n");
                printf("   (1) Continuar    (2) Salir     \n");
                printf("-----------------------------------\n");

                do {
                    scanf("%d", &continuar);
                    fflush(stdin);
                    if(continuar == 2){
                        return;
                    }
                    system("cls");
                } while(continuar != 1);
            }
        }
    }
}
