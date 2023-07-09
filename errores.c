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

//FUNCION QUE VALIDA EL INGRESO DE UN NUMERO
void validarIngreso(char opcionChar[],int *opcion){
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
            printf("Opción inválida. Ingrese un número.\n");
        } else {
            *opcion = atoi(opcionChar); // Convertir la cadena a un entero
            // Validar la opción ingresada
            if ( (*opcion < 0) || (*opcion > 8) ) {
                printf("Opción inválida. Ingrese un número válido.\n");
            }
        }

    } while( (*opcion < 0) || (*opcion > 8) || !esNumero );
}
