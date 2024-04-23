/*##### MÓDULO DESCUENTOS   #####*/
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>
#include "descuentos.h"
//#include "sesiones.h"
//#include "sesiones.c"
#define LINE 150

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

void nuevo_descuento(Descuentos **d,Descuentos_clientes **dc,Cliente *clt ,int *n_desc,int*n_desc_clien, int *n_cliente){

    int *n_lin,lin,k,j,indice_d_cl,indice_d,sel,i,tamanio_nuevo_desc_cl;
    char id_cliente[8]="\0",fecha_cad[11]="\0";

    lin=0;
    n_lin=&lin;
    indice_d_cl=(*n_desc_clien);
    indice_d=(*n_desc);
    (*n_desc)++;

    if((*d = (Descuentos *)realloc(*d, (*n_desc) * sizeof(Descuentos)))==NULL){
        printf("Error al reservar memoria para los Descuentos\n");
        exit(1); 
    }

    printf("Introduzca una breve descripcion del descuento:\n");
    leer_string((*d)[indice_d].Descrip,51);                            //Introducimos la cadena

    printf("\nIntroduce el importe del descuento:\n");
    leer_string((*d)[indice_d].Importe,4);               //Introducimos el importe del descuento

    do{
        printf("\nElija el Estado del Descuento:\n 1.Activo\n 2.Inactivo\n");
        scanf("%i",&sel);
        if (sel==1)
        {
            (*d)[indice_d].Estado=activo;

        }else if (sel==2)
        {
            (*d)[indice_d].Estado=inactivo;

        }else
        {
            printf("\nIntroduzca una opción válida\n");
        }
    }while(sel != 1 && sel != 2);


    do{

        printf("\nElija en los productos en los que se aplica:\n 1.Todos\n 2.Esizon\n");
        scanf("%i",&sel);
        if (sel==1)
        {
            (*d)[indice_d].Aplicabilidad=todos;

        }else if (sel==2)
        {
            (*d)[indice_d].Aplicabilidad=esizon;

        }else
        {
            printf("\nIntroduzca una opción válida\n");
        }
    }while(sel != 1 && sel != 2);


    do{

        printf("\nElija un tipo de descuento:\n 1.Codpro\n 2.Cheqreg\n");
        fflush(stdin);
        scanf("%i",&sel);

        if (sel==1)
        {
            (*d)[indice_d].Tipo=codpro;

            *n_desc_clien += *n_cliente;
            tamanio_nuevo_desc_cl = indice_d_cl + (*n_cliente);


            if((*dc =(Descuentos_clientes*)realloc(*dc, tamanio_nuevo_desc_cl * sizeof(Descuentos_clientes))) == NULL){
                printf("Error al reservar memoria para los Descuentos_clientes\n");
                exit(1);
            }

            j=indice_d-1;
            while(j>=0 && (*d)[j].Tipo != codpro) j--;

            if ( j<0 ) {


                strcpy((*d)[indice_d].Id_cod,"codig00001");
                strcpy((*dc)[indice_d_cl].Id_cod, (*d)[indice_d].Id_cod);

            }else{

                siguiente_id_desc_o_lock((*d)[indice_d].Id_cod,(*d)[j].Id_cod,"descuento");
                strcpy((*dc)[indice_d_cl].Id_cod,(*d)[indice_d].Id_cod) ;


            }

            printf("\nIntroduzca la fecha de caducidad del descuento formato:(dd/mm/aaaa)\n");
            leer_string(fecha_cad,11);


            k=indice_d_cl;
            for ( i=0 ; i<*n_cliente ; i++ ){

                strcpy((*dc)[k].Id_cod,(*d)[indice_d].Id_cod);

                strcpy((*dc)[k].Id_cliente,clt[i].Id_cliente);

                (*dc)[k].Estado=no;

                fecha_actual((*dc)[k].f_asignacion,0);

                strcpy((*dc)[k].f_caducidad,fecha_cad);

                k++;
            }

        }else if (sel==2)
        {

            (*n_desc_clien)++;

            if((*dc =(Descuentos_clientes*)realloc(*dc, (indice_d_cl + 1) * sizeof(Descuentos_clientes))) == NULL){
                printf("Error al reservar memoria para los Descuentos_clientes\n");
                exit(1);
            }

            (*d)[indice_d].Tipo=cheqreg;

            j=indice_d-1;
            while(j>=0 && (*d)[j].Tipo != cheqreg) j--;

            if ( j<0 ) {

                strcpy((*d)[indice_d].Id_cod,"che0000001");
                strcpy((*dc)[indice_d_cl].Id_cod, (*d)[indice_d].Id_cod);

            }else{

                siguiente_id_desc_o_lock((*d)[indice_d].Id_cod,(*d)[j].Id_cod,"cheqreg");
                strcpy((*dc)[indice_d_cl].Id_cod, (*d)[indice_d].Id_cod);

            }

            fecha_actual((*dc)[indice_d_cl].f_asignacion,0);

            (*dc)[indice_d_cl].Estado=no;

            printf("Introduzca la id del Cliente al que quiere asignar el cheque regalo:\n");

            leer_string(id_cliente,8);
            strcpy((*dc)[indice_d_cl].Id_cliente, id_cliente);


            printf("\nIntroduzca la fecha de caducidad del descuento formato:(dd/mm/aaaa)\n");
            leer_string((*dc)[indice_d_cl].f_caducidad, 11);

            sel=2;

        }else
        {
            printf("\nIntroduzca una opción válida\n");
        }
    }while(sel != 1 && sel != 2);

}

