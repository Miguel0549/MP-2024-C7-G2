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

#### Pruebas de caja negra del módulo principal

#### Pruebas de caja negra del módulo sesiones

#### Pruebas de caja negra del módulo productos

##### PROCEDIMIENTO OBTENER DATO

Cabecera: static void obtener_dato_f(FILE **f,char *n)

Precondicion: El tamaño de n debe ser mayor al dato que se debe introducir, f debe estar abierto en modo lectura y el cursor debe estar situado al principio del dato a leer

Poscondicion: Almacena en n los caracteres leidos en f hasta que se encuentre '-' o '\n' o EOF y deja el cursor una posicion despues del dato leido

DATOS DE ENTRADA: doble puntero a tipo FILE, puntero a char 

DATOS DE SALIDA: ninguno, sólo modifica el puntero a char 

CASO 1 

Al ejecutarla, vuelca en el puntero a char un campo concreto de la información en el fichero

##### FUNCIÓN  BUSCAR ID EN FICHERO

Cabecera: int buscar_id (FILE *f,char *n)

Precondicion: f debe ser F_PRODUCTO o F_CATEGORIAS y estar abierto para lectura

Poscondicion: Devuelve la id de n dentro del fichero

DATOS DE ENTRADA: puntero a FILE y puntero a char 

DATOS DE SALIDA: devuleve la id 

static int buscar_id_f(FILE **f,char *n);
static void suma1(char *s,int i);
static void lista_cat();
static void lista_prod();
static int cadena_valida(char *v);
static void quitaenter(char *);
static void lista_prod_asoc(int *asoc,int tamanio_asoc);
static void listado_prod();
static void listado_prod_asoc(int *asoc,int tamanio_asoc);
static void baja_producto(int *asoc,sesion ses,int tamanio_asoc);
static void borrar_producto(int indice);
static void modificar_producto(sesion ses,int *asoc,int tamanio_asoc);
static void menu_modificar_producto (int indice);
static void listado_cat();
static void modificar_categoria();



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

ostcondición:crea el fichero descuentos_clientes.txt sino existe e imprime un mensaje de error si es el caso

CASO 1

    Al ejecutarla, crea el archivo descuentos.txt

##### PROCEDIMIENTO CARGAR DESCUENTOS 

 cabecera:void carga_descuentos(Descuentos **d )

 precondición: recibe como doble puntero el vector de estructura

 postcondición: Carga del fichero descuentos.txt a un vector de estructuras del tipo indicado

DATOS DE ENTRADA: el vector de estructura Descuentos 

DATOS DE SALIDA: ninguno

CASO 1:

    Al ejecutarla, carga los datos del .txt en el vector descuentos 

##### PROCEDIMIENTO CARGAR DESCUENTOS CLIENTES

 cabecera:void carga_descuentos_clientes(Descuentos_clientes **dc)

 precondición: recibe como doble puntero el vector de estructura

 postcondición: Carga del fichero descuentos.txt a un vector de estructuras del tipo indicado

DATOS DE ENTRADA: el vector de estructura Descuentos_clientes

DATOS DE SALIDA: ninguno

CASO 1:

    Al ejecutarla, carga los datos del .txt en el vector descuentos_clientes

##### PROCEDIMIENTO VOLCADO DESCUENTOS
    
 cabecera: void volcado_descuentos(Descuentos **d)

 precondición:  recibe como doble puntero el vector de estructuras, inicializado

 postcondición: Vuelca el contenido del vector de estructuras al fichero descuentos.txt

DATOS DE ENTRADA: el vector de estructuras Descuentos

DATOS DE SALIDA: ninguno

CASO 1:

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

    Al ejecutarla, permite modificar la información  de un descuento ya existente




    void fecha_actual();
    fecha de_string_a_fecha(char*);
    int comparar_fechas(fecha,fecha);
    void crear_fichero_descuentos();
    void crear_fichero_descuentos_clientes();
    void leer_string(char*,int);
    int num_desc_desde_fich();
    int num_desc_clien_desde_fich();
    int indice_con_id_descuento(Descuentos**,char*,int);
    int indice_con_id_descuento_cl(Descuentos_clientes**,char*,int);
    void borrar_descuento_con_id(Descuentos**,Descuentos_clientes**,char*,int *,int*);




