#include <stdio.h>
#define CANT_PROD 3

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

void ingresar_productos(PRODUCTO *productos[], int cant_prod);
void listar_productos(PRODUCTO *productos[], int cant_prod);


void main()
{
    PRODUCTO productos[CANT_PROD];

    ingresar_productos(productos, CANT_PROD);

    listar_productos(productos, CANT_PROD);

}

void ingresar_productos(PRODUCTO *productos[], int cant_prod)
{
    int i;

    for (i=0; i < cant_prod; i++)
    {
        printf("Producto [%i]", i+1);
        printf("\n");

        printf("Código: ");
        scanf("%i", &productos[i]->cod_producto);
        printf("\n");
        fflush(stdin);

        puts("Detalle: ");
        gets(productos[i]->detalle);
        fflush(stdin);

        printf("Precio: ");
        scanf("%f", &productos[i]->precio);
        printf("\n");
        fflush(stdin);

        printf("Stock: ");
        scanf("%i", &productos[i]->stock);
        printf("\n");
        fflush(stdin);

        puts("Ubicación:");
        gets(productos[i]->ubicacion);
        fflush(stdin);

    }
}

void listar_productos(PRODUCTO productos[], int cant_prod)
{
    int i;

    for (i = 0; i < cant_prod; i++)
    {
        printf("Producto [%i]", i+1);
        printf("\n");

        printf("Código [%i] ", productos[i]->cod_producto);
        printf("\n");

        puts("Detalle: ");
        puts(productos[i]->detalle);

        printf("Precio: %.2f", productos[i]->precio);
        printf("\n");

        printf("Stock: %i", productos[i]->stock);
        printf("\n");

        puts("Ubicación:");
        puts(productos[i]->ubicacion);

    }
}
