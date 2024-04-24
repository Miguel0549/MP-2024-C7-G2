#include "Principal.h"
#include <stdlib.h>


int main(){

    ProductoPedido *p_ped;
    Pedido *ped;
    Locker *l;
    CompartimentoLocker *c_l;
    Devoluciones *dev;
    Cliente *clt;
    Transportista *transp;
    Adminprov *admp;
    Descuentos *desc;
    Descuentos_clientes *desc_cl;

    int pedido=0,pr_ped=0,devoluciones=0,lockers=0,comp_lockers=0,trasp=0,client=0,admin_prov=0,descuento=0,descuento_cl=0,id_usu_act;
    int *n_ped,*n_prod_ped,*n_lock,*n_c_lock,*n_dev,*n_cliente,*n_tranp,*n_admp,*usu_act,*n_prod,*n_cat,*n_desc,*n_desc_cl;
    usu t_usu;
    usu *tipo_usu;

    n_ped=&pedido;
    n_prod_ped=&pr_ped;
    n_lock = &lockers;
    n_c_lock = &comp_lockers;
    n_dev = &devoluciones;
    n_cliente = &client;
    n_tranp = &trasp;
    n_admp = &admin_prov;
    n_desc = &descuento;
    n_desc_cl = &descuento_cl;

    usu_act = &id_usu_act;
    tipo_usu = &t_usu;

    cargar_categoria();
    cargar_producto();
    carga_adminprov(&admp,n_admp);
    carga_cliente(&clt,n_cliente);
    carga_transp(&transp,n_tranp);
    carga_pedidos(&ped,n_ped);
    carga_prod_pedido(ped,&p_ped,n_ped,n_prod_ped);
    carga_lockers(&l,n_lock);
    carga_compartimento_lockers(&c_l,n_c_lock);
    carga_descuentos(&desc,n_desc);
    carga_descuentos_clientes(&desc_cl,n_desc_cl);
    carga_devoluciones(&dev,n_dev);


    //menu_inicio_sesion(&clt,&admp,&transp,n_cliente,n_admp,n_tranp,usu_act,tipo_usu);
    menu_principal(clt,admp,transp,l,c_l,ped,p_ped,dev,desc,desc_cl,n_cliente,n_admp,n_tranp,n_lock,n_c_lock,n_ped,n_prod_ped,n_dev,n_desc,n_desc_cl,admin,2);



    return 0;

}

