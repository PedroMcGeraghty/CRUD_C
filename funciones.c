#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <ctype.h>
#include <time.h>
#include "funciones.h"
#define N 100
#include <stdbool.h>


struct  Creditos{
    int orden;
    char nombreCliente[50];
    float importe;
    char tipoDeCredito[20];
    int dia ;
    int mes ;
    int ano ;
    int NroCuotas;
    float importeCuotas;
    float IVA;
    float totalCuota;
    int activo;
};

struct CreditoAuxiliar{
    int orden;
    char nombre[25];
    char apellido[25];
    float importe;
    char tipoDeCredito[20];
    int dia ;
    char mesCad[3];
    int ano;
    int NroCuotas;
    float importeCuotas;
    float IVA;
    float totalCuota;
    int activo;
};

//ERRORES
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


//PUNTO 4:LEER ARCHIVO
void leerDatosCSV(FILE *pArchivo) {
    pArchivo=fopen("prestamos.csv","r");

    //VERIFICO SI SE PUDO ABRIR EL ARCHIVO
    if(pArchivo==NULL){
        printf("Error al abrir el archivo\n");
        return;
    }

    //VARIABLES QUE ME VAN A AYUDAR A IMPRIMIR EN PANTALLA
    char linea[2000],no[30],tc[30];
    int or,di,me,an,nc;
    float im,ic,iv,t;

    fgets(linea,sizeof(linea),pArchivo); // LEE LA PRIMER LINEA Y LA DESCARTA YA QUE LA VOY A PRINTEAR YO

    printf(" %s\t\t%s  \t\t%s\t%s\t\t%s  \t%s \t%s \t%s %s\n", "ORDEN", "NOMBRE", "IMPORTE", "TIPO CREDITO", "FECHA", "NUM.CUOTAS","IMP. CUOTA","IVA","TOTAL CUOTA");

    while (fgets(linea,sizeof(linea),pArchivo)){
        leer(linea,&or,no,&im,tc,&di,&me,&an,&nc,&ic,&iv,&t);//PASO LAS VARIABLES A UNA FUNCION QUE VA A LEER LA PRIMER LINEA Y VA A IR UBICANDO EN CADA VARIABLE EL CAMPO CORRESPONDIENTE
        //printf("________________________________________________________________________________________________________________________________\n");
        printf("| \t%-4d   | %-16s  | %-8.2f | %-1s \t| %-2d | %-1d | %-5d |  %9d | %-9.2f | %-7.2f | %10.2f |\n", or, no, im, tc, di, me, an, nc, ic, iv, t);
        printf("________________________________________________________________________________________________________________________________\n");
    }
    fclose(pArchivo);

    system("pause");
    system("cls");
}


//FUNCION QUE LEE LA PRIMER LINEA Y LAS SUBDIVIDE EN CADENAS PARA PODER GUARDARLAS EN SU VARIABLE CORRESPONDEINTE
void leer(char *linea,int *or,char *no,float *im,char *tc,int *di,int *me,int *an,int *nc,float *ic,float *iv,float *t){

    //USO DEL TOKEN
    char *orden, *nombre, *importe, *tipocredito, *dia, *mes, *anio, *numerocuotas,*importecuotas, *iva,*importet,*ok;
    ok=strtok(linea,";");
    orden=(ok);
    *or=atoi(orden);

    nombre=strtok(NULL,";");
    strcpy(no,nombre);

    importe=strtok(NULL,";");
    *im=atol(importe);

    tipocredito=strtok(NULL,";");
    strcpy(tc,tipocredito);

    dia=strtok(NULL,";");
    *di=atol(dia);

    mes=strtok(NULL,";");
    *me=atol(mes);

    anio=strtok(NULL,";");
    *an=atol(anio);

    numerocuotas=strtok(NULL,";");
    *nc=atol(numerocuotas);

    importecuotas=strtok(NULL,";");
    *ic=atol(importecuotas);

    iva=strtok(NULL,";");
    *iv=atol(iva);

    importet=strtok(NULL,";");
    *t=atol(importet);

}

