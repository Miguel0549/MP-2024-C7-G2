/* Fichero  en que irán las funciones del módulo descuentos que se necesiten en otros modulos*/

typedef enum { 
    codpro, cheqreg, // tipos de descuentos
    activo, inactivo, //estados de los descuentos 
    todos, esizon, //Aplicabilidad de los descuentos en los productos
    si,no // Estado de descuentos clientes 
}opciones;

/*TIPO DESCUENTOS*/
typedef struct
{
    char Id_cod[11],Descrip[51], Importe[4];
    opciones Tipo, Estado, Aplicabilidad;
}Descuentos;

/*TIPO DESCUENTOS CLIENTES*/
typedef struct 
{
    char Id_cliente[8],Id_cod[11], 
    f_asignacion[11], f_caducidad[11]; //por comodidad las fechas serán del tipo "00/00/0000\0" que posteriormente será pasada al tipo fecha
    opciones Estado; //si para aplicado y no en caso contrario
}Descuentos_clientes;
//cabecera: void crear_fichero_descuentos()
//precondición: ninguna
//postcondición:crea el fichero descuentos.txt sino existe e imprime un mensaje de error si es el caso
void crear_fichero_descuentos();

//cabecera: void crear_fichero_descuentos_clientes()
//precondición: ninguna
//postcondición:crea el fichero descuentos_clientes.txt sino existe e imprime un mensaje de error si es el caso
void crear_fichero_descuentos_clientes();


 //cabecera:void carga_descuentos(Descuentos **d )
 //precondición: recibe como doble puntero el vector de estructuras
 //postcondición: Carga del fichero descuentos.txt a un vector de estructuras del tipo indicado
void carga_descuentos(Descuentos **d);

 //cabecera:void carga_descuentos_clientes(Descuentos_clientes **dc)
 //precondición: recibe como doble puntero el vector de estructuras
 //postcondición:Carga del fichero descuentos_clientes.txt a un vector de estructuras del tipo indicado
void carga_descuentos_clientes(Descuentos_clientes **dc);
 //cabecera: void volcado_descuentos(Descuentos **d)
 //precondición:  recibe como doble puntero el vector de estructuras, inicializado
 //postcondición: Vuelca el contenido del vector de estructuras al fichero descuentos.txt
void volcado_descuentos(Descuentos*);

 //cabecera: void volcado_descuentos_clientes(Descuentos **dc)
 //precondición:  recibe como doble puntero el vector de estructuras, inicializado
 //postcondición: Vuelca el contenido del vector de estructuras al fichero descuentos_clientes.txt

//cabecera: void listar_descuentos(Descuentos *d,int *n_desc)
//precondición: *d inicializado
//postcondición: lista los descuentos actuales en el vector
void listar_descuentos(Descuentos*);

//cabecera: void listar_descuentos_cliente(char id_cliente[7],Descuentos_clientes v[])
//precondición: Recibe el id de un cliente así como al dirección de memoria de la estructura de los descuentos 
//postcondición: imprime(y lista) los descuentos que tiene vigente el cliente 


 //cabecera:
 //precondición:
 //postcondición:
