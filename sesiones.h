
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

    /*FUNCIONES CLIENTES*/
//cabecera void carga_cliente(Cliente**)
//precondición:fichero inicializado
//postcondición:carga en el doble puntero a estructura cliente la información del fichero
void carga_cliente(Cliente**,int*);

//cabecera void volcado_cliente(Cliente**)
//precondición:fichero y estructura inicializados
//postcondición:vuelca la información al fichero
void volcado_cliente(Cliente **,int*);

//cabecera: void nuevo_cliente(Cliente **,int *);
//precondición: **c doble puntero a estructura inicializado y *n_clientes puntero que apunta al numero actual de clientes
//postcondición: amplia el vector de estructuras e inicializa desde entrada de teclado un nuevo cliente
void nuevo_cliente(Cliente **,int *);

    /*FUNCIONES ADMINPROV*/
//cabecera void carga_Adminprov(Adminprov**)
//precondición:fichero inicializado
//postcondición:carga en el doble puntero a estructura adminprov la información del fichero
void carga_adminprov(Adminprov**,int*);

//cabecera void volcado_adminprov(Adminprov**)
//precondición:fichero y vector de estrtuctuas inicializados
//postcondición:vuelca al fiichero la información del vector de estructuras
void volcado_adminprov(Adminprov**,int*);

//cabecera: void nuevo_adminprov(Adminprov **,int *);
//precondición: **a doble puntero a estructura inicializado y *n_adminprov puntero que apunta al numero actual de admin/proveedores
//postcondición: amplia el vector de estructuras e inicializa desde entrada de teclado un nuevo admin/proveedor
void nuevo_adminprov(Adminprov **,int *);

    /*FUNCIONES TRANSPORTISTA*/
//cabecera void carga_transp(Transportista**)
//precondición:fichero inicializado
//postcondición:carga en el doble puntero a estructura Transportista la información del fichero
void carga_transp(Transportista**,int*);

//cabecera void volcado_transp(Transportista**)
//precondición:fichero inicializado, así como el vector de estructura transportista
//postcondición:vuelca la información del vector de estructura Transportista al fichero
void volcado_transp(Transportista**,int*);

//cabecera: void nuevo_transportista(Tranportista **,int *);
//precondición: **t doble puntero a estructura inicializado y *n_transportista puntero que apunta al numero actual de transportistas
//postcondición: amplia el vector de estructuras e inicializa desde entrada de teclado un nuevo transportista
void nuevo_transportista(Transportista **,int *);

//cabecera:int num_cliente_fich()
//precondición: que exista el .txt correspondiente
//postcondición: devuelve el número de líneas que tiene el fichero
int num_cliente_fich();

//cabecera:int num_admin_fich()
//precondición: que exista el .txt correspondiente
//postcondición: devuelve el número de líneas que tiene el fichero
int num_admin_fich();

//cabecera:int num_transp_fich()
//precondición: que exista el .txt correspondiente
//postcondición: devuelve el número de líneas que tiene el fichero
int num_transp_fich();