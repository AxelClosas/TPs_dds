#include<stdio.h>
#include<stdlib.h>
#include <locale.h>
#include <windows.h>

typedef struct
{
    char nombre[100];
    char direccion[100];
    float ingresos;
    int hijos;
    long documento;
    char sexo;
    char estado_civil;
    int dia;
    int mes;
    int anio;

}Beneficiarios;

void config_entorno_ejecucion()
{
    //https://es.stackoverflow.com/questions/151363/leer-escribir-caracteres-especiales-del-espa%C3%B1ol-acentos-%C3%B1-en-una-aplicaci - fuente
    setlocale(LC_ALL, "spanish"); // Cambiar locale - Suficiente para máquinas Linux
    SetConsoleCP(1252); // Cambiar STDIN -  Para máquinas Windows
    SetConsoleOutputCP(1252);
}

void cargar_datos (){
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

    printf("Sexo\n\t[M] Masculino\n\t[F] Femenino\n\n%c",175);
    fflush(stdin);
    scanf("%c", &reg.sexo);
    printf("\n");

    printf("Estado civil\n\t[S] Soltero\n\t[C] Casado\n\t[V] Viudx\n\t[D] Divorciado\n\n%c ",175);
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
    scanf("%i",&reg.anio);
    printf("\n");


    FILE *pf = fopen("Beneficiarios.dat","ab");

    int total = fwrite(&reg,sizeof(reg),1,pf);
    if (total != 1){
    puts("error de carga");
    }
    fclose(pf);

}
void  mostrar ( Beneficiarios beneficiario){
    printf("\nNombre: %s\nDireccion: %sIngresos: %.2f\nhijos: %d\ndocumento: %ld\nSexo: %sestado civil: %sdia: %d\nmes: %d\nanio:%d \n"
            ,beneficiario.nombre,beneficiario.direccion,beneficiario.ingresos,beneficiario.hijos,beneficiario.documento
            ,beneficiario.sexo,beneficiario.estado_civil,beneficiario.dia,beneficiario.mes,beneficiario.anio);
    printf("===============================");

}

void mostrar_todos(){
    Beneficiarios beneficiario;
    FILE *pf = fopen("Beneficiarios.dat","rb");
    if (pf == NULL){
        puts("error al abrir el archivo");
        return -1;

    }
    fseek(pf, 0, SEEK_SET);
    fread(&beneficiario,sizeof(Beneficiarios),1,pf);
    while(!feof(pf)){
        mostrar(beneficiario);
        fread(&beneficiario,sizeof(Beneficiarios),1,pf);
    }
    fclose(pf);
}

void beneficiarios_varones(){
    Beneficiarios beneficiario;
    FILE* pf =fopen("Beneficiarios.dat","rb");

    if (pf == NULL){
        puts("error al abrir el archivo");
        return ;
    }
    rewind(pf);
    while(fread(&beneficiario,sizeof(Beneficiarios),1,pf)){

        if (beneficiario.sexo == 'M' && beneficiario.ingresos > 2500){

            printf("\nNombre: %sDocumento: %ld ingresos: %.2f \n",beneficiario.nombre,beneficiario.documento,beneficiario.ingresos);
            printf("=============================================");

        }
    }
    fclose(pf);
}

FILE *conexion()
{
    FILE *arch;
    arch = fopen("beneficiarios.dat", "a+b");
    return arch;
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

 int main(){
    config_entorno_ejecucion();
    int opcion;
    int mes=0;
    do
    {
        int op;

        puts("1. Cargar beneficiario");
        puts("2. Informe de Benf. varones con ingresos > 2500");
        puts("3. Generar listado de cumpleaños");
        puts("4. Mostrar todos los beneficiarios");
        printf("\n");
        puts("0. Salir");
        printf("\n");
        printf("\n>> ");
        scanf("%i", &op);


        switch(op)
        {
        case 1:
            cargar_datos();
            break;
        case 2:
            beneficiarios_varones();
            break;
        case 3:
            system("cls");
            printf("\nMes >> ");
            scanf("%i",&mes);
            listado_cumpl(mes);
            break;
        case 4:
            mostrar_todos();
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
