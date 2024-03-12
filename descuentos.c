/*##### MÓDULO DESCUENTOS   #####*/
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>

#include "descuentos.h"

//Tipos 
typedef struct fecha{
    int dia, mes, anno;
}fecha;

void crear_fichero_descuentos();
void crear_fichero_descuentos_clientes();

int main(){   //main para pruebas, quitar a la hora de unir los módulos
crear_fichero_descuentos;
crear_fichero_descuentos_clientes;
return 0;
}


//cabecera: crear_fichero_descuentos()
//preconción: ninguna
//postconción: crea el fichero descuentos
void crear_fichero_descuentos()
{
    FILE* f;
    if ((f = fopen("../Descuentos/descuentos.txt", "w")) == NULL)
        printf("Error al abrir el archivo\n");
    fclose(f);
}
//cabecera: crear_fichero_descuentos_clientes()
//preconción: ninguna
//postconción: crea el fichero descuentos
void crear_fichero_descuentos_clientes()
{
    FILE* f;
    if ((f = fopen("../Descuentos/descuentos_clientes.txt", "w")) == NULL)
        printf("Error al abrir el archivo\n");
    fclose(f);
}






// cabecera: fecha fecha_actual()
// precondición: ninguna
// postcondición: devuelve una estructura fecha con la fecha actual
fecha fecha_actual()
{ // FUNCIONA
    fecha fecha_actual;
    time_t t = time(NULL);
    struct tm tiempo_actual = *localtime(&t);

    // Pasamos los datos desde la estructura tm a fecha
    fecha_actual.dia = tiempo_actual.tm_mday;
    fecha_actual.mes = tiempo_actual.tm_mon + 1;
    fecha_actual.anno = tiempo_actual.tm_year + 1900;

    return fecha_actual;
}

/*POR HACER 
    Función que compare fechas(para comparar la caducidad de los descuentos)
    Función que inicialice cada uno de los tipos(2) 
    Función que convierta de cadena de 11 carácteres al tipo fecha para poder compararlo con la actual y a la inversa
    Función que compruebe si el descuento está vigente
    --más funciones en adelante--
*/