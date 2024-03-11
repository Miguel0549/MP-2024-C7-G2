#ifndef PRODUCTOS_H
#define PRODUCTOS_H
#define F_PRODUCTO "Productos.txt"
#define F_CATEGORIAS "Categorias.txt"
typedef struct {
    char[51] descrip;
    int id_prod,id_gestor,id_categ,stock,entrega,importe;
}producto;
typedef struct {
    int id_cat;
    char[51] descrip;
}categoria;

//void escritura_producto(producto *p)
//Precondicion: Todas los campos de p deben estar definidos a excepcion de id_prod
//Poscondicion: Escribe en el fichero el nuevo producto, tomando como id la menor disponible
//y devuelve en p.id_prod la id asignada
void escritura_producto(producto *);
//int buscar_id (FILE *f,char *n)
//Precondicion: f debe ser F_PRODUCTO o F_CATEGORIAS y estar abierto para lectura
//poscondicion: Devuelve la id de n dentro del fichero
int buscar_id (FILE *,char *);
#endif