#include "Pedidos.h"
#include <stdio.h>
#include "estado.h"
#include <stdlib.h>
#include <string.h>

#define LINEA 100

void carga_pedidos( Pedido **ped ,int *n_ped){     // FUNCIONA

    int i;
    char line[LINEA]="0";
    char contador_lineas[LINEA]="0";

    FILE *f;

    if ((f = fopen("Files\\Pedidos.txt", "r")) == NULL) {

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

            strcpy((*ped)[i].id_pedido, strtok(line, "-\n"));
            strcpy((*ped)[i].fecha_ped, strtok(NULL, "-\n"));
            strcpy((*ped)[i].id_cliente, strtok(NULL, "-\n"));
            strcpy((*ped)[i].lugar_entrega, strtok(NULL, "-\n"));

            if (strcmp( (*ped)[i].lugar_entrega, "domicilio") == 0 ){

                strcpy((*ped)[i].id_cod_prom, strtok(NULL, "-\n"));

            }else{

                strcpy((*ped)[i].id_locker, strtok(NULL, "-\n"));

            }



        }

        rewind(f);
        fclose(f);

    }

}


void carga_prod_pedido( ProductoPedido **pr_ped ,int *n_pr_ped){     // FUNCIONA

    int i,j;
    char line[LINEA]="0";
    char contador_lineas[LINEA]="0";
    char unidades[2],estado[18]="\0";
    char *ptr;

    FILE *f;

    if ((f = fopen("Files\\ProductosPedidos.txt", "r")) == NULL) {

        printf("Error al abrir el archivo");

    } else {

        while(!feof(f)){

            fgets(contador_lineas,LINEA,f);
            (*n_pr_ped)++;

        }


        *pr_ped = (ProductoPedido *)calloc(*n_pr_ped, sizeof(ProductoPedido));
        if (*pr_ped == NULL) {
            printf("Error al crear la memoria para los lockers.\n");
            exit(1);
        }

        rewind(f);

        for ( i=0 ; i< *n_pr_ped; i++ ) {

            fgets(line,LINEA,f);

            strcpy((*pr_ped)[i].id_pedido, strtok(line, "-\n"));
            strcpy((*pr_ped)[i].id_prod, strtok(NULL, "-\n"));
            (*pr_ped)[i].unidades = strtol(strtok(NULL, "-\n"),&ptr,10);
            strcpy((*pr_ped)[i].fecha_entrega, strtok(NULL, "-\n"));
            (*pr_ped)[i].importe = strtol(strtok(NULL, "-\n"),&ptr,10);
            strcpy(estado, strtok(NULL, "-\n"));

            if ( strcmp(estado,"enPreparacion") == 0 ){

                (*pr_ped)[i].est_pedido = enPreparacion;

            }else if ( strcmp(estado,"entregado") == 0  ){

                (*pr_ped)[i].est_pedido = entregado;

                strcpy((*pr_ped)[i].id_transp, strtok(NULL, "-\n"));
                strcpy((*pr_ped)[i].fecha_entr_dev, strtok(NULL, "-\n"));


            }else if ( strcmp(estado,"devuelto") == 0 ){

                (*pr_ped)[i].est_pedido = devuelto;

                strcpy((*pr_ped)[i].id_transp, strtok(NULL, "-\n"));
                strcpy((*pr_ped)[i].fecha_entr_dev, strtok(NULL, "-\n"));

            }else if ( strcmp(estado,"enReparto") == 0 ){

                (*pr_ped)[i].est_pedido = enReparto;

                strcpy((*pr_ped)[i].id_transp, strtok(NULL, "-\n"));

            }else if ( strcmp(estado,"transportista") == 0 ){

                (*pr_ped)[i].est_pedido = trasnportista;

                strcpy((*pr_ped)[i].id_transp, strtok(NULL, "-\n"));

            }else if ( strcmp(estado,"enviado") == 0 ){

                (*pr_ped)[i].est_pedido = enviado;

            }else if ( strcmp(estado,"enLocker") == 0 ){

                (*pr_ped)[i].est_pedido = enLocker;


                strcpy((*pr_ped)[i].id_transp, strtok(NULL, "-\n"));
                strcpy((*pr_ped)[i].id_locker, strtok(NULL, "-\n"));
                strcpy((*pr_ped)[i].cod_locker, strtok(NULL, "-\n"));
                strcpy((*pr_ped)[i].fecha_entr_dev, strtok(NULL, "-\n"));

            }else{

                printf("Error al ver el estado del pedido");

            }


            for ( j=0 ; j<18 ; j++ ){

                estado[j] = '\0';

            }



        }

        rewind(f);
        fclose(f);

    }

}



