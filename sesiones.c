/*##### MODULO SESIONES #####*/

#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sesiones.h"
#define LINE 150

//char* usuario_actual(char*);
//FUCION QUE DEVUELVA EL TIPO DE ENUM

void borrar_adminprov_con_id(Adminprov**,char*,int*);



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


void nuevo_adminprov(Adminprov **a,int *n_adminprov){
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
            siguiente_id(Id,4);
        }
    printf("\n Su Id de administrador/proveedor es: ");
    puts(Id); 
    strcpy((*a)[*n_adminprov-1].Id_empresa,Id);

    printf("\nIntrozuca el nombre de su empresa(20 caracteres):\n");     
    leer_string(nomb,21);
    //puts(nomb);
    strcpy((*a)[*n_adminprov-1].Nombre,nomb);
    if(strcmp(nomb,"ESIZON\0")==0){
        (*a)[*n_adminprov-1].Perfil_usuario=admin;
    }else{
        (*a)[*n_adminprov-1].Perfil_usuario=proveedor;
    }           

    printf("\nIntroduzca su correco electrónico de empresa(31 caracteres):\n");
    leer_string((*a)[*n_adminprov-1].email,31);

    printf("\nCree e introduzca una contraseña(hasta 15 dígitos):\n");
    leer_string((*a)[*n_adminprov-1].Contrasenna,16);
    }
}



//cabecera:int indice_con_id_cliente(Adminprov **vector_admin,cha*id_admin,int)
//precondición: vector cliente un vector de estructura adminprov, id admin una cadena y num_admin el número de admin/prov registrados del vector
//postcondición: devuelve el valor del indice del vector de estructura cuya id coincide con el de la cadena
int indice_con_id_adminprov(Adminprov**vector_admin,char *id_admin,int num_admin){
    int i=0,devolver;
    do{
        if(strcmp(id_admin,(*vector_admin)[i].Id_empresa)==0){
        devolver=i;
    }
        i++;
    }while(i<=num_admin);
    return devolver;
}



void borrar_adminprov_con_id(Adminprov**vector_admin,char *Id_admin, int *n_admin){
    int i,aux;
    aux=*n_admin;

    if(*n_admin==1){
        free(vector_admin);
        *n_admin=0;
    }else{
    for(i=indice_con_id_adminprov(vector_admin,Id_admin,aux)+1;i<aux;i++)
        (*vector_admin)[i-1]=(*vector_admin)[i];
    }
    (*n_admin)=aux-1;
}


void menu_principal_transportista ( Cliente *client , Adminprov *admp , Transportista *transp , Locker *lock , CompartimentoLocker *c_lock , Pedido *ped, ProductoPedido *pr_p , Devoluciones *dev , int *n_cliente, int *n_admp , int *n_transp , int *n_lock , int *n_c_lock , int *n_ped , int *n_pr_p , int *n_dev , usu tipo_usu, int id_usu_act){

    int op;

    printf("                Transportista: %s                 \n",transp[id_usu_act].Nombre);
    printf("-----------------------------------------------------------\n");

    do{

        printf("1.Perfil\n2.Repartos\n3.Retornos\n4.Salir\n");
        scanf("%i",&op);

        system("cls");

        switch (op) {
            case 1:
                break;
            case 2:
                break;
            case 3:

                menu_pedidos(client,transp,lock,c_lock,ped,pr_p,n_cliente,n_transp,n_lock,n_c_lock,n_ped,n_pr_p,transportista,id_usu_act);

                system("cls");

                menu_principal_cliente(client,admp,transp,lock,c_lock,ped,pr_p,dev,n_cliente,n_admp,n_transp,n_lock,n_c_lock,n_ped,n_pr_p,n_dev,transportista,id_usu_act);


                break;
            case 4:

                volcado_adminprov(&admp,n_admp);
                volcado_transp(&transp,n_transp);
                volcado_cliente(&client,n_cliente);

                volcado_pedidos(ped,n_ped);
                volcado_prod_pedidos(ped,pr_p,n_ped,n_pr_p);
                volcado_devoluciones(dev,n_dev);

                volcado_lockers(lock,n_lock);
                volcado_comp_lockers(c_lock,n_c_lock);
                exit(1);

            default:
                printf("\nEscribe un numero valido.");
                break;
        }


    }while( op < 1 || op > 10 );


}


