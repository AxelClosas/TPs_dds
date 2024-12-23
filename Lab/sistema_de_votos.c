#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "C:\Users\axelc\dev\TPs_dds\Lab\css.c"

typedef struct Partido
{
    long int id;
    char nombre[20];
    unsigned long int cant_votos_presi;
    unsigned long int cant_votos_gober;
    short int activo;

}PARTIDO;

typedef struct Mesa
{
    long int id;
    long int cant_vot;
    unsigned long int cant_votos_blanco;
    unsigned long int cant_votos_impugnado;

    PARTIDO lista_partidos[100];
}MESA;

/* LOGICA */

        /* PARTIDOS */
long int buscar_id(long int id, FILE *arch);
void nuevo_partido();
void listar_partidos();
void listar_partidos_activos();
void editar_partido();
// Renombrar el archivo Partido.dat a Partido.bak y generar un nuevo Partido.dat con los partidos activos únicamente
void proceso_baja_fisica(FILE **arch_part);

int mostrar_datos(PARTIDO *reg);
void encabezado_tabla_partidos(PARTIDO *reg);
int cantidad_partidos_activos();

void proceso_cambiar_nombre(long int id, FILE *arch);
void proceso_eliminar_registro(long int id, FILE *arch);

        /* MESAS */
void crear_mesas(int cant_mesas);
int advertencia();

void listar_mesas();

        /* PROCESOS */


