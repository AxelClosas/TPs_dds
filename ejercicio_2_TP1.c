#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Variables de jugadores
    int numero_uno, numero_dos;
    // Varibles de lógica
    int ganador = 0, intentos = 0, intentos_max = 3, jugar = 1;

    while (jugar == 1)
    {
        printf("\n");
        do
        {
            printf("Jugador 1. Ingresa el n%cmero secreto: ", 163);
            scanf("%d", &numero_uno);
            system("CLS");
        } while (numero_uno < 1 || numero_uno > 10);

        while (intentos < intentos_max)
        {
            printf("Intento %d", intentos+1);
            printf("\n\nJugador 2. Ingresa tu respuesta: ");
            scanf("%d", &numero_dos);

            if (numero_uno == numero_dos)
            {
                ganador = 1;
                intentos = intentos_max;
            }
            else
            {
                if (numero_dos > numero_uno)
                    printf("\n\n\tCasi... Tu n%cmero es mayor.\n", 163);
                else
                    printf("\n\n\tCasi... Tu n%cmero es menor.\n", 163);

                intentos++;
                system("PAUSE");
                system("CLS");
            }

        }

        if (ganador == 1)
            printf("\n\n\tVictoria!, has acertado el n%cmero secreto.\n", 163);
        else
            printf("\n\nDerrota!, no has logrado acertar el n%cmero secreto. La respuesta era %d\n\n", 163, numero_uno);

        intentos = 0;
        ganador = 0;

        system("PAUSE");
        system("CLS");

        printf("Quieren volver a jugar?\n\t1.SI\n\t0.NO\n\nOpci%cn: ", 162);
        scanf("%d", &jugar);

        system("PAUSE");
        system("CLS");

    }

    return 0;
}
