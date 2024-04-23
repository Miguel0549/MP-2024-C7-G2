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
    int Num_comp;
    char cod_locker[7];
    estado est_locker;      // Ocupado o vacio
    char fecha_ocup[11];     // Formato dd/mm/aa
    char fecha_cad[11];      // Formato dd/mm/aa


}CompartimentoLocker;




void carga_lockers( Locker **lock ,int *);
void carga_compartimento_lockers( CompartimentoLocker **c_lock ,int *n_c_lock);

void volcado_lockers ( Locker *l, int *n_lock );
void volcado_comp_lockers ( CompartimentoLocker *c_l, int *n_c_lock );

void siguiente_id_desc_o_lock(char *vect_dest , char *vect_id , char *tipo);

#endif //PROYECTO_MP_LOCKERS_H
