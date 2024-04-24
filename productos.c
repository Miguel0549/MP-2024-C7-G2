#include "productos.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define LINE 150

 producto *array_prod;
 categoria *array_cat;
 int tamanio_p,tamanio_c;


//PROTOTIPO DE FUNCIONES PRIVADAS
static void obtener_dato_f(FILE **f,char *n);
static int buscar_id_f(FILE **f,char *n);
static void suma1(char *s,int i);
static void lista_cat();
static void lista_prod();
static int cadena_valida(char *v);
static void quitaenter(char *);
static void lista_prod_asoc(int *asoc,int tamanio_asoc);
static void listado_prod();
static void listado_prod_asoc(int *asoc,int tamanio_asoc);
static void baja_producto(int *asoc,sesion ses,int tamanio_asoc);
void borrar_producto(int indice);
static void modificar_producto(sesion ses,int *asoc,int tamanio_asoc);
void menu_modificar_producto (int indice);
static void listado_cat();
static void modificar_categoria();



int reducir_stock(char *id,int resta)
{
    int error=0,encontrado=0,indice;

    for (int i=0;i<tamanio_p&&encontrado==0;i++){

        if (strcmp(id,array_prod[i].id_prod)==0)
        {
            encontrado=1;
            indice=i;
        }
    }

    if(encontrado==1&&resta<=array_prod[indice].stock){
        array_prod[indice].stock -= resta;
    }else{
        error=1;
    }
    return error;
}



void menu_cliente_producto_conpedido( Pedido **ped , ProductoPedido **prod_ped , int *n_ped , int *n_pr_ped , char id_cliente[8] )
{
    char id[8]="\0";
    producto  p;
    int unidades;

    char seleccion;
    int encontrado=0,a;
    seleccion=menu_cliente_prod();
    if (seleccion!='3')
    {
        printf("Escriba la id del producto a comprar, o bien escriba 's' para salir\n");
        fflush(stdin);
        fgets(id,8,stdin);
        for (int i=0;i<tamanio_p&&encontrado==0;i++)
        {
            if(strcmp(id,array_prod[i].id_prod)==0){

                encontrado=1;
                p = array_prod[i];

                do{

                    printf("Cuantas unidades desea comprar?: ");
                    scanf("%i",&unidades);

                }while( reducir_stock(p.id_prod,unidades) == 1);

                hacer_pedido(ped,prod_ped,n_ped,n_pr_ped,unidades,p.importe,p.id_prod,id_cliente);


            }

        }
    }
    if (seleccion=='3'||encontrado==0)
    {
        strcpy(id,"0000000\0");
    }
    system("cls");
}


char menu_cliente_prod ( )
{


    char seleccion,salida;
    int *asoc,i,j=0,a;//asoc es un vector de enteros cuyos elementos son las indices de los productos a buscar
    char nombre[51],idcat[8];
    system("cls");
    printf("Que desea realizar?\n1)Consulta por categoria\n2)Consulta por nombre\n3)Salir\n");
    fflush(stdin);
    seleccion=getchar();
    switch (seleccion)
    {
        case('1'):
            do{
                system("cls");
                lista_cat();
                printf("Escriba el nombre de la categoria a buscar\n");
                while ((a = getchar()) != '\n' && a != EOF) { }//Limpia el Buffer de entrada
                fgets(nombre,51,stdin);
                quitaenter(nombre);
                cataid(idcat,nombre);
                if (idcat[0]=='-')
                {
                    printf("Error, categoria no encontrada, ¿desea salir? s/n\n");
                    salida=getchar();
                }
                else
                {
                    asoc=(int *)malloc((tamanio_p)*sizeof(int));
                    for (i=0;i<tamanio_p;i++)//Obtencion de asoc
                    {
                        if (strcmp(array_prod[i].id_categ,idcat)==0)
                        {
                            asoc[j]=i;
                            j++;
                        }
                    }
                    if (j==0)
                    {
                        printf("No se ha encontrado ningun producto asociado a esa categoria.\n");
                        seleccion='3';
                        system("PAUSE");
                    }
                    else
                    {
                        asoc=(int *)realloc(asoc,j*sizeof(int));
                        lista_prod_asoc(asoc,j);

                    }
                    free(asoc);

                    salida='s';
                }
            }while(salida!='s');

            break;
        case('2'):

            system("cls");
            printf("Escriba el nombre del producto a buscar\n");
            while ((a = getchar()) != '\n' && a != EOF) { }//Limpia el Buffer de entrada
            fgets(nombre,51,stdin);
            quitaenter(nombre);
            asoc=(int *)malloc((tamanio_p)*sizeof(int));
            for (i=0;i<tamanio_p;i++)//Obtencion de asoc
            {
                if (strstr(array_prod[i].nombre,nombre)!=NULL)
                {
                    asoc[j]=i;
                    j++;
                }
            }
            if (j==0)
            {
                printf("No se ha encontrado ningun producto.\n");
                seleccion='3';
            }
            else
            {
                printf("Se han encontrado los siguientes productos\n");
                asoc=(int *)realloc(asoc,j*sizeof(int));
                lista_prod_asoc(asoc,j);

            }
            free(asoc);
            system("PAUSE");
            salida='s';
            break;
        case ('3'):
            while ((a = getchar()) != '\n' && a != EOF) { }//Limpia el Buffer de entrada
            break;
        default:
            while ((a = getchar()) != '\n' && a != EOF) { }//Limpia el Buffer de entrada
            seleccion=menu_cliente_prod();
    }
    return seleccion;
}