void volcado_pedidos ( Pedido *p, int *n_ped ){

    int i,j;
    char line[LINEA]="\0";
    FILE *f;

    if ((f = fopen("Files\\Pedidos.txt", "w+")) == NULL) {

        printf("Error al abrir el archivo");

    } else {

        for ( i=0 ; i<*n_ped ; i++ ){

            strcpy(line, p[i].id_pedido);
            strcat(line, "-");
            strcat(line, p[i].fecha_ped);
            strcat(line, "-");
            strcat(line, p[i].id_cliente);
            strcat(line, "-");
            strcat(line, p[i].lugar_entrega);

            if (strcmp( p[i].lugar_entrega, "domicilio") == 0 ){

                if ( strcmp( p[i].id_cod_prom,"\0\0\0\0\0\0\0\0\0\0") != 0 ){

                    strcat(line, "-");
                    strcat(line, p[i].id_cod_prom);

                }


            }else if ( strcmp( p[i].lugar_entrega, "locker") == 0 ){

                strcat(line, "-");
                strcat(line, p[i].id_locker);

            }else printf("Error en el estado del pedido ( volcado )");


            if(i < *n_ped - 1) {
                strcat(line, "\n");
            }

            fprintf(f, "%s", line);

            for ( j=0 ; j<LINEA ; j++ ) line[j]='\0';

        }



    }


    fclose(f);

}




void volcado_prod_pedidos ( ProductoPedido *pr_p, int *n_pr_ped ){

    int i;
    char line[LINEA]="\0",unidades[6]="\0",importe[6]="\0";
    FILE *f;

    if ((f = fopen("Files\\ProductosPedidos.txt", "w+")) == NULL) {

        printf("Error al abrir el archivo");

    } else {

        for ( i=0 ; i<*n_pr_ped ; i++ ){

            strcpy(line, pr_p[i].id_pedido);
            strcat(line, "-");
            strcat(line, pr_p[i].id_prod);
            strcat(line, "-");

            sprintf(unidades,"%i",pr_p[i].unidades);
            strcat(line, unidades);

            strcat(line, "-");
            strcat(line, pr_p[i].fecha_entrega);
            strcat(line, "-");

            sprintf(importe,"%i",pr_p[i].importe);
            strcat(line, importe);
            strcat(line, "-");

            switch (pr_p[i].est_pedido) {

                case enPreparacion:

                    strcat(line, "enPreparacion");
                    break;
                case enviado:

                    strcat(line, "enviado");
                    break;
                case enReparto:

                    strcat(line, "enReparto");
                    strcat(line, "-");
                    strcat(line, pr_p[i].id_transp);
                    break;
                case enLocker:

                    strcat(line, "enLocker");
                    strcat(line, "-");
                    strcat(line, pr_p[i].id_transp);
                    strcat(line, "-");
                    strcat(line, pr_p[i].id_locker);
                    strcat(line, "-");
                    strcat(line, pr_p[i].cod_locker);
                    strcat(line, "-");
                    strcat(line, pr_p[i].fecha_entr_dev);
                    break;
                case entregado:

                    strcat(line, "entregado");
                    strcat(line, "-");
                    strcat(line, pr_p[i].id_transp);
                    strcat(line, "-");
                    strcat(line, pr_p[i].fecha_entr_dev);
                    break;
                case devuelto:

                    strcat(line, "devuelto");
                    strcat(line, "-");
                    strcat(line, pr_p[i].id_transp);
                    strcat(line, "-");
                    strcat(line, pr_p[i].fecha_entr_dev);
                    break;
                case trasnportista:

                    strcat(line, "transportista");
                    strcat(line, "-");
                    strcat(line, pr_p[i].id_transp);
                    break;
                default:
                    printf("Error con el tipo de prod_pedido ( volcado )");
                    break;
            }

            if(i < *n_pr_ped - 1) {
                strcat(line, "\n");
            }

            fprintf(f, "%s", line);


        }



    }


    fclose(f);

}

void eliminar_pedido ( Pedido *ped, int indice_ped, int *n_ped ){

    int i;
    char borrado[8]="#######";

    strcpy( ped[indice_ped].id_pedido , borrado );


}


