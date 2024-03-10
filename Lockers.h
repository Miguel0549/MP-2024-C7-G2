#ifndef PROYECTO_MP_LOCKERS_H
#define PROYECTO_MP_LOCKERS_H

#include "estado.h"

typedef struct {

    char id_locker[10];
    char localidad[20];
    char provincia[20];
    char ubicacion[20];
    int Num_compT;
    int Num_compOcup;

}Locker;

typedef struct {

    char id_locker[10];
    int Num_compT;
    int cod_locker;
    estado est_locker;      // Ocupado o vacio
    char fecha_ocup[8];     // Formato dd/mm/aa
    char fecha_cad[8];      // Formato dd/mm/aa


}CompartimentoLocker;



#endif //PROYECTO_MP_LOCKERS_H
