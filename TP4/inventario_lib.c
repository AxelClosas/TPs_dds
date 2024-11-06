#include <stdio.h>
#include "agregar_libro.h"
#include "listar_inventario.h>

/* Código Tole commit a3a9e06c9395bd0873a62a5e8ea5b556349cd426 */

int main()
{
    int opcion = 1;
    do
    {
        agregar_libro();
        printf("?");
        scanf("%i", &opcion);

    }while(opcion == 1);
}
