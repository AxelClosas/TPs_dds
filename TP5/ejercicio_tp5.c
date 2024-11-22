#include <stdio.h>
#include <stdlib.h>

// Tipo Abstracto de Dato (TAD) -
/*
    Pila de libros, platos, discos, etc.
    Lista Last In First Out -> Ultimo en entrar primero en salir

*/

typedef struct estudiante
{ // datos
    char nombre[100];
    int edad;
    float prom;

    // puntero al siguiente
    struct estudiante *ps;

}NodoEstudiante;

void carga_estudiante(NodoEstudiante **CABEZA, int i);
void mostrar_lista(NodoEstudiante **CABEZA);
void liberar_memoria(NodoEstudiante **CABEZA);
NodoEstudiante Pop(NodoEstudiante **CABEZA);


NodoEstudiante Top(NodoEstudiante **CABEZA);

int main()
{
    NodoEstudiante *cima; // Puntero cabecera
    cima = NULL;

    int cant;

    printf("Ingresa la cantidad de estudiantes que desees agregar\n>> ");
    scanf("%i",&cant);

    for (int i=0; i < cant; i++)
    {
        carga_estudiante(&cima, i+1);
    }

    NodoEstudiante reg = Pop(&cima);
    printf("\nEl ejecutarse Pop\n");
    printf("%s\n", reg.nombre);
    printf("%i\n", reg.edad);
    printf("%.2f\n", reg.prom);


    NodoEstudiante primer_elemento = Top(&cima);
    printf("\nEl ejecutarse TOP\n");
    printf("%s\n", primer_elemento.nombre);
    printf("%i\n", primer_elemento.edad);
    printf("%.2f\n", primer_elemento.prom);

    system("pause");
    printf("\n*-- LISTA DE ALUMNOS --*\n");
    mostrar_lista(&cima);
    liberar_memoria(&cima);

    return 0;
}

void carga_estudiante(NodoEstudiante **CABEZA, int i)
{
    system("CLS");
    NodoEstudiante *nuevo; // Declaración de estructura
    nuevo = (NodoEstudiante *)malloc(sizeof(NodoEstudiante)); // Pido memoria
    if (nuevo == NULL)
    {
        printf("No se pudo asignar memoria.\n");
        exit(-1);
    }

    printf("Estudiante [%i]\n", i);
    printf("Nombre\n>> ");
    fflush(stdin);
    gets(nuevo->nombre);

    printf("\nEdad\n>> ");
    fflush(stdin);
    scanf("%i", &nuevo->edad);

    printf("\nPromedio\n>> ");
    fflush(stdin);
    scanf("%f", &nuevo->prom);

    nuevo->ps=NULL; // Buenas practicas

    if (*CABEZA == NULL)
        *CABEZA = nuevo;
    else
    {
        nuevo->ps = *CABEZA;
        *CABEZA = nuevo;
    }

}

void mostrar_lista(NodoEstudiante **CABEZA)
{
    while (*CABEZA != NULL)
    {
        printf("\n----\n");
        printf("Nombre: %s\n", (*CABEZA)->nombre);
        printf("Edad: %i\n", (*CABEZA)->edad);
        printf("Promedio: %.2f\n", (*CABEZA)->prom);
        *CABEZA = (*CABEZA)->ps;
    }
}

void liberar_memoria(NodoEstudiante **CABEZA)
{
    NodoEstudiante *aux;
    while (*CABEZA != NULL)
    {
        aux = *CABEZA;
        *CABEZA = (*CABEZA)->ps;
        free(aux);
    }
}

NodoEstudiante Pop(NodoEstudiante **CABEZA)
{
    NodoEstudiante *aux;
    NodoEstudiante aux_comun;

    if (*CABEZA == NULL)
    {
        printf("\nLa lista esta vacia.\n");
        exit(-1);
    }
    else
    {
        aux = *CABEZA;
        aux_comun = *aux;

        *CABEZA = (*CABEZA)->ps;

        free(aux);
    }
    return aux_comun;
}

NodoEstudiante Top(NodoEstudiante **CABEZA)
{
    NodoEstudiante aux;
    if (*CABEZA == NULL)
    {
        printf("Lista vacia\n");
        exit(-1);
    }
    else
    {
        aux = **CABEZA;
    }
    return aux;
}
