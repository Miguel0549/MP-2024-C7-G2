#ifndef AMAZON_MP_ESTADO_H
#define AMAZON_MP_ESTADO_H

typedef enum {

    ocupado,
    vacio,
    enPreparacion,
    enviado,
    enReparto,
    enLocker,
    entregado,
    devuelto,
    trasnportista,
    pediente,
    aceptado,
    denegado,
    recibido,

}estado;


typedef enum{

    cliente,
    admin,
    proveedor,
    transportista,


}usu;




#endif //AMAZON_MP_ESTADO_H
