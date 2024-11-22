#include <stdio.h>

typedef struct resp
{
    char MayorVta_codigo[10];
    char MayorVta_descrip[50];
    int MayorVta_canti[10];

    char MenorVta_codigo[10];
    char MenorVta_descrip[10];
    int MenorVta_canti[10];
}RESP;

typedef struct venta
{
    char codigo[10];
    char descripcion[50];
    int cantidadvta;
    float preciovta;
    int dia;
    int mes;
    int anio;
}VENTA;

RESP proceso_mayor_menor_venta(FILE *pf, int dia_i, int mes_i, int anio_i, int dia_f, int mes_f, int anio_f);

void crear_datos();

int main()
{
    FILE *pf = fopen("artventa.dat", "rb");
    if (pf == NULL)
        return -1;
    RESP estat;

    estat = proceso_mayor_menor_venta(pf, 01, 01, 2024, 30, 06, 2024);
    printf("Mayor venta\n");
    printf("\nCodigo: %s\nDescripcion: %s\nCantidad: %i", estat.MayorVta_codigo, estat.MayorVta_descrip, estat.MayorVta_canti);

    printf("Menor venta\n");
    printf("\nCodigo: %s\nDescripcion: %s\nCantidad: %i", estat.MenorVta_codigo, estat.MenorVta_descrip, estat.MenorVta_canti);

    return 0;
}


RESP proceso_mayor_menor_venta(pf, int dia_i, int mes_i, int anio_i, int dia_f, int mes_f, int anio_f)
{
    int mayor = 1; int menor = 99999;
    VENTA reg;
    VENTA aux_may, aux_men;
    RESP respuesta;

//    fread(&reg, sizeof(VENTA), 1, pf); // dia=02 mes=05 anio=2024
    do
    {   fread(&reg, sizeof(VENTA), 1, pf); // dia=02 mes=05 anio=2024
        if ( ((reg.dia >= dia_i) && (reg.dia <= dia_f)) &&
            ((reg.mes >= mes_i) && (reg.mes <= mes_f)) &&
            ((reg.anio >= anio_i) && (reg.anio <= anio_f)) )
        {
            if (reg.cantidadvta > mayor)
            {
                aux_may = reg;
                mayor = reg.cantidadvta;
            }
            else if (reg.cantidadvta < menor)
            {
                aux_men = reg;
                menor = reg.cantidadvta;
            }
        }

    }while(!feof(pf));

//    while(!feof(pf))
//    {
//        if ( ((reg.dia >= dia_i) && (reg.dia <= dia_f)) &&
//            ((reg.mes >= mes_i) && (reg.mes <= mes_f)) &&
//            ((reg.anio >= anio_i) && (reg.anio <= anio_f)) )
//        {
//            if (reg.cantidadvta > mayor)
//            {
//                aux_may = reg;
//                mayor = reg.cantidadvta;
//            }
//            else if (reg.cantidadvta < menor)
//            {
//                aux_men = reg;
//                menor = reg.cantidadvta;
//            }
//        }
//        fread(&reg, sizeof(VENTA), 1, pf);
//    }

    strcpy(respuesta.MayorVta_codigo, aux_may.codigo);
    strcpy(respuesta.MayorVta_descrip, aux_may.descripcion);
    respuesta.MayorVta_canti = aux_may.cantidadvta;

    strcpy(respuesta.MenorVta_codigo, aux_men.codigo);
    strcpy(respuesta.MenorVta_descrip, aux_men.descripcion);
    respuesta.MenorVta_canti = aux_men.cantidadvta;

    return respuesta;

}
