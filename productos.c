#include "productos.h"
void escritura_producto(producto *p)
{
    FILE *f;
    int id;
    if ((*f=fopen(F_PRODUCTO,r+))!=NULL){
        //Busqueda de la menor id posible
        id=buscar_id(f,' ');

    }
}