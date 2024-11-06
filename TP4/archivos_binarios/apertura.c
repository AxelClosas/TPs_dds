#include <stdio.h>
#include <stdlib.h>

typedef struct
{
char nombre[100];
char direccion[100];
float ingresos;
int hijos;
long documento;
char sexo[10];
char estado_civil[15];
int dia;
int mes;
int anio;

}Beneficiarios;

struct reg
{
    int numero;
};

int main()
{
    // Apertura de archivo binario
    FILE *archivo;
//    archivo = fopen("beneficiarios.dat", "wb");
//    if (archivo == NULL) return -1;

    // Escritura de archivo binario
    // fwrite(dir-buffer, tam, num_elem, punt_arch)

//    struct reg nuevo;
//    printf("numero: ");
//    scanf("%i", &nuevo.numero);
//    int i;
//    for (i=0; i < 5; i++)
//    {
//        fwrite(&nuevo, sizeof(struct reg), 1, archivo);
//    }
//    fclose(archivo);
//


    archivo = fopen("beneficiarios.dat", "rb");
    if (archivo == NULL)
        exit(-1);


    Beneficiarios beneficiario;

    rewind(archivo);

    while (fread(&beneficiario, sizeof(Beneficiarios), 1, archivo) == 1)
    {
//        int a = fread(&beneficiario, sizeof(Beneficiarios), 1, archivo);
//        printf("%i", a);

        printf("%s\n", beneficiario.nombre);
        printf("%s\n", beneficiario.direccion);
    }

    fclose(archivo);

    return 0;
}
