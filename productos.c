#include "productos.h"
#include <string.h>
#include <stdio.h>
void alta_producto()//Por hacer
{
    FILE *f;
    char nulo='\n';
    int id;
    if ((f=fopen(F_PRODUCTO,"r+"))!=NULL){
        id=buscar_id(&f,&nulo);
    }
}
int buscar_id(FILE **f,char *n)//Posible error, necesita ser probado
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

    }while(strcmp(n,d)!=0);//comparacion de cadena actual con la cadena introducida
    fclose(*f);
    return id;
}