//PUNTO 5: CREAR ARCHIVO
void crearArchivo(FILE *ArchivoCreado,char archivoBinario[] ){
   //ABRO EL ARCHIVO EN MODO W , YA QUE SI NO EXISTE EL ARCHIVO BINARIO CON ESE NOMBRE , LO CREA
    ArchivoCreado =fopen(archivoBinario, "w");
      if(ArchivoCreado != NULL){
        system("cls");
        printf("\n\n\n\n\n\n\n\t\t\t\t\t\t*Archivo creado exitosamente*\n\n\n");
        fclose(ArchivoCreado);

    }
    else{
        printf("\n\n\t\t\t\t\t*Error en la creaci%cn del archivo*\n",162);

    }

    system("pause");
    system("cls");
}

//PUNTO 6: MIGRAR DATOS

void migrar(FILE *pArchivo, FILE *archivoCreado , char *archivoBinario){

    //ESTA FUNCION RECORRE EL ARCHIVO CSV USANDO LA FUNCION leer
    //UNA VEZ LEIDO LOS DATOS , PROCESO LOS DATOS ANTES DE ENVIARLOS AL STRUCT
    //UNA VEZ PROCESADO Y ENVIADO AL STRUCT LOS GUARDO EN EL ARCHIVO BINARIO CREADO ANTERIORMENTE
    //DEFINO NUEVAMENTE LAS VARIABLES PARA PODER LEER EL ARCHIVO CSV Y PROCESAR LOS DATOS


    //int i = 0;
    char *meses[] = {"nul","ene", "feb", "mar", "abr", "may", "jun", "jul", "ago", "sep", "oct", "nov", "dic"};//CADENA QUE ME VA AYUDAR A PASAR EL DATO NUMERICO DEL MES A UN EN FORMATO CADENA

    pArchivo = fopen("prestamos.csv","r");
    archivoCreado = fopen(archivoBinario,"rb+");

    char linea[2000],no[30],tc[30];
    int or,di,me,an,nc;
    float im,ic,iv,t;


    struct CreditoAuxiliar aux;

    fseek(archivoCreado, 0*sizeof(struct Creditos), SEEK_SET);

    if(pArchivo!=NULL){
        fgets(linea,2000,pArchivo);//Leo primer linea  descarto

        while(!feof(pArchivo)){
            leer(linea,&or,no,&im,tc,&di,&me,&an,&nc,&ic,&iv,&t);

//    **PASAR LAS VARIABLES LEIDAS DEL CSV A NUESTRO STRUCT*
//    **HAY VARIABLES QUE SE PROCESAN ANTES DE IR AL STRUCT

            aux.orden=or;

            //MAYUSCULIZAR VARIABLES

            mayusculizador(no);
            mayusculizador(tc);


            //DIVIDIR NOMBRES
            char* token = strtok(no, " "); // Se utiliza el espacio como delimitador

            if (token != NULL) {
                strcpy(aux.nombre, token); // Copiar el primer token (nombre) en la variable nombre
                    token = strtok(NULL, " "); // Obtener el siguiente token (apellido)

                if (token != NULL) {
                        strcpy(aux.apellido, token); // Copiar el segundo token (apellido) en la variable apellido
                    }
                }

            aux.importe=im;
            strcpy(aux.tipoDeCredito,tc);
            aux.dia=di;
            strcpy(aux.mesCad,meses[me]);
            aux.ano=an;
            aux.NroCuotas= nc;
            aux.importeCuotas=ic;
            aux.IVA=iv;
            aux.totalCuota=t;
            aux.activo=1;



            //IMPRIMIR EN EL ARCHIVO BINARIO UNA LINEA DE NUESTRO STRUCT
            fwrite(&aux, sizeof(struct Creditos), 1, archivoCreado);

            fgets(linea,2000,pArchivo);

            }

        fclose(pArchivo);

        fclose(archivoCreado);

        printf("\n\n\n\n\n\n\n\t\t\t\t\t\t*Datos migrados correctamente*\n\n\n\n\n");
    }
    else{
        printf("Error en la extracci%cn de datos\n", 162);
    }
    system("pause");
    system("cls");
}

//FUNCION QUE MAYUSCULIZA(SI NECESITO MAYUSCULIZAR UNA CADENA LLAMO A ESTA FUNCION)
void mayusculizador(char *mayus){
   while (*mayus) {
        *mayus = toupper(*mayus);
        mayus++;
    }

}

//PUNTO 7 : IMPRIMIR LA TABLA DE BINARIO CON SUS RESPECTIVAS CONDICIONES

