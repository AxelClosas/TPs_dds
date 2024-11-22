#include <stdio.h>
#include <stdlib.h>


int main()
{
    int n, p;
    int *edades;
    int *mas_edades;
    int i;
    int j;
    int total;

    printf("Ingresa la cantidad de edades a ingresar\n>> ");
    scanf("%i", &n);

    edades = (int *)calloc(n, sizeof(int));
    if (edades == NULL)
    {
        printf("Error. no se pudo asignar memoria.");
        exit(-1);
    }

    for (i=0; i < n; i++)
    {
        int aux;
        printf("Edad %i\n>> ", i+1);
        scanf("%i", &aux );
        *(edades+i) = aux;
    }

    printf("\nIngresa la cantidad de edades que deseas agregar\n>> ");
    scanf("%i", &p);
    total = n + p;

    mas_edades = (int *)realloc(edades, total*sizeof(int));
    if (mas_edades == NULL)
    {
        printf("Error. no se pudo asignar mas memoria.");
        exit(-1);
    }


    for (j=i; j < total; j++)
    {
        int aux;
        printf("Edad %i\n>> ", j+1);
        scanf("%i", &aux );
        *(mas_edades+j) = aux;
    }

    for (i=0; i < total; i++)
        printf("\nEdad ingresada >> %i\n", *(mas_edades+i));

    free(edades);
    free(mas_edades);


    return 0;
}
