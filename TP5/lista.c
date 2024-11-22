#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo
{
    int dato;
    struct Nodo *ps;
}NODO;

int menu();
void push(NODO **CIMA);
void pop(NODO **CABEZA);

void imprimir(NODO *CABEZA)
{
    while(CABEZA != NULL)
    {
        printf("DATO %i", CABEZA->dato);
        printf("\n========================\n");
        CABEZA = CABEZA->ps;
    }
}

int main()
{   int cont = 1;
    int op;
    NODO *cima;
    cima = NULL;

    do
    {
        op = menu();
        switch(op)
        {
        case 1:
            push(&cima);
            break;
        case 2:
            pop(&cima);
            break;
        }

        printf("\nContinuar [1.SI, 0.NO]\n>> ");
        scanf("%i", &cont);

    }while(cont == 1);

    imprimir(cima);
    free(cima);
    return 0;
}

int menu()
{
    int op;
    printf("1. Agregar elemento\n");
    printf("2. Quitar elemento\n");
    printf(">> ");
    fflush(stdin);
    scanf("%i", &op);

    return op;
}
void push(NODO **CABEZA)
{
    NODO *nuevo;
    int a;
    nuevo = (NODO *)malloc(sizeof(NODO));
    if (nuevo == NULL)
    {
        printf("No se pudo asignar memoria.\n");
        exit(-1);
    }

    system("cls");

    printf("Ingresa un valor: ");
    scanf("%i", &a);
    nuevo->dato = a;
    nuevo->ps = NULL;

    if (*CABEZA == NULL)
        *CABEZA = nuevo;
    else
    {
        nuevo->ps = *CABEZA;
        *CABEZA = nuevo;
    }

}

void pop(NODO **CABEZA)
{

}
