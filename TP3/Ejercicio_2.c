#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define cant_fichas 3

#define T 5

typedef struct tab
{
    int jugador;
    int tablero[T][T];
    int vidas;

} TABLERO;

void pintar_tablero(TABLERO *jug);
void ubicar_fichas(TABLERO *jug);
void iniciar_juego(TABLERO *jug1, TABLERO *jug2);


void main()
{
    int jugar;


    do
    {
        TABLERO J1 = {1, {{0}}, 3 };
        TABLERO J2 = {2, {{0}}, 3 };
        ubicar_fichas(&J1);
        ubicar_fichas(&J2);

        system("PAUSE");
        system("CLS");


        iniciar_juego(&J1, &J2);

        printf("Volver a jugar?\n\n\t1. SI\n\t0. NO\n\n\tOpcion: ");
        scanf("%i", &jugar);
    } while (jugar == 1);

}

int turno_aleatorio()
{
    srand(time(0));

    int turno = (rand() % 2) + 1;

    return turno;
}

int atacar_coordenada(TABLERO *jug, int fila, int columna)
{
    int i, j;
    int golpe;

    for (i=0; i < T; i++)
        for (j=0; j < T; j++)
        {
            if (jug->tablero[fila - 1][columna - 1] == 1)
            {
                jug->tablero[fila - 1][columna - 1] = 0;
                golpe = 1;
            } else
            {
                golpe = 0;
            }
        }

    return golpe;
}

void iniciar_juego(TABLERO *jug1, TABLERO *jug2)
{
    int turno_inicial = turno_aleatorio();

    int fila, columna, golpe;

    printf("Jugador [%i]. Ingresa tus coordenadas de ataque...\n", turno_inicial);
    printf("Fila: ");
    scanf("%i", &fila);

    printf("\n");

    printf("Columna: ");
    scanf("%i", &columna);

    do
    {
        if (turno_inicial == 1)
        {
            golpe = atacar_coordenada(jug2, fila, columna);

        }
        else{

        }
    } while ( (jug1->vidas == 0) || (jug2->vidas == 0) );

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
            if ((fila < 1 || fila > T) || (columna < 1 || columna > T))
            {
                printf("Posiciones fuera de rango... Vuelve a ingresarlas...");
                printf("\n\n");
            }

        } while ((fila < 1 || fila > T) || (columna < 1 || columna > T ));

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
