#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED


//FUNCION QUE ABRE UN ARCHIVO DE TEXTO Y LO MUESTRA EN PANTALLA
void leerDatosCSV(FILE *pArchivo);
void leer(char *linea,int *orden, char *nombre,float *importe,char *tipoCredito,int *dia, int *mes ,int *ano ,int *nroCutoas, float *importeCuotas ,float *IVA, float *totalCuotas);
void crearArchivo(FILE *ArchivoCreado,char archivoBinario[]);
void migrar(FILE *pArchivo, FILE *archivoCreado , char *archivoBinario);
void mayusculizador(char *mayus);


void imprimirTodo(FILE *ArchivoCreado,char archivoBinario[]);
void imprimirActivos(FILE *ArchivoCreado,char *archivoBinario) ;
void imprimirPorTipo(FILE *ArchivoCreado,char archivoBinario[],char *tipoCredito);
void agregarCliente(FILE *archivoCreado,char archivoBinario[]);
void busquedaDelCliente(FILE *archivoCreado,char archivoBinario[],int metodoBusqueda);
void modificarDatos(FILE *archivoCreado, char *archivoBinario);
void darDeBaja(FILE *archivoCreado, char *archivoBinario);
#endif // FUNCIONES_H_INCLUDED
