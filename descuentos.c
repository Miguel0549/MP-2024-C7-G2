/*##### MÓDULO DESCUENTOS   #####*/
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>
#include "descuentos.h"
//#include "sesiones.h"
//#include "sesiones.c"
#define LINE 100

#include "Devoluciones.h"

/*CABECERAS*/
    void fecha_actual();
    fecha de_string_a_fecha(char*);
    int comparar_fechas(fecha,fecha);
    void crear_fichero_descuentos();
    void crear_fichero_descuentos_clientes();
    void leer_string(char*,int);
    int num_desc_desde_fich();
    int num_desc_clien_desde_fich();
    int indice_con_id_descuento(Descuentos**,char*,int);
    int indice_con_id_descuento_cl(Descuentos_clientes**,char*,int);
    void borrar_descuento_con_id(Descuentos**,Descuentos_clientes**,char*,int *,int*);


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
/*
void nuevo_descuento(Descuentos **d,Descuentos_clientes **dc,int *n_desc,int*n_desc_clien){

    int *n_lin,lin,indice,k,indice_d,num,buffer,sel,i=0;
    char id_cliente[7]="\0";
    //char fecha[11]="\0";
    lin=0;
    num=num_cliente_fich();
    n_lin=&lin;
    indice=(*n_desc_clien);
    indice_d=(*n_desc);
    (*n_desc_clien)++;
    (*n_desc)++;
    if((*d = (Descuentos *)realloc(*d, *n_desc * sizeof(Descuentos)))==NULL){
        printf("Error al reservar memoria para los Descuentos\n");
        exit(1); 
    }
    if((*dc =(Descuentos_clientes*)realloc(*dc, *n_desc_clien * sizeof(Descuentos_clientes)))==NULL){
        printf("Error al reservar memoria para los Descuentos_clientes\n");
        exit(1); 
    }
    (*dc)[indice].Estado=no;
    fecha_actual((*dc)[indice_d].f_asignacion);
    //strcpy((*dc)[indice].f_asignacion,"10/04/2024");
    printf("\nIntrozuca la Id del descuento:\n");     
    leer_string((*d)[indice_d].Id_cod,11);           //Introducimos la Id del código
    puts((*d)[indice_d].Id_cod);
    strcpy((*dc)[indice].Id_cod,(*d)[indice_d].Id_cod);
    puts((*dc)[indice].Id_cod);
    printf("\nIntroduzca una breve descripción del descuento:\n");
    leer_string((*d)[indice_d].Descrip,51);                            //Introducimos la cadena

    printf("\nIntroduce el importe del descuento:\n");
    leer_string((*d)[indice_d].Importe,4);               //Introducimos el importe del descuento

    while ((i=getchar()) != '\n' && i != EOF){} //limpiamos el buffer
    printf("\nIntroduzca la fecha de caducidad del descuento formato:(dd/mm/aaaa)\n");
    leer_string((*dc)[indice].f_caducidad,11);

    i=0;
    do{
        printf("\nElija el Estado del Descuento:\n 1.Activo\n 2.Inactivo\n");
        scanf("%i",&sel);
        if (sel==1)
        {
            (*d)[indice_d].Estado=activo;
            i++;
        }else if (sel==2)
        {
            (*d)[indice_d].Estado=inactivo;
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
            (*d)[indice_d].Aplicabilidad=todos;
            i++;
        }else if (sel==2)
        {
            (*d)[indice_d].Aplicabilidad=esizon;
            i++;
        }else
        {
            printf("\nIntroduzca una opción válida\n");
        }
    }while(i==0);
    i=0;
    do{
        printf("\nElija un tipo de descuento:\n 1.Codpro\n 2.Cheqreg\n");
        scanf("%i",&sel);
        if (sel==1)
        {   
            (*d)[indice_d].Tipo=codpro;
            i++;
           // (*n_desc_clien)=(*n_desc_clien)+num; //sumamos al nuemro actual de desc_clientes el numero de clientes
            //if((*dc = (Descuentos_clientes *)realloc(*d, *n_desc_clien * sizeof(Descuentos_clientes)))==NULL){
            //    printf("Error al reservar memoria para los Descuentos\n");
           //     exit(1); 
            //} 
            pasar_ids_desde_fich(id_cliente,n_lin);
            strcpy((*dc)[indice].Id_cliente,id_cliente);
            if(num>1){
                k=0;
                while (k<num-1)
                {
                (*n_desc_clien)++;
                if((*dc = (Descuentos_clientes *)realloc(*dc, *n_desc_clien * sizeof(Descuentos_clientes)))==NULL){
                
                     printf("Error al reservar memoria para los Descuentos\n");
                    exit(1); 

                }
                (*n_lin)++;
                k++;
                pasar_ids_desde_fich(id_cliente,n_lin);
                strcpy((*dc)[indice+k].Id_cliente,id_cliente);
                puts(id_cliente);
                strcpy((*dc)[indice+k].Id_cod,(*dc)[indice].Id_cod);
                strcpy((*dc)[indice+k].f_caducidad,(*dc)[indice].f_caducidad);
                strcpy((*dc)[indice+k].f_asignacion,(*dc)[indice].f_asignacion);
                (*dc)[indice+k].Estado=(*dc)[indice].Estado;
                }
            }
        }else if (sel==2)
        {
            (*d)[indice_d].Tipo=cheqreg;
            i++;
            printf("Introduzca la id del Cliente al que quiere asignar el cheque regalo:\n");
            while ((buffer=getchar()) != '\n' && buffer != EOF){}
            leer_string(id_cliente,7);
            strcpy((*dc)[indice].Id_cliente,id_cliente);
        }else
        {
            printf("\nIntroduzca una opción válida\n");
        }
    }while(i==0);
   
   // (*dc)[indice_d].f_asignacion==de_decha_a_string(fecha_actual());

}*/