void imprimirTodo(FILE *ArchivoCreado,char archivoBinario[]){
    system("cls");
    ArchivoCreado=fopen(archivoBinario,"rb");//ABRO EL ARCHIVO BINARIO EN MODO LECTURA

     if (ArchivoCreado != NULL) {//VERIFICO SI EL ARCHIVO SE ABRIO CORRECTAMENTE

      struct CreditoAuxiliar existente;//VARIABLE STRUCT DONDE VOY A GUARDAR LOS DATOS DEL ARCHIVO BINARIO PARA LUEGO IMPRIMIRLOS
       // LEO Y DESCARTO LA PRIMER LINEA
            printf("+-------+------------------+------------------+---------+--------------+-----+------+-------------+--------------+---------+----------+--------+\n");
            printf("| Orden |      Nombre      |     Apellido     | Importe |     Tipo     | Dia | Mes  |     Anio    | Num. Cuotas  |   Imp.  |   Total  | Activo |\n");
            printf("+-------+------------------+------------------+---------+--------------+-----+------+-------------+--------------+---------+----------+--------+\n");
        fread(&existente, sizeof(struct CreditoAuxiliar), 1, ArchivoCreado);

          while (fread(&existente, sizeof(struct CreditoAuxiliar), 1, ArchivoCreado)) {


            printf("| %-5d | %-16s | %-16s | %-7.2f | %-4s | %-3d | %-4s | %-11d | %-12d | %-7.2f | %-8.2f | %-6d |\n", existente.orden, existente.nombre, existente.apellido, existente.importe, existente.tipoDeCredito, existente.dia, existente.mesCad, existente.ano, existente.NroCuotas, existente.importeCuotas, existente.totalCuota, existente.activo);//LEO EL BINARIO EN UNA LINEA CON MI STRUCT
            printf("+-------+------------------+------------------+---------+--------------+-----+------+-------------+--------------+---------+----------+--------+\n");

        }

    }else{
        printf("Error al abrir el archivo.\n");
    }
    system("pause");
    system("cls");
    fclose(ArchivoCreado);
}

//FUNCION QUE SOLO IMPRIME AQUELLOS CLIENTES QUE ESTAN ACTIVOS
void imprimirActivos(FILE *ArchivoCreado,char *archivoBinario) {
    system("cls");
    struct CreditoAuxiliar existente;

    ArchivoCreado=fopen(archivoBinario,"rb");//ABRIMOS EL ARCHIVO EN MODO LECTURA
    if(ArchivoCreado!=NULL){

    }
      if (ArchivoCreado != NULL) {
        printf("+-------+------------------+------------------+---------+--------------+-----+------+-------------+--------------+---------+----------+--------+\n");
        printf("| Orden | Nombre           | Apellido         | Importe | Tipo         | Dia | Mes  | Anio        | Num. Cuotas  | Imp.    | Total    | Activo |\n");
        printf("+-------+------------------+------------------+---------+--------------+-----+------+-------------+--------------+---------+----------+--------+\n");
        fread(&existente, sizeof(struct CreditoAuxiliar), 1, ArchivoCreado);

        while (fread(&existente, sizeof(struct CreditoAuxiliar), 1, ArchivoCreado) ) {
            if (existente.activo == 1) {//COMPARA EN ESE MOMENTO CON EL STRUCT LEIDO EL CAMPO ACTIVO PARA SABER SI PRINTEARLO O NO
                 printf("| %-5d | %-16s | %-16s | %-7.2f | %-4s | %-3d | %-4s | %-11d | %-12d | %-7.2f | %-8.2f | %-6d |\n", existente.orden, existente.nombre, existente.apellido, existente.importe, existente.tipoDeCredito, existente.dia, existente.mesCad, existente.ano, existente.NroCuotas, existente.importeCuotas, existente.totalCuota, existente.activo);
                 printf("+-------+------------------+------------------+---------+--------------+-----+------+-------------+--------------+---------+----------+--------+\n");
            }else{
                //printf("Error al abrir el archivo.\n");
            }
        }
        system("pause");
        system("cls");
        fclose(ArchivoCreado);
    }else{
        printf("\n\n\t\t\t\t\t\tError a abrir el archivo");
    }
}

