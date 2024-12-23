#include <stdio.h>
#include <string.h>

void eliminar_repetidas(char palabra_uno[], char nueva[]);
void contar_coincidencias(char palabra[], char palabra_dos[], int cuenta[]);
void mostrar_coincidencias(char palabra[], int cuenta[]);

void main()
{

    char palabra_uno[35], palabra_dos[35], nueva[30];

    int i = 0;



    while (i < 3)
    {
        int cuenta[35] = {0};

        printf("Ingresa la palabra uno: ");
        gets(palabra_uno);
        fflush(stdin);

        printf("\n");
        printf("Ingresa la palabra dos: ");
        gets(palabra_dos);
        fflush(stdin);

        eliminar_repetidas(palabra_uno, nueva);

        printf("Palabra uno: %s", palabra_uno);

        printf("\n");

        printf("Palabra dos: %s", palabra_dos);

        printf("\n");

        printf("Palabra uno sin repetidas: %s", nueva);

        contar_coincidencias(nueva, palabra_dos, cuenta);

        printf("\n\n");

        printf("Las coincidencias son las siguientes...\n\n");

        mostrar_coincidencias(nueva, cuenta);

        i++;
    }

}


void mostrar_coincidencias(char palabra[], int cuenta[])
{
    int i;

    for ( i = 0; palabra[i] != '\0'; i++)
    {
        printf("%c = %d", palabra[i], cuenta[i]);
        printf("\n");
    }
}


void eliminar_repetidas(char palabra_uno[], char nueva[])
{
    int i = 0;
    int k = 0;

    while ( palabra_uno[i] != '\0')
    {
        int repetida = 0;
        int j = 0;

        while (j < i)
        {
            if (palabra_uno[i] == palabra_uno[j])
            {
                repetida = 1;
                break;
            }
            else
            {
                j++;
            }
        }
        if (repetida == 0)
        {
            nueva[k] = palabra_uno[i];
            k++;
        }

        i++;
    }

    nueva[k] = '\0';

}


void contar_coincidencias(char palabra[], char palabra_dos[], int cuenta[])
{
    int i = 0;
    int j;


    while (palabra[i] != '\0')
    {
        j = 0;
        while (palabra_dos[j] != '\0')
        {
            if (palabra[i] == palabra_dos[j])
                cuenta[i]++;

            j++;
        }

        i++;
    }
}
