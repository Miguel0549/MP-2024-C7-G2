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


int main(){ // main para pruebas

    Cliente *c;

    carga_cliente(&c);
    volcado_cliente(&c);
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

//cabecera: void carga_descuentos(Clientes **d)
//precondición: sea **c un doble puntero a una estructura clientes
//postcondición: carga en el vector de estructura Descuentos los datos desde el fichero clientes.txt
void carga_cliente(Cliente **c){
    int i,n_clien;
    char line[LINE]="\0";
    FILE *f;
    n_clien=num_cliente();

    if((f=fopen("clientes.txt","r"))==NULL)
        printf("Error al abrir el archivo\n");
    
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
        rewind(f);
        fclose(f);
}

//cabecera:void volcado_descuentos(Clientes **c)
//precondición:**c incializado y descuentos.txt creado
//postcondición:descuentos.txt contiene la información que contenía el vector de estructuras
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