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
    fclose(f);
    //free(v);  
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
            fputc('\0',f);
        }
    }
    fclose(f);
    //free(v);
}
producto * volcar_producto()//No Probada todavia
{
    FILE *f;
    char aux[51];//Cadena auxiliar para rellenar los datos, 51 es el valor de la cadena más larga
    producto *v;
    char j;
    if (v=(producto *)malloc(sizeof(producto))==NULL)
    {
        printf("Error de alocación de memoria.\n");
    }
    else
    {
        if(f=fopen(F_PRODUCTO,"r")==NULL)
        {
            printf("ERROR: No se ha encontrado el fichero Productos.txt, no se ha podido cargar memoria de los productos.\n");
        }
        else
        {
            for(int i=0;j!=EOF;i++)//Bucle para obtener cada dato
            {
                realloc(v,(i+1)*sizeof(producto));
                fgets(v[i].id_prod,8,f);
                fseek(f,1,SEEK_CUR);
                //nombre y descrip varian en tamaño, por lo que fgets leera basura
                obtener_dato_f(&f,v[i].nombre);
                obtener_dato_f(&f,v[i].descrip);
                fgets(v[i].id_categ,5,f);
                fseek(f,1,SEEK_CUR);
                fgets(v[i].id_gestor,5,f);
                fseek(f,1,SEEK_CUR);
                //obtencion de enteros, primero leerlo como cadena y luego pasarlo a entero
                obtener_dato_f(&f,aux);
                v[i].stock=atoi(aux);
                obtener_dato_f(&f,aux);
                v[i].entrega=atoi(aux);
                obtener_dato_f(&f,aux);
                v[i].importe=atoi(aux);
                j=fgetc(f);
            }
        }
        
    }
    return v;
}
categoria * volcar_categoria()//No Probada todavia
{
    FILE *f;
    categoria *v;
    char j;
    if (v=(categoria *)malloc(sizeof(categoria))==NULL)
    {
        printf("Error de alocación de memoria.\n");
    }
    else
    {
        if(f=fopen(F_CATEGORIAS,"r")==NULL)
        {
            printf("ERROR: No se ha encontrado el fichero Categorias.txt, no se ha podido cargar memoria de las categorias.\n");
        }
        else
        {
            for(int i=0;j!=EOF;i++)//Bucle para obtener cada dato
            {
                realloc(v,(i+1)*sizeof(producto));
                fgets(v[i].id_cat,5,f);
                fseek(f,1,SEEK_CUR);
                fgets(v[i].descrip,51,f);//Dejara de leer en EOF o en '/n'
                j=fgetc(f);

            }
        }
    }
}

//FUNCIONES PRIVADAS

//Cabecera: static void obtener_dato_f(FILE **f,char *n)
//Precondicion: El tamaño de n debe ser mayor al dato que se debe introducir, f debe estar abierto en modo lectura y el cursor debe estar situado al principio del dato a leer
//Poscondicion: Almacena en n los caracteres leidos en f hasta que se encuentre '-' o '\n' o EOF y deja el cursor una posicion despues del dato leido
static void obtener_dato_f(FILE **f,char *n)
{

}
//Cabecera: int buscar_id (FILE *f,char *n)
//Precondicion: f debe ser F_PRODUCTO o F_CATEGORIAS y estar abierto para lectura
//poscondicion: Devuelve la id de n dentro del fichero
static int buscar_id_f(FILE **f,char *n)
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
