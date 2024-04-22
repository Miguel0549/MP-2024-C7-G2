#ifndef PROYECTO_MP_PRINCIPAL_H
#define PROYECTO_MP_PRINCIPAL_H

#include "productos.h"

void menu_principal ( Cliente *client , Adminprov *admp , Transportista *transp , Locker *lock , CompartimentoLocker *c_lock , Pedido *ped, ProductoPedido *pr_p , Devoluciones *dev , Descuentos *desc, Descuentos_clientes *desc_cl, int *n_cliente, int *n_admp , int *n_transp , int *n_lock , int *n_c_lock , int *n_ped , int *n_pr_p , int *n_dev ,int *n_desc,int *n_desc_cl, usu tipo_usu, int id_usu_act );
void menu_principal_cliente ( Cliente *client , Adminprov *admp , Transportista *transp , Locker *lock , CompartimentoLocker *c_lock , Pedido *ped, ProductoPedido *pr_p , Devoluciones *dev , producto *prod, categoria *cat, Descuentos *desc, Descuentos_clientes *desc_cl, int *n_cliente, int *n_admp , int *n_transp , int *n_lock , int *n_c_lock , int *n_ped , int *n_pr_p , int *n_dev ,int *n_prod,int *n_cat,int *n_desc,int *n_desc_cl, usu tipo_usu, int id_usu_act);
void menu_principal_admin ( Cliente *client , Adminprov *admp , Transportista *transp , Locker *lock , CompartimentoLocker *c_lock , Pedido *ped, ProductoPedido *pr_p , Devoluciones *dev , producto *prod, categoria *cat, Descuentos *desc, Descuentos_clientes *desc_cl, int *n_cliente, int *n_admp , int *n_transp , int *n_lock , int *n_c_lock , int *n_ped , int *n_pr_p , int *n_dev ,int *n_prod,int *n_cat,int *n_desc,int *n_desc_cl, usu tipo_usu, int id_usu_act);
void menu_principal_proveedor ( Cliente *client , Adminprov *admp , Transportista *transp , Locker *lock , CompartimentoLocker *c_lock , Pedido *ped, ProductoPedido *pr_p , Devoluciones *dev , producto *prod, categoria *cat, Descuentos *desc, Descuentos_clientes *desc_cl, int *n_cliente, int *n_admp , int *n_transp , int *n_lock , int *n_c_lock , int *n_ped , int *n_pr_p , int *n_dev ,int *n_prod,int *n_cat,int *n_desc,int *n_desc_cl, usu tipo_usu, int id_usu_act );
void menu_principal_transportista ( Cliente *client , Adminprov *admp , Transportista *transp , Locker *lock , CompartimentoLocker *c_lock , Pedido *ped, ProductoPedido *pr_p , Devoluciones *dev , producto *prod, categoria *cat, Descuentos *desc, Descuentos_clientes *desc_cl, int *n_cliente, int *n_admp , int *n_transp , int *n_lock , int *n_c_lock , int *n_ped , int *n_pr_p , int *n_dev ,int *n_prod,int *n_cat,int *n_desc,int *n_desc_cl, usu tipo_usu, int id_usu_act);

void datos_admin_prov( Adminprov *admpr , int ind_admpr);
void modificar_admin ( Adminprov **admpr , int ind_admpr);
void listado_cliente ( Cliente *clt , int *n_clt );
void listado_adminprov_prod( Adminprov *admpr , producto *prod , int *n_admpr , int *n_prod );
void modificar_proveedor ( Adminprov *prov, int id_act );
void listado_prod_ext ( Adminprov *adminprov , producto *prod , int *n_admpr , int * n_prod );
void listado_prod ( Adminprov *admpr , producto *prod, int *n_prod ,int *n_admpr ,int ind_admpr , usu tipo_usu );
void listado_proveedores ( Adminprov *admpr , int *n_admpr , usu tipo_usu);

void borrar_adminprov_con_id(Adminprov**,char*,int*);


#endif //PROYECTO_MP_PRINCIPAL_H
