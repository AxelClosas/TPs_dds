#include <stdio.h>

void listar_inventario(char nombre_arch[])
{
    FILE *archivo;
    char info[100];

    int fin = 0;

    archivo = fopen(nombre_arch, "rt");
    if (archivo == NULL) return -1;

    puts("Inventario:");

    while ( !feof(archivo) )
    {
        fscanf(archivo,"%[^\n]\n", info);
        printf("%s\n", info);
    }

    fclose(archivo);
}

