#include "productos.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//TODO: implementacion de categoria. Temporalmente tendran todas 1 hasta desarrollo de categoria.
void alta_producto(categoria *c,producto *v)//Por probar
{
    int tamanio=TAMANIO_PROD(*v),error;
    char salida='n',carga='n',aux[8];
    producto p;//Auxiliar para guardar temporalmente el producto nuevo
    printf("Comienzo de registro de un producto.\n");
    do{
        printf("Escribe el nombre del producto (no puede contener -,maximo 15 caracteres)\nNombre: ");
        fgets(p.nombre,16,stdin);
        printf("\nEscribe una descripcion del producto (no puede contener -,maximo 50 caracteres)\nDescripcion: ");
        fgets(p.descrip,51,stdin);
        lista_cat(c);
        printf("Escribe el identificador de la categoria que quieras asociar al producto.\nCategoria: ");
        fgets(p.id_categ,5,stdin);
        printf("\nEscribe el stock inicial del producto.\nStock: ");
        scanf("%d",&p.stock);
        printf("\nEscribe la cantidad de dias de compromiso de entrega.\nEntrega: ");
        scanf("%d",&p.entrega);
        printf("\nEscribe el importe en euros de cada producto.\nImporte: ");
        scanf("%d",&p.importe);
        if((cadena_valida(p.nombre,16)!=0)&&(cadena_valida(p.descrip,51)!=0)&&(p.stock!=EOF)&&(p.entrega!=EOF)&&(p.importe!=EOF))//Comprobacion de los datos
        {
            printf("\nDatos introducidos no validos.\n");
            error=1;
        }
        else
        {
            printf("\nRecopilacion de los datos.\n");
            printf("Nombre: %s\n",p.nombre);
            printf("Descripcion: %s\n",p.descrip);
            printf("Stock inicial: %d unidades\n",p.stock);
            printf("Compromiso de entrega: %d dias\n",p.entrega);
            printf("Importe: %d euros\n",p.importe);
            printf("¿Es la informacion correcta? Escriba s para confirmar.\n");
            carga=getchar();
            if (carga=='s')
            {
                //REMOVER DESPUES
                strcpy(p.id_gestor,"0001\0");
                //REMOVER DESPUES
                //p.id_gestor=usuario_actual().id;
                //Obtencion de la proxima id disponible
                strcpy(aux,v[tamanio-1].id_prod);
                suma1(aux,7);//Suma a la cadena 1
                strcpy(p.id_prod,aux);
                //Subida del producto al vector
                if(realloc(v,(tamanio+1)*(sizeof(producto)))!=NULL)//agrega espacio al vector para poner el nuevo producto
                {
                    v[tamanio]=p;
                    error=0;
                    salida='s';
                }
                else
                {
                    printf("Se ha producido un error en la carga del producto.\n");
                    error=2;
                }
            }
            else
            {
                printf("Alta de producto abortada.\n");
                error=3;
            }
        }
        if(error!=0)
        {
            printf("¿Desea cancelar el alta? Escriba s para salir.\n");
            salida=getchar();
        }
    }while(salida!='s');
    if(error!=0)
    {
        printf("Alta de producto fallida. Error: %d.\n",error);
    }
    else
    {
        printf("Alta de producto con exito.\n");
    }
}
void alta_categoria(categoria *v)//Por probar
{
    int error,tamanio=TAMANIO_CAT(*v);
    categoria c;
    char salida,carga,aux[5];
    printf("Comienzo de alta de una categoria.\n");
    do{
        printf("Escribe la descripcion de la categoria.\n Esta no puede contener guiones o ser mayor de 51 caracteres.\n");
        fgets(c.descrip,51,stdin);
        if (cadena_valida(c.descrip,51)==0)
        {
            printf("\nDatos introducidos no validos.\n");
            error=1;
        }
        else
        {
            printf("\nConfirmacion de los datos.\n");
            printf("Decricpcion: %s\n",c.descrip);
            printf("Desea confirmar la categoria? Escriba s para confirmar.\n");
            carga=getchar();
            if (carga=='s')
            {
                //Obtencion de la proxima id
                strcpy(aux,v[tamanio-1].id_cat);
                suma1(aux,4);
                strcpy(c.id_cat,aux);
                if (realloc(v,(tamanio+1)*sizeof(categoria))==NULL)
                {
                    printf("Error de memoria.\n");
                    error=2;
                }
                else
                {
                    v[tamanio]=c;
                    error=0;
                    salida='s';
                }
            }
            else
            {
                printf("Alta de categoria abortada.\n");
                error=3;
            }
        }
        if (error!=0)
        {
            printf("¿Desea cancelar el alta? Escriba 's' para salir.\n");
            salida=getchar();
        }
    }while(salida=='s');
    if (error==0)
    {
        printf("Alta de categoria con exito.\n");
    }
    else
    {
        printf("Alta de categoria fallida. Error: %d",error);
    }
}
void guardar_producto(producto *v)
{
    FILE *f;
    int i;
    int n_elem=TAMANIO_PROD(*v);
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
    int n_elem=TAMANIO_CAT(*v);
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
                realloc(v,(i+1)*sizeof(categoria));
                fgets(v[i].id_cat,5,f);
                fseek(f,1,SEEK_CUR);
                fgets(v[i].descrip,51,f);//Dejara de leer en EOF o en '/n'
                j=fgetc(f);

            }
        }
    }
}
void idacat(char *descrip,categoria *c,char *id)
{
    descrip[0]='-';
    descrip[1]='\0';
    int tamanio=TAMANIO_CAT(*c),encontrado=1;
    for (int i=0;(i<tamanio)||(encontrado);i++)
    {
        if (strcmp(c[i].id_cat,id))
        {
            strcpy(descrip,c[i].descrip);
            encontrado=0;
        }
    }
}

