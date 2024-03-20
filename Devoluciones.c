#include "Devoluciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define LINEA 100

void carga_devoluciones( Devoluciones **dev ,int *n_dev){    // FUNCIONA

    int i,j;
    char line[LINEA]="0";
    char estado[18]="\0";
    char contador_lineas[LINEA]="0";

    FILE *f;

    if ((f = fopen("C:\\Users\\migue\\Desktop\\CLASE\\AMAZON_MP\\Proyecto_MP\\Files\\Devoluciones.txt", "r")) == NULL) {

        printf("Error al abrir el archivo");

    } else {

        while(!feof(f)){

            fgets(contador_lineas,LINEA,f);
            (*n_dev)++;

        }


        *dev = (Devoluciones *)calloc(*n_dev, sizeof(Devoluciones));
        if (*dev == NULL) {
            printf("Error al crear la memoria para las Devoluciones.\n");
            exit(1);
        }

        rewind(f);

        for ( i=0 ; i< *n_dev; i++ ) {

            fgets(line,LINEA,f);

            strcpy((*dev)[i].id_pedido, strtok(line, "-\n"));
            strcpy((*dev)[i].id_prod, strtok(NULL, "-\n"));
            strcpy((*dev)[i].fecha_dev, strtok(NULL, "-\n"));
            strcpy((*dev)[i].motivo, strtok(NULL, "-\n"));
            strcpy(estado, strtok(NULL, "-\n"));

            if (strcmp( estado , "pendiente")==0){

                (*dev)[i].est_dev = pediente;

                strcpy((*dev)[i].fecha_cad, strtok(NULL, "-\n"));

            }else if ( strcmp( estado , "aceptado")==0 ){

                (*dev)[i].est_dev = aceptado;

                strcpy((*dev)[i].fecha_acp, strtok(NULL, "-\n"));

            }else if ( strcmp( estado , "denegado")==0 ){

                (*dev)[i].est_dev = denegado;

            }else if ( strcmp( estado , "enviado")==0 ){

                (*dev)[i].est_dev = enviado;

            }else if ( strcmp(estado,"recibido") == 0) {

                (*dev)[i].est_dev = recibido;

            }else{

                printf("Error al ver el estado de la devolucion");

            }


            for ( j=0 ; j<18 ; j++ ){

                estado[j] = '\0';

            }


        }

        rewind(f);
        fclose(f);

    }

}