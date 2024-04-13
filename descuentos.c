/*##### MÓDULO DESCUENTOS   #####*/
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>
#include "descuentos.h"
#define LINE 100

//Tipos 
typedef struct fecha{
    int dia, mes, anno;
}fecha;

/*CABECERAS*/
fecha fecha_actual();
fecha de_string_a_fecha(char*);
int comparar_fechas(fecha,fecha);
void crear_fichero_descuentos();
void crear_fichero_descuentos_clientes();
void leer_string(char*,int);
int num_desc_desde_fich();
int indice_con_id_descuento(Descuentos**,char*,int);

    /*MAIN PROVISIONAL*/
int main(){   //main para pruebas, quitar a la hora de unir los módulos
Descuentos *d;
int desc,*n_desc;
Descuentos_clientes *dc;
//char cad[]="0020312";
desc=num_desc_desde_fich();
n_desc=&desc;
//crear_fichero_descuentos();
//printf("\n%i\n",num_desc());
carga_descuentos(&d,n_desc);
carga_descuentos_clientes(&dc,n_desc);
listar_descuentos_propios(&d,&dc,"0020312",n_desc);
//nuevo_descuento(&d,&dc,n_desc);
volcado_descuentos(&d,n_desc);
volcado_descuentos_clientes(&dc,n_desc);

//carga_descuentos(&d);
//listar_descuentos(&d);
//volcado_descuentos(&d);
//printf("Id: %s\n",d[0].Id_cod);
return 0;
}

//Cuerpos de función

  /*FUNCIONES CON FICHEROS*/
//cabecera: crear_fichero_descuentos()
//preconción: ninguna
//postconción: crea el fichero descuentos
void crear_fichero_descuentos()
{
    FILE* f;
    if ((f = fopen("descuentos.txt", "a+")) == NULL)
        printf("Error al abrir el archivo(función crear)\n");
    fclose(f);
}

//cabecera: crear_fichero_descuentos_clientes()
//preconción: ninguna
//postconción: crea el fichero descuentos_clientes
void crear_fichero_descuentos_clientes()
{
    FILE* f2;
    if ((f2 = fopen("descuentos_clientes.txt", "a+")) == NULL)
        printf("Error al abrir el archivo\n");
    fclose(f2);
}

//cabecera: void nuevo_descuento(Descuentos **d)   MODIFICAR PARA CREAR EN descuentos_clinetes.txt su descuento asociado
//precondición: *n_desc puntero que apunta al número total de descuentos actual
//postcondición: crea y añade a la estructura un nuevo descuento
void nuevo_descuento(Descuentos **d,Descuentos_clientes **dc,int *n_desc){
    int sel,i=0;
    (*n_desc)++;
    if((*d = (Descuentos *)realloc(*d, *n_desc * sizeof(Descuentos)))==NULL){
        printf("Error al reservar memoria para los Descuentos\n");
        exit(1); 
    }
    if((*dc =(Descuentos_clientes*)realloc(*dc, *n_desc * sizeof(Descuentos_clientes)))==NULL){
        printf("Error al reservar memoria para los Descuentos_clientes\n");
        exit(1); 
    }
    (*dc)[*n_desc-1].Estado=no;
    //(*dc)[*n_desc-1].Id_cliente=cliente_actual();
    strcpy((*dc)[*n_desc-1].Id_cliente,"0020312"); //PROVISIONAL
    strcpy((*dc)[*n_desc-1].f_asignacion,"10/04/2024");
    printf("\nIntrozuca la Id del descuento:\n");     
    leer_string((*d)[*n_desc-1].Id_cod,11);           //Introducimos la Id del código
    
    strcpy((*dc)[*n_desc-1].Id_cod,(*d)[*n_desc-1].Id_cod);

    printf("\nIntroduzca una breve descripción del descuento:\n");
    leer_string((*d)[*n_desc-1].Descrip,51);                            //Introducimos la cadena

    printf("\nIntroduce el importe del descuento:\n");
    leer_string((*d)[*n_desc-1].Importe,4);               //Introducimos el importe del descuento

    while ((i=getchar()) != '\n' && i != EOF){} //limpiamos el buffer
    printf("\n Introduzca la fecha de caducidad del descuento formato:(dd/mm/aaaa)\n");
    leer_string((*dc)[*n_desc-1].f_caducidad,11);

    do{
        printf("\nElija un tipo de descuento:\n 1.Codpro\n 2.Cheqreg\n");
        scanf("%i",&sel);
        if (sel==1)
        {
            (*d)[*n_desc-1].Tipo=codpro;
            i++;
        }else if (sel==2)
        {
            (*d)[*n_desc-1].Tipo=cheqreg;
            i++;
        }else
        {
            printf("\nIntroduzca una opción válida\n");
        }
    }while(i==0);
    i=0;
    do{
        printf("\nElija el Estado del Descuento:\n 1.Activo\n 2.Inactivo\n");
        scanf("%i",&sel);
        if (sel==1)
        {
            (*d)[*n_desc-1].Estado=activo;
            i++;
        }else if (sel==2)
        {
            (*d)[*n_desc-1].Estado=inactivo;
            i++;
        }else
        {
            printf("\nIntroduzca una opción válida\n");
        }
    }while(i==0);
    i=0;
        do{
        printf("\nElija en los productos en los que se aplica:\n 1.Todos\n 2.Esizon\n");
        scanf("%i",&sel);
        if (sel==1)
        {
            (*d)[*n_desc-1].Aplicabilidad=todos;
            i++;
        }else if (sel==2)
        {
            (*d)[*n_desc-1].Aplicabilidad=esizon;
            i++;
        }else
        {
            printf("\nIntroduzca una opción válida\n");
        }
    }while(i==0);
   
   // (*dc)[*n_desc-1].f_asignacion==de_decha_a_string(fecha_actual());

}

