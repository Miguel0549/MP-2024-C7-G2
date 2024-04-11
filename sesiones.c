/*##### MODULO SESIONES #####*/

#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sesiones.h"
#define LINE 100 

//char* usuario_actual(char*);
//FUCION QUE DEVUELVA EL TIPO DE ENUM

void  de_int_a_id_cliente(int,char*);
void de_int_a_id_empresa(int,char*);
void leer_string(char*,int);
void borrar_cliente_con_id(Cliente**,char*,int*);
int indice_con_id_cliente(Cliente**,char*,int);
int main(){ // main para pruebas
    int *n_clien,clientes;
   // int *n_adminprov,adminprov;
   // int *n_transport,transport;
    Cliente *c;
    //Adminprov *a;
    //Transportista *t;
    clientes=3;
    n_clien=&clientes;
    //adminprov=1;
    //n_adminprov=&adminprov;
    
    carga_cliente(&c,n_clien);
    borrar_cliente_con_id(&c,"000002",n_clien);
    volcado_cliente(&c,n_clien);
    /*
    carga_adminprov(&a,n_adminprov);
    nuevo_adminprov(&a,n_adminprov);
    volcado_adminprov(&a,n_adminprov);*/
   // transport=1;
    //n_transport=&transport;
   // carga_transp(&t,n_transport);
    //nuevo_transportista(&t,n_transport);
    //volcado_transp(&t,n_transport);
    return 0;
}

//cabecera: crear_fichero_clientes()
//preconción: ninguna
//postconción: crea el fichero clientes
void crear_fichero_clientes()
{
    FILE* f2;
    if ((f2 = fopen("clientes.txt", "a+")) == NULL)
        printf("Error al abrir el archivo\n");
    fclose(f2);
}

void carga_cliente(Cliente **c,int *n_clien){
    int i;
    char line[LINE]="\0";
    FILE *f;
  

    if((f=fopen("clientes.txt","r"))==NULL){
        printf("Error al abrir el archivo\n");
        }
        else{
            *c = (Cliente *)calloc(*n_clien, sizeof(Cliente));
            if(*c==NULL){
                printf("Error al reservar memoria para los clientes\n");
                exit(1);
            }else{
                rewind(f);
                for(i=0;i<*n_clien;i++){

                    fgets(line,LINE,f);
                    strcpy((*c)[i].Id_cliente, strtok(line,"-"));
                    strcpy((*c)[i].Nombr_cliente, strtok(NULL, "-\n"));  //cargamos los datos tipo char
                    strcpy((*c)[i].Dir_cliente, strtok(NULL, "-\n"));
                    strcpy((*c)[i].Localidad, strtok(NULL, "-\n"));
                    strcpy((*c)[i].Provincia, strtok(NULL, "-\n"));
                    strcpy((*c)[i].email, strtok(NULL, "-\n"));
                    strcpy((*c)[i].Contrasenna, strtok(NULL, "-\n"));
                    strcpy((*c)[i].Cartera, strtok(NULL, "-\n"));
                 }   
            }
        }
        rewind(f);
        fclose(f);
}

void volcado_cliente(Cliente **c,int *n_clien){

    int i;
    char line[LINE]="\0";
    FILE *f;

    if ((f = fopen("clientes.txt", "w+")) == NULL) {

        printf("Error al abrir el archivo");

    } else {

        for ( i=0 ; i<*n_clien ; i++ ){
           // strcpy(line,"\n");
            strcpy(line, (*c)[i].Id_cliente);
            
            strcat(line, "-");
            strcat(line, (*c)[i].Nombr_cliente);
            strcat(line, "-");
            strcat(line, (*c)[i].Dir_cliente);
            strcat(line, "-");
            strcat(line, (*c)[i].Localidad);
            strcat(line, "-");
            strcat(line, (*c)[i].Provincia);
            strcat(line, "-");
            strcat(line, (*c)[i].email);
            strcat(line, "-");
            strcat(line, (*c)[i].Contrasenna);
            strcat(line, "-");
            strcat(line, (*c)[i].Cartera);
            
           if(i < *n_clien - 1) strcat(line, "\n");
            fprintf(f, "%s", line);
        }

    }

    fclose(f);

}

