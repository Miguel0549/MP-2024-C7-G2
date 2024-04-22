#include "Principal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



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


void menu_principal_transportista ( Cliente *client , Adminprov *admp , Transportista *transp , Locker *lock , CompartimentoLocker *c_lock , Pedido *ped, ProductoPedido *pr_p , Devoluciones *dev , producto *prod, categoria *cat, Descuentos *desc, Descuentos_clientes *desc_cl, int *n_cliente, int *n_admp , int *n_transp , int *n_lock , int *n_c_lock , int *n_ped , int *n_pr_p , int *n_dev ,int *n_prod,int *n_cat,int *n_desc,int *n_desc_cl, usu tipo_usu, int id_usu_act ){

    int op;


    do{

        printf("                Transportista: %s                 \n",transp[id_usu_act].Nombre);
        printf("-----------------------------------------------------------\n");

        do{

            printf("1.Perfil\n2.Repartos\n3.Retornos\n4.Salir\n");
            scanf("%i",&op);

            system("cls");

            switch (op) {
                case 1:

                    datos_transportista(transp,id_usu_act);

                    system("cls");

                    break;
                case 2:

                    menu_pedidos_transp(lock,c_lock,ped,pr_p,n_lock,n_c_lock,n_ped,n_pr_p,transp[id_usu_act].Id_transp,transportista);

                    system("cls");

                    break;
                case 3:

                    //menu_devoluciones_transportistas(ped,pr_p,dev,n_dev,n_ped,n_pr_p,transp[id_usu_act].Id_transp,transportista);

                    system("cls");

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

                    volcado_descuentos(&desc,n_desc);
                    volcado_descuentos_clientes(&desc_cl,n_desc_cl);

                    guardar_producto();
                    guardar_categoria();

                    exit(1);

                default:
                    printf("\nEscribe un numero valido.");
                    break;
            }


        }while( op < 1 || op > 10 );

    }while(1);


}

void listado_prod ( Adminprov *admpr , producto *prod, int *n_prod ,int *n_admpr,int ind_admpr , usu tipo_usu ){

    int i,j,op;
    char c='a',id_prod[8]="\0";

    system("cls");


    if ( tipo_usu == admin ){


        printf("---------------------- Todos los productos ------------------------\n\n");

        for ( i=0 ; i<*n_prod ; i++ ){

            printf("[%c].%s-%s-%s\n",c,prod[i].id_prod,prod[i].id_categ,prod[i].nombre);
            c++;

        }

        printf("-------------------------------------------------------------\n\n");


    }else{


        printf("---------------------- Sus productos ------------------------\n\n");

        for ( i=0 ; i<*n_prod ; i++ ){

            if ( strcmp(prod[i].id_gestor,admpr[ind_admpr].Id_empresa)==0 ){

                printf("[%c].%s-%s-%s\n",c,prod[i].id_prod,prod[i].id_categ,prod[i].nombre);
                c++;

            }

        }

        printf("-------------------------------------------------------------\n\n");

    }


    do{

        printf("1.Alta\n2.Baja\n3.Modificar\n4.Salir\n");
        scanf("%i",&op);


        switch (op) {
            case 1:

                if ( tipo_usu == admin ){

                    alta_producto(NULL,n_admpr);

                }else{

                    alta_producto(admpr[ind_admpr].Id_empresa,n_admpr);

                }



                system("cls");

                break;
            case 2:

                do{

                    printf("Escribe el Id del producto a borrar: ");
                    fflush(stdin);
                    gets(id_prod);

                    j=0;
                    while ( j<*n_prod && strcmp(id_prod,prod[j].id_prod) !=0) j++;

                    if ( j >= *n_prod || strcmp(prod[j].id_gestor,admpr[ind_admpr].Id_empresa)!=0 ) printf("\nEscribe un id valido\n");

                }while ( j >= *n_prod || strcmp(prod[j].id_gestor,admpr[ind_admpr].Id_empresa)!=0);

                borrar_producto(j);

                system("cls");

                break;
            case 3:

                do{

                    printf("Escribe el id del producto a modificar: ");
                    fflush(stdin);
                    gets(id_prod);

                    j=0;
                    while ( j<*n_prod && strcmp(id_prod,prod[j].id_prod) !=0) j++;

                    if ( j >= *n_prod || strcmp(prod[j].id_gestor,admpr[ind_admpr].Id_empresa)!=0 ) printf("\nEscribe un id valido\n");

                }while ( j >= *n_prod || strcmp(prod[j].id_gestor,admpr[ind_admpr].Id_empresa)!=0);

                menu_modificar_producto(j);

                system("cls");

                break;
            case 4:
                break;
            default:
                printf("Escribe un numero del 1 al 4.");
                break;
        }

        system("cls");

    }while ( op < 1 || op > 4);



}



