#ifndef PROYECTO_MP_DEVOLUCIONES_H
#define PROYECTO_MP_DEVOLUCIONES_H

#include "estado.h"

typedef struct {

    char id_pedido[8];       // 7 digitos
    char id_prod[8];         // 7 digitos
    char fecha_dev[11];   // Formato dd/mm/aa
    char motivo[51];
    estado est_dev;      // Pendiente, Aceptado, Denegado, Enviado o Recibido
    char fecha_acp[11];   // Formato dd/mm/aa
    char fecha_cad[11];   // Formato dd/mm/aa

}Devoluciones;


void carga_devoluciones( Devoluciones **dev ,int *n_dev);


#endif //PROYECTO_MP_DEVOLUCIONES_H
