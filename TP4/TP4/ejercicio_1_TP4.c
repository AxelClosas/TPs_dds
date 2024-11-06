#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct libro
{
    char titulo[50];
    char autor[50];
    int anio;
} LIBRO;

void buscar_libro();
void listar_inventario(char nombre_arch[]);
void agregar_libro();
int guardar_libro(LIBRO p);

int main()
{
    int seguir=1;
    int otro_libro;
    do
    {
        int op=0;
        printf("SOFTWARE DE GESTI%cN DE LIBRER%cA",224, 214);
        printf("\n");
        printf("1. Ingresar nuevo libro\n");
        printf("2. Listar inventario\n");
        printf("3. Buscar libro por T%ctulo\n", 161);
        printf("0. Salir\n\n");

        printf("?? "); scanf("%i", &op);

        switch(op)
        {
        case 1:
            do
            {
                agregar_libro();
                printf("Ingresar otro libro? [1.SI, 0.NO]\n?? "); scanf("%i",&otro_libro);
            }while(otro_libro);
            break;
        case 2:
            system("cls");
            listar_inventario("inventario.txt");
            printf("\n");
            break;
        case 3:
            buscar_libro();
            break;
        case 0:
            return;
            break;
        }


    }while(seguir);

    return 0;
}

void agregar_libro()
{
    LIBRO nuevo;

    printf("Ingrese el T%ctulo del libro:\n", 161);
    fflush(stdin);
    gets(nuevo.titulo);

    printf("Ingrese el Autor del libro:\n");
    fflush(stdin);
    gets(nuevo.autor);

    printf("Ingrese el a%co de publicaci%cn del libro:\n", 162);
    fflush(stdin);
    scanf("%d", &nuevo.anio);

    guardar_libro(nuevo);

}

int guardar_libro(LIBRO p){
    FILE *archivo;
	archivo = fopen ("inventario.txt", "at");//add
	if(archivo == NULL){
		printf("No se pudo abrir el archivo.");
		return -1;
	}
    fprintf(archivo, "%s, %s, %d\n", p.titulo, p.autor, p.anio);
	fclose(archivo);
}

void listar_inventario(char nombre_arch[])
{
    FILE *archivo;
    char info[100];

    archivo = fopen(nombre_arch, "rt");
    if (archivo == NULL) return -1;
    puts("Inventario:");

    while ( !feof(archivo) )
    {
        fscanf(archivo,"%[^\n]\n", info);
        printf("%s\n", info);
    }

    fclose(archivo);
}

void buscar_libro()
{
    char nombre_libro[50];
    char contenido [100];
    char bandera = 'S';

    FILE *arch;
    arch = fopen("inventario.txt","rt");
    if (arch == NULL)
    {
        printf("\nerror al abrir archivo");
        return -1;
    }
    while (bandera == 'S' || bandera == 's')
    {
        int encontrado=0;
        printf("\nIngrese el nombre del libro: ");
        fflush(stdin);
        scanf("%[^\n]", nombre_libro);

        fseek(arch,0,SEEK_SET);

        while(fgets(contenido,sizeof(contenido),arch)!= NULL){
            char *resultado = strstr(contenido,nombre_libro);
            if (resultado != NULL){
                printf("\nEl contenido del libro buscado es: %s",contenido);
                encontrado = 1;
            }
        }
        if (encontrado != 1)
            printf("el libro no fue encontrado");


        printf("\nQuieres buscar otro libro [S/N]\n?? ");
        fflush(stdin);
        scanf("%c",&bandera);

    }
    fclose(arch);
}
