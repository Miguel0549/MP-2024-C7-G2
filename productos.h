#ifndef PRODUCTOS_H
#define PRODUCTOS_H
#define F_PRODUCTO "Productos.txt"
#define F_CATEGORIAS "Categorias.txt"

#include <stdio.h>
//REMOVER DESPUES, PERTENECE AL MODULO DE SESIONES
typedef enum {administrador,proveedor,cliente}perfil;
typedef struct {
    char id[8];
    perfil perfil_usuario;
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
extern producto *array_prod;//Vector de productos el cual se inicializa con volcar_producto y se libera con guardar_producto.
extern categoria *array_cat;//Vector de categorias el cual se inicializa con volcar_categoria y se libera con guardar_categoria.
extern int tamanio_p,tamanio_c;//Enteros utilizados para almacenar el tamaño del producto y categoria
//Cabecera: void menu_cliente_prod (producto **p,categoria **c,int *tamanio_p, int *tamanio_c);
//Precondicion: p y c deben estar previamente definidos mediante las funciones volcar_producto y volcar_categoria
//Poscondicion: Muestra en pantalla el menu de productos para el cliente
void menu_cliente_prod (producto *p,categoria *c,int tamanio_p,int tamanio_c);
//Cabecera: void menu_adminprov_prod (producto **p,categproa *c,int *tamanio_p,int tamanio_c,sesion ses)
//Precondicion: sesion debe ser un administrador o proveedor y estar registrado en el sistema
//Poscondicion: Muestra en pantalla el menu de productos para el administrador o proveedor y muestra los productos asociados a esa sesion
void menu_adminprov_prod (producto **p,categoria *c,int *tamanio_p,int tamanio_c,sesion ses);
//Cabecera: producto * volcar_producto()
//Precondicion: 
//poscondicion: Vuelca todos la informacion de los productos en el fichero "Productos.txt", devolviéndolo en un array
producto * volcar_producto(int *tamanio);
//Cabecera: void guardar_producto(producto *v)
//Precondicion: v debe de ser una cadena de tipo producto definida de forma dinámica
//Poscondición: Guarda todos los miembros de producto en el fichero "Productos.txt"
void guardar_producto(producto *v,int n_elem);
//Cabecera: categoria * guardar_categoria()
//Precondicion: 
//Poscondición: Guarda todos los miembros de categoria en el fichero "Categorias.txt"
void guardar_categoria(categoria *v,int n_elem);
//Cabecera: void volcar_categoria(categoria *v)
//Precondicion: v debe de ser una cadena de tipo categoria definida de forma dinamica
//Poscondicion: Vuelca toda la informacion de las categorias en el fichero "Categorias.txt", devolviendolo en un array
categoria * volcar_categoria(int *tamanio);
//Cabecera: void alta_producto(char *id,producto *v)
//Precondicion: El usuario actual debe ser administrador/proveedor.
//Poscondicion: Lee todos los campos de producto por teclado y los escribe al final del vector,
//otorgandole la proxima id disponible
void alta_producto(categoria *c,producto **v,int *tamanio_p,int tamanio_c,char *id);
//Cabecera: void mod_prod(producto)
//Precondicion: producto.id_prod=id del producto a modificar
//Poscondicion: Cambia los datos del producto con id producto.id_prod
void mod_prod(producto);
//Cabecera: void Busqueda_prod_nombre(char *nombre)
//Precondicion: nombre debe seruna cadena ya definida
//Poscondicion: Escribe por pantalla todos los productos cuyo nombre coincida con n
void Busqueda_prod_nombre(char *n);
//cabecera: void Busqueda_prod_cat(char *id)
//Precondicion: id debe pertenecer a una categoria
//Poscondicion: Escribe por pantalla todos los productos 
//que pertenecen a la categoria con identificador id
void Busqueda_prod_cat(char *id);
//Cabecera: producto cargar_prod(char *id)
//Precondicion: id debe ser una id de un producto registrado
//Poscondicion: Devuelve todo la informacion del producto con identificador id
producto cargar_prod(char *id);
//Cabecera: alta_categoria(categoria *v)
//Precondicion: v es un vector definido de forma dinamica que contiene todas las categorias registradas
//Poscondicion: Introduce en el vector v una nueva categoria cuya descripcion es introducida por teclado
//y cuya id es la proxima disponible
void alta_categoria(categoria **v,int *tamanio); 
//Cabecera: void baja_categoria(categoria **c,int *tamanio_c);
//Precondicion: El usuario actual debe ser administrador
//Poscondcion: Borra la categoria que especifique el usuario y ajusta el vector de acuerdo a ello
void baja_categoria(categoria **c,int *tamanio,producto *p);
//Cabecera: void idacat(char *descrip,categoria *c,char *id)
//Precondicion: id deben ser 4 "digitos" sin signo, terminado en '\0'. No puede ser "0000"
//Poscondicion: Devuelve en descrip v.descripcion del elemento de v cuya id coincida con v.id_cat.
//Si no se encuentra, se devuelve en descrip "-\0";
void idacat(char *descrip,categoria *c,char *id,int tamanio);
//Cabecera: cataid(char *id,categoria *c,char *descrip,int tamanio)
//Precondicion: descrip debe estar definido y tener 51 elementos, el final de la cadena debe terminar en '\0'
//Poscondicion: Devuelve en id la c.id_cat de la categoria cuyo c.descrip coincida con descrip.
void cataid(char *id,categoria *c,char *descrip,int tamanio);
#endif