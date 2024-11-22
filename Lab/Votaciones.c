#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxPartidos 2
// Cambio
int pass_admin= 9898;

typedef struct Partido
{
    int codigo;
    char nombrePartido[100];
    unsigned long int cant_votos_presi;
    unsigned long int cant_votos_gober;
    int Borrado;
}Partidos;

typedef struct Mesa
{
    long int nroMesa;
    unsigned long int votos_impug;
    unsigned long int votos_blanco;
    unsigned long int votos;
    Partidos par[maxPartidos];
    int borrado;
}mesas;

// partidos
int altaPartido(); // OK
long keyPartido(FILE*pf,int key); // OK
int listarPartidos(); // OK
int modificarPar(); // OK
int removerPartido(); // OK
int limpiezaPar(); // OK
// mesas
long keyMesas(FILE*pf,long int key); // OK
int mostrarMesas(); // OK
int limpiarMesa(); // OK
int Baja_Mesa(); // OK
int escribirMesa(); // Falta agregar ordenamiento por inserción
int info_Mesa(); // OK

int menu1()
{
        int opcion;
        int pass;
        int control;
        system("cls");
        do
        {
            system("cls");
            printf("\n[1]. Ingresar Partidos");
            printf("\n[2]. Listar Partidos");
            printf("\n[3]. Modificar partidos");
            printf("\n[4]. Borrar partidos");
            printf("\n[5]. Mesas");
            printf("\n[7]. Salir");
            printf("\nOpcion: ");
            fflush(stdin);
            scanf("%d",&opcion);

            if ((opcion == 1) || (opcion == 4) || (opcion == 3))
            {   printf("Contrase%ca\n>> ",164);
                fflush(stdin);
                scanf("%i", &pass);
                if (pass == pass_admin)
                    control = 1;
                else
                {
                    printf("Contrase%ca incorrecta!\n", 164);
                    control = 0;
                    system("pause");
                }
            }
            else
                control = 1;

        } while (control == 0);

        return opcion;
}
int menu2()
{
    int pass, control, opcion;
    do
    {
        system("cls");
        printf("\n[1]. Cargar Mesa");
        printf("\n[2]. Listar Mesas");
        printf("\n[4]. Relevamiento de Mesa"); // Relevamiento de mesas: Permitir ver información de una mesa en particular ordenado de mayor a menor según la cantidad de votos de cada cargo y poniendo el porcentaje correspondiente.
        printf("\n[5]. Borrar Mesa");
        printf("\n[6]. salir\nOpcion: ");
        fflush(stdin);
        scanf("%d",&opcion);
        if (opcion == 5)
        {   printf("Contrase%ca\n>> ",164);
            fflush(stdin);
            scanf("%i", &pass);
            if (pass == pass_admin)
                control = 1;
            else
            {
                printf("Contrase%ca incorrecta!\n", 164);
                control = 0;
                system("pause");
            }
        }
        else
            control = 1;

        } while (control == 0);

        return opcion;
}

int main()
{   int opcion,op1;
    do
    {
        opcion = menu1();
        switch (opcion)
        {
        case 1:
            altaPartido();
            break;
        case 2:
            listarPartidos();
            break;
        case 3:
            modificarPar();
            break;
        case 4:
            removerPartido();
            break;

        case 5:// MESAS
            do
            {   op1 = menu2();
                switch(op1)
                {
                case 1:
                    escribirMesa();
                    break;
                case 2:
                    mostrarMesas();
                    printf("\n");
                    system("pause");
                    break;
                case 4:
                    info_Mesa(); // TODO;
                    break;
                case 5:
                    Baja_Mesa();

                    break;
                case 6:
                    printf("\nSaliendo...\n");
                    system("pause");
                    break;
                default :
                    printf("\nOpcion invalida");
                    break;
                }
            }while(op1 != 6);
            break;
        case 7:
            puts("saliendo...");
            break;
        default:
            puts("Opcion invalida");
            break;

        }
    }while(opcion != 7);
    return 0;

}
long keyPartido(FILE*pf,int key)
{
    Partidos partido;
    long posReg = -1;
    fseek(pf,0,SEEK_SET);
    fread(&partido,sizeof(partido),1,pf);
    while(!feof(pf))
    {
        if (key == partido.codigo)
        {
            posReg = ftell(pf)-sizeof(Partidos);
        }
        fread(&partido,sizeof(partido),1,pf);
    }
    return posReg;
}

