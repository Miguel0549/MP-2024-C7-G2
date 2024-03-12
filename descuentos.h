/* Fichero  en que irán las funciones del módulo descuentos que se necesiten en otros modulos*/
typedef enum { 
    codpro, cheqreg, // tipos de descuentos
    activo, inactivo, //estados de los descuentos 
    todos, esizon //Aplicabilidad de los descuentos en los productos
}opciones;

/*TIPO DESCUENTOS*/
typedef struct descuentos
{
    char Id_cod[10],Descrip[50];
    int Importe;    
    opciones Tipo, Estado, Aplicabilidad;
}Descuentos;

//cabecera: 
//precondición: 
//postcondición:  
