#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <ctype.h>
#include <time.h>
#include "funciones.h"
#include "interfaz.h"
#include "errores.h"
#define N 100
#define n 20

void validarIngreso(int *opcion){
    system("cls");
    do{
        menu();
        if ( (*opcion < 0) || (*opcion > 8) ) {
            printf("\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\tOpcion invalida. Ingrese un numero valido.\n");
            scanf("%d",opcion);
        }
            system("cls");

    }while( (*opcion < 0) || (*opcion > 8) );
}

//FUNCION QUE VALIDA EL INGRESO DE UN NUMERO
void validarDigito(char opcionChar[],int *opcion) {
    int esNumero = 1;
    do{
        esNumero = 1;
        fflush(stdin);
        gets(opcionChar);
        for (int i = 0; i < strlen(opcionChar); i++) {
            if (!isdigit(opcionChar[i])) {
                esNumero = 0;
                break;
            }
        }


        if (!esNumero) {
            printf("\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\tOpcion invalida. Ingrese un numero.\n");
        } else {
            *opcion = atoi(opcionChar); // CONVERTIR LA CADENA A UN ENTERO
        }

    } while( !esNumero );
}
