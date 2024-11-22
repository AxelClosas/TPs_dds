#include<stdio.h>
#include<stdlib.h>
#include <windows.h>
#include <locale.h>

typedef struct
{
    char nombre[100];
    char direccion[100];
    float ingresos;
    int hijos;
    long int documento;
    char sexo;
    char estado_civil;
    int dia;
    int mes;
    int anio;

}Beneficiarios;


void cargar_benef();
void ingresos_benef();
void listado_cumpl(int mes);
int guardar_archivo(Beneficiarios);


FILE *conexion()
{
    FILE *arch;
    arch = fopen("beneficiarios.dat", "a+b");
    return arch;
}


void config_entorno_ejecucion()
{
    //https://es.stackoverflow.com/questions/151363/leer-escribir-caracteres-especiales-del-espa%C3%B1ol-acentos-%C3%B1-en-una-aplicaci - fuente
    setlocale(LC_ALL, "spanish"); // Cambiar locale - Suficiente para máquinas Linux
    SetConsoleCP(1252); // Cambiar STDIN -  Para máquinas Windows
    SetConsoleOutputCP(1252);
}
int main()
{
    config_entorno_ejecucion();
    int opcion=1;
    int mes=0;
    do
    {
        int op;

        puts("1. Cargar beneficiario");
        puts("2. Informe de Benf. varones con ingresos > 2500");        puts("3. Generar listado de cumpleaños");
        printf("\n");
        puts("0. Salir");
        printf("\n");
        printf("\n>> ");
        scanf("%i", &op);


        switch(op)
        {
        case 1:
            cargar_benef();
            break;
        case 2:
            ingresos_benef();
            break;
        case 3:
            system("cls");
            printf("\nMes >> ",175);
            scanf("%i",&mes);
            listado_cumpl(mes);
            break;
        case 0:
            printf("Estas seguro que deseas salir? [1.SI, 0.NO]\n");
            printf("\n>> ");
            scanf("%i", &opcion);
            if (opcion) exit(0);
            break;
        default:
            printf("\nOpcio incorrecta. Vuelve a intentar\n");
            break;
        }

            printf("Continuar trabajando? [1.SI, 0.NO]\n");
            printf("\n>> ");
            scanf("%i", &opcion);
            if (opcion) system("cls");

    } while (opcion);


    return 0;
}

void cargar_benef()
{
    Beneficiarios reg; int res;

    printf("A continuacion ingrese los datos del beneficiario\n");
    printf("Nombre: ");
    fflush(stdin);
    gets(reg.nombre);
    printf("\n");

    printf("Dirección: ");
    fflush(stdin);
    gets(reg.direccion);
    printf("\n");

    printf("Ingresos: ");
    fflush(stdin);
    scanf("%f",&reg.ingresos);
    printf("\n");

    printf("Hijos: ");
    fflush(stdin);
    scanf("%i",&reg.hijos);
    printf("\n");

    printf("DNI: ");
    fflush(stdin);
    scanf("%ld",&reg.documento);
    printf("\n");

    printf("Sexo\n\t[M] Masculino\n\t[F] Femenino\n\n>> ");
    fflush(stdin);
    scanf("%c", &reg.sexo);
    printf("\n");
    printf("Estado civil\n\t[S] Soltero\n\t[C] Casado\n\t[V] Viudx\n\t[D] Divorciado\n\n>> ");
    fflush(stdin);
    scanf("%c",&reg.estado_civil);
    printf("\n");

    printf("Fecha de Nacimiento\n");
    printf("\tDia >> ");
    fflush(stdin);
    scanf("%i",&reg.dia);
//        printf("\n");

    printf("\tMes >> ");
    fflush(stdin);
    scanf("%i",&reg.mes);
//        printf("\n");

    printf("\tAño >> ");
    fflush(stdin);
    scanf("%i",&reg.anio);    printf("\n");

    if(!guardar_archivo(reg))
        printf("\n\tRegistro creado\n");
    else
        printf("No se pudo guardar el registro.");
}

int guardar_archivo(Beneficiarios reg)
{
    FILE *arch = conexion();

    if (arch == NULL) return 1;

    fwrite(&reg, sizeof(Beneficiarios), 1, arch);
    fclose(arch);

    return 0;
}
void ingresos_benef()
{
    Beneficiarios reg;

    FILE *arch = conexion();
    if (arch == NULL) return 1;

    system("cls");
    printf("Nombre\t\tDNI\n");

    fseek(arch, 0, SEEK_SET); // Coloca el puntero al inicio del archivo
    // BENEFICIARIOS BENEFICIARIOS

    fread(&reg, sizeof(Beneficiarios), 1, arch);
    // feof() retorna un valor distinto de 0 cuando se lee el fin de archivo.
    while (!feof(arch))
    {
        if (reg.ingresos >= 2500 && reg.sexo == 'M')
            printf("%s\t\t%ld\n", reg.nombre, reg.documento);


        fread(&reg, sizeof(Beneficiarios), 1, arch);
    }
    printf("\n\n");

    fclose(arch);

}
void listado_cumpl(int mes)
{
    Beneficiarios reg;
    FILE *arch = conexion();
    if (arch == NULL) return -1;

    fseek(arch, 0, SEEK_SET);
    printf("\n\tMes: %i\n\n",mes);
    puts("Nombre|Dirección|DNI|Hijos|Estado Civ.|Día\n");
    fread(&reg, sizeof(Beneficiarios), 1, arch);
    while (!feof(arch))
    {
        if(reg.mes == mes)
            printf("%s | %s | %ld | %i | %c | %i \n", reg.nombre,reg.direccion,reg.documento,reg.hijos,reg.estado_civil,reg.dia);
        fread(&reg, sizeof(Beneficiarios), 1, arch);
    }
    fclose(arch);
    system("pause");

}
