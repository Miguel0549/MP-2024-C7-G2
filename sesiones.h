#include "descuentos.h"

typedef struct
{
    char Id_empresa[5];
    char Nombre[21];
    char email[31];
    char Contrasenna[16];
    usu Perfil_usuario;

}Adminprov;


void menu_inicio_sesion ( Cliente *client , Adminprov *admp , Transportista *transp , int *n_cliente, int *n_admp , int *n_transp , int *usu_act , usu *tipo_usu );

void inicio_sesion ( Cliente *client , Adminprov *admp , Transportista *transp, int *n_cliente, int *n_admp , int *n_transp , int *usu_act , usu *tipo_usu);
void registro ( Cliente *client , Adminprov *admp , Transportista *transp, int *n_cliente, int *n_admp , int *n_transp );

void inicio_sesion_cliente ( Cliente *client , int *n_cliente , int *usu_act);
void inicio_sesion_admin (  Adminprov *admp ,  int *n_admp , int *usu_act );
void inicio_sesion_proveedor ( Adminprov *admp ,  int *n_admp , int *usu_act );
void inicio_sesion_transportista (  Transportista *transp , int *n_transp , int *usu_act);

void menu_principal ( Cliente *client , Adminprov *admp , Transportista *transp , Locker *lock , CompartimentoLocker *c_lock , Pedido *ped, ProductoPedido *pr_p , Devoluciones *dev , int *n_cliente, int *n_admp , int *n_transp , int *n_lock , int *n_c_lock , int *n_ped , int *n_pr_p , int *n_dev , usu tipo_usu , int id_usu_act );
void menu_principal_cliente ( Cliente *client , Adminprov *admp , Transportista *transp , Locker *lock , CompartimentoLocker *c_lock , Pedido *ped, ProductoPedido *pr_p , Devoluciones *dev , int *n_cliente, int *n_admp , int *n_transp , int *n_lock , int *n_c_lock , int *n_ped , int *n_pr_p , int *n_dev , usu tipo_usu, int id_usu_act);
void menu_principal_admin ( Cliente *client , Adminprov *admp , Transportista *transp , Locker *lock , CompartimentoLocker *c_lock , Pedido *ped, ProductoPedido *pr_p , Devoluciones *dev , int *n_cliente, int *n_admp , int *n_transp , int *n_lock , int *n_c_lock , int *n_ped , int *n_pr_p , int *n_dev , usu tipo_usu, int id_usu_act);
void menu_principal_proveedor ( Cliente *client , Adminprov *admp , Transportista *transp , Locker *lock , CompartimentoLocker *c_lock , Pedido *ped, ProductoPedido *pr_p , Devoluciones *dev , int *n_cliente, int *n_admp , int *n_transp , int *n_lock , int *n_c_lock , int *n_ped , int *n_pr_p , int *n_dev , usu tipo_usu, int id_usu_act);
void menu_principal_transportista ( Cliente *client , Adminprov *admp , Transportista *transp , Locker *lock , CompartimentoLocker *c_lock , Pedido *ped, ProductoPedido *pr_p , Devoluciones *dev , int *n_cliente, int *n_admp , int *n_transp , int *n_lock , int *n_c_lock , int *n_ped , int *n_pr_p , int *n_dev , usu tipo_usu, int id_usu_act);



    /*FUNCIONES ADMINPROV*/
//cabecera void carga_Adminprov(Adminprov**)
//precondición:fichero inicializado
//postcondición:carga en el doble puntero a estructura adminprov la información del fichero
void carga_adminprov(Adminprov**,int*);

//cabecera void volcado_adminprov(Adminprov**)
//precondición:fichero y vector de estrtuctuas inicializados
//postcondición:vuelca al fiichero la información del vector de estructuras
void volcado_adminprov(Adminprov**,int*);

//cabecera: void nuevo_adminprov(Adminprov **,int *);
//precondición: **a doble puntero a estructura inicializado y *n_adminprov puntero que apunta al numero actual de admin/proveedores
//postcondición: amplia el vector de estructuras e inicializa desde entrada de teclado un nuevo admin/proveedor
void nuevo_adminprov(Adminprov **,int *);

// cabecera: void de_int_a_id_empresa(int i_id, char * s_id)
// precondicion: i_id es un numero de 4 digitos como máximo
// postcondicion: convierte el entero i_id en un string s_id
void de_int_a_id_empresa(int i_id, char* s_id);