//cabecera: void carga_descuentos(Descuentos **d)
//precondición: sea **d un doble puntero a una estructura descuentos 
//postcondición: carga en el vector de estructura Descuentos los datos desde el fichero descuentos.txt
void carga_descuentos(Descuentos **d,int *n_desc){
    int i;
    char line[LINE]="\0";
    char estado[10]="\0";
    FILE *f;

    if((f=fopen("descuentos.txt","r"))==NULL){
        printf("Error al abrir el archivo\n");
    }else{
    
        }
        if(((*d) = (Descuentos *)calloc(*n_desc, sizeof(Descuentos)))==NULL){
            printf("Error al reservar memoria para los Descuentos\n");
            exit(1);
        }else{
            rewind(f);
            for(i=0;i<*n_desc;i++){

                fgets(line,LINE,f);
                strcpy((*d)[i].Id_cod, strtok(line,"-"));
                strcpy((*d)[i].Descrip, strtok(NULL, "-\n"));  //cargamos los datos tipo char
                strcpy((*d)[i].Importe, strtok(NULL, "-\n"));

                strcpy(estado, strtok(NULL, "-\n"));//introducimos la siguiente cadena entre los '-'
                    

                    if(strcmp(estado,"codpro")==0){
                        (*d)[i].Tipo=codpro;

                    }else if(strcmp(estado, "cheqreg")==0){
                        (*d)[i].Tipo=cheqreg;
                    }else{puts("Error del campo TIPO"); }

                    for(int k=0;k<10;k++) estado[k]='\0';
                
                    strcpy(estado, strtok(NULL, "-\n"));
                    
                    if(strcmp(estado,"activo")==0){
                        (*d)[i].Estado=activo;

                    }else if(strcmp(estado,"inactivo")==0){
                        (*d)[i].Estado=inactivo;
                    }else{puts("Error del campo ESTADO"); }

                    for(int k=0;k<10;k++) estado[k]='\0';
                    strcpy(estado, strtok(NULL, "-\n"));

                    if(strcmp(estado, "todos")==0){
                        (*d)[i].Aplicabilidad=todos;

                    }else if(strcmp(estado, "esizon")==0){
                        (*d)[i].Aplicabilidad=esizon;
                    }else{puts("Error del campo APLICABILIDAD");}; 
                
                for(int k=0;k<10;k++) estado[k]='\0';

        }
    }
    rewind(f);
    fclose(f);

}