//cabecera: void carga_descuentos(Descuentos **d)
//precondición: sea **d un doble puntero a una estructura descuentos 
//postcondición: carga en el vector de estructura Descuentos los datos desde el fichero descuentos.txt
void carga_descuentos(Descuentos **d,int *n_desc){
    int i,j;
    char c;
    char line[LINE]="\0";
    char estado[10]="\0";
    FILE *f;
    j=0;
    if((f=fopen("descuentos.txt","r"))==NULL){
        printf("Error al abrir el archivo\n");
    }else{
    
        }
        if(((*d) = (Descuentos *)calloc(*n_desc, sizeof(Descuentos)))==NULL){
            printf("Error al reservar memoria para los Descuentos\n");
            exit(1);
        }else{
            rewind(f);
            c=fgetc(f);
            if(*n_desc==1 && c==EOF )
                j++;
            rewind(f);
            for(i=j;i<*n_desc;i++){                    

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
    int i,j;
    char line[LINE]="\0";
    char estado[10]="\0";
    char c;
    FILE *f;
    j=0;
    if((f=fopen("descuentos_clientes.txt","r"))==NULL){
        printf("Error al abrir el archivo\n");
    }else{
        
        *dc = (Descuentos_clientes *)calloc(*n_desc_c, sizeof(Descuentos_clientes));
        if(*dc==NULL){
            printf("Error al reservar memoria para los Descuentos\n");
            exit(1);
        }else{
            rewind(f);
            c=fgetc(f);
             if(*n_desc_c==1 && c==EOF)
                j++;
            rewind(f);
            for(i=j;i<*n_desc_c;i++){

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
//postcondición:descuentos.txt contiene la información que contenílolololola el vector de estructuras
void volcado_descuentos(Descuentos **d,int*n_desc){
    int aux;
    char line[LINE]="\0";
    FILE *f;
    aux=*n_desc;

    if ((f = fopen("Descuentos.txt", "w+")) == NULL) {

        printf("Error al abrir el archivo");

    } else {

        for ( int i=0 ; i<aux ; i++ ){
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
        c=getc(f);
        if(c==EOF){
            n_lin=-1;
        }else{
            while(i==0){

                 c = fgetc(f);

                if(c == '\n'){
                    n_lin++;
            }
            if(c == EOF) //Si el caracter es end of file imprimimos el contador y salimos del while
               // printf("%i",n_lin);  //El número de lineas
                i++;
            }  
        }
    }
 return (n_lin+1);
}


//cabecera:int num_desc()
//precondición: archivo .txt inicializado
//postcondición:devuelve el número de líneas que tiene el fichero
int num_desc_clien_desde_fich(){
char c; 
int n_lin,i;
n_lin=0;
i=0;

FILE *f;
if((f= fopen("descuentos_clientes.txt","r"))==NULL){
       printf("Error al abrir el archivo\n");
    }else{
         c=getc(f);
        if(c==EOF){
            n_lin=-1;
        }else{
            while(i==0){

                c = fgetc(f);

                if(c == '\n')
                n_lin++;
            
                if(c == EOF)  //Si el caracter es end of file imprimimos el contador y salimos del while
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
    char fecha[11]="\0";
    fecha_actual(fecha,0);
    while (c_salida==0)
    {
        if((*dc)[i].Id_cod==Id_cod) c_salida++ ;
        else
        {
            i++;
        }
    }

    if((*dc)[i].Estado== si || comparar_fechas(de_string_a_fecha((*dc)[i].f_caducidad),de_string_a_fecha(fecha))>0) ret=1;


    return ret;
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

int indice_con_id_descuento_cl(Descuentos_clientes**vector_descuentos_cl,char *id_descuento,int num_desc_cl){
    int i=0,devolver;
    do{
        if(strcmp(id_descuento,(*vector_descuentos_cl)[i].Id_cod)==0){
        devolver=i;
    }
        i++;
    }while(i<=num_desc_cl);
    if(strcmp(id_descuento,(*vector_descuentos_cl)[i].Id_cod)!=0)
        devolver=-1;
    return devolver;
}

//, modificaciones del los mismos, 

//
void borrar_descuento_con_id(Descuentos**vector_descuento,Descuentos_clientes**dc,char *Id_descuento, int *n_descuento,int*n_descuento_cl){
    int i,aux,aux2;
    aux=*n_descuento;
    aux2=*n_descuento_cl;

    if(aux==1){
        free(vector_descuento);
        *n_descuento=0;
        free(dc);
        *n_descuento_cl=0;
        aux++;
    }else{
        i=indice_con_id_descuento(vector_descuento,Id_descuento,aux)+1;
        if(i==-1){
            printf("la id no existe\n");

        }else{
    for(i;i<aux;i++)
        (*vector_descuento)[i-1]=(*vector_descuento)[i];
    for(i=indice_con_id_descuento_cl(dc,Id_descuento,aux2)+1;i<aux;i++)
        (*dc)[i-1]=(*dc)[i];
        }
    }
    (*n_descuento)=aux-1;
}

void modificar_descuento(Descuentos**d,Descuentos_clientes**dc,int*n_desc,int*n_desc_clien, int *n_client){
    int k,s,i_desc,num,i_dc,sel,sal;
    int buffer,lin,*n_lin,salida_bu=0;
    char id_cliente[8]="\0";
    char id_desc[11]="\0";
    printf("Introduzca la Id del descuento que quiere modificar:  ");
    leer_string(id_desc,11);
    i_desc=indice_con_id_descuento(d,id_desc,*n_desc);
    i_dc=indice_con_id_descuento_cl(dc,id_desc,*n_desc_clien);
    num=*n_client;
    lin=0;
    n_lin=&lin;
    id_desc[0]='\0';

    printf("\nIntroduce un campo modificar:\n1.Código identificador\n2.Descripción\n3.Importe\n4.Tipo de Descuento\n5.Estado del Descuento\n6.Aplicabilidad del Descuento\n7.Cliente asociado(sólo para cheques regalo\n8.Fecha de caducidad\n9.Salir\n\n ");
    scanf("%i",&sel);
    do{
    switch (sel)
    {
    case 1:printf("Introduce la nueva id del Descuento\n");
                leer_string(id_desc,11);
                strcpy((*d)[i_desc].Id_cod,id_desc);
                strcpy((*dc)[i_dc].Id_cod,id_desc);
        break;
    
    case 2:printf("Introduce una nueva Descripción:\n");
                leer_string((*d)[i_desc].Descrip,51);
        break;
    
    case 3:printf("Introduzca el nuevo importe del descuento(3dígitos)\n");
                leer_string((*d)[i_desc].Importe,4);
        break;

    case 4:s=0;
        do{
        printf("\nElija un tipo de descuento:\n 1.Codpro\n 2.Cheqreg\n");
        scanf("%i",&s);
        if (s==1)
        {   
            (*d)[i_desc].Tipo=codpro;
            salida_bu++;
            pasar_ids_desde_fich(id_cliente,n_lin);
            strcpy((*dc)[i_desc].Id_cliente,id_cliente);
            if(num>1){
                k=0;
                while (k<num-1)
                {
                (*n_desc_clien)++;
                if((*dc = (Descuentos_clientes *)realloc(*dc, *n_desc_clien * sizeof(Descuentos_clientes)))==NULL){
                     printf("Error al reservar memoria para los Descuentos\n");
                    exit(1); 
                }
                (*n_lin)++;
                k++;
                pasar_ids_desde_fich(id_cliente,n_lin);
                strcpy((*dc)[i_dc+k].Id_cliente,id_cliente);
                puts(id_cliente);
                strcpy((*dc)[i_dc+k].Id_cod,(*dc)[i_dc].Id_cod);
                strcpy((*dc)[i_dc+k].f_caducidad,(*dc)[i_dc].f_caducidad);
                strcpy((*dc)[i_dc+k].f_asignacion,(*dc)[i_dc].f_asignacion);
                (*dc)[i_dc+k].Estado=(*dc)[i_dc].Estado;
                }
            }
        }else if (s==2)
        {
            (*d)[i_desc].Tipo=cheqreg;
            salida_bu++;
            printf("Introduzca la id del Cliente al que quiere asignar el cheque regalo:\n");
            while ((buffer=getchar()) != '\n' && buffer != EOF){}
            leer_string(id_cliente,7);
            strcpy((*dc)[i_dc].Id_cliente,id_cliente);
        }else
        {
            printf("\nIntroduzca una opción válida\n");
        }
    }while(salida_bu==0);
    break;

    case 5:salida_bu=0;
            s=0;
            do{
            printf("Introduce el estado del Descuento\n1.Activo\n2.Inactivo\n");
            scanf("%i",&s);
             if (s==1)
        {
            (*d)[i_desc].Estado=activo;
            salida_bu++;
        }else if (sel==2)
        {
            (*d)[i_desc].Estado=inactivo;
            salida_bu++;
        }else
        {
            printf("\nIntroduzca una opción válida\n");
        }
            }while(salida_bu==0);
        break;
    
    case 6: salida_bu=0;
            s=0;
             do{
            printf("Introduce la Aplicabilidad del Descuento\n1.Todos\n2.Esizon\n");
            scanf("%i",&s);
             if (s==1)
        {
            (*d)[i_desc].Aplicabilidad=todos;
            salida_bu++;
        }else if (sel==2)
        {
            (*d)[i_desc].Aplicabilidad=esizon;
            salida_bu++;
        }else
        {
            printf("\nIntroduzca una opción válida\n");
        }
            }while(salida_bu==0);
        break;

    case 7:
        id_cliente[0]='\0';
        printf("Introduce la nueva id asociada al cheque regalo:\n");
        leer_string((*dc)[i_dc].Id_cliente,8);
        break;
    case 8: printf("Introduce la nueva fecha de caducidad:\n");
        leer_string((*dc)[i_dc].f_caducidad,11);
        break;

    case 9: printf("Cerrando modificación de Descuentos...");
                sal++;
        break;
    default:printf("\nIntroduzca una opción válida\n");
        break;
    }
    }while(sal==0);


}
void pasar_ids_desde_fich(char cadena[],int*num_linea){
    char c;
    int n_lin,i,num;
    n_lin=*num_linea;
    i=0;
    num=1;

    FILE *f;
    if((f=fopen("clientes.txt","r"))==NULL){
        printf("Error al abrir el archivo\n");
    }else{
        while(num<n_lin){
            c=fgetc(f);
            if(c=='\n')
                num++;
        }

        while(i<6){
            c=fgetc(f);
            cadena[i]=c;
            i++;
        }
    }
}


