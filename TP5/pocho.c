#include <stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Nodo
{
    char *nombre;
    int edad;
    float promedio;
    struct Nodo *sig;
}alumno;

alumno* add(alumno*lista,char *nombre,int edad,float promedio)
{
    alumno *nuevo_alu,*temp;
    nuevo_alu = (alumno*)malloc(sizeof(alumno));
    if (nuevo_alu == NULL)
    {
        puts("error de memoria");
        exit(-1);
    }
    nuevo_alu->nombre = (char*)malloc(sizeof(nombre));
    if(nuevo_alu->nombre == NULL)
    {
        puts("error al asignar memoria");
        exit(-1);
    }
    strcpy(nuevo_alu->nombre,nombre);
    nuevo_alu->edad = edad;
    nuevo_alu->promedio = promedio;
    nuevo_alu->sig = NULL;
    if (lista == NULL)
    {
       lista = nuevo_alu;
    }
    else
    {
        //agrega al pricipio
        /*nuevo_alu->sig = lista;
        lista = nuevo_alu;*/

        //agrega al final
        temp = lista;
        while(temp->sig != NULL)
        {
           temp = temp->sig;
        }
        temp->sig = nuevo_alu;
    }

    return lista;
}
void imprimir(alumno *lista)
{
    int i = 0;
    printf("========================");
    while(lista != NULL)
    {

        printf("\nDatos del alumno %d\nNombre: %s\nEdad: %d\nPromedio: %.2f\n",i+1,lista->nombre,lista->edad,lista->promedio);
        printf("========================");
        lista = lista->sig;
        i++;
    }
}

void liberar_lista(alumno *lista)
{
    alumno *temp;
    while(lista != NULL)
    {
        temp = lista;
        lista = lista->sig;
        free(temp->nombre);
        free(temp);
    }
}


int main()
{
    alumno *alu;
    alu = NULL;

    int n;
    printf("ingrese la cantidad de alumnos que agregar: ");
    scanf("%d",&n);

    for(int i=0;i<n;i++)
    {
        char nombre[31];
        int edad;
        float prom;

        printf("\ningrese el nombre del alumno %d: ",i+1);
        fflush(stdin);
        gets(nombre);
        printf("ingrese la edad del alumno %d: ",i+1);
        fflush(stdin);
        scanf("%d",&edad);
        printf("ingrese el promedio del alumno %d: ",i+1);
        fflush(stdin);
        scanf("%f",&prom);

        alu = add(alu,nombre,edad,prom);



    }

    printf("\nlos alumnos que ingreso: \n");
    imprimir(alu);
    liberar_lista(alu);
    return 0;

}
