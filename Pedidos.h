#ifndef PROYECTO_MP_PEDIDOS_H
#define PROYECTO_MP_PEDIDOS_H

#include "estado.h"

typedef struct {

    int id_pedido;           // 7 digitos
    char fecha_ped[8];       // Formato dd/mm/aa
    int id_cliente;          // 7 digitos
    char lugar_entrega[9];   // Domicilio o Locker
    char id_locker[10];      // Lock###
    char id_cod_prom[10];

}Pedido;



typedef struct {

    int id_pedido;            // 7 digitos
    int id_prod;              // 7 digitos
    int unidades;
    char fecha_entrega[8];    // Formato dd/mm/aa
    int importe;
    estado est_pedido;        // enPreparación, enviado, enReparto, enLocker, entregado, devuelto o transportista
    int id_transp;            // 7 digitos
    char id_locker[10];
    int cod_locker;
    char fecha_entr_dev[8];   // Formato dd/mm/aa

}ProductoPedido;


typedef struct {

    int id_transp;     // 4 digitos
    char nombre[20];
    char emal[30];
    char contrasena[15];
    char nombre_empresa[20];
    char ciudad_reparto[20];

}Transportista;

#endif //PROYECTO_MP_PEDIDOS_H