void nuevo_cliente(Cliente **c,int *n_cliente){
    char Id[7];
    (*n_cliente)++;
    if((*c = (Cliente *)realloc(*c, *n_cliente * sizeof(Cliente)))==NULL)
    {
        printf("Error al reservar memoria para los Clientes\n");
        exit(1); 
    }else{
    de_int_a_id_cliente(*n_cliente,Id);
    printf("\n Su Id de cliente es: ");
    puts(Id); 
    strcpy((*c)[*n_cliente-1].Id_cliente,Id);

    printf("\nIntrozuca su nombre y apellidos(20 caracteres):\n");     
    leer_string((*c)[*n_cliente-1].Nombr_cliente,21);             
    
    printf("\nIntroduzca su dirección(50 caracteres):\n");
    leer_string((*c)[*n_cliente-1].Dir_cliente,51);                            

    printf("\nIntroduzca su localidad(20 caracteres):\n");
    leer_string((*c)[*n_cliente-1].Localidad,21);              
    
    printf("\nIntroduzca su Provincia(20 caracteres):\n");
    leer_string((*c)[*n_cliente-1].Provincia,21);

    printf("\nIntroduzca su correco electrónico(31 caracteres):\n");
    leer_string((*c)[*n_cliente-1].email,31);

    printf("\nCree e introduzca una contraseña(hasta 15 dígitos):\n");
    leer_string((*c)[*n_cliente-1].Contrasenna,16);

    strcpy((*c)[*n_cliente-1].Cartera,"000000");
    }
}


void carga_adminprov(Adminprov **a,int *n_admin){
    int i;
    char line[LINE]="\0";
    char estado[10]="\0";
    FILE *f;
    

    if((f=fopen("adminprov.txt","r"))==NULL){
        printf("Error al abrir el archivo\n");
        }
        *a = (Adminprov *)calloc(*n_admin, sizeof(Adminprov));
        if(*a==NULL){
            printf("Error al reservar memoria para los admin/proveedores\n");
            exit(1);
        }else{
            rewind(f);
            for(i=0;i<*n_admin;i++){

                fgets(line,LINE,f);
                strcpy((*a)[i].Id_empresa, strtok(line,"-"));
                strcpy((*a)[i].Nombre, strtok(NULL, "-\n"));  //cargamos los datos tipo char
                strcpy((*a)[i].email, strtok(NULL, "-\n"));
                strcpy((*a)[i].Contrasenna, strtok(NULL, "-\n"));

                strcpy(estado, strtok(NULL, "-\n"));//introducimos la siguiente cadena entre los '-'
                    

                 if(strcmp(estado,"administrador")==0){
                        (*a)[i].Perfil_usuario=administrador;

                 }else if(strcmp(estado, "proveedor")==0){
                        (*a)[i].Perfil_usuario=proveedor;
                }else{puts("Error del campo TIPO PROV/ADMIN"); }

                for(int k=0;k<10;k++) estado[k]='\0';
            
            }   
        }
        rewind(f);
        fclose(f);
}

void volcado_adminprov(Adminprov **a,int*n_admin){
    int i;
    char line[LINE]="\0";
    FILE *f;

    if ((f = fopen("adminprov.txt", "w+")) == NULL) {

        printf("Error al abrir el archivo");

    } else {

        for ( i=0 ; i<*n_admin ; i++ ){
           // strcpy(line,"\n");
            strcpy(line, (*a)[i].Id_empresa);
            strcat(line, "-");
            strcat(line, (*a)[i].Nombre);
            strcat(line, "-");
            strcat(line, (*a)[i].email);
            strcat(line, "-");
            strcat(line, (*a)[i].Contrasenna);
            strcat(line, "-");

             if((*a)[i].Perfil_usuario==proveedor){
                strcat(line,"proveedor");
            }else if((*a)[i].Perfil_usuario==administrador){
                strcat(line,"administrador");
            }else{
                puts("Error en el volcado de TIPO prov/admin");
            }
            
           if(i < *n_admin - 1) strcat(line, "\n");
            fprintf(f, "%s", line);
        }

    }

    fclose(f);

}


