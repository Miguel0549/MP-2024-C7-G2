/*##### MODULO SESIONES #####*/

#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sesiones.h"
#define LINE 150

//char* usuario_actual(char*);
//FUCION QUE DEVUELVA EL TIPO DE ENUM


void carga_adminprov(Adminprov **a,int *n_admin){
    int i;
    char line[LINE]="\0",contador_lineas[LINE]="0";
    char estado[10]="\0";
    FILE *f;
    

    if((f=fopen("Files\\adminprov.txt","r"))==NULL){
        printf("Error al abrir el archivo\n");
        }

        while(!feof(f)){

            fgets(contador_lineas,LINE,f);
            (*n_admin)++;

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
                        (*a)[i].Perfil_usuario= admin;

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

    if ((f = fopen("Files\\adminprov.txt", "w+")) == NULL) {

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
            }else if((*a)[i].Perfil_usuario==admin){
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


void nuevo_adminprov(Adminprov **a,int *n_adminprov, usu tipo_usu){

    char Id[7],nomb[21];
    (*n_adminprov)++;
    if((*a = (Adminprov *)realloc(*a, *n_adminprov * sizeof(Adminprov)))==NULL)
    {
        printf("Error al reservar memoria para los Clientes\n");
        exit(1); 
    }else{
        
        if(*n_adminprov==1){
            de_int_a_id_empresa(*n_adminprov,Id);
        }else{
            strcpy(Id,(*a+(*n_adminprov-2))->Id_empresa);
            crear_siguiente_id(4,Id,Id);
        }

        if ( tipo_usu != admin){

            printf("\n Su Id de administrador/proveedor es: ");
            puts(Id);

        }else{

            printf("\n El Id asignado de administrador/proveedor es: ");
            puts(Id);

        }


    strcpy((*a)[*n_adminprov-1].Id_empresa,Id);

    printf("\nIntrozuca el nombre de su empresa(20 caracteres):\n");     
    leer_string(nomb,21);

    strcpy((*a)[*n_adminprov-1].Nombre,nomb);
    if(strcmp(nomb,"ESIZON\0")==0){
        (*a)[*n_adminprov-1].Perfil_usuario=admin;
    }else{
        (*a)[*n_adminprov-1].Perfil_usuario=proveedor;
    }           

    printf("\nIntroduzca su correco electronico de empresa(31 caracteres):\n");
    leer_string((*a)[*n_adminprov-1].email,31);

    printf("\nCree e introduzca una contrasena(hasta 15 dígitos):\n");
    leer_string((*a)[*n_adminprov-1].Contrasenna,16);
    }

    system("cls");
    printf("\nProveedor creado corectamente.\n");
    system("pause");
    system("cls");


}



void modificar_proveedor ( Adminprov *prov, int id_act ){

    printf("Nombre: ");
    fflush(stdin);
    gets(prov[id_act].Nombre);

    printf("Email (30): ");
    fflush(stdin);
    gets(prov[id_act].email);

    printf("Contrasena (15): ");
    fflush(stdin);
    gets(prov[id_act].Contrasenna);


    system("cls");
    printf("\nHas modificado los datos corectamente.\n");
    system("pause");
    system("cls");

}



void modificar_admin ( Adminprov **admpr , int ind_admpr){


    if ( (*admpr)[ind_admpr].Perfil_usuario != admin){

        printf("Nombre: ");
        fflush(stdin);
        gets((*admpr)[ind_admpr].Nombre);

    }

    printf("Email (30): ");
    fflush(stdin);
    gets((*admpr)[ind_admpr].email);

    printf("Contrasena (15): ");
    fflush(stdin);
    gets((*admpr)[ind_admpr].Contrasenna);


    system("cls");
    printf("\nHas modificado tus datos corectamente.\n");
    system("pause");
    system("cls");


}


void inicio_sesion_cliente ( Cliente *client , int *n_cliente , int *usu_act ){

    int i;
    char email[31]="\0",contrasena[16]="\0",error;

    do{

        error=0;

        printf("Introduzca su email: ");;
        fflush(stdin);
        gets(email);

        printf("Introduzca su contrasena: ");
        fflush(stdin);
        gets(contrasena);

        i=0;
        while ( i<*n_cliente && strcmp(client[i].email,email)!=0 ) i++;

        if ( i >= *n_cliente ) error = 1;
        else {

            if ( strcmp(client[i].Contrasenna,contrasena)!=0 ) error = 1;

        }

        if ( error == 1 ){

            printf("\nEl email o la contrasena son incorectos.\n");
            system("pause");
            system("cls");

        }else *usu_act = i;

    }while(error==1);


    printf("\nHa iniciado sesion correctamente.");
    system("pause");
    system("cls");


}

void inicio_sesion_admin (  Adminprov *admp ,  int *n_admp , int *usu_act ){

    int i;
    char email[31]="\0",contrasena[16]="\0",error;

    do{

        error=0;

        printf("Introduzca su email: ");;
        fflush(stdin);
        gets(email);

        printf("Introduzca su contrasena: ");
        fflush(stdin);
        gets(contrasena);

        i=0;
        while ( i<*n_admp && strcmp(admp[i].email,email)!=0 ) i++;

        if ( i >= *n_admp ) error = 1;
        else {

            if ( strcmp(admp[i].Contrasenna,contrasena)!=0 ) error = 1;

            if ( admp[i].Perfil_usuario != admin ) error = 1;


        }

        if ( error == 1 ){

            printf("\nEl email o la contrasena son incorectos.\n");
            system("pause");
            system("cls");

        }else *usu_act = i;

    }while(error==1);


    printf("\nHa iniciado sesion correctamente.");
    system("pause");
    system("cls");


}

void inicio_sesion_proveedor ( Adminprov *admp ,  int *n_admp , int *usu_act ){

    int i;
    char email[31]="\0",contrasena[16]="\0",error;

    do{

        error=0;

        printf("Introduzca su email: ");;
        fflush(stdin);
        gets(email);

        printf("Introduzca su contrasena: ");
        fflush(stdin);
        gets(contrasena);

        i=0;
        while ( i<*n_admp && strcmp(admp[i].email,email)!=0 ) i++;

        if ( i >= *n_admp ) error = 1;
        else {

            if ( strcmp(admp[i].Contrasenna,contrasena)!=0 ) error = 1;

            if ( admp[i].Perfil_usuario != proveedor ) error = 1;


        }

        if ( error == 1 ){

            printf("\nEl email o la contrasena son incorectos.\n");
            system("pause");
            system("cls");

        }else *usu_act = i;

    }while(error==1);


    printf("\nHa iniciado sesion correctamente.");
    system("pause");
    system("cls");


}

void inicio_sesion_transportista (  Transportista *transp , int *n_transp , int *usu_act){

    int i;
    char email[31]="\0",contrasena[16]="\0",error;

    do{

        error=0;

        printf("Introduzca su email: ");;
        fflush(stdin);
        gets(email);

        printf("Introduzca su contrasena: ");
        fflush(stdin);
        gets(contrasena);

        i=0;
        while ( i<*n_transp && strcmp(transp[i].email,email)!=0 ) i++;

        if ( i >= *n_transp ) error = 1;
        else {

            if ( strcmp(transp[i].Contrasenna,contrasena)!=0 ) error = 1;

        }

        if ( error == 1 ){

            printf("\nEl email o la contrasena son incorectos.\n");
            system("pause");
            system("cls");

        }else *usu_act = i;

    }while(error==1);


    printf("\nHa iniciado sesion correctamente.");
    system("pause");
    system("cls");



}



void registro ( Cliente *client , Adminprov *admp , Transportista *transp, int *n_cliente, int *n_admp , int *n_transp ){

    int op;

    do{

        printf("Como quieres registrarte?:\n1.Cliente\n2.Proveedor\n3.Transportista\n");
        scanf("%i",&op);


        switch (op) {
            case 1:
                nuevo_cliente(&client,n_cliente);
                break;
            case 2:
                nuevo_adminprov(&admp,n_admp,proveedor);
                break;
            case 3:
                nuevo_transportista(&transp,n_transp);
                break;
            default:
                printf("\nEscribe un numero del 1 al 3");
                break;
        }

    }while( op<1 || op>3);


}


void inicio_sesion ( Cliente *client , Adminprov *admp , Transportista *transp, int *n_cliente, int *n_admp , int *n_transp , int *usu_act , usu *tipo_usu){


    int op;

    do{

        printf("Como quieres iniciar sesion?:\n1.Cliente\n2.Admin\n3.Proveedor\n4.Transportista\n");
        scanf("%i",&op);

        system("cls");

        switch (op) {
            case 1:

                *tipo_usu=cliente;
                inicio_sesion_cliente( client,n_cliente,usu_act);

                break;
            case 2:

                *tipo_usu=admin;
                inicio_sesion_admin(admp,n_admp,usu_act);

                break;
            case 3:

                *tipo_usu=proveedor;
                inicio_sesion_proveedor(admp,n_admp,usu_act);

                break;
            case 4:

                *tipo_usu=transportista;
                inicio_sesion_transportista(transp,n_transp,usu_act);

                break;
            default:
                printf("\nEscribe un numero del 1 al 4.");
                break;
        }

    }while( op < 1 || op > 4);



}


void menu_inicio_sesion ( Cliente *client , Adminprov *admp , Transportista *transp , int *n_cliente, int *n_admp , int *n_transp , int *usu_act , usu *tipo_usu ){

    int op;

    printf("1.Iniciar sesion\n2.Registro\n");
    scanf("%i",&op);

    system("cls");

    switch (op) {

        case 1:

            inicio_sesion(client,admp,transp,n_cliente,n_admp,n_transp,usu_act,tipo_usu);

            break;
        case 2:

            registro(client,admp,transp,n_cliente,n_admp,n_transp);
            
            break;
        default:
            break;
    }


}




