#include <stdio.h>
#include <stdlib.h>

int main()
{
    int numero_usuario;
    int serie = 1;
    int i = 10;
    int resultado_previo = 0;
    int resultado = 0;

    printf("El presente programa realiza la sumatoria de la serie 1+11+111+1111+...n donde n ser%c menor al n%cmero que se ingrese por teclado.\n\n", 160, 163);
    printf("N%cmero: ", 163);
    scanf("%d", &numero_usuario);

    while (resultado < numero_usuario)
    {
        resultado_previo = resultado + 1;
        serie = serie + (1 * i);
        resultado = resultado + serie;
        i = i * 10;
    }

    printf("Resultado: %d", resultado_previo);
    printf("\n\n");
    system("PAUSE");

    return 0;
}