int altaPartido()
{
    Partidos par;
    int op;
    FILE*ptr = fopen("Partidos.dat","a+b");
    if (ptr == NULL) {
        puts("error al abrir el archivo");
        return -1;
    }
    do
    {
        fseek(ptr,0,SEEK_END);
        long tam = ftell(ptr)/sizeof(Partidos);
        if (tam == maxPartidos)
        {
            puts("No se puede agregar mas partidos");
            system("pause");
            return -1;
        }
        printf("\nIngrese el Codigo del partido: ");
        fflush(stdin);
        scanf("%d",&par.codigo);
        if (keyPartido(ptr,par.codigo) == -1)
        {
            printf("Ingrese el Nombre del Partido: ");
            fflush(stdin);
            gets(par.nombrePartido);
        }
        else
        {
           printf("\nYa existe un partido con este codigo\n");
           system("pause");
           return -1;
        }
        fseek(ptr,0,SEEK_END);
        int falla = fwrite(&par,sizeof(Partidos),1,ptr);
        if (falla != 1)
        {
            puts("error de escritura");
            return -1;
        }
        fflush(ptr);
        printf("\nQuieres ingresar otro partido SI/1 NO/0\nOpcion: ");
        scanf("%d",&op);
    }while(op == 1);
    fclose(ptr);
    return 0;
}

int listarPartidos ()
{
    Partidos par;
    FILE*pf = fopen("Partidos.dat","rb");
    if (pf == NULL)
    {
        puts("error al abrir el archivo"); system("pause");
        return -1;
    }
    fseek(pf,0,SEEK_SET);
    fread(&par,sizeof(Partidos),1,pf);
    while(!feof(pf))
    {
        printf("\nCodigo: %d",par.codigo);
        printf("\nNombre del Partido: %s",par.nombrePartido);
        fread(&par,sizeof(Partidos),1,pf);
    }
    printf("\n");
    system("pause");
    fclose(pf);

    return 0;
}

