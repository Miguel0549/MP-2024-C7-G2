#ifndef PROYECTO_MP_TRANSPORTISTAS_H
#define PROYECTO_MP_TRANSPORTISTAS_H

#include "Clientes.h"
typedef struct {
    char Id_transp[5];
    char Nombre[21];
    char email[31];
    char Contrasenna[16];
    char Nom_empre[21];
    char Ciudad[21];

}Transportista;


void de_int_a_id_empresa(int i_id, char* s_id);
void carga_transp(Transportista**t,int *n_trans);
void volcado_transp(Transportista **t,int *n_trans);
void nuevo_transportista(Transportista **t,int *n_transport, int *ind_usu_act);
int indice_con_id_transp(Transportista**vector_transp,char *id_transp,int num_transp);
void borrar_transp_con_id(Transportista**vector_transp,char *Id_trans, int *n_transp);
void modificar_transp ( Transportista *tranp , int indice_transp );
void listado_transportista ( Transportista *transp, int *n_transp );
void datos_transportista ( Transportista *transp , int ind_transp );

#endif //PROYECTO_MP_TRANSPORTISTAS_H
