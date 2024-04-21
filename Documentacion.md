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

Este módulo tiene dos objetivos principalmente:

Por un lado, es el encargado de gestionar el inicio de sesión para poder acceder al menú. Y, por otro lado, es el encargado de unir el resto de módulos mediante los diferentes menús que permiten usar las diferentes funciones de los otros módulos.

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

