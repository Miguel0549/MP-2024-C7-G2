#include <stdio.h>
#include "Lockers.h"
#include "Pedidos.h"
#include <stdlib.h>

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

    int pedido=0,pr_ped=0,i;
    int *n_ped,*n_prod_ped;

    n_ped=&pedido;
    n_prod_ped=&pr_ped;

    carga_pedidos(&ped,n_ped);
    carga_prod_pedido(&p_ped,n_prod_ped);

   // menu_pedidos(ped,p_ped,n_ped,n_prod_ped,cliente);


    for ( i=0 ; i< pr_ped ; i++ ){

        printf("Id_pedido: %s\nId_prod: %s\nunidades: %i\nfecha_entrega: %s\nimporte: %i\nestado_pedido: %u\nid_trasp: %s\nid_lock: %s\ncod_lock: %s\nfecha_entr_dev: %s",
               p_ped[i].id_pedido,
               p_ped[i].id_prod,
               p_ped[i].unidades,
               p_ped[i].fecha_entrega,
               p_ped[i].importe,
               p_ped[i].est_pedido,
               p_ped[i].id_transp,
               p_ped[i].id_locker,
               p_ped[i].cod_locker,
               p_ped[i].fecha_entr_dev);



    }





}

