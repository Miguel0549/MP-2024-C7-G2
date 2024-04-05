
typedef enum{
    administrador, proveedor
}tipo_per;

typedef struct 
{
    char Id_cliente[7], Nombr_cliente[21], Dir_cliente[51],Localidad[21], Provincia[21], email[31] ,Contrasenna[16],Cartera[6];    
}Cliente;

typedef struct
{
    char Id_empresa[4],Nombre[20], email[30],Contrasenna[15];
    tipo_per Perfil_usuario;
}Adminprov;

typedef struct {
    char Id_transp[4],Nombre[20],email[30],Contrasenna[15],Nom_empre[20],Ciudad[20];
}Transportista;

void carga_cliente(Cliente**);
void volcado_cliente(Cliente **);