void menu_principal_proveedor ( Cliente *client , Adminprov *admp , Transportista *transp , Locker *lock , CompartimentoLocker *c_lock , Pedido *ped, ProductoPedido *pr_p , Devoluciones *dev , producto *prod, categoria *cat, Descuentos *desc, Descuentos_clientes *desc_cl, int *n_cliente, int *n_admp , int *n_transp , int *n_lock , int *n_c_lock , int *n_ped , int *n_pr_p , int *n_dev ,int *n_prod,int *n_cat,int *n_desc,int *n_desc_cl, usu tipo_usu, int id_usu_act ){

    int op;

    do{

        printf("                EMPRESA: %s                 \n",admp[id_usu_act].Nombre);
        printf("-----------------------------------------------------------\n");

        do{

            printf("1.Perfil\n2.Productos\n3.Pedidos\n4.Salir\n");
            scanf("%i",&op);

            system("cls");

            switch (op) {
                case 1:

                    datos_admin_prov(admp,id_usu_act);

                    system("cls");

                    break;
                case 2:

                    listado_prod(admp,prod,n_prod,n_admp,id_usu_act,proveedor);

                    system("cls");

                    break;
                case 3:

                    //menu_pedidos_prov(ped,pr_p,prod,n_ped,n_pr_p,n_prod,proveedor);

                    system("cls");


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

                    volcado_descuentos(&desc,n_desc);
                    volcado_descuentos_clientes(&desc_cl,n_desc_cl);

                    guardar_producto();
                    guardar_categoria();

                    exit(1);

                default:
                    printf("\nEscribe un numero valido.");
                    break;
            }


        }while( op < 1 || op > 10 );

    }while(1);


}




void menu_principal_admin ( Cliente *client , Adminprov *admp , Transportista *transp , Locker *lock , CompartimentoLocker *c_lock , Pedido *ped, ProductoPedido *pr_p , Devoluciones *dev , producto *prod, categoria *cat, Descuentos *desc, Descuentos_clientes *desc_cl, int *n_cliente, int *n_admp , int *n_transp , int *n_lock , int *n_c_lock , int *n_ped , int *n_pr_p , int *n_dev ,int *n_prod,int *n_cat,int *n_desc,int *n_desc_cl, usu tipo_usu, int id_usu_act ){

    int op;

    do{

        printf("                 Administrador                 \n");
        printf("-----------------------------------------------------------\n");

        do{

            printf("1.Perfil\n2.Clientes\n3.Proveedores\n4.Productos\n5.Categorias\n6.Pedidos\n7.Transportista\n8.Descuentos\n9.Devoluciones\n10.Salir\n");
            scanf("%i",&op);

            system("cls");

            switch (op) {
                case 1:

                    datos_admin_prov(admp,id_usu_act);

                    system("cls");

                    break;
                case 2:

                    listado_cliente(client,n_cliente);

                    system("cls");

                    break;
                case 3:

                    listado_adminprov_prod(admp,prod,n_admp,n_prod);

                    system("cls");

                    break;
                case 4:

                    listado_prod(admp,prod,n_prod,n_admp,-1,admin);

                    system("cls");

                    break;
                case 5:

                    menu_admin_cat();

                    system("cls");

                    break;
                case 6:

                    menu_pedidos_admin(ped,pr_p,n_ped,n_pr_p,admin);

                    system("cls");

                    break;
                case 7:

                    listado_transportista(transp,n_transp);

                    system("cls");

                    break;
                case 8:

                    listar_descuentos(&desc,n_desc);

                    system("cls");

                    break;
                case 9:

                    menu_devoluciones_admin(ped,pr_p,dev,n_dev,n_ped,n_pr_p,admin);
                    system("cls");

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

                    volcado_descuentos(&desc,n_desc);
                    volcado_descuentos_clientes(&desc_cl,n_desc_cl);

                    guardar_producto();
                    guardar_categoria();

                    exit(1);
                default:
                    printf("\nEscribe un numero valido.");
                    break;
            }


        }while( op < 1 || op > 10 );

    } while (1);


}

