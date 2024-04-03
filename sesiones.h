
typedef enum{
    administrador, proveedor
}tipo_per;

typedef struct 
{
    char Id_cliente[7], Nombr_cliente[20], Dir_cliente[50],Localidad[20], Provincia[20], email[30] ,Contrasenna[15],Cartera[6];    
}Cliente;

typedef struct
{
    char Id_empresa[4],Nombre[20], email[30],Contrasenna[15];
    tipo_per Perfil_usuario;
}Adminprov;

typedef struct {
    char Id_transp[4],Nombre[20],email[30],Contrasenna[15],Nom_empre[20],Ciudad[20];
}Transportista;