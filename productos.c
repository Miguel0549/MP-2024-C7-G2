#include "productos.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//PROTOTIPO DE FUNCIONES PRIVADAS
static void obtener_dato_f(FILE **f,char *n);
static int buscar_id_f(FILE **f,char *n);
static void suma1(char *s,int i);
static void lista_cat(categoria *lista,int tamanio);
static void lista_prod(producto *lista,categoria *c,int tamanio_c,int tamanio_p);
static int cadena_valida(char *v);
static void quitaenter(char *);
static void lista_prod_asoc(producto *p,int *asoc,categoria *c,int tamanio_c,int tamanio_asoc);
static void listado_prod(producto *p,categoria *c,int tamanio_c,int tamanio_p);
static void listado_prod_asoc(producto *p,int *asoc,categoria *c,int tamanio_c,int tamanio_p);
static void baja_producto(producto **v,int *tamanio_p,categoria *c, int tamanio_c,int *asoc,sesion ses,int tamanio_asoc);
static void borrar_producto(producto **p,int *tamanio_prod,int indice);
static void modificar_producto(sesion ses,int *asoc,int tamanio_asoc);
static void menu_modificar_producto (int indice);
static void listado_cat();

//Declaracion de variables publicas
producto *array_prod;
categoria *array_cat;
int tamanio_p,tamanio_c;

