#include "Devoluciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define LINEA 100

void carga_devoluciones( Devoluciones **dev ,int *n_dev){    // Sin probar

    int i;
    char line[LINEA]="0";
    char estado[18];
    char contador_lineas[LINEA]="0";

    FILE *f;

    if ((f = fopen("C:\\Users\\migue\\Desktop\\CLASE\\AMAZON_MP\\Proyecto_MP\\Files\\Pedidos.txt", "r")) == NULL) {

        printf("Error al abrir el archivo");

    } else {

        while(!feof(f)){

            fgets(contador_lineas,LINEA,f);
            (*n_dev)++;

        }


        *dev = (Devoluciones *)calloc(*n_dev, sizeof(Devoluciones));
        if (*dev == NULL) {
            printf("Error al crear la memoria para los lockers.\n");
            exit(1);
        }

        rewind(f);

        for ( i=0 ; i< *n_dev; i++ ) {

            fgets(line,LINEA,f);

            strcpy((*dev)[i].id_pedido, strtok(line, "-"));
            strcpy((*dev)[i].id_prod, strtok(NULL, "-"));
            strcpy((*dev)[i].fecha_dev, strtok(NULL, "-"));
            strcpy((*dev)[i].motivo, strtok(NULL, "-"));
            strcpy(estado, strtok(NULL, "-"));

            if (strcmp( estado , "pendiente")==0){

                (*dev)[i].est_dev = pediente;

            }else if ( strcmp( estado , "aceptado")==0 ){

                (*dev)[i].est_dev = aceptado;

            }else if ( strcmp( estado , "denegado")==0 ){

                (*dev)[i].est_dev = denegado;

            }else if ( strcmp( estado , "enviado")==0 ){

                (*dev)[i].est_dev = enviado;

            }else if ( strcmp(estado,"recibido") == 0) {

                (*dev)[i].est_dev = recibido;

            }else{

                printf("Error al ver el estado de la devolucion");

            }



        }

        rewind(f);
        fclose(f);

    }

}