void crear_pedido ( Pedido **ped, int *n_ped , char usu_act[8]){

    int i=0,j,n;
    char borrado[8]="#######",prueba_id_ped[8]="\0",prueba_fecha[11]="\0",prueba_id_cliente[8]="\0",prueba_lugar[10]="\0",prueba_id_lock[11]="\0",prueba_id_cod_prom[11]="\0";
    char *aux,*nulo;
    int id_pedido,cifras=0;

    while ( i<*n_ped  && strcmp( (*ped)[i].id_pedido , borrado) != 0 ){

        i++;
    }

    aux = (char *)calloc(cifras+1,sizeof(char));
    nulo = (char *)calloc(8-cifras,sizeof(char));

    id_pedido = i+1;
    n= id_pedido;

    while ( n % 10 > 1){

        n = n / 10;
        cifras++;
    }

    for ( j=0 ; j<7-cifras ; j++ ){

        nulo[j]='0';

    }


    if ( i >= *n_ped ){

        *ped = ( Pedido *)realloc(NULL, (*n_ped+1) * sizeof(Pedido));

        for ( j=0 ; j<10 ; j++ ) (*ped)[*n_ped].lugar_entrega[j] = '\0';


        sprintf(aux,"%i",*n_ped+1);

        strcat(nulo,aux);

        strcpy((*ped)[*n_ped].id_pedido,nulo);

        system("cls");

        fflush(stdin);
        printf("Fecha_pedido: ");
        gets((*ped)[*n_ped].fecha_ped);

        strcpy( (*ped)[*n_ped].id_cliente , usu_act);
        fflush(stdin);
        printf("Lugar_entrega: ");
        gets((*ped)[*n_ped].lugar_entrega);
        fflush(stdin);

        if (strcmp((*ped)[*n_ped].lugar_entrega,"domicilio") == 0){

            printf("Id_cod_prom: ");
            gets((*ped)[*n_ped].id_cod_prom);

        }else if ( strcmp((*ped)[*n_ped].lugar_entrega,"locker") == 0 ){

            printf("Id_locker: ");
            gets((*ped)[*n_ped].id_locker);

        }else{

            printf("Error con el lugar de entrega de pedido en alta");
            exit(1);

        }

        strcpy(prueba_id_ped,(*ped)[*n_ped].id_pedido);
        strcpy(prueba_fecha,(*ped)[*n_ped].fecha_ped);
        strcpy(prueba_id_cliente,(*ped)[*n_ped].id_cliente);
        strcpy(prueba_lugar,(*ped)[*n_ped].lugar_entrega);
        strcpy(prueba_id_lock,(*ped)[*n_ped].id_locker);
        strcpy(prueba_id_cod_prom,(*ped)[*n_ped].id_cod_prom);

        (*n_ped)++;





    }else{

        if ( i == 0){

            strcpy( (*ped)[i].id_pedido , "0000001");

        }else{

            sprintf(aux,"%i",id_pedido);

            strcat(nulo,aux);


            strcpy( (*ped)[i].id_pedido,nulo);

            system("cls");

            printf("Fecha_pedido: ");
            gets((*ped)[i].fecha_ped);
            printf("Id_cliente: ");
            gets((*ped)[i].id_cliente);
            printf("Lugar_entrega: ");
            gets((*ped)[i].lugar_entrega);

            if (strcmp((*ped)[i].lugar_entrega,"domicilio") == 0){

                printf("Id_cod_prom: ");
                gets((*ped)[i].id_cod_prom);

            }else if ( strcmp((*ped)[i].lugar_entrega,"locker") == 0 ){

                printf("Id_locker: ");
                gets((*ped)[i].id_locker);

            }else{

                printf("Error con el lugar de entrega de pedido en alta");
                exit(1);

            }

        }



    }


}


void modificar_pedido ( Pedido *ped , int *n_ped , int indice ){


    printf("Fecha_pedido: ");
    scanf("%s",ped[indice].fecha_ped);
    printf("Id_cliente: ");
    scanf("%s",ped[indice].id_cliente);
    printf("Lugar_entrega: ");
    scanf("%s",ped[indice].lugar_entrega);

    if (strcmp(ped[indice].lugar_entrega,"domicilio") == 0){

        printf("Id_cod_prom: ");
        scanf("%s",ped[indice].id_cod_prom);

    }else if ( strcmp(ped[indice].lugar_entrega,"locker") == 0 ){

        printf("Id_locker: ");
        scanf("%s",ped[indice].id_locker);

    }else{

        printf("Error con el lugar de entrega de pedido en modificar");
        exit(1);

    }



}