//cabecera: void carga_descuentos(Descuentos_clientes **dc)
//precondición: sea **d un doble puntero a una estructura descuentos_clientes 
//postcondición: carga en el vector de estructura Descuentos los datos desde el fichero descuentos.txt
void carga_descuentos_clientes(Descuentos_clientes **dc,int *n_desc_c){
    int i;
    char line[LINE]="\0";
    char estado[10]="\0";
    FILE *f;

    if((f=fopen("descuentos_clientes.txt","r"))==NULL){
        printf("Error al abrir el archivo\n");
    }else{
        
        *dc = (Descuentos_clientes *)calloc(*n_desc_c, sizeof(Descuentos_clientes));
        if(*dc==NULL){
            printf("Error al reservar memoria para los Descuentos\n");
            exit(1);
        }else{
            rewind(f);
            for(i=0;i<*n_desc_c;i++){

                fgets(line,LINE,f);
                strcpy((*dc)[i].Id_cliente, strtok(line,"-"));
                strcpy((*dc)[i].Id_cod, strtok(NULL, "-\n"));  //cargamos los datos tipo char
                strcpy((*dc)[i].f_asignacion, strtok(NULL, "-\n"));
                strcpy((*dc)[i].f_caducidad, strtok(NULL, "-\n"));

                strcpy(estado, strtok(NULL, "-\n"));//introducimos la siguiente cadena entre los '-'
                    

                    if(strcmp(estado,"si")==0){
                        (*dc)[i].Estado=si;

                    }else if(strcmp(estado, "no")==0){
                        (*dc)[i].Estado=no;
                    }else{puts("Error del campo ESTADO"); }

                 for(int k=0;k<10;k++) estado[k]='\0';
            }   
        }
    }
    rewind(f);
    fclose(f);

}

//cabecera:void volcado_descuentos(Descuentos **d)
//precondición:**d incializado y descuentos.txt creado
//postcondición:descuentos.txt contiene la información que contenía el vector de estructuras
void volcado_descuentos(Descuentos **d,int*n_desc){

    char line[LINE]="\0";
    FILE *f;

    if ((f = fopen("Descuentos.txt", "w+")) == NULL) {

        printf("Error al abrir el archivo");

    } else {

        for ( int i=0 ; i<*n_desc ; i++ ){
           // strcpy(line,"\n");
            strcpy(line, (*d)[i].Id_cod);
            
            strcat(line, "-");
            strcat(line, (*d)[i].Descrip);
            strcat(line, "-");
            strcat(line, (*d)[i].Importe);
            strcat(line, "-");
            if((*d)[i].Tipo==cheqreg){
                strcat(line,"cheqreg");
            }else if((*d)[i].Tipo==codpro){
                strcat(line,"codpro");
            }else{
                puts("Error en el volcado de TIPO");
            }

             strcat(line, "-");
            if((*d)[i].Estado==activo){
                strcat(line,"activo");
            }else if((*d)[i].Estado==inactivo){
                strcat(line,"inactivo");
            }else{
                puts("Error en el volcado de ESTADO");
            }

             strcat(line, "-");
            if((*d)[i].Aplicabilidad==esizon){
                strcat(line,"esizon");
            }else if((*d)[i].Aplicabilidad==todos){
                strcat(line,"todos");
            }else{
                puts("Error en el volcado de APLICABILDAD");
            }
            
           if(i < *n_desc - 1) strcat(line, "\n");
            fprintf(f, "%s", line);
        }

    }

    fclose(f);

}

