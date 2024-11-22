#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tam_apeynom 50
#define tam_usuario 10
#define tam_pass 12

typedef struct usuario
{
    char apeynom[tam_apeynom];
    char usuario[tam_usuario];
    char pass[tam_pass];
    short int rol;

}Usuario;

void registrarse();
void iniciar_sesion();

int main()
{
    int op;

    do
    {
        op = menu();
        switch(op)
        {
        case 1:
            iniciar_sesion();
            break;
        case 2:
            registrarse();
            break;
        case 0:
            system("cls");
            printf("Hasta pronto!");
            break;
        default:
            printf("Opcion no disponible.\n");
            continue;
        }

    } while (op!=0);
}


int menu()
{
    int op;
    printf("\n1. INICIAR SESION\n");
    printf("\n2. REGISTRARSE\n");
    printf("\n0. SALIR\n");
    printf("\n>> ");
    fflush(stdin);
    scanf("%i", &op);
    return op;
}

void registrarse()
{
    Usuario nuevo; int op;
    printf("1. Perfil Admin")
    system("cls");
    puts("Formulario de registro");
    printf("\nNombre completo: ");
    fflush(stdin);
    gets(nuevo.apeynom);

    printf("\nUsuario: ");
    fflush(stdin);
    gets(nuevo.usuario);

    printf("\nContraseña: ");
    fflush(stdin);
    gets(nuevo.pass);
}
