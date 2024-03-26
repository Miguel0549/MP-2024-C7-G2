#ifndef PRODUCTOS_H
#define PRODUCTOS_H
#define F_PRODUCTO "Productos.txt"
#define F_CATEGORIAS "Categorias.txt"
#include <stdio.h>
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
//Cabecera: producto * volcar_producto()
//Precondicion: 
//poscondicion: Vuelca todos la informacion de los productos en el fichero "Productos.txt", devolviéndolo en un array
producto * volcar_producto();
//Cabecera: void guardar_producto(producto *v)
//Precondicion: v debe de ser una cadena de tipo producto definida de forma dinámica
//Poscondición: Guarda todos los miembros de producto en el fichero "Productos.txt"
void guardar_producto(producto *v);
//Cabecera: categoria * guardar_categoria()
//Precondicion: 
//Poscondición: Guarda todos los miembros de categoria en el fichero "Categorias.txt"
void guardar_categoria(categoria *v);
//Cabecera: void volcar_categoria(categoria *v)
//Precondicion: v debe de ser una cadena de tipo categoria definida de forma dinamica
//Poscondicion: Vuelca toda la informacion de las categorias en el fichero "Categorias.txt", devolviendolo en un array
categoria * volcar_categoria();
//Cabecera: void alta_producto(char *id,producto *v)
//Precondicion: id tiene que ser el identificador del usuario que crea el producto,
//debe existir y ser un administrador/proveedor
//Poscondicion: Lee todos los campos de producto por teclado y los escribe al final del vector,
//otorgandole la proxima id disponible
void alta_producto(char *id,producto *v);
//Cabecera: void baja producto(producto *v)
//Precondicion: v debe apuntar al producto a borrar
//Poscondicion: Borra la informacion de un producto
void baja_producto(producto *v);
//Cabecera: void mod_prod(producto)
//Precondicion: producto.id_prod=id del producto a modificar
//Poscondicion: Cambia los datos del producto con id producto.id_prod
void mod_prod(producto);
//Cabecera: void Busqueda_prod_nombre(char *nombre)
//Precondicion: nombre debe seruna cadena ya definida
//Poscondicion: Escribe por pantalla todos los productos cuya descripcion coincida con nombre
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
//Cabecera: alta_cat(categoria *v)
//Precondicion: v es un vector definido de forma dinamica que contiene todas las categorias registradas
//Poscondicion: Introduce en el vector v una nueva categoria cuya descripcion es introducida por teclado
//y cuya id es la proxima disponible
void alta_cat(categoria *v); 
#endif