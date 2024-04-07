/*##### MODULO SESIONES #####*/

#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sesiones.h"
#define LINE 100 

//char* usuario_actual(char*);
//FUCION QUE DEVUELVA EL TIPO DE ENUM

char* convertir_entero_char(int);
int num_cliente();
int num_adminprov();
int num_transp();


int main(){ // main para pruebas

    Cliente *c;
    Adminprov *a;
    Transportista *t;
   // carga_cliente(&c);
   // volcado_cliente(&c);
  // carga_adminprov(&a);
  // volcado_adminprov(&a);
    carga_transp(&t);
    volcado_transp(&t);
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

void carga_cliente(Cliente **c){
    int i,n_clien;
    char line[LINE]="\0";
    FILE *f;
    n_clien=num_cliente();

    if((f=fopen("clientes.txt","r"))==NULL){
        printf("Error al abrir el archivo\n");
        }
        else{
            *c = (Cliente *)calloc(n_clien, sizeof(Cliente));
            if(*c==NULL){
                printf("Error al reservar memoria para los Descuentos\n");
                exit(1);
            }else{
                rewind(f);
                for(i=0;i<n_clien;i++){

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

void volcado_cliente(Cliente **c){

    int i,n_clien;
    char line[LINE]="\0";
    FILE *f;
    n_clien=num_cliente();

    if ((f = fopen("clientes.txt", "w+")) == NULL) {

        printf("Error al abrir el archivo");

    } else {

        for ( i=0 ; i<n_clien ; i++ ){
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
            strcat(line, "-");
            
           if(i < n_clien - 1) strcat(line, "\n");
            fprintf(f, "%s", line);
        }

    }

    fclose(f);

}

//cabecera: int num_cliente()
//precondición clientes.txt existente
//postcondicióin: devuleve el número de líneas que hay escritas en el fichero
int num_cliente(){
    char c; 
    int n_lin,i;
    n_lin=0;
    i=0;

    FILE *f;
    if((f= fopen("clientes.txt","r"))==NULL){
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

//cabecera: int num_adminprov()
//precondición adminprov.txt existente
//postcondicióin: devuleve el número de líneas que hay escritas en el fichero
int num_adminprov(){
    char c; 
    int n_lin,i;
    n_lin=0;
    i=0;

    FILE *f;
    if((f= fopen("adminprov.txt","r"))==NULL){
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

//cabecera: int num_transp()
//precondición transportistas.txt existente
//postcondicióin: devuleve el número de líneas que hay escritas en el fichero
int num_transp(){
    char c; 
    int n_lin,i;
    n_lin=0;
    i=0;

    FILE *f;
    if((f= fopen("transportistas.txt","r"))==NULL){
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

void carga_adminprov(Adminprov **a){
    int i,n_admin;
    char line[LINE]="\0";
    char estado[10]="\0";
    FILE *f;
    n_admin=num_adminprov();

    if((f=fopen("adminprov.txt","r"))==NULL){
        printf("Error al abrir el archivo\n");
        }
        *a = (Adminprov *)calloc(n_admin, sizeof(Adminprov));
        if(*a==NULL){
            printf("Error al reservar memoria para los Descuentos\n");
            exit(1);
        }else{
            rewind(f);
            for(i=0;i<n_admin;i++){

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

void volcado_adminprov(Adminprov **a){
    int i,n_admin;
    char line[LINE]="\0";
    FILE *f;
    n_admin=num_adminprov();

    if ((f = fopen("adminprov.txt", "w+")) == NULL) {

        printf("Error al abrir el archivo");

    } else {

        for ( i=0 ; i<n_admin ; i++ ){
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
            
           if(i < n_admin - 1) strcat(line, "\n");
            fprintf(f, "%s", line);
        }

    }

    fclose(f);

}

void carga_transp(Transportista**t){
    int i,n_trans;
    char line[LINE]="\0";
    FILE *f;
    n_trans=num_transp();

    if((f=fopen("transportistas.txt","r"))==NULL)
        printf("Error al abrir el archivo\n");
    
        *t = (Transportista *)calloc(n_trans, sizeof(Transportista));
        if(*t==NULL){
            printf("Error al reservar memoria para los Descuentos\n");
            exit(1);
        }else{
            rewind(f);
            for(i=0;i<n_trans;i++){

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

void volcado_transp(Transportista **t){
    int i,n_trans;
    char line[LINE]="\0";
    FILE *f;
    n_trans=num_transp();

    if ((f = fopen("transportistas.txt", "w+")) == NULL) {

        printf("Error al abrir el archivo");

    } else {

        for ( i=0 ; i<n_trans ; i++ ){
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

           if(i < n_trans - 1) strcat(line, "\n");
            fprintf(f, "%s", line);
        }

    }

    fclose(f);

}