int modificarPar()
{
    /*
        Verificar que existan mesas
        Cuando se modifiqué el nombre (al final), recorrer el archivo Mesas.dat y modificar cada
    */
    int flag = 0;
    mesas mesa;
    Partidos par;
    long int cod_part;
    int op;
    int op1;
    FILE*ptr_mesas = fopen("Mesas.dat","r+b");
    if (ptr_mesas == NULL)
    {
        puts("paso 1");
        flag = 0;
    }
    else
        puts("paso 2");
        flag = 1;

    FILE*ptr = fopen("Partidos.dat","r+b");
    if (ptr == NULL)
    {
        puts("error al abrir el archivo");
        system("pause");
        return -1;
    }
    do
    {
        listarPartidos();
        printf("\nIngrese el codigo del partido que desea modifcar: ");
        fflush(stdin);
        scanf("%d",&cod_part);
        long pos = keyPartido(ptr,cod_part);
        if (pos == -1)
        {
            puts("No hay ningun partido con ese codigo");
            system("pause");
            return -1;
        }
        fseek(ptr,pos,SEEK_SET);
        int falla = fread(&par,sizeof(Partidos),1,ptr);
        if (falla != 1)
        {
            puts("error al leer el archivo");
            system("pause");
            return -1;
        }
        else
        {
            printf("\nCodigo: %d",par.codigo);
            printf("\nNombre del Partido: %s",par.nombrePartido);
            printf("\nEste es el partido que quieres modificar SI/1 NO/0");
            printf("\n>>> ");
            fflush(stdin);
            scanf("%d",&op1);
            if (op1 == 0)
            {
                puts("saliendo...");
                system("pause");
                return -1;
            }

        }
        printf("Ingrese el Nombre del Partido: ");
        fflush(stdin);
        gets(par.nombrePartido);
        fseek(ptr,pos,SEEK_SET);
        int falla1 = fwrite(&par,sizeof(Partidos),1,ptr);
        if (falla != 1)
        {
            puts("error de escritura");
            system("pause");
            return -1;
        }
        fflush(ptr);
        printf("\nEl nuevo partido con sus modificaciones es: ");
        printf("\nNombre del Partido: %s",par.nombrePartido);
        printf("\nQuieres modificar otro partido SI/1 NO/0\nOpcion: ");
        fflush(stdin);
        scanf("%d",&op);

        fseek(ptr,0,SEEK_END);
        int cant_partidos = ftell(ptr)/sizeof(Partidos);
        if (flag == 1)
        {
           fseek(ptr_mesas,0,SEEK_SET);
           falla = fread(&mesa,sizeof(mesas),1,ptr_mesas);
           if (falla != 1)
           {
               puts("error de lectura");
               exit(-1);
           }
           while(!feof(ptr_mesas))
           {
               for (int i=0;i<cant_partidos;i++)
               {
                   if (cod_part == mesa.par[i].codigo)
                   {
                       strcpy(mesa.par[i].nombrePartido,par.nombrePartido);
                   }
               }
               fread(&mesa,sizeof(mesas),1,ptr_mesas);
           }
           fseek(ptr_mesas,-sizeof(mesas),SEEK_CUR);
           falla = fwrite(&mesa,sizeof(mesas),1,ptr_mesas);
           fflush(ptr_mesas);
        }
    }while(op == 1);
    fclose(ptr);
    fclose(ptr_mesas);
}

int removerPartido()
{
    Partidos par;
    long int cod_part;
    int op,op1;
    FILE*ptr = fopen("Partidos.dat","r+b");
    if (ptr == NULL)
    {   puts("error al abrir el archivo");
        return -1;
    }
    do
    {
        fseek(ptr,0,SEEK_SET);
        int falla = fread(&par,sizeof(Partidos),1,ptr);
        if (falla != 1)
        {   puts("error de lectura");
            return -1;
        }
        // Mostrar información de posibles partidos a borrar
        while(!feof(ptr))
        {
            if (par.Borrado != 1)
            {
                printf("\nPartidos: ");
                printf("\nCodigo: %d",par.codigo);
                printf("\nNombre del Partido: %s",par.nombrePartido);
            }
            fread(&par,sizeof(Partidos),1,ptr);
        }

        printf("\nIngrese el codigo del partido: ");
        fflush(stdin);
        scanf("%d",&cod_part);
        long posArch = keyPartido(ptr,cod_part);
        if (posArch != -1)
        {
           fseek(ptr,posArch,SEEK_SET);
           int falla1 = fread(&par,sizeof(Partidos),1,ptr);
           if (falla1 != 1)
           {
              puts("error de lectura");
              return -1;
           }
            printf("\nCodigo: %d",par.codigo);
            printf("\nNombre del Partido: %s",par.nombrePartido);

            printf("\n\nEste es el partido que quieres eliminar SI/1 NO/0\nOpcion: ");
            fflush(stdin);
            scanf("%d",&op1);
            if (op1 == 0)
            {
                puts("saliendo...");
                system("pause");
                return 0;
            }
            par.Borrado = 1;
            fseek(ptr,posArch,SEEK_SET);
            int falla2 = fwrite(&par,sizeof(Partidos),1,ptr);
            if (falla2 != 1)
            {   puts("No se pudo eliminar el registro.");
                return -1;
            }
            fflush(ptr);
        }
        else
        {
            puts("no hay un partido con ese codigo");
            system("pause");
            return 0;
        }

        printf("\nQuiere eliminar otro partido SI/1 NO/0 \nOpcion: ");
        fflush(stdin);
        scanf("%d",&op);

    }while(op == 1);
    fclose(ptr);
    limpiezaPar();

    return 0;
}

