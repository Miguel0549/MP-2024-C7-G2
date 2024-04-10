#ifndef PROYECTO_MP_DEVOLUCIONES_H
#define PROYECTO_MP_DEVOLUCIONES_H

#include "estado.h"
#include "Pedidos.h"

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
void volcado_devoluciones ( Devoluciones *d, int *n_dev );

void crear_devolucion( Pedido *ped, ProductoPedido *prod_ped, Devoluciones **dev, int *n_dev, int *n_pedidos, int *n_prod_ped );
void eliminar_devolucion ( Devoluciones *dev , int indice_dev);

void menu_devoluciones ( Pedido *ped, ProductoPedido *prod_ped, Devoluciones *dev, int *n_dev, int *n_pedidos, int *n_prod_ped, usu tipo_usu );

void menu_devoluciones_clientes ( Pedido *ped, ProductoPedido *prod_ped, Devoluciones *dev, int *n_dev, int *n_pedidos, int *n_prod_ped, char id_cliente[7], usu tipo_u);
void menu_devoluciones_admin ( Pedido *ped, ProductoPedido *prod_ped, Devoluciones *dev, int *n_dev, int *n_pedidos, int *n_prod_ped, usu tipo_u);
void menu_devoluciones_transportistas ( Pedido *ped, ProductoPedido *prod_ped, Devoluciones *dev, int *n_dev, int *n_pedidos, int *n_prod_ped,char id_transp[5], usu tipo_u);


#endif //PROYECTO_MP_DEVOLUCIONES_H
