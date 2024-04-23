#include "Devoluciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define LINEA 150

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

        fecha_actual((*dev)[*n_dev].fecha_dev,0);

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

            fecha_actual((*dev)[i].fecha_dev,0);

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

void ver_devolucion (  Devoluciones *dev ,  int indice_dev ){

    char op;

    switch (dev[indice_dev].est_dev) {

        case pediente:


            do{

                printf("Acepta esta devolucion?(s/n): ");
                fflush(stdin);
                scanf("%c",&op);


                if ( op == 's' || op == 'S'){

                    dev[indice_dev].est_dev = aceptado;

                    fecha_actual(dev[indice_dev].fecha_acp,0);

                    printf("\nDevolucion aceptada.\n");
                    system("pause");
                    system("cls");

                }

                if ( op != 's' && op != 'S' && op != 'n' && op != 'N' ){

                    printf("\nEscribe s o n.\n");

                }


            } while ( op != 's' && op != 'S' && op != 'n' && op != 'N');


            break;
        case enviado:

            do{

                printf("Confirma  devolucion?(s/n): ");
                fflush(stdin);
                scanf("%c",&op);

                if ( op == 's' || op == 'S'){

                    dev[indice_dev].est_dev = recibido;

                    // stock ++

                    printf("\nEl recibo del paquete se ha confirmado exitosamente..\n");
                    system("pause");
                    system("cls");

                }

                if ( op != 's' && op != 'S' && op != 'n' && op != 'N' ){

                    printf("\nEscribe s o n.\n");

                }

            } while ( op != 's' && op != 'S' && op != 'n' && op != 'N' );


            break;
        default:
            break;
    }


}


void hacer_devolucion_cliente ( Devoluciones **dev , int *n_dev , char id_prod[8] , char id_ped[8]){

    int i;
    char borrado_8[8]="#######",borrado_51[51];

    i=0;

    while ( i<*n_dev  && strcmp( (*dev)[i].id_pedido , borrado_8) != 0 ){

        i++;
    }


    if ( i >= *n_dev ){

        *dev = ( Devoluciones *)realloc(*dev, (*n_dev+1) * sizeof(Devoluciones));

        strcpy((*dev)[*n_dev].id_pedido,id_ped);
        strcpy((*dev)[*n_dev].id_prod,id_prod);
        fecha_actual((*dev)[*n_dev].fecha_dev,0);

        printf("Motivo: ");
        fflush(stdin);
        gets((*dev)[*n_dev].motivo);

        (*dev)[*n_dev].est_dev = pediente;

        strcpy((*dev)[*n_dev].fecha_cad,"14/09/2024");  // Prueba

        (*n_dev)++;

    }else{

        strcpy((*dev)[*n_dev].motivo,borrado_51);

        strcpy((*dev)[i].id_pedido,id_ped);
        strcpy((*dev)[i].id_prod,id_prod);
        fecha_actual((*dev)[i].fecha_dev,0);

        printf("Motivo: ");
        fflush(stdin);
        gets((*dev)[i].motivo);

        (*dev)[i].est_dev = pediente;

        strcpy((*dev)[*n_dev].fecha_cad,"14/09/2024");  // Prueba
        
    }

}



void devolucion_cliente ( Devoluciones *dev, int *n_dev , int indice_dev ){

    char confirma;
    int i=0;

    do{

        printf("Confirma el envio del productopara su devolucion?(s/n): ");
        fflush(stdin);
        scanf("%c",&confirma);

        if( confirma == 's' || confirma == 'S'){

            dev[indice_dev].est_dev = enviado;

        }

    }while( confirma != 's' && confirma != 'S' && confirma != 'n' && confirma != 'N');

}



void modificar_devolucion (  Devoluciones *dev, int indice_dev){

    char estado[15]="\0",confirma;

    printf("Fecha_devolucion: ");
    fflush(stdin);
    gets(dev[indice_dev].fecha_dev);
    printf("Motivo: ");
    fflush(stdin);
    gets(dev[indice_dev].motivo);
    printf("Estado_dev: ");
    fflush(stdin);
    gets(estado);


    if (strcmp( estado , "pendiente")==0){

        dev[indice_dev].est_dev = pediente;

        printf("Fecha_cad: ");
        fflush(stdin);
        gets(dev[indice_dev].fecha_cad);

    }else if ( strcmp( estado , "aceptado")==0 ){

        dev[indice_dev].est_dev = aceptado;

        printf("Fecha_acp: ");
        fflush(stdin);
        gets(dev[indice_dev].fecha_acp);

    }else if ( strcmp( estado , "denegado")==0 ){

        dev[indice_dev].est_dev = denegado;

    }else if ( strcmp( estado , "enviado")==0 ){

        dev[indice_dev].est_dev = enviado;

    }else if ( strcmp(estado,"recibido") == 0) {

        dev[indice_dev].est_dev = recibido;

    }else{

        printf("Error al ver el estado de la devolucion (en modificar)");

    }



}



