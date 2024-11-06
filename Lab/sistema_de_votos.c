#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct Partido
{
    long int id;
    char nombre[100];
    unsigned long int cant_votos_presi;
    unsigned long int cant_votos_gober;

    char valido;

}PARTIDO;

typedef struct Mesa
{
    long int id;
    long int cant_vot;
    unsigned long int cant_votos_blanco;
    unsigned long int cant_votos_impugnado;


    PARTIDO lista_partidos[100];

}MESA;

FILE *conexion_partidos()
{
    FILE *arch = fopen("Partidos.dat", "a+b");
    return arch;
}
FILE *crear_nuevo_archivo_mesas()
{
    FILE *arch = fopen("Mesas.dat", "wb");
    return arch;
}

FILE *conexion_mesas()
{
    FILE *arch = fopen("Mesas.dat", "a+b");
    return arch;
}

void linea_vacia_30_caracteres()
{
    int i;
    printf("%c",186);
    for (i=0; i < 28;i++)
        printf(" ");
    printf("%c",186);
    printf("\n");
}

void divisor_30_caracteres()
{
    int i;
    printf("%c",186);
    for (i=0; i < 28;i++)
        printf("-");
    printf("%c",186);
    printf("\n");
}

void nuevo_partido();
long int buscar_id(long int id, FILE *arch);
void listar_partidos();
void crear_mesas(int cant_mesas);
int cantidad_partidos_activos();
void listar_mesas();

int main()
{
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 7);
    int op_menu;
    int otro_part;
    int cant_mesas;
    int continuar;
    int op_salir = 0;
    int i;
    do
    {
        system("cls");
        //176: ░, 200: ╚, 201: ╔, 205: ═, 186: ║, 187: ╗, 188: ╝

        // Linea superior
        printf("%c",201);
        for (i=0; i<28; i++)
            printf("%c", 205);
        printf("%c",187);
        printf("\n");

        // PARTIDOS
        printf("%c",186);
        printf("%c",176);
        printf(" PARTIDOS ",176);
        for (i=0; i<17; i++)
            printf("%c", 176);
        printf("%c",186);
        printf("\n");

        // LISTA DE OPCIONES
        printf("%c[1] Cargar partidos         %c\n", 186, 186);
        printf("%c[2] Listar partidos         %c\n", 186, 186);
        printf("%c                            %c\n", 186, 186); // Espacio vacio de 30 caracteres

        // MESAS
        printf("%c",186);
        printf("%c",176);
        printf(" MESAS ",176);
        for (i=0; i<20; i++)
            printf("%c", 176);
        printf("%c",186);
        printf("\n");

//        printf("%c%c MESAS %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 186, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 186);
        // LISTA DE OPCIONES
        printf("%c[3] Crear Mesas             %c\n", 186, 186);
        printf("%c[4] Listar Mesas            %c\n", 186, 186);
        printf("%c[5] Contabilizar votos      %c\n", 186, 186);

        linea_vacia_30_caracteres();
        linea_vacia_30_caracteres();

        divisor_30_caracteres();
        printf("%c[0] SALIR                   %c\n", 186, 186); // Espacio vacio de 30 caracteres

        linea_vacia_30_caracteres();

        // Linea inferior
        printf("%c",200);
        for (i=0; i<28; i++)
            printf("%c", 205);
        printf("%c",188);

        printf("\n\n>> ");
        scanf("%i", &op_menu);

        switch(op_menu) {
            case 1:
                do
                {
                    nuevo_partido();
                    printf("\nCargar otro partido? [1.SI / 0.NO]\n\n>> ");
                    scanf("%i", &otro_part);
                }while(otro_part);

                break;

            case 2:
                listar_partidos();
                system("pause");
                break;
            case 3:
                system("cls");
                SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 4);
                printf("ATENCION! Este procedimiento implica BORRAR el archivo Mesas.dat si existe, y CREAR uno nuevo desde CERO(0), podrias perder informacion sensible si decides continuar.\n");

                printf("\nContinuar? [1.SI / 0.NO]\n>> ");
                scanf("%i", &continuar);
                if (continuar)
                {
                    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 7);
                    do
                    {
                        if (cant_mesas == 0)
                        {
                            system("CLS");
                            printf("La cantidad de mesas no puede ser 0.\n");
                        }
                        printf("Cantidad de mesas\n\n>> ");
                        scanf("%i", &cant_mesas);

                    } while(cant_mesas == 0);
                    crear_mesas(cant_mesas);
                }
                break;
            case 4:
                listar_mesas();
                break;
            case 0:
                system("cls");
                printf("Estas seguro que deseas salir? [1.SI / 0.NO]\n\n>> ");
                scanf("%i", &op_salir);
                if (op_salir)
                    break;
                else
                    op_salir = 0;
                break;
        }

    } while(!op_salir);

    return 0;
}