int limpiezaPar()
{
    FILE *pf = fopen("Partidos.dat", "rb");
    if (pf == NULL)
    {
        puts("error de apertura del archivo Partidos.dat");
        return -1;
    }
    FILE*pf1 = fopen("Temporal.tmp","wb");
    if (pf1 == NULL)
    {
        puts("error de apertura");
        return -1;
    }

    Partidos par;

    fseek(pf,0,SEEK_SET);

    int falla = fread(&par,sizeof(Partidos),1,pf);
    if (falla != 1)
    {
        puts("error de lectura");
        return -1;
    }
    while(!feof(pf))
    {
        if (par.Borrado != 1)
        {
            fseek(pf1,0,SEEK_END);
            int falla1 = fwrite(&par,sizeof(Partidos),1,pf1);
            if(falla1 != 1)
            {
                puts("error de escritura");
                return -1;
            }
            fflush(pf1);
        }
        fread(&par,sizeof(Partidos),1,pf);
    }

    fclose(pf);
    fclose(pf1);

    if( remove("Partidos.dat") == 0)
    {
        printf("\nSe elimino Partidos.dat\n");
        if ( rename("Temporal.tmp", "Partidos.dat") == 0)
            printf("\nSe renombró Temporal.tmp a Partidos.dat\n");
        else
            printf("\nNo se pudo renombrar el archivo Temporal.tmp\n");
    }
    else
        puts("No se pudo eliminar Partidos.dat porque el archivo no existe.");

    system("pause");
    return 0;
}
long keyMesas(FILE*pf,long int key)
{
    mesas mesa;
    long int posReg = -1;
    fseek(pf,0,SEEK_SET);
    fread(&mesa,sizeof(mesas),1,pf);
    while(!feof(pf))
    {
        if (key == mesa.nroMesa)
        {
            posReg = ftell(pf) - sizeof(mesas);
        }
        fread(&mesa,sizeof(mesas),1,pf);
    }
    return posReg;
}
int limpiarMesa()
{
    FILE *pf = fopen("Mesas.dat", "rb");
    if (pf == NULL)
    {
        printf("\nError al abrir el archivo Mesas.dat\n");
        exit(-1);
    }
    FILE*pf1 = fopen("TemporalMesa.tmp","wb");
    if (pf1 == NULL)
    {
        puts("error de apertura");
        return -1;
    }
    mesas mesa;

    fseek(pf,0,SEEK_SET);
    int falla = fread(&mesa,sizeof(mesas),1,pf);
    if (falla != 1)
    {
        puts("error de lectura");
        return -1;
    }
    while(!feof(pf))
    {
        if (mesa.borrado != 1)
        {
            fseek(pf1,0,SEEK_END);
            int falla1 = fwrite(&mesa,sizeof(mesas),1,pf1);
            if(falla1 != 1)
            {
                puts("error de escritura");
                return -1;
            }
            fflush(pf1);
        }
        fread(&mesa,sizeof(mesas),1,pf);
    }
    fclose(pf1);
    fclose(pf);

    if( remove("Mesas.dat") == 0)
    {
        printf("\nSe elimino Mesas.dat\n");
        if ( rename("TemporalMesa.tmp", "Mesas.dat") == 0)
            printf("\nSe renombró TemporalMesa.tmp a Mesas.dat\n");
        else
            printf("\nNo se pudo renombrar el archivo TemporalMesa.tmp\n");
    }
    else
        puts("No se pudo eliminar Mesas.dat");

    system("pause");
    return 0;

}