void menu_adminprov_prod (sesion ses)
{
    int i,tamanio_asoc=0,*asoc,a;
    char seleccion;
    asoc=(int *)malloc((tamanio_p)*sizeof(int));
    system("cls");
    printf("Sus productos.\n");
    for (i=0;i<tamanio_p;i++)
    {
        if (strcmp(array_prod[i].id_gestor,ses.id)==0)
        {
            asoc[tamanio_asoc]=i;
            tamanio_asoc++;
        }
    }
    asoc=(int *)realloc(asoc,tamanio_asoc*sizeof(int));
    listado_prod_asoc(asoc,tamanio_asoc);
    printf("Que desea realizar?\n1)Alta de un nuevo prducto\n2)Busqueda de productos\n3)Baja de un producto\n4)Modificar un producto\n5)Salir\n");
    seleccion=getchar();
    system("cls");

    switch(seleccion)
    {
        case('1'):
        alta_producto(ses.id,0);
        free(asoc);
        menu_adminprov_prod(ses);
        break;
        case('2'):
        free(asoc);
        menu_cliente_prod();
        menu_adminprov_prod(ses);
        break;
        case('3'):
        baja_producto(asoc,ses,tamanio_asoc);
        free(asoc);
        menu_adminprov_prod(ses);
        break;
        case('4'):
        free(asoc);
        menu_adminprov_prod(ses);
        break;
        case('5'):
        break;
        default:
        free(asoc);
        menu_adminprov_prod(ses);
    }
}
void menu_admin_cat()
{
    int seleccion;

    do{

        system("cls");
        printf("------------------------- Categorias disponibles----------------------------\n\n");
        listado_cat();
        printf("----------------------------------------------------------------------------\n\n");
        printf("Que desea hacer?\n1.Alta de categoria\n2.Modificar categoria\n3.Baja de categoria\n4.Salir\n");
        scanf("%i",&seleccion);
        switch (seleccion)
        {
            case 1://Alta
                alta_categoria();
                break;
            case 2://Modificar
                modificar_categoria();
                break;
            case 3://Baja
                baja_categoria();
                break;
            case 4://Salida del programa
                break;
            default://Si se introduce un caracter no valido
                printf("Escribe un numero del 1 al 4");
                break;
        }

    }while (seleccion != 4);

}
void alta_producto(char *id , int *n_admpr )
{
    int error,a,i;
    char salida='n',carga='n',aux[51],aux2[51],id_gestor_nuevo[5]="\0";
    producto p;//Auxiliar para guardar temporalmente el producto nuevo
    printf("Comienzo de registro de un producto.\n");
    do{
        while ((a = getchar()) != '\n' && a != EOF) { }//Limpia el buffer de entrada
        printf("Escribe el nombre del producto (no puede contener -,maximo 15 caracteres)\nNombre: ");
        fflush(stdin);
        fgets(p.nombre,16,stdin);
        quitaenter(p.nombre);
        printf("\nEscribe una descripcion del producto (no puede contener -,maximo 50 caracteres)\nDescripcion: ");
        fflush(stdin);
        fgets(p.descrip,51,stdin);
        quitaenter(p.descrip);
        
        lista_cat();
        printf("Escribe la categoria que quieras asociar al producto.\nCategoria: ");
        fflush(stdin);
        fgets(aux2,51,stdin);
        quitaenter(aux2);
        cataid(p.id_categ,aux2);
        
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
            carga=getchar();
            while ((a = getchar()) != '\n' && a != EOF) { }//Limpia el buffer de entrada
            
            if (carga=='s')
            {

                if ( id == NULL){

                    printf("Introduce la id de un gestos: ");
                    fflush(stdin);
                    gets(id_gestor_nuevo);

                   // i=0;
                   // while( i<)

                    strcpy(p.id_gestor,id_gestor_nuevo);

                }else{

                    strcpy(p.id_gestor,id);
                }

                //Obtencion de la proxima id disponible
                if (tamanio_p==0)
                {
                    strcpy(p.id_prod,"0000001\0");
                }
                else
                {
                    strcpy(aux,array_prod[tamanio_p-1].id_prod);
                    suma1(aux,7);//Suma a la cadena 1
                    strcpy(p.id_prod,aux);
                }
                //Subida del producto al vector
                tamanio_p=tamanio_p+1;
                if((array_prod=(producto *)realloc(array_prod,(tamanio_p)*(sizeof(producto))))!=NULL)//agrega espacio al vector para poner el nuevo producto
                {
                    array_prod[(tamanio_p)-1]=p;

                    error=0;
                    salida='s';
                }
                else
                {
                    printf("Se ha producido un error en la carga del producto.\n");
                    tamanio_p=tamanio_p-1;
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
            
            salida=getchar();
            while ((a = getchar()) != '\n' && a != EOF) { }//Limpia el buffer de entrada
            
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
void alta_categoria()
{
    int error,a;
    categoria c;
    char salida,carga,aux[5];
    printf("Comienzo de alta de una categoria.\n");
    do{
        printf("Escribe la descripcion de la categoria.\nEsta no puede contener guiones o ser mayor de 51 caracteres.\n");
        fflush(stdin);
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
            fflush(stdin);
            carga=getchar();
            while ((a = getchar()) != '\n' && a != EOF) { }//Limpia el Buffer de entrada
            if (carga=='s')
            {
                //Obtencion de la proxima id
                if (tamanio_c==0)
                {
                    strcpy(c.id_cat,"0001\0");
                }
                else
                {
                    strcpy(aux,array_cat[tamanio_c-1].id_cat);
                    suma1(aux,4);
                    strcpy(c.id_cat,aux);
                    tamanio_c++;
                }
                if ((array_cat=(categoria *)realloc(array_cat,(tamanio_c)*sizeof(categoria)))==NULL)
                {
                    printf("Error de memoria.\n");
                    tamanio_c--;
                    error=2;
                }
                else
                {
                    array_cat[tamanio_c-1]=c;
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
            salida=getchar();
            while ((a = getchar()) != '\n' && a != EOF) { }//Limpia el Buffer de entrada
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
static void baja_producto(int *asoc,sesion ses,int tamanio_asoc)
{
    int i,indice,a,encontrado=0;
    char salida='s';
    char id_prod[8];
    char confirmar='n';
    system("cls");
    if(ses.perfil_usuario==admin)
    {
        printf("Como administrador, puede eliminar cualquier producto del sistema.\n");
        listado_prod();
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
            if (encontrado==1)
            {
                printf("Va a borrar el producto %s,desea confirmar? Escriba 's' para confirmar\n",array_prod[indice].nombre);
                while ((a = getchar()) != '\n' && a != EOF) { }//Limpieza de buffer
                confirmar=getchar();
                if(confirmar=='s')
                {
                    salida='n';
                    borrar_producto(indice);
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
        listado_prod_asoc(asoc,tamanio_asoc);
        do{
            while ((a = getchar()) != '\n' && a != EOF) { }//Limpieza de buffer
            printf("Escribe el identificador del producto a eliminar.\nId: ");
            fgets(id_prod,8,stdin);
            for (i=0;i<tamanio_asoc&&encontrado;i++)//Encuentra el indice del producto a borrar
            {
                if(strcmp(array_prod[asoc[i]].id_prod,id_prod)==0)
                {
                    encontrado=1;
                    indice=asoc[i];
                }
            }
            if (encontrado==1)
            {
                printf("Va a borrar el producto %s,desea confirmar? Escriba 's' para confirmar\n",array_prod[indice].nombre);
                while ((a = getchar()) != '\n' && a != EOF) { }//Limpieza de buffer
                confirmar=getchar();
                if(confirmar=='s')
                {
                    salida='s';
                    borrar_producto(indice);
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
void baja_categoria()
{
    int a,*asoc,tamanio_asoc=0,i,indice,error=0;
    char salida='n',id_cat[5],descrip[51],confirmar;
    asoc=(int *)malloc((tamanio_p)*sizeof(producto));//asoc es un vector que va a contener todas los indices de los productos que coincidan con la categoria a borrar

    do{
        printf("Escribe el identificador de la categoria a borrar.\n");
        fflush(stdin);
        fgets(id_cat,5,stdin);
        while ((a = getchar()) != '\n' && a != EOF) { }//Limpia el Buffer de entrada
        indice=idacat(descrip,id_cat);
        if(descrip[0]=='-')//'-' significa que no se ha encontrado la id
        {
            printf("No se ha encontrado la categoria\nDesea cancelar la baja? Escriba 's' para salir");
            salida=getchar();
            while ((a = getchar()) != '\n' && a != EOF) { }//Limpieza de buffer
        }
        else
        {

            system("cls");
            printf("Va a borrar la categoria %s.\nEscriba 's' para confirmar\n",descrip);
            fflush(stdin);
            confirmar=getchar();
            while ((a = getchar()) != '\n' && a != EOF) { }//Limpieza de buffer
            if (confirmar=='s')
            {
                for (i=0;i<tamanio_p;i++)
                {
                    if(strcmp(id_cat,array_prod[i].id_categ)==0)
                    {
                        asoc[tamanio_asoc]=i;
                        tamanio_asoc++;
                    }
                }
                asoc=(int *)realloc(asoc,tamanio_asoc*sizeof(int));
                if (tamanio_asoc!=0)
                {
                    system("cls");

                    listado_prod_asoc(asoc,tamanio_asoc);
                    printf("\n\nLos siguientes productos estan asociados a la categoria a borrar.\nBorrar esta categoria tambien borrara esos productos.\nSi no quiere borrarlos, cancele y asocie dichos productos a otra categoria.\nDesea continuar? Escriba 's' para continuar.\n");
                    fflush(stdin);
                    confirmar=getchar();
                    while ((a = getchar()) != '\n' && a != EOF) { }//Limpieza de buffer
                    if (confirmar=='s')
                    {
                        for (i=0;i<tamanio_asoc;i++)//Borrado de los productos asociados a la categoria
                        {
                            borrar_producto(asoc[i]);
                        }
                        for (i=indice;i<tamanio_c-1;i++)//Borrado de la categoria
                        {
                            array_cat[i]=array_cat[i+1];
                        }
                        tamanio_c--;
                        array_cat=(categoria *)realloc(array_cat,(tamanio_c)*sizeof(categoria));
                        printf("Borrado de categoria con exito\n");
                        system("pause");
                    }
                    else
                    {
                        printf("Baja de categoria abortada.\n");
                        error = 1;
                        while ((a = getchar()) != '\n' && a != EOF) { }//Limpieza de buffer
                    }

                }else
                {
                    for (i=indice;i<tamanio_c-1;i++)//Borrado de la categoria
                        {
                            array_cat[i]=array_cat[i+1];
                        }
                        tamanio_c--;
                        array_cat=(categoria *)realloc(array_cat,(tamanio_c)*sizeof(categoria));
                        printf("Borrado de categoria con exito\n");
                }
            }
            else
            {
                {
                    printf("Baja de categoria abortada.\n");
                    error=1;
                    system("pause");
                    while ((a = getchar()) != '\n' && a != EOF) { }//Limpieza de buffer
                }
                
            }
        }
    }while(error == 1);
    free(asoc);
}
void guardar_producto ()
{
    FILE *f;
    int i;
    if ((f=fopen("Files\\Productos.txt","w"))==NULL)
    {
        printf("Error de apertura de fichero., no se han guardado los datos");
    }
    else
    {
        rewind(f);
        for (i=0;i<tamanio_p;i++)//Volcado de un elemento
        {
            fputs(array_prod[i].id_prod,f);
            fputc('-',f);
            fputs(array_prod[i].nombre,f);
            fputc('-',f);
            fputs(array_prod[i].descrip,f);
            fputc('-',f);
            fputs(array_prod[i].id_categ,f);
            fputc('-',f);
            fputs(array_prod[i].id_gestor,f);
            fputc('-',f);
            fprintf(f,"%d",array_prod[i].stock);
            fputc('-',f);
            fprintf(f,"%d",array_prod[i].entrega);
            fputc('-',f);
            fprintf(f,"%d",array_prod[i].importe);

            if(i < tamanio_p - 1) {
                fputc('\n',f);
            }

        }
    }
    fclose(f);
    free(array_prod);  
}
void guardar_categoria()
{
    FILE *f;
    int i;
    if ((f=fopen(F_CATEGORIAS,"w"))==NULL)
    {
        printf("Error de apertura de fichero.");
    }
    else
    {
        for (i=0;i<tamanio_c;i++)//Volcado de un elemento
        {
            fputs(array_cat[i].id_cat,f);
            fputc('-',f);
            fputs(array_cat[i].descrip,f);
            if ( i < tamanio_c-1 ) fputc('\n',f);
        }
    }
    fclose(f);
    free(array_cat);
}
void cargar_producto()
{
    FILE *f;
    char aux[51];//Cadena auxiliar para rellenar los datos, 51 es el valor de la cadena más larga
    char j;
    int i;


    if((f=fopen(F_PRODUCTO,"r"))==NULL)
    {
            printf("ERROR: No se ha encontrado el fichero Productos.txt, no se ha podido cargar memoria de los productos.\n");
            tamanio_p=0;
    }
    else
    {
        for(i=0;j!=EOF;i++){

            array_prod=(producto *)realloc(array_prod,(i+1)*sizeof(producto));
            fgets(array_prod[i].id_prod,8,f);
            fseek(f,1,SEEK_CUR);
            //nombre y descrip varian en tamaño, por lo que fgets leera basura
            obtener_dato_f(&f,array_prod[i].nombre);
            obtener_dato_f(&f,array_prod[i].descrip);
            fgets(array_prod[i].id_categ,5,f);
            fseek(f,1,SEEK_CUR);
            fgets(array_prod[i].id_gestor,5,f);
            fseek(f,1,SEEK_CUR);
            //obtencion de enteros, primero leerlo como cadena y luego pasarlo a entero
            obtener_dato_f(&f,aux);
            array_prod[i].stock=atoi(aux);
            obtener_dato_f(&f,aux);
            array_prod[i].entrega=atoi(aux);
            obtener_dato_f(&f,aux);
            array_prod[i].importe=atoi(aux);
            j=fgetc(f);
            fseek(f,-1,SEEK_CUR);



            }//Bucle para obtener cada dato{


    }

    (tamanio_p)=i;
    fclose(f);

}
        

void cargar_categoria()
{
    FILE *f;
    int i;
    char j='-';
    if ((array_cat=(categoria *)malloc(sizeof(categoria)))==NULL)
    {
        printf("Error de alocación de memoria.\n");
    }
    else
    {
        if((f=fopen(F_CATEGORIAS,"r"))==NULL)
        {
            printf("ERROR: No se ha encontrado el fichero Categorias.txt, no se ha podido cargar memoria de las categorias.\n");
            tamanio_c=0;
        }
        else
        {
            for(i=0;j!=EOF;i++)//Bucle para obtener cada dato
            {
                array_cat=(categoria *)realloc(array_cat,((i+1)*sizeof(categoria)));
                fgets(array_cat[i].id_cat,5,f);
                fseek(f,1,SEEK_CUR);
                fgets(array_cat[i].descrip,51,f);//Dejara de leer en EOF o en '/n'
                quitaenter(array_cat[i].descrip);
                j=fgetc(f);
                fseek(f,-1,SEEK_CUR);
            }
            (tamanio_c)=i;
            fclose(f);
        }
    }
}
int idacat(char *descrip,char *id)
{
    descrip[0]='-';
    descrip[1]='\0';
    int encontrado=1,indice=0;
    for (int i=0;(i<tamanio_c)&&(encontrado);i++)
    {
        if (strcmp(array_cat[i].id_cat,id)==0)
        {
            strcpy(descrip,array_cat[i].descrip);
            encontrado=0;
            indice=i;
        }
    }
    return indice;
}
void cataid(char *id,char *descrip)
{
    id[0]='-';
    id[1]='\0';
    int encontrado=1;
    for (int i=0;(i<tamanio_c)&&(encontrado);i++)
    {
        if (strcmp(array_cat[i].descrip,descrip)==0)
        {
            strcpy(id,array_cat[i].id_cat);
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
        error=2;
    }
    return error;
}
//Cabecera: static void lista_prod(producto *lista,categoria *c)
//Precondicion: Todos los campos de lista y c deben estar inicializados
//Poscondicion: Imprime por pantalla lista como una lista de los productos
static void lista_prod()
{
    char descrip_cat[51];//auxiliar para guardar la descripcion de la categoria
    printf("-------------------------------------------------------\n");
    for(int i=0;i<tamanio_p;i++)
    {
        idacat(descrip_cat,array_prod[i].id_categ);
        printf("Nombre: %s\n",array_prod[i].nombre);
        printf("Descripcion: %s\n",array_prod[i].descrip);
        printf("Categoria: %s\n",descrip_cat);
        printf("Precio: %d euros\n",array_prod[i].importe);
        printf("Stock: %d unidades\n",array_prod[i].stock);
        printf("Entrega en %d dias\n",array_prod[i].entrega);
        printf("Identificador: %s\n",array_prod[i].id_prod);
        printf("-------------------------------------------------------\n");
    }
}
//Cabecera: static void lista_cat(categoria *lista)
//Precondicion: Todos los campos de lista deben estar inicializados, tamanio <= nº de elementos de lista.
//Poscondicon: Imprime por pantalla lista como una lista de las categorias
static void lista_cat()
{
    printf("-------------------------------------------------------\n");
    for(int i=0;i<tamanio_c;i++)
    {
        printf("Descripcion: %s\n",array_cat[i].descrip);
        printf("Identificador: %s\n",array_cat[i].id_cat);
        printf("-------------------------------------------------------\n");
    }
}
//Cabecera: static void lista_prod_asoc(producto *p,int *asoc,categoria *c,int tamanio_c,int tamanio_asoc)
//Precondicion: Todas las entradas asignadas, todos los elementos de asoc deben ser menores que el numero de elementos del vector p
//Poscondicion: Imprime por pantalla todos los productos que apunte cada indice de asoc en p
static void lista_prod_asoc(int *asoc,int tamanio_asoc)
{
    char descrip_cat[51];//auxiliar para guardar la descripcion de la categoria
    printf("-------------------------------------------------------\n");
    for(int i=0;i<tamanio_asoc;i++)
    {
        idacat(descrip_cat,array_prod[asoc[i]].id_categ);
        printf("Nombre: %s\n",array_prod[asoc[i]].nombre);
        printf("Descripcion: %s\n",array_prod[asoc[i]].descrip);
        printf("Categoria: %s\n",descrip_cat);
        printf("Precio: %d€\n",array_prod[asoc[i]].importe);
        printf("Stock: %d unidades\n",array_prod[asoc[i]].stock);
        printf("Entrega en %d dias\n",array_prod[asoc[i]].entrega);
        printf("Identificador: %s\n",array_prod[asoc[i]].id_prod);
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
static void listado_prod()
{
    int i;
    char aux[51];
    printf("Identificador-Nombre-Descripcion-Categoria-Precio-Stock-Entrega-Gestor.\n");
    for (i=0;i<tamanio_p;i++)
    {
        idacat(aux,array_prod[i].id_categ);
        printf("%s|%s|%s|%s|%d euros|%d Uds.|%d dias|%s\n",array_prod[i].id_prod,array_prod[i].nombre,array_prod[i].descrip,aux,array_prod[i].importe,array_prod[i].stock,array_prod[i].entrega,"Por implementar");
    }
}
//Cabecera: static void listado_prod_asoc(producto *p,int *asoc,categoria *c,int tamanio_c,int tamanio_p)
//Precondicion: p y c definidas, tamanio_c y tamanio_p son equivalentes al numero de elementos de p y de c
//Poscondicion: Muestra por pantalla una lista de los productos de forma mas compacta a traves de un vector que asocia las posiciones de los productos
static void listado_prod_asoc(int *asoc,int tamanio_asoc)
{
    int i;
    char aux[51];

    printf("----------------------------------------------------------------------------\n\n");
    printf("Identificador-Nombre-Descripcion-Categoria-Precio-Stock-Entrega-Gestor.\n\n");
    for (i=0;i<tamanio_asoc;i++)
    {
        idacat(aux,array_prod[i].id_categ);
        printf("%s-%s-%s-%s-%d-%d-%d-%s\n",array_prod[asoc[i]].id_prod,array_prod[asoc[i]].nombre,array_prod[asoc[i]].descrip,aux,array_prod[asoc[i]].importe,array_prod[asoc[i]].stock,array_prod[asoc[i]].entrega,"Por implementar");
    }

    printf("----------------------------------------------------------------------------\n");
}
//Cabecera: static void borrar_producto(producto **p,int *tamanio_prod,int indice)
//Precondicion: *tamanio_prod debe ser el numero de indices de *p, indice<*tamanio_prod
//Poscondicion: borra el elemento indice del vector p y reduce el tamaño del vector en uno
void borrar_producto(int indice)
{
    for (int i=indice;i<(tamanio_p)-1;i++)//Borra el producto mediante la sustitucion de este por el siguiente
    {
        array_prod[i]=array_prod[i+1];
    }
    tamanio_p=(tamanio_p)-1;
    array_prod=(producto *)realloc(array_prod,(tamanio_p)*sizeof(producto));

    system("cls");
    printf("Ha eliminado el producto exitosamente.\n");
    system("pause");

}
//Cabecera: static void modificar_producto(sesion ses);
//Precondicion: array_prod y array_cat deben estar cargados mediante volcar_producto y volcar_categoria. tamanio_p y tamanio_c deben ser el numero de elementos de array_prod y arra_cat respectivamente
//Poscondicion: Muestra por pantalla un menu por el que el usuario puede modificar cualquier caracteristica de los productos que tenga permiso modificar.
static void modificar_producto(sesion ses,int *asoc,int tamanio_asoc)
{
    int encontrado=0,indice,a,i;
    char *id_prod,salida='n';
    if(ses.perfil_usuario==admin)
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
        listado_prod_asoc(asoc,tamanio_asoc);
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
 void menu_modificar_producto (int indice)
{
    int asoc[1]={indice},a,aux_int;
    char seleccion,aux[51],confirmar,id[8],descrip[51];

    system ("cls");
    lista_prod_asoc(asoc,1);
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
            printf("Va a remplazar el siguiente valor\n Descripcion: %s <- %s \n Escriba 's' para confirmar",array_prod[indice].descrip,aux);
            confirmar=getchar();
            while ((a = getchar()) != '\n' && a != EOF) { }//Limpieza de buffer
            if (confirmar=='s')
                strcpy(array_prod[indice].descrip,aux);
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
            printf("Va a remplazar el siguiente valor\n Entrega: %i dias <- %i dias\n Escriba 's' para confirmar",array_prod[indice].entrega,aux_int);
            confirmar=getchar();
            while ((a = getchar()) != '\n' && a != EOF) { }//Limpieza de buffer
            if (confirmar=='s')
                array_prod[indice].entrega=aux_int;
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
        lista_cat();
        printf("Escribe el nombre de la categoria a asignar\n");
        fgets(aux,51,stdin);
        cataid(aux,id);
        if (id[0]=='-')
        {
            printf("Error, el nombre introducido no coincide con ninguna categoria\n");
            system("pause");
        }
        else
        {
            idacat(descrip,array_prod[indice].id_categ);
            printf("Va a remplazar el siguiente valor\n Categoria: %s <- %s \n Escriba 's' para confirmar",descrip,aux);
            confirmar=getchar();
            if (confirmar=='s')
                strcpy(array_prod[indice].id_categ,aux);
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
    printf("Identificador|Descripcion\n\n");
    for (int i=0;i<tamanio_c;i++)
    {
        printf("%s|%s\n",array_cat[i].id_cat,array_cat[i].descrip);
    }
}
//Cabecera: static void modificar_categoria();
//Precondicion: El usuario debe ser administrador
//Poscondicion: Muestra por pantalla un menu interactivo en el que el usuario puede cambiar el nombre de cualquier categoria
void modificar_categoria()
{
    int indice,a,error=0;//Indice es el indice de la categoria a cambiar dentro del vector
    char id[5],descrip[51],salida,confirmar;//id y desc son auxiliares que almacenan la id a cambiar y la nueva descripcion

    do{

        system("cls");
        printf("Categorias disponibles.\n\n");
        listado_cat();
        printf("Escriba el identificador de la categoria a la que quiera cambiar el nombre.\n");
        fflush(stdin);
        fgets(id,5,stdin);
        indice=idacat(descrip,id);
        while ((a = getchar()) != '\n' && a != EOF) { }//Limpieza de buffer
        if (descrip[0]=='-')
        {
            printf("Error: No se ha encontrado la categoria.");
            error = 1;
        }

    } while (error == 1);

    system("cls");

    printf("Categoria a modificar: %s\nEscriba el nuevo nombre de la categoria\n",descrip);
    fgets(descrip,51,stdin);
    quitaenter(descrip);
    if(cadena_valida(descrip)==0)
    {
        printf("Va a modificar el siguiente valor.\nDescripcion %s <- %s\nQuiere continuar? Escriba 's' para confirmar\n",array_cat[indice].descrip,descrip);
        confirmar=getchar();
        while ((a = getchar()) != '\n' && a != EOF) { }//Limpieza de buffer

        error = 0;

        do{

            if (confirmar=='s')
            {
                strcpy(array_cat[indice].descrip,descrip);
                printf("Modificacion de categoria con exito\n");
                system("pause");
            }else
            {
                printf("Descripcion no valida.\n");
                salida=getchar();
                while ((a = getchar()) != '\n' && a != EOF) { }//Limpieza de buffer
                if (salida!='s')
                {
                    error = 1;
                }
            }

        } while (error==1);

            
    }

}

void menu_pedidos_prov( Pedido *ped , ProductoPedido **prod_ped, int *n_pedidos ,int *n_prod_ped, char id_admpr_act[5] ,usu tipo_usu ){

    int i,j,k,op,op_ped;
    int n;
    char id_pedido[8];

    do{

        n=1;

        printf("---------------------- Todos los pedidos asociados a sus productos ---------------------\n\n");

        for ( i=0 ; i<*n_pedidos; i++ ){

            j=0;
            while( j < *n_prod_ped && strcmp(ped[i].id_pedido,(*prod_ped)[j].id_pedido)!=0) j++;

            k=0;
            while( k < tamanio_p && strcmp(array_prod[k].id_prod,(*prod_ped)[j].id_prod)!=0 ) k++;

            if (strcmp( id_admpr_act , array_prod[k].id_gestor)==0){

                printf("[%i].%s-%s-%s-%s",n,ped[i].id_pedido,ped[i].fecha_ped,ped[i].id_cliente,ped[i].lugar_entrega);

                if (strcmp(ped[i].lugar_entrega,"domicilio")==0 ){

                    printf("-domicilio-%s\n",ped[i].id_cod_prom);

                }else if ( strcmp(ped[i].lugar_entrega,"locker") ==0) {

                    printf("-locker-%s-%s\n",ped[i].id_locker,ped[i].id_cod_prom);

                }

                n++;
            }

        }

        do{

            printf("\nElija una opcion:\n");
            printf("1.Gestionar estado\n2.Asignar transportista\n3.Asignar locker\n4.Salir\n");
            scanf("%i", &op);

            switch (op) {
                case 1:

                    printf("Escribe el pedido a modificar su estado: ");
                    fflush(stdin);
                    gets(id_pedido);

                    i=0;
                    while ( i<*n_prod_ped && strcmp(id_pedido,(*prod_ped)[i].id_pedido)!=0) i++;

                    system("cls");

                    printf("Elija el estado nuevo del pedido:\n\n1.enPreparacion\n2.enviado\n3.enReparto\n4.enLocker\n5.entregado\n6.devuelto\n7.transportista\n ");
                    scanf("%i",&op_ped);

                    switch (op_ped) {
                        case 1:

                            (*prod_ped)[i].est_pedido = enPreparacion;

                            break;
                        case 2:

                            (*prod_ped)[i].est_pedido = enviado;

                            break;
                        case 3:

                            (*prod_ped)[i].est_pedido =enReparto;

                            printf("Introduzca la id de un transportista para asignarle: ");
                            fflush(stdin);
                            gets((*prod_ped)[i].id_transp);

                            break;
                        case 4:

                            (*prod_ped)[i].est_pedido =enLocker;

                            printf("Introduzca la id de un transportista para asignarle: ");
                            fflush(stdin);
                            gets((*prod_ped)[i].id_transp);

                            printf("Introduzca el Id de un locker: ");
                            fflush(stdin);
                            gets((*prod_ped)[i].id_locker);

                            printf("Introduzca el codigo del locker (6 digitos): ");
                            fflush(stdin);
                            gets((*prod_ped)[i].cod_locker);

                            fecha_actual((*prod_ped)[i].fecha_entr_dev,0);

                            break;
                        case 5:

                            (*prod_ped)[i].est_pedido = entregado;

                            printf("Introduzca la id de un transportista para asignarle: ");
                            fflush(stdin);
                            gets((*prod_ped)[i].id_transp);

                            fecha_actual((*prod_ped)[i].fecha_entr_dev,0);

                            break;
                        case 6:

                            (*prod_ped)[i].est_pedido = devuelto;

                            printf("Introduzca la id de un transportista para asignarle: ");
                            fflush(stdin);
                            gets((*prod_ped)[i].id_transp);

                            fecha_actual((*prod_ped)[i].fecha_entr_dev,0);

                            break;
                        case 7:

                            (*prod_ped)[i].est_pedido = trasnportista;

                            break;
                    }


                    break;
                case 2:

                    printf("Escribe el pedido a modificar su estado: ");
                    fflush(stdin);
                    gets(id_pedido);

                    i=0;
                    while ( i<*n_prod_ped && strcmp(id_pedido,(*prod_ped)[i].id_pedido)!=0) i++;

                    printf("Introduzca la id de un transportista para asignarle: ");
                    fflush(stdin);
                    gets((*prod_ped)[i].id_transp);


                    break;
                case 3:
                    break;
                case 4: // salir
                    break;
                default:
                    printf("Escribe un numero del 1 al 4");
                    break;
            }




        }while ( op < 1 || op > 4 );


    }while( op != 4);

}



//POR HACER: REMPLAZAR TODAS LAS DECLARACIONES DE LOS VECTORES DE PRODUCTO Y CATEGORIA COMO SUS TAMAÑOS POR SUS VARIABLES PUBLICAS
//POR HACER: TESTEAR MODIFICACION DE PRODUCTO Y MENU DE CATEGORIA Y DEBUGARLO
//POR HACER: MEJORAR LAS LIMPIEZAS DEL BUFFER DE ENTRADA