//FUNCION QUE RECIBE POR PARAMETRO EL TIPO DE CREDITO PARA SABER QUE CLIENTES PRINTEAR EN BASE A SU TIPO DE CREDITO
void imprimirPorTipo(FILE *archivoCreado,char archivoBinario[],char *tipoCredito){
    system("cls");
    archivoCreado=fopen(archivoBinario,"rb");//ABRE EL ARCHIVO EN MODO LECTURA
    struct CreditoAuxiliar existente;
     printf("+-------+------------------+------------------+---------+--------------+-----+------+-------------+--------------+---------+----------+--------+\n");
     printf("| Orden | Nombre           | Apellido         | Importe | Tipo         | Dia | Mes  | Anio        | Num. Cuotas  | Imp.    | Total    | Activo |\n");
     printf("+-------+------------------+------------------+---------+--------------+-----+------+-------------+--------------+---------+----------+--------+\n");
    if (archivoCreado != NULL) {
        fread(&existente, sizeof(struct CreditoAuxiliar), 1, archivoCreado);

        while (fread(&existente, sizeof(struct CreditoAuxiliar), 1, archivoCreado) ) {
            if (!strcmp(tipoCredito,existente.tipoDeCredito)) {
                  printf("| %-5d | %-16s | %-16s | %-7.2f | %-4s | %-3d | %-4s | %-11d | %-12d | %-7.2f | %-8.2f | %-6d |\n", existente.orden, existente.nombre, existente.apellido, existente.importe, existente.tipoDeCredito, existente.dia, existente.mesCad, existente.ano, existente.NroCuotas, existente.importeCuotas, existente.totalCuota, existente.activo);
                  printf("+-------+------------------+------------------+---------+--------------+-----+------+-------------+--------------+---------+----------+--------+\n");
            }else{
                //printf("Error al abrir el archivo.\n");
            }
        }
    }else{
                printf("Error al abrir el archivo.\n");
            }


    system("pause");
    system("cls");
}


bool contieneNumeros(const char* cadena) {
    return (strpbrk(cadena, "0123456789") != NULL);
}


