#include <stdio.h>
#include <string.h>
#include <locale.h>

#define MAX_PRODUCTOS 15

typedef struct {
    int codigoProducto;
    char detalle[100];
    float precio;
    int stock;
    char ubicacion[50];
} Producto;

void ingresarProductos(Producto productos[], int n);//cargar vector
void ordenarProductos(Producto productos[], int n); // ordenar los productos con algoritmo de burbuja
void mostrarProductos(Producto productos[], int n); //mostrar los productos

int main() {

	setlocale(LC_ALL, "es_ES.UTF-8");

    Producto productos[MAX_PRODUCTOS];
    Producto productosOrdenados[MAX_PRODUCTOS];

    ingresarProductos(productos, MAX_PRODUCTOS);

    // Copiar los productos al nuevo vector para ordenarlos
    for (int i = 0; i < MAX_PRODUCTOS; i++) {
        productosOrdenados[i] = productos[i];
    }

    // Ordenar los productos por c�digo
    ordenarProductos(productosOrdenados, MAX_PRODUCTOS);


    printf("\nProductos originales:\n");
    mostrarProductos(productos, MAX_PRODUCTOS);

    printf("\nProductos ordenados por C�digo de Producto:\n");
    mostrarProductos(productosOrdenados, MAX_PRODUCTOS);

    return 0;
}


void ingresarProductos(Producto productos[], int n) {
    for (int i = 0; i < n; i++) {
        printf("\nProducto %d:\n", i + 1);
        printf("Ingrese el c�digo del producto: ");
        scanf("%d", &productos[i].codigoProducto);
		fflush(stdin);

        printf("Ingrese el detalle del producto: ");
        gets(productos[i].detalle);
        fflush(stdin);

        printf("Ingrese el precio del producto: ");
        scanf("%f", &productos[i].precio);
		fflush(stdin);

        printf("Ingrese el stock del producto: ");
        scanf("%d", &productos[i].stock);
		fflush(stdin);

		printf("Ingrese la ubicaci�n del producto: ");
        gets(productos[i].ubicacion);
        fflush(stdin);
    }
}

// Funci�n para ordenar los productos con el algoritmo de burbuja
void ordenarProductos(Producto productos[], int n) {
    Producto temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (productos[j].codigoProducto > productos[j + 1].codigoProducto) {
                temp = productos[j];
                productos[j] = productos[j + 1];
                productos[j + 1] = temp;
            }
        }
    }
}

// Funci�n para mostrar los productos
void mostrarProductos(Producto productos[], int n) {
    for (int i = 0; i < n; i++) {
        printf("\nProducto %d:\n", i + 1);
        printf("C�digo Producto: %d\n", productos[i].codigoProducto);
        printf("Detalle: %s", productos[i].detalle);
        printf("Precio: %.2f\n", productos[i].precio);
        printf("Stock: %d\n", productos[i].stock);
        printf("Ubicaci�n: %s\n", productos[i].ubicacion);
    }
}

