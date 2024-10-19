#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void guardar_nombre();
void guardar_apellido();
int verificar_campo(char cadena[]);

int main()
{
    int ingresar = 1;
    int opcion;
    while (ingresar != 0)
    {
        puts("Ingresa la opcion:");
        puts("1. Ingresar nombres");
        puts("2. Ingresar apellidos");
        puts("\n0. Salir");
        printf("? ");
        fflush(stdin);
        scanf("%i", &opcion);

        if (opcion == 0) return -1;

        if (opcion == 1) guardar_nombre();
        if (opcion == 2) guardar_apellido();

        system("pause");
        system("cls");
        puts("Seguir ingresando datos? (1=SI, 0=NO)\n");
        fflush(stdin);
        scanf("%i", &ingresar);
    }


    return 0;
}

void guardar_nombre()
{
    FILE* listado;
    int ingresar = 1;

    printf("Para salir: presiona Enter con la linea vacia\n\n");

    while (ingresar != 0)
    {
        listado = fopen("listado.txt", "at");
        char nombre[30] = {'\0'};
        puts("Nombre:");
        fflush(stdin);
        gets(nombre);

        // Condición de cierre ingresar nombres
        if (verificar_campo(nombre))
            fprintf(listado, "%s\n", nombre);

        ingresar = verificar_campo(nombre);

        fclose(listado);
    }

}


void guardar_apellido()
{
    FILE* listado;
    int ingresar = 1;

    while (ingresar != 0)
    {
        listado = fopen("listado.txt", "at");
        char apellido[30] = {'\0'};
        puts("Apellido:");
        fflush(stdin);
        gets(apellido);

        // Condición de cierre ingresar apellidos
        if (verificar_campo(apellido))
            fprintf(listado, "%s\n", apellido);

        ingresar = verificar_campo(apellido);

        fclose(listado);
    }

}

int verificar_campo(char cadena[])
{
    // Retorna 1 si el tamaño de la cadena recibida > 0. Caso contrario retorna 0.

    /* Operador ternario. Equivalente al If-else.
        variable = (condicion) ? asigar_valor_verdadero : asignar_valor_falso;
    */
    return ( (strlen(cadena)) ? 1 : 0 );
}
