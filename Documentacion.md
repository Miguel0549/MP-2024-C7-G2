---
bibliography: ../Referencias.bib
biblio-style: "apalike"
link-citations: true

title: "Metodología de la Programación"
author:
    - Miguel Catalá Garrido
    - Pablo Beato Martínez
    - Manuel Díaz de la Rocha de Castro
---

# <span style='color:blue'> **MP-2024-C7-G2** </span>

---

## Índice

-   [ **MP-2024-C7-G2** ](#-nombre-del-proyecto-)
    -   [Índice](#índice)
-   [Documentación de usuario](#documentación-de-usuario)
    -   [Descripción funcional](#descripción-funcional)
    -   [Tecnología](#tecnología)
    -   [Manual de instalación](#manual-de-instalación-por-hacer)
    -   [Acceso al sistema](#acceso-al-sistema-por-hacer)
    -   [Manual de referencia](#manual-de-referencia-por-hacer)
    -   [Guía del operador](#guía-del-operador-por-hacer)
-   [Documentación del sistema](#documentación-del-sistema)
    -   [Especificación del sistema](#especificación-del-sistema)
    -   [Módulos](#módulos)
    -   [Plan de prueba](#plan-de-prueba)
        -   [Prueba de los módulos](#prueba-de-los-módulos)
            -   [MODULO PRINCIPAL](#modulo-principal)
            -   [MODULO SESIONES](#modulo-sesiones)
            -   [MODULO PRODUCTOS](#modulo-productos)
            -   [MODULO DESCUENTOS](#modulo-descuentos)
            -   [MODULO PEDIDOS/DEVOLUCIONES](#modulo-pedidos-devoluciones)
        -   [Prueba de integración](#prueba-de-integración)
        -   [Plan de pruebas de aceptación](#plan-de-pruebas-de-aceptación-por-hacer)
-   [Documentación del código fuente](#documentación-del-código-fuente-por-hacer)

---

<div id='usuario' />

# Documentación de usuario

Una vez ejecutado el programa, le pregutará con qué tipo de usuario desea acceder a la plataforma, siendo estos: Cliente, Administrador/Proveedor, Transportista;
una vez seleccionado esto, podrá crear un usuario del tipo seleccionado o iniciar sesión en uno ya existente. Una vez iniciado sesión y en función del tipo de usuario escojido, podrá navegar por los distintos menús.

MENÚ DE Cliente

Se le darán 6 opciones:

-   Perfil: Se le mostrará por pantalla sus credenciales y podrá modificarla si lo desea, incluido modificar su cartera

-   Productos: Esta opción permite al cliente realizar consultas de productos tanto por categoría como por nombre

-   Descuentos: Mediante esta opción el cliente podrá consultar todos los códigos promocionales y cheques regalo que tiene asignados

-   Pedidos: Mediante esta opción se le permite al cliente realizar pedidos controlando los códigos promocionales, así como comsultar el estado de cada uno de los productos de sus pedidos, por último, con el código de locker correspondiente podrá recoger sus productos del mismo.

-   Devoluciones: Con esta opción el cliente puede llevar a cabo devoluciones de productos así como realizar un seguimiento de las mismas

-   Salir del sistema: Con está opción vuelve al menú de acceso



MENÚ DE Admin

Se le darán 10 opciones:

-   Perfil: Se le mostrará por pantalla sus credenciales y podrá modificarla si lo desea

-   Clientes: Esta opción permite acceder a la información de los clientes dados de alta, en el correspondiente menú podrá realizar altas, bajas, búsquedas, listados y modificaciones de los clientes.

-   Proveedores: Esta opción permite acceder a la información de los proveedores dados de alta, en el correspondiente menú podrá realizar altas, bajas, búsquedas listados y modificaciones de los clientes.

-   Productos: Esta opción permite acceder a la información de los productos dados de alta, en el correspondiente menú podrá realizar altas, bajas, búsquedas listados y modificaciones de los productos.

-   Categorías: Esta opción permite acceder a la información de las categorías dados de alta, en el correspondiente menú podrá realizar altas, bajas, búsquedas listados y modificaciones de las categorías.

-   Pedidos: Esta opción permite acceder a la información de los productos dados de alta, en el correspondiente menú podrá realizar altas, bajas, búsquedas listados y modificaciones de los productos, además se podrá filtrar en los listados según el estado de los mismos, también se podrá asigmar a los transportistas los productos pedidos en función de la dirección del cliente y ciudad de reparto.

-   Transportista: Esta opción permite acceder a la información de los transportistas dados de alta, en el correspondiente menú podrá realizar altas, bajas, búsquedas listados y modificaciones de los transportistas.

-   Descuentos:Esta opción permite acceder a la información de los descuentos dados de alta, en el correspondiente menú podrá realizar altas, bajas, búsquedas listados y modificaciones de los descuentos, además podrá filtrar en los listados por clientes que tienen asignados alguno y los que han hecho uso de alguno.

-   Devoluciones: Esta opción permite acceder a la información de las devoluciones dados de alta, en el correspondiente menú podrá realizar altas, bajas, búsquedas listados y modificaciones de las devoluciones, también podrá consultar todas las devoluiones solicitadas, así como aceptar las mismas. Por supuesto también podrá cambiar el estado de los mismos a recibido.

-   Salir del sistema: Con está opción vuelve al menú de acceso.



MENU DE Proveedor

Se le darán 4 opciones:

-   Perfil: Se le mostrará por pantalla sus credenciales y podrá modificarla si lo desea.

-   Productos: Podrá  hacer desde aquí las mismas acciones que el administrador pero únicamente sobre los productos que él mismo suministra.

-   Pedidos: El usuario proveedor sólo podrá acceder únicamnete a la información de los pedidos de los productos que él mismo suministra, así como gestionar el estado de los productos, asignar transportistas, lockers, etc.

-   Salir del sistema: Con está opción vuelve al menú de acceso.


MENU DE Transportista

Se le darán 4 opciones:

-   Perfil: Se le mostrará por pantalla sus credenciales y podrá modificarla si lo desea.

-   Repartos: Podrá consultar la lista de productos que tiene asignados para su entrega

-   Retornos: Podrá consultar los pedidos en lockers caducados que tenga pendientes

-   Salir del sistema: Con está opción vuelve al menú de acceso.


Debe cerrar el programa correctamente para que se guarden los datos.


<div id='funcional' />

## Descripción funcional

El objetivo de esta práctica es realizar la implementación de una versión simplificada de una aplicación, similar a la archiconocida páginaweb  _Amazon_, en la que se permite comprar y vender(en el caso de los proveedores) productos, hacer uso de lockers y devoluciones.

El sistema dispondrá de 4 perfiles de usuarios:

-   Un perfil de cliente, que podrá realizar todo lo mencionado en la sección MENU DE cliente.
-   Un perfil de administrador, que podrá realizar todo lo mencionado en la sección MENU DE administrador.
-   Un perfil de proveedor, que podrá realizar todo lo mencionado en la sección MENU DE proveedor.
-   Un perfil de transportista, que podrá realizar todo lo mencionado en la sección MENU DE transportista.

<div id='tecnología' />

## Tecnología

-   [Vscode](https://code.visualstudio.com/)
-   [Clion](https://www.jetbrains.com/clion/)
-   [GitHub](https://github.com/)
-   [Git](https://git-scm.com/)

<div id='instalación' />

## Manual de instalación

Ya que es un programa .exe portable, no hace falta instalación, por lo que los siguientes pasos serán para ejecutarlo por código fuente

1. Instale un compilador de C así como una interfaz
2. Descomprima MP-2024-C7-G2.zip
3. Haga click derecho en la carpeta MP-2024-C7-G2 y seleccione "Abrir con" y seleccione su interfaz
4. Una vez ahi, simplemente ejecute el programa como proyecto

<div id='acceso' />

## Acceso al sistema

Una vez ejecutado el programa, le preguntará si desea iniciar sesión o registrarse, una vez seleccione le mmostrará un menú para que seleccione con qué tipo de usuario quiere iniciar sesión o registrarse, según su anterior elección, una vez iniciado sesión, se le mostrarán diferentes opciones en función del tipo de usuario, pudiendo así acceder de un menú a otro.

Para salir correctamente, debe introducir la opción que muestre el menú 

<div id='referencia' />

## Manual de referencia

VENTAJAS

-   Permite acceder a miles de productos
-   Permite recoger esos productos en Lockers
-   Permite la devolución de los productos comprados
-   Permite a los proveedores llegar a muchos clientes


ERRORES FRECUENTES

-   Los ficheros, deben contener un \n al final y ninguno al principio.
-   Si un fichero está vacío sólo debe tener una única línea.
-   Para volver salir del programa tienes que acceder al menú principal y pulsar 0.
-   En algunos equipos, no se reconocen las tildes.

<div id='operador' />

## Guía del operador

MENÚ DE ADMINISTRADOR

Para acceder a un usuario administrador deberá crearlo previamente, recuerde que para ello, en empresa debe de introducir "ESIZON" tras esto y el inicio de sesión, se le mostrará el siguiente menú:

MENÚ DE Admin

Se le darán 10 opciones:

-   Perfil: Se le mostrará por pantalla sus credenciales y podrá modificarla si lo desea

-   Clientes: Esta opción permite acceder a la información de los clientes dados de alta, en el correspondiente menú podrá realizar altas, bajas, búsquedas, listados y modificaciones de los clientes.

-   Proveedores: Esta opción permite acceder a la información de los proveedores dados de alta, en el correspondiente menú podrá realizar altas, bajas, búsquedas listados y modificaciones de los clientes.

-   Productos: Esta opción permite acceder a la información de los productos dados de alta, en el correspondiente menú podrá realizar altas, bajas, búsquedas listados y modificaciones de los productos.

-   Categorías: Esta opción permite acceder a la información de las categorías dados de alta, en el correspondiente menú podrá realizar altas, bajas, búsquedas listados y modificaciones de las categorías.

-   Pedidos: Esta opción permite acceder a la información de los productos dados de alta, en el correspondiente menú podrá realizar altas, bajas, búsquedas listados y modificaciones de los productos, además se podrá filtrar en los listados según el estado de los mismos, también se podrá asigmar a los transportistas los productos pedidos en función de la dirección del cliente y ciudad de reparto.

-   Transportista: Esta opción permite acceder a la información de los transportistas dados de alta, en el correspondiente menú podrá realizar altas, bajas, búsquedas listados y modificaciones de los transportistas.

-   Descuentos:Esta opción permite acceder a la información de los descuentos dados de alta, en el correspondiente menú podrá realizar altas, bajas, búsquedas listados y modificaciones de los descuentos, además podrá filtrar en los listados por clientes que tienen asignados alguno y los que han hecho uso de alguno.

-   Devoluciones: Esta opción permite acceder a la información de las devoluciones dados de alta, en el correspondiente menú podrá realizar altas, bajas, búsquedas listados y modificaciones de las devoluciones, también podrá consultar todas las devoluiones solicitadas, así como aceptar las mismas. Por supuesto también podrá cambiar el estado de los mismos a recibido.

-   Salir del sistema: Con está opción vuelve al menú de acceso.


<div id='sistema' />

# Documentación del sistema

<div id='requisitos' />

## Especificación del sistema

-   Poseer un ordenador con Windows
-   Tener una interfaz instalado con compilador incluido
-   Tener el código fuente del programa o bien el ejecutable y los ficheros .txt en la carpeta del programa

<div id='módulos' />

## Módulos

El proyecto se divide en 4 módulos:

MODULO PRINCIPAL 

Este módulo tiene un único objetivo, unir el resto de módulos, así como llamar al resto de funciones que necesite

MODULO SESIONES 

Este módulo es el encargado de gestionar los ficheros clientes.txt, adminprov.txt y todas las funciones relacionadas con los mismos. Este permite listar usuarios, editarlos y eliminarlos, ya sea, como un administrador (tendrá acceso a todos los tipos de usuarios del sistema)o como un cliente, transportista  o proveedor(podiendo interactuar únicamente con su propia información).

MODULO PRODUCTOS 

Este módulo es el encargado de gestionar los ficheros productos.txt y categorías.txt y todas las funciones relacionadas con los mismos. Permitiendo así dar de alta y baja productos, así como categorías, listarlos con filtros e incluso buscarlos por nombre.

MODULO DESCUENTOS 

Este módulo es el encargado de gestionar los fichero descuentos.txt y descuentos_clientes.txt así como todas las funciones relacionadas con los mismos, Permitiendo así crear códigos promocionales y cheques regalo para su uso en los diferentes productos, también permite funciones de listado de los mismos.

<div id='pruebas' />

## Plan de prueba

### Prueba de los módulos
### MODULO PRINCIPAL
#### Pruebas de caja negra del módulo principal

### MODULO SESIONES
#### Pruebas de caja negra del módulo sesiones

### MODULO PRODUCTOS
#### Pruebas de caja negra del módulo productos

##### PROCEDIMIENTO OBTENER DATO

Cabecera: static void obtener_dato_f(FILE **f,char *n)

Precondicion: El tamaño de n debe ser mayor al dato que se debe introducir, f debe estar abierto en modo lectura y el cursor debe estar situado al principio del dato a leer

Poscondicion: Almacena en n los caracteres leidos en f hasta que se encuentre '-' o '\n' o EOF y deja el cursor una posicion despues del dato leido

DATOS DE ENTRADA: doble puntero a tipo FILE, puntero a char 

DATOS DE SALIDA: ninguno, sólo modifica el puntero a char 

CASO 1 

    Al ejecutarla, vuelca en el puntero a char un campo concreto de la información en el fichero


static void suma1(char *s,int i); suma 1 a una cadena
static void lista_cat();     
static void lista_prod();
static int cadena_valida(char *v); si la cadena tiene - y quita /n
static void quitaenter(char *);     quitar /n y sustituye por /0
static void lista_prod_asoc(int *asoc,int tamanio_asoc); 
static void listado_prod();
static void listado_prod_asoc(int *asoc,int tamanio_asoc);  //compacto
static void baja_producto(int *asoc,sesion ses,int tamanio_asoc);
static void borrar_producto(int indice);
static void modificar_producto(sesion ses,int *asoc,int tamanio_asoc);
static void menu_modificar_producto (int indice);
static void listado_cat();  //compacto
static void modificar_categoria();

//Cabecera: void menu_cliente_prod (producto **p,categoria **c,int *tamanio_p, int *tamanio_c);
//Precondicion: p y c deben estar previamente definidos mediante las funciones volcar_producto y volcar_categoria
//Poscondicion: Muestra en pantalla el menu de productos para el cliente
void menu_cliente_prod ();
//Cabecera: void menu_adminprov_prod (producto **p,categproa *c,int *tamanio_p,int tamanio_c,sesion ses)
//Precondicion: sesion debe ser un administrador o proveedor y estar registrado en el sistema
//Poscondicion: Muestra en pantalla el menu de productos para el administrador o proveedor y muestra los productos asociados a esa sesion
void menu_adminprov_prod (sesion ses);
//Cabecera: producto * volcar_producto()
//Precondicion: 
//poscondicion: Vuelca todos la informacion de los productos en el fichero "Productos.txt", devolviéndolo en un array
void cargar_producto();
//Cabecera: void guardar_producto(producto *v)
//Precondicion: v debe de ser una cadena de tipo producto definida de forma dinámica
//Poscondición: Guarda todos los miembros de producto en el fichero "Productos.txt"
void guardar_producto();
//Cabecera: categoria * guardar_categoria()
//Precondicion: 
//Poscondición: Guarda todos los miembros de categoria en el fichero "Categorias.txt"
void guardar_categoria();
//Cabecera: void volcar_categoria(categoria *v)
//Precondicion: v debe de ser una cadena de tipo categoria definida de forma dinamica
//Poscondicion: Vuelca toda la informacion de las categorias en el fichero "Categorias.txt", devolviendolo en un array
void cargar_categoria();
//Cabecera: void alta_producto(char *id,producto *v)
//Precondicion: El usuario actual debe ser administrador/proveedor.
//Poscondicion: Lee todos los campos de producto por teclado y los escribe al final del vector,
//otorgandole la proxima id disponible
void alta_producto();
//Cabecera: void mod_prod(producto)
//Precondicion: producto.id_prod=id del producto a modificar
//Poscondicion: Cambia los datos del producto con id producto.id_prod
void mod_prod(producto);
//Cabecera: void Busqueda_prod_nombre(char *nombre)
//Precondicion: nombre debe ser una cadena ya definida
//Poscondicion: Escribe por pantalla todos los productos cuyo nombre coincida con n
void Busqueda_prod_nombre(char *n);
//cabecera: void Busqueda_prod_cat(char *id)
//Precondicion: id debe pertenecer a una categoria
//Poscondicion: Escribe por pantalla todos los productos 
//que pertenecen a la categoria con identificador id
void Busqueda_prod_cat(char *id);
//Cabecera: alta_categoria(categoria *v)
//Precondicion: v es un vector definido de forma dinamica que contiene todas las categorias registradas
//Poscondicion: Introduce en el vector v una nueva categoria cuya descripcion es introducida por teclado
//y cuya id es la proxima disponible
void alta_categoria(); 
//Cabecera: void baja_categoria(categoria **c,int *tamanio_c);
//Precondicion: El usuario actual debe ser administrador
//Poscondcion: Borra la categoria que especifique el usuario y ajusta el vector de acuerdo a ello
void baja_categoria();
//Cabecera: void idacat(char *descrip,categoria *c,char *id)
//Precondicion: id deben ser 4 "digitos" sin signo, terminado en '\0'. No puede ser "0000"
//Poscondicion: Devuelve en descrip v.descripcion del elemento de v cuya id coincida con v.id_cat.
//Si no se encuentra, se devuelve en descrip "-\0";
int idacat(char *descrip,char *id);
//Cabecera: cataid(char *id,categoria *c,char *descrip,int tamanio)
//Precondicion: descrip debe estar definido y tener 51 elementos, el final de la cadena debe terminar en '\0'
//Poscondicion: Devuelve en id la c.id_cat de la categoria cuyo c.descrip coincida con descrip.
void cataid(char *id,char *descrip);
//Cabecera: menu_admin_cat();
//Precondicion: El usuario actual debe ser un administrador
//Poscondicion: Muestra por pantalla un menu el cual el usuario puede dar de alta, modificar o borrar cualquier categoria
void menu_admin_cat();

### MODULO DESCUENTOS
#### Pruebas de caja negra del módulo descuentos

##### crear_fichero _descuentos

 cabecera: void crear_fichero_descuentos()

 precondición: ninguna

 postcondición:crea el fichero descuentos.txt sino existe e imprime un mensaje de error si es el caso

CASO 1

    Al ejecutarla, crea el archivo descuentos.txt

##### crear_fichero_descuenros_clientes()

 cabecera: void crear_fichero_descuentos_clientes()

 precondición: ninguna

 postcondición:crea el fichero descuentos_clientes.txt sino existe e imprime un mensaje de error si es el caso

CASO 1

    Al ejecutarla, crea el archivo descuentos.txt

##### PROCEDIMIENTO CARGAR DESCUENTOS 

 cabecera:void carga_descuentos(Descuentos **d )

 precondición: recibe como doble puntero el vector de estructura

 postcondición: Carga del fichero descuentos.txt a un vector de estructuras del tipo indicado

DATOS DE ENTRADA: el vector de estructura Descuentos 

DATOS DE SALIDA: ninguno

CASO 1

    Al ejecutarla, carga los datos del .txt en el vector descuentos 

##### PROCEDIMIENTO CARGAR DESCUENTOS CLIENTES

 cabecera:void carga_descuentos_clientes(Descuentos_clientes **dc)

 precondición: recibe como doble puntero el vector de estructura

 postcondición: Carga del fichero descuentos.txt a un vector de estructuras del tipo indicado

DATOS DE ENTRADA: el vector de estructura Descuentos_clientes

DATOS DE SALIDA: ninguno

CASO 1

    Al ejecutarla, carga los datos del .txt en el vector descuentos_clientes

##### PROCEDIMIENTO VOLCADO DESCUENTOS
    
 cabecera: void volcado_descuentos(Descuentos **d)

 precondición:  recibe como doble puntero el vector de estructuras, inicializado

 postcondición: Vuelca el contenido del vector de estructuras al fichero descuentos.txt

DATOS DE ENTRADA: el vector de estructuras Descuentos

DATOS DE SALIDA: ninguno

CASO 1

    Al ejecutarla, vuelca desde el vector en el fichero la información sobre los descuentos

##### PROCEDIMIENTO VOLCADO DESCUENTOS CLIENTES
    
 cabecera: void volcado_descuentos(Descuentos_clientes **dc)

 precondición:  recibe como doble puntero el vector de estructuras, inicializado

 postcondición: Vuelca el contenido del vector de estructuras al fichero descuentos_clientes.txt

DATOS DE ENTRADA: el vector de estructuras Descuentos_clientes

DATOS DE SALIDA: ninguno

CASO 1

    Al ejecutarla, vuelca desde el vector en el fichero la información sobre los descuentos_clientes

##### PROCEDIMIENTO LISTAR DESCUENTOS

cabecera: void listar_descuentos(Descuentos *d,int *n_desc)

precondición: *d inicializado

postcondición: lista los descuentos actuales en el vector

DATOS DE ENTRADA: el vector de descuentos, así como un puntero que apunta al número total de descuentos

DATOS DE SALIDA: ninguno

CASO 1
    Al ejecutarla, imprime por pantalla la información básica de todos los descuentos actuales

##### PROCEDIMIENTO LISTAR DESCUENTOS CON ID

cabecera:void listar_descuentos_propios(char*Id_cliente)

precondición:sea Id cliente un punteroa  char que apunta a la información en la estructura

postcomdición: imprime por pantalla la lsita de descuentos asignados a esa ID de cliente 

DATOS DE ENTRADA: un puntero a char con la id de un cliente

DATOS DE SALIDA: ninguno, ya que sólo imprime por pantalla la información

CASO 1

    Al ejecutarla, imprime por pantalla la información básica de los descuentos asociados a esa id

CASO 2 

    Al ejecutarla, no encuentra la id correspondiente y, por tanto sólo imprime un mensaje de error 

##### FUCNIÓN COMPRIOBAR DESCUENTO


cabecera: int comprobar_descuento(Descuentos_clientes**dc,char Id_cod[])

precondición: **dc inicializado e Id_cod un código de descuento válido

postcondición: devuelve: 0 si está en vigor y 1 si no es válido por cualquier otra razón, además imprime por pantalla el error producido

DATOS DE ENTRADA: el vector de estructuras descuentos_clientes y una cadena con el código de un descuento existente

DATOS DE SALIDA: 0 si el desdcuento es válido y 1 sino lo es

CASO 1

    Al ejecutarla, el descuento introducido está en vigor y está activo, por lo que devuelve 0

CASO 2

    Al ejecutarla, el descuento introducido no está en vigor o bien no está activo, por lo que devuelve 1


##### PROCEDIMIENTO NUEVO DESCUENTO

cabecera: void nuevo_descuento(Descuentos **d ,Descuentos_clientes **dc, int *num_desc,int *num_desc_clien)

precondición: **d y **dc inicializados y num_desc y num_desc_clien son punteros que apuntan respectivamente al número de descuentos/descuentos_clientes que hay

postcondición: ninguna

DATOS DE ENTRADA: dos vectores de estructuras y dos punteros a enteros que indican el número de elemento de los mismos

DATOS DE SALIDA: ninguno, ya que sólo se carga la nueva información

CASO 1

    Al ejecutarla, permite introducir la información del nuevo descuento por teclado, pudiendo también elegir entre múltiples opciones para los parámetros de los descuentos


##### PROCEDIMIENTO MODIFICAR DESCUENTO

cabecera: modificar_descuento(Descuentos **d ,Descuentos_clientes **dc, int *num_desc , int *num_desc_clien);

precondición: **d y **dc inicializados y num_desc y num_desc_clien son punteros que apuntan respectivamente al número de descuentos/descuentos_clientes que hay

postcondición: ninguna

DATOS DE ENTRADA: dos vectores de estructuras y dos punteros a enteros que indican el número de elemento de los mismos

DATOS DE SALIDA: ninguno, ya que sólo se modifica y actualiza a la nueva información ambos vectores

CASO 1

    Al ejecutarla, nos permite, en una estructura selctiva elgir la información  de un descuento ya existente

##### PROCEDIMIENTO FECHA ACTUAL

cabecera: void fecha_actual(char fecha_act[11])

precondición: fecha_act una cadena de 11 caracteres

postcondición: ninguna, ya que modifica la cadena que se le pasa por parámetro

DATOS DE ENTRADA: una cadena de 11 caracteres, si bien sólo se usará como puntero para modificarla

DATOS DE SALIDA: ninguna

CASO 1

    Al ejecutarla, modifica la cadena de caracteres e introduce la fecha actual en formato: dd/mm/aaaa  (día/mes/año)

##### FUNCIÓN DE CADENA A FECHA

cabecera: fecha de_string_a_fecha(char *cadena)

precondición: cadena inicializada con una fecha válida

postcondición: convierte cadena en una fecha y lo devuelve

DATOS DE ENTRADA: una cadena de 11 caracteres

DATOS DE SALIDA: la fecha de la cadena en la estructura fecha

CASO 1

    Al ejecutarla, nos devuelve una estructura fecha inicializada con la fecha de la cadena

##### FUNCION COMPARAR FECHAS

cabecera: int comparar_fechas(fecha fecha1, fecha fecha2)
precondicion: fecha1 y fecha2 inicializados
postcondicion: devuelve => =0 - fechas iguales
                           >0 - fechas1 mayor que fecha2
                           <0 - fecha1 menor que fecha2

DATOS DE ENTRADA: dos fechas en su tipo correspondiente

DATOS DE SALIDA: 0 si ambas son iguales, > a 0 si la primera es mayor a la segunda y < a 0 si es al revés

CASO 1

    Al ejecutarla fecha1 es la misma que fecha2, por lo que el programa devuelve 0 (12/05/2024=12/05/2024)

CASO 2

    Al ejecutarla, fecha1 es posterior a fecha2, por lo que el programa devuelve 1 (12/05/2024>03/03/1945)

CASO 3

    Al ejecutarla, fecha1 es anterior a fecha2, por lo que el programa devuelve -1 (12/05/2024<10/01/2030)


##### PROCEDIMIENTO LEER CADENA

cabecera: void leer_string(char * cadena, int elem)

precondición: ninguna

postcondición: lee en cadena la cadena introducida por el usuario

DATOS DE ENTRADA: un puntero a char que funciona como cadena y el número de elementos que se deseaan leer

DATOS DE SALIDA: ninguno ya que modifica el parámetro puntero a char que recibe

CASO 1

    Al ejecutarla, permite introducir por teclado una cadena de elem-1 elementos

##### FUNCIÓN NÚMERO DE DESCUENTOS DESDE FICHERO

cabecera:int num_desc_desde_fich()

precondición: archivo .txt inicializado, preferiblemente hacer volcado antes de ejecutarla

postcondición:devuelve el número de líneas que tiene el fichero

DATOS DE ENTRADA: niguno

DATOS DE SALIDA: el número de descuentos que hay en el fichero 

CASO 1

    Al ejecutarla, devuelve el descuentos que hay dados de alta en el fichero, en este caso, 5

##### FUNCIÓN NÚMERO DE DESCUENTOS_CLIENTE DESDE FICHERO

cabecera:int num_desc_clien_desde_fich()

precondición: archivo .txt inicializado, preferiblemente hacer volcado antes de ejecutarla

postcondición:devuelve el número de líneas que tiene el fichero

DATOS DE ENTRADA: niguno

DATOS DE SALIDA: el número de descuentos que hay en el fichero 

CASO 1

    Al ejecutarla, devuelve el descuentos que hay dados de alta en el fichero, en este caso, 12

##### FUNCIÓN INDICE A PARTIR DE ID DE DESCUENTO


cabecera:int indice_con_id_descuentos(Descuentos **vector_descuentos,char*id_desc,int num_desc)

precondición: vector cliente un vector de estructura descuentos, id_desc una cadena y num_desc el número de descuentos registrados del vector

postcondición: devuelve el valor del indice del vector de estructura cuya id coincide con el de la cadena

DATOS DE ENTRADA: vector de estructuras descuentos, id del descuento, número de descuentos

DATOS DE SALIDA: índice de esa id en el vector de estructras descuentos

CASO 1:

    Al ejecutarla, devuelve la posición en el vector de esa id, en este caso el 4

CASO 2: 

    Al ejecutarla, devuelve -1, ya que la id introducida no existe

##### FUNCIÓN INDICE A PARTIR DE ID DE DESCUENTO EN DESCUENTOS_CLIENTES


cabecera:int indice_con_id_descuentos_clien(Descuentos_clientes **vector_descuentos_cl,char*id_desc,int num_desc_cl)

precondición: vector cliente un vector de estructura descuentos_clientes, id_desc una cadena y num_desc el número de descuentos_clientes registrados del vector

postcondición: devuelve el valor del indice del vector de estructura cuya id coincide con el de la cadena

DATOS DE ENTRADA: vector de estructuras descuentos_clientes, id del descuento, número de descuentos_clientes

DATOS DE SALIDA: índice de esa id en el vector de estructras descuentos_clientes

CASO 1:

    Al ejecutarla, devuelve la posición en el vector de esa id, en este caso el 8

CASO 2: 

    Al ejecutarla, devuelve -1, ya que la id introducida no existe

##### PROCEDIMIENTO BORRAR DESCUENTO CON ID

 cabecera: void borrar_descuento_con_id(Descuentos**vector_descuento,Descuentos_clientes**dc,char *Id_descuento, int *n_descuento,int*n_descuento_cl){

 precondición: vectores a estructuras inicializadas, id de descuento válida y n_descuento y n_descuento_cl elementos de los respectivos vectores de estructuras

 postcondición: borra el descuento con la id introducida

DATOS DE ENTRADA: vectores de estructuras descuentos y descuentos_clientes, su número de elementos y la id de un descuento

DATOS DE SALIDA: ninguno

CASO 1

        Al ejecutarla, borra de ambos vectores el descuento con la id introducida

#### Prueba de caja blanca del módulo descuentos
##### PRUEBAS SOBRE EL PROCEDIMIENTO BORRAR DESCUENTO

CÓDIGO:

    void borrar_descuento_con_id(Descuentos **vector_descuento, Descuentos_clientes **dc,char *Id_descuento, int *n_descuento,int *n_descuento_cl){
    int i,aux,aux2;
    aux=*n_descuento;
    aux2=*n_descuento_cl;           //1 asignaciones

    if(aux==1){                     //2   si
        free(vector_descuento);
        *n_descuento=0;
        free(dc);
        *n_descuento_cl=0;
        aux++;
    }else{                          //3   si_no
        i=indice_con_id_descuento(vector_descuento,Id_descuento,aux)+1;
        if(i==-1){                     //4     si2
            printf("la id no existe\n");

        }else{                          //5        sino2
    for(i;i<aux;i++)                    //6        bucle for1
        (*vector_descuento)[i-1]=(*vector_descuento)[i];   
                                                        //7fin for1
    for(i=indice_con_id_descuento_cl(dc,Id_descuento,aux2)+1;i<aux;i++) //8 bucle for2    
        (*dc)[i-1]=(*dc)[i];
                                        //9 fin for2
        }                              //10 fin si2
    }                               //11 fin si 
    (*n_descuento)=aux-1;   //12 fin 
}


![Grafo de control de flujo del procedimiento](GCF_Descuentos.png "Grafo de control de flujo del procedimiento")

Complejidad computacional

V(G) = número de regiones = 6

Luego las seis rutas linealmente independientes serían: 

•	Ruta 1 (aquella en la que se llega a ejecutar todo): 

             1-2-3-4-5-6-7-6-8-9-8-10-11-12

•	Ruta 2 (no se cumple la condición del segundo bucle y no hace la operación en el for 2):

             1-2-3-4-5-6-7-6-8-10-11-12

•	Ruta 3 (no se cumple la condición del primer bucle y no hace la operación en el for 1): 

             1-2-3-4-5-6-8-9-8-10-11-12

•	Ruta 4 (no se cumplen ninguna de las condiciones de los dos bucles for ):

             1-2-3-4-5-6-8-10-11-12

•	Ruta 5 (se cumple la condición del segundo if): 

             1-2-3-4-10-11-12

•	Ruta 6 (Se cumple la condición del primer if):

            1-2-11-12


Ruta 1

Si tenemos 3 descuentos y 3 descuentos clientes, por lo que cada vector tiene 3 posiciones o espacios, con la siguiente información:

vector_descuentos[0].id_desc= black001              vector_descuentos_clientes[0].id_cod= black001

vector_descuentos[1].id_desc= black002              vector_descuentos_clientes[1].id_cod= black002

vector_descuentos[2].id_desc= black003              vector_descuentos_clientes[2].id_cod= black003

Si la cadena que pasamos por parámetro es "black003", comprobamos que lo borra de manera correcta de ambos vectores, primero encontrando su posición en el vector y luego copiando todos los siguientes una posición antes.

Ruta 2

Si tenemos 3 descuentos y 3 descuentos clientes, por lo que cada vector tiene 3 posiciones o espacios, con la siguiente información:

vector_descuentos[0].id_desc= black001              vector_descuentos_clientes[0].id_cod= black001

vector_descuentos[1].id_desc= black002              vector_descuentos_clientes[1].id_cod= black002

vector_descuentos[2].id_desc= black003              vector_descuentos_clientes[2].id_cod= black003


Si la cadena que pasamos por parámetro es "black003", comprobamos que lo borra de manera correcta de ambos vectores, primero encontrando su posición en el vector y luego, no llega a entrar en el bucle porque es el último elemento.


Ruta 3

Si tenemos 1 descuentos y 3 descuentos clientes, por lo que cada vector tiene 3 posiciones o espacios, con la siguiente información:

vector_descuentos[0].id_desc= black001              vector_descuentos_clientes[0].id_cod= black001

                                                    vector_descuentos_clientes[1].id_cod= black002

                                                    vector_descuentos_clientes[2].id_cod= black003



Si la cadena que pasamos por parámetro es "black001", comprobamos que lo borra de manera correcta de ambos vectores entrando únicamente en el segundo bucle.

Ruta 4 

Si tenemos 1 descuentos y 1 descuentos clientes, por lo que cada vector tiene 3 posiciones o espacios, con la siguiente información:

vector_descuentos[0].id_desc= black001              vector_descuentos_clientes[0].id_cod= black001

Si la cadena que pasamos por parámetro es "black001", comprobamos que lo borra de manera correcta de ambos vectores y sin entrar en ningún bucle

Ruta 5

Si tenemos 3 descuentos y 3 descuentos clientes, por lo que cada vector tiene 3 posiciones o espacios, con la siguiente información:

vector_descuentos[0].id_desc= black001              vector_descuentos_clientes[0].id_cod= black001

vector_descuentos[1].id_desc= black002              vector_descuentos_clientes[1].id_cod= black002

vector_descuentos[2].id_desc= black003              vector_descuentos_clientes[2].id_cod= black003

Si la cadena que pasamos por parámetro es "black004", descuento inexistente, comprobamos que imprime por pantalla el error y salta al final de la función

Ruta 6

Si tenemos 1 descuentos y 1 descuentos clientes, por lo que cada vector tiene 3 posiciones o espacios, con la siguiente información:

vector_descuentos[0].id_desc= black001              vector_descuentos_clientes[0].id_cod= black001

Si la cadena que pasamos por parámetro es "black001", elimininará, liberando la memoria de los vectores el dato



### MODULO PEDIDOS DEVOLUCIONES
#### Pruebas de integración de caja negra del módulo pedidos devoluciones


void carga_devoluciones( Devoluciones **dev ,int *n_dev);
void volcado_devoluciones ( Devoluciones *d, int *n_dev );

void crear_devolucion( Pedido *ped, ProductoPedido *prod_ped, Devoluciones **dev, int *n_dev, int *n_pedidos, int *n_prod_ped );
void eliminar_devolucion ( Devoluciones *dev , int indice_dev);

void menu_devoluciones ( Pedido *ped, ProductoPedido *prod_ped, Devoluciones *dev, int *n_dev, int *n_pedidos, int *n_prod_ped, usu tipo_usu );

void menu_devoluciones_clientes ( Pedido *ped, ProductoPedido *prod_ped, Devoluciones *dev, int *n_dev, int *n_pedidos, int *n_prod_ped, char id_cliente[7], usu tipo_u);
void menu_devoluciones_admin ( Pedido *ped, ProductoPedido *prod_ped, Devoluciones *dev, int *n_dev, int *n_pedidos, int *n_prod_ped, usu tipo_u);
void menu_devoluciones_transportistas ( Pedido *ped, ProductoPedido *prod_ped, Devoluciones *dev, int *n_dev, int *n_pedidos, int *n_prod_ped,char id_transp[5], usu tipo_u);

void carga_lockers( Locker **lock ,int *);
void carga_compartimento_lockers( CompartimentoLocker **c_lock ,int *n_c_lock);

void volcado_lockers ( Locker *l, int *n_lock );
void volcado_comp_lockers ( CompartimentoLocker *c_l, int *n_c_lock );


void fecha_actual( char fecha_act[11]);

void carga_pedidos( Pedido **ped ,int *n_ped);
void carga_prod_pedido( ProductoPedido **pr_ped ,int *n_pr_ped);

void volcado_pedidos ( Pedido *p, int *n_ped );
void volcado_prod_pedidos ( ProductoPedido *pr_p, int *n_pr_ped );

void eliminar_pedido ( Pedido *ped, int indice_ped);
void crear_pedido ( Pedido **ped, int *n_ped , char usu_act[8] );
void modificar_pedido ( Pedido *ped , ProductoPedido *pr_ped, int *n_ped ,int *n_pr_ped, int indice ,usu tipo_usu, char usu_act[8] );
void recoger_pedido( Pedido *ped , ProductoPedido *prod_ped, int *n_pedidos,int *n_pr_ped, char id_cliente[8] , int opcion_pedido , usu tipo_usu );

//void asignar_transportista( Pedido *ped ,ProductoPedido *prod_ped, Transportista *transp, int *n_transp,  int *n_pedidos , int *n_pr_ped , usu tipo_usu , int indice_p , char prov_cliente[21] );
//void asignar_locker( Pedido *ped ,ProductoPedido *prod_ped, Locker *lock, int *n_lock, int *n_pedidos , int *n_pr_ped , usu tipo_usu , int indice_p , char prov_cliente[21] );

void crear_siguiente_id ( int num_digitos, char vect_dest[num_digitos] , char vect_id[num_digitos]);

void menu_pedidos ( Pedido *ped , ProductoPedido *prod_ped ,int *n_pedidos ,int *n_prod_ped, usu tipo_usu );

void menu_pedidos_clientes(Pedido *ped , ProductoPedido *prod_ped, int *n_pedidos, int *n_prod_ped, char id_cliente[8] , usu tipo_usu );
void menu_pedidos_admin(Pedido *ped , ProductoPedido *prod_ped, int *n_pedidos, int *n_pr_ped , usu tipo_usu);
void menu_pedidos_prov(Pedido *ped , ProductoPedido *prod_ped, int *n_pedidos , usu tipo_usu);
void menu_pedidos_transp(Pedido *ped , ProductoPedido *prod_ped, int *n_pedidos , int *n_pr_ped, char id_tr_act[5], usu tipo_usu);

void menu_prod_ped( Pedido *ped, ProductoPedido *pr_p, int *n_ped,int *n_pr_ped , char id_ped[8] ,char id_cliente[8],usu tipo_usu);