void listado_cliente ( Cliente *clt , int *n_clt ){

    int i,j,op;
    char c='a',resp,op_cl[8],id_cliente_borrar[8]="\0";

    do{

        printf("--------------------- Clientes ------------------------\n\n");

        for ( i=0 ; i<*n_clt ; i++ ){

            printf("[%c].%s-%s\n",c,clt[i].Id_cliente,clt[i].Nombr_cliente);


            c++;
        }

        printf("\n\n-----------------------------------------------\n");


        do{

            printf("1.Alta\n2.Baja\n3.Modificar\n4.Salir\n");
            scanf("%i",&op);


            switch (op) {
                case 1:

                    nuevo_cliente(&clt,n_clt);

                    system("cls");

                    break;
                case 2:

                    printf("Escribe el Id del cliente a borrar: ");
                    fflush(stdin);
                    gets(id_cliente_borrar);


                    borrar_cliente_con_id(&clt,id_cliente_borrar,n_clt);

                    system("cls");

                    break;
                case 3:

                    do{

                        printf("Escribe el id del cliente a modificar: ");
                        fflush(stdin);
                        gets(op_cl);

                        j=0;
                        while ( j<*n_clt && strcmp(op_cl,clt[j].Id_cliente) !=0) j++;

                        if ( j >= *n_clt) printf("\nEscribe un id valido\n");

                    }while ( j >= *n_clt);


                    modificar_cliente(&clt,j,admin);

                    system("cls");

                    break;
                case 4:
                    break;
                default:
                    printf("Escribe un numero del 1 al 4.");
                    break;
            }

            system("cls");

        }while ( op < 1 || op > 4);


    }while( op != 4 );


}

void menu_principal_cliente ( Cliente *client , Adminprov *admp , Transportista *transp , Locker *lock , CompartimentoLocker *c_lock , Pedido *ped, ProductoPedido *pr_p , Devoluciones *dev , producto *prod, categoria *cat, Descuentos *desc, Descuentos_clientes *desc_cl, int *n_cliente, int *n_admp , int *n_transp , int *n_lock , int *n_c_lock , int *n_ped , int *n_pr_p , int *n_dev ,int *n_prod,int *n_cat,int *n_desc,int *n_desc_cl, usu tipo_usu, int id_usu_act ) {

    int op;

    do{

        printf("                 Usuario: %s                 \n",client[id_usu_act].Nombr_cliente);
        printf("-----------------------------------------------------------\n");

        do{

            printf("1.Perfil\n2.Productos\n3.Descuentos\n4.Pedidos\n5.Devoluciones\n6.Salir\n");
            scanf("%i",&op);

            system("cls");

            switch (op) {
                case 1:

                    datos_cliente(client,id_usu_act);

                    system("cls");

                    break;
                case 2:

                    menu_cliente_prod();

                    system("cls");

                    break;
                case 3:

                    listar_descuentos_propios(&desc,&desc_cl,client[id_usu_act].Id_cliente,n_desc);

                    system("pause");
                    system("cls");

                    break;
                case 4:

                    menu_pedidos_clientes(ped, pr_p,c_lock, n_ped, n_pr_p,n_c_lock, client[id_usu_act].Id_cliente,cliente);
                    system("cls");

                    break;
                case 5:

                    menu_devoluciones_clientes(ped,pr_p,dev,n_dev,n_ped,n_pr_p,client[id_usu_act].Id_cliente,cliente);
                    system("cls");

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

                    volcado_descuentos(&desc,n_desc);
                    volcado_descuentos_clientes(&desc_cl,n_desc_cl);

                    guardar_producto();
                    guardar_categoria();

                    exit(1);
                default:
                    printf("\nEscribe un numero valido.");
                    break;
            }


        }while( op < 1 || op > 6 );

    }while(1);





}


