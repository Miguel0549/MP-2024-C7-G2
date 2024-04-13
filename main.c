#include <stdio.h>
#include <string.h>
//#include "/home/mercurio/Documentos/Proyecto MP/Proyecto_MP/sesiones.h "

//#include <>  añadir los fuicheros necesarios 
void menu_principal_usuario(char Id[7]);
void menu_principal_transportista(char transp[4]);
int main(){
    printf("texto de prueba\n");
    menu_principal_usuario();

    return 0;
}

//cabecera: void menu_principal_usuario(char Id_usuario[7])
//precoindición: recibe el id del usuario que ha iniciado sesión 
//postcondición: imprime el menú de usuario
void menu_principal_usuario(char Id[7]){
    int i=0,opt;
    do{
       // printf("Usuario: %s\n ----------------------------------------------------\n",nomb_cliente);
        printf("1. Perfil\n
                2. Productos\n
                3. Descuentos\n
                4. Pedidos\n
                5. Devoluciones\n 
                6. Salir del sistema\n");
        scanf("%i",&opt);
        switch (opt)
        {
        case 1: mostrar_perfil();
            break;
        case 2: mostrar_productos();
            break;
        case 3: mostrar_descuentos();
            break;
        case 4: mostar_pedidos();
            break;
        case 5: mostrar_Devoluciones();
            break;
        case 6: printf("--Apagando sistema--");
            break;
    
        default:printf("\n**DEBE SELECCIONAR UNA OPCION VALIDA**\n");
            break;
        }
    }while(i!=6);
}
//cabecera: void menu_principal_transportista(char transportista[7])
//precoindición: recibe el id del transportista que ha iniciado sesión 
//postcondición: imprime el menú de transportista

//cabecera: void menu_principal_proveedor(char Id_proveedor[7])
//precoindición: recibe el id del usuario que ha iniciado sesión 
//postcondición: imprime el menú de proveedor

//cabecera: void menu_principal_administrador(char Id_admin[7])
//precoindición: recibe el id del usuario que ha iniciado sesión 
//postcondición: imprime el menú de administrador 