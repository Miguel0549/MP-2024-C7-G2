#ifndef AMAZON_MP_ESTADO_H
#define AMAZON_MP_ESTADO_H

typedef enum {

    enPreparacion,   // 0
    enviado,         // 1
    enReparto,       // 2
    enLocker,        // 3
    entregado,       // 4
    devuelto,        // 5
    trasnportista,   // 6
    pediente,        // 7
    aceptado,        // 8
    denegado,        // 9
    recibido,        // 10
    ocupado,         // 11
    vacio,           // 12

}estado;


typedef enum{

    cliente,
    admin,
    proveedor,
    transportista,


}usu;




#endif //AMAZON_MP_ESTADO_H