int escribirMesa()
{
    FILE *ptr_M = fopen("Mesas.dat","a+b");
    if (ptr_M == NULL)
    {
        puts("error al abrir el archivo");
        return -1;
    }
    FILE *ptr_P = fopen("Partidos.dat","rb");
    if (ptr_P == NULL)
    {
        puts("error al abrir el archivo");
        return -1;
    }
    int op;
    long int accum = 0;
    int i=0;
    mesas mesa;
    Partidos par;
 /* Info de mesas */
    do
    {
        printf("\nIngrese el numero de la mesa: ");
        fflush(stdin);
        scanf("%ld",&mesa.nroMesa);
        if (keyMesas(ptr_M,mesa.nroMesa) != -1 )
            printf("\nYa existe la mesa %ld",mesa.nroMesa);

    } while (keyMesas(ptr_M,mesa.nroMesa) != -1);

    fseek(ptr_P,0,SEEK_END);

    long cant_par = ftell(ptr_P)/sizeof(Partidos);

    if (cant_par == 0) {
        printf("\nDebe existir al menos un partido para crear la mesa\n");
        return -1;
    }
    fseek(ptr_P,0,SEEK_SET);
    int falla = fread(&par,sizeof(Partidos),1,ptr_P);
    if (falla != 1)
    {   puts("error de lectura");
        exit(-1);
    }
    while (!feof(ptr_P))
    {
        mesa.par[i] = par;
        i++;
        fread(&par,sizeof(Partidos),1,ptr_P);
    }
    /* Info de mesas */
    /* Ingreso de votos */
    printf("\nIngrese la cantidad de votos de cada partido\n ");
    for (i =0; i < cant_par; i++)
    {
        int votos_presi, votos_gob;

        printf("Partido [%li]\n", mesa.par[i].codigo);
        printf("Nombre [%s]\n", mesa.par[i].nombrePartido);
        printf("\nVotos a Presidente: ");
        fflush(stdin);
        scanf("%i", &votos_presi);
        mesa.par[i].cant_votos_presi = votos_presi;

        printf("\nVotos a Gobernador: ");
        fflush(stdin);
        scanf("%i", &votos_gob);

        mesa.par[i].cant_votos_gober = votos_gob;

        accum += mesa.par[i].cant_votos_presi;
        accum += mesa.par[i].cant_votos_gober;
    }
    printf("\nIngrese la cantidad de votos en blanco: ");
    fflush(stdin);
    scanf("%ld",&mesa.votos_blanco);
    printf("\nIngrese la cantidad de votos impugnados: ");
    fflush(stdin);
    scanf("%ld",&mesa.votos_impug);

    accum += mesa.votos_blanco;
    accum += mesa.votos_impug;

    mesa.votos = accum;

    printf("\n");
    fseek(ptr_M,0,SEEK_END);
    fwrite(&mesa,sizeof(mesas),1,ptr_M);
    fflush(ptr_M);
    fclose(ptr_M);
    fclose(ptr_P);
    ordenar_mesas();

    return 0;
}
int mostrarMesas()
{
    FILE *ptr_M = fopen("Mesas.dat","rb");
    if (ptr_M == NULL)
    {
        puts("Error al abrir el archivo1");
        exit(-1);
    }
    FILE *ptr_P = fopen("Partidos.dat","rb");
    if (ptr_P == NULL)
    {
        puts("error al abrir el archivo2");
        exit(-1);
    }
    mesas mesa;
    Partidos par;
    fseek(ptr_P,0,SEEK_END);
    long cant_par = ftell(ptr_P)/sizeof(Partidos);

    fseek(ptr_M,0,SEEK_SET);
    int falla = fread(&mesa,sizeof(mesas),1,ptr_M);

    if (falla != 1)
    {
        puts("error de lectura");
        exit(-1);
    }
    while(!feof(ptr_M))
    {
        printf("\nMesa Numero: %ld\n",mesa.nroMesa);
        for(int i = 0; i < cant_par ;i++ )
        {
            printf("\nPartido [%s]\n", mesa.par[i].nombrePartido);
            printf("\nVotos a Presidente: %li\n",mesa.par[i].cant_votos_presi);
            printf("\nVotos a Gobernador: %li",mesa.par[i].cant_votos_gober);
        }
        fread(&mesa,sizeof(mesas),1,ptr_M);
        printf("\n");
    }
    fclose(ptr_M);
    fclose(ptr_P);

    return 0;
}