void menu_devoluciones_clientes ( Pedido *ped, ProductoPedido *prod_ped, Devoluciones *dev, int *n_dev, int *n_pedidos, int *n_prod_ped, char id_cliente[8], usu tipo_u){

    int i,j,existe,op,op_menu,cifras,n,indice_dev;
    char c='a',borrado[8]="#######",vector_id[8]="\0",*num;

    do{

        existe = 0;
        cifras = 0;

        printf("-------------------- Sus devoluciones --------------------\n\n");

        for (i = 0; i < *n_dev; i++) {

            if (strcmp(dev[i].id_pedido,borrado)!=0){

                j=0;

                while (  j<*n_pedidos && strcmp(dev[i].id_pedido,ped[j].id_pedido)!=0){

                    j++;
                }


                if ( j<*n_pedidos){

                    if (strcmp(ped[j].id_cliente,id_cliente) == 0){

                        if ( dev[i].est_dev == pediente || dev[i].est_dev == aceptado ){

                            existe=1;

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


                            c++;

                        }



                    }


                }


            }

        }

        if ( existe == 0 ){

            printf("\nNo tiene devoluciones asocidadas.\n");
            system("pause");

        }else{

            do{

                printf("----------------------------------------------------\n");

                printf("Elija una opcion.\n1.Ver devolucion\n2.Salir\n");
                scanf("%i",&op_menu);

                switch (op_menu) {
                    case 1:

                        do{


                            printf("Escribe el id del pedido para interactuar con el: ");
                            scanf("%i",&op);

                            n=op;

                            while ( n > 1){

                                n /= 10;
                                cifras++;

                            }

                            num = (char *) calloc(cifras+1,sizeof(char));

                            vector_id[0]= '0';

                            for (i=0 ; i<6-cifras; i++ ){

                                strcat(vector_id,"0");

                            }

                            sprintf(num,"%i",op);

                            strcat(vector_id,num);

                            indice_dev=0;

                            while( indice_dev<*n_dev && strcmp(vector_id,dev[indice_dev].id_pedido)!=0){

                                indice_dev++;
                            }

                            if ( indice_dev >= *n_dev){

                                printf("\nIntroduce una id correcta.");
                                system("pause");
                            }

                        }while( indice_dev >= *n_dev );

                        devolucion_cliente(dev,n_dev,indice_dev);

                        system("cls");

                        break;
                    case 2:
                        break;
                    default:
                        printf("Escribe un numero del 1 al 2");
                        break;
                }

            }while ( op_menu != 1 && op_menu != 2);

        }



    } while ( op_menu != 2 && existe == 1);


}






