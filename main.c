#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <ctype.h>
#include <time.h>
#include "funciones.h"
#include "interfaz.h"
#define N 100
#define n 20


//typedef struct Creditos ;


int main(){
    char tipoCredito[n],opcionChar[n];
    int opcion,opcion2,metodoBusqueda;
    FILE *pArchivo = NULL;
    FILE *ArchivoCreado= NULL;
    char archivoBinario[30]= "creditos.dat";
    char yesno;


    do{
        menu();//FUNCION QUE PRINTEA EL MENU DE OPCIONES
        validarIngreso(opcionChar,&opcion);

    switch(opcion){
        case 1: system("cls");
               leerDatosCSV(pArchivo);
               break;
       case 2:system("cls");

              do{

                  printf("\n\n\t\t\t\t\t\tCREACION DE ARCHIVO BINARIO\n\n");
                  printf("\t\t\t\tSe creara un archivo binario de nombre 'creditos.dat' en la carpeta 'BINARIOS'. \n");
                  printf("\n\n\t\t\t\t\t\tDesea continuar? [Y/N] : ");
                  fflush(stdin);
                  scanf("%c",&yesno);
                 system("cls");
                //Emite mensaje de opcion

                  if((yesno== 'y')||(yesno== 'Y')){                 //VALIDA LA OPCION QUE ELIGIO EL USUARIO
                        crearArchivo(ArchivoCreado,archivoBinario);
                        break;
                        system("cls");

                  }else if((yesno== 'n')||(yesno== 'N')){
                        system("cls");
                        printf("\n\n\n\n\t\t\t\t\t\tNo se creo el archivo\n");
                        system("pause");
                        system("cls");
                        break;
                  }else{
                        printf("\n\n\t\t\t\t\tHa ingresado una opcion incorrecta elija nuevamente\n\n");
                  }
                  }while(((yesno!= 'y')||(yesno!= 'Y')) && ((yesno!= 'n')||(yesno!= 'N')));
              break;
        case 3: system("cls");
                migrar(pArchivo,ArchivoCreado,archivoBinario);
                break;
        case 4: system("cls");


                        do {
                            do{
                                printf("\n\n\t\t\t\t\tIngrese el numero de la lista que desea seleccionar\n");
                                printf("\n\n\t\t\t\t\t\t1: Listar todos (activos y inactivos)\n");
                                printf("\t\t\t\t\t\t2: Solo los activos\n");
                                printf("\t\t\t\t\t\t3: El ingreso por teclado de un tipo de crédito\n");
                                printf("\t\t\t\t\t\t0: volver al menu principal\n\t\t\t\t\t\t\t");
                                scanf("%d", &opcion2);
                                system("cls");

                                if((opcion2 !=1) && (opcion2 !=2) && (opcion2 !=3) && (opcion2 !=0)){
                                    printf("\t\tA ingresado una opcion incorreta, intente nuevamente\n\n");
                                }

                            }while((opcion2 !=1) && (opcion2 !=2) && (opcion2 !=3) && (opcion2 !=0) );

                            switch (opcion2) {
                                case 1:printf("Listando todos los clientes (activos e inactivos)\n");
                                      imprimirTodo(ArchivoCreado,archivoBinario);
                                      break;
                                case 2:printf("Listando solo los clientes activos\n");
                                      imprimirActivos(ArchivoCreado,archivoBinario);
                                      break;
                                case 3:
                                        system("cls");
                                        // VALIDAR EL TIPO DE CREDITO INGRESADO
                                        do{

                                           printf("\n\n\t\t\t\t\tIngrese el tipo de credito a listar(a sola firma/con garantia)\n\n\t\t\t\t\tSu Opcion : ");
                                           fflush(stdin);
                                           gets(tipoCredito);
                                           mayusculizador(tipoCredito);
                                            if (strcmp(tipoCredito, "CON GARANTIA") == 0) {
                                                printf("\n\n\t\t\t\t\tSe ingreso el tipo de credito \"con garantia\"\n\n");

                                            } else if (strcmp(tipoCredito, "A SOLA FIRMA") == 0) {
                                                printf("\n\n\t\t\t\t\tSe ingreso el tipo de credito \"a sola firma\"\n\n");

                                            } else {
                                                fflush(stdin);
                                                printf("\n\n\t\t\t\tTipo de credito invalido ingrese nuevamente\n");


                                            }
                                        }while((strcmp(tipoCredito, "CON GARANTIA") != 0)&&(strcmp(tipoCredito, "A SOLA FIRMA") != 0));
                                        system("pause");
                                       imprimirPorTipo(ArchivoCreado,archivoBinario,tipoCredito);

                                       break;

                                       case 0:system("cls");
                                            printf("\n\n\t\t\t\t\t\tVolver al menu principal\n\n");
                                            //opcion2=NULL;
                                            system("pause");
                                            system("cls");
                                            break;
                            }


                        } while (opcion2 >0 && opcion2 < 4);

                    break;
        case 5:system("cls");
               agregarCliente(ArchivoCreado,archivoBinario);
               break;

        case 6:system("cls");
               printf("\n\n\t\t\t\t\tIngrese de que manera desea buscar al cliente\n\n\t\t\t\t\t");
                //VALIDACION DE METODO DE BUSQUEDA
                printf("\n\n\t\t\t\t\t\t1:Busqueda por  numero de orden\n");
                printf("\t\t\t\t\t\t2:busqueda por apellido\n");
                printf("\t\t\t\t\t\t0:Salir\n\t\t\t\t");
                fflush(stdin);
                scanf("%d",&metodoBusqueda);
                while((metodoBusqueda < -1) || (metodoBusqueda >2)   ){
                    system("cls");
                    printf("\n\n\t\t\t\t\tIngrese nuevamente la opcion que desea elegir\n");
                    printf("\n\n\t\t\t\t\t\t1:Busqueda por  numero de orden\n");
                    printf("\t\t\t\t\t\t2:busqueda por apellido\n");
                    printf("\t\t\t\t\t\t0:Salir\n\t\t\t\t");
                    fflush(stdin);
                    scanf("%d",&metodoBusqueda);
                }

               busquedaDelCliente(ArchivoCreado,archivoBinario,metodoBusqueda);
               break;
        case 7:system("cls");
               modificarDatos(ArchivoCreado,archivoBinario);
               break;
        case 8:system("cls");
               darDeBaja(ArchivoCreado,archivoBinario);

               break;

        }




        fflush(stdin);
    }while(opcion != 0);
    system("cls");
    printf("\n\n\n\n\t\t\t\t\tUsted a finalizado el sistema\n\n\t\t\t\t\t");
    system("pause");
return 0;
}
