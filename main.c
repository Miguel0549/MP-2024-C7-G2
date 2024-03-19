#include <stdio.h>
#include "Lockers.h"
#include "Pedidos.h"

int main(){

    //Locker *l ;
    //int n_lock=0;
    //int *lock;
    //int i;

    //lock = &n_lock;

    //carga_lockers(&l,lock);

    //for (i=0;i< n_lock ;i++){

    //    printf("Id_Locker: %s\nLocalidad: %s\nProvincia: %s\nUbicacion: %s\nNum_compT: %i\nNum_compOcup: %i\n\n",
    //           l[i].id_locker,
    //           l[i].localidad,
    //           l[i].provincia,
    //           l[i].ubicacion,
    //           l[i].Num_compT,
    //           l[i].Num_compOcup);
//
// }

    ProductoPedido *p_ped;
    Pedido *ped;

    int pedido=0,pr_ped=4,i;
    int *n_ped,*n_prod_ped;

    n_ped=&pedido;
    n_prod_ped=&pr_ped;

   // menu_pedidos(ped,p_ped,n_ped,n_prod_ped,cliente);

    carga_pedidos(&ped,n_ped);

    for ( i=0 ; i<pedido ; i++ ){

        printf("Id_pedido: %s\nFecha_pedido: %s\nid_cliente: %s\nlugar_entrega: %s\nid_locker: %s\nid_cod_prom: %s\n",
               ped[i].id_pedido,
               ped[i].fecha_ped,
               ped[i].id_cliente,
               ped[i].lugar_entrega,
               ped[i].id_locker,
               ped[i].id_cod_prom);

    }





    return 0;
}