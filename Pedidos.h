#ifndef PROYECTO_MP_PEDIDOS_H
#define PROYECTO_MP_PEDIDOS_H

#include "estado.h"

typedef struct {

    char id_pedido[8];           // 7 digitos
    char fecha_ped[11];       // Formato dd/mm/aa
    char id_cliente[8];          // 7 digitos
    char lugar_entrega[10];   // Domicilio o Locker
    char id_locker[11];
    char id_cod_prom[11];

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

void fecha_actual( char fecha_act[11]);

void carga_pedidos( Pedido **ped ,int *n_ped);
void carga_prod_pedido( ProductoPedido **pr_ped ,int *n_pr_ped);

void volcado_pedidos ( Pedido *p, int *n_ped );
void volcado_prod_pedidos ( ProductoPedido *pr_p, int *n_pr_ped );

void eliminar_pedido ( Pedido *ped, int indice_ped);
void crear_pedido ( Pedido **ped, int *n_ped , char usu_act[8] );
void modificar_pedido ( Pedido *ped , ProductoPedido *pr_ped, int *n_ped ,int *n_pr_ped, int indice ,usu tipo_usu, char usu_act[8] );
void recoger_pedido( Pedido *ped , ProductoPedido *prod_ped, int *n_pedidos,int *n_pr_ped, char id_cliente[8] , int opcion_pedido , usu tipo_usu );

//void asignar_transportista( Pedido *ped ,ProductoPedido *prod_ped, Transportista *transp, int *n_transp,  int *n_pedidos , int *n_pr_ped , usu tipo_usu , int indice_p , char prov_cliente[21] );
//void asignar_locker( Pedido *ped ,ProductoPedido *prod_ped, Locker *lock, int *n_lock, int *n_pedidos , int *n_pr_ped , usu tipo_usu , int indice_p , char prov_cliente[21] );

void crear_siguiente_id ( int num_digitos, char vect_dest[num_digitos] , char vect_id[num_digitos]);

void menu_pedidos ( Pedido *ped , ProductoPedido *prod_ped ,int *n_pedidos ,int *n_prod_ped, usu tipo_usu );

void menu_pedidos_clientes(Pedido *ped , ProductoPedido *prod_ped, int *n_pedidos, int *n_prod_ped, char id_cliente[8] , usu tipo_usu );
void menu_pedidos_admin(Pedido *ped , ProductoPedido *prod_ped, int *n_pedidos, int *n_pr_ped , usu tipo_usu);
void menu_pedidos_prov(Pedido *ped , ProductoPedido *prod_ped, int *n_pedidos , usu tipo_usu);
void menu_pedidos_transp(Pedido *ped , ProductoPedido *prod_ped, int *n_pedidos , int *n_pr_ped, char id_tr_act[5], usu tipo_usu);

void menu_prod_ped( Pedido *ped, ProductoPedido *pr_p, int *n_ped,int *n_pr_ped , char id_ped[8] ,char id_cliente[8],usu tipo_usu);



#endif //PROYECTO_MP_PEDIDOS_H
