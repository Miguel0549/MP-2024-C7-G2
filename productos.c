#include "productos.h"
#include <string.h>
#include <stdio.h>
void escritura_producto(producto *p)
{
    FILE *f;
    char nulo='\n';
    int id;
    if ((f=fopen(F_PRODUCTO,"r+"))!=NULL){
        id=buscar_id(f,&nulo);
    }
}
int buscar_id(FILE *f,char *n)
{
    char d[51];
    char i;
    int j;
    int id=0;
    rewind(f);
    do{
        id++;
        //Busqueda de comienzo de descripcion
        do{
            i=fgetc(f);
        
        }while(i!='-');
        //captacion de la cadena
        do{
            i=fgetc(f);
            d[j]=i;
            j++;
        }while(i!='-'||i!='\n'||i!=EOF);
        d[j-1]='\0';

    }while(strcmp(n,d)!=0);//comparacion
    return id;
}