void datos_admin_prov ( Adminprov *admpr, int ind_admpr ){

    char resp;
    system("cls");

    printf("------------------------------------------------------\n\n");
    printf("Id_empresa: %s\nNombre_empresa: %s\nEmail: %s\nContrasena: %s\n",
           admpr[ind_admpr].Id_empresa,
           admpr[ind_admpr].Nombre,
           admpr[ind_admpr].email,
           admpr[ind_admpr].Contrasenna);


    if ( admpr[ind_admpr].Perfil_usuario == admin ) printf("Perfil_Usuario: administrador\n\n");
    else printf("Perfil_Usuario: proveedor\n\n");


    printf("------------------------------------------------------\n\n");

    do{

        printf("Quiere cambiar sus datos?(s/n): ");
        fflush(stdin);
        scanf("%c",&resp);

        system("cls");

        if ( resp == 's' || resp == 'S' ){

            modificar_admin(&admpr,ind_admpr);

        }else if ( resp != 's' & resp != 'S' && resp != 'n' & resp != 'N' ) printf("\nEscribe s o n");

    } while (resp != 's' & resp != 'S' && resp != 'n' & resp != 'N');


}


void listado_prod_ext ( Adminprov *adminprov , producto *prod , int *n_admpr , int * n_prod ){

    int i,j,k;
    char c='a';

    system("cls");

    i=0;
    while ( i < *n_admpr && strcmp(adminprov[i].Nombre,"ESIZON")!=0) i++;


    printf("--------------------- Productos externos ------------------------\n\n");

    for ( j=0 ; j<*n_prod ; j++ ){

        if (strcmp(prod[j].id_gestor,adminprov[i].Id_empresa)!=0){

            printf("[%c].%s-%s-%s-%s\n",c,prod[j].id_prod,prod[j].id_gestor,prod[j].id_categ,prod[j].nombre);
            c++;

        }

    }

    printf("\n\n-----------------------------------------------------------\n");

    system("pause");

}



