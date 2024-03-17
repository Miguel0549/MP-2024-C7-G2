#include "Pedidos.h"
#include <stdio.h>
#include "estado.h"

void menu_pedidos ( Pedido **ped , int *n_pedidos , usu tipo_usu ){

    int i;
    char opcion[9];

    switch (tipo_usu) {


        case cliente:

            printf("--------- Sus pedidos realizados ---------\n\n");



            break;
        case admin:

            printf("--------- Todos los pedidos ---------\n\n");

            for (i=0 ; i<*n_pedidos ; i++ ){

                printf("[%i].%s-%s-%s-%s-%s-%s\n",i,(*ped)[i].id_pedido,
                                                           (*ped)[i].fecha_ped,
                                                           (*ped)[i].id_cliente,
                                                           (*ped)[i].lugar_entrega,
                                                           (*ped)[i].id_locker,
                                                           (*ped)[i].id_cod_prom);

                printf("Escriba por pantalla lo que desea hacer (alta , baja , modificar ):");
                scanf("%s",opcion);
            }
            break;
        case proveedor:
            break;
        case transportista:
            break;
    }







}