//FUNCIONES PRIVADAS

//Cabecera: static void obtener_dato_f(FILE **f,char *n)
//Precondicion: El tamaño de n debe ser mayor al dato que se debe introducir, f debe estar abierto en modo lectura y el cursor debe estar situado al principio del dato a leer
//Poscondicion: Almacena en n los caracteres leidos en f hasta que se encuentre '-' o '\n' o EOF y deja el cursor una posicion despues del dato leido
static void obtener_dato_f(FILE **f,char *n)//Por probar todavia
{
    int i;
    char j;
    for (i=0;(j!='-')&&(j!='\n')&&(j!=EOF)||(i==0);i++)
    {
        j=fgetc(*f);
        n[i]=j;
    }
    n[i-1]='\0';
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
//Cabecera: static void suma1(char *s,int i)
//Precondicion: La cadena s tiene que tener mayor tamaño que i.
//i tiene que ser el numero de digitos de la cadena
//Poscondicon: Suma 1 en base 10 a s de i digitos.
static void suma1(char *s,int i)
{
    for (int j=0;(i>=0)||(j==1);i--)
    {
        if (s[i]=='9')
        {
            s[i]='0';
        }
        else
        {
            s[i]++;
            j=1;
        }
    }
}
//Cabecera: static int cadena_valida(char *v,int size)
//Precondicion: v tiene que ser una cadena obtenida mediante fgets y size el tamaño de la cadena
//Poscondicion: Devuelve 0 si la cadena cumple con las restricciones y devuelve distinto de 0 si se produce un error 
//y establece '/n' como fin de la cadena, si lo hay.
static int cadena_valida(char *v,int size)
{
    int error=0;
    int i;
    for (i=0;(i<size)||(error!=0)||(v[i]=='\0');i++)
    {
        if(v[i]=='-')
        {
            error=1;
        }
    }
    if (v[i-1]=='\n')
    {
        v[i-1]=='\0';
    }
    return error;
}
//Cabecera: static void lista_prod(producto *lista,categoria *c)
//Precondicion: Todos los campos de lista y c deben estar inicializados
//Poscondicion: Imprime por pantalla lista como una lista de los productos
static void lista_prod(producto *lista,categoria *c)
{
    int tamanio=TAMANIO_PROD(*lista);
    char descrip_cat[51];//auxiliar para guardar la descripcion de la categoria
    printf("-------------------------------------------------------\n");
    for(int i=0;i<tamanio;i++)
    {
        idacat(descrip_cat,c,lista[i].id_categ);
        printf("Nombre: %s\n",lista[i].nombre);
        printf("Descripcion: %s\n",lista[i].descrip);
        printf("Categoria: %s\n",descrip_cat);
        printf("Precio: %d€\n",lista[i].importe);
        printf("Stock: %d unidades\n",lista[i].stock);
        printf("Entrega en %d dias\n",lista[i].entrega);
        printf("Identificador: %s\n",lista[i].id_prod);
        printf("-------------------------------------------------------\n");
    }
}
//Cabecera: static void lista_cat(categoria *lista)
//Precondicion: Todos los campos de lista deben estar inicializados
//Poscondicon: Imprime por pantalla lista como una lista de las categorias
static void lista_cat(categoria *lista)
{
    int tamanio=TAMANIO_CAT(*lista);
    printf("-------------------------------------------------------\n");
    for(int i=0;i<tamanio;i++)
    {
        printf("Descripcion: %s\n",lista[i].descrip);
        printf("Identificador: %s\n",lista[i].id_cat);
        printf("-------------------------------------------------------\n");
    }
}