int main()
{
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 7);
    int op_menu;
    int otro_part;
    int cant_mesas;
    int continuar;
    int op_salir = 0;
    int id_partido;
    int i;
    do
    {
        op_menu = menu();

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
                listar_partidos_activos();
                system("pause");
                break;
            case 3:
                listar_partidos();
                system("pause");
                break;
            case 4:
                editar_partido();
                system("pause");
                break;

            case 6:
                system("cls");
                cant_mesas = advertencia();
                if (cant_mesas > 0)
                    crear_mesas(cant_mesas);

                break;
            case 7:
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
void encabezado(int espacio_izq, int op)
{
    // Trabajo con el interior, espacio_izq = n caracteres ascii para centrar el encabezado
    int i;
    int espacio_interior = 30;
    int cant_ascii_lateral = 1; // lateral
    int rellenar = 0;
    char partidos[]="PARTIDOS";
    size_t t_partidos = 0;
    char mesas[]="MESAS";
    size_t t_mesas = 0;
    char procesos[]="PROCESOS";
    size_t t_procesos = 0;
    char admin[] = "PANEL ADMIN";
    size_t t_admin = 0;
    char informacion[] = "INFORMACION";
    size_t t_informacion = 0;

    switch (op)
    {
    case 4:
        t_admin = strlen(admin);
        printf("%c", 186);
        for (i=0; i < espacio_izq; i++)
            printf("%c", 176);
        printf(" ");
        printf("%s",admin); // n letras
        printf(" ");
        rellenar = espacio_interior - cant_ascii_lateral - cant_ascii_lateral - espacio_izq - 2 - t_admin ; // El num en la formula es la cant. de printf(" ");
        for (i=0; i < rellenar; i++)
            printf("%c", 176);
        printf("%c", 186);
        break;

    case 1:
        t_partidos = strlen(partidos);
        printf("%c", 186);
        for (i=0; i < espacio_izq; i++)
            printf("%c", 176);
        printf(" ");
        printf("%s",partidos); // n letras
        printf(" ");
        rellenar = espacio_interior - cant_ascii_lateral - cant_ascii_lateral - espacio_izq - 2 - t_partidos ; // El num en la formula es la cant. de printf(" ");
        for (i=0; i < rellenar; i++)
            printf("%c", 176);
        printf("%c", 186);
        break;
    case 2:
        t_mesas = strlen(mesas);
        printf("%c", 186);
        for (i=0; i < espacio_izq; i++)
            printf("%c", 176);
        printf(" ");
        printf("%s",mesas); // n letras
        printf(" ");
        rellenar = espacio_interior - cant_ascii_lateral - cant_ascii_lateral - espacio_izq - 2 - t_mesas ; // El num en la formula es la cant. de printf(" ");
        for (i=0; i < rellenar; i++)
            printf("%c", 176);
        printf("%c", 186);
        break;

    case 3:
        t_procesos = strlen(procesos);
        printf("%c", 186);
        for (i=0; i < espacio_izq; i++)
            printf("%c", 176);
        printf(" ");
        printf("%s",procesos); // n letras
        printf(" ");
        rellenar = espacio_interior - cant_ascii_lateral - cant_ascii_lateral - espacio_izq - 2 - t_procesos ; // El num en la formula es la cant. de printf(" ");
        for (i=0; i < rellenar; i++)
            printf("%c", 176);
        printf("%c", 186);
        break;
    case 5:
        t_informacion = strlen(informacion);
        printf("%c", 186);
        for (i=0; i < espacio_izq; i++)
            printf("%c", 176);
        printf(" ");
        printf("%s",informacion); // n letras
        printf(" ");
        rellenar = espacio_interior - cant_ascii_lateral - cant_ascii_lateral - espacio_izq - 2 - t_informacion ; // El num en la formula es la cant. de printf(" ");
        for (i=0; i < rellenar; i++)
            printf("%c", 176);
        printf("%c", 186);
        break;

    }
    // PARTIDOS


}
int menu()
{
    int op_menu;
    int i;
    system("cls");
    //176: ░, 200: ╚, 201: ╔, 205: ═, 186: ║, 187: ╗, 188: ╝
    // Linea superior
    printf("%c",201);
    for (i=0; i<28; i++)
        printf("%c", 205);
    printf("%c",187);
    printf("\n");
    // Linea superior
    /* PANEL ADMIN */
    encabezado(1, 4);
    printf("\n");
        // LISTA DE OPCIONES
    printf("%c[1] Cargar partidos         %c\n", 186, 186);
    printf("%c[4] Editar partido          %c\n", 186, 186);
    printf("%c[6] Crear Mesas             %c\n", 186, 186);
    linea_vacia_30_caracteres();
    linea_vacia_30_caracteres();
    /* PARTIDOS */
    encabezado(1, 1);
    printf("\n");
        // LISTA DE OPCIONES
    printf("%c[2] Listar partidos activos %c\n", 186, 186);
    printf("%c[3] Listar todos los part.  %c\n", 186, 186);
    linea_vacia_30_caracteres();
        /* MESAS */
    encabezado(1, 2);
    printf("\n");
        // LISTA DE OPCIONES
    printf("%c[7] Listar Mesas            %c\n", 186, 186);
    linea_vacia_30_caracteres();
    /* PROCESOS */
    encabezado(1, 3);
    printf("\n");
        // LISTA DE OPCIONES
    printf("%c[99] Contabilizar votos     %c\n", 186, 186);
    linea_vacia_30_caracteres();
    linea_vacia_30_caracteres();
    divisor_30_caracteres();
    printf("%c[0] SALIR                   %c\n", 186, 186); // Espacio vacio de 30 caracteres
    // Linea inferior
    printf("%c",200);
    for (i=0; i<28; i++)
        printf("%c", 205);
    printf("%c",188);
    printf("\n\n>> ");
    scanf("%i", &op_menu);
    return op_menu;
}
void nuevo_partido()
{
    system("cls");
    PARTIDO nuevo;
    FILE *arch = fopen("Partidos.dat", "a+b");
    if (arch == NULL)
    {
        printf("No se pudo abrir el archivo Partidos.dat");
        return -1;
    }
    nuevo.activo= 1;
    nuevo.cant_votos_presi = 0;
    nuevo.cant_votos_gober = 0;
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

    printf("Nombre (max. %i caracteres)\n>> ", sizeof(nuevo.nombre));
    fflush(stdin);
    gets(nuevo.nombre);
    printf("\n");

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

void encabezado_tabla_partidos(PARTIDO *reg)
{
    if (&reg != NULL)
    {
        int i;
        for (i=0; i< 3; i++) printf(" "); // Imprime 3 espacios seguidos
        printf("ID");
        for (i=0; i< 3; i++) printf(" "); // Imprime 3 espacios seguidos

        for (i=0; i<7; i++) printf(" "); // Imprime 6 espacios seguidos
        printf("NOMBRE");
        for (i=0; i<7; i++) printf(" "); // Imprime 6 espacios seguidos

        for (i=0; i< 3; i++) printf(" "); // Imprime 3 espacios seguidos
        printf("ACTIVO");
        for (i=0; i< 3; i++) printf(" "); // Imprime 3 espacios seguidos

        printf("\n");
        divisor_35_caracteres();
    }
}
void listar_partidos_activos()
{
    FILE *arch = fopen("Partidos.dat", "rb");
    if (arch == NULL) return -1;
    PARTIDO reg;
    fseek(arch, 0, SEEK_SET);
    encabezado_tabla_partidos(&reg);
    fread(&reg, sizeof(PARTIDO), 1, arch);
    while (!feof(arch))
    {
        if (reg.activo == 1)
        {
            int i;
            int cant_letras=0;
            for (i=0; i< 3; i++) printf(" "); // Imprime 3 espacios seguidos
            printf("%li", reg.id);
            for (i=0; i< 3; i++) printf(" "); // Imprime 3 espacios seguidos

            cant_letras = strlen(reg.nombre);
            if (cant_letras != 20)
            {
                printf("%s", reg.nombre);
                int n = 20 - cant_letras;
                for (i=0; i < n; i++) printf(" "); // Imprime n espacios seguidos después del nombre
            }
            else
                printf("%s", reg.nombre);

            for (i=0; i< 6; i++) printf(" "); // Imprime 5 espacios seguidos
            printf("%i\n", reg.activo);
            for (i=0; i< 6; i++) printf(" "); // Imprime 5 espacios seguidos
            printf("\n");
        }
        fread(&reg, sizeof(PARTIDO), 1, arch);
    }
    fclose(arch);
}


void listar_partidos()
{
    FILE *arch = fopen("Partidos.dat", "rb");
    if (arch == NULL) return -1;
    PARTIDO reg;
    fseek(arch, 0, SEEK_SET);
    encabezado_tabla_partidos(&reg);
    fread(&reg, sizeof(PARTIDO), 1, arch);
    while (!feof(arch))
    {

        int i;
        int cant_letras=0;
        for (i=0; i< 3; i++) printf(" "); // Imprime 3 espacios seguidos
        printf("%li", reg.id);
        for (i=0; i< 3; i++) printf(" "); // Imprime 3 espacios seguidos

        cant_letras = strlen(reg.nombre);
        if (cant_letras != 20)
        {
            printf("%s", reg.nombre);
            int n = 20 - cant_letras;
            for (i=0; i < n; i++) printf(" "); // Imprime n espacios seguidos después del nombre
        }
        else
            printf("%s", reg.nombre);

        for (i=0; i< 6; i++) printf(" "); // Imprime 5 espacios seguidos
        printf("%i\n", reg.activo);
        for (i=0; i< 6; i++) printf(" "); // Imprime 5 espacios seguidos
        printf("\n");
        fread(&reg, sizeof(PARTIDO), 1, arch);
    }
    fclose(arch);
}

int cantidad_partidos_activos()
{
    int cant = 0;
    PARTIDO reg;

    FILE *arch = fopen("Partidos.dat", "rb");
    if (arch == NULL){
        printf("No se pudo abrir el archivo Partidos.dat");
        return -1;
    }

    fread(&reg, sizeof(PARTIDO), 1, arch);
    while(!feof(arch))
    {
        if (reg.activo == 1) cant++;
        fread(&reg, sizeof(PARTIDO), 1, arch);
    }
    fclose(arch);
    return cant;
}


void crear_mesas(int cant_mesas)
{
    int cant_part = cantidad_partidos_activos();

    FILE *arch_mesas = fopen("Mesas.dat", "wb");
    if (arch_mesas == NULL)
    {
        printf("No se pudo abrir el archivo Mesas.dat");
        return -1;
    }

    FILE *arch_part = fopen("Partidos.dat", "rb");
    if (arch_part == NULL)
    {
        printf("No se pudo abrir el archivo Partidos.dat");
        return -1;
    }
    if (cant_part == 0)
    {
        printf("Error. Debe existir al menos un partido para crear las mesas.\n");
        exit(-1);
    }

    int i;
    for (i=0; i < cant_mesas; i++)
    {
        MESA nueva;
        PARTIDO aux;

        nueva.id = i+1;
        nueva.cant_vot = 0;
        nueva.cant_votos_blanco = 0;
        nueva.cant_votos_impugnado = 0;


        fseek(arch_part, 0, SEEK_SET);
        // K -> Posicionar los partidos en el array lista_partidos
        int k = 0;
        fread(&aux, sizeof(PARTIDO), 1, arch_part);
        while (!feof(arch_part))
        {
            if (aux.activo == 1) {
                nueva.lista_partidos[k] = aux;
                k++;
            }
            fread(&aux, sizeof(PARTIDO), 1, arch_part);
        }
        fwrite(&nueva, sizeof(MESA), 1, arch_mesas);

    }
    fclose(arch_mesas);
    fclose(arch_part);
}

int advertencia()
{   int cant_mesas = 1;
    int continuar;

    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 4);
    printf("ATENCION! Este procedimiento implica BORRAR el archivo Mesas.dat si existe,\n");
    printf("y CREAR uno nuevo desde CERO(0), podrias perder informacion sensible si decides continuar.\n");
    printf("\nContinuar?\n\t[1] SI\n\t[0] NO\n\n>> ");
    scanf("%i", &continuar);

    if (continuar)
    {
        system("cls");
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
    }
    else
        cant_mesas = 0;

    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 7);

    return cant_mesas;
}
void listar_mesas()
{
    int cant_part = cantidad_partidos_activos();
    FILE *arch = fopen("Mesas.dat", "rb");
    MESA reg;
    if (arch == NULL)
    {
        printf("Error al abrir el archivo Mesas.dat\n");
        exit(-1);
    }
    fseek(arch, 0, SEEK_SET);
    fread(&reg, sizeof(MESA), 1, arch);

    int p;
    printf("[ID_M]");
    for (p=0; p < cant_part; p++)    
        printf("\t[ID_P%i]\t[V_P%i]\t[V_G%i]\t", p+1, p+1, p+1);
    printf("\n");
    while (!feof(arch))
    {
        int i;
        // printf("\n------------------------------\n");
        printf("[%li]", reg.id);
        // printf("ID PARTIDO -- NOMBRE DE PARTIDO\n");
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

int mostrar_datos(PARTIDO *reg)
{
    int confirmar;
    system("cls");
    printf("Partido seleccionado\n");
    printf("ID [%li]\n", reg->id);
    printf("NOMBRE: %s\n", reg->nombre);
    printf("\nConfirmas la seleccion?\n\t[1] SI\n\t[0] NO\n>> ");
    fflush(stdin);
    scanf("%i", &confirmar);
    return confirmar;
}


void proceso_cambiar_nombre(long int id, FILE *arch)
{
    PARTIDO reg;
    long pos_reg = buscar_id(id, arch);
    fseek(arch, pos_reg, SEEK_SET);

    int falla = fread(&reg, sizeof(PARTIDO),1,arch);
    if (falla != 1) {
        printf("Fallo la lectura.");
        exit(-1);
    }

    printf("ID [%li]\n", reg.id);
    printf("\nNombre >> ");
    fflush(stdin);
    gets(reg.nombre);

    fseek(arch, pos_reg, SEEK_SET);
    falla = fwrite(&reg, sizeof(PARTIDO), 1, arch);
    fflush(arch);

    if (falla == 1)
    {
        printf("\nRegistro modificado con exito.\n");
        system("pause");
    }
    else
    {
        printf("\nNo se podido modificar el registro.\n");
        system("pause");
    }
}
void proceso_eliminar_registro(long int id, FILE *arch)
{
    PARTIDO reg;
    long pos_reg = buscar_id(id, arch);
    fseek(arch, pos_reg, SEEK_SET);

    int falla = fread(&reg, sizeof(PARTIDO),1,arch);
    if (falla != 1) {
        printf("Fallo la lectura.");
        exit(-1);
    }
    reg.activo = 0;
    reg.id = 0;

    fseek(arch, pos_reg, SEEK_SET);
    falla = fwrite(&reg, sizeof(PARTIDO), 1, arch);
    if (falla == 1)
    {
        printf("\nRegistro eliminado\n");
    }
    else {
        printf("\nNo se pudo eliminar el archivo.\n");
        exit(-1);
    }
}
void proceso_baja_fisica(FILE **arch_part)
{
    FILE *nuevo_temp;
    PARTIDO aux;
    nuevo_temp = fopen("Partidos.tmp", "wb");
    rewind(*arch_part);
    fread(&aux, sizeof(PARTIDO), 1, *arch_part);
    while (!feof(*arch_part))
    {
        if (aux.activo == 1)
            fwrite(&aux, sizeof(PARTIDO), 1, nuevo_temp);
        fread(&aux, sizeof(PARTIDO), 1, *arch_part);
    }
    fclose(nuevo_temp);
    fclose(*arch_part);

    remove("Partidos.bak");

    if ( (rename("Partidos.dat", "Partidos.bak")) == 0 )
        printf("Archivo Partidos.dat renombrado por: Partidos.bak\n");
    else
        printf("No se pudo renombrar el archivo Partidos.dat.\n");

    system("pause");

    if ( (rename("Partidos.tmp", "Partidos.dat")) == 0 )
        printf("Archivo Partidos.tmp renombrado por: Partidos.dat\n");
    else
        printf("No se pudo renombrar el archivo Partidos.tmp.\n");

}
void editar_partido()
{
    long int id;
    long pos_reg;
    int op;
    int confirmar;
    FILE *arch_part = fopen("Partidos.dat", "r+b");
    if (arch_part == NULL) {
        printf("No se pudo abrir el archivo Partidos.dat");
        exit(-1);
    }
    PARTIDO reg;

    do {
        do
        {   fseek(arch_part, 0, SEEK_SET);
            printf("\nLista de partidos disponibles\n\n");
            listar_partidos_activos();
            printf("\n");
            printf("Ingresa el ID del partido que desees EDITAR\n>> ");
            fflush(stdin);
            scanf("%li", &id);
            // Recupero la posición del registro
            pos_reg = buscar_id(id, arch_part);
            system("cls");
            if (pos_reg == -1) printf("Partido no encontrado. Prueba a ingresar otro ID\n\n");
        }while(pos_reg == -1);

        // Ubico el puntero del archivo al inicio registro ubicado
        fseek(arch_part, pos_reg, SEEK_SET);
        // Leo el registro
        fread(&reg, sizeof(PARTIDO), 1, arch_part);
        // Muestro los datos y valido
        int confirmar = mostrar_datos(&reg);
        if (confirmar == 1)
        {
            printf("\nAcciones");
            printf("\n\t[1] Cambiar nombre");
            printf("\n\t[2] Eliminar partido");
            printf("\n>> ");
            scanf("%i", &op);

            if (op == 1) proceso_cambiar_nombre(id, arch_part);

            if (op == 2)
            {   proceso_eliminar_registro(id, arch_part);
                proceso_baja_fisica(&arch_part);
            }
        }
    }
    while(!confirmar);
    fclose(arch_part);
}