void nuevo_adminprov(Adminprov **a,int *n_adminprov){
    char Id[7],nomb[21];
    (*n_adminprov)++;
    if((*a = (Adminprov *)realloc(*a, *n_adminprov * sizeof(Adminprov)))==NULL)
    {
        printf("Error al reservar memoria para los Clientes\n");
        exit(1); 
    }else{
    de_int_a_id_empresa(*n_adminprov,Id);
    printf("\n Su Id de administrador/proveedor es: ");
    puts(Id); 
    strcpy((*a)[*n_adminprov-1].Id_empresa,Id);

    printf("\nIntrozuca el nombre de su empresa(20 caracteres):\n");     
    leer_string(nomb,21); 
    puts(nomb);
    strcpy((*a)[*n_adminprov-1].Nombre,nomb);
    if(strcmp(nomb,"ESIZON\0")==0){
        (*a)[*n_adminprov-1].Perfil_usuario=administrador;
    }else{
        (*a)[*n_adminprov-1].Perfil_usuario=proveedor;
    }           

    printf("\nIntroduzca su correco electrónico de empresa(31 caracteres):\n");
    leer_string((*a)[*n_adminprov-1].email,31);

    printf("\nCree e introduzca una contraseña(hasta 15 dígitos):\n");
    leer_string((*a)[*n_adminprov-1].Contrasenna,16);
    }
}


void carga_transp(Transportista**t,int *n_trans){
    int i;
    char line[LINE]="\0";
    FILE *f;

    if((f=fopen("transportistas.txt","r"))==NULL){
        printf("Error al abrir el archivo\n");
    }
        *t = (Transportista *)calloc(*n_trans, sizeof(Transportista));
        if(*t==NULL){
            printf("Error al reservar memoria para los transportistas\n");
            exit(1);
        }else{
            rewind(f);
            for(i=0;i<*n_trans;i++){

                fgets(line,LINE,f);
                strcpy((*t)[i].Id_transp, strtok(line,"-"));
                strcpy((*t)[i].Nombre, strtok(NULL, "-\n"));  //cargamos los datos tipo char
                strcpy((*t)[i].email, strtok(NULL, "-\n"));
                strcpy((*t)[i].Contrasenna, strtok(NULL, "-\n"));
                strcpy((*t)[i].Nom_empre, strtok(NULL, "-\n"));
                strcpy((*t)[i].Ciudad, strtok(NULL, "-\n"));
            
            }   
        }
        rewind(f);
        fclose(f);
}

void volcado_transp(Transportista **t,int *n_trans){
    int i;
    char line[LINE]="\0";
    FILE *f;
    if ((f = fopen("transportistas.txt", "w")) == NULL) {

        printf("Error al abrir el archivo");

    } else {

        for ( i=0 ; i<*n_trans ; i++ ){
           // strcpy(line,"\n");
            strcpy(line, (*t)[i].Id_transp);
            strcat(line, "-");
            strcat(line, (*t)[i].Nombre);
            strcat(line, "-");
            strcat(line, (*t)[i].email);
            strcat(line, "-");
            strcat(line, (*t)[i].Nom_empre);
            strcat(line, "-");
            strcat(line, (*t)[i].Contrasenna);
            strcat(line, "-");
            strcat(line, (*t)[i].Ciudad);

           if(i < *n_trans - 1) strcat(line, "\n");
            fprintf(f, "%s", line);
        }

    }

    fclose(f);

}


