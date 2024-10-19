#include <stdio.h>

/*

Código Producto
- Detalle
- Precio
- Stock
- Ubicación

*/

typedef struct prod
{
    long cod_producto;
    char detalle[30];
    float precio;
    int stock;
    char ubicacion[30];

}PRODUCTO;

void ingresar_productos(PRODUCTO productos[], int cant_elementos);
void ord_burbuja(PRODUCTO productos[], int cant_elementos);
void listar_productos(PRODUCTO productos[], int cant_elementos);


void main()
{
    PRODUCTO productos[3];

    ingresar_productos(productos, 3);

    listar_productos(productos, 3);

}

void ingresar_productos(PRODUCTO productos[], int cant_elementos)
{
    int i;

    for (i=0; i < cant_elementos; i++)
    {
        printf("Producto (%i)\n\n", i+1);

        printf("Codigo:\n");
        scanf("%i", &productos[i].cod_producto);
        fflush(stdin);
        printf("\n");

        printf("Detalle:\n");
        gets(productos[i].detalle);
        fflush(stdin);
        printf("\n");

        printf("Precio:\n");
        scanf("%f", &productos[i].precio);
        fflush(stdin);
        printf("\n");

        printf("Stock:\n");
        scanf("%i", &productos[i].stock);
        fflush(stdin);
        printf("\n");

        printf("Ubicacion:\n");
        scanf("%s", productos[i].ubicacion);
        fflush(stdin);
        printf("\n\n");

    }
}

void listar_productos(PRODUCTO productos[], int cant_elementos)
{
    ord_burbuja(productos, cant_elementos);

    int i;
    for (i=0; i < cant_elementos; i++)
    {
        printf("Producto (%i)\n", i+1);

        printf("[Codigo]: %i\n", productos[i].cod_producto);
        printf("[Detalle]:%s\n", productos[i].detalle);
        printf("[Precio] %.2f\n", productos[i].precio);
        printf("[Stock]: %i\n", productos[i].stock);
        printf("[Ubicacion]: %s\n", productos[i].ubicacion);

    }

}

void ord_burbuja(PRODUCTO productos[], int cant_elementos)
{
    int pasada;
    int j;
    int interruptor = 1;


    for (pasada=0; pasada < cant_elementos - 1 && interruptor; pasada++)
    {
        interruptor = 0;
        for (j=0; j < cant_elementos - pasada - 1; j++)
        {
            if (productos[j].cod_producto > productos[j+1].cod_producto)
            {
                PRODUCTO aux = productos[j];
                productos[j] = productos[j+1];
                productos[j+1] = aux;
                interruptor = 1;
            }
        }
    }
}
