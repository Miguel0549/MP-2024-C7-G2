#include "Devoluciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pedidos.h"


#define LINEA 100

void carga_devoluciones( Devoluciones **dev ,int *n_dev){    // FUNCIONA

    int i,j;
    char line[LINEA]="0";
    char estado[18]="\0";
    char contador_lineas[LINEA]="0";

    FILE *f;

    if ((f = fopen("Files\\Devoluciones.txt", "r")) == NULL) {

        printf("Error al abrir el archivo");

    } else {

        while(!feof(f)){

            fgets(contador_lineas,LINEA,f);
            (*n_dev)++;

        }


        *dev = (Devoluciones *)calloc(*n_dev, sizeof(Devoluciones));
        if (*dev == NULL) {
            printf("Error al crear la memoria para las Devoluciones.\n");
            exit(1);
        }

        rewind(f);

        for ( i=0 ; i< *n_dev; i++ ) {

            fgets(line,LINEA,f);

            strcpy((*dev)[i].id_pedido, strtok(line, "-\n"));
            strcpy((*dev)[i].id_prod, strtok(NULL, "-\n"));
            strcpy((*dev)[i].fecha_dev, strtok(NULL, "-\n"));
            strcpy((*dev)[i].motivo, strtok(NULL, "-\n"));
            strcpy(estado, strtok(NULL, "-\n"));

            if (strcmp( estado , "pendiente")==0){

                (*dev)[i].est_dev = pediente;

                strcpy((*dev)[i].fecha_cad, strtok(NULL, "-\n"));

            }else if ( strcmp( estado , "aceptado")==0 ){

                (*dev)[i].est_dev = aceptado;

                strcpy((*dev)[i].fecha_acp, strtok(NULL, "-\n"));

            }else if ( strcmp( estado , "denegado")==0 ){

                (*dev)[i].est_dev = denegado;

            }else if ( strcmp( estado , "enviado")==0 ){

                (*dev)[i].est_dev = enviado;

            }else if ( strcmp(estado,"recibido") == 0) {

                (*dev)[i].est_dev = recibido;

            }else{

                printf("Error al ver el estado de la devolucion");

            }


            for ( j=0 ; j<18 ; j++ ){

                estado[j] = '\0';

            }


        }

        rewind(f);
        fclose(f);

    }

}



void volcado_devoluciones ( Devoluciones *d, int *n_dev ){

    int i;
    char line[LINEA]="\0",Num_compT[4]="\0";
    FILE *f;

    if ((f = fopen("Files\\Devoluciones.txt", "w+")) == NULL) {

        printf("Error al abrir el archivo");

    } else {

        for ( i=0 ; i<*n_dev ; i++ ){

            strcpy(line, d[i].id_pedido);
            strcat(line, "-");
            strcat(line, d[i].id_prod);
            strcat(line, "-");
            strcat(line, d[i].fecha_dev);
            strcat(line, "-");
            strcat(line, d[i].motivo);

            switch (d[i].est_dev) {

                case enviado:

                    strcat(line, "-");
                    strcat(line, "enviado");
                    break;
                case pediente:

                    strcat(line, "-");
                    strcat(line, "pendiente");
                    strcat(line, "-");
                    strcat(line,d[i].fecha_cad);
                    break;
                case aceptado:

                    strcat(line, "-");
                    strcat(line, "aceptado");
                    strcat(line, "-");
                    strcat(line,d[i].fecha_acp);
                    break;
                case denegado:

                    strcat(line, "-");
                    strcat(line, "denegado");
                    break;
                case recibido:

                    strcat(line, "-");
                    strcat(line, "recibido");
                    break;
                default:
                    printf("Error con el estado de la devolucion ( volcado )");
                    break;
            }



            if(i < *n_dev - 1) {
                strcat(line, "\n");
            }

            fprintf(f, "%s", line);


        }



    }


    fclose(f);

}


void eliminar_devolucion ( Devoluciones *dev , int indice_dev){

    char borrado[8]="#######";

    strcpy( dev[indice_dev].id_pedido , borrado );

    printf("\nEl pedido se elimino correctamente.\n");
    system("pause");


}