//cabecera:void volcado_descuentos_clientes(Descuentos_clientes **dc)
//precondición:**dc incializado y descuentos_clientes.txt creado
//postcondición:descuentos_clientes.txt contiene la información que contenía el vector de estructuras
void volcado_descuentos_clientes(Descuentos_clientes **dc,int *n_desc_c){

    int i;
    char line[LINE]="\0";
    FILE *f;

    if ((f = fopen("Descuentos_clientes.txt", "w+")) == NULL) {

        printf("Error al abrir el archivo");

    } else {

        for ( i=0 ; i<*n_desc_c ; i++ ){
           // strcpy(line,"\n");
            strcpy(line, (*dc)[i].Id_cliente);
            
            strcat(line, "-");
            strcat(line, (*dc)[i].Id_cod);
            strcat(line, "-");
            strcat(line, (*dc)[i].f_asignacion);
            strcat(line, "-");
            strcat(line, (*dc)[i].f_caducidad);
            strcat(line, "-");

            if((*dc)[i].Estado==si){
                strcat(line,"si");
            }else if((*dc)[i].Estado==no){
                strcat(line,"no");
            }else{
                puts("Error en el volcado de ESTADO");
            }
           if(i < *n_desc_c - 1) strcat(line, "\n");
            fprintf(f, "%s", line);
        }

    }

    fclose(f);



}

//cabecera: void listar_descuentos(Descuentos *d)
//precondición: *d inicializado
//postcondición: lista los descuentos actuales en el vector
void listar_descuentos(Descuentos**d,int*n_desc){
    int i=0;
    puts("Lista de Descuentos, por ID:");
    do
    {
        printf(" %i.",i+1);
        puts((*d)[i].Id_cod);
        i++;
    } while (i<=*n_desc-1);
    
}

//cabecera:void listar_descuentos_propios(char*Id_cliente)
//precondición:sea Id cliente un punteroa  char que apunta a la información en la estructura
//postcomdición: imprime por pantalla la lsita de descuentos asignados a esa ID de cliente 
void listar_descuentos_propios(Descuentos **d, Descuentos_clientes **dc,char *Id_cliente,int*n_desc){
    int i=0,cont=1,j;
    //Id_a_user(*Id_cliente);
    printf("Descuentos de %s:\n",Id_cliente);
    do
    {
        if(strcmp((*dc)[i].Id_cliente,Id_cliente)==0){
            j=indice_con_id_descuento(d,(*dc)[i].Id_cod,*n_desc);
             printf(" %i.",cont);
             puts((*dc)[i].Id_cod);
             printf("Cantidad:");
             puts((*d)[j].Importe);
             printf("Fecha de expedición:");
             puts((*dc)[i].f_asignacion);
             printf("Fecha de caducidad:");
             puts((*dc)[i].f_caducidad);
             if((*d)[j].Estado==activo){printf("Descuento activo\n\n");}
             else{ printf("Descuento inactivo\n\n");}
             cont++;
        }
       
        //puts((*dc)[i].Id_cod);
        i++;
    } while (i<=*n_desc-1);

}

//cabecera:int num_desc()
//precondición: archivo .txt inicializado
//postcondición:devuelve el número de líneas que tiene el fichero
int num_desc_desde_fich(){
char c; 
int n_lin,i;
n_lin=0;
i=0;

FILE *f;
if((f= fopen("descuentos.txt","r"))==NULL){
       printf("Error al abrir el archivo\n");
    }else{
        while(i==0){

            c = fgetc(f);

            if(c == '\n'){
                n_lin++;
            }
            if(c == EOF){  //Si el caracter es end of file imprimimos el contador y salimos del while
               // printf("%i",n_lin);  //El número de lineas
                i++;
            }
        }
    }
 return (n_lin+1);
}

//cabecera: int comprobar_descuento(Descuentos_clientes**dc,char Id_cod[])
//precondición: **dc inicializado e Id_cod un código de descuento válido
//postcondición: devuelve: 0 si está en vigor y 1 si no es válido por cualquier otra razón, además imprime por pantalla el error producido
int comprobar_descuento(Descuentos_clientes**dc,char *Id_cod){
    int i=0,c_salida=0,ret;
    
    while (c_salida==0)
    {
        if((*dc)[i].Id_cod==Id_cod) c_salida++ ;
        else
        {
            i++;
        }
    }

    if((*dc)[i].Estado== si || comparar_fechas(de_string_a_fecha((*dc)[i].f_caducidad),fecha_actual())>0) ret=1;


    return ret;
}

   /*FUNCIONES DE FECHAS*/

