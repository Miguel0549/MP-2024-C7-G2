#include <stdio.h>
#include "Lockers.h"
#include "Pedidos.h"
#include "Devoluciones.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>


int main(){

    ProductoPedido *p_ped;
    Pedido *ped;
    Locker *l;
    CompartimentoLocker *c_l;
    Devoluciones *dev;

    int pedido=0,pr_ped=0,devoluciones=0,lockers=0,comp_lockers=0,i;
    int *n_ped,*n_prod_ped,*n_lock,*n_c_lock,*n_dev;
    char prueba[11];

    n_ped=&pedido;
    n_prod_ped=&pr_ped;
    n_lock = &lockers;
    n_c_lock = &comp_lockers;
    n_dev = &devoluciones;

    carga_pedidos(&ped,n_ped);
    carga_prod_pedido(&p_ped,n_prod_ped);
    carga_lockers(&l,n_lock);
    carga_compartimento_lockers(&c_l,n_c_lock);
    carga_devoluciones(&dev,n_dev);


     menu_pedidos(ped,p_ped,n_ped,n_prod_ped,transportista);

     volcado_devoluciones(dev,n_dev);
     volcado_lockers(l,n_lock);
     volcado_comp_lockers(c_l,n_c_lock);

    return 0;

}