//PUNTO 8: AGREGAR UN NUEVO CLIENTE
void agregarCliente(FILE *archivoCreado,char archivoBinario[]){
    system("cls");
    //archivoCreado= fopen(archivoBinario,"ab");
    int opcion,flag=0;
    struct CreditoAuxiliar nuevo;
    struct CreditoAuxiliar existente;
    char *meses[] = {"nul","ene", "feb", "mar", "abr", "may", "jun", "jul", "ago", "sep", "oct", "nov", "dic"};//ARRAY QUE ME AYUDA DE PASAR DE MES EN FORMATO NUMERO A MES FORMATO TEXTO
    int diaMes;


    //VALIDACION DE ORDEN
    do{
        printf("\n\n\t\t\t\t\tIngrese el numero de orden: ");
        scanf("%d",&nuevo.orden);
        while(nuevo.orden < 0|| nuevo.orden>100){
            printf("\n\n\t\t\t\t\tError: numero negativo. ingrese nuevamente numero de orden: ");
            scanf("%d",&nuevo.orden);
        }

        // COMPROBAR SI YA EXISTE EL NUMERO DE ORDEN

        archivoCreado = fopen(archivoBinario, "rb");
        if (archivoCreado != NULL) {
            flag = 0;
            while (fread(&existente, sizeof( struct CreditoAuxiliar), 1, archivoCreado)) {
                if (existente.orden == nuevo.orden) {
                    fclose(archivoCreado);
                    printf("\n\n\t\t\t\t\tError: Ya existe un registro con el mismo numero de orden.\n");

                    flag=1;
                }

            }
            fclose(archivoCreado);
        }else{
            printf("\n\n\t\t\t\t\tError al abrir el archivo\n");
        }

    }while(flag== 1);


    //VALIDACION DE NOMBRE
     do {
        printf("\n\n\t\t\t\t\tIngrese el nombre del cliente: ");
        fflush(stdin);

        char nuevoNombre[100];
        fgets(nuevoNombre, sizeof(nuevoNombre), stdin);
        nuevoNombre[strcspn(nuevoNombre, "\n")] = '\0';  // Eliminar el carácter de nueva línea

        if (contieneNumeros(nuevoNombre)) {
            printf("\n\t\t\t\t\tError: No ingrese números en el nombre.\n");
            continue;
        }

        // Hasta este punto, la entrada es válida y se puede copiar a nuevo.nombre
        strcpy(nuevo.nombre, nuevoNombre);
        break;

    } while (1);

    //VALIDACION DE APELLIDO
     do {
        printf("\n\n\t\t\t\t\tIngrese el apellido del cliente: ");
        fflush(stdin);

        char nuevoApellido[100];
        fgets(nuevoApellido, sizeof(nuevoApellido), stdin);
        nuevoApellido[strcspn(nuevoApellido, "\n")] = '\0';  // Eliminar el carácter de nueva línea

        if (contieneNumeros(nuevoApellido)) {
            printf("\n\t\t\t\t\tError: No ingrese números en el apellido.\n");
            continue;
        }
        mayusculizador(nuevoApellido);
        // HASTA ESTE PUNTO, LA ENTRADA ES VALIDA Y SE PUEDE COPIAR A nuevo.nombre
        strcpy(nuevo.apellido, nuevoApellido);
        break;

    } while (1);

        //VALIDAR QUE SEA POSITIVO
        do{
            printf("\n\n\t\t\t\t\tIngrese el importe del cliente: ");
            fflush(stdin);
            scanf("%f",&nuevo.importe);
            if(nuevo.importe<0){
                printf("A ingreseado un valor incorrecto , intente nuevamente");
            }
        }while(nuevo.importe<0);

       //VALIDACION TIPO DE CREDITO
        printf("\n\n\t\t\t\t\tSeleccione el tipo de credito de cliente");
        printf("\n\n\t\t\t\t\t\t1:A sola firma\n");
        printf("\t\t\t\t\t\t2:con garantia\n\t\t\t\t");
        fflush(stdin);
        scanf("%d",&opcion);
    while(opcion < 1 || opcion >2){
        printf("\n\n\t\t\t\t\t\tIngrese nuevamente el tipo de  credito de cliente");
        printf("\n\n\t\t\t\t\t\t1:A sola firma\n");
        printf("\t\t\t\t\t\t2:con garantia\n\t\t\t\t");
        fflush(stdin);
        scanf("%d",&opcion);
    }


    if(opcion == 1){
        strcpy(nuevo.tipoDeCredito,"A SOLA FIRMA");
    }else{
         strcpy(nuevo.tipoDeCredito,"CON GARANTIA");
    }

    //VALIDACION FECHA

    printf("\n\n\t\t\t\t\tIngrese el dia : ");
    fflush(stdin);
    scanf("%d",&nuevo.dia);
    printf("\n\n\t\t\t\t\tIngrese el numero de mes : ");
    fflush(stdin);
    scanf("%d",&diaMes);
    printf("\n\n\t\t\t\t\tIngrese el anio : ");
    fflush(stdin);
    scanf("%d",&nuevo.ano);

    while((nuevo.dia<1 || nuevo.dia>31)||(diaMes<1 || diaMes >13)|| (nuevo.ano<0) || (nuevo.ano>2023)){
        printf("\n\n\t\t\t\t\tError:ingreso mal la fecha.Ingrese nuevamente la fecha  ");
        printf("\n\n\t\t\t\t\tIngrese el dia : ");
        fflush(stdin);
        scanf("%d",&nuevo.dia);
        printf("\n\n\t\t\t\t\tIngrese el numero de mes : ");
        fflush(stdin);
        scanf("%d",&diaMes);
        printf("\n\n\t\t\t\t\tIngrese el anio : ");
        scanf("%d",&nuevo.ano);

    }
    strcpy(nuevo.mesCad,meses[diaMes]);
    //VALIDACION NUMERO DE CUOTAS

    printf("\n\n\t\t\t\t\tIngrese el numero de cuotas : ");
    scanf("%d",&nuevo.NroCuotas);

    while(nuevo.NroCuotas<0){
        printf("\n\n\t\t\t\t\tIngrese nuevamente el numero de cuotas : ");
        scanf("%d",&nuevo.NroCuotas);
    }

    nuevo.importeCuotas= nuevo.importe/nuevo.NroCuotas;
    nuevo.IVA= nuevo.importeCuotas*0.21;

    nuevo.totalCuota = nuevo.importeCuotas+nuevo.IVA;

    nuevo.activo = 1;

    system("pause");
    system("cls");



     archivoCreado = fopen(archivoBinario, "r+b");
    if (archivoCreado != NULL) {
        // Encontrar la posición de inserción
        int posicion = -1;

        while (fread(&existente, sizeof(struct CreditoAuxiliar), 1, archivoCreado) ) {

            if (existente.orden > nuevo.orden) {
                fseek(archivoCreado, -sizeof(struct CreditoAuxiliar), SEEK_CUR);
                posicion = ftell(archivoCreado);
                break;
            }
        }
        if (posicion == -1) {
            posicion = ftell(archivoCreado);
        }

        // DESLPAZAR LOS REGISTROS HACIA ADELANTE PARA ABRIR ESPACIO
        fseek(archivoCreado, 0, SEEK_END);
        int finArchivo = ftell(archivoCreado);
        int bytesPorMover = finArchivo - posicion;
        char *buffer = (char *)malloc(bytesPorMover);
        fseek(archivoCreado, posicion, SEEK_SET);
        fread(buffer, bytesPorMover, 1, archivoCreado);
        fseek(archivoCreado, posicion, SEEK_SET);
        fwrite(&nuevo, sizeof(struct CreditoAuxiliar), 1, archivoCreado);
        fwrite(buffer, bytesPorMover, 1, archivoCreado);
        free(buffer);

        fclose(archivoCreado);
        printf("\n\n\n\n\t\t\t\t\tEl cliente ha sido registrado correctamente.\n\n\n");
    } else {
        printf("Error al abrir el archivo.\n");
    }

    system("pause");
    system("cls");

}

