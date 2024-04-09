
typedef enum{
    administrador, proveedor
}tipo_per;

typedef struct 
{
    char Id_cliente[7], Nombr_cliente[21], Dir_cliente[51],Localidad[21], Provincia[21], email[31] ,Contrasenna[16],Cartera[7];    
}Cliente;

typedef struct
{
    char Id_empresa[5],Nombre[21], email[31],Contrasenna[16];
    tipo_per Perfil_usuario;
}Adminprov;

typedef struct {
    char Id_transp[5],Nombre[21],email[31],Contrasenna[16],Nom_empre[21],Ciudad[21];
}Transportista;


//cabecera void carga_cliente(Cliente**)
//precondición:fichero inicializado
//postcondición:carga en el doble puntero a estructura cliente la información del fichero
void carga_cliente(Cliente**,int*);

//cabecera void volcado_cliente(Cliente**)
//precondición:fichero y estructura inicializados
//postcondición:vuelca la información al fichero
void volcado_cliente(Cliente **,int*);

//cabecera void carga_Adminprov(Adminprov**)
//precondición:fichero inicializado
//postcondición:carga en el doble puntero a estructura adminprov la información del fichero
void carga_adminprov(Adminprov**,int*);

//cabecera void volcado_adminprov(Adminprov**)
//precondición:fichero y vector de estrtuctuas inicializados
//postcondición:vuelca al fiichero la información del vector de estructuras
void volcado_adminprov(Adminprov**,int*);

//cabecera void carga_transp(Transportista**)
//precondición:fichero inicializado
//postcondición:carga en el doble puntero a estructura Transportista la información del fichero
void carga_transp(Transportista**,int*);

//cabecera void volcado_transp(Transportista**)
//precondición:fichero inicializado, así como el vector de estructura transportista
//postcondición:vuelca la información del vector de estructura Transportista al fichero
void volcado_transp(Transportista**,int*);