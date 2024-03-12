/* Fichero  en que irán las funciones del módulo descuentos que se necesiten en otros modulos*/

typedef enum { 
    codpro, cheqreg, // tipos de descuentos
    activo, inactivo, //estados de los descuentos 
    todos, esizon, //Aplicabilidad de los descuentos en los productos
    si,no // Estado de descuentos clientes 
}opciones;

/*TIPO DESCUENTOS*/
typedef struct descuentos
{
    char Id_cod[10],Descrip[50];
    int Importe;    
    opciones Tipo, Estado, Aplicabilidad;
}Descuentos;

/*TIPO DESCUENTOS CLIENTES*/
typedef struct descuentos_clientes
{
    char Id_cliente[7],Id_cod[10], 
    f_asignacion[11], f_caducidad[11]; //por comodidad las fechas serán del tipo "00/00/0000\0" que posteriormente será pasada al tipo fecha
    opciones Estado; //si para aplicado y no en caso contrario
}Descuentos_clientes;

//cabecera: 
//precondición: 
//postcondición:  