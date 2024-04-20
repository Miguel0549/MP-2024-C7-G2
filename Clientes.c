#include "Clientes.h"
#include<stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINE 150


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


void siguiente_id(char*cad,int i){
    for(int j=0;(i>=0)&&(j==0);i--)
        if(cad[i-1]=='9'){
            cad[i-1]='0';
        }else{
            cad[i-1]++;
            j=1;
        }
}


//cabecera:int indice_con_id_cliente(Cliente **vector_cliente,cha*id_cliente,int)
//precondición: vector cliente un vector de estructura cliente, id cliente una cadena y num_clien el número de clientes registrados del vector
//postcondición: devuelve el valor del indice del vector de estructura cuya id coincide con el de la cadena
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


/////////////////////////////////////////////////////////////////////////////////////////////////////

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
    char line[LINE]="\0",contador_lineas[LINE]="0";
    FILE *f;


    if((f=fopen("Files\\clientes.txt","r"))==NULL){
        printf("Error al abrir el archivo\n");
    }else{

        while(!feof(f)){

            fgets(contador_lineas,LINE,f);
            (*n_clien)++;

        }

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

    if ((f = fopen("Files\\clientes.txt", "w+")) == NULL) {

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
    char Id[8];
    (*n_cliente)++;
    if((*c = (Cliente *)realloc(*c, *n_cliente * sizeof(Cliente)))==NULL)
    {
        printf("Error al reservar memoria para los Clientes\n");
        exit(1);
    }else{

        if(*n_cliente==1){
            de_int_a_id_cliente(*n_cliente,Id);
        }else{
            strcpy(Id,(*c+(*n_cliente-2))->Id_cliente);
            siguiente_id(Id,6);
        }
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