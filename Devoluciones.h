#ifndef PROYECTO_MP_DEVOLUCIONES_H
#define PROYECTO_MP_DEVOLUCIONES_H

#include "estado.h"

typedef struct {

    int id_pedido;       // 7 digitos
    int id_prod;         // 7 digitos
    char fecha_dev[8];   // Formato dd/mm/aa
    char motivo[50];
    estado est_dev;      // Pendiente, Aceptado, Denegado, Enviado o Recibido
    char fecha_acp[8];   // Formato dd/mm/aa
    char fecha_cad[8];   // Formato dd/mm/aa

}Devoluciones;



#endif //PROYECTO_MP_DEVOLUCIONES_H
