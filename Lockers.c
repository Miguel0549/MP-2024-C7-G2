#include "Lockers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINEA 100


// Caberea: void carga_lockers( Locker ** )
// Precondicion:
// Postcondicion: Vuelca los datos del fichero en la estructura


void carga_lockers( Locker **lock ,int *n_lock){      // Funciona

    int i;
    char line[LINEA]="0";
    char contador_lineas[LINEA]="0";
    char n_comp_t[3]={0},n_comp_ocup[3]={0};
    char *ptr;

    FILE *f;

    if ((f = fopen("C:\\Users\\migue\\Desktop\\CLASE\\AMAZON_MP\\Proyecto_MP\\Files\\Lockers.txt", "r")) == NULL) {

        printf("Error al abrir el archivo");

    } else {

        while(!feof(f)){

            fgets(contador_lineas,LINEA,f);
            (*n_lock)++;

        }


        *lock = (Locker *)calloc(*n_lock, sizeof(Locker));
        if (*lock == NULL) {
            printf("Error al crear la memoria para los lockers.\n");
            exit(1);
        }

        rewind(f);

       for ( i=0 ; i< *n_lock ; i++ ) {

           fgets(line,LINEA,f);

           strcpy((*lock)[i].id_locker, strtok(line, "-"));
           strcpy((*lock)[i].localidad, strtok(NULL, "-"));
           strcpy((*lock)[i].provincia, strtok(NULL, "-"));
           strcpy((*lock)[i].ubicacion, strtok(NULL, "-"));
           strcpy(n_comp_t, strtok(NULL, "-"));
           strcpy(n_comp_ocup, strtok(NULL, "-"));


           (*lock)[i].Num_compT = strtol(n_comp_t, &ptr, 10);
           (*lock)[i].Num_compOcup = strtol(n_comp_ocup, &ptr, 10);

           strcpy(n_comp_t,"00");
           strcpy(n_comp_ocup,"00");

        }

        rewind(f);
        fclose(f);

    }

}




