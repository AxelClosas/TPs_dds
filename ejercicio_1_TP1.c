#include <stdio.h>
#include <stdlib.h>

int main()
{
    int minutos_usuario, minutos_semana = 10080, i = 0;
    float resultado = 0;

    while (i < 15)
    {
        printf("Minutos: ");
        scanf("%d", &minutos_usuario);

        resultado = (float)minutos_usuario / (float)minutos_semana;

        printf("\n\t%d minutos equivalen a %.2f semanas.", minutos_usuario, resultado);
        printf("\n");
        printf("\n");

        i++;
    }

    return 0;
}
