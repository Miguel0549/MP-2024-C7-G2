#include "Pedidos.h"
#include <stdio.h>
#include "estado.h"
#include <stdlib.h>
#include <string.h>

#define LINEA 100

void carga_pedidos( Pedido **ped ,int *n_ped){

    int i;
    char line[LINEA]="0";
    char *token;
    char contador_lineas[LINEA]="0";

    FILE *f;

    if ((f = fopen("C:\\Users\\migue\\Desktop\\CLASE\\AMAZON_MP\\Proyecto_MP\\Files\\Pedidos.txt", "r")) == NULL) {

        printf("Error al abrir el archivo");

    } else {

        while(!feof(f)){

            fgets(contador_lineas,LINEA,f);
            (*n_ped)++;

        }


        *ped = (Pedido *)calloc(*n_ped, sizeof(Pedido));
        if (*ped == NULL) {
            printf("Error al crear la memoria para los lockers.\n");
            exit(1);
        }

        rewind(f);

        for ( i=0 ; i< *n_ped; i++ ) {

            fgets(line,LINEA,f);

            strcpy((*ped)[i].id_pedido, strtok(line, "-"));
            strcpy((*ped)[i].fecha_ped, strtok(NULL, "-"));
            strcpy((*ped)[i].id_cliente, strtok(NULL, "-"));
            strcpy((*ped)[i].lugar_entrega, strtok(NULL, "-"));

            if (strcmp( (*ped)[i].lugar_entrega, "domicilio") == 0 ){

                strcpy((*ped)[i].id_cod_prom, strtok(NULL, "-"));

            }else{

                strcpy((*ped)[i].id_locker, strtok(NULL, "-"));

            }



        }

        rewind(f);
        fclose(f);

    }

}





void menu_pedidos_clientes( Pedido *ped , ProductoPedido *prod_ped, int *n_pedidos,int *n_prod_ped, char id_cliente[7] ){

    int i;
    int opcion;
    char c;

    printf("--------- Todos sus pedidos ---------\n\n");

    for (i=0 ; i<*n_pedidos && strcmp( id_cliente , ped[i].id_cliente ) == 0 ; i++ ){

        printf("[%i].%s-%s-%s-%s-%s-%s\n", i,
               ped[i].id_pedido,
               ped[i].fecha_ped,
               ped[i].id_cliente,
               ped[i].lugar_entrega,
               ped[i].id_locker,
               ped[i].id_cod_prom);

    }

    printf("------------------------------------------------\n\n");

    do{

        printf("Seleccione un pedido para ver los productos asociados a este:");
        scanf("%i",&opcion);


        if (strcmp(id_cliente,ped[opcion].id_cliente) != 0 ){

            printf("Introduzca un numeo vaido.");

        }

    }while( strcmp(id_cliente,ped[opcion].id_cliente) != 0);


    for (i = 0; i < *n_prod_ped && strcmp(ped[opcion].id_pedido,prod_ped[i].id_pedido) == 0 ; ++i){

        switch (prod_ped[opcion].est_pedido) {


            case enPreparacion:

                printf("[%c].%s-%s-%i-%s-%i-%s\n", c,
                       prod_ped[i].id_pedido,
                       prod_ped[i].id_prod,
                       prod_ped[i].unidades,
                       prod_ped[i].fecha_entrega,
                       prod_ped[i].importe,
                       "enPreparacion");

                break;
            case enviado:

                printf("[%c].%s-%s-%i-%s-%i-%s\n", c,
                       prod_ped[i].id_pedido,
                       prod_ped[i].id_prod,
                       prod_ped[i].unidades,
                       prod_ped[i].fecha_entrega,
                       prod_ped[i].importe,
                       "enviado");

                break;
            case enReparto:

                printf("[%c].%s-%s-%i-%s-%i-%s-%s\n", c,
                       prod_ped[i].id_pedido,
                       prod_ped[i].id_prod,
                       prod_ped[i].unidades,
                       prod_ped[i].fecha_entrega,
                       prod_ped[i].importe,
                       "enReparto",
                       prod_ped[i].id_transp);

                break;
            case enLocker:

                printf("[%c].%s-%s-%i-%s-%i-%s-%s-%s-%i-%s\n", c,
                       prod_ped[i].id_pedido,
                       prod_ped[i].id_prod,
                       prod_ped[i].unidades,
                       prod_ped[i].fecha_entrega,
                       prod_ped[i].importe,
                       "enLocker",
                       prod_ped[i].id_transp,
                       prod_ped[i].id_locker,
                       prod_ped[i].cod_locker,
                       prod_ped[i].fecha_entr_dev);

                break;
            case entregado:

                printf("[%c].%s-%s-%i-%s-%i-%s-%s\n", c,
                       prod_ped[i].id_pedido,
                       prod_ped[i].id_prod,
                       prod_ped[i].unidades,
                       prod_ped[i].fecha_entrega,
                       prod_ped[i].importe,
                       "entregado",
                       prod_ped[i].id_transp);

                break;
            case devuelto:

                printf("[%c].%s-%s-%i-%s-%i-%s-%s-%s\n", c,
                       prod_ped[i].id_pedido,
                       prod_ped[i].id_prod,
                       prod_ped[i].unidades,
                       prod_ped[i].fecha_entrega,
                       prod_ped[i].importe,
                       "devuelto",
                       prod_ped[i].id_transp,
                       prod_ped[i].fecha_entr_dev);

                break;
            case trasnportista:

                printf("[%c].%s-%s-%i-%s-%i-%s-%s\n", c,
                       prod_ped[i].id_pedido,
                       prod_ped[i].id_prod,
                       prod_ped[i].unidades,
                       prod_ped[i].fecha_entrega,
                       prod_ped[i].importe,
                       "devuelto",
                       prod_ped[i].id_transp);

                break;
            default:

                printf("Error con el estado del producto del pedido");
                exit(1);


        }

        c++;
    }


}


