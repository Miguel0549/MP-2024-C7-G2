/*##### MÓDULO DESCUENTOS   #####*/
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>
#include "descuentos.h"
#define LINE 100

Descuentos convertir_cadena_a_Descuentos(char*);
//Tipos 
typedef struct fecha{
    int dia, mes, anno;
}fecha;
void crear_fichero_descuentos();
void crear_fichero_descuentos_clientes();

int main(){   //main para pruebas, quitar a la hora de unir los módulos
Descuentos *d;
int n=0,*p;
p = &n;
crear_fichero_descuentos();
//crear_fichero_descuentos_clientes;
carga_descuentos(&d,p);

printf("Id: %s\n",d[0].Id_cod);
return 0;
}


//cabecera: crear_fichero_descuentos()
//preconción: ninguna
//postconción: crea el fichero descuentos
void crear_fichero_descuentos()
{
    FILE* f;
    if ((f = fopen("descuentos.txt", "a+")) == NULL)
        printf("Error al abrir el archivo\n");
    fclose(f);
}
//cabecera: crear_fichero_descuentos_clientes()
//preconción: ninguna
//postconción: crea el fichero descuentos_clientes
void crear_fichero_descuentos_clientes()
{
    FILE* f2;
    if ((f2 = fopen("../Descuentos/descuentos_clientes.txt", "w")) == NULL)
        printf("Error al abrir el archivo\n");
    fclose(f2);
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



// cabecera: int comparar_fechas(fecha fecha1, fecha fecha2)
// precondicion: fecha1 y fecha2 inicializados
// postcondicion: devuelve => =0 - fechas iguales
//                            >0 - fechas1 mayor que fecha2
//                            <0 - fecha1 menor que fecha2
int comparar_fechas(fecha fecha1, fecha fecha2)
{ // FUNCIONA
    int resultado = 0;
    if (fecha1.anno == fecha2.anno)
        if (fecha1.mes == fecha2.mes)
            if (fecha1.dia == fecha2.dia)
                resultado = 0;
            else if (fecha1.dia > fecha2.dia)
                resultado = 1;
            else
                resultado = -1;

        else if (fecha1.mes > fecha2.mes)
            resultado = 1;
        else
            resultado = -1;

    else if (fecha1.anno > fecha2.anno)
        resultado = 1;
    else
        resultado = -1;

    return resultado;
}



void carga_descuentos(Descuentos **d,int *n_desc){
    int i;
    char line[LINE]="\0";
    char cuenta_lin[LINE]="\0";
    char estado[10]="\0";
    FILE *f;

    if((f=fopen("descuentos.txt","r"))==NULL){
        printf("Error al abrir el archivo\n");
    }else{
        while(!feof(f)){

            fgets(cuenta_lin,LINE,f);
            (*n_desc)++;
        }
    }
    *d = (Descuentos *)calloc(*n_desc, sizeof(Descuentos));
    if(*d==NULL){
        printf("Error al reservar memoria para los Descuentos\n");
        exit(1);
    }else{
        rewind(f);
        for(i=0;i<*n_desc;i++){

        fgets(line,LINE,f);
            strcpy((*d)[i].Id_cod, strtok(line,"-"));
            strcpy((*d)[i].Descrip, strtok(NULL, "-\n"));  //cargamos los datos tipo char
            strcpy((*d)[i].Importe, strtok(NULL, "-\n"));

            strcpy(estado, strtok(NULL, "-\n"));//introducimos la siguiente cadena entre los '-'
                

                if(strcmp(estado,"codpro")==0){
                    (*d)[i].Tipo=codpro;

                }else if(strcmp(estado, "cheqreg")==0){
                    (*d)[i].Tipo=cheqreg;
                }else{puts("Error del campo TIPO"); }

                for(int k=0;k<10;k++) estado[k]='\0';
            
                strcpy(estado, strtok(NULL, "-\n"));
                
                if(strcmp(estado,"activo")==0){
                    (*d)[i].Estado=activo;

                }else if(strcmp(estado,"inactivo")==0){
                    (*d)[i].Estado=inactivo;
                }else{puts("Error del campo ESTADO"); }

                for(int k=0;k<10;k++) estado[k]='\0';
                strcpy(estado, strtok(NULL, "-\n"));

                if(strcmp(estado, "todos")==0){
                    (*d)[i].Aplicabilidad=todos;

                }else if(strcmp(estado, "esizon")==0){
                    (*d)[i].Aplicabilidad=esizon;
                }else{puts("Error del campo APLICABILIDAD");}; 
            
            for(int k=0;k<10;k++) estado[k]='\0';

        }
    }
    rewind(f);
    fclose(f);

}


/*
void carga_descuentos_clientes(Descuentos_clientes **dc){
    int i;

}*/




/*POR HACER 
    Función que compare fechas(para comparar la caducidad de los descuentos)
    Función que inicialice cada uno de los tipos(2) 
    Función que convierta de cadena de 11 carácteres al tipo fecha para poder compararlo con la actual y a la inversa
    Función que compruebe si el descuento está vigente
    --más funciones en adelante--
*/



