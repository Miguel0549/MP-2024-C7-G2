#include "productos.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
void guardar_producto(producto *v)
{
    FILE *f;
    int i;
    int n_elem=sizeof(*v)/sizeof(producto);
    if ((f=fopen(F_PRODUCTO,"w"))==NULL)
    {
        printf("Error de apertura de fichero.");
    }
    else
    {
        for (i=0;i<n_elem;i++)//Volcado de un elemento
        {
            fputs(v[i].id_prod,f);
            fputc('-',f);
            fputs(v[i].nombre,f);
            fputc('-',f);
            fputs(v[i].descrip,f);
            fputc('-',f);
            fputs(v[i].id_categ,f);
            fputc('-',f);
            fputs(v[i].id_gestor,f);
            fputc('-',f);
            fprintf(f,"%d",v[i].stock);
            fputc('-',f);
            fprintf(f,"%d",v[i].stock);
            fputc('-',f);
            fprintf(f,"%d",v[i].entrega);
            fputc('-',f);
            fprintf(f,"%d",v[i].importe);
            fputc('\n',f);
        }
    }
}
void guardar_categoria(categoria *v)
{
    FILE *f;
    int i;
    int n_elem=sizeof(*v)/sizeof(categoria);
    if ((f=fopen(F_CATEGORIAS,"w"))==NULL)
    {
        printf("Error de apertura de fichero.");
    }
    else
    {
        for (i=0;i<n_elem;i++)//Volcado de un elemento
        {
            fputs(v[i].id_cat,f);
            fputc('-',f);
            fputs(v[i].descrip,f);
            fputc('-',f);
        }
    }
}
int buscar_id_f(FILE **f,char *n)
{
    char d[51];
    char i;
    int j;
    int id=0;
    rewind(*f);
    do{
        id++;
        //Busqueda de comienzo de descripcion
        do{
            i=fgetc(*f);
        
        }while(i!='-');
        //captacion de la cadena
        for(j=0;((i!='-')&&(i!='\n')&&(i!=EOF)&&(j<51))||(j==0);j++){
            i=fgetc(*f);
            d[j]=i;
        }
        d[j-1]='\0';
        //Mueve el cursor hasta la siguiente id
        while(i!=EOF&&i!='\n')
        {
            i=fgetc(*f);
        }

    }while(strcmp(n,d)!=0);//comparacion de cadena actual con la cadena introducida
    return id;
}