void menu_pedidos_admin( Pedido *ped ,ProductoPedido *prod_ped,  int *n_pedidos ){

    int i,j,tipo_ped;
    char opc,resp;
    int op_ped;

    printf("¿Desea listar los pedidos segun su estado? (s/n):");
    scanf("%c",&resp);

    if ( resp == 's' || resp == 'S'){

        printf("1.«enPreparación»\n2.«enviado»\n3.«enReparto»\n4.«enLocker»\n5.«entregado»\n6.«devuelto»\n7.«transportista»\n");
        printf("Elija el tipo de pedido (1-7):");
        scanf("%i",&tipo_ped);

        switch (tipo_ped) {

            case 1:

                printf("--------- Pedidos en preparacion ---------\n\n");

                for (i=0 ; i<*n_pedidos && prod_ped[i].est_pedido == enPreparacion ; i++ ){

                    j = 0;
                    while (strcmp(prod_ped[i].id_pedido, ped[j].id_pedido) != 0) {
                        j++;
                    }

                    printf("[%i].%s-%s-%s-%s-%s-%s\n", j,
                           ped[j].id_pedido,
                           ped[j].fecha_ped,
                           ped[j].id_cliente,
                           ped[j].lugar_entrega,
                           ped[j].id_locker,
                           ped[j].id_cod_prom);

                }

                break;
            case 2:

                printf("--------- Pedidos enviados ---------\n\n");

                for (i=0 ; i<*n_pedidos && prod_ped[i].est_pedido == enviado ; i++ ) {

                    j = 0;
                    while (strcmp(prod_ped[i].id_pedido, ped[j].id_pedido) != 0) {
                        j++;
                    }

                    printf("[%i].%s-%s-%s-%s-%s-%s\n", j,
                           ped[j].id_pedido,
                           ped[j].fecha_ped,
                           ped[j].id_cliente,
                           ped[j].lugar_entrega,
                           ped[j].id_locker,
                           ped[j].id_cod_prom);

                }

                break;
            case 3:

                printf("--------- Pedidos en reparto ---------\n\n");

                for (i=0 ; i<*n_pedidos && prod_ped[i].est_pedido == enReparto ; i++ ){

                    j = 0;
                    while (strcmp(prod_ped[i].id_pedido, ped[j].id_pedido) != 0) {
                        j++;
                    }

                    printf("[%i].%s-%s-%s-%s-%s-%s\n", j,
                           ped[j].id_pedido,
                           ped[j].fecha_ped,
                           ped[j].id_cliente,
                           ped[j].lugar_entrega,
                           ped[j].id_locker,
                           ped[j].id_cod_prom);

                }

                break;
            case 4:

                printf("--------- Pedidos en locker ---------\n\n");

                for (i=0 ; i<*n_pedidos && prod_ped[i].est_pedido == enLocker ; i++ ){

                    j = 0;
                    while (strcmp(prod_ped[i].id_pedido, ped[j].id_pedido) != 0) {
                        j++;
                    }

                    printf("[%i].%s-%s-%s-%s-%s-%s\n", j,
                           ped[j].id_pedido,
                           ped[j].fecha_ped,
                           ped[j].id_cliente,
                           ped[j].lugar_entrega,
                           ped[j].id_locker,
                           ped[j].id_cod_prom);

                }

                break;
            case 5:

                printf("--------- Pedidos en transportista ---------\n\n");

                for (i=0 ; i<*n_pedidos && prod_ped[i].est_pedido == trasnportista ; i++ ){

                    j = 0;
                    while (strcmp(prod_ped[i].id_pedido, ped[j].id_pedido) != 0) {
                        j++;
                    }

                    printf("[%i].%s-%s-%s-%s-%s-%s\n", j,
                           ped[j].id_pedido,
                           ped[j].fecha_ped,
                           ped[j].id_cliente,
                           ped[j].lugar_entrega,
                           ped[j].id_locker,
                           ped[j].id_cod_prom);

                }

                break;
            case 6:

                printf("--------- Pedidos devueltos ---------\n\n");

                for (i=0 ; i<*n_pedidos && prod_ped[i].est_pedido == devuelto ; i++ ){

                    j = 0;
                    while (strcmp(prod_ped[i].id_pedido, ped[j].id_pedido) != 0) {
                        j++;
                    }

                    printf("[%i].%s-%s-%s-%s-%s-%s\n", j,
                           ped[j].id_pedido,
                           ped[j].fecha_ped,
                           ped[j].id_cliente,
                           ped[j].lugar_entrega,
                           ped[j].id_locker,
                           ped[j].id_cod_prom);

                }

                break;
            case 7:

                printf("--------- Pedidos en preparacion ---------\n\n");

                for (i=0 ; i<*n_pedidos && prod_ped[i].est_pedido == enPreparacion ; i++ ){

                    j = 0;
                    while (strcmp(prod_ped[i].id_pedido, ped[j].id_pedido) != 0) {
                        j++;
                    }

                    printf("[%i].%s-%s-%s-%s-%s-%s\n", j,
                           ped[j].id_pedido,
                           ped[j].fecha_ped,
                           ped[j].id_cliente,
                           ped[j].lugar_entrega,
                           ped[j].id_locker,
                           ped[j].id_cod_prom);

                }

                break;
            default:
                printf("Error en el tipo de pedido");
                exit(1);

        }


    }else{

        printf("--------- Todos los pedidos ---------\n\n");

        for (i=0 ; i<*n_pedidos ; i++ ){

            printf("[%i].%s-%s-%s-%s-%s-%s\n",i,
                   ped[i].id_pedido,
                   ped[i].fecha_ped,
                   ped[i].id_cliente,
                   ped[i].lugar_entrega,
                   ped[i].id_locker,
                   ped[i].id_cod_prom);

        }

    }


    printf("\nElija una opcion:\n");
    printf("1.alta\n2.baja\n3.modificar\n4.asignar transportista )\n");
    scanf("%i",&op_ped);

    switch (op_ped) {

        case 1:

            // crear_pedido();

            break;
        case 2:

            // eliminar_pedido();

            break;
        case 3:

            // modificar_pedido();

            break;
        case 4:

            // asignar_transp();

            break;
        default:
            break;

    }


}


void menu_pedidos_prov( Pedido *ped , ProductoPedido *prod_ped, int *n_pedidos ){



}

void menu_pedidos_transp( Pedido *ped , ProductoPedido *prod_ped, int *n_pedidos ){




}




void menu_pedidos ( Pedido *ped , ProductoPedido *prod_ped ,int *n_pedidos ,int *n_prod_ped, usu tipo_usu ){

    int i;
    char id_cliente[7];

    switch (tipo_usu) {


        case cliente:

            menu_pedidos_clientes(ped,prod_ped,n_pedidos,n_prod_ped,id_cliente);

            break;
        case admin:

            menu_pedidos_admin(ped,prod_ped,n_pedidos);

            break;
        case proveedor:

            menu_pedidos_prov(ped,prod_ped,n_pedidos);

            break;
        case transportista:

            menu_pedidos_transp(ped,prod_ped,n_pedidos);

            break;
        default:

            printf("Error con el tipo de ususario");
            exit(1);

    }

}
