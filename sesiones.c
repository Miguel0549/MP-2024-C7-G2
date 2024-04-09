/*##### MODULO SESIONES #####*/

#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sesiones.h"
#define LINE 100 

//char* usuario_actual(char*);
//FUCION QUE DEVUELVA EL TIPO DE ENUM

void  de_int_a_id_cliente(int,char*);
void nuevo_cliente(Cliente **,int *);
void leer_string(char*,int);

int main(){ // main para pruebas
    int *n_clien,clientes;
    Cliente *c;
    clientes=2;
    n_clien=&clientes;
   /*Adminprov *a;
    Transportista *t;*/
    carga_cliente(&c,n_clien);
    nuevo_cliente(&c,n_clien);
    volcado_cliente(&c,n_clien);

   /* carga_adminprov(&a);
    volcado_adminprov(&a);
    carga_transp(&t);
    volcado_transp(&t);*/
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
                printf("Error al reservar memoria para los Descuentos\n");
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
            printf("Error al reservar memoria para los Descuentos\n");
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

void carga_transp(Transportista**t,int *n_trans){
    int i;
    char line[LINE]="\0";
    FILE *f;

    if((f=fopen("transportistas.txt","r"))==NULL){
        printf("Error al abrir el archivo\n");
    }
        *t = (Transportista *)calloc(*n_trans, sizeof(Transportista));
        if(*t==NULL){
            printf("Error al reservar memoria para los Descuentos\n");
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
    if ((f = fopen("transportistas.txt", "w+")) == NULL) {

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



//cabecera: void nuevo_cliente(Cliente **c)
//precondición: **c un vector de estructura cliente inicializado
//postcondición: crea y añade a la estructura un nuevo cliente
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