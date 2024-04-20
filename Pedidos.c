#include "Pedidos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LINEA 150

void fecha_actual( char fecha_act[11] , int mes){

    fecha fecha_actual;
    time_t t = time(NULL);
    struct tm tiempo_actual = *localtime(&t);
    char dd[4]="\0",mm[4]="\0",aa[5]="\0";
    char fecha[11]="\0";

    // Pasamos los datos desde la estructura tm a fecha
    fecha_actual.dia = tiempo_actual.tm_mday;
    fecha_actual.mes = tiempo_actual.tm_mon + 1 + mes;
    fecha_actual.anno = tiempo_actual.tm_year + 1900;

    sprintf(dd,"%i",fecha_actual.dia);
    sprintf(mm,"%i",fecha_actual.mes);
    sprintf(aa,"%i",fecha_actual.anno);


    if ( fecha_actual.dia < 10 ){

        strcpy(fecha,"0");
        strcat(fecha,dd);
        strcat(fecha,"/");

    }else{

        strcpy(fecha,dd);
        strcat(fecha,"/");

    }

    if ( fecha_actual.mes < 10 ){

        strcat(fecha,"0");
        strcat(fecha,mm);
        strcat(fecha,"/");

    }else{

        strcat(fecha,mm);
        strcat(fecha,"/");

    }

    strcat(fecha,aa);
    strcpy(fecha_act,fecha);

}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
                strcpy((*ped)[i].id_cod_prom, strtok(NULL, "-\n"));

            }



        }

        rewind(f);
        fclose(f);

    }

}