void menu_prod_ped ( ProductoPedido *pr_p , int *n_pr_ped , char id_ped[8] , usu est){

    int i,cont=1,ind_prod_ped;
    char c;

    system("cls");

    printf("---------------- Productos asociados al pedido ----------------\n\n");

    for ( i=0 ; i< *n_pr_ped ; i++ ){

        if (strcmp( pr_p[i].id_pedido,id_ped)==0){

            printf("[%i].%s-%i\n",cont,pr_p[i].id_prod,pr_p[i].unidades);
            cont++;

        }

    }

    printf("Escriba el id del producto que desee ver: ");
    scanf("%i",&ind_prod_ped);

    ind_prod_ped--;

    system("cls");

    printf("------------------------- Producto %i --------------------------\n\n",ind_prod_ped);

    printf("Id_Ped: %s\nId_Prod: %s\nUnidades: %i\nFecha_prevista_entrega: %s\nImporte: %i\n",pr_p[ind_prod_ped].id_pedido,
                                                          pr_p[ind_prod_ped].id_prod,
                                                          pr_p[ind_prod_ped].unidades,
                                                          pr_p[ind_prod_ped].fecha_entrega,
                                                          pr_p[ind_prod_ped].importe);

    printf("Estado: ");
    switch (pr_p[ind_prod_ped].est_pedido) {

        case enPreparacion:

            printf("en Preparacion\n");

            break;
        case enviado:

            printf("enviado\n");

            break;
        case enReparto:

            printf("enReparto\n");
            printf("Id_transportista: %s\n",pr_p[i].id_transp);

            break;
        case enLocker:

            printf("enLocker\n");
            printf("Id_transportista: %s\n",pr_p[i].id_transp);
            printf("Id_locker: %s",pr_p[i].id_locker);
            printf("Cod_locker: %s",pr_p[i].cod_locker);
            printf("Fecha de entrega: %s\n",pr_p[i].fecha_entr_dev);

            break;
        case entregado:

            printf("entregado\n");
            printf("Id_transportista: %s\n",pr_p[i].id_transp);
            printf("Fecha de entrega: %s\n",pr_p[i].fecha_entr_dev);

            break;
        case devuelto:

            printf("devuelto\n");
            printf("Id_transportista: %s\n",pr_p[i].id_transp);
            printf("Fecha de entrega: %s\n",pr_p[i].fecha_entr_dev);

            break;
        case trasnportista:

            printf("transportista\n");
            printf("Id_transportista: %s\n",pr_p[i].id_transp);

            break;
        default:
            printf("Error con el estado del prod_ped ( menu prod ped )");
            exit(1);

    }


    if ( est == admin ){

        do{

            printf("\n Quiere modificar este producto? (s/n): ");
            scanf("%c",&c);

            system("cls");

            if ( c == 's' || c == 'S'){

                printf("Unidades: ");


            }else if ( c == 'n' || c == 'N'){



            }else printf("Escribe s o n");


        } while ( c != 's' && c != 'S' && c != 'n' && c != 'N');



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


void menu_pedidos_admin( Pedido *ped ,ProductoPedido *prod_ped,  int *n_pedidos , int *n_pr_ped) {

    int i, tipo_ped;
    char c = 'a', resp, nulo[11] = "\0",resp_2;
    int op_ped,flag_existe=0,op_accion_pedido;

    do {

        printf("Desea listar los pedidos segun su estado? (s/n):");
        fflush(stdin);
        scanf("%c", &resp);

        system("cls");

        if (resp == 's' || resp == 'S') {

            printf("1.domicilio\n2.locker\n");
            printf("Elija el tipo de pedido (1-2):");
            scanf("%i", &tipo_ped);

            switch (tipo_ped) {

                case 1:

                    printf("--------- Pedidos a domicilio ---------\n\n");

                    i = 0;

                    while (i < *n_pedidos) {

                        if ((strcmp(ped[i].lugar_entrega, "domicilio") == 0 ) && strcmp(ped[i].id_pedido, "#######") != 0) {

                            flag_existe = 1;

                            printf("[%c].%s-%s-%s-%s-%s\n", c,
                                   ped[i].id_pedido,
                                   ped[i].fecha_ped,
                                   ped[i].id_cliente,
                                   ped[i].lugar_entrega,
                                   ped[i].id_cod_prom);

                            c++;
                        }

                        i++;
                    }

                    if (flag_existe == 0) {

                        printf("No hay pedidos a domicilio\n");
                        exit(1);
                    }

                    break;
                case 2:

                    printf("--------- Pedidos a locker ---------\n\n");

                    i=0;

                    while (i < *n_pedidos) {

                        if ((strcmp(ped[i].lugar_entrega, "locker") == 0 ) && strcmp(ped[i].id_pedido, "#######") != 0) {

                            flag_existe = 1;

                            printf("[%c].%s-%s-%s-%s-%s\n", c,
                                       ped[i].id_pedido,
                                       ped[i].fecha_ped,
                                       ped[i].id_cliente,
                                       ped[i].lugar_entrega,
                                       ped[i].id_locker);

                            c++;
                        }

                        i++;

                    }

                    if (flag_existe == 0) {

                        printf("No hay pedidos a locker\n");
                        exit(1);
                    }

                    break;

                default:
                    printf("Error en el tipo de pedido");
                    exit(1);

            }

        }else if (resp == 'n' || resp == 'N') {

            system("cls");

            printf("--------- Todos los pedidos ---------\n\n");

            for (i = 0; i < *n_pedidos; i++) {

                if ( strcmp(ped[i].id_pedido, "#######") != 0 ){

                    if (strcmp(ped[i].lugar_entrega, "domicilio") == 0) {

                        printf("[%c].%s-%s-%s-%s-%s\n", c,
                               ped[i].id_pedido,
                               ped[i].fecha_ped,
                               ped[i].id_cliente,
                               ped[i].lugar_entrega,
                               ped[i].id_cod_prom);

                    } else if (strcmp(ped[i].lugar_entrega, "locker") == 0) {

                        printf("[%c].%s-%s-%s-%s-%s\n", c,
                               ped[i].id_pedido,
                               ped[i].fecha_ped,
                               ped[i].id_cliente,
                               ped[i].lugar_entrega,
                               ped[i].id_locker);

                    } else {

                        printf("Error con el lugar de entrega pedido");
                        exit(1);

                    }

                    c++;

                }

            }


        } else printf("Introduce s o n\n");

    }while (resp != 's' && resp != 'S' && resp != 'n' && resp != 'N');


        do{

            printf("\nElija una opcion:\n");
            printf("1.alta\n2.baja\n3.modificar\n4.ver productos asociados \n");
            scanf("%i", &op_ped);

            switch (op_ped) {

                case 1:

                    crear_pedido(&ped,n_pedidos,"0000004");

                    break;
                case 2:

                    do{

                        printf("----------------------------\n\n");
                        printf("Escribe el id de pedido que quiera borrar: ");
                        scanf("%i",&op_accion_pedido);

                        eliminar_pedido( ped,op_accion_pedido-1,n_pedidos);

                        printf("Quiere eliminar mas pedidos? (s/n): ");
                        fflush(stdin);
                        scanf("%c",&resp_2);


                    }while ( resp_2 != 'n' && resp_2 != 'N');

                    break;
                case 3:

                    printf("----------------------------\n\n");
                    printf("Escribe el id de pedido que quiera modificar: ");
                    scanf("%i",&op_accion_pedido);

                    modificar_pedido( ped , n_pedidos ,op_accion_pedido - 1 );

                    break;
                case 4:

                    printf("Escribe el id del pedido que quiera ver: ");
                    scanf("%i",&op_accion_pedido);

                    menu_prod_ped(  prod_ped, n_pr_ped ,ped[op_accion_pedido-1].id_pedido , admin);

                    break;
                default:
                    break;

            }

        }while ( op_ped != 1 && op_ped != 2 && op_ped != 3 && op_ped != 4 );



    }




    void menu_pedidos_prov(Pedido *ped, ProductoPedido *prod_ped, int *n_pedidos) {


    }

    void menu_pedidos_transp(Pedido *ped, ProductoPedido *prod_ped, int *n_pedidos) {


    }


    void menu_pedidos(Pedido *ped, ProductoPedido *prod_ped, int *n_pedidos, int *n_prod_ped, usu tipo_usu) {

        int i;
        char id_cliente[7];

        switch (tipo_usu) {


            case cliente:

                menu_pedidos_clientes(ped, prod_ped, n_pedidos, n_prod_ped, id_cliente);

                break;
            case admin:

                menu_pedidos_admin(ped, prod_ped, n_pedidos, n_prod_ped);

                break;
            case proveedor:

                menu_pedidos_prov(ped, prod_ped, n_pedidos);

                break;
            case transportista:

                menu_pedidos_transp(ped, prod_ped, n_pedidos);

                break;
            default:

                printf("Error con el tipo de ususario");
                exit(1);

        }

    }
