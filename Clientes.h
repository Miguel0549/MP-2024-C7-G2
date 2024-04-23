#ifndef PROYECTO_MP_CLIENTES_H
#define PROYECTO_MP_CLIENTES_H


#include "Lockers.h"

typedef struct{

    char Id_cliente[8];
    char Nombr_cliente[21];
    char Dir_cliente[51];
    char Localidad[21];
    char Provincia[21];
    char email[31];
    char Contrasenna[16];
    char Cartera[7];

}Cliente;

void leer_string(char*cadena, int elem);
void siguiente_id(char*cad,int i);

void crear_siguiente_id ( int num_digitos, char vect_dest[num_digitos] , char vect_id[num_digitos]);

void carga_cliente(Cliente **c,int *n_clien);
void volcado_cliente(Cliente **c,int *n_clien);
void nuevo_cliente(Cliente **c,int *n_cliente, int *ind_usu_act);
void modificar_cliente ( Cliente **clt, int id_act , usu tipo_usu );
void datos_cliente ( Cliente *clt , int id_act);
void borrar_cliente_con_id(Cliente**vector_cliente,char *Id_cliente, int *n_clientes);

#endif //PROYECTO_MP_CLIENTES_H