void carga_prod_pedido( Pedido *ped,ProductoPedido **pr_ped ,int *n_ped ,int *n_pr_ped){     // FUNCIONA

    int i,j,k;
    char line[LINEA]="0";
    char contador_lineas[LINEA]="0";
    char estado[18]="\0";
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
                strcat(line, "-");
                strcat(line, p[i].id_cod_prom);

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




void volcado_prod_pedidos ( Pedido *ped,ProductoPedido *pr_p ,int *n_ped ,int *n_pr_ped ){

    int i,j;
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

void eliminar_pedido ( Pedido *ped, int indice_ped){

    char borrado[8]="#######";

    strcpy( ped[indice_ped].id_pedido , borrado );


}


void crear_siguiente_id ( int num_digitos, char vect_dest[num_digitos+1] , char vect_id[num_digitos+1]){

    int j,cifras=0,n,n_aux;
    char *aux,*nulo,*ptr;

    n= strtol(vect_id,&ptr,10);
    n++;
    n_aux = n;

    while ( n >= 1 ){

        n /= 10;
        cifras++;
    }

    aux = (char *)calloc(cifras+1,sizeof(char));
    nulo = (char *)calloc(num_digitos-cifras,sizeof(char));

    sprintf(aux,"%i",n_aux);

    for ( j=0 ; j<num_digitos-cifras ; j++ ){

        nulo[j]='0';

    }

    strcat(nulo,aux);
    strcpy(vect_dest,nulo);

}


void hacer_pedido (Pedido **ped, ProductoPedido **pr_ped, int *n_ped ,int *n_pr_ped, int unidades , int importe ,char id_prod[8],char id_cliente[8] ){

    *ped = ( Pedido *)realloc(*ped, (*n_ped+1) * sizeof(Pedido));

    crear_siguiente_id(7,(*ped)[*n_ped].id_pedido,(*ped)[*n_ped-1].id_pedido);

    fecha_actual((*ped)[*n_ped].fecha_ped,0);
    strcpy((*ped)[*n_ped].id_cliente,id_cliente);


    printf("Como quiere el pedido? ( domicilio o locker ): ");
    fflush(stdin);
    gets((*ped)[*n_ped].lugar_entrega);

    if (strcmp((*ped)[*n_ped].lugar_entrega,"domicilio")==0){

        printf("Cod_prom: ");
        fflush(stdin);
        gets((*ped)[*n_ped].id_cod_prom);

    }else if ( strcmp((*ped)[*n_ped].lugar_entrega,"locker")==0 ){

        printf("Id_Lock: ");
        fflush(stdin);
        gets((*ped)[*n_ped].id_locker);


    }else printf("Error en el lugar de entrega (añadir pedido)");



    *pr_ped = ( ProductoPedido *)realloc(*pr_ped, (*n_pr_ped+1) * sizeof(ProductoPedido));

    strcpy( (*pr_ped)[*n_pr_ped].id_prod,id_prod);

    strcpy( (*pr_ped)[*n_pr_ped].id_pedido,(*ped)[*n_ped].id_pedido);
    (*pr_ped)[*n_pr_ped].unidades = unidades;

    fecha_actual((*pr_ped)[*n_pr_ped].fecha_entrega,1);

    (*pr_ped)[*n_pr_ped].importe = importe;
    (*pr_ped)[*n_pr_ped].est_pedido = enPreparacion;

    (*n_ped)++;
    (*n_pr_ped)++;

}




void crear_pedido ( Pedido **ped, int *n_ped , char usu_act[8] , usu tipo_usu){

    int i=0,j,n;
    char borrado[8]="#######";
    char id_sig[8]="\0";


    while ( i<*n_ped  && strcmp( (*ped)[i].id_pedido , borrado) != 0 ){

        i++;
    }


    if ( i >= *n_ped ){

        *ped = ( Pedido *)realloc(*ped, (*n_ped+1) * sizeof(Pedido));

        for ( j=0 ; j<10 ; j++ ) (*ped)[*n_ped].lugar_entrega[j] = '\0';

        crear_siguiente_id(7,id_sig,(*ped)[i-1].id_pedido);

        strcpy((*ped)[*n_ped].id_pedido,id_sig);

        system("cls");

        fflush(stdin);
        printf("Fecha_pedido: ");
        gets((*ped)[*n_ped].fecha_ped);

        printf("Id_cliente: ");
        fflush(stdin);
        gets((*ped)[*n_ped].id_cliente);

        fflush(stdin);
        printf("Lugar_entrega: ");
        gets((*ped)[*n_ped].lugar_entrega);
        fflush(stdin);

        if (strcmp((*ped)[*n_ped].lugar_entrega,"domicilio") == 0){

            printf("Id_cod_prom: ");
            fflush(stdin);
            gets((*ped)[*n_ped].id_cod_prom);

        }else if ( strcmp((*ped)[*n_ped].lugar_entrega,"locker") == 0 ){

            printf("Id_locker: ");
            fflush(stdin);
            gets((*ped)[*n_ped].id_locker);

        }else{

            printf("Error con el lugar de entrega de pedido en alta");
            exit(1);

        }

        (*n_ped)++;


            }else{

                if ( i == 0){

                    strcpy( (*ped)[i].id_pedido , "0000001");

                }else{

                    crear_siguiente_id(7,id_sig,(*ped)[i-1].id_pedido);

                    strcpy( (*ped)[i].id_pedido,id_sig);

                    system("cls");

                    printf("Fecha_pedido: ");
                    fflush(stdin);
                    gets((*ped)[i].fecha_ped);
                    strcpy( (*ped)[*n_ped].id_cliente , usu_act);
                    printf("Lugar_entrega: ");
                    fflush(stdin);
                    gets((*ped)[i].lugar_entrega);

                    if (strcmp((*ped)[i].lugar_entrega,"domicilio") == 0){

                        printf("Id_cod_prom: ");
                        fflush(stdin);
                        gets((*ped)[i].id_cod_prom);

                    }else if ( strcmp((*ped)[i].lugar_entrega,"locker") == 0 ){

                        printf("Id_locker: ");
                        fflush(stdin);
                        gets((*ped)[i].id_locker);

                    }else{

                        printf("Error con el lugar de entrega de pedido en alta");
                        exit(1);

                    }

                }



            }




}


void modificar_pedido ( Pedido *ped , ProductoPedido *pr_ped ,int *n_ped , int *n_pr_ped, int indice ,usu tipo_usu, char usu_act[8]){

    int op,i,j=0;

    switch (tipo_usu) {

        case admin:

            printf("Fecha_pedido: ");
            fflush(stdin);
            gets(ped[indice].fecha_ped);
            printf("Id_cliente: ");
            fflush(stdin);
            gets(ped[indice].id_cliente);
            printf("Lugar_entrega: ");
            fflush(stdin);
            gets(ped[indice].lugar_entrega);

            if (strcmp(ped[indice].lugar_entrega,"domicilio") == 0){

                printf("Id_cod_prom: ");
                fflush(stdin);
                gets(ped[indice].id_cod_prom);

            }else if ( strcmp(ped[indice].lugar_entrega,"locker") == 0 ){

                printf("Id_locker: ");
                fflush(stdin);
                gets(ped[indice].id_locker);

            }else{

                printf("Error con el lugar de entrega de pedido en modificar");
                exit(1);

            }


            break;
        case proveedor:

            while ( strcmp(ped[indice].id_pedido,pr_ped[j].id_pedido)!=0) j++;

            switch (pr_ped[j].est_pedido) {

                case enPreparacion:

                    for (i=0 ; i<*n_pr_ped ; i++){

                        if ( strcmp(ped[indice].id_pedido,pr_ped[i].id_pedido)==0){

                            pr_ped[i].est_pedido = enviado;

                        }

                    }


                    break;
                case enviado:

                    for (i=0 ; i<*n_pr_ped ; i++){

                        if ( strcmp(ped[indice].id_pedido,pr_ped[i].id_pedido)==0){

                            pr_ped[i].est_pedido = enReparto;

                        }

                    }

                    break;
                case enReparto:

                    printf("--------- Nuevo estado del pedido -------\n");
                    printf("3.enLocker\n4.entregado\n");
                    scanf("%i",&op);


                    if ( op == 3){

                        for (i=0 ; i<*n_pr_ped ; i++){

                            if ( strcmp(ped[indice].id_pedido,pr_ped[i].id_pedido)==0){

                                pr_ped[i].est_pedido = enLocker;

                            }

                        }

                    }else if ( op == 4 ){

                        for (i=0 ; i<*n_pr_ped ; i++){

                            if ( strcmp(ped[indice].id_pedido,pr_ped[i].id_pedido)==0){

                                pr_ped[i].est_pedido = entregado;

                            }

                        }

                    }else{

                        printf("Error con el estado del pedido ( modificar estado pedido )");
                        exit(1);

                    }

                    break;
                default:
                    break;
            }

            break;

        default:
            break;
    }


}


void recoger_pedido( Pedido *ped , ProductoPedido *prod_ped, int *n_pedidos,int *n_pr_ped, char id_cliente[8] , int opcion_pedido , usu tipo_usu ){

    int i=0,error=0;
    char zero_8[8]="\0",zero_7[7]="\0",zero_11[11]="\0",zero_5[5]="\0",codigo_lock[7]="\0";

    printf("Introduce el codigo del locker: ");
    fflush(stdin);
    gets(codigo_lock);

    //if (strcmp(codigo_lock,))


    i=0;

    while ( i<*n_pr_ped && strcmp( ped[opcion_pedido].id_pedido,prod_ped[i].id_pedido)!=0 ){
        i++;
    }

    if (strcmp(ped[opcion_pedido].id_pedido,prod_ped[i].id_pedido)==0){

        strcpy( prod_ped[i].id_locker,zero_11);
        strcpy( prod_ped[i].cod_locker,zero_7);
        fecha_actual( prod_ped[i].fecha_entr_dev,0);

        prod_ped[i].est_pedido = entregado;

    }



    printf("\nHas recogido el pedido.\n");
    system("pause");




    system("cls");
    menu_pedidos_clientes(ped, prod_ped, n_pedidos,n_pr_ped,id_cliente,cliente);

}



void menu_prod_ped ( Pedido *ped, ProductoPedido *pr_p, int *n_ped,int *n_pr_ped , char id_ped[8] ,char id_cliente[8],usu tipo_usu){

    int i=0,cont=0,ind_prod_ped,error=0;
    char c,op,estado_ped_nuevo[14]="\0",zero_8[8]="\0",zero_7[7]="\0",zero_11[11]="\0",zero_5[5]="\0";

    system("cls");

    while (i< *n_pr_ped && strcmp( pr_p[i].id_pedido,id_ped)!=0) i++;

    ind_prod_ped = i;

    printf("------------------------- Producto %i --------------------------\n\n",ind_prod_ped+1);

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
            printf("Id_transportista: %s\n",pr_p[ind_prod_ped].id_transp);

            break;
        case enLocker:

            printf("enLocker\n");
            printf("Id_transportista: %s\n",pr_p[ind_prod_ped].id_transp);
            printf("Id_locker: %s\n",pr_p[ind_prod_ped].id_locker);
            printf("Cod_locker: %s\n",pr_p[ind_prod_ped].cod_locker);
            printf("Fecha de entrega: %s\n",pr_p[ind_prod_ped].fecha_entr_dev);

            break;
        case entregado:

            printf("entregado\n");
            printf("Id_transportista: %s\n",pr_p[ind_prod_ped].id_transp);
            printf("Fecha de entrega: %s\n",pr_p[ind_prod_ped].fecha_entr_dev);

            break;
        case devuelto:

            printf("devuelto\n");
            printf("Id_transportista: %s\n",pr_p[ind_prod_ped].id_transp);
            printf("Fecha de entrega: %s\n",pr_p[ind_prod_ped].fecha_entr_dev);

            break;
        case trasnportista:

            printf("transportista\n");
            printf("Id_transportista: %s\n",pr_p[ind_prod_ped].id_transp);

            break;
        default:
            printf("Error con el estado del prod_ped ( menu prod ped )");
            exit(1);

    }

    printf("----------------------------------------------------------------\n");

    system("pause");


    if ( tipo_usu == admin ){

        do{

            printf("\n Quiere modificar este producto? (s/n): ");
            scanf("%c",&c);

            system("cls");

            strcpy( pr_p[ind_prod_ped].id_transp,zero_5);
            strcpy( pr_p[ind_prod_ped].id_locker,zero_11);
            strcpy( pr_p[ind_prod_ped].cod_locker,zero_7);
            strcpy( pr_p[ind_prod_ped].fecha_entr_dev,zero_11);


            if ( c == 's' || c == 'S'){

                printf("Unidades: ");
                scanf("%i",&pr_p[ind_prod_ped].unidades);
                printf("Fecha_prev_entrega: ");
                fflush(stdin);
                gets(pr_p[ind_prod_ped].fecha_entrega);
                printf("Importe: ");
                scanf("%i",&pr_p[ind_prod_ped].importe);

                do{

                    printf("Estado_pedido: ");
                    fflush(stdin);
                    fgets(estado_ped_nuevo,14,stdin);

                    if (strcmp(estado_ped_nuevo,"enPreparacion")==0){

                        pr_p[ind_prod_ped].est_pedido = enPreparacion;


                    }else if ( strcmp(estado_ped_nuevo,"enviado")==0 ){

                        pr_p[ind_prod_ped].est_pedido = enviado;

                    }else if ( strcmp(estado_ped_nuevo,"enReparto")==0 ){

                        pr_p[ind_prod_ped].est_pedido = enReparto;

                    }else if ( strcmp(estado_ped_nuevo,"enLocker")==0 ){

                        pr_p[ind_prod_ped].est_pedido = enLocker;

                    }else if ( strcmp(estado_ped_nuevo,"entregado")==0 ){

                        pr_p[ind_prod_ped].est_pedido = entregado;

                    }else if ( strcmp(estado_ped_nuevo,"devuelto")==0 ){

                        pr_p[ind_prod_ped].est_pedido = devuelto;

                    }else if ( strcmp(estado_ped_nuevo,"transportista")==0 ){

                        pr_p[ind_prod_ped].est_pedido = trasnportista;

                    }else{

                        printf("Escribe un estado valido.\n");
                        error=1;

                    }

                } while (error == 1);


            }else if ( c == 'n' || c == 'N'){


            }else printf("Escribe s o n");


        } while ( c != 's' && c != 'S' && c != 'n' && c != 'N');

    }

        printf("\n");
        system("cls");

        if ( tipo_usu == cliente ){

            menu_pedidos_clientes(ped, pr_p, n_ped, n_pr_ped, id_cliente,cliente);

        }else if ( tipo_usu == admin ){


            menu_pedidos_admin(ped, pr_p, n_ped, n_pr_ped,admin);

        }



}




void menu_pedidos_clientes( Pedido *ped , ProductoPedido *prod_ped, int *n_pedidos,int *n_pr_ped, char id_cliente[8] , usu tipo_usu ){

    int i,j,k,op_ped,op_accion_pedido,existe=0;
    int opcion,error=0;
    char c='a',resp_2;
    char fecha_act[11]="\0";

    printf("--------- Todos sus pedidos ---------\n\n");

    for (i=0 ; i<*n_pedidos ; i++ ){

        if ( strcmp( id_cliente , ped[i].id_cliente ) == 0){

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

    do{

        printf("\nElija una opcion:\n");
        printf("1.ver productos asociados\n2.Recoger Pedido\n3.salir\n");
        scanf("%i", &op_ped);

        switch (op_ped) {

            case 1:

                printf("Escribe la id del pedido para ver los productos asociados a este:");
                scanf("%i",&op_accion_pedido);

                menu_prod_ped( ped,prod_ped, n_pedidos,n_pr_ped ,ped[op_accion_pedido-1].id_pedido ,id_cliente, cliente);

                system("cls");

                menu_pedidos_clientes(ped, prod_ped, n_pedidos,n_pr_ped,id_cliente,cliente);

                break;
            case 2:

                for (i=0 ; i<*n_pedidos ; i++ ){

                    if ( strcmp( id_cliente , ped[i].id_cliente ) == 0){

                        k=0;
                        while( k<*n_pr_ped && strcmp(ped[i].id_pedido,prod_ped[k].id_pedido)!=0 ){
                            k++;
                        }

                        if ( prod_ped[k].est_pedido == enLocker) existe = 1;
                    }

                }

                if ( existe == 1 ){

                    do{

                        printf("Escribe el id del pedido que quiera recoger: ");
                        scanf("%i",&op_accion_pedido);


                        if (strcmp(id_cliente,ped[op_accion_pedido-1].id_cliente)!=0 || prod_ped[k].est_pedido != enLocker){

                            printf("Elije un pedido valido.\n");
                            error=1;
                        }

                    }while ( error == 1 );


                    recoger_pedido( ped , prod_ped, n_pedidos,n_pr_ped, id_cliente , op_accion_pedido-1, cliente );

                }else{

                    printf("\nNo tiene ningun pedido en locker.");
                    system("pause");
                    system("cls");
                    menu_pedidos_clientes(ped, prod_ped, n_pedidos,n_pr_ped,id_cliente,cliente);
                }



                break;
            case 3:
                break;
            default:

                printf("Elije un numero del 1 al 3\n");
                break;
        }

    }while ( op_ped < 1 || op_ped > 3);


}



void asignar_transportista( Pedido *ped ,ProductoPedido *prod_ped, Transportista *transp, int *n_transp,  int *n_pedidos , int *n_pr_ped , usu tipo_usu , int indice_p , char prov_cliente[21] ){

    int i,j,op,error=0;
    char c='a';

    system("cls");

    do{

        printf("---------------- Transportistas disponibles en %s -----------------\n\n",prov_cliente);

        for ( i=0 ; i< *n_pr_ped ; i++ ){

            if (strcmp(transp[i].Ciudad,prov_cliente)==0){

                printf("[%c].%s\n",c,transp[i].Id_transp);
                c++;
            }

        }

        printf("Escribe el id de un transportista: ");
        scanf("%i",&op);

        if (strcmp(transp[op-1].Ciudad,prov_cliente)!=0){

            error = 1;
            printf("\nElije uno de los transportistas dados.");
            system("pause");
            system("cls");

        }

    }while ( error == 1 );


    i=0;
    while ( strcmp(ped[indice_p].id_pedido,prod_ped[i].id_pedido)!=0){

        i++;
    }

    strcpy(prod_ped[i].id_transp,transp[op-1].Id_transp);



}



void asignar_locker( Pedido *ped ,ProductoPedido *prod_ped, Locker *lock, int *n_lock, int *n_pedidos , int *n_pr_ped , usu tipo_usu , int indice_p , char prov_cliente[21] ){

    int i,j,op,error=0;
    char c='a';

    system("cls");

    do{

        printf("---------------- Lockers disponibles en %s -----------------\n\n",prov_cliente);

        for ( i=0 ; i< *n_lock ; i++ ){

            if (strcmp(lock[i].provincia,prov_cliente)==0){

                printf("[%c].%s\n",c,lock[i].id_locker);
                c++;
            }

        }

        printf("Escribe el id de un locker: ");
        scanf("%i",&op);

        if (strcmp(lock[op-1].provincia,prov_cliente)!=0){

            error = 1;
            printf("\nElije uno de los lockers dados.");
            system("pause");
            system("cls");

        }

    }while ( error == 1 );


    for ( i=0 ; i< *n_pr_ped ; i++ ){

        if ( strcmp(ped[indice_p].id_pedido,prod_ped[i].id_pedido)==0){

            strcpy(prod_ped[i].id_locker,lock[op-1].id_locker);

        }

    }

}






void menu_pedidos_admin( Pedido *ped ,ProductoPedido *prod_ped,  int *n_pedidos , int *n_pr_ped , usu tipo_usu) {

    int i, j,tipo_ped,error=0;
    char c = 'a', resp,resp_2;
    int op_ped,op_accion_pedido,existe=0;

    do {

        printf("Desea listar los pedidos segun su estado? (s/n):");
        fflush(stdin);
        scanf("%c", &resp);

        system("cls");

        if (resp == 's' || resp == 'S') {

            do{

                printf("1.enPreparacion\n2.enviado\n3.enReparto\n4.enLocker\n5.entregado\n6.devuelto\n7.transportista\n");
                printf("Elija el tipo de pedido (1-7):");
                scanf("%i", &tipo_ped);

                system("cls");

                switch (tipo_ped) {

                    case 1:

                        printf("--------- Pedidos en Preparacion ---------\n\n");

                        i = 0;

                        while (i < *n_pedidos) {

                            j=0;

                            while ( j < *n_pr_ped && prod_ped[j].est_pedido != enPreparacion){
                                j++;
                            }

                            if ( j < *n_pr_ped ) {


                                if ( strcmp(ped[i].id_pedido,prod_ped[j].id_pedido)==0 ){

                                    if (strcmp(ped[i].lugar_entrega, "domicilio") == 0 ) {

                                        printf("[%c].%s-%s-%s-%s-%s\n", c,
                                               ped[i].id_pedido,
                                               ped[i].fecha_ped,
                                               ped[i].id_cliente,
                                               ped[i].lugar_entrega,
                                               ped[i].id_cod_prom);


                                    }else if (strcmp(ped[i].lugar_entrega, "locker") == 0){

                                        printf("[%c].%s-%s-%s-%s-%s\n", c,
                                               ped[i].id_pedido,
                                               ped[i].fecha_ped,
                                               ped[i].id_cliente,
                                               ped[i].lugar_entrega,
                                               ped[i].id_locker);


                                    }

                                    c++;



                                }


                            }else{

                                printf("No hay pedidos en preparacion\n");
                                system("pause");
                                system("cls");
                                menu_pedidos_admin(ped, prod_ped, n_pedidos,n_pr_ped,admin);

                            }

                            i++;

                        }

                        break;
                    case 2:

                        printf("--------- Pedidos enviados ---------\n\n");

                        i = 0;

                        while (i < *n_pedidos) {

                            j=0;

                            while ( j < *n_pr_ped && prod_ped[j].est_pedido != enReparto){
                                j++;
                            }

                            if ( j < *n_pr_ped ) {


                                if ( strcmp(ped[i].id_pedido,prod_ped[j].id_pedido)==0 ){

                                    if (strcmp(ped[i].lugar_entrega, "domicilio") == 0 ) {

                                        printf("[%c].%s-%s-%s-%s-%s\n", c,
                                               ped[i].id_pedido,
                                               ped[i].fecha_ped,
                                               ped[i].id_cliente,
                                               ped[i].lugar_entrega,
                                               ped[i].id_cod_prom);


                                    }else if (strcmp(ped[i].lugar_entrega, "locker") == 0){

                                        printf("[%c].%s-%s-%s-%s-%s\n", c,
                                               ped[i].id_pedido,
                                               ped[i].fecha_ped,
                                               ped[i].id_cliente,
                                               ped[i].lugar_entrega,
                                               ped[i].id_locker);


                                    }

                                    c++;

                                }


                            }else{

                                printf("No hay pedidos enviados\n");
                                system("pause");
                                system("cls");
                                menu_pedidos_admin(ped, prod_ped, n_pedidos,n_pr_ped,admin);

                            }

                            i++;

                        }

                        break;

                    case 3:

                        printf("--------- Pedidos en reparto ---------\n\n");

                        i = 0;

                        while (i < *n_pedidos) {

                            j=0;

                            while ( j < *n_pr_ped && prod_ped[j].est_pedido != enReparto){
                                j++;
                            }

                            if ( j < *n_pr_ped ) {


                                if ( strcmp(ped[i].id_pedido,prod_ped[j].id_pedido)==0 ){

                                    if (strcmp(ped[i].lugar_entrega, "domicilio") == 0 ) {

                                        printf("[%c].%s-%s-%s-%s-%s\n", c,
                                               ped[i].id_pedido,
                                               ped[i].fecha_ped,
                                               ped[i].id_cliente,
                                               ped[i].lugar_entrega,
                                               ped[i].id_cod_prom);


                                    }else if (strcmp(ped[i].lugar_entrega, "locker") == 0){

                                        printf("[%c].%s-%s-%s-%s-%s\n", c,
                                               ped[i].id_pedido,
                                               ped[i].fecha_ped,
                                               ped[i].id_cliente,
                                               ped[i].lugar_entrega,
                                               ped[i].id_locker);


                                    }

                                    c++;



                                }


                            }else{

                                printf("No hay pedidos en reparto\n");
                                system("pause");
                                system("cls");
                                menu_pedidos_admin(ped, prod_ped, n_pedidos,n_pr_ped,admin);

                            }

                            i++;

                        }

                        break;
                    case 4:

                        printf("--------- Pedidos en locker ---------\n\n");

                        i = 0;

                        while (i < *n_pedidos) {

                            j=0;

                            while ( j < *n_pr_ped && prod_ped[j].est_pedido != enLocker){
                                j++;
                            }

                            if ( j < *n_pr_ped ) {


                                if ( strcmp(ped[i].id_pedido,prod_ped[j].id_pedido)==0 ){

                                    if (strcmp(ped[i].lugar_entrega, "domicilio") == 0 ) {

                                        printf("[%c].%s-%s-%s-%s-%s\n", c,
                                               ped[i].id_pedido,
                                               ped[i].fecha_ped,
                                               ped[i].id_cliente,
                                               ped[i].lugar_entrega,
                                               ped[i].id_cod_prom);


                                    }else if (strcmp(ped[i].lugar_entrega, "locker") == 0){

                                        printf("[%c].%s-%s-%s-%s-%s\n", c,
                                               ped[i].id_pedido,
                                               ped[i].fecha_ped,
                                               ped[i].id_cliente,
                                               ped[i].lugar_entrega,
                                               ped[i].id_locker);


                                    }

                                    c++;



                                }


                            }else{

                                printf("No hay pedidos en locker\n");
                                system("pause");
                                system("cls");
                                menu_pedidos_admin(ped, prod_ped, n_pedidos,n_pr_ped,admin);

                            }

                            i++;

                        }

                        break;
                    case 5:

                        printf("--------- Pedidos entregados ---------\n\n");

                        i = 0;

                        while (i < *n_pedidos) {

                            j=0;

                            while ( j < *n_pr_ped && prod_ped[j].est_pedido != entregado){
                                j++;
                            }

                            if ( j < *n_pr_ped ) {


                                if ( strcmp(ped[i].id_pedido,prod_ped[j].id_pedido)==0 ){

                                    if (strcmp(ped[i].lugar_entrega, "domicilio") == 0 ) {

                                        printf("[%c].%s-%s-%s-%s-%s\n", c,
                                               ped[i].id_pedido,
                                               ped[i].fecha_ped,
                                               ped[i].id_cliente,
                                               ped[i].lugar_entrega,
                                               ped[i].id_cod_prom);


                                    }else if (strcmp(ped[i].lugar_entrega, "locker") == 0){

                                        printf("[%c].%s-%s-%s-%s-%s\n", c,
                                               ped[i].id_pedido,
                                               ped[i].fecha_ped,
                                               ped[i].id_cliente,
                                               ped[i].lugar_entrega,
                                               ped[i].id_locker);


                                    }

                                    c++;



                                }


                            }else{

                                printf("No hay pedidos entregados\n");
                                system("pause");
                                system("cls");
                                menu_pedidos_admin(ped, prod_ped, n_pedidos,n_pr_ped,admin);

                            }

                            i++;

                        }

                        break;
                    case 6:

                        printf("--------- Pedidos devueltos ---------\n\n");

                        i = 0;

                        while (i < *n_pedidos) {

                            j=0;

                            while ( j < *n_pr_ped && prod_ped[j].est_pedido != devuelto ){
                                j++;
                            }

                            if ( j < *n_pr_ped ) {


                                if ( strcmp(ped[i].id_pedido,prod_ped[j].id_pedido)==0 ){

                                    if (strcmp(ped[i].lugar_entrega, "domicilio") == 0 ) {

                                        printf("[%c].%s-%s-%s-%s-%s\n", c,
                                               ped[i].id_pedido,
                                               ped[i].fecha_ped,
                                               ped[i].id_cliente,
                                               ped[i].lugar_entrega,
                                               ped[i].id_cod_prom);


                                    }else if (strcmp(ped[i].lugar_entrega, "locker") == 0){

                                        printf("[%c].%s-%s-%s-%s-%s\n", c,
                                               ped[i].id_pedido,
                                               ped[i].fecha_ped,
                                               ped[i].id_cliente,
                                               ped[i].lugar_entrega,
                                               ped[i].id_locker);


                                    }

                                    c++;



                                }


                            }else{

                                printf("No hay pedidos devueltos\n");
                                system("pause");
                                system("cls");
                                menu_pedidos_admin(ped, prod_ped, n_pedidos,n_pr_ped,admin);

                            }

                            i++;

                        }

                        break;
                    case 7:

                        printf("--------- Pedidos en transportista ---------\n\n");

                        i = 0;

                        while (i < *n_pedidos) {

                            j=0;

                            while ( j < *n_pr_ped && prod_ped[j].est_pedido != trasnportista){
                                j++;
                            }

                            if ( j < *n_pr_ped ) {


                                if ( strcmp(ped[i].id_pedido,prod_ped[j].id_pedido)==0 ){

                                    if (strcmp(ped[i].lugar_entrega, "domicilio") == 0 ) {

                                        printf("[%c].%s-%s-%s-%s-%s\n", c,
                                               ped[i].id_pedido,
                                               ped[i].fecha_ped,
                                               ped[i].id_cliente,
                                               ped[i].lugar_entrega,
                                               ped[i].id_cod_prom);


                                    }else if (strcmp(ped[i].lugar_entrega, "locker") == 0){

                                        printf("[%c].%s-%s-%s-%s-%s\n", c,
                                               ped[i].id_pedido,
                                               ped[i].fecha_ped,
                                               ped[i].id_cliente,
                                               ped[i].lugar_entrega,
                                               ped[i].id_locker);


                                    }

                                    c++;



                                }


                            }else{

                                printf("No hay pedidos en transportista\n");
                                system("pause");
                                system("cls");
                                menu_pedidos_admin(ped, prod_ped, n_pedidos,n_pr_ped,admin);

                            }

                            i++;

                        }

                        break;
                    default:

                        printf("Escribe un numero del (1-7)");
                        system("cls");

                        break;

                }

            } while (tipo_ped < 1 ||  tipo_ped > 7);


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
            printf("1.alta\n2.baja\n3.modificar\n4.ver productos asociados\n5.aignar transportista\n6.Asignar Locker\n7.salir\n");
            scanf("%i", &op_ped);

            switch (op_ped) {

                case 1:

                    crear_pedido(&ped,n_pedidos,NULL,admin);

                    system("cls");

                    menu_pedidos_admin(ped, prod_ped, n_pedidos,n_pr_ped,admin);

                    break;
                case 2:

                    do{

                        printf("----------------------------\n\n");
                        printf("Escribe el id de pedido que quiera borrar: ");
                        scanf("%i",&op_accion_pedido);

                        eliminar_pedido( ped,op_accion_pedido-1);

                        printf("Quiere eliminar mas pedidos? (s/n): ");
                        fflush(stdin);
                        scanf("%c",&resp_2);

                    }while ( resp_2 != 'n' && resp_2 != 'N');

                        system("cls");

                    menu_pedidos_admin(ped, prod_ped, n_pedidos,n_pr_ped,admin);

                    break;
                case 3:

                    printf("----------------------------\n\n");
                    printf("Escribe el id de pedido que quiera modificar: ");
                    scanf("%i",&op_accion_pedido);

                    i=0;

                    modificar_pedido( ped , prod_ped,n_pedidos,n_pr_ped ,op_accion_pedido - 1 ,admin,"0000004");

                    system("cls");

                    menu_pedidos_admin(ped, prod_ped, n_pedidos,n_pr_ped,admin);

                    break;
                case 4:

                    printf("Escribe el id del pedido que quiera ver: ");
                    scanf("%i",&op_accion_pedido);

                    menu_prod_ped( ped,prod_ped, n_pedidos,n_pr_ped ,ped[op_accion_pedido-1].id_pedido ,NULL, admin);

                    system("cls");

                    menu_pedidos_admin(ped, prod_ped, n_pedidos,n_pr_ped,admin);

                    break;
                case 5:

                    do{

                        printf("Escribe el id del pedido al que quiera asignar un transportista: ");
                        scanf("%i",&op_accion_pedido);

                        j=0;

                        while (  j<*n_pr_ped && strcmp(ped[op_accion_pedido].id_pedido,prod_ped[j].id_pedido)!=0  ){

                            if (prod_ped[j].est_pedido == enReparto || prod_ped[j].est_pedido == trasnportista ) existe=1;
                            j++;
                        }

                        if ( existe == 1 ){

                           // asignar_transportista(ped,prod_ped,transp,n_transp,n_pedidos,n_pr_ped,admin,op_accion_pedido--, usu[act].provincia);

                        }else{

                            printf("\nElije un pedido valido\n");
                            system("pause");
                            system("cls");
                            menu_pedidos_admin(ped, prod_ped, n_pedidos,n_pr_ped,admin);

                        }

                        printf("Quiere asignar otro transportista? (s/n): ");
                        fflush(stdin);
                        scanf("%c",&resp_2);

                    } while ( resp_2 != 'n' && resp_2 != 'N' );

                case 6:

                    do{

                        printf("Escribe el id del pedido al que quiera asignar un locker: ");
                        scanf("%i",&op_accion_pedido);

                        if ( strcmp(ped[op_accion_pedido-1].lugar_entrega,"locker")!=0){

                            printf("Elije un pedido destinado a locker.\n");
                            error=1;
                        }

                    }while ( error != 0);

                    //asignar_locker(ped,prod_ped,locker,n_lock,n_pedidos,n_pr_ped,admin,op_accion_pedido--, usu[act].provincia)

                    break;
                case 7:
                    break;
                default:

                    printf("Elije un numero del 1 al 7\n\n");
                    break;
            }

        }while ( op_ped != 1 && op_ped != 2 && op_ped != 3 && op_ped != 4 && op_ped != 5 && op_ped != 6 && op_ped != 7);



    }



void menu_pedidos_prov(Pedido *ped, ProductoPedido *prod_ped, int *n_pedidos, usu tipo_usu){






}

void menu_pedidos_transp ( Locker *lock, CompartimentoLocker *c_lock ,Pedido *ped, ProductoPedido *prod_ped,int *n_lock, int *n_c_lock, int *n_pedidos ,int *n_pr_ped,char id_tr_act[5], usu tipo_usu) {

    int i,j,k,l,op,op_prod,n_comp_act;
    char c='a',confirma,zero_11[11]="\0",zero_7[7]="\0";


    printf("---------------------- Todos sus repartos ---------------------\n\n");


    for ( i=0 ; i<*n_pr_ped ; i++ ){

        if ( i < *n_pr_ped && strcmp(prod_ped[i].id_transp,id_tr_act)==0 && prod_ped[i].est_pedido == enReparto){

            printf("[%c].%s-%i-%i-%s\n",c,prod_ped[i].id_prod,prod_ped[i].unidades,prod_ped[i].importe,prod_ped[i].fecha_entrega);
            c++;

        }

    }

    do{

        printf("---------------------------------------------------------------\n");
        printf("Elije una opcion:\n");
        printf("1.entregar pedido\n2.salir\n");
        scanf("%i",&op);

        switch (op) {

            case 1:

                do{

                    printf("\nEscribe la id de un producto: ");
                    scanf("%i", &op_prod);

                }while( strcmp(prod_ped[op_prod-1].id_transp,id_tr_act)!=0 && prod_ped[op_prod-1].est_pedido != enReparto);



                do{

                    system("cls");
                    printf("-------------------------------- Producto %i -------------------------\n\n",op);
                    printf("Confirma la entrega de este pedido?(s/n): ");
                    fflush(stdin);
                    scanf("%c",&confirma);

                }while( confirma != 's' && confirma != 'S' && confirma != 'n' && confirma != 'N');


                if ( confirma == 'S' || confirma == 's'){

                    j=0;
                    while ( j<*n_pedidos && strcmp(ped[j].id_pedido,prod_ped[op_prod-1].id_pedido)!=0){
                        j++;
                    }

                    prod_ped[op_prod-1].est_pedido = entregado;

                    if (strcmp(ped[j].lugar_entrega,"domicilio")==0){

                        strcpy(prod_ped[op_prod-1].id_locker,zero_11);
                        strcpy(prod_ped[op_prod-1].cod_locker,zero_7);

                        fecha_actual(prod_ped[op_prod-1].fecha_entr_dev,0);

                        printf("\nLa entrega se ha confirmado.\n");

                    }else if (strcmp(ped[j].lugar_entrega,"locker")==0){

                        k=0;
                        while (strcmp(ped[j].id_locker,lock[k].id_locker)!=0) k++;

                        if ( lock[k].Num_compT - lock[k].Num_compOcup !=0 ){

                            n_comp_act = lock[k].Num_compOcup + 1;

                            l=0;
                            while ( c_lock[l].Num_comp != n_comp_act ) l++;

                            strcpy(prod_ped[op-1].id_locker,ped[j].id_locker);
                            strcpy(prod_ped[op-1].cod_locker,c_lock[l].cod_locker);

                        }


                        fecha_actual(prod_ped[op_prod-1].fecha_entr_dev,0);



                        printf("\nLa entrega se ha confirmado.\n");


                    }else printf("Error con el lugar de entrega (entrega)\n");


                }

                system("pause");
                system("cls");
                menu_pedidos_transp(lock,c_lock,ped, prod_ped,n_lock ,n_c_lock,n_pedidos,n_pr_ped,"0002",transportista);


                break;
            case 2:
                break;
            default:
                printf("Elije una opcion valida.\n");
                break;
        }

    }while ( op != 1 && op != 2);


}


    void menu_pedidos(Cliente *clt, Transportista *transp ,Locker *lock, CompartimentoLocker *c_lock ,Pedido *ped, ProductoPedido *prod_ped,int *n_cliente, int *n_transp, int *n_lock, int *n_c_lock, int *n_pedidos ,int *n_prod_ped, usu tipo_usu, int id_act ) {

        switch (tipo_usu) {


            case cliente:

                menu_pedidos_clientes(ped, prod_ped, n_pedidos, n_prod_ped, clt[id_act].Id_cliente,cliente);

                break;
            case admin:

                menu_pedidos_admin(ped, prod_ped, n_pedidos, n_prod_ped,admin);

                break;
            case proveedor:

                menu_pedidos_prov(ped, prod_ped, n_pedidos,proveedor);

                break;
            case transportista:

                menu_pedidos_transp(lock,c_lock,ped, prod_ped,n_lock,n_c_lock, n_pedidos,n_prod_ped,transp[id_act].Id_transp,transportista);

                break;
            default:

                printf("Error con el tipo de ususario");
                exit(1);

        }

    }