void menu_devoluciones_admin ( Pedido *ped, ProductoPedido *prod_ped, Devoluciones *dev, int *n_dev, int *n_pedidos, int *n_prod_ped, usu tipo_u) {

    int i, op_dev,op,tipo_dev,existe=0;
    char c = 'a',resp,borrado[8]="#######";

    do{

        do{

            printf("Desea listar las devoluciones segun su estado? (s/n):");
            fflush(stdin);
            scanf("%c", &resp);

            system("cls");


            if (resp == 's' || resp == 'S'){

                do{

                    printf("1.Pendiente\n2.Aceptado\n3.Denegado\n4.Enviado\n5.Recibido\n");
                    printf("Elija el tipo de devolucion (1-5):");
                    scanf("%i", &tipo_dev);

                    system("cls");

                    switch (tipo_dev) {

                        case 1:

                            printf("-------------------- Devoluciones pendientes --------------------\n\n");

                            for ( i=0 ; i<*n_dev ; i++ ){

                                if ( strcmp(dev[i].id_pedido,borrado)!=0 ){

                                    if ( dev[i].est_dev == pediente ){

                                        existe = 1;

                                        printf("[%c].%s-%s-%s-pendiente-%s\n", c, dev[i].id_pedido, dev[i].id_prod, dev[i].fecha_dev,dev[i].fecha_cad);

                                        c++;
                                    }

                                }

                            }

                            break;
                        case 2:

                            printf("-------------------- Devoluciones aceptadas --------------------\n\n");

                            for ( i=0 ; i<*n_dev ; i++ ){

                                if ( strcmp(dev[i].id_pedido,borrado)!=0 ){

                                    if ( dev[i].est_dev == aceptado ){

                                        existe = 1;

                                        printf("[%c].%s-%s-%s-aceptado-%s\n", c, dev[i].id_pedido, dev[i].id_prod, dev[i].fecha_dev,dev[i].fecha_acp);

                                        c++;
                                    }

                                }


                            }

                            break;
                        case 3:

                            printf("-------------------- Devoluciones denegadas --------------------\n\n");

                            for ( i=0 ; i<*n_dev ; i++ ){

                                if ( strcmp(dev[i].id_pedido,borrado)!=0 ){

                                    if ( dev[i].est_dev == denegado ){

                                        existe = 1;

                                        printf("[%c].%s-%s-%s-denegado\n", c, dev[i].id_pedido, dev[i].id_prod, dev[i].fecha_dev);

                                        c++;
                                    }

                                }



                            }

                            break;
                        case 4:

                            printf("-------------------- Devoluciones enviadas --------------------\n\n");

                            for ( i=0 ; i<*n_dev ; i++ ){

                                if ( strcmp(dev[i].id_pedido,borrado)!=0 ){

                                    if ( dev[i].est_dev == enviado ){

                                        existe = 1;

                                        printf("[%c].%s-%s-%s-enviado\n", c, dev[i].id_pedido, dev[i].id_prod, dev[i].fecha_dev);

                                        c++;
                                    }

                                }


                            }

                            break;
                        case 5:

                            printf("-------------------- Devoluciones recibidas --------------------\n\n");

                            for ( i=0 ; i<*n_dev ; i++ ){

                                if ( strcmp(dev[i].id_pedido,borrado)!=0 ){

                                    if ( dev[i].est_dev == recibido ){

                                        existe = 1;

                                        printf("[%c].%s-%s-%s-recibido\n", c, dev[i].id_pedido, dev[i].id_prod, dev[i].fecha_dev);

                                        c++;
                                    }

                                }


                            }

                            break;
                        default:

                            system("cls");
                            printf("Escribe un numero del (1-5)\n");
                            system("pause");
                            system("cls");

                            break;
                    }


                }while( tipo_dev < 1 || tipo_dev > 5);


            }else if ( resp == 'n' || resp == 'N'){

                printf("-------------------- Todas las devoluciones --------------------\n\n");

                for (i = 0; i < *n_dev; i++) {

                    if (strcmp(dev[i].id_pedido,borrado)!=0){

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


                        c++;

                    }



                }

            }else{

                system("cls");
                printf("Introduce s o n\n");
                system("pause");

            }



        } while (resp != 's' && resp != 'S' && resp != 'n' && resp != 'N');





        do {

            printf("\nElija una opcion:\n");
            printf("1.alta\n2.baja\n3.modificar\n4.ver devolucion\n5.salir\n");
            scanf("%i", &op_dev);


            switch (op_dev) {
                case 1:

                    crear_devolucion( ped,prod_ped,&dev,n_dev,n_pedidos,n_prod_ped);

                    system("cls");

                    break;
                case 2:

                    printf("Que devolucion quiere borrar?: ");
                    scanf("%i",&op);
                    eliminar_devolucion(dev,op-1);

                    system("cls");

                    break;
                case 3:

                    printf("Que devolucion quiere modificar?: ");
                    scanf("%i",&op);
                    modificar_devolucion(dev,op-1);
                    system("cls");


                    break;
                case 4:

                    printf("Introduce el indice del pedido que quiera ver: ");
                    scanf("%i",&op);

                    ver_devolucion(dev,op-1);

                    system("cls");

                    break;
                case 5:
                default:
                    printf("Escribe un numero del 1 al 5.");
                    break;

            }


        } while (op_dev < 1 || op_dev > 5);


    }while( op_dev != 5);


}



void menu_devoluciones_transportistas ( Pedido *ped, ProductoPedido *prod_ped, Devoluciones *dev, int *n_dev, int *n_pedidos, int *n_prod_ped,char id_transp[5], usu tipo_u){



    

}


