#ifndef PRODUCTOS_H
#define PRODUCTOS_H
#define F_PRODUCTO "Files\\Productos.txt"
#define F_CATEGORIAS "Files\\Categorias.txt"

#include "sesiones.h"

#include <stdio.h>
//REMOVER DESPUES, PERTENECE AL MODULO DE SESIONES

typedef struct {
    char id[8];
    usu perfil_usuario;
}sesion;

typedef struct {
    char nombre[16];
    char descrip[51];
    char id_prod[8];
    char id_gestor[5];
    char id_categ[5];
    int stock,entrega,importe;//Estos valores no pueden tener más de 50 dígitos
}producto;

typedef struct {
    char id_cat[5];
    char descrip[51];
}categoria;


extern producto *array_prod;
extern categoria *array_cat;
extern int tamanio_p,tamanio_c;

//extern producto *array_prod;//Vector de productos el cual se inicializa con volcar_producto y se libera con guardar_producto.
//extern categoria *array_cat;//Vector de categorias el cual se inicializa con volcar_categoria y se libera con guardar_categoria.
//extern int tamanio_p,tamanio_c;//Enteros utilizados para almacenar el tamaño del producto y categoria
//Cabecera: void menu_cliente_prod (producto **p,categoria **c,int *tamanio_p, int *tamanio_c);
//Precondicion: p y c deben estar previamente definidos mediante las funciones volcar_producto y volcar_categoria
//Poscondicion: Muestra en pantalla el menu de productos para el cliente
char menu_cliente_prod ();
//Cabecera: void menu_adminprov_prod (producto **p,categproa *c,int *tamanio_p,int tamanio_c,sesion ses)
//Precondicion: sesion debe ser un administrador o proveedor y estar registrado en el sistema
//Poscondicion: Muestra en pantalla el menu de productos para el administrador o proveedor y muestra los productos asociados a esa sesion
void menu_adminprov_prod (sesion ses);
//Cabecera: producto * volcar_producto()
//Precondicion: 
//poscondicion: Vuelca todos la informacion de los productos en el fichero "Productos.txt", devolviéndolo en un array
void cargar_producto();
//Cabecera: void guardar_producto(producto *v)
//Precondicion: v debe de ser una cadena de tipo producto definida de forma dinámica
//Poscondición: Guarda todos los miembros de producto en el fichero "Productos.txt"
void guardar_producto();
//Cabecera: categoria * guardar_categoria()
//Precondicion: 
//Poscondición: Guarda todos los miembros de categoria en el fichero "Categorias.txt"
void guardar_categoria();
//Cabecera: void volcar_categoria(categoria *v)
//Precondicion: v debe de ser una cadena de tipo categoria definida de forma dinamica
//Poscondicion: Vuelca toda la informacion de las categorias en el fichero "Categorias.txt", devolviendolo en un array
void cargar_categoria();
//Cabecera: void alta_producto(char *id,producto *v)
//Precondicion: El usuario actual debe ser administrador/proveedor.
//Poscondicion: Lee todos los campos de producto por teclado y los escribe al final del vector,
//otorgandole la proxima id disponible
void alta_producto( char *id , int *n_admpr);
//Cabecera: void mod_prod(producto)
//Precondicion: producto.id_prod=id del producto a modificar
//Poscondicion: Cambia los datos del producto con id producto.id_prod
void mod_prod(producto);
//Cabecera: void Busqueda_prod_nombre(char *nombre)
//Precondicion: nombre debe ser una cadena ya definida
//Poscondicion: Escribe por pantalla todos los productos cuyo nombre coincida con n
void Busqueda_prod_nombre(char *n);
//cabecera: void Busqueda_prod_cat(char *id)
//Precondicion: id debe pertenecer a una categoria
//Poscondicion: Escribe por pantalla todos los productos 
//que pertenecen a la categoria con identificador id
void Busqueda_prod_cat(char *id);
//Cabecera: alta_categoria(categoria *v)
//Precondicion: v es un vector definido de forma dinamica que contiene todas las categorias registradas
//Poscondicion: Introduce en el vector v una nueva categoria cuya descripcion es introducida por teclado
//y cuya id es la proxima disponible
void alta_categoria(); 
//Cabecera: void baja_categoria(categoria **c,int *tamanio_c);
//Precondicion: El usuario actual debe ser administrador
//Poscondcion: Borra la categoria que especifique el usuario y ajusta el vector de acuerdo a ello
void baja_categoria();
//Cabecera: void idacat(char *descrip,categoria *c,char *id)
//Precondicion: id deben ser 4 "digitos" sin signo, terminado en '\0'. No puede ser "0000"
//Poscondicion: Devuelve en descrip v.descripcion del elemento de v cuya id coincida con v.id_cat.
//Si no se encuentra, se devuelve en descrip "-\0";
int idacat(char *descrip,char *id);
//Cabecera: cataid(char *id,categoria *c,char *descrip,int tamanio)
//Precondicion: descrip debe estar definido y tener 51 elementos, el final de la cadena debe terminar en '\0'
//Poscondicion: Devuelve en id la c.id_cat de la categoria cuyo c.descrip coincida con descrip.
void cataid(char *id,char *descrip);
//Cabecera: menu_admin_cat();
//Precondicion: El usuario actual debe ser un administrador
//Poscondicion: Muestra por pantalla un menu el cual el usuario puede dar de alta, modificar o borrar cualquier categoria
void menu_admin_cat();
void menu_modificar_producto (int indice);
void borrar_producto(int indice);

void menu_cliente_producto_conpedido( Pedido **ped , ProductoPedido **prod_ped , int *n_ped , int *n_pr_ped , char id_cliente[8] );
int reducir_stock(char *id,int resta);

#endif