void menu_principal_proveedor ( Cliente *client , Adminprov *admp , Transportista *transp , Locker *lock , CompartimentoLocker *c_lock , Pedido *ped, ProductoPedido *pr_p , Devoluciones *dev , int *n_cliente, int *n_admp , int *n_transp , int *n_lock , int *n_c_lock , int *n_ped , int *n_pr_p , int *n_dev , usu tipo_usu, int id_usu_act){

    int op;

    printf("                EMPRESA: %s                 \n",admp[id_usu_act].Nombre);
    printf("-----------------------------------------------------------\n");

    do{

        printf("1.Perfil\n2.Productos\n3.Pedidos\n4.Salir\n");
        scanf("%i",&op);

        system("cls");

        switch (op) {
            case 1:
                break;
            case 2:
                break;
            case 3:

                menu_pedidos(client,transp,lock,c_lock,ped,pr_p,n_cliente,n_transp,n_lock,n_c_lock,n_ped,n_pr_p,proveedor,id_usu_act);

                system("cls");

                menu_principal_proveedor(client,admp,transp,lock,c_lock,ped,pr_p,dev,n_cliente,n_admp,n_transp,n_lock,n_c_lock,n_ped,n_pr_p,n_dev,proveedor,id_usu_act);


                break;
            case 4:

                volcado_adminprov(&admp,n_admp);
                volcado_transp(&transp,n_transp);
                volcado_cliente(&client,n_cliente);

                volcado_pedidos(ped,n_ped);
                volcado_prod_pedidos(ped,pr_p,n_ped,n_pr_p);
                volcado_devoluciones(dev,n_dev);

                volcado_lockers(lock,n_lock);
                volcado_comp_lockers(c_lock,n_c_lock);
                exit(1);

            default:
                printf("\nEscribe un numero valido.");
                break;
        }


    }while( op < 1 || op > 10 );


}




void menu_principal_admin ( Cliente *client , Adminprov *admp , Transportista *transp , Locker *lock , CompartimentoLocker *c_lock , Pedido *ped, ProductoPedido *pr_p , Devoluciones *dev , int *n_cliente, int *n_admp , int *n_transp , int *n_lock , int *n_c_lock , int *n_ped , int *n_pr_p , int *n_dev , usu tipo_usu, int id_usu_act){

    int op;

    printf("                 Administrador                 \n");
    printf("-----------------------------------------------------------\n");

    do{

        printf("1.Perfil\n2.Clientes\n3.Proveedores\n4.Productos\n5.Categorias\n6.Pedidos\n7.Transportista\n8.Descuento\n9.Devoluciones\n10.Salir\n");
        scanf("%i",&op);

        system("cls");

        switch (op) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:

                menu_pedidos(client,transp,lock,c_lock,ped,pr_p,n_cliente,n_transp,n_lock,n_c_lock,n_ped,n_pr_p,admin,id_usu_act);

                system("cls");

                menu_principal_admin(client,admp,transp,lock,c_lock,ped,pr_p,dev,n_cliente,n_admp,n_transp,n_lock,n_c_lock,n_ped,n_pr_p,n_dev,admin,id_usu_act);

                break;
            case 7:
                break;
            case 8:
                break;
            case 9:

                menu_devoluciones_admin(ped,pr_p,dev,n_dev,n_ped,n_pr_p,admin);
                system("cls");
                menu_principal_admin(client,admp,transp,lock,c_lock,ped,pr_p,dev,n_cliente,n_admp,n_transp,n_lock,n_c_lock,n_ped,n_pr_p,n_dev,admin,id_usu_act);

                break;
            case 10:
                volcado_adminprov(&admp,n_admp);
                volcado_transp(&transp,n_transp);
                volcado_cliente(&client,n_cliente);

                volcado_pedidos(ped,n_ped);
                volcado_prod_pedidos(ped,pr_p,n_ped,n_pr_p);
                volcado_devoluciones(dev,n_dev);

                volcado_lockers(lock,n_lock);
                volcado_comp_lockers(c_lock,n_c_lock);
                exit(1);
            default:
                printf("\nEscribe un numero valido.");
                break;
        }


    }while( op < 1 || op > 10 );




}