void crear_devolucion( Pedido *ped, ProductoPedido *prod_ped, Devoluciones **dev, int *n_dev, int *n_pedidos, int *n_prod_ped ){

    int i,j,k;
    char borrado[8]="#######";

    i=0;

    while ( i<*n_dev  && strcmp( (*dev)[i].id_pedido , borrado) != 0 ){

        i++;
    }


    if ( i >= *n_dev ){

        *dev = ( Devoluciones *)realloc(*dev, (*n_dev+1) * sizeof(Devoluciones));

        do{

            printf("Id_pedido: ");
            fflush(stdin);
            gets((*dev)[*n_dev].id_pedido);

            k=0;

            while ( k<*n_pedidos && strcmp(ped[k].id_pedido,(*dev)[*n_dev].id_pedido)!=0) k++;

            if ( k >= *n_pedidos ){

                printf("Escribe una id valida.\n");

            }

        }while( k >= *n_pedidos);


        do{

            printf("Id_prod: ");
            fflush(stdin);
            gets((*dev)[*n_dev].id_prod);

            j=0;

            while ( j<*n_prod_ped && strcmp((*dev)[*n_dev].id_prod,prod_ped[j].id_prod)!=0) j++;

            if ( j >= *n_prod_ped ){

                printf("Escribe una id valida.\n");

            }

        }while( j >= *n_prod_ped);

        fecha_actual((*dev)[*n_dev].fecha_dev);

        printf("Motivo: ");
        fflush(stdin);
        gets((*dev)[*n_dev].motivo);

        (*dev)[*n_dev].est_dev = pediente;

        printf("Fecha_cad: ");
        fflush(stdin);
        gets((*dev)[*n_dev].fecha_cad);

        (*n_dev)++;



    }else{

        if ( i == 0){

            strcpy( (*dev)[i].id_pedido , "0000001");

        }else{

            do{

                printf("Id_pedido: ");
                fflush(stdin);
                gets((*dev)[i].id_pedido);

                k=0;

                while ( k<*n_pedidos && strcmp(ped[k].id_pedido,(*dev)[i].id_pedido)!=0) k++;

                if ( k >= *n_pedidos ){

                    printf("Escribe una id valida.\n");

                }

            }while( k >= *n_pedidos);


            do{

                printf("Id_prod: ");
                fflush(stdin);
                gets((*dev)[i].id_prod);

                j=0;

                while ( j<*n_prod_ped && strcmp((*dev)[i].id_pedido,prod_ped[j].id_pedido)!=0) j++;

                if ( j >= *n_prod_ped ){

                    printf("Escribe una id valida.\n");

                }

            }while( j >= *n_prod_ped);

            fecha_actual((*dev)[i].fecha_dev);

            printf("Motivo: ");
            fflush(stdin);
            gets((*dev)[i].motivo);

            (*dev)[i].est_dev = pediente;

            printf("Fecha_cad: ");
            fflush(stdin);
            gets((*dev)[*n_dev].fecha_cad);

        }



    }




}



void menu_devoluciones_clientes ( Pedido *ped, ProductoPedido *prod_ped, Devoluciones *dev, int *n_dev, int *n_pedidos, int *n_prod_ped, char id_cliente[7], usu tipo_u){


}


void menu_devoluciones_admin ( Pedido *ped, ProductoPedido *prod_ped, Devoluciones *dev, int *n_dev, int *n_pedidos, int *n_prod_ped, usu tipo_u) {

    int i, op_dev,op;
    char c = 'a';

    printf("-------------------- Todas las devoluciones --------------------\n\n");

    for (i = 0; i < *n_dev; i++) {

        if (strcmp(dev[i].id_pedido,"#######")!=0){

            printf("[%c].%s-%s-%s-", c, dev[i].id_pedido, dev[i].id_prod, dev[i].fecha_dev);

            switch (dev[i].est_dev) {

                case pediente:
                    printf("pendiente-%s\n", dev[i].fecha_cad);
                    break;
                case aceptado:
                    printf("aceptado-%s\n", dev[i].fecha_acp);
                    break;
                case denegado:
                    printf("pendiente\n");
                    break;
                case enviado:
                    printf("enviado\n");
                    break;
                case recibido:
                    printf("recibido\n");
                    break;
                default:
                    printf("Error con el estado de la devolucion.\n");
                    system("pause");
                    exit(1);

        }


        }


        c++;

    }


    do {

        printf("\nElija una opcion:\n");
        printf("1.alta\n2.baja\n3.modificar\n4.ver productos asociados\n5.salir\n");
        scanf("%i", &op_dev);


        switch (op_dev) {
            case 1:

                crear_devolucion( ped,prod_ped,&dev,n_dev,n_pedidos,n_prod_ped);

                system("cls");
                menu_devoluciones(ped,prod_ped,dev,n_dev,n_pedidos,n_prod_ped,admin);

                break;
            case 2:

                printf("Que devolucion quiere borrar?: ");
                scanf("%i",&op);
                eliminar_devolucion(dev,op-1);

                system("cls");
                menu_devoluciones(ped,prod_ped,dev,n_dev,n_pedidos,n_prod_ped,admin);

                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                volcado_devoluciones(dev,n_dev);
                exit(1);
            default:
                break;

        }


    } while (op_dev != 1 && op_dev != 2 && op_dev != 3 && op_dev != 4 && op_dev != 5);


}



void menu_devoluciones_transportistas ( Pedido *ped, ProductoPedido *prod_ped, Devoluciones *dev, int *n_dev, int *n_pedidos, int *n_prod_ped,char id_transp[5], usu tipo_u){


}


void menu_devoluciones ( Pedido *ped, ProductoPedido *prod_ped, Devoluciones *dev, int *n_dev, int *n_pedidos, int *n_prod_ped, usu tipo_usu ){

    char id_cliente[8]="0000004";

    switch (tipo_usu) {


        case cliente:

            menu_devoluciones_clientes(ped, prod_ped,dev, n_dev, n_pedidos,n_prod_ped, id_cliente,cliente);

            break;
        case admin:

            menu_devoluciones_admin(ped, prod_ped,dev ,n_dev, n_pedidos,n_prod_ped,admin);

            break;
        case transportista:

            menu_devoluciones_transportistas(ped, prod_ped,dev, n_dev,n_pedidos,n_prod_ped,"0002",transportista);

            break;
        default:

            printf("Error con el tipo de ususario");
            exit(1);

    }


}





