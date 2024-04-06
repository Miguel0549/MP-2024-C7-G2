
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


//cabecera void carga_cliente(Cliente**)
//precondición:fichero inicializado
//postcondición:carga en el doble puntero a estructura cliente la información del fichero
void carga_cliente(Cliente**);

//cabecera void volcado_cliente(Cliente**)
//precondición:fichero y estructura inicializados
//postcondición:vuelca la información al fichero
void volcado_cliente(Cliente **);

//cabecera void carga_Adminprov(Adminprov**)
//precondición:fichero inicializado
//postcondición:carga en el doble puntero a estructura adminprov la información del fichero
void carga_adminprov(Adminprov**);

//cabecera void volcado_adminprov(Adminprov**)
//precondición:fichero y vector de estrtuctuas inicializados
//postcondición:vuelca al fiichero la información del vector de estructuras
void volcado_adminprov(Adminprov**);

//cabecera void carga_transp(Transportista**)
//precondición:fichero inicializado
//postcondición:carga en el doble puntero a estructura Transportista la información del fichero
void carga_transp(Transportista**);

//cabecera void volcado_transp(Transportista**)
//precondición:fichero inicializado, así como el vector de estructura transportista
//postcondición:vuelca la información del vector de estructura Transportista al fichero
void volcado_transp(Transportista**);