void nuevo_transportista(Transportista **t,int *n_transport){
    char Id[5];
    (*n_transport)++;
    if((*t = (Transportista*)realloc(*t, *n_transport * sizeof(Transportista)))==NULL)
    {
        printf("Error al reservar memoria para los transportistas\n");
        exit(1); 
    }else{
    de_int_a_id_empresa(*n_transport,Id);
    printf("\n Su Id de transportista es: ");
    puts(Id); 
    strcpy((*t)[*n_transport-1].Id_transp,Id);

    printf("\nIntrozuca su nombre y apellidos(20 caracteres):\n");     
    leer_string((*t)[*n_transport-1].Nombre,21);
   
    printf("\nIntroduzca su correco electrónico de empresa(31 caracteres):\n");
    leer_string((*t)[*n_transport-1].email,31);

     printf("\nIntroduzca el nombre de su empresa(21 caracteres):\n");
    leer_string((*t)[*n_transport-1].Nom_empre,21);

    printf("\nCree e introduzca una contraseña(hasta 15 dígitos):\n");
    leer_string((*t)[*n_transport-1].Contrasenna,16);
    
    printf("\nCree e introduzca su ciudad(hasta 15 dígitos):\n");
    leer_string((*t)[*n_transport-1].Ciudad,16);

    }
}



// cabecera: void leer_string(char * cadena, int elem)
// precondicion: ninguna
// postcondicion: lee en cadena la cadena introducida por el usuario
void leer_string(char*cadena, int elem)
{
    int i=0;

    fflush(stdin);
    fgets(cadena, elem , stdin);
    fflush(stdin);
 //puts(cadena);
    for (i = 0; cadena[i] != '\n' && i < elem + 1; i++)
        if (cadena[i] == '\n')
            cadena[i] = '\0';

    while (i < elem + 1) {
        if (cadena[i] == '\n')
            cadena[i] = '\0';
        i++;
    }
}



// cabecera: void de_int_a_id_cliente(int i_id, char * s_id)
// precondicion: i_id es un numero de 6 digitos como máximo
// postcondicion: convierte el entero i_id en un string s_id
void de_int_a_id_cliente(int i_id, char* s_id)
{ 
    char cadena[7];
    int i, j = 0;

    strcpy(s_id, "000000");

    itoa(i_id, cadena, 10);

    for (i = 6 - strlen(cadena); i < 6; i++) {
        s_id[i] = cadena[j];
        j++;
    }
}


// cabecera: void de_int_a_id_empresa(int i_id, char * s_id)
// precondicion: i_id es un numero de 4 digitos como máximo
// postcondicion: convierte el entero i_id en un string s_id
void de_int_a_id_empresa(int i_id, char* s_id)
{ 
    char cadena[5];
    int i, j = 0;

    strcpy(s_id, "0000");

    itoa(i_id, cadena, 10);

    for (i = 4 - strlen(cadena); i < 4; i++) {
        s_id[i] = cadena[j];
        j++;
    }
}

int indice_con_id_cliente(Cliente**vector_cliente,char *id_cliente,int num_clien){
    int i=0,devolver;
    do{
        if(strcmp(id_cliente,(*vector_cliente)[i].Id_cliente)==0){
        devolver=i;
    }
        i++;
    }while(i<=num_clien);
    return devolver;
}

void borrar_cliente_con_id(Cliente**vector_cliente,char *Id_cliente, int *n_clientes){
    int i,aux;
    aux=*n_clientes;

    if(*n_clientes==1){
        free(vector_cliente);
        *n_clientes=0;
    }else{
    for(i=indice_con_id_cliente(vector_cliente,Id_cliente,aux)+1;i<aux;i++)
        (*vector_cliente)[i-1]=(*vector_cliente)[i];
    }
    (*n_clientes)=aux-1;
}