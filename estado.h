#ifndef AMAZON_MP_ESTADO_H
#define AMAZON_MP_ESTADO_H

typedef enum {

    ocupado,         // 0
    vacio,           // 1
    enPreparacion,   // 2
    enviado,         // 3
    enReparto,       // 4
    enLocker,        // 5
    entregado,       // 6
    devuelto,        // 7
    trasnportista,   // 8
    pediente,        // 9
    aceptado,        // 10
    denegado,        // 11
    recibido,        // 12

}estado;


typedef enum{

    cliente,
    admin,
    proveedor,
    transportista,


}usu;




#endif //AMAZON_MP_ESTADO_H