void listado_proveedores ( Adminprov *admpr , int *n_admpr ,usu tipo_usu){

    int i,j,op;
    char c='a',id_proveedor[5]="\0";

    system("cls");

    do{

        printf("--------------------- Proveedores ------------------------\n\n");

        for ( i=0 ; i<*n_admpr ; i++ ){

            if (strcmp(admpr[i].Nombre,"ESIZON") != 0){

                printf("[%c].%s-%s\n",c,admpr[i].Id_empresa,admpr[i].Nombre);
                c++;

            }

        }

        printf("\n\n-----------------------------------------------\n");


        do{

            printf("1.Alta\n2.Baja\n3.Modificar\n4.Salir\n");
            scanf("%i",&op);


            switch (op) {
                case 1:

                    nuevo_adminprov(&admpr,n_admpr,admin);

                    system("cls");

                    break;
                case 2:

                    printf("Escribe el Id del proveedor a borrar: ");
                    fflush(stdin);
                    gets(id_proveedor);

                    borrar_adminprov_con_id(&admpr,id_proveedor,n_admpr);

                    system("cls");

                    break;
                case 3:

                    do{

                        printf("Escribe el id del cliente a modificar: ");
                        fflush(stdin);
                        gets(id_proveedor);

                        j=0;
                        while ( j<*n_admpr && strcmp(id_proveedor,admpr[j].Id_empresa) !=0) j++;

                        if ( j >= *n_admpr) printf("\nEscribe un id valido\n");

                    }while ( j >= *n_admpr);


                    modificar_proveedor(admpr,j);

                    system("cls");

                    break;
                case 4:
                    break;
                default:
                    printf("Escribe un numero del 1 al 4.");
                    break;
            }

            system("cls");

        }while ( op < 1 || op > 4);


    }while( op != 4 );



}



void listado_adminprov_prod( Adminprov *admpr , producto *prod , int *n_admpr , int *n_prod ){

    int i,op;

    system("cls");

    do{

        do{

            printf("1.Proveedores\n2.Productos externos\n3.salir\n");
            scanf("%i",&op);

            switch (op) {
                case 1:

                    listado_proveedores(admpr,n_admpr,admin);

                    system("cls");

                    break;
                case 2:

                    listado_prod_ext(admpr,prod,n_admpr,n_prod);

                    system("cls");
                    break;
                case 3:
                    break;
                default:
                    printf("Escribe un numero del 1 al 3");
                    break;
            }


        }while ( op < 1 || op > 3);

    }while( op != 3);


}


void menu_principal ( Cliente *client , Adminprov *admp , Transportista *transp , Locker *lock , CompartimentoLocker *c_lock , Pedido *ped, ProductoPedido *pr_p , Devoluciones *dev , Descuentos *desc, Descuentos_clientes *desc_cl, int *n_cliente, int *n_admp , int *n_transp , int *n_lock , int *n_c_lock , int *n_ped , int *n_pr_p , int *n_dev ,int *n_desc,int *n_desc_cl, usu tipo_usu, int id_usu_act ){

    int *n_prod,*n_cat;

    n_prod = &tamanio_p;
    n_cat = &tamanio_c;



    switch (tipo_usu) {


        case cliente:

            menu_principal_cliente(client,admp,transp,lock,c_lock,ped,pr_p,dev,array_prod,array_cat,desc,desc_cl,n_cliente,n_admp,n_transp,n_lock,n_c_lock,n_ped,n_pr_p,n_dev,n_prod,n_cat,n_desc,n_desc_cl,cliente,id_usu_act);

            break;
        case admin:

            menu_principal_admin(client,admp,transp,lock,c_lock,ped,pr_p,dev,array_prod,array_cat,desc,desc_cl,n_cliente,n_admp,n_transp,n_lock,n_c_lock,n_ped,n_pr_p,n_dev,n_prod,n_cat,n_desc,n_desc_cl,admin,id_usu_act);

            break;
        case proveedor:

            menu_principal_proveedor(client,admp,transp,lock,c_lock,ped,pr_p,dev,array_prod,array_cat,desc,desc_cl,n_cliente,n_admp,n_transp,n_lock,n_c_lock,n_ped,n_pr_p,n_dev,n_prod,n_cat,n_desc,n_desc_cl,proveedor,id_usu_act);

            break;
        case transportista:

            menu_principal_transportista(client,admp,transp,lock,c_lock,ped,pr_p,dev,array_prod,array_cat,desc,desc_cl,n_cliente,n_admp,n_transp,n_lock,n_c_lock,n_ped,n_pr_p,n_dev,n_prod,n_cat,n_desc,n_desc_cl,cliente,id_usu_act);

            break;
        default:

            printf("Error con el tipo de ususario");
            exit(1);

    }


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