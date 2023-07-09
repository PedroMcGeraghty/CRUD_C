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
#include <stdbool.h>

//FUNCION QUE PRINTEA EL MENU DE OPCIONES
void menu() {

        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\tBienvenido al menu Principal\n");
        printf("\n\n\t\t\t\t\t\t\t\t\t\t\t\tIngrese el numero de la accion que desea seleccionar\n");
        printf("\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t1:Listar texto.Mostrara en pantalla el archivo de texto\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\t2:Crear un nuevo archivo binario\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\t3:Migrar los datos del archivo de texto hacia el archivo binario.\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\t4:Listar los datos de los clientes\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\t5:Agregar un nuevo cliente\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\t6:Buscar un cliente en nuestro archivo binario\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\t7:Modificar el tipo de credito de un cliente seleccionado\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\t8:Dar de baja al cliente seleccionado\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\t0:Salir del sistema\n");
}

void menu2() {
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\tIngrese el numero de la lista que desea seleccionar\n");
    printf("\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t1: Listar todos (activos y inactivos)\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t2: Solo los activos\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t3: El ingreso por teclado de un tipo de crédito\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t0: volver al menu principal\n\t\t\t\t\t\t\t");
}

