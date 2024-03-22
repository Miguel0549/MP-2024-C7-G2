/*##### MÓDULO DESCUENTOS   #####*/
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>
#include "descuentos.h"
#define LINE 100

//Tipos 
typedef struct fecha{
    int dia, mes, anno;
}fecha;
void crear_fichero_descuentos();
void crear_fichero_descuentos_clientes();
void leer_string(char*,int);
void nuevo_descuento(Descuentos**,int);

int main(){   //main para pruebas, quitar a la hora de unir los módulos
Descuentos *d;
int n=1;
int *p;
p = &n;
crear_fichero_descuentos();
//crear_fichero_descuentos_clientes;
//carga_descuentos(&d,p);
nuevo_descuento(&d,n);
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



//cabecera: void nuevo_descuento(int *n_desc)
//precondición: *n_desc puntero que apunta al número total de descuentos actual
//postcondición: crea y añade a la estructura un nuevo descuento
void nuevo_descuento(Descuentos **d,int n_desc){
    int sel,i=0;
    (*d )= (Descuentos *)calloc(n_desc, sizeof(Descuentos));
    if(d==NULL){
        printf("Error al reservar memoria para los Descuentos\n");
        exit(1);
    }

    printf("\nIntrozuca la Id del descuento:\n");     
    leer_string((*d)[n_desc-1].Id_cod,11);           //Introducimos la Id del código
    
    printf("\nIntroduzca una breve descripción del descuento:\n");
    leer_string((*d)[n_desc-1].Descrip,51);                            //Introducimos la cadena

    printf("\nIntroduce el importe del descuento:\n");
    leer_string((*d)[n_desc-1].Importe,4);               //Introducimos el importe del descuento
    do{
        printf("\nElija un tipo de descuento:\n 1.Codpro\n 2.Cheqreg\n");
        scanf("%i",&sel);
        if (sel==1)
        {
            (*d)[n_desc-1].Tipo=codpro;
            i++;
        }else if (sel==2)
        {
            (*d)[n_desc-1].Tipo=cheqreg;
            i++;
        }else
        {
            printf("\nIntroduzca una opción válida\n");
        }
    }while(i==0);
    i=0;
    do{
        printf("\nElija el Estado del Descuento:\n 1.Activo\n 2.Inactivo\n");
        scanf("%i",&sel);
        if (sel==1)
        {
            (*d)[n_desc-1].Estado=activo;
            i++;
        }else if (sel==2)
        {
            (*d)[n_desc-1].Estado=inactivo;
            i++;
        }else
        {
            printf("\nIntroduzca una opción válida\n");
        }
    }while(i==0);
    i=0;
        do{
        printf("\nElija en los productos en los que se aplica:\n 1.Todos\n 2.Esizon\n");
        scanf("%i",&sel);
        if (sel==1)
        {
            (*d)[n_desc-1].Aplicabilidad=todos;
            i++;
        }else if (sel==2)
        {
            (*d)[n_desc-1].Aplicabilidad=esizon;
            i++;
        }else
        {
            printf("\nIntroduzca una opción válida\n");
        }
    }while(i==0);

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

// cabecera: void leer_string(char * cadena, int elem)
// precondicion: ninguna
// postcondicion: lee en cadena la cadena introducida por el usuario
void leer_string(char*cadena, int elem)
{
    //int i;

    fflush(stdin);
    fgets(cadena, elem , stdin);
    fflush(stdin);
    puts(cadena);
    /*for (i = 0; cadena[i] != '\n' && i < elem + 1; i++)
        if (cadena[i] == '\n')
            cadena[i] = '\0';

    i = 0;
    while (i < elem + 1) {
        if (cadena[i] == '\n')
            cadena[i] = '\0';
        i++;
    }*/
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



//cabecera: void carga_descuentos(Descuentos **d,int *n_desc)
//precondición: sea **d un doble puntero a una estructura descuentos y *n_desc un puntero a entero con el número total de descuentos
//postcondición: carga en el vector de estructura Descuentos los datos desde el fichero descuentos.txt
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



//cabecera:void volcado_descuentos(Descuentos **d,int *n_desc)
//precondición:**d incializado y descuentos.txt creado
//postcondición:descuentos.txt contiene la información que contenía el vector de estructuras

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