//PUNTO 9: BUSQUEDA POR NUMERO DE ORDEN O APELLIDO(EL METODO LO PASO POR MARAMETRO DESDE UN VALOR QUE LE PIDO AL USUARIO EN EL MAIN)
void busquedaDelCliente(FILE *archivoCreado,char archivoBinario[],int metodoBusqueda){

    char apellidoBuscado[25];
    int clienteBuscado;
    struct CreditoAuxiliar existente;
    int flag=0;
    archivoCreado=fopen(archivoBinario,"rb");

        switch(metodoBusqueda){
            case 1:
                     printf("\n\n\t\t\t\tIngrese el numero de orden que desa buscar : ");
                     scanf("%d",&clienteBuscado);

                        while(clienteBuscado < 0 || clienteBuscado>100){
                            printf("\n\n\t\t\t\tError: numero negativo. ingrese nuevamente numero de orden :");
                            scanf("%d",&clienteBuscado);
                        }

                    fread(&existente, sizeof(struct CreditoAuxiliar), 1, archivoCreado);
                    while(fread(&existente, sizeof(struct CreditoAuxiliar), 1, archivoCreado)){
                        if(clienteBuscado==existente.orden){
                                    system("cls");
                                    printf("\n\n\t\t\t\tOrden: %d\n", existente.orden);
                                    printf("\t\t\t\tNombre: %s\n", existente.nombre);
                                    printf("\t\t\t\tApellido: %s\n", existente.apellido);
                                    printf("\t\t\t\tImporte: %.2f\n", existente.importe);
                                    printf("\t\t\t\tTipo de Credito: %s\n", existente.tipoDeCredito);
                                    printf("\t\t\t\tFecha: %d-%s-%d\n", existente.dia, existente.mesCad, existente.ano);
                                    printf("\t\t\t\tNumero de Cuotas: %d\n", existente.NroCuotas);
                                    printf("\t\t\t\tImporte de la Cuota: %.2f\n", existente.importeCuotas);
                                    printf("\t\t\t\tIVA: %.2f\n", existente.IVA);
                                    printf("\t\t\t\tTotal de la Cuota: %.2f\n", existente.totalCuota);
                                    printf("\t\t\t\tActivo: %d\n\n", existente.activo);
                                    fclose(archivoCreado);
                                    system("pause");
                                    system("cls");
                                    return;
                        }else{
                            flag =1;
                        }

                    }

                    if(flag){
                        printf("\n\n\t\t\t\tNo se encontro el cliente con ese numero de orden\n\n");
                        fclose(archivoCreado);
                        system("pause");
                        system("cls");
                        return;
                    }
                    break;

            case 2: printf("\n\n\t\t\t\tIngrese el apellido que del cliente que desea buscar: ");
                    fflush(stdin);
                    gets(apellidoBuscado);
                    mayusculizador(apellidoBuscado);

                     fread(&existente, sizeof(struct CreditoAuxiliar), 1, archivoCreado);
                     while(fread(&existente, sizeof(struct CreditoAuxiliar), 1, archivoCreado)) {
                        if(strcmp(existente.apellido, apellidoBuscado) == 0) {
                            system("cls");
                            printf("\n\n\n\t\t\t\t\tOrden: %d\n", existente.orden);
                            printf("\t\t\t\t\t\tNombre: %s\n", existente.nombre);
                            printf("\t\t\t\t\t\tApellido: %s\n", existente.apellido);
                            printf("\t\t\t\t\t\tImporte: %.2f\n", existente.importe);
                            printf("\t\t\t\t\t\tTipo de Credito: %s\n", existente.tipoDeCredito);
                            printf("\t\t\t\t\t\tFecha: %d-%s-%d\n", existente.dia, existente.mesCad, existente.ano);
                            printf("\t\t\t\t\t\tNumero de Cuotas: %d\n", existente.NroCuotas);
                            printf("\t\t\t\t\t\tImporte de la Cuota: %.2f\n", existente.importeCuotas);
                            printf("\t\t\t\t\t\tIVA: %.2f\n", existente.IVA);
                            printf("\t\t\t\t\t\tTotal de la Cuota: %.2f\n", existente.totalCuota);
                            printf("\t\t\t\t\t\tActivo: %d\n\n", existente.activo);
                            fclose(archivoCreado);
                            system("pause");
                            system("cls");
                            return;
                        } else {
                            flag = 1;
                        }
                    }

                    if(flag) {
                        printf("\n\n\t\t\t\tNo se encontró el cliente con ese apellido\n\n");
                        fclose(archivoCreado);
                        system("pause");
                        system("cls");
                        return;
                    }


        }
}

