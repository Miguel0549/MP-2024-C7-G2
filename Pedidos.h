#ifndef PROYECTO_MP_PEDIDOS_H
#define PROYECTO_MP_PEDIDOS_H

#include "estado.h"

typedef struct {

    char id_pedido[8];           // 7 digitos
    char fecha_ped[11];       // Formato dd/mm/aa
    char id_cliente[8];          // 7 digitos
    char lugar_entrega[9];   // Domicilio o Locker
    char id_locker[10];      // Lock###
    char id_cod_prom[10];

}Pedido;



typedef struct {

    char id_pedido[8];            // 7 digitos
    char id_prod[8];              // 7 digitos
    int unidades;
    char fecha_entrega[11];        // Formato dd/mm/aa
    int importe;
    estado est_pedido;            // enPreparación, enviado, enReparto, enLocker, entregado, devuelto o transportista
    char id_transp[5];            // 4 digitos
    char id_locker[11];
    char cod_locker[7];
    char fecha_entr_dev[11];       // Formato dd/mm/aa

}ProductoPedido;


typedef struct {

    char id_transp[5];     // 4 digitos
    char nombre[20];
    char emal[30];
    char contrasena[15];
    char nombre_empresa[20];
    char ciudad_reparto[20];

}Transportista;



void carga_pedidos( Pedido **ped ,int *n_ped);
void carga_prod_pedido( ProductoPedido **pr_ped ,int *n_pr_ped);

void menu_pedidos ( Pedido *ped , ProductoPedido *prod_ped ,int *n_pedidos ,int *n_prod_ped, usu tipo_usu );

void menu_pedidos_clientes(Pedido *ped , ProductoPedido *prod_ped, int *n_pedidos, int *n_prod_ped, char id_cliente[7] );
void menu_pedidos_admin(Pedido *ped , ProductoPedido *prod_ped, int *n_pedidos);
void menu_pedidos_prov(Pedido *ped , ProductoPedido *prod_ped, int *n_pedidos);
void menu_pedidos_transp(Pedido *ped , ProductoPedido *prod_ped, int *n_pedidos);




#endif //PROYECTO_MP_PEDIDOS_H