void menu_cliente_prod (producto *p,categoria *c,int tamanio_p,int tamanio_c)
{
    char seleccion,salida;
    int *asoc,i,j=0,a;//asoc es un vector de enteros cuyos elementos son las indices de los productos a buscar
    char nombre[51],idcat[8];
    system("cls");
    printf("Que desea realizar?\n1)Consulta por categoria\n2)Consulta por nombre\n3)Salir\n");
    seleccion=getchar();
    switch (seleccion)
    {
        case('1'): 
        do{
            system("cls");
            lista_cat(c,tamanio_c);
            printf("Escriba el nombre de la categoria a buscar\n");
            while ((a = getchar()) != '\n' && a != EOF) { }//Limpia el Buffer de entrada
            fgets(nombre,51,stdin);
            quitaenter(nombre);
            cataid(idcat,c,nombre,tamanio_c);
            if (idcat[0]=='-')
            {
                printf("Error, categoria no encontrada, ¿desea salir? s/n\n");
                salida=getchar();
            }
            else
            {
                asoc=(int *)malloc(tamanio_p*sizeof(int));
                for (i=0;i<tamanio_p;i++)//Obtencion de asoc
                {
                    if (strcmp(p[i].id_categ,idcat)==0)
                    {
                        asoc[j]=i;
                        j++;
                    }
                }
                if (j==0)
                {
                    printf("No se ha encontrado ningun producto asociado a esa categoria.\n");
                }
                else
                {
                    asoc=(int *)realloc(asoc,j*sizeof(int));
                    lista_prod_asoc(p,asoc,c,tamanio_c,j);
                    
                }
                free(asoc);
                printf("Pulse enter para salir.\n");
                system("PAUSE");
                salida='s';
            }
        }while(salida!='s');
        menu_cliente_prod(p,c,tamanio_p,tamanio_c);
        break;
        case('2'):
        
            system("cls");
            printf("Escriba el nombre del producto a buscar\n");
            while ((a = getchar()) != '\n' && a != EOF) { }//Limpia el Buffer de entrada
            fgets(nombre,51,stdin);
            quitaenter(nombre);
                asoc=(int *)malloc(tamanio_p*sizeof(int));
                for (i=0;i<tamanio_p;i++)//Obtencion de asoc
                {
                    if (strstr(p[i].nombre,nombre)!=NULL)
                    {
                        asoc[j]=i;
                        j++;
                    }
                }
                if (j==0)
                {
                    printf("No se ha encontrado ningun producto.\n");
                }
                else
                {
                    asoc=(int *)realloc(asoc,j*sizeof(int));
                    lista_prod_asoc(p,asoc,c,tamanio_c,j);
                    
                }
                free(asoc);
                printf("Pulse enter para salir.\n");
                system("PAUSE");
                salida='s';
        
        menu_cliente_prod(p,c,tamanio_p,tamanio_c);
        break;
        case ('3'):
        break;
        default:
        menu_cliente_prod(p,c,tamanio_p,tamanio_c);

    }
}
void menu_adminprov_prod (producto **p,categoria *c,int *tamanio_p,int tamanio_c,sesion ses)
{
    int i,tamanio_asoc=0,*asoc,a;
    char seleccion;
    asoc=(int *)malloc(*tamanio_p*sizeof(int));
    system("cls");
    printf("Sus productos.\n");
    for (i=0;i<*tamanio_p;i++)
    {
        if (strcmp((*p)[i].id_gestor,ses.id)==0)
        {
            asoc[tamanio_asoc]=i;
            tamanio_asoc++;
        }
    }
    asoc=(int *)realloc(asoc,tamanio_asoc*sizeof(int));
    listado_prod_asoc(*p,asoc,c,tamanio_c,tamanio_asoc);
    printf("Que desea realizar?\n1)Alta de un nuevo prducto\n2)Busqueda de productos\n3)Baja de un producto\n4)Modificar un producto\n5)Salir\n");
    seleccion=getchar();
    system("cls");
    switch(seleccion)
    {
        case('1'):
        alta_producto(c,p,tamanio_p,tamanio_c,ses.id);
        free(asoc);
        menu_adminprov_prod(p,c,tamanio_p,tamanio_c,ses);
        break;
        case('2'):
        free(asoc);
        menu_cliente_prod(*p,c,*tamanio_p,tamanio_c);
        menu_adminprov_prod(p,c,tamanio_p,tamanio_c,ses);
        break;
        case('3'):
        baja_producto(p,tamanio_p,c,tamanio_c,asoc,ses,tamanio_asoc);
        free(asoc);
        menu_adminprov_prod(p,c,tamanio_p,tamanio_c,ses);
        break;
        case('4'):
        free(asoc);
        menu_adminprov_prod(p,c,tamanio_p,tamanio_c,ses);
        break;
        case('5'):
        break;
        default:
        free(asoc);
        menu_adminprov_prod(p,c,tamanio_p,tamanio_c,ses);
    }
}
void menu_admin_cat()
{
    char seleccion;
    int a;
    system("cls");
    printf("Estas son las categorias disponibles\n");
    listado_cat();
    printf("Que desea hacer?\n1)Alta de categoria\n2)Modificar categoria\n3)Baja de categoria\n4)Salir\n");
    seleccion=getchar();
    while ((a = getchar()) != '\n' && a != EOF) { }//Limpieza de buffer
    switch (seleccion)
    {
        case '1'://Alta
        alta_categoria(&array_cat,&tamanio_c);
        menu_admin_cat();
        break;
        case '2'://Modificar
        //modificar_categoria();POR HACER
        menu_admin_cat();
        break;
        case '3'://Baja
        baja_categoria();
        menu_admin_cat();
        break;
        case '4'://Salida del programa
        break;
        default://Si se introduce un caracter no valido
        menu_admin_cat();
    }
}
void alta_producto(categoria *c,producto **v,int *tamanio_p,int tamanio_c,char *id)
{
    int error,a;
    char salida='n',carga='n',aux[51],aux2[51];
    producto p;//Auxiliar para guardar temporalmente el producto nuevo
    printf("Comienzo de registro de un producto.\n");
    do{
        while ((a = getchar()) != '\n' && a != EOF) { }//Limpia el buffer de entrada
        printf("Escribe el nombre del producto (no puede contener -,maximo 15 caracteres)\nNombre: ");
        fgets(p.nombre,16,stdin);
        quitaenter(p.nombre);
        printf("\nEscribe una descripcion del producto (no puede contener -,maximo 50 caracteres)\nDescripcion: ");
        fgets(p.descrip,51,stdin);
        quitaenter(p.descrip);
        
        lista_cat(c,tamanio_c);
        printf("Escribe la categoria que quieras asociar al producto.\nCategoria: ");
        fgets(aux2,51,stdin);
        quitaenter(aux2);
        cataid(p.id_categ,c,aux2,tamanio_c);
        
        printf("\nEscribe el stock inicial del producto.\nStock: ");
        fgets(aux,51,stdin);
        p.stock=atoi(aux);
        
        printf("\nEscribe la cantidad de dias de compromiso de entrega.\nEntrega: ");
        fgets(aux,51,stdin);
        p.entrega=atoi(aux);
        
        printf("\nEscribe el importe en euros de cada producto.\nImporte: ");
        fgets(aux,51,stdin);
        p.importe=atoi(aux);
        
        if((cadena_valida(p.nombre)!=0)&&(cadena_valida(p.descrip)!=0)&&(cadena_valida(p.id_categ)!=0)&&(p.stock!=EOF)&&(p.entrega!=EOF)&&(p.importe!=EOF))//Comprobacion de los datos
        {
            printf("\nDatos introducidos no validos.\n");
            error=1;
        }
        else
        {
            system("cls");
            printf("\nRecopilacion de los datos.\n");
            printf("Nombre: %s\n",p.nombre);
            printf("Descripcion: %s\n",p.descrip);
            printf("Categoria %s\n",aux2);
            printf("Stock inicial: %d unidades\n",p.stock);
            printf("Compromiso de entrega: %d dias\n",p.entrega);
            printf("Importe: %d euros\n",p.importe);
            printf("¿Es la informacion correcta? Escriba s para confirmar.\n");
            for (carga=0;carga=getchar() == 's' || carga=='n';) {}
            
            if (carga=='s')
            {
                strcpy(p.id_gestor,id);
                //Obtencion de la proxima id disponible
                if (*tamanio_p==0)
                {
                    strcpy(p.id_prod,"0000001\0");
                }
                else
                {
                    strcpy(aux,(*v+(*tamanio_p-1))->id_prod);
                    suma1(aux,7);//Suma a la cadena 1
                    strcpy(p.id_prod,aux);
                }
                //Subida del producto al vector
                *tamanio_p=*tamanio_p+1;
                if((*v=(producto *)realloc(*v,(*tamanio_p)*(sizeof(producto))))!=NULL)//agrega espacio al vector para poner el nuevo producto
                {
                    (*v)[(*tamanio_p)-1]=p;
                    error=0;
                    salida='s';
                }
                else
                {
                    printf("Se ha producido un error en la carga del producto.\n");
                    *tamanio_p=*tamanio_p-1;
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
            printf("¿Desea cancelar el alta? s/n.\n");
            
            for (salida=0;salida=getchar() == 's' || salida=='n';) {}
            
        }
    }while(salida!='s');
    if(error!=0)
    {
        printf("Alta de producto fallida. Error: %d.\n",error);
        system("pause");
    }
    else
    {
        printf("Alta de producto con exito. Id: %s\n",p.id_prod);
        system("pause");
    }
}
void alta_categoria(categoria **v,int *tamanio)
{
    int error,a;
    categoria c;
    char salida,carga,aux[5];
    printf("Comienzo de alta de una categoria.\n");
    do{
        while ((a = getchar()) != '\n' && a != EOF) { }//Limpia el Buffer de entrada
        printf("Escribe la descripcion de la categoria.\nEsta no puede contener guiones o ser mayor de 51 caracteres.\n");
        fgets(c.descrip,51,stdin);
        quitaenter(c.descrip);
        if (cadena_valida(c.descrip)!=0)
        {
            printf("\nDatos introducidos no validos.\n");
            error=1;
        }
        else
        {
            printf("\nConfirmacion de los datos.\n");
            printf("Decripcion: %s\n",c.descrip);
            printf("¿Desea confirmar la categoria? s/n.\n");
            for (carga=0;carga=getchar() == 's' || carga=='n';) {}
            if (carga=='s')
            {
                //Obtencion de la proxima id
                if (*tamanio==0)
                {
                    strcpy(c.id_cat,"0001\0");
                }
                else
                {
                    strcpy(aux,(*v+(*tamanio-1))->id_cat);
                    suma1(aux,4);
                    strcpy(c.id_cat,aux);
                    *tamanio=*tamanio+1;
                }
                if ((*v=(categoria *)realloc(*v,(*tamanio)*sizeof(categoria)))==NULL)
                {
                    printf("Error de memoria.\n");
                    *tamanio--;
                    error=2;
                }
                else
                {
                    (*v)[*tamanio-1]=c;
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
            printf("¿Desea cancelar el alta? s/n.\n");
            for (salida=0;salida=getchar() == 's' || salida=='n';) {}
        }
    }while(salida!='s');
    if (error==0)
    {
        printf("Alta de categoria con exito.\n");
    }
    else
    {
        printf("Alta de categoria fallida. Error: %d",error);
    }
}
static void baja_producto(producto **v,int *tamanio_p,categoria *c, int tamanio_c,int *asoc,sesion ses,int tamanio_asoc)//TODO: Implementar la comprobacion de proveedor, POR PROBAR
{
    int i,indice,a,encontrado=0;
    char salida='s';
    char id_prod[8];
    char confirmar='n';
    system("cls");
    if(ses.perfil_usuario==administrador)
    {
        printf("Como administrador, puede eliminar cualquier producto del sistema.\n");
        listado_prod(*v,c,tamanio_c,*tamanio_p);
        do{
            while ((a = getchar()) != '\n' && a != EOF) { }//Limpieza de buffer
            printf("Escribe el identificador del producto a eliminar.\nId: ");

            fgets(id_prod,8,stdin);
            for (i=0;i<*tamanio_p&&encontrado==0;i++)//Encuentra el indice del producto a borrar
            {
                if(strcmp((*v)[i].id_prod,id_prod)==0)
                {
                    encontrado=1;
                    indice=i;
                }
            }
            if (encontrado==1)
            {
                printf("Va a borrar el producto %s,desea confirmar? Escriba 's' para confirmar\n",v[indice]->nombre);
                while ((a = getchar()) != '\n' && a != EOF) { }//Limpieza de buffer
                confirmar=getchar();
                if(confirmar=='s')
                {
                    salida='n';
                    borrar_producto(v,tamanio_p,indice);
                    printf("Baja de producto con exito");
                }
                else
                {
                    printf("Eliminacion de producto abortada.\n");
                }
            }

        }while(salida=='s');
    }
    else
    {
        printf("Como proveedor, solo puede borrar productos asociados a su nombre.\n");
        listado_prod_asoc(*v,asoc,c,tamanio_c,tamanio_asoc);
        do{
            while ((a = getchar()) != '\n' && a != EOF) { }//Limpieza de buffer
            printf("Escribe el identificador del producto a eliminar.\nId: ");
            fgets(id_prod,8,stdin);
            for (i=0;i<tamanio_asoc&&encontrado;i++)//Encuentra el indice del producto a borrar
            {
                if(strcmp((*v)[asoc[i]].id_prod,id_prod)==0)
                {
                    encontrado=1;
                    indice=asoc[i];
                }
            }
            if (encontrado==1)
            {
                printf("Va a borrar el producto %s,desea confirmar? Escriba 's' para confirmar\n",v[indice]->nombre);
                while ((a = getchar()) != '\n' && a != EOF) { }//Limpieza de buffer
                confirmar=getchar();
                if(confirmar=='s')
                {
                    salida='s';
                    borrar_producto(v,tamanio_p,indice);
                    printf("Baja de producto con exito");
                }
                else
                {
                    printf("Eliminacion de producto abortada.\n");
                }
            }
        }while(salida=='s');
    } 
    if(confirmar=='s')
    {
        printf("Borrado del producto con exito.\n");
        while ((a = getchar()) != '\n' && a != EOF) { }//Limpieza de buffer
    }
    else
    {
        printf("No se ha podido borrar el producto.\n");
        while ((a = getchar()) != '\n' && a != EOF) { }//Limpieza de buffer
    }
}
void baja_categoria()//Por terminar
{
    int a,*asoc,tamanio_asoc=0,i,indice;
    char salida='n',id_cat[5],descrip[51],confirmar;
    system("cls");
    printf("Comienzo de borrado de una categoria.\n");
    lista_cat(array_cat,tamanio_c);
    asoc=(int *)malloc(tamanio_p*sizeof(producto));//asoc es un vector que va a contener todas los indices de los productos que coincidan con la categoria a borrar
    do{
        pritnf("Escribe el identificador de la id a borrar.\n");
        fgets(id_cat,5,stdin);
        indice=idacat(descrip,array_cat,id_cat,tamanio_c);
        if(descrip[0]=='-')//'-' significa que no se ha encontrado la id
        {
            printf("No se ha encontrado la categoria\nDesea cancelar la baja? Escriba 's' para salir");
            salida=getchar();
            while ((a = getchar()) != '\n' && a != EOF) { }//Limpieza de buffer
        }
        else
        {
            printf("Va a borrar la categoria %s.\nEscriba 's' para confirmar\n",descrip);
            confirmar=getchar();
            while ((a = getchar()) != '\n' && a != EOF) { }//Limpieza de buffer
            if (confirmar=='s')
            {
                for (i=0;i<tamanio_p;i++)
                {
                    if(strcmp(id_cat,array_prod[i].id_categ))
                    {
                        asoc[tamanio_asoc]=i;
                        tamanio_asoc++;
                    }
                }
                asoc=(int *)realloc(asoc,tamanio_asoc*sizeof(int));
                if (tamanio_asoc!=0)
                {
                    listado_prod_asoc(array_prod,asoc,array_cat,tamanio_c,tamanio_asoc);
                    printf("Los siguientes productos estan asociados a la categoria a borrar.\nBorrar esta categoria tambien borrara esos productos.\nSi no quiere borrarlos, cancele y asocie dichos productos a otra categoria.\nDesea continuar? Escriba 's' para continuar.\n");
                    confirmar='n';
                    confirmar=getchar();
                    while ((a = getchar()) != '\n' && a != EOF) { }//Limpieza de buffer
                    if (confirmar=='s')
                    {
                        for (i=0;i<tamanio_asoc;i++)//Borrado de los productos asociados a la categoria
                        {
                            borrar_producto(&array_prod,&tamanio_p,asoc[i]);
                        }
                        for (i=indice;i<tamanio_c-1;i++)//Borrado de la categoria
                        {
                            array_cat[i]=array_cat[i+1];
                        }
                        tamanio_c--;
                        array_cat=(categoria *)realloc(array_cat,tamanio_c*sizeof(categoria));
                        printf("Borrado de categoria con exito\n");
                    }
                    else
                    {
                        printf("Baja de categoria abortada.\nDesea salir? Escriba 's' para salir\n");
                        salida=getchar();
                        while ((a = getchar()) != '\n' && a != EOF) { }//Limpieza de buffer
                    }
                }
                else
                {
                    for (i=indice;i<tamanio_c-1;i++)//Borrado de la categoria
                        {
                            array_cat[i]=array_cat[i+1];
                        }
                        tamanio_c--;
                        array_cat=(categoria *)realloc(array_cat,tamanio_c*sizeof(categoria));
                        printf("Borrado de categoria con exito\n");
                }
            }
            else
            {
                {
                    printf("Baja de categoria abortada.\nDesea salir? Escriba 's' para salir\n");
                    salida=getchar();
                    while ((a = getchar()) != '\n' && a != EOF) { }//Limpieza de buffer
                }
                
            }
        }
    }while(salida=='s');
    free(asoc);
}
void guardar_producto(producto *v,int n_elem)
{
    FILE *f;
    int i;
    if ((f=fopen(F_PRODUCTO,"w"))==NULL)
    {
        printf("Error de apertura de fichero., no se han guardado los datos");
    }
    else
    {
        rewind(f);
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
            fprintf(f,"%d",v[i].entrega);
            fputc('-',f);
            fprintf(f,"%d",v[i].importe);
            fputc('\n',f);
        }
    }
    fclose(f);
    free(v);  
}
void guardar_categoria(categoria *v,int n_elem)
{
    FILE *f;
    int i;
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
            fputc('\n',f);
        }
    }
    fclose(f);
    free(v);
}
producto * volcar_producto(int *tamanio)
{
    FILE *f;
    char aux[51];//Cadena auxiliar para rellenar los datos, 51 es el valor de la cadena más larga
    static producto *v;
    char j;
    int i;
    if ((v=(producto *)malloc(sizeof(producto)))==NULL)
    {
        printf("Error de alocación de memoria.\n");
    }
    else
    {
        if((f=fopen(F_PRODUCTO,"r"))==NULL)
        {
            printf("ERROR: No se ha encontrado el fichero Productos.txt, no se ha podido cargar memoria de los productos.\n");
            *tamanio=0;
        }
        else
        {
            for(i=0;j!=EOF;i++)//Bucle para obtener cada dato
            {
                v=(producto *)realloc(v,(i+1)*sizeof(producto));
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
                fseek(f,-1,SEEK_CUR);
            }
            *tamanio=i;
            fclose(f);
        }
        
    }
    return v;
}
categoria * volcar_categoria(int *tamanio)//No Probada todavia
{
    FILE *f;
    int i;
    static categoria *v;
    char j='-';
    if ((v=(categoria *)malloc(sizeof(categoria)))==NULL)
    {
        printf("Error de alocación de memoria.\n");
    }
    else
    {
        if((f=fopen(F_CATEGORIAS,"r"))==NULL)
        {
            printf("ERROR: No se ha encontrado el fichero Categorias.txt, no se ha podido cargar memoria de las categorias.\n");
            *tamanio=0;
        }
        else
        {
            for(i=0;j!=EOF;i++)//Bucle para obtener cada dato
            {
                v=(categoria *)realloc(v,((i+1)*sizeof(categoria)));
                fgets(v[i].id_cat,5,f);
                fseek(f,1,SEEK_CUR);
                fgets(v[i].descrip,51,f);//Dejara de leer en EOF o en '/n'
                quitaenter(v[i].descrip);
                j=fgetc(f);
                fseek(f,-1,SEEK_CUR);
            }
            *tamanio=i;
            fclose(f);
        }
    }
    return v;
}
int idacat(char *descrip,categoria *c,char *id,int tamanio)
{
    descrip[0]='-';
    descrip[1]='\0';
    int encontrado=1,indice=0;
    for (int i=0;(i<tamanio)&&(encontrado);i++)
    {
        if (strcmp(c[i].id_cat,id)==0)
        {
            strcpy(descrip,c[i].descrip);
            encontrado=0;
            indice=i;
        }
    }
    return indice;
}
void cataid(char *id,categoria *c,char *descrip,int tamanio)
{
    id[0]='-';
    id[1]='\0';
    int encontrado=1;
    for (int i=0;(i<tamanio)&&(encontrado);i++)
    {
        if (strcmp(c[i].descrip,descrip)==0)
        {
            strcpy(id,c[i].id_cat);
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
    for (int j=0;(i>=0)&&(j==0);i--)
    {
        if (s[i-1]=='9')
        {
            s[i-1]='0';
        }
        else
        {
            s[i-1]++;
            j=1;
        }
    }
}
//Cabecera: static int cadena_valida(char *v,int size)
//Precondicion: v tiene que ser una cadena obtenida mediante fgets y size el tamaño de la cadena
//Poscondicion: Devuelve 0 si la cadena cumple con las restricciones y devuelve distinto de 0 si se produce un error 
//y establece '/n' como fin de la cadena, si lo hay.
static int cadena_valida(char *v)
{
    int error=0;
    int i,size=strlen(v);
    for (i=0;(i<size)&&(error!=0)&&(v[i]=='\0');i++)
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
static void lista_prod(producto *lista,categoria *c,int tamanio_p,int tamanio_c)
{
    char descrip_cat[51];//auxiliar para guardar la descripcion de la categoria
    printf("-------------------------------------------------------\n");
    for(int i=0;i<tamanio_p;i++)
    {
        idacat(descrip_cat,c,lista[i].id_categ,tamanio_c);
        printf("Nombre: %s\n",lista[i].nombre);
        printf("Descripcion: %s\n",lista[i].descrip);
        printf("Categoria: %s\n",descrip_cat);
        printf("Precio: %d euros\n",lista[i].importe);
        printf("Stock: %d unidades\n",lista[i].stock);
        printf("Entrega en %d dias\n",lista[i].entrega);
        printf("Identificador: %s\n",lista[i].id_prod);
        printf("-------------------------------------------------------\n");
    }
}
//Cabecera: static void lista_cat(categoria *lista)
//Precondicion: Todos los campos de lista deben estar inicializados, tamanio <= nº de elementos de lista.
//Poscondicon: Imprime por pantalla lista como una lista de las categorias
static void lista_cat(categoria *lista,int tamanio)
{
    printf("-------------------------------------------------------\n");
    for(int i=0;i<tamanio;i++)
    {
        printf("Descripcion: %s\n",lista[i].descrip);
        printf("Identificador: %s\n",lista[i].id_cat);
        printf("-------------------------------------------------------\n");
    }
}
//Cabecera: static void lista_prod_asoc(producto *p,int *asoc,categoria *c,int tamanio_c,int tamanio_asoc)
//Precondicion: Todas las entradas asignadas, todos los elementos de asoc deben ser menores que el numero de elementos del vector p
//Poscondicion: Imprime por pantalla todos los productos que apunte cada indice de asoc en p
static void lista_prod_asoc(producto *p,int *asoc,categoria *c,int tamanio_c,int tamanio_asoc)
{
    char descrip_cat[51];//auxiliar para guardar la descripcion de la categoria
    printf("-------------------------------------------------------\n");
    for(int i=0;i<tamanio_asoc;i++)
    {
        idacat(descrip_cat,c,p[asoc[i]].id_categ,tamanio_c);
        printf("Nombre: %s\n",p[asoc[i]].nombre);
        printf("Descripcion: %s\n",p[asoc[i]].descrip);
        printf("Categoria: %s\n",descrip_cat);
        printf("Precio: %d€\n",p[asoc[i]].importe);
        printf("Stock: %d unidades\n",p[asoc[i]].stock);
        printf("Entrega en %d dias\n",p[asoc[i]].entrega);
        printf("Identificador: %s\n",p[asoc[i]].id_prod);
        printf("-------------------------------------------------------\n");
    }
}
//Cabecera: static void quitaenter(char *c)
//Precondicion: La cadena debe estar definida con un '/0'
//Poscondicion: Establece '\n', si lo hay, como final de la cadena
static void quitaenter(char *c)
{
    if (c[strlen(c)-1]=='\n')
        {
            c[strlen(c)-1]='\0';
        }
}
//Cabecera: static void listado_prod(producto *p,categoria *c,int tamanio_c,int tamanio_p)
//Precondicion: p y c definidas, tamanio_c y tamanio_p son equivalentes al numero de elementos de p y de c
//Poscondicion: Muestra por pantalla una lista de los productos de forma mas compacta
static void listado_prod(producto *p,categoria *c,int tamanio_c,int tamanio_p)
{
    int i;
    char aux[51];
    printf("Identificador-Nombre-Descripcion-Categoria-Precio-Stock-Entrega-Gestor.\n");
    for (i=0;i<tamanio_p;i++)
    {
        idacat(aux,c,p[i].id_categ,tamanio_c);
        printf("%s|%s|%s|%s|%d euros|%d Uds.|%d dias|%s\n",p[i].id_prod,p[i].nombre,p[i].descrip,aux,p[i].importe,p[i].stock,p[i].entrega,"Por implementar");
    }
}
//Cabecera: static void listado_prod_asoc(producto *p,int *asoc,categoria *c,int tamanio_c,int tamanio_p)
//Precondicion: p y c definidas, tamanio_c y tamanio_p son equivalentes al numero de elementos de p y de c
//Poscondicion: Muestra por pantalla una lista de los productos de forma mas compacta a traves de un vector que asocia las posiciones de los productos
static void listado_prod_asoc(producto *p,int *asoc,categoria *c,int tamanio_c,int tamanio_asoc)
{
    int i;
    char aux[51];
    printf("Identificador-Nombre-Descripcion-Categoria-Precio-Stock-Entrega-Gestor.\n");
    for (i=0;i<tamanio_asoc;i++)
    {
        idacat(aux,c,p[i].id_categ,tamanio_c);
        printf("%s|%s|%s|%s|%d euros|%d Uds.|%d dias|%s\n",p[asoc[i]].id_prod,p[asoc[i]].nombre,p[asoc[i]].descrip,aux,p[asoc[i]].importe,p[asoc[i]].stock,p[asoc[i]].entrega,"Por implementar");
    }
}
//Cabecera: static void borrar_producto(producto **p,int *tamanio_prod,int indice)
//Precondicion: *tamanio_prod debe ser el numero de indices de *p, indice<*tamanio_prod
//Poscondicion: borra el elemento indice del vector p y reduce el tamaño del vector en uno
static void borrar_producto(producto **p,int *tamanio_prod,int indice)
{
    for (int i=indice;i<(*tamanio_prod)-1;i++)//Borra el producto mediante la sustitucion de este por el siguiente
    {
        (*p)[i]=(*p)[i+1];
    }
    *tamanio_prod=(*tamanio_prod)-1;
    *p=(producto *)realloc(*p,*tamanio_prod*sizeof(producto));
}
//Cabecera: static void modificar_producto(sesion ses);
//Precondicion: array_prod y array_cat deben estar cargados mediante volcar_producto y volcar_categoria. tamanio_p y tamanio_c deben ser el numero de elementos de array_prod y arra_cat respectivamente
//Poscondicion: Muestra por pantalla un menu por el que el usuario puede modificar cualquier caracteristica de los productos que tenga permiso modificar.
static void modificar_producto(sesion ses,int *asoc,int tamanio_asoc)
{
    int encontrado=0,indice,a,i;
    char *id_prod,salida='n';
    if(ses.perfil_usuario==administrador)
    {
        
        printf("Como administrador, puede modificar cualquier producto del sistema.\n");
        listado_prod(array_prod,array_cat,tamanio_c,tamanio_p);
        do{
            while ((a = getchar()) != '\n' && a != EOF) { }//Limpieza de buffer
            printf("Escribe el identificador del producto a eliminar.\nId: ");

            fgets(id_prod,8,stdin);
            for (i=0;i<tamanio_p&&encontrado==0;i++)//Encuentra el indice del producto a borrar
            {
                if(strcmp(array_prod[i].id_prod,id_prod)==0)
                {
                    encontrado=1;
                    indice=i;
                }
            }
            if(encontrado==1)
            {
                menu_modificar_producto(i);
            }
            else
            {
                printf("No se ha encontrado la id introducida. Desea salir? Escriba s para salir");
                while ((a = getchar()) != '\n' && a != EOF) { }//Limpieza de buffer
                salida=getchar();
            }
        }while(salida=='s');
    }
    else
    {
        printf("Como proveedor, solo puede modificar los productos asociados a su nombre.\n");
        listado_prod_asoc(array_prod,asoc,array_cat,tamanio_c,tamanio_asoc);
        do{
            while ((a = getchar()) != '\n' && a != EOF) { }//Limpieza de buffer
            printf("Escribe el identificador del producto a modificar.\nId: ");
            fgets(id_prod,8,stdin);
            for (i=0;i<tamanio_asoc&&encontrado;i++)//Encuentra el indice del producto a borrar
            {
                if(strcmp(array_prod[asoc[i]].id_prod,id_prod)==0)
                {
                    encontrado=1;
                    indice=asoc[i];
                }
            }
            if(encontrado==1)
            {
                menu_modificar_producto(i);
            }
            else
            {
                printf("No se ha encontrado la id introducida. Desea salir? Escriba s para salir");
                while ((a = getchar()) != '\n' && a != EOF) { }//Limpieza de buffer
                salida=getchar();
            }
        }while(salida=='s');
    }
}
//Cabecera: static void menu_modificar_producto (int indice)
//Precondicion: indice menor que tamanio_p
//Poscondicion: Muestra por pantalla un menu recursivo en el que el usuario puede modificar el producto de elemento indice en el vector array_prod
static void menu_modificar_producto (int indice)
{
    int asoc[1]={indice},a,aux_int;
    char seleccion,aux[51],confirmar,id[8],descrip[51];

    system ("cls");
    lista_prod_asoc(array_prod,asoc,array_cat,tamanio_c,1);
    printf("Que desea modificar?\n1)Nombre\n2)Descripcion\n3)Compromiso de entrega\n4)Importe\n5)Stock\n6)Categoria\n7)Atras");
    seleccion=getchar();
    while ((a = getchar()) != '\n' && a != EOF) { }//Limpieza de buffer
    switch (seleccion)//Captacion del dato
    {
        case'1'://Nombre
        printf("Escribe el nuevo nombre. (Maximo 15 caracteres, no puede contener '-')\n");
        fgets(aux,51,stdin);
        quitaenter(aux);
        if (cadena_valida(aux))
        {
            printf("Error: El valor introducido no es valido\n");
            system("pause");
        }
        else
        {
            printf("Va a remplazar el siguiente valor\n Nombre: %s  <- %s \n Escriba 's' para confirmar",array_prod[indice].nombre,aux);
            confirmar=getchar();
            while ((a = getchar()) != '\n' && a != EOF) { }//Limpieza de buffer
            if (confirmar=='s')
                strcpy(array_prod[indice].nombre,aux); 
        }
        menu_modificar_producto(indice);
        break;
        case '2'://Descripcion
        printf("Escribe la nueva descripcion. (Maximo 50 caracterres, no puede contener '-')\n");
        fgets(aux,51,stdin);
        quitaenter(aux);
        if (cadena_valida(aux))
        {
            printf("Error: El valor introducido no es valido\n");
            system("pause");
        }
        else
        {
            printf("Va a remplazar el siguiente valor\n Descripcion: %s <- %s \n Escriba 's' para confirmar",array_prod[indice].importe,aux);
            confirmar=getchar();
            while ((a = getchar()) != '\n' && a != EOF) { }//Limpieza de buffer
            if (confirmar=='s')
                strcpy(array_prod[indice].importe,aux);
        }
        menu_modificar_producto(indice);
        break;
        case '3'://Compromiso de entrega
        printf("Escribe el nuevo compromiso de entrega en dias.\n");
        fgets(aux,51,stdin);
        a=atoi(aux);
        if (a==0)
        {
            printf("Error: El valor introducido no es valido\n");
            system("pause");
        }
        else
        {
            printf("Va a remplazar el siguiente valor\n Entrega: %i dias <- %i dias\n Escriba 's' para confirmar",array_prod[indice].importe,aux_int);
            confirmar=getchar();
            while ((a = getchar()) != '\n' && a != EOF) { }//Limpieza de buffer
            if (confirmar=='s')
                array_prod[indice].importe=aux_int;
        }
        menu_modificar_producto(indice);
        break;
        case '4'://Importe
        printf("Escribe el nuevo importe en euros\n");
        fgets(aux,51,stdin);
        aux_int=atoi(aux);
        if (aux_int==0)
        {
            printf("Error: El valor introducido no es valido\n");
            system("pause");
        }
        else
        {
            printf("Va a remplazar el siguiente valor\n Importe: %i euros <- %i euros\n Escriba 's' para confirmar",array_prod[indice].importe,aux_int);
            confirmar=getchar();
            while ((a = getchar()) != '\n' && a != EOF) { }//Limpieza de buffer
            if (confirmar=='s')
                array_prod[indice].importe=aux_int;
        }
        menu_modificar_producto(indice);
        break;
        case '5'://Stock
        printf("Escribe el nuevo stock\n");
        fgets(aux,51,stdin);
        aux_int=atoi(aux);
        if (aux_int==0)
        {
            printf("Error: El valor introducido no es valido\n");
            system("pause");
        }
        else
        {
            printf("Va a remplazar el siguiente valor\n Stock: %i unidades <- %i unidades\n Escriba 's' para confirmar",array_prod[indice].stock,aux_int);
            confirmar=getchar();
            if (confirmar=='s')
                array_prod[indice].stock=aux_int;
        }
        menu_modificar_producto(indice);
        break;
        case '6'://Categoria
        lista_cat(array_cat,tamanio_c);
        printf("Escribe el nombre de la categoria a asignar\n");
        fgets(aux,51,stdin);
        cataid(aux,array_cat,id,tamanio_c);
        if (id[0]=='-')
        {
            printf("Error, el nombre introducido no coincide con ninguna categoria\n");
            system("pause");
        }
        else
        {
            idacat(descrip,array_cat,array_prod[indice].id_categ,tamanio_c);
            printf("Va a remplazar el siguiente valor\n Categoria: %s <- %s \n Escriba 's' para confirmar",descrip,aux);
            confirmar=getchar();
            if (confirmar=='s')
                strcpy(array_prod[indice].id_categ,aux_int);
        }
        menu_modificar_producto(indice);
        case '7'://Salida
        break;
        default://Default, si no se introduce un valor valido
        menu_modificar_producto(indice);
    }
}
//Cabecera: static void listado_cat()
//Precondicion: array_categoria debe estar definido y tamanio_cat debe ser menor o igual al numero de elementos
//Poscondicion: Muestra por pantalla todas las categorias de forma mas compacta
static void listado_cat()
{
    printf("Identificador|Descripcion\n");
    for (int i=0;i<tamanio_c;i++)
    {
        printf("%s|%s\n",array_cat[i].id_cat,array_cat[i].descrip);
    }
}
//POR HACER: REMPLAZAR TODAS LAS DECLARACIONES DE LOS VECTORES DE PRODUCTO Y CATEGORIA COMO SUS TAMAÑOS POR SUS VARIABLES PUBLICAS
//POR HACER: PODER MODIFICAR CATEGORIAS
//POR HACER: TESTEAR MODIFICACION DE PRODUCTO Y DEBUGARLO
//POR HACER: MEJORAR LAS LIMPIEZAS DEL BUFFER DE ENTRADA