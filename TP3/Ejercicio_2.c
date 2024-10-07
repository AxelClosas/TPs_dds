#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define T 5
#define cant_fichas 3

typedef struct tab
{
    int jugador;
    int tablero[T][T];

} TABLERO;

void pintar_tablero(TABLERO *jug);
void ubicar_fichas(TABLERO *jug);

void main()
{

    TABLERO J1 = {1, {{0}} };
    TABLERO J2 = {2, {{0}} };

    ubicar_fichas(&J1);
    ubicar_fichas(&J2);


}


void ubicar_fichas(TABLERO *jug)
{
    int i, j, k;
    int fila, columna;

    printf("Observa el tablero y luego ingresa la fila y columna para ubicar tu ficha.\n\n");

    for (i=0; i < cant_fichas; i++)
    {
        printf("Jugador [%i]\n\n", jug->jugador);
        pintar_tablero(jug);
        printf("\n\n");
        printf("Tienes %d fichas disponibles...\n\n", cant_fichas - i);
        printf("\n");
        do
        {
            printf("Fila: ");
            scanf("%d", &fila);
            printf("\n");
            printf("Columna: ");
            scanf("%d", &columna);
            if ((fila < 1 || fila > 5) || (columna < 1 || columna > 5))
            {
                printf("Posiciones fuera de rango... Vuelve a ingresarlas...");
                printf("\n\n");
            }

        } while ((fila < 1 || fila > 5) || (columna < 1 || columna > 5));

        for (j = 0; j < T; j++)
            for (k = 0; k < T; k++)
                if (j == fila - 1 && k == columna - 1)
                    if (jug -> tablero[fila - 1][columna - 1] != 1)
                        jug -> tablero[fila - 1][columna - 1] = 1;
                    else
                    {
                        printf("Ya has ingresado esas coordenadas, prueba a ingresar otras...\n");
                        i--;
                    }


        system("PAUSE");
        system("CLS");
    }
}


void pintar_tablero(TABLERO *jug)
{
    int i,j;

    // Dibujar el tablero
    for (i = 0; i < T; i++)
        printf("\t[%d]", i+1);

    printf("\n\n");

    for (i = 0; i < T; i++)
    {
        printf(" [%i]\t", i+1);
        for (j = 0; j < T; j++)
        {
            printf(" %i\t", jug -> tablero[i][j]);
        }
        printf("\n\n");
    }

}