//PUNTO 10: MODIFICAR DATOS

void modificarDatos(FILE *archivoCreado, char *archivoBinario) {
    archivoCreado = fopen(archivoBinario, "rb+");
    struct CreditoAuxiliar existente;
    int clienteBuscado;
    int encontrado = 0;
    char confirmacion;
    int opcion;

    printf("\n\n\t\t\t\tIngrese el numero de orden que desa buscar : ");
    scanf("%d", &clienteBuscado);

    while (clienteBuscado < 0 || clienteBuscado > 100) {
        printf("\n\n\t\t\t\tError: numero negativo. ingrese nuevamente numero de orden :");
        scanf("%d", &clienteBuscado);
    }

    while (fread(&existente, sizeof(struct CreditoAuxiliar), 1, archivoCreado)) {
        if (existente.orden == clienteBuscado) {
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\n\n\t\t\t\t\tNo se ha encontrado al cliente");
        return;
    }

    system("cls");
    printf("\n\n\t\t\t\t\t**Informacion actual del cliente**\n\n");
    printf("\t\t\t\t\t\tNombre: %s\n", existente.nombre);
    printf("\t\t\t\t\t\tApellido: %s\n", existente.apellido);
    printf("\t\t\t\t\t\tImporte: %.2f\n", existente.importe);
    printf("\t\t\t\t\t\tTipo de Credito: %s\n", existente.tipoDeCredito);

    printf("\n\n\t\t\t\t\t**Actualizar informacion**\n\n");
    do{
        printf("\n\t\t\t\t\tIngrese el nuevo importe: ");
        scanf("%f", &existente.importe);
        if(existente.importe<0){
            printf("\n\t\t\t\t\tA ingreseado un valor incorrecto , intente nuevamente");
        }
    }while(existente.importe<0);

    //VALIDACION TIPO DE CREDITO
        printf("\n\n\t\t\t\t\tSeleccione el nuevo tipo de credito de cliente");
        printf("\n\n\t\t\t\t\t\t\t1:A sola firma\n");
        printf("\t\t\t\t\t\t\t2:con garantia\n\t\t\t\t");
        fflush(stdin);
        scanf("%d",&opcion);
    while(opcion < 1 || opcion >2){
        printf("\n\n\t\t\t\t\t\t\tIngrese nuevamente el tipo de  credito de cliente");
        printf("\n\n\t\t\t\t1:A sola firma\n");
        printf("\t\t\t\t\t\t\t2:con garantia\n\t\t\t\t");
        fflush(stdin);
        scanf("%d",&opcion);
    }

    fflush(stdin);
    if(opcion == 1){
        strcpy(existente.tipoDeCredito,"A SOLA FIRMA");
    }else{
         strcpy(existente.tipoDeCredito,"CON GARANTIA");
    }


    //VALIDACION DE OPCION
    do{
        printf("\n\n\t\t\t\t\t ¿Desea modificar los datos de este cliente? (y/n): ");
        scanf("%c", &confirmacion);

        if(confirmacion == 'y'||confirmacion == 'Y'){
            // MOVEMOS EL CURSOS DONDE DESEAMOS MODIFICAR LOS DATOS
            fseek(archivoCreado, -sizeof(struct CreditoAuxiliar), SEEK_CUR);
            //SOBREESCRIBIMOS LOS DATOS
            fwrite(&existente, sizeof(struct CreditoAuxiliar), 1, archivoCreado);
            fclose(archivoCreado);
            system("cls");
            printf("\n\n\n\n\n\t\t\t\t**Los datos del cliente han sido modificados correctamente.**\n\n");
            system("pause");
            system("cls");
            return;
        }else if(confirmacion == 'n'||confirmacion == 'N'){
             printf("\n\n\n\n\n\t\t\t\t**Los datos no se han sido modificado**\n\n");
             system("pause");
             system("cls");
             return;
        }else{
            printf("\n\n\n\n\n\t\t\t\t **A tocado una tecla erronea intente nuevamente**\n\n");
            fflush(stdin);
        }
    }while(confirmacion != 'y'||confirmacion != 'Y' || confirmacion == 'n'||confirmacion == 'N' );


    fclose(archivoCreado);
}

//PUNTO 11: DAR DE BAJA A UN CLIENTE
void darDeBaja(FILE *archivoCreado, char *archivoBinario){
    archivoCreado = fopen(archivoBinario, "rb+");
    struct CreditoAuxiliar existente;
    int clienteBuscado;
    int encontrado = 0;
    char confirmacion;


    printf("\n\n\t\t\t\tIngrese el numero de orden que desa buscar : ");
    scanf("%d",&clienteBuscado);

    while(clienteBuscado < 0 || clienteBuscado>100){
        printf("\n\n\t\t\t\tError: numero negativo. ingrese nuevamente numero de orden :");
        scanf("%d",&clienteBuscado);
    }

    while (fread(&existente, sizeof(struct CreditoAuxiliar), 1, archivoCreado)) {
        if (existente.orden == clienteBuscado) {
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\n\n\t\t\t\t\tNo se ha encontrado al cliente");
        return;
    }

    printf("\n\n\n\t\t\t\t\t\tNombre: %s\n", existente.nombre);
    printf("\t\t\t\t\t\tApellido: %s\n", existente.apellido);
    printf("\t\t\t\t\t\tActivo: %d \n", existente.activo);
    existente.activo=0;

    fflush(stdin);
    //VALIDACION DE OPCION
    do{
        printf("\n\n\t\t\t\t\t ¿Desea dar de baja al cliente? (Y/N): ");
        fflush(stdin);
        scanf("%c", &confirmacion);
        if(confirmacion == 'y'||confirmacion == 'Y'){
            system("cls");
            // MOVEMOS EL CURSOS DONDE DESEAMOS MODIFICAR LOS DATOS
            fseek(archivoCreado, -sizeof(struct CreditoAuxiliar), SEEK_CUR);

            //SOBREESCRIBIMOS LOS DATOS
            fwrite(&existente, sizeof(struct CreditoAuxiliar), 1, archivoCreado);
            fclose(archivoCreado);

            printf("\n\n\n\n\n\t\t\t\t\t**El cliente fue dado de baja**\n\n");
            fflush(stdin);
            system("pause");
            system("cls");
            fclose(archivoCreado);
            return;
        }else if(confirmacion == 'n'||confirmacion == 'N'){
             system("cls");
             printf("\n\n\n\n\n\t\t\t\t\t**No se dio de baja al cliente*\n\n");
             system("pause");
             system("cls");
             fclose(archivoCreado);
             return;
        }else{
            system("cls");
            printf("\n\n\n\n\n\t\t\t\t **A tocado una tecla erronea intente nuevamente**\n\n");
            fflush(stdin);
        }
    }while(confirmacion != 'y'||confirmacion != 'Y' || confirmacion == 'n'||confirmacion == 'N' );

    fclose(archivoCreado);

}






