void nuevo_partido()
{
    system("cls");
    PARTIDO nuevo;
    FILE *arch = conexion_partidos();
    // TODOs: Mostrar un mensaje si no se pudo abrir el archivo. Hay varias lineas involucradas.
    if (arch == NULL) return -1;

    nuevo.valido = 'S';

    do
    {
        if (buscar_id(nuevo.id, arch) != -1)
        {
            system("cls");
            printf("ID existente.\n");
        }
        printf("ID >> ");
        fflush(stdin);
        scanf("%li", &nuevo.id);
        printf("\n");

    }while( buscar_id(nuevo.id, arch) != -1);

    printf("Nombre\n>> ");
    fflush(stdin);
    gets(nuevo.nombre);
    printf("\n");
    nuevo.cant_votos_presi = 0;
    nuevo.cant_votos_gober = 0;



    fwrite(&nuevo, sizeof(PARTIDO), 1, arch);
    fclose(arch);
}


long int buscar_id(long int id, FILE *arch)
{
    fpos_t pos_reg = -1;
    fpos_t pos_ini = ftell(arch);
    PARTIDO reg;

    fseek(arch, 0, SEEK_SET); // Ubica el puntero al inicio del archivo

    while ((fread(&reg, sizeof(PARTIDO), 1, arch)) && (pos_reg == -1) )
    {
        if (reg.id == id)
            pos_reg = ftell(arch) - sizeof(PARTIDO);
    }

    fseek(arch, pos_ini * sizeof(PARTIDO), SEEK_SET);

    return pos_reg;
}


void listar_partidos()
{
    FILE *arch = conexion_partidos();
    if (arch == NULL) return -1;

    PARTIDO reg;
    fseek(arch, 0, SEEK_SET);

    fread(&reg, sizeof(PARTIDO), 1, arch);

    while (!feof(arch))
    {
        printf("ID >> %li\n", reg.id);
        printf("Nombre >> %s\n", reg.nombre);
        printf("Partido activo >> %c\n", reg.valido);
        printf("\n");
        fread(&reg, sizeof(PARTIDO), 1, arch);
    }

    fclose(arch);
}

int cantidad_partidos_activos()
{
    int cant = 0;
    PARTIDO reg;
    FILE *arch = conexion_partidos();    if (arch == NULL) return -1;


    fread(&reg, sizeof(PARTIDO), 1, arch);
    while(!feof(arch))
    {
        if (reg.valido == 'S')
            cant++;

        fread(&reg, sizeof(PARTIDO), 1, arch);
    }
    fclose(arch);
    return cant;

}
void crear_mesas(int cant_mesas)
{
    int cant_part = cantidad_partidos_activos();

    FILE *arch_mesas = crear_nuevo_archivo_mesas();
    if (arch_mesas == NULL) return -1;

    FILE *arch_part = conexion_partidos();
    if (arch_part == NULL) return -1;

    if (cant_part == 0)
    {
        printf("Error. Debe existir al menos un partido para crear las mesas.\n");
        exit(-1);
    }

    int i;
    for (i=0; i < cant_mesas; i++)
    {
        int j;
        MESA nueva;
        PARTIDO aux;

        nueva.id = i+1;
        nueva.cant_vot = 0;
        nueva.cant_votos_blanco = 0;
        nueva.cant_votos_impugnado = 0;

        fseek(arch_part, 0, SEEK_SET);

        fread(&aux, sizeof(PARTIDO), 1, arch_part);
        for (j=0; j < cant_part; j++)
        {
            if (!feof(arch_part))
                nueva.lista_partidos[j] = aux;

            fread(&aux, sizeof(PARTIDO), 1, arch_part);
        }
        fwrite(&nueva, sizeof(MESA), 1, arch_mesas);
    }

    fclose(arch_mesas);
    fclose(arch_part);
}

void listar_mesas()
{
    int cant_part = cantidad_partidos_activos();
    FILE *arch = conexion_mesas();
    MESA reg;

    if (arch == NULL)
    {
        printf("Error al abrir el archivo.");
        exit(-1);
    }

    fseek(arch, 0, SEEK_SET);

    fread(&reg, sizeof(MESA), 1, arch);

    while (!feof(arch))
    {
        int i;
        printf("\n------------------------------\n");
        printf("Nro. de Mesa >> %li\n", reg.id);

        printf("ID PARTIDO -- NOMBRE DE PARTIDO\n");
        for (i=0; i < cant_part; i++)
        {

            printf("    %i     ", reg.lista_partidos[i].id);
            printf("    %s     \n", reg.lista_partidos[i].nombre);

        }
        fread(&reg, sizeof(MESA), 1, arch);
    }
    system("pause");
    fclose(arch);
}