// cabecera: fecha fecha_actual()
// precondición: ninguna
// postcondición: devuelve una estructura fecha con la fecha actual
fecha fecha_actual()
{ // FUNCIONA
    fecha fecha_actual;
    time_t t = time(NULL);
    struct tm tiempo_actual = *localtime(&t);

    // Pasamos los datos desde la estructura tm a fecha
    fecha_actual.dia = tiempo_actual.tm_mday;
    fecha_actual.mes = tiempo_actual.tm_mon + 1;
    fecha_actual.anno = tiempo_actual.tm_year + 1900;

    return fecha_actual;
}


// cabecera: int comparar_fechas(fecha fecha1, fecha fecha2)
// precondicion: fecha1 y fecha2 inicializados
// postcondicion: devuelve => =0 - fechas iguales
//                            >0 - fechas1 mayor que fecha2
//                            <0 - fecha1 menor que fecha2
int comparar_fechas(fecha fecha1, fecha fecha2)
{ // FUNCIONA
    int resultado = 0;
    if (fecha1.anno == fecha2.anno)
        if (fecha1.mes == fecha2.mes)
            if (fecha1.dia == fecha2.dia)
                resultado = 0;
            else if (fecha1.dia > fecha2.dia)
                resultado = 1;
            else
                resultado = -1;

        else if (fecha1.mes > fecha2.mes)
            resultado = 1;
        else
            resultado = -1;

    else if (fecha1.anno > fecha2.anno)
        resultado = 1;
    else
        resultado = -1;

    return resultado;
}


// cabecera: fecha de_string_a_fecha(char *cadena)
// precondición: cadena inicializada con una fecha válida
// postcondición: convierte cadena en una fecha y lo devuelve
fecha de_string_a_fecha(char* cadena)
{ // FUNCIONA
    char s_dia[3], s_mes[3], s_anno[5];
    fecha ej_fecha;

    // Almacenamos el dia en una cadena
    s_dia[0] = cadena[0];
    s_dia[1] = cadena[1];
    s_dia[2] = '\0';

    // Almacenamos el mes en una cadena
    s_mes[0] = cadena[3];
    s_mes[1] = cadena[4];
    s_mes[2] = '\0';

    // Almacenamos el año en una cadena
    s_anno[0] = cadena[6];
    s_anno[1] = cadena[7];
    s_anno[2] = cadena[8];
    s_anno[3] = cadena[9];
    s_anno[4] = '\0';

    // Convertimos el dia, mes y año en enteros
    ej_fecha.dia = (int)strtol(s_dia, NULL, 10);
    ej_fecha.mes = (int)strtol(s_mes, NULL, 10);
    ej_fecha.anno = (int)strtol(s_anno, NULL, 10);

    return ej_fecha;
}

  /*FUNCIONES VARIAS*/

// cabecera: void leer_string(char * cadena, int elem)
// precondicion: ninguna
// postcondicion: lee en cadena la cadena introducida por el usuario
void leer_string(char*cadena, int elem)
{
    int i;
   
    fflush(stdin);
    fgets(cadena,elem,stdin);
    fflush(stdin);
    //puts(cadena);
    for (i = 0; cadena[i] != '\n' && i < elem + 1; i++)
        if (cadena[i] == '\n')
            cadena[i] = '\0';

    i = 0;
    while (i < elem + 1) {
        if (cadena[i] == '\n')
            cadena[i] = '\0';
        i++;
    }
}


void siguiente_id(char*cad,int i){
    for(int j=0;(i>=0)&&(j==0);i--)
        if(cad[i-1]=='9'){
            cad[i-1]='0';
        }else{
            cad[i-1]++;
            j=1;
        }
}   

//cabecera:int indice_con_id_descuentos(Cliente **vector_descuentos,cha*id_desc,int num_desc)
//precondición: vector cliente un vector de estructura descuentos, id_desc una cadena y num_desc el número de descuentpos registrados del vector
//postcondición: devuelve el valor del indice del vector de estructura cuya id coincide con el de la cadena
int indice_con_id_descuento(Descuentos**vector_descuentos,char *id_descuento,int num_desc){
    int i=0,devolver;
    do{
        if(strcmp(id_descuento,(*vector_descuentos)[i].Id_cod)==0){
        devolver=i;
    }
        i++;
    }while(i<=num_desc);
    return devolver;
}