//cabecera: void carga_descuentos(Descuentos **d)
//precondición: sea **d un doble puntero a una estructura descuentos 
//postcondición: carga en el vector de estructura Descuentos los datos desde el fichero descuentos.txt
void carga_descuentos(Descuentos **d,int *n_desc){

    int i,j;
    char c;
    char line[LINE]="\0",contador_lineas[LINE]="0";
    char estado[10]="\0";
    FILE *f;
    j=0;
    if((f=fopen("Files\\descuentos.txt","r"))==NULL){
        printf("Error al abrir el archivo\n");
    }else{


        while(!feof(f)){

            fgets(contador_lineas,LINE,f);
            (*n_desc)++;

        }

    
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
                strcpy((*d)[i].Id_cod, strtok(line,"-\n"));
                strcpy((*d)[i].Descrip, strtok(NULL, "-\n"));  //cargamos los datos tipo char

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

                    strcpy((*d)[i].Importe, strtok(NULL, "-\n"));

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
    char line[LINE]="\0",contador_lineas[LINE]="0";
    char estado[10]="\0";
    char c;
    FILE *f;
    j=0;
    if((f=fopen("Files\\descuentos_clientes.txt","r"))==NULL){
        printf("Error al abrir el archivo\n");
    }else{

        while(!feof(f)){

            fgets(contador_lineas,LINE,f);
            (*n_desc_c)++;

        }


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

    char line[LINE]="\0";
    FILE *f;

    if ((f = fopen("Files\\descuentos.txt", "w+")) == NULL) {

        printf("Error al abrir el archivo");

    } else {

        for ( int i=0 ; i<*n_desc ; i++ ){


            strcpy(line, (*d)[i].Id_cod);
            strcat(line, "-");
            strcat(line, (*d)[i].Descrip);
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
            strcat(line, (*d)[i].Importe);


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

    if ((f = fopen("Files\\descuentos_clientes.txt", "w+")) == NULL) {

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

//cabecera: lista_clientes_con_descuentos(Descuentos *Des , Descuentos_clientes *desc_cl , int *n_desc , int *n_desc_cl)
//precondición: *Des,*desc_cl,*n_desc y *n_desc_cl inicializado
//postcondición: lista los clientes con descuentos asociados
void lista_clientes_con_descuentos ( Descuentos *Des , Descuentos_clientes *desc_cl , int *n_desc , int *n_desc_cl ){

    int i,j;
    char c='a';

    system("cls");

    printf("------------------------------ Clientes con descuentos asociados --------------------------------\n\n");

    for ( i=0 ; i< *n_desc ; i++ ){


        for ( j=0 ; j<*n_desc_cl ; j++ ){

            if (strcmp(Des[i].Id_cod,desc_cl[j].Id_cod)==0){

                printf("[%c].%s-%s-%s\n",c,desc_cl[j].Id_cliente,desc_cl[j].Id_cod,Des[i].Descrip);

                c++;
            }

        }

    }


    system("pause");

}

//cabecera: lista_clientes_con_descuentos(Descuentos *Des , Descuentos_clientes *desc_cl , int *n_desc , int *n_desc_cl)
//precondición: *Des,*desc_cl,*n_desc y *n_desc_cl inicializado
//postcondición: lista los clientes con descuentos usados
void lista_clientes_con_descuentos_usados ( Descuentos *Des , Descuentos_clientes *desc_cl , int *n_desc , int *n_desc_cl ){

    int i,j;
    char c='a';

    system("cls");

    printf("------------------------------ Clientes con descuentos usados --------------------------------\n\n");

    for ( i=0 ; i< *n_desc ; i++ ){


        for ( j=0 ; j<*n_desc_cl ; j++ ){

            if (strcmp(Des[i].Id_cod,desc_cl[j].Id_cod)==0){

                if ( desc_cl[j].Estado == si){

                    printf("[%c].%s-%s-%s\n",c,desc_cl[j].Id_cliente,desc_cl[j].Id_cod,Des[i].Descrip);

                    c++;

                }

            }

        }

    }


    system("pause");

}


void asignar_cod_prom_cliente( Descuentos_clientes **desc_cl , int *n_desc_cl , char id_desc[11] ){

    int indice;
    char id_cliente[8]="\0";

    indice = *n_desc_cl;
    (*n_desc_cl)++;

    if((*desc_cl =(Descuentos_clientes*)realloc(*desc_cl, (*n_desc_cl) * sizeof(Descuentos_clientes))) == NULL){
        printf("Error al reservar memoria para los Descuentos_clientes\n");
        exit(1);
    }

    strcpy((*desc_cl)[indice].Id_cod,id_desc);

    (*desc_cl)[indice].Estado=no;

    fecha_actual((*desc_cl)[indice].f_asignacion,0);

    printf("Introduzca la id del Cliente al que quiere asignar el cheque regalo:\n");

    leer_string(id_cliente,8);
    strcpy((*desc_cl)[indice].Id_cliente, id_cliente);

    printf("\nIntroduzca la fecha de caducidad del descuento formato:(dd/mm/aaaa)\n");
    leer_string((*desc_cl)[indice].f_caducidad, 11);


}


void menu_descuentos( Descuentos **desc , Descuentos_clientes **desc_cl, Cliente *clt , int *n_desc , int *n_desc_cl , int *n_clt ){


    int op;
    char id_descuento[11]="\0";

    do{

        system("cls");

        listar_descuentos(*desc,n_desc);

        do{

            printf("\nElija una opcion:\n");
            printf("1.alta\n2.baja\n3.modificar\n4.ver clientes con descuentos asociados\n5.ver clientes con descuentos usados\n6.Asignar cheque regalo\n7.salir\n");
            scanf("%i", &op);

            switch (op) {
                case 1:

                    nuevo_descuento(desc,desc_cl,clt,n_desc,n_desc_cl,n_clt);

                    system("cls");

                    break;
                case 2:

                    printf("Escriba la id del descuento qu quiera borrar: ");
                    fflush(stdin);
                    gets(id_descuento);

                    borrar_descuento_con_id(desc,desc_cl,id_descuento,n_desc,desc_cl);

                    system("cls");

                    break;
                case 3:

                    modificar_descuento(desc,desc_cl,n_desc,n_desc_cl,n_clt);

                    system("cls");

                    break;
                case 4:

                    lista_clientes_con_descuentos(*desc,*desc_cl,n_desc,n_desc_cl);

                    system("cls");

                    break;
                case 5:

                    lista_clientes_con_descuentos_usados(*desc,*desc_cl,n_desc,n_desc_cl);

                    system("cls");

                    break;
                case 6:

                    printf("Introduce la id del descuento a asignar: ");
                    fflush(stdin);
                    gets(id_descuento);

                    asignar_cod_prom_cliente(desc_cl,n_desc_cl,id_descuento);

                    system("cls");

                    break;
                case 7:
                    break;
                default:
                    break;
            }

        }while ( op < 1 || op > 7);

    }while ( op != 7 );



}



//cabecera: void listar_descuentos(Descuentos *d)
//precondición: *d inicializado
//postcondición: lista los descuentos actuales en el vector
void listar_descuentos(Descuentos*d,int*n_desc){

    int i=0;
    char c='a';

    printf("--------------------------- Todos los descuentos ----------------------------\n\n");

    for ( i=0 ; i<*n_desc ; i++ ){

        printf("[%c].%s-%s-",c,d[i].Id_cod,d[i].Descrip);

        if ( d[i].Tipo == cheqreg ){

            printf("cheqreg");

        }else if ( d[i].Tipo == codpro){

            printf("codpro");

        }else printf("error con el tipo de descuento (lista descuentos)");

        printf("-");

        if ( d[i].Estado == activo ){

            printf("activo");

        }else if ( d[i].Estado == inactivo ){

            printf("inactivo");

        }else printf("error con el tipo de descuento (lista descuentos)");

        printf("-%s",d[i].Importe);

        printf("-");

        if ( d[i].Aplicabilidad == esizon ){

            printf("esizon\n");

        }else if ( d[i].Aplicabilidad == todos){

            printf("todos\n");

        }else printf("error con el tipo de descuento (lista descuentos)");

        c++;

    }

    printf("---------------------------------------------------------------------------------");
    
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
             printf("Fecha de expedicion:");
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

void borrar_descuento_cliente ( ){



}


void borrar_descuento_con_id(Descuentos **desc,Descuentos_clientes**desc_cl,char *Id_descuento, int *n_descuento,int*n_descuento_cl) {

    int i, aux, aux2;
    aux = *n_descuento;
    aux2 = *n_descuento_cl;

    if (aux == 1) {

        free(desc);
        *n_descuento = 0;
        free(desc_cl);
        *n_descuento_cl = 0;
        aux++;

    } else {
        i = indice_con_id_descuento(desc, Id_descuento, aux) + 1;
        if (i == -1) {
            printf("la id no existe\n");

        } else {

            for (i; i < aux; i++) {

                (*desc)[i - 1] = (*desc)[i];

            }

        }

        (*n_descuento) = aux - 1;
    }

}


void pasar_ids_desde_fich(char cadena[], int *num_linea){
    char c;
    int n_lin, i, num;
    n_lin = *num_linea;
    i = 0;
    num = 1;

    FILE *f;
    if ((f = fopen("clientes.txt", "r")) == NULL) {
        printf("Error al abrir el archivo\n");
    } else {
        while (num < n_lin) {
            c = fgetc(f);
            if (c == '\n')
                num++;
        }

        while (i < 6) {
            c = fgetc(f);
            cadena[i] = c;
            i++;
        }
    }
}


    void modificar_descuento(Descuentos **d, Descuentos_clientes **dc, int *n_desc, int *n_desc_clien, int *n_client) {

        int k, s, i_desc, num, i_dc, sel, sal;
        int buffer, lin, *n_lin, salida_bu = 0;
        char id_cliente[8] = "\0";
        char id_desc[11] = "\0";
        printf("Introduzca la Id del descuento que quiere modificar:  ");
        leer_string(id_desc, 11);
        i_desc = indice_con_id_descuento(d, id_desc, *n_desc);
        i_dc = indice_con_id_descuento_cl(dc, id_desc, *n_desc_clien);
        num = *n_client;
        lin = 0;
        n_lin = &lin;
        id_desc[0] = '\0';

        printf("\nIntroduce un campo modificar:\n1.Codigo identificador\n2.Descripcion\n3.Importe\n4.Estado del Descuento\n5.Aplicabilidad del Descuento\n6.Cliente asociado(solo para cheques regalo\n7.Fecha de caducidad\n8.Salir\n\n ");
        scanf("%i", &sel);
        do {
            switch (sel) {
                case 1:
                    printf("Introduce la nueva id del Descuento\n");
                    leer_string(id_desc, 11);
                    strcpy((*d)[i_desc].Id_cod, id_desc);
                    strcpy((*dc)[i_dc].Id_cod, id_desc);
                    break;

                case 2:
                    printf("Introduce una nueva Descripción:\n");
                    leer_string((*d)[i_desc].Descrip, 51);
                    break;

                case 3:
                    printf("Introduzca el nuevo importe del descuento(3digitos)\n");
                    leer_string((*d)[i_desc].Importe, 4);
                    break;
                case 4:

                    s = 0;
                    do {
                        printf("Introduce el estado del Descuento\n1.Activo\n2.Inactivo\n");
                        scanf("%i", &s);
                        if (s == 1) {
                            (*d)[i_desc].Estado = activo;

                        } else if (s == 2) {
                            (*d)[i_desc].Estado = inactivo;

                        } else {
                            printf("\nIntroduzca una opción válida\n");
                        }
                    } while (s != 1 && s != 2);
                    break;

                case 5:
                    salida_bu = 0;
                    s = 0;
                    do {
                        printf("Introduce la Aplicabilidad del Descuento\n1.Todos\n2.Esizon\n");
                        scanf("%i", &s);
                        if (s == 1) {
                            (*d)[i_desc].Aplicabilidad = todos;
                            salida_bu++;
                        } else if (sel == 2) {
                            (*d)[i_desc].Aplicabilidad = esizon;
                            salida_bu++;
                        } else {
                            printf("\nIntroduzca una opción válida\n");
                        }
                    } while (salida_bu == 0);
                    break;

                case 6:
                    id_cliente[0] = '\0';
                    printf("Introduce la nueva id asociada al cheque regalo:\n");
                    leer_string((*dc)[i_dc].Id_cliente, 8);
                    break;
                case 7:
                    printf("Introduce la nueva fecha de caducidad:\n");
                    leer_string((*dc)[i_dc].f_caducidad, 11);
                    break;

                case 8:
                    printf("Cerrando modificacion de Descuentos...");
                    sal++;
                    break;
                default:
                    printf("\nIntroduzca una opción válida\n");
                    break;
            }
        } while (sal == 0);


    }


