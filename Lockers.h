#ifndef PROYECTO_MP_LOCKERS_H
#define PROYECTO_MP_LOCKERS_H

#include "estado.h"

typedef struct {

    char id_locker[11];
    char localidad[20];
    char provincia[20];
    char ubicacion[20];
    int Num_compT;
    int Num_compOcup;

}Locker;

typedef struct {

    char id_locker[11];
    char Num_compT[3];
    char cod_locker[7];
    estado est_locker;      // Ocupado o vacio
    char fecha_ocup[11];     // Formato dd/mm/aa
    char fecha_cad[11];      // Formato dd/mm/aa


}CompartimentoLocker;




void carga_lockers( Locker **lock ,int *);
void carga_compartimento_lockers( CompartimentoLocker **c_lock ,int *n_c_lock);



#endif //PROYECTO_MP_LOCKERS_H