int Baja_Mesa() // Baja lógica de la mesa
{
    FILE*ptr_M = fopen("Mesas.dat","r+b");
    if (ptr_M == NULL)
    {   puts("error al abrir el archivo1");
        exit(-1);
    }
    int op1;
    mesas mesa;
    long int cod_mesa;
    long int pos;
    do
    {
        printf("\nIngresa en numero de mesa: ");
        fflush(stdin);
        scanf("%li",&cod_mesa);
        pos = keyMesas(ptr_M,cod_mesa);
        if (pos == -1)
        {
            puts("Mesa inexistente");
            system("pause");
        }

    } while(pos == -1);

    fseek(ptr_M,pos,SEEK_SET);
    int falla = fread(&mesa,sizeof(mesas),1,ptr_M);
    if (falla != 1)
    {
        puts("error de lectura");
        exit(-1);
    }
    printf("\nNro. de Mesa: [%li]",mesa.nroMesa);

    printf("¿\nEsta es la mesa que deseas borrar? [1]SI [0]NO\nOpcion: ");
    fflush(stdin);
    scanf("%d",&op1);
    if(op1 == 0)
       return -1;
    else
    {
        mesa.borrado = 1;
        fseek(ptr_M,pos,SEEK_SET);
        fwrite(&mesa,sizeof(mesas),1,ptr_M);
        fflush(ptr_M);
    }
    fclose(ptr_M);
    limpiarMesa(); // Proceso de baja fisica

    return 0;
}


int info_Mesa()
{
    FILE *ptr_M = fopen("Mesas.dat", "rb");
    FILE *ptr_P = fopen("Partidos.dat", "rb");

    int op;
    mesas mesa;
    Partidos par;
    long int codigo_mesa;
    fseek(ptr_P,0,SEEK_END);

    int cant_par = ftell(ptr_P)/sizeof(Partidos);
    do
    {

        printf("\nIngrese el numero de mesa: ");
        fflush(stdin);
        scanf("%ld",&codigo_mesa);
        long int pos = keyMesas(ptr_M,codigo_mesa);
        if (pos == -1)
        {
            printf("\nMesa inexistente\n");
            system("pause");
            return -1;
        }
        fseek(ptr_M,pos,SEEK_SET);
        int falla = fread(&mesa,sizeof(mesas),1,ptr_M);
        if (falla != 1)
        {
            puts("error de lectura");
            exit(-1);
        }
        system("cls");
        printf("Mesa [%li]\n", mesa.nroMesa);
        printf("\nTotal de votos: [%li]\n", mesa.votos);

        printf("\nVotos en Blanco: %ld\t%.2f%c", mesa.votos_blanco, (((float)mesa.votos_blanco/(float)mesa.votos)*100), 37);
        printf("\nVotos Impugnados: %ld\t%.2f%c", mesa.votos_impug, (((float)mesa.votos_impug/(float)mesa.votos)*100), 37);
        printf("\n\nVotos a partidos\n");

        for(int i=0;i<cant_par;i++)
        {
            printf("\nPartido [%s]", mesa.par[i].nombrePartido);
            printf("\nVotos a Presidente [%li] [%.2f%c]", mesa.par[i].cant_votos_presi, (((float)mesa.par[i].cant_votos_presi/(float)mesa.votos)*100), 37 );
            printf("\nVotos a Gobernador [%li] [%.2f%c]", mesa.par[i].cant_votos_gober, (((float)mesa.par[i].cant_votos_gober/(float)mesa.votos)*100), 37);
            printf("\n");
        }

        printf("\nQuieres buscar otra mesa?\nSI/1 NO/0\n>>>");
        fflush(stdin);
        scanf("%d",&op);

    }while(op != 0);

    return 0;
}

