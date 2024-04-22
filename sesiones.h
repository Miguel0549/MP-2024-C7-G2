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
void nuevo_adminprov(Adminprov **,int *, usu );