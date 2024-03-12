#include <stdio.h>
#include "descuentos.h"
void crear_fichero_descuentos();

int main(){   //main para pruebas, quitar a la hora de unir los módulos
crear_fichero_descuentos;
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