void menu_principal_cliente ( Cliente *client , Adminprov *admp , Transportista *transp , Locker *lock , CompartimentoLocker *c_lock , Pedido *ped, ProductoPedido *pr_p , Devoluciones *dev , int *n_cliente, int *n_admp , int *n_transp , int *n_lock , int *n_c_lock , int *n_ped , int *n_pr_p , int *n_dev , usu tipo_usu, int id_usu_act ) {

    int op;

    printf("                 Usuario: %s                 \n",client[id_usu_act].Nombr_cliente);
    printf("-----------------------------------------------------------\n");

    do{

        printf("1.Perfil\n2.Productos\n3.Descuentos\n4.Pedidos\n5.Devoluciones\n6.Salir\n");
        scanf("%i",&op);

        system("cls");

        switch (op) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:

                menu_pedidos(client,transp,lock,c_lock,ped,pr_p,n_cliente,n_transp,n_lock,n_c_lock,n_ped,n_pr_p,cliente,id_usu_act);
                system("cls");
                menu_principal_cliente(client,admp,transp,lock,c_lock,ped,pr_p,dev,n_cliente,n_admp,n_transp,n_lock,n_c_lock,n_ped,n_pr_p,n_dev,cliente,id_usu_act);


                break;
            case 5:

                menu_devoluciones_clientes(ped,pr_p,dev,n_dev,n_ped,n_pr_p,client[id_usu_act].Id_cliente,cliente);
                system("cls");
                menu_principal_cliente(client,admp,transp,lock,c_lock,ped,pr_p,dev,n_cliente,n_admp,n_transp,n_lock,n_c_lock,n_ped,n_pr_p,n_dev,cliente,id_usu_act);



                break;
            case 6:

                volcado_adminprov(&admp,n_admp);
                volcado_transp(&transp,n_transp);
                volcado_cliente(&client,n_cliente);

                volcado_pedidos(ped,n_ped);
                volcado_prod_pedidos(ped,pr_p,n_ped,n_pr_p);
                volcado_devoluciones(dev,n_dev);

                volcado_lockers(lock,n_lock);
                volcado_comp_lockers(c_lock,n_c_lock);

                exit(1);
            default:
                printf("\nEscribe un numero valido.");
                break;
        }


    }while( op < 1 || op > 6 );








}

void menu_principal ( Cliente *client , Adminprov *admp , Transportista *transp , Locker *lock , CompartimentoLocker *c_lock , Pedido *ped, ProductoPedido *pr_p , Devoluciones *dev , int *n_cliente, int *n_admp , int *n_transp , int *n_lock , int *n_c_lock , int *n_ped , int *n_pr_p , int *n_dev , usu tipo_usu , int id_usu_act){


    switch (tipo_usu) {


        case cliente:

            menu_principal_cliente(client,admp,transp,lock,c_lock,ped,pr_p,dev,n_cliente,n_admp,n_transp,n_lock,n_c_lock,n_ped,n_pr_p,n_dev,cliente,id_usu_act);

            break;
        case admin:

            menu_principal_admin(client,admp,transp,lock,c_lock,ped,pr_p,dev,n_cliente,n_admp,n_transp,n_lock,n_c_lock,n_ped,n_pr_p,n_dev,admin,id_usu_act);

            break;
        case proveedor:

            menu_principal_proveedor(client,admp,transp,lock,c_lock,ped,pr_p,dev,n_cliente,n_admp,n_transp,n_lock,n_c_lock,n_ped,n_pr_p,n_dev,proveedor,id_usu_act);

            break;
        case transportista:

            menu_principal_transportista(client,admp,transp,lock,c_lock,ped,pr_p,dev,n_cliente,n_admp,n_transp,n_lock,n_c_lock,n_ped,n_pr_p,n_dev,transportista,id_usu_act);

            break;
        default:

            printf("Error con el tipo de ususario");
            exit(1);

    }


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
                nuevo_adminprov(&admp